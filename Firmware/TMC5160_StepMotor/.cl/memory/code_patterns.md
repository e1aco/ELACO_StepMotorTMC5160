# 代码惯用法记录（本项目级）

> 记录本项目的代码模式约定，/cl run 生成代码时遵循。

## 实现来源约束（用户确认 2026-08-05，更新于 2026-08-05）

- [2026-08-05 更新] 当前任务为移植 `C:\Users\admin\Desktop\XM\ELACO_StepMotorTMC5160\AIFirmware\StepMotorDriver_Keil` 项目内容，**允许参考并移植该 Keil 项目代码**（用户 /cl gon 时明确决定）。
- 移植代码须按 11.5「复刻/移植既有代码」规则消化为 cl 可循骨架（保留逻辑、重命名符合命名空间、补文件头/段标记、不照抄）。
- 寄存器操作/时序仍须核对 `.cl/datasheet/*.md`，数据手册为依据，外部项目仅作移植来源。

## 命名空间与分层

- 模块前缀: `tmc`（TMC5160 驱动）→ `tmc_drv.c/h`（SPI 寄存器原语）+ `tmc_usr.c/h`（运动业务逻辑）
- 分层: DRV_ 仅 SPI/寄存器操作；USR_ 仅调 DRV_ API
- 引用依据: `.cl/datasheet/TMC5160A_Datasheet_Rev1.14.md`

## 现有 CubeMX 外设（勿重复初始化）

- SPI3: 主模式，模式3，2.625 Mbps
- TIM4_CH1 (PB6): TMC_CLK (Period=5 → 14MHz 步进时钟源)
- TIM2_CH3 (PB10) / TIM3_CH1 (PC6): 预留 PWM
- TIM5 (8399/4999): LED 闪烁用；8400×5000=42,000,000 → **需 42MHz 定时器时钟才为 1s**（若 APB1=84MHz 则为 0.5s/2Hz）⚠️ 时钟分母待实测确认，勿当既定事实
- CAN1: 500kbps, 中断已开
- USART1: 115200
- IWDG: 32 分频, reload 2000（需定时喂狗）

## CAN 调试回传（PCAN-USB 实测 2026-08-05，作为调试方法备用）

- 能力：PC + PEAK PCAN-USB（python-can, pcan 后端）+ `tools/can_monitor.py --id <监听ID>`，可在无串口的板子上做 CAN 调试回传；板端桥协议见 skill `templates/debug_can_proto.md`。
- 实测（500k 总线）：发送扩展帧 `0x1AA55F42`、数据 `00 00 00 C8 01 02 03 CE` → 对方以 **ID+1 = `0x1AA55F43`** 应答 `00 00 00 00 10 02 1f 31`。
- 注意：真实调试 ID 以项目要求为准（`can_monitor.py` 的 `--id` 已参数化），实测仅证明收发/应答链路通。
- 提醒：监听回帧用应答 ID（请求 ID+1）；波特率须与 PC 驱动侧一致。
