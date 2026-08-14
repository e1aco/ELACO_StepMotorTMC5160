#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""can_send_test.py — 通过 PCAN 发送运动命令并监听反馈（复现/验证抖动停锁）

协议（require.md # CAN 协议）：
  命令帧 0x1AA55F42: [0-3]值(int32 LE) [4]命令码 [5]电机 [6]参数组 [7]校验和
  反馈帧 0x1AA55F43: [0-3]值(int32 LE) [4]状态位 [5]电机 [6]温度/保护 [7]校验和
    问题判据: 反馈 byte[6] 最低三位非 0 → bit0=OTPW, bit1=OT, bit2=drv_err(保护关断)

用法:
  python can_send_test.py                          # 默认复现 trace 序列
  python can_send_test.py --cycles 5 --interval 3.8
  python can_send_test.py --value1 200 --value2 51200 --group 3 --motor 1
  python can_send_test.py --cmd 4 --value1 20000   # 速度模式
"""

import argparse
import sys
import time
import datetime

CMD_TX_ID = 0x1AA55F42
RSP_TX_ID = 0x1AA55F43   # 反馈
DBG_TX_ID = 0x1AA55F44   # 遥测

STATUS_BITS = [
    (0x01, "到位"),
    (0x02, "失步"),
    (0x04, "过温"),
    (0x08, "驱动错误"),
    (0x10, "SPI异常"),
]
PROTECT_BITS = [
    (0x01, "OTPW"),
    (0x02, "OT"),
    (0x04, "drv_err"),
    (0x08, "S2GA"),
    (0x10, "S2GB"),
    (0x20, "S2VSA"),
    (0x40, "S2VSB"),
    (0x80, "失步"),
]


def checksum(data):
    return sum(data[:7]) & 0xFF


def make_cmd(value, cmd=0x01, motor=0x01, group=0x03):
    b = bytearray(8)
    v = int(value) & 0xFFFFFFFF
    b[0] = v & 0xFF
    b[1] = (v >> 8) & 0xFF
    b[2] = (v >> 16) & 0xFF
    b[3] = (v >> 24) & 0xFF
    b[4] = cmd & 0xFF
    b[5] = motor & 0xFF
    b[6] = group & 0xFF
    b[7] = checksum(b)
    return b


def fmt_flags(byte, table):
    parts = [name for bit, name in table if byte & bit]
    return "+".join(parts) if parts else "-"


def parse_args():
    p = argparse.ArgumentParser(description="PCAN 发送运动命令 + 监听反馈")
    p.add_argument("--channel", default="PCAN_USBBUS1")
    p.add_argument("--bitrate", type=int, default=500000)
    p.add_argument("--cmd", type=lambda s: int(s, 0), default=0x01,
                   help="命令码: 1=绝对位置 2/3=相对正/反 4=速度 5=停止")
    p.add_argument("--motor", type=lambda s: int(s, 0), default=0x01,
                   help="电机: 0x01=U1 0x02=U2 0x06=ALL")
    p.add_argument("--value1", type=lambda s: int(s, 0), default=200)
    p.add_argument("--value2", type=lambda s: int(s, 0), default=51200)
    p.add_argument("--group", type=lambda s: int(s, 0), default=0x03)
    p.add_argument("--interval", type=float, default=3.8,
                   help="两次命令间隔秒（复现 trace 用 3.8）")
    p.add_argument("--cycles", type=int, default=0,
                   help="命令轮数(0=无限, 每轮一条命令)")
    p.add_argument("--problem-only", action="store_true",
                   help="只在问题(byte[6]!=0)时打印，静默正常帧")
    p.add_argument("--no-dbg", action="store_true",
                   help="不打印 0x1AA55F44 遥测帧")
    p.add_argument("--dbg-alarm", action="store_true",
                   help="只打印报警遥测: FAULT 帧 / A= 非 - 非 OTPW")
    p.add_argument("--setup", default="",
                   help="循环前先发一条设置命令, 格式 cmd,motor,value,group(0x可) e.g. 04,02,20000,03")
    p.add_argument("--log", default=".cl/capture/send_test.log",
                   help="回传日志文件")
    return p.parse_args()


def main():
    args = parse_args()
    try:
        import can
    except ImportError:
        sys.stderr.write("[cl] 缺少 python-can: pip install python-can\n")
        return 1

    try:
        bus = can.Bus(interface="pcan", channel=args.channel,
                      bitrate=args.bitrate)
    except Exception as exc:  # noqa: BLE001
        sys.stderr.write(f"[cl] 无法打开 PCAN {args.channel}: {exc}\n")
        return 1

    t0 = time.time()

    def log(line, fh=None):
        ts = datetime.datetime.now().strftime("[%H:%M:%S.%f")[:-3] + "]"
        s = f"{ts} {line}"
        print(s, flush=True)
        if fh:
            fh.write(s + "\n")
            fh.flush()

    fh = None
    if args.log:
        import os
        os.makedirs(os.path.dirname(args.log) or ".", exist_ok=True)
        fh = open(args.log, "w", encoding="utf-8")
        fh.write("# can_send_test start\n")

    motor_name = {0x01: "U1", 0x02: "U2", 0x06: "ALL"}.get(args.motor,
                                                          hex(args.motor))
    log(f"命令: cmd={args.cmd} {motor_name} 值[{args.value1}/{args.value2}] "
        f"组{args.group} 间隔{args.interval}s 轮数{args.cycles or '无限'}",
        fh)

    def is_alarm(txt):
        if "FAULT" in txt:
            return True
        if "A=" not in txt:
            return False
        return not (("A=-" in txt) or ("A=OTPW" in txt))

    cycle = 0
    values = [args.value1, args.value2]
    try:
        if args.setup:
            parts = [x.strip() for x in args.setup.split(",")]
            if len(parts) == 4:
                def pv(s):
                    s = s.strip()
                    return int(s, 16) if s.lower().startswith("0x") else int(s, 10)
                scmd = pv(parts[0])
                smot = pv(parts[1])
                sval = pv(parts[2])
                sgrp = pv(parts[3])
                bus.send(can.Message(
                    arbitration_id=CMD_TX_ID, data=make_cmd(sval, scmd, smot, sgrp),
                    is_extended_id=True))
                log(f"SETUP cmd={scmd} motor={smot:#04x} value={sval} group={sgrp}", fh)
                time.sleep(0.5)
        while True:
            if args.cycles and cycle >= args.cycles:
                break
            value = values[cycle % 2]
            data = make_cmd(value, args.cmd, args.motor, args.group)
            bus.send(can.Message(arbitration_id=CMD_TX_ID, data=data,
                                 is_extended_id=True))
            log(f"TX  0x{CMD_TX_ID:X} {data.hex()}  "
                f"cmd={args.cmd} {motor_name} pos={value} group={args.group}",
                fh)
            cycle += 1

            # 监听反馈直到下一条命令：重点看 byte[6]
            deadline = time.time() + args.interval
            while time.time() < deadline:
                frame = bus.recv(timeout=0.05)
                if frame is None:
                    continue
                if frame.arbitration_id == RSP_TX_ID:
                    d = bytes(frame.data[:8])
                    value_rx = int.from_bytes(d[0:4], "little", signed=True)
                    status = d[4]
                    motor = d[5]
                    protect = d[6]
                    ok = (status, protect)  # noqa: F841
                    # 问题判据: drv_err | S2 短路位 | 失步（OTPW 仅提示，不算问题）
                    if (not args.problem_only) or (protect & 0xFE):
                        log(
                            f"RX  0x{RSP_TX_ID:X} {d.hex()} "
                            f"值={value_rx} 状态={status:02X}({fmt_flags(status, STATUS_BITS)}) "
                            f"byte6={protect:02X}({fmt_flags(protect, PROTECT_BITS)})",
                            fh)
                    if protect & 0xFE:
                        log("!!! 问题: 驱动保护/失步（byte[6] 含 drv_err/S2/失步 位）!!!", fh)
                elif frame.arbitration_id == DBG_TX_ID:
                    try:
                        txt = bytes(frame.data[:8]).decode("latin-1")
                    except Exception:  # noqa: BLE001
                        txt = bytes(frame.data[:8]).hex()
                    if not args.no_dbg:
                        show = (not args.problem_only) and (
                            (not args.dbg_alarm) or is_alarm(txt))
                        if show:
                            log(f"DBG 0x{DBG_TX_ID:X} {txt!r}", fh)
                        elif fh:
                            fh.write(f"DBG 0x{DBG_TX_ID:X} {txt!r}\n")
                            fh.flush()
    except KeyboardInterrupt:
        print("\n[cl] 已中断")
    finally:
        if fh:
            fh.close()
        bus.shutdown()
    return 0


if __name__ == "__main__":
    sys.exit(main())
