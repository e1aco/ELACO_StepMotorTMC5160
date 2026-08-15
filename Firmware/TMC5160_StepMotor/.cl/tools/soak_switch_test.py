#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""soak_switch_test.py — U2 持续速度运转 + U1 快速方向切换暴力测试（单进程独占 PCAN）

协议（require.md # CAN 协议）:
  命令 0x1AA55F42: [0-3]值(int32 LE) [4]命令码 [5]电机 [6]参数组 [7]校验和
  反馈 0x1AA55F43:  [0-3]值 [4]状态位 [5]电机 [6]保护位(bit0=OTPW bit2=drv_err bit3-6=S2 bit7=失步) [7]校验和
  遥测 0x1AA55F44:  文本分帧("CAN 当串口"), 按 ID 还原, 判据 A= 字段/S=10/FAULT

判据（问题帧 = 任一项）:
  A= 非 OTPW/- 的报警 (RESET/DRVERR/UVCP/S2GA/S2GB/S2VSA/S2VSB/OT/OLA/OLB)
  S=10 (SPI 异常)
  FAULT 快照帧
  F43 反馈 byte[6] & 0xFE (drv_err|S2|失步)

用法:
  python soak_switch_test.py [--rounds 50] [--interval 0.5] [--value 51200]
                             [--u2-vel 20000] [--group 3] [--log <file>] [--status <file>]
"""

import argparse
import datetime
import os
import re
import sys
import time

CMD_TX_ID = 0x1AA55F42
RSP_TX_ID = 0x1AA55F43
DBG_TX_ID = 0x1AA55F44

PROBLEM_PATTERNS = [
    (re.compile(r"A=(?!OTPW,|-)[A-Z0-9]+"), "A-alarm"),
    (re.compile(r"S=10"), "SPI-err"),
    (re.compile(r"FAULT"), "FAULT-frame"),
]

PROTECT_BITS = [
    (0x01, "OTPW"), (0x02, "OT"), (0x04, "drv_err"),
    (0x08, "S2GA"), (0x10, "S2GB"), (0x20, "S2VSA"),
    (0x40, "S2VSB"), (0x80, "失步"),
]


def checksum(data):
    return sum(data[:7]) & 0xFF


def make_cmd(value, cmd, motor, group):
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
    return bytes(b)


def fmt_flags(byte, table):
    parts = [name for bit, name in table if byte & bit]
    return "+".join(parts) if parts else "-"


class Soak:
    def __init__(self, args):
        self.args = args
        self.problems = 0
        self.last_problem = ""
        self.updated = "-"
        self.tx_count = 0
        self.total_lines = 0
        self.updated_line = "-"
        self.partial = bytearray()
        self.pat_counts = [0] * len(PROBLEM_PATTERNS)
        self.rsp_problem = 0
        self.dec_err = 0
        self.rec_warn = 0
        self._recon_last = 0
        os.makedirs(os.path.dirname(args.log) or ".", exist_ok=True)
        self.fh = open(args.log, "w", encoding="utf-8")
        self.fh.write("# soak_switch_test start\n")

    def log(self, line):
        ts = datetime.datetime.now().strftime("[%H:%M:%S.%f")[:-3] + "]"
        self.fh.write(ts + " " + line + "\n")
        self.fh.flush()

    def on_line(self, text):
        self.total_lines += 1
        self.updated = datetime.datetime.now().strftime("[%H:%M:%S.%f")[:-3] + "]"
        self.updated_line = text
        if "\ufffd" in text:
            self.dec_err += 1
        self.log("DBG %s" % text)
        for i, (re_ptn, name) in enumerate(PROBLEM_PATTERNS):
            if re_ptn.search(text):
                self.pat_counts[i] += 1
                self.problems += 1
                self.last_problem = "%s [%s] %s" % (self.updated, name, text)
                self.log("!!! PROBLEM %s %s" % (name, text))
                break

    def feed_dbg(self, payload):
        self.partial.extend(payload)
        while True:
            nl = self.partial.find(b"\n")
            if nl < 0:
                break
            chunk = self.partial[: nl + 1].rstrip(b"\r\n")
            del self.partial[: nl + 1]
            text = chunk.decode("utf-8", errors="replace")
            text = re.sub(r"^[\ufffd\x00-\x1f]+", "", text)
            if text.strip():
                self.on_line(text)
        if len(self.partial) > 512 and len(self.partial) > self._recon_last + 256:
            self.rec_warn += 1
            self._recon_last = len(self.partial)
        elif len(self.partial) < 256:
            self._recon_last = 0

    def feed_rsp(self, data):
        if len(data) < 8:
            return
        value_rx = int.from_bytes(data[0:4], "little", signed=True)
        status = data[4]
        motor = data[5]
        protect = data[6]
        self.log("RX cmd=%d m=%d val=%d st=%02X(%s) b6=%02X(%s)" % (
            -1, motor, value_rx, status, fmt_flags(status, [
                (0x01, "到位"), (0x02, "失步"), (0x04, "过温"),
                (0x08, "驱动错误"), (0x10, "SPI异常")]),
            protect, fmt_flags(protect, PROTECT_BITS)))
        if protect & 0xFE:
            is_u1 = (motor == 0x01)
            real_issue = (protect & 0xFE) if is_u1 else (protect & 0x7E)
            if real_issue:
                self.rsp_problem += 1
                self.problems += 1
                self.last_problem = "%s [F43-byte6] m=%d b6=%02X" % (
                    datetime.datetime.now().strftime("[%H:%M:%S.%f")[:-3] + "]", motor, protect)
                self.log("!!! PROBLEM [F43-byte6] m=%d b6=%02X(%s)" % (
                    motor, protect, fmt_flags(protect, PROTECT_BITS)))

    def write_status(self):
        if not self.args.status:
            return
        lines = [
            "updated: %s" % self.updated,
            "lines: %d" % self.total_lines,
            "tx_count: %d" % self.tx_count,
            "problems: %d" % self.problems,
            "last_problem: %s" % (self.last_problem[:200] if self.last_problem else "-"),
            "patterns:",
        ]
        for (_, name), c in zip(PROBLEM_PATTERNS, self.pat_counts):
            lines.append("  %s: %d" % (name, c))
        lines.append("rsp_problem: %d" % self.rsp_problem)
        lines.append("decode_errors: %d reconstruct_warn: %d" % (self.dec_err, self.rec_warn))
        try:
            tmp = self.args.status + ".tmp"
            with open(tmp, "w", encoding="utf-8") as f:
                f.write("\n".join(lines) + "\n")
            os.replace(tmp, self.args.status)
        except OSError:
            pass

    def close(self):
        self.write_status()
        self.fh.close()


def main():
    p = argparse.ArgumentParser(description="U2 速度 + U1 方向快速切换暴力测试")
    p.add_argument("--channel", default="PCAN_USBBUS1")
    p.add_argument("--rounds", type=int, default=50, help="往返轮数（每轮 +V 和 -V 各一次）")
    p.add_argument("--interval", type=float, default=0.5, help="命令间隔秒")
    p.add_argument("--value", type=lambda s: int(s, 0), default=51200)
    p.add_argument("--u2-vel", type=lambda s: int(s, 0), default=20000)
    p.add_argument("--group", type=lambda s: int(s, 0), default=0x03)
    p.add_argument("--log", default=".cl/capture/soak_switch.log")
    p.add_argument("--status", default=".cl/capture/soak_status")
    args = p.parse_args()

    try:
        import can
    except ImportError:
        sys.stderr.write("[cl] 缺少 python-can\n")
        return 1

    try:
        bus = can.Bus(interface="pcan", channel=args.channel, bitrate=500000)
    except Exception as exc:
        sys.stderr.write("[cl] 无法打开 PCAN %s: %s\n" % (args.channel, exc))
        return 1

    soak = Soak(args)
    soak.log("start rounds=%d interval=%s value=%d u2_vel=%d group=%d" % (
        args.rounds, args.interval, args.value, args.u2_vel, args.group))

    bus.send(can.Message(arbitration_id=CMD_TX_ID,
                         data=make_cmd(args.u2_vel, 0x04, 0x02, args.group),
                         is_extended_id=True))
    soak.tx_count += 1
    soak.log("TX U2 vel=%d" % args.u2_vel)

    last_tx = time.monotonic()
    round_no = 0
    next_sign = 1
    end = time.monotonic() + args.rounds * 2 * args.interval + 10
    try:
        while True:
            now = time.monotonic()
            if round_no >= args.rounds:
                soak.log("rounds done, drain 3s")
                if time.monotonic() > end:
                    break
            elif now - last_tx >= args.interval:
                value = args.value * next_sign
                bus.send(can.Message(arbitration_id=CMD_TX_ID,
                                     data=make_cmd(value, 0x01, 0x01, args.group),
                                     is_extended_id=True))
                soak.tx_count += 1
                round_no += 1
                next_sign = -next_sign
                last_tx = now
                soak.log("TX U1 %s %d (round %d/%d)" % (
                    "+" if value >= 0 else "-", value, round_no, args.rounds))

            frame = bus.recv(timeout=0.05)
            if frame is None:
                soak.write_status()
                continue
            if frame.arbitration_id == DBG_TX_ID:
                soak.feed_dbg(bytes(frame.data[:frame.dlc]) if frame.dlc else b"")
            elif frame.arbitration_id == RSP_TX_ID:
                soak.feed_rsp(bytes(frame.data[:frame.dlc]) if frame.dlc else b"")
            soak.write_status()
    except KeyboardInterrupt:
        soak.log("interrupted")
    finally:
        soak.log("done problems=%d" % soak.problems)
        soak.close()
        bus.shutdown()
    return 0


if __name__ == "__main__":
    sys.exit(main())