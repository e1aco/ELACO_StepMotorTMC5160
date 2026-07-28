# 项目状态

## 基本信息
- **项目名**: ELACO_StepMotorTMC5160
- **类型**: embedded (STM32 + TMC5160)
- **MCU**: STM32F407ZET6
- **工具链**: Keil MDK-ARM v5
- **工程文件**: Firmware/StepMotorDriver_Keil/MDK-ARM/StepMotorDriver_Keil.uvprojx

## 当前进度
- **阶段**: 开发中
- **已完成**: SPI通讯、CAN协议、电机基本转动、编码器测试、EEPROM、FreeModbus移植、CAN PID调参(0x06)
- **待解决**:
  1. FreeModbus 未测试
  2. PCB散热问题
  3. 需增加NTC过温保护
  4. 电机卡死超时机制
  5. 电机/芯片发热排查
  6. 相对位置微步运动不转(30微步)

## 已配置工具
| 工具 | 路径 |
|------|------|
| Keil UV4 | C:\Keil_v5\UV4\UV4.exe |
| OpenOCD | tools/openocd/xpack-openocd-0.12.0-7/bin/openocd.exe |
| arm-gcc | E:\STM32CubeCLT_1.21.0\GNU-tools-for-STM32\bin\arm-none-eabi-gcc.EXE |

## 外设扫描 (ela si)
| 外设 | 模块 | 说明 |
|------|------|------|
| SPI | ela_tmc5160_drv | TMC5160 通讯 |
| CAN | ela_can_usr, ela_can_drv | CAN 收发 |
| TIM | ela_timer_drv | 定时器 |
| USART | usart.c | 串口 |
| IWDG | iwdg.c | 独立看门狗 |
| GPIO | gpio.c | 通用IO |
| EEPROM | ela_eeprom | 存储 |

## 核心模块
- **ela_tmc5160_drv** — TMC5160 驱动层
- **ela_tmc5160_usr** — TMC5160 用户层
- **ela_can_usr** — CAN 用户协议
- **ela_can_drv** — CAN 驱动层
- **ela_motor_ctrl** — 电机控制
- **ela_closed_loop** — 闭环控制
- **ela_pid** — PID 调节
- **ela_timer_drv** — 定时器驱动
- **ela_eeprom** — EEPROM 操作
- **elaco_main** — 主逻辑

## CAN协议
- 接收 ID: 0x1AA55F42
- 反馈 ID: 0x1AA55F43
- 详见 README.md
