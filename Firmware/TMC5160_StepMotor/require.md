# 硬件资源池 (Hardware Pool)
芯片: STM32F407ZETx (LQFP144)
晶振频率: 8MHz HSE (PH0/PH1)
关键器件:
  - TMC5160 步进电机驱动 x2 (U1/U2，通过 SPI3 控制)
  - 0.05R 电流采样电阻
  - MCU_LED (PA1)、TEST_LED (PA2)
  - SW1 按键 (PD1)
  - CAN1 (500kbps)
  - 步进电机 57CME13
    1. 相数 2
    2. 保持力矩（N.m） 1.3
    3. 电机机座（mm） 57
    4. 步距角 1.8
    5. 电感（mH） 1.6
    6. 建议使用电压（VDC） 36V
    7. 额定电流（A） 4
    8. 电阻（Ω） 0.42
    9. 转子惯量（Kg·cm²）  0.3
    10. 电机重量（KG） 0.8

# 引脚固定映射表 (Pin Mapping)
| 功能网标 | 引脚号 | 外设功能 |
| :------- | :----- | :------- |
| MCU_LED      | PA1  | GPIO_Output |
| TEST_LED     | PA2  | GPIO_Output |
| USART1_TX    | PA9  | USART1_TX (115200) |
| USART1_RX    | PA10 | USART1_RX |
| CAN1_RX      | PA11 | CAN1_RX |
| CAN1_TX      | PA12 | CAN1_TX |
| SWDIO        | PA13 | SYS_JTMS-SWDIO (ST-LINK SWD) |
| SWCLK        | PA14 | SYS_JTCK-SWCLK |
| U2_SPI1_SCN  | PB0  | GPIO_Output (片选) |
| U2_DRV_ENN   | PB1  | GPIO_Output (使能) |
| TMC_CLK      | PB6  | TIM4_CH1 PWM (Period=5, Prescaler=0, Pulse=3, 14MHz) |
| PB7          | PB7  | GPIO_Input (无标签) |
| PWM (TIM2)   | PB10 | TIM2_CH3 PWM (Prescaler=8399, Period=9999, OPM) |
| U2_SD_MODE   | PB12 | GPIO_Output |
| U2_SPI_MODE  | PB13 | GPIO_Output |
| PWM (TIM3)   | PC6  | TIM3_CH1 PWM (Prescaler=41) |
| SPI3_SCK     | PC10 | SPI3_SCK (Master, 2.625Mbps, CPOL=High, CPHA=2Edge) |
| SPI3_MISO    | PC11 | SPI3_MISO |
| SPI3_MOSI    | PC12 | SPI3_MOSI |
| SW1          | PD1  | GPIO_Input (PullUp) |
| U1_SPI_MODE  | PD2  | GPIO_Output |
| U1_SD_MODE   | PD3  | GPIO_Output |
| U1_REFL_DIR  | PD4  | GPIO_Output |
| U1_SPI1_SCN  | PD5  | GPIO_Output (片选) |
| U2_SWP_DIAG1 | PF11 | GPIO_Input |
| U2_SWN_DIAG0 | PF12 | GPIO_Input |
| U2_REFL_DIR  | PF13 | GPIO_Output |
| U1_SWN_DIAG0 | PG11 | GPIO_Input |
| U1_SWP_DIAG1 | PG12 | GPIO_Input |
| U1_DRV_ENN   | PG13 | GPIO_Output (使能) |
| OSC_IN/OUT   | PH0/PH1 | HSE 8MHz |

# 工具链池 (Toolchain Pool)
IDE/编译器: Keil MDK-ARM V5.32
芯片型号: STM32F407ZETx
优化等级: Level 3 (CubeMX CompilerOptimize=6)
FPU: 硬件 FPU（Cortex-M4F 单精度）

# 调试与烧录 (Debug/Flash)
调试器: ST-LINK
烧录指令: 通过 Keil MDK 下载按钮烧录（调试器选 ST-LINK，SWD: PA13/PA14），
  CLI 备用: pyOCD 或 STM32CubeProgrammer (st-flash / ST-LINK_CLI)

# 项目全局目标 (Global Goal)
使用CAN指令控制TMC5160芯片2来驱动电机2实现绝对位置正反转，相对位置正反转和速度模式正反转。

# 任务队列 (Task Queue)
> 状态标记说明:
> [ ] 未开始
> [x] AI 认为已完成（需人工验收）
> [✓] 人工验收通过
> [!] 阻塞待分析
> [c] Code Only — 已生成代码，调试由你手动接管

> 任务条目格式：`- [标记] 标题（起 YYYY-MM-DD | 止 YYYY-MM-DD | 验收 YYYY-MM-DD 说明）`——同时记录开始与结束/验收时间，跨会话可衔接。

## 2026-08-05
- [✓] 移植C:\Users\admin\Desktop\XM\ELACO_StepMotorTMC5160\AIFirmware\StepMotorDriver_Keil项目内容。（起 2026-08-05 | 止 2026-08-05 | 验收 2026-08-05：修复 IWDG 未喂狗导致周期性复位/偶发卡顿）
  - 已生成源码 `module/drv/` + `module/usr/`：
    - drv: tmc5160_drv / can_drv / timer_drv / eeprom
    - usr: tmc5160_usr / can_usr / motor_ctrl / closed_loop / queue / pid
  - 无 app_main：初始化 + 主循环直接写在 `Core/Src/main.c`
  - 中断回调（CAN RX0 + TIM7 周期）在 `Core/Src/stm32f4xx_it.c`
  - 手动编译步骤（Keil）：
    1. MDK-ARM/StepMotorDriver_Keil.uvprojx 中添加 module/drv 与 module/usr 下全部 .c
    2. Include Paths 增加 `module`（代码用 `drv/xxx.h`、`usr/xxx.h` 引用）
    3. 编译下载（ST-LINK SWD），调试由你手动接管

## 2026-08-05
- [✓] 设置ID为 1AA55F44作为调试输出并自行设置CAN协议后进行调试，can协议保存在需求文件 # CAN 协议 下。（起 2026-08-05 | 止 2026-08-07 | 验收 2026-08-07：周期遥测帧 0x1AA55F44 输出正常；0x1AA55F42 命令协议按需求文件实施）

## 2026-08-10
- [✓] 确认新实现的 CAN 调试帧能正确显示报警源（U2 电机 OTPW 过温预警）。（起 2026-08-10 | 止 2026-08-11 | 验收 2026-08-11：真机 24V 上电，U2 过温预警状态下捕获到 `D=84064000 G=00000000 A=OTPW`，U1 段 `A=-`，与判据一致；marker 握手 20260811-091858 起算命中）
   - 背景：上一条温度任务中新增 CAN 调试帧报警源解码（can_usr.c `CAN_DbgAppendAlarm`），DRV_STATUS bit26=OTPW、bit25=OT、S2G/S2V/Ox、GSTAT DRVERR/UVCP/RESET 文本化追加到 `A=` 字段。
   - 判据：CAN 调试帧 U2 段 `D=0x84xxxxxx`（bit26 置位）时 `A=OTPW` 正确显示；U1 无报警时 `A=-`。

## 2026-08-06
- [c] 解决电机空载情况下，tmc5160依旧温升超过120℃的情况。（起 2026-08-06 | 止 进行中）
  驱动芯片温升较高，在电机空载状态下依旧会报警，这表示温度已经超过了120℃。我们需要在以下这些方法里进行排查：
  1. 电流设置（最重要）,但是这一步我已经做了相关调整，电机温度有明显改善，但是芯片并没有。
  2. 斩波模式 (Chopper)：如果参数不当，会导致电流波形畸变，有效值（RMS）飙升。
  3. PWM 频率:频率过低（如低于20kHz）会进入人耳可听频段并增加铁损发热；频率过高（>100kHz）会增加开关损耗。建议先试试 36kHz ~ 48kHz 区间。
  4. 待机状态:如果一直保持 ENABLE 高电平，大电流一直灌入线圈，不转也发热。
- 26-08-07 更新:
现已加装散热片，CAN反馈正常。测试有保持电流情况下芯片温度反馈。
运行30分钟后温度报警，但是停止电机后立刻停止报警，说明是电机运行时芯片发热。所以尝试修改DRVSTRENGTH 为 0 或 1。减少不必要的过快的mos开关。
- 26-08-10 更新: [c] DRVSTRENGTH 设为 0(weak)。DRV_CONF(0x0A)=0x00000400（只写寄存器，其余字段按复位缺省 BBMTIME=0/BBMCLKS=4/OTSELECT=0/FILT_ISENSE=0）。编译 0 Error 0 Warning。烧录与实测由人工接管。
- 26-08-10 更新: [c] 代入电机/MOS 参数推导项目专属配置（替代 datasheet 默认值），详见 .cl/memory/hardware_corrections.md：
  - DRVSTRENGTH=0（AOD4126 Qgd=10nC → ch03.p17 表3.3）
  - IRUN=10→27（电机额定 4A，ch09.p74 公式 → 4.02A RMS）、IHOLD=1→8（约1.2A RMS）
  - 新增 PWMCONF=0xC40D001E（PWM_FREQ=%01 → fPWM=2/683×14MHz=41.0kHz，落 36~48kHz 区间；复位 %00=27.3kHz 偏低致铁损发热）
  - CHOPCONF 注释修正（HSTRT 实为 0，StealthChop 下 TOFF 仅使能电机）
  - 编译 0 Error 0 Warning。烧录与实测由人工接管。


# CAN 协议
## 设置CAN协议

### 1. 接收命令协议 (CAN ID: `0x1AA55F42`)

| 字节索引 | 含义 | 说明 |
| :--- | :--- | :--- |
| [0-3] | 值 (int32) | 4字节小端（低字节在前），含义由命令码决定 |
| [4] | 命令码 | 见下方命令码表 |
| [5] | 电机选择 | 0x01=U1, 0x02=U2, 0x06=所有电机 |
| [6] | 参数/分组 | 0x01~0x04=运动参数组（命令0x01~0x05），0x01~0x06=PID参数类型（命令0x06） |
| [7] | 校验和 | 前7字节累加取低8位 |

#### 命令码定义

| 命令码 | 名称 | [0-3] 含义 | [6] 含义 |
| :--: | :--- | :--- | :--- |
| 0x01 | 绝对位置移动 | 目标位置（微步） | 运动参数组 (0x01~0x04) |
| 0x02 | 相对位置正转 | 移动步数 | 运动参数组 (0x01~0x04) |
| 0x03 | 相对位置反转 | 移动步数 | 运动参数组 (0x01~0x04) |
| 0x04 | 速度模式 | 目标速度（微步/秒） | 运动参数组 (0x01~0x04) |
| 0x05 | 停止/刹车 | 0（忽略） | 运动参数组 (0x01~0x04) |
| 0x06 | PID调参 | 参数值（Q16或整数） | PID参数类型 (0x01~0x06) |
| 0x07 | 闭环使能 | 0（忽略） | 0（忽略） |
| 0x08 | 闭环禁用 | 0（忽略） | 0（忽略） |

#### 运动参数组定义 (命令 0x01~0x05 使用)

| 参数组 | 说明 | VMAX | AMAX | 典型场景 |
| :--: | :--- | ----: | ----: | :--- |
| 0x01 | 低速精准 | 5,000 | 1,000 | 精准定位 |
| 0x02 | 中速普通 | 20,000 | 5,000 | 日常运动 |
| 0x03 | 快速 | 50,000 | 10,000 | 快速移动 |
| 0x04 | 高速 | 100,000 | 20,000 | 长距离搬运 |

#### PID参数类型定义 (命令 0x06 使用)

| 参数类型 | 含义 | 值格式 | 默认值 |
| :--: | :--- | :--- | ----: |
| 0x01 | Kp（比例系数） | Q16定点数 | 8192 (0.5) |
| 0x02 | Ki（积分系数） | Q16定点数 | 2048 (0.125) |
| 0x03 | Kd（微分系数） | Q16定点数 | 4096 (0.25) |
| 0x04 | out_max（最大输出速度） | 直接整数 | 50000 |
| 0x05 | out_min（最小输出速度） | 直接整数 | -50000 |
| 0x06 | integral_max（积分限幅） | 直接整数 | 32768 |

> **Q16定点数**：实际值 = Q16值 / 65536。例如 Kp=0.5 → Q16值 = 0.5 × 65536 = 8192。

### 2. 反馈响应协议 (CAN ID: `0x1AA55F43`)

| 字节索引 | 含义 | 说明 |
| :--- | :--- | :--- |
| [0-3] | 值 (int32) | 4字节小端，含义由 byte[6] 决定 |
| [4] | 标志/参数类型 | 运动反馈=状态标志位，调参反馈=参数类型 |
| [5] | 电机选择 | 0x01=U1, 0x02=U2 |
| [6] | 反馈类型 | 0x01~0x05=运动反馈，0x06=调参反馈 |
| [7] | 校验和 | 前7字节累加取低8位 |

#### 运动反馈 (byte[6] = 0x01~0x05)

| 字节索引 | 含义 | 说明 |
| :--- | :--- | :--- |
| [0-3] | 偏差值 (int32) | X_ENC - XACTUAL (正值=编码器超前, 负值=编码器滞后) |
| [4] | 状态标志位 | bit0=到位, bit1=失步, bit2=过温, bit3=驱动错误, bit4=SPI异常 |
| [5] | 电机选择 | |
| [6] | 运动阶段 | bit0=加速, bit1=匀速, bit2=减速, bit3=归零等待, bit4=静止锁轴 |
| [7] | 校验和 | |

**状态标志位 (byte[4]) 详解：**
```
bit0 → 0=运动中，1=已到位
bit1 → 0=正常，1=堵转/失步
bit2 → 0=正常，1=过温告警
bit3 → 0=正常，1=驱动错误
bit4 → 0=SPI正常，1=SPI通讯异常
bit5-7 → 保留
```

#### 调参反馈 (byte[6] = 0x06)

| 字节索引 | 含义 | 说明 |
| :--- | :--- | :--- |
| [0-3] | 参数值 (int32) | 刚设置的参数值 |
| [4] | 参数类型 | 0x01=Kp, 0x02=Ki, 0x03=Kd, 0x04=out_max, 0x05=out_min, 0x06=integral_max |
| [5] | 电机选择 | |
| [6] | 固定 0x06 | 标识为调参反馈 |
| [7] | 校验和 | |

#### 反馈发送规则

| 命令码 | 发送时机 |
| :---: | :--- |
| 0x01/0x02/0x03 | 立即发送启动反馈 + 到位后发送到位反馈 |
| 0x04/0x05 | 仅立即发送一次 |
| 0x06 | 立即发送调参确认反馈 |
| 0x07/0x08 | 立即发送确认反馈 |
| 异常 | 堵转/过温/驱动错误/SPI异常状态变化时，5ms定时器触发发送 |
