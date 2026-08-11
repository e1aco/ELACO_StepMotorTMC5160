# 硬件修正记录（本项目级）

> 记录实测发现的硬件/寄存器修正，/cl run 生成代码时优先读取。

## 初始化状态

- (暂无记录，等待第一次调试后填写)

## 注意事项

- TMC5160 调试遥测（0x1AA55F44 CAN 周期帧）读到 `DRV_STATUS=FFFFFFFF`、`S=10`（SPI 异常）时，**先确认是否已给 TMC5160 上 24V 驱动电源**——未供电时 SPI 读回全 1 属正常，非代码问题。

- TMC5160 SPI3: CPOL=High, CPHA=2Edge (模式3), 2.625 Mbps, 32-bit 数据帧（4.1 节 SPI DATAGRAM）
- TMC5160 地址位 AD0/AD1 接法决定 SPI 地址，需按板卡确认（U1/U2）
- 0.05R 电流采样电阻：IHOLD/IRUN 电流换算按第9节 SELECTING SENSE RESISTORS

## 项目专属配置推导（2026-08-10，代入电机+MOS 参数，取代 datasheet 默认值）

> 器件代入：电机 57CME13 额定 4A/电感 1.6mH/相阻 0.42Ω/36V；MOS AOD4126 Qgd=10nC(typ)；
> RSENSE=0.05Ω，VFS(VSRT)=325mV(ch28.p123)，fCLK=14MHz(TIM4_CH1, Period=5, Prescaler=0)。

| 寄存器 | 项目推导值 | 依据 | 取代的 datasheet 默认 |
|--------|-----------|------|----------------------|
| DRV_CONF.DRVSTRENGTH | **0**(weak) | ch03.p17 表3.3：Qgd=10nC∈10~20nC → 0/1，取最小 0；复位 %10(medium) 过强致开关振铃发热 | %10(medium)=2 |
| IHOLD_IRUN.IRUN | **27** → 4.02A RMS | ch09.p74 公式 `IRMS=(CS+1)/32×VFS/RSENSE/√2`，代入 4A 额定：CS=27 | (复位默认未定义) |
| IHOLD_IRUN.IHOLD | **8** → 约1.2A RMS | 保持力矩 1.3N.m 充足 + 静止降热 | 0 |
| IHOLD_IRUN.IHOLDDELAY | 6 | ch06.p038：平滑降流 | 0 |
| PWMCONF.PWM_FREQ | **%01** → 41.0kHz | ch07.p60 表7.1：`fPWM=2/683×14MHz=41.0kHz`，落 36~48kHz 推荐区；复位 %00=27.3kHz 偏低(铁损/可听) | %00=27.3kHz |
| PWMCONF 整体 | **0xC40D001E** | 复位 0xC40C001E 仅改 bit16(PWM_FREQ=%01)，pwm_autoscale/autograd=1 保留 | 0xC40C001E |
| CHOPCONF | TOFF=5/TBL=01/MRES=0(256微步) | ch07 CN：StealthChop 下 TOFF 仅使能电机；注释修正 HSTRT 实为 0 | 0x10410150 |
