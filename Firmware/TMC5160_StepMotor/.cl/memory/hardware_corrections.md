# 硬件修正记录（本项目级）

> 记录实测发现的硬件/寄存器修正，/cl run 生成代码时优先读取。

## 初始化状态

- (暂无记录，等待第一次调试后填写)

## 注意事项

- TMC5160 调试遥测（0x1AA55F44 CAN 周期帧）读到 `DRV_STATUS=FFFFFFFF`、`S=10`（SPI 异常）时，**先确认是否已给 TMC5160 上 24V 驱动电源**——未供电时 SPI 读回全 1 属正常，非代码问题。

- TMC5160 SPI3: CPOL=High, CPHA=2Edge (模式3), 2.625 Mbps, 32-bit 数据帧（4.1 节 SPI DATAGRAM）
- TMC5160 地址位 AD0/AD1 接法决定 SPI 地址，需按板卡确认（U1/U2）
- 0.05R 电流采样电阻：IHOLD/IRUN 电流换算按第9节 SELECTING SENSE RESISTORS

## 2026-08-14 双机 S2 短路闩存故障修复（CAN 反馈 byte6 + FaultMonitor）

### 现象
双机运行（U2 速度模式 + U1 200↔51200µ步快速切换）时，U1 偶发进入 S2 对地/对电源短路保护闩存（DRV_STATUS s2gb=0x801B4003 / s2ga+s2vsa 等），**驱动停止保持扭矩→"停止锁轴"**，编码器与 XACTUAL 脱开（实测编码器冻结在 -50995）。反馈 byte6 只显示 0x01(OTPW)，**0x04 判据抓不到 S2**。

### 根因
1. **byte6 未含 S2 短路位**：固件 protect_flags 只含 OTPW/OT/GSTAT drv_err，S2 位（s2ga/s2gb/s2vsa/s2vsb）漏报；GSTAT drv_err 被周期读清，0x04 只在快照瞬间出现，判据不可靠。
2. **OTPW 被当硬故障**：FaultMonitor 掩码含 bit26(otpw)，电机过热(OTPW 120°C 警告)即触发闩存+每 1s ENN 翻转恢复（can_usr.c FaultMonitor），反复关断/使能运行中的驱动器产生电流瞬变，**诱发 S2 短路误触发**，形成 抖动→锁轴 放大器。

### 修复（module/usr/can_usr.c）
1. `USR_CAN_SendMotionFeedback` byte6 增加位：bit3=S2GA(27), bit4=S2GB(28), bit5=S2VSA(12), bit6=S2VSB(13), bit7=失步(ENC_STATUS deviation_warn)；保留 bit0=OTPW, bit1=OT, bit2=drv_err。
2. FaultMonitor 两处故障掩码剔除 `(1UL<<26)`(OTPW)，OTPW 只上报不闩存不恢复。

### 验证（ST-Link 烧录后，PCAN 实测 2026-08-14）
- U1 单独 200↔51200：编码器跟随、无失步、byte6=01(OTPW) 仅提示，零 FAULT。
- 双机 15 轮（U2 vel 20000 + U1 切换 2.5s）：全程编码器完美跟随（243→51200→204...）、无 S2/失步/drv_err、零 FAULT、板子全程响应。
- 结论：OTPW→ENN 翻转→S2 误触发放大链已切断，双机快速切换不再锁轴。

### 热致 S2 假触发根因定位与修复（2026-08-14 第二轮）
- 长浸泡复现：S2GA/S2GB **假触发**在 4A 全电流 + 持续运行至 OTPW(120°C) 后出现，方向相关（原仅 +51200，TBL 加长后 ± 方向及静止均现），每次闩存轴自由漂移 ~3.7万步→编码器基准永久偏移→失步永久误报（X_ENC 与 XACTUAL 失准，需断电清除，固件无归零命令）。
- 修复链：
  1. **CHOPCONF.TBL %10(36clk)→%11(54clk)**：死区加长仅推迟首次触发（3.5→5.6min），未根除。
  2. **IRUN 27(4A)→20(3A)**：热功率↓~44%，**根除 S2 假触发**。验证：双机 150 轮浸泡（U2 vel 20000 + U1 200↔51200@2.5s）0 次 S2/失步/drv_err/FAULT，移动量精确 ±51200 无丢步，仅 byte6=01(OTPW) 提示。
- **OTPW 是持续现象（芯片结温高，升温快）**，但已不触发闩存/恢复，属无害提示。

### 监控判据更新
PCAN 监控问题判据：`byte6 & 0xFE`（drv_err|S2|失步），不再是 `byte6==0x04`。测试脚本 `.cl/tools/can_send_test.py` 已同步。

## 项目专属配置推导（2026-08-10，代入电机+MOS 参数，取代 datasheet 默认值）

> 器件代入：电机 57CME13 额定 4A/电感 1.6mH/相阻 0.42Ω/36V；MOS AOD4126 Qgd=10nC(typ)；
> RSENSE=0.05Ω，VFS(VSRT)=325mV(ch28.p123)，fCLK=14MHz(TIM4_CH1, Period=5, Prescaler=0)。

| 寄存器 | 项目推导值 | 依据 | 取代的 datasheet 默认 |
|--------|-----------|------|----------------------|
| DRV_CONF.DRVSTRENGTH | **0**(weak) | ch03.p17 表3.3：Qgd=10nC∈10~20nC → 0/1，取最小 0；复位 %10(medium) 过强致开关振铃发热 | %10(medium)=2 |
| IHOLD_IRUN.IRUN | **20** → 3.02A RMS | ch09.p74 公式 `IRMS=(CS+1)/32×VFS/RSENSE/√2`；2026-08-14 由 27(4A) 降下：双机持续 4A 至 OTPW 后 S2 短路比较器热漂移误触发，降流热功率↓44% | 27 → 4.02A RMS |
| IHOLD_IRUN.IHOLD | **8** → 约1.2A RMS | 保持力矩 1.3N.m 充足 + 静止降热 | 0 |
| IHOLD_IRUN.IHOLDDELAY | 6 | ch06.p038：平滑降流 | 0 |
| PWMCONF.PWM_FREQ | **%01** → 41.0kHz | ch07.p60 表7.1：`fPWM=2/683×14MHz=41.0kHz`，落 36~48kHz 推荐区；复位 %00=27.3kHz 偏低(铁损/可听) | %00=27.3kHz |
| PWMCONF 整体 | **0xC40D001E** | 复位 0xC40C001E 仅改 bit16(PWM_FREQ=%01)，pwm_autoscale/autograd=1 保留 | 0xC40C001E |
| CHOPCONF | TOFF=5/TBL=%11(54clk)/MRES=%0000(256微步) | 值 0x000181C5。注意 TMC5160 位定义：TBL=bit[16:15]、MRES=bit[27:24]、diss2vs=bit31、diss2g=bit30、HSTRT/HEND 在 StealthChop 忽略；2026-08-14 由 %10(36clk) 加长至 %11 抑制 S2GA 误触发 | 0x000101C5 |
