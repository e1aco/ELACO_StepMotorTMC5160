# 项目状态

## 基本信息
- **项目名**: StepMotorDriver_Keil
- **类型**: embedded (STM32F407ZET6 + TMC5160)
- **MCU**: STM32F407ZET6
- **工具链**: Keil MDK-ARM v5
- **工程**: Firmware/StepMotorDriver_Keil/MDK-ARM/StepMotorDriver_Keil.uvprojx

## 当前进度
- **阶段**: S0 — 初始化完成

## 已实现功能
SPI通讯 · CAN协议(0x01~0x06) · 电机转动 · 编码器 · EEPROM · FreeModbus移植 · PID调参

## 待解决
1. FreeModbus 未测试
2. PCB散热 / NTC过温保护
3. 电机卡死超时机制
4. ~~电机/芯片发热排查~~（2026-07-31 软件降流：IHOLD=1 + TPOWERDOWN=40 + CoolStep，待上机验证 ADR-003）
5. 相对位置微步运动不转(30微步)

## 核心模块
ela_tmc5160_drv · ela_tmc5160_usr · ela_can_usr/drv · ela_motor_ctrl · ela_closed_loop · ela_pid · ela_timer_drv · ela_eeprom · elaco_main

## 工具
| 工具 | 路径 |
|------|------|
| Keil UV4 | C:\Keil_v5\UV4\UV4.exe |
| OpenOCD | tools/openocd/.../openocd.exe |
| arm-gcc | E:\STM32CubeCLT_1.21.0\...\arm-none-eabi-gcc.EXE |

## 下一步
运行 `/ela new <功能描述>` 开始新功能
