# 硬件资源池 (Hardware Pool)
芯片: STM32H750VBT6 (LQFP100, Cortex-M7)
晶振频率: 8 MHz (HSE, PH0/PH1)
关键器件:
  - 驱动芯片: TMC5160
  - 外部 MOS: AOD4126
  - 采样电阻 RS: 0.05R
  - 步进电机: 57CME13
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
  # /cl init 会从 datasheet 提取所需参数，提取不到才向你提问。

# 引脚固定映射表 (Pin Mapping)

| 功能网标 | 引脚号 | 外设功能 | 说明 |
| :------- | :----- | :------- | :--- |
| HSE_IN | PH0 | RCC_OSC_IN | 8MHz 晶振输入 |
| HSE_OUT | PH1 | RCC_OSC_OUT | 8MHz 晶振输出 |
| LED_MCU | PA4 | GPIO_Output | 用户指示灯, 默认高 |
| U1_DRV_ENN | PA10 | GPIO_Output | TMC5160 #1 驱动使能(低有效), 默认高 |
| U1_SPI_SCN | PA11 | GPIO_Output | TMC5160 #1 SPI 片选(低有效), 默认高 |
| SWDIO | PA13 | DEBUG_JTMS | SWD 调试 |
| SWCLK | PA14 | DEBUG_JTCK | SWD 调试 |
| U2_DRV_ENN | PA15 | GPIO_Output | TMC5160 #2 驱动使能(低有效), 默认高 |
| FDCAN2_RX | PB12 | FDCAN2_RX | CAN 总线接收 |
| FDCAN2_TX | PB13 | FDCAN2_TX | CAN 总线发送 |
| USART1_TX | PB14 | USART1_TX | 调试串口发送 |
| USART1_RX | PB15 | USART1_RX | 调试串口接收 |
| SPI3_SCK | PC10 | SPI3_SCK | TMC5160 SPI 时钟 |
| SPI3_MISO | PC11 | SPI3_MISO | TMC5160 SPI 数据输入 |
| SPI3_MOSI | PC12 | SPI3_MOSI | TMC5160 SPI 数据输出 |
| U2_SPI_SCN | PD3 | GPIO_Output | TMC5160 #2 SPI 片选(低有效), 默认高 |
| TMC_CLK | PD14 | TIM4_CH3 | TMC5160 外部时钟(PWM 输出) |

# 工具链池 (Toolchain Pool)
IDE/编译器: CMake + GCC (arm-none-eabi-gcc)
芯片型号: STM32H750VBT6
优化等级: 6 (Os — optimize for size)
FPU: 单精度 + 双精度 (Cortex-M7 DP-FPU)
CubeMX 版本: 6.17.0, FW_H7 V1.13.0

# 调试与烧录 (Debug/Flash)
调试器: ST-Link (SWD, PA13/PA14)
调试回传接口: USART1 (PB14/PB15, 速率待确认) 或 FDCAN2 (PB12/PB13, 500kbps)
烧录工具: ST-Link + OpenOCD
烧录指令: python tools/openocd_flash.py --flash <每次编译产出的 hex 路径> --target stm32h7x
复位/运行: python tools/openocd_flash.py --reset --target stm32h7x
> 残留进程兜底: python tools/openocd_flash.py --kill

# 时钟树摘要 (Clock Tree, 从 .ioc 提取)
- PLL1: HSE 8MHz → DIVM1=1 → VCO1=960MHz → DIVP1=2 → SYSCLK=480MHz
- HCLK: 240MHz (HPRE=DIV2)
- APB1/APB2/APB3/APB4: 120MHz (均 DIV2)
- TIM4CLK: 240MHz (APB1×2, APB1=120MHz)
- SPI3CLK: 64MHz (PCLK3=120MHz 经分频, 实际波特率 8Mbit/s prescaler=8)
- USART1CLK: 64MHz (HSI 源)
- FDCANCLK: 8MHz (HSE 直接)
- ADCCLK: 16.125MHz

# SPI3 配置 (TMC5160 通信)
模式: Master Full Duplex
波特率: 8 Mbit/s (prescaler=8 @ 64MHz)
极性: CPOL=HIGH (Idle HIGH)
相位: CPHA=2EDGE (Sample on 2nd edge)
数据宽度: 8-bit

# FDCAN2 配置
波特率: 500 kbit/s (Prescaler=1, Seg1=13, Seg2=2, 20TQ)
自动重发: ENABLE

# TIM4 配置
CH3: PWM Generation (TMC_CLK — 为 TMC5160 提供外部时钟)
PWM频率: 15Mhz

# 项目全局目标 (Global Goal) — /cl init 访谈填写；需求锁锚点，禁静默降级
> 由 /cl init「全局目标访谈」填写，AI 生成/调参/验收一律对照本节。每行 = 量化目标（值+单位）+ 验收判据（仪器/工况/数值）+ 来源（你 / AI 提议 / 待实测确定）。

- 一句话定位: 双 TMC5160 独立电机控制，CAN 指令驱动，支持绝对位置/相对位置/速度三种运动模式
- 精度: 待实测确定（有光编 4000ppr, ×4=16000cpr, 理论分辨率 0.0225°/count；闭环定位精度由编码器+控制算法决定，待调定后实测）
- 速度: 最高 600rpm, 加减速由 TMC5160 内部速度规划（VDCOL/TCOOLTHRS 等），暂不外部干预 | 来源: 你
- 控制周期: 待定（CAN 协议后续定义，位置环周期由 TMC5160 内部扫描）| 来源: 待定
- 负载: 待实测确定（电机 57CME13, 保持力矩 1.3N·m, 转子惯量 0.3kg·cm²）| 来源: 待实测确定
- 接口/通信: CAN 500kbps, 协议后续定义 | 来源: 待定
- 电源: 24VDC（电机建议 36V, 降额使用）| 来源: 你
- 编码器: 光编 4000ppr (×4=16000cpr), 用于闭环反馈 | 来源: 你
- 验收判据: 待定（由你确定）| 来源: 你
- 优先级: 待定（由你确定）| 来源: 待定
- 首版范围 (MVP): 待定 | 来源: 待定
- 待实测确定项: 精度指标、负载工况、控制周期、验收判据、优先级、MVP 范围

# 时序测量表 (Timing Budget) — AI 维护，外部实测需人工回填
> 架构级时序预算控制：每个关键时序操作一行，理论值由 AI 按时钟树/datasheet 推导（附依据），实测值按测试方法获取。

## 默认指标（前置配置，人工可修改，AI 生成/重推导条目时按此默认）
- 预算比例: 中断/采样型 = 周期 × 30%（硬上限 50%，可改）
- 绝对型裕量: datasheet 最坏情况 × 2
- 测试周期默认: 软件条目 = 每次变更都测 | 硬件条目 = 仅首次测
- 测试方法词表: 软件(SysTick) / 硬件(Saleae) / 外部(示波器/逻辑分析仪)
- 状态词表: [ ] 待测 / [x] 已测 / [!] 需外部仪器 / [expired] 过期（保留+注明原因）
- 时序测试点 IO: PD14 (TMC_CLK, TIM4_CH3) — 可翻转供 Saleae 捕获
- 探针默认位置: 函数级（ISR 入口/出口），语句级由条目位置列自定义覆盖

## 条目表（AI 按上述默认生成；理论值/实测值记录于此）
| 操作 | 位置/探针位置 | 理论值(推导) | 依据 | 预算/判据 | 测试周期 | 测试方法 | 实测值 | 实测日期 | 状态 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| SPI3 TMC5160 读写周期 | HAL_SPI_TransmitReceive 前后 | 12.5us @ 8Mbit/s, 10 字节 | SPI3CLK=64MHz, prescaler=8 → 8Mbit/s | 3.75us (×30%) | 每次变更都测 | 软件(SysTick) | (待测) | | [ ] |
| TIM4 PWM 输出 (TMC_CLK) | PD14 示波器 | (待配置) | TIM4CLK=240MHz, 分频/ARR 待定 | — | 仅首次测 | 硬件(Saleae) | | | [!] |
| USART1 串口回传 | PB14 TX | (待配置) | USART1CLK=64MHz, 波特率待定 | — | 每次变更都测 | 软件(SysTick) | | | [ ] |
| 主循环单圈 | main while(1) | (待测) | 推算 | — | 仅首次测 | 硬件(Saleae) | | | [!] |

# 仿真参数 (Simulation) — AI 维护（可选，允许为空，不阻塞 init）

## 配置
> 仿真目录: (待定)
> MATLAB: (待定)
> 状态文件: .cl/sim/state.md

## 辨识结果
| 参数 | 值 | 单位 | 来源 | 日期 | 状态 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| J 转动惯量      | (TBC) | kg·m²     | | | [ ] |
| B 摩擦系数      | (TBC) | N·m·s/rad | | | [ ] |
| Kt 力矩常数     | (TBC) | N·m/A     | | | [ ] |
| R 相电阻        | (TBC) | Ω         | | | [ ] |
| L 相电感        | (TBC) | mH        | | | [ ] |

# 任务队列 (Task Queue) — AI 自动维护（允许为空）
