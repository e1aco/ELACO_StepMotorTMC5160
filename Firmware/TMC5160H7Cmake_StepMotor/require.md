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
构建体系: cmake
CMake 工程: 工程根=本目录; target=TMC5160H7_StepMotor; 工具链文件=cmake/gcc-arm-none-eabi.cmake（cmake_build.py 自动探测）; 构建目录=build_cl（与 CLion 的 build/ 隔离）
编译指令: python tools/cmake_build.py <工程根> [--define 宏]   # RESULT 行为真相判据，产物 hex/elf 落 build_cl/（唯一权威 details/build.md）
IDE/编译器: CMake + GCC (arm-none-eabi-gcc) + Ninja（STM32CubeCLT 提供）；CLion 打开同一工程用其自有 Profile
芯片型号: STM32H750VBT6
优化等级: 6 (Os — optimize for size)
FPU: 单精度 + 双精度 (Cortex-M7 DP-FPU)
CubeMX 版本: 6.17.0, FW_H7 V1.13.0

# 调试与烧录 (Debug/Flash)
调试器: ST-Link (SWD, PA13/PA14)
调试回传接口: USART1 (PB14/PB15, 速率待确认) 或 FDCAN2 (PB12/PB13, 500kbps)
烧录工具: ST-Link + OpenOCD
烧录指令: python tools/openocd_flash.py --flash <工程根>\build_cl\TMC5160H7_StepMotor.hex --target stm32h7x
复位/运行: python tools/openocd_flash.py --reset --target stm32h7x
> 残留进程兜底: python tools/openocd_flash.py --kill

# 时钟树摘要 (Clock Tree, 从 .ioc 提取)
- PLL1: HSE 8MHz → DIVM1=1 → VCO1=960MHz → DIVP1=2 → SYSCLK=480MHz
- HCLK: 240MHz (HPRE=DIV2)
- APB1/APB2/APB3/APB4: 120MHz (均 DIV2)
- TIM4CLK: 240MHz (APB1×2, APB1=120MHz)
- SPI3CLK: 103.2MHz (PLL3Q: HSE8/5×129/2, 2026-09-09 CubeMX 改; 原 CLKP/HSI 64MHz), 实际波特率 6.45Mbit/s prescaler=16
- USART1CLK: 64MHz (HSI 源)
- FDCANCLK: 8MHz (HSE 直接)
- ADCCLK: 16.125MHz

# SPI3 配置 (TMC5160 通信)
模式: Master Full Duplex
波特率: 6.45 Mbit/s (SPI3 kernel=PLL3Q 103.2MHz, prescaler=16)（2026-09-09 CubeMX 改配置+实测通过；≤fCLK/2=7.5MHz 规格内）
极性: CPOL=HIGH (Idle HIGH)
相位: CPHA=2EDGE (Sample on 2nd edge)
数据宽度: 8-bit

# FDCAN2 配置
波特率: 500 kbit/s (Prescaler=1, Seg1=13, Seg2=2, 16TQ @8MHz HSE)
自动重发: ENABLE
MessageRAM 分配 (移植适配, CubeMX 重生成需保留): ExtFiltersNbr=1 / RxFifo0ElmtsNbr=8 / TxFifoQueueElmtsNbr=3

# CAN 命令协议 (自 TMC5160_StepMotor 移植提取) — 来源: 源工程 can_drv/can_usr 实现
## 帧格式（经典帧, 扩展 ID, 8 字节）
- 校验和: byte7 = (byte0..byte6 累加) & 0xFF

## 命令帧 0x1AA55F42 (上位机 → MCU)
| 字节 | 含义 |
| :--- | :--- |
| byte0-3 | value: int32 小端（位置/偏移/速度） |
| byte4 | cmd: 0x01绝对定位 / 0x02相对顺时针 / 0x03相对逆时针 / 0x04速度模式 / 0x05停止 / 0x06 PID调参(未实现) / 0x07闭环使能 / 0x08闭环禁用 |
| byte5 | motor: 0x01=U1 / 0x02=U2 / 0x06=全部 |
| byte6 | param: 运动参数组 ID 1~5（cmd 0x06 时为 PID 参数类型） |
| byte7 | checksum |

## 反馈帧 0x1AA55F43 (MCU → 上位机)
| 字节 | 含义 |
| :--- | :--- |
| byte0-3 | pos: 编码器位姿 X_ENC int32 小端 |
| byte4 | status: bit0到位 bit1失步 bit2过温 bit3驱动错 bit4 SPI异常 |
| byte5 | motor |
| byte6 | protect: bit0=OTPW bit1=OT bit2=drv_err bit3=S2GA bit4=S2GB bit5=S2VSA bit6=S2VSB bit7=失步 |
| byte7 | checksum |

## 调试通道
- 调试遥测已迁移 J-Link RTT（1Hz 心跳，rtt_dbg 封装），不再占用 CAN 总线

# TIM4 配置
CH3: PWM Generation (TMC_CLK — 为 TMC5160 提供外部时钟)
PWM频率: 15Mhz

# 项目全局目标 (Global Goal) — /cl init 访谈填写；需求锁锚点，禁静默降级
> 由 /cl init「全局目标访谈」填写，AI 生成/调参/验收一律对照本节。每行 = 量化目标（值+单位）+ 验收判据（仪器/工况/数值）+ 来源（你 / AI 提议 / 待实测确定）。

- 一句话定位: 双 TMC5160 独立电机控制，CAN 指令驱动，支持绝对位置/相对位置/速度三种运动模式
- 精度: 0.09°/count（光编 1000PPR ×4=4000cpr；闭环定位精度由编码器+控制算法决定，待调定后实测）
- 速度: 最高 600rpm, 加减速由 TMC5160 内部速度规划（VDCOL/TCOOLTHRS 等），暂不外部干预 | 来源: 你
- 控制周期: 待定（CAN 协议后续定义，位置环周期由 TMC5160 内部扫描）| 来源: 待定
- 负载: 待实测确定（电机 57CME13, 保持力矩 1.3N·m, 转子惯量 0.3kg·cm²）| 来源: 待实测确定
- 接口/通信: CAN 500kbps, 协议后续定义 | 来源: 待定
- 电源: 24VDC（电机建议 36V, 降额使用）| 来源: 你
- 编码器: 光编 1000PPR, ×4正交解码=4000cpr (ENC_CONST=12.8 对齐 51200微步/圈), 用于闭环反馈 | 来源: 你, 实测验证
- 验收判据: 待定（由你确定）| 来源: 你
- 优先级: 待定（由你确定）| 来源: 待定
- 首版范围 (MVP): 待定 | 来源: 待定
- 待实测确定项: 精度指标、负载工况、控制周期、验收判据、优先级、MVP 范围

## 工作流程
两路电机，等待发送指令回零（回零使用无编码器的那种回零模式 使用SPI轮询判断回零完成），两路电机分别回零，一路回零到位后第二路开始回零
（使用CAN来控制回零即可， 检测到一路回零完成后CAN控制第二路回零。）回零完成后上报。 完成回零等待控制运行指令，进行相对或绝对运动，不允许电机的所有模式超过
某个运行位置(0-最大目标值)，会导致堵转和不可控行为，这时上报超出界限。在范围内可以自由运行。此外如何控制两个电机的位置不互相干涉需要如何控制（上位机还是我们
？）暂时待定。
轮子:
1. 上电回零程序 （CAN指令回零（速度+方向）-> 以这个速度和方向进行回零 -> 堵转检测确认零点 -> 向反方向运动几微步防止卡死标定为零点 -> 停止运行）
2. 相对运动，绝对运动，速度模式3个程序 （已有）
3. 堵转，过流保护程序 （在运行中途堵转，则立刻停止并且反向运动几步，（既要保证不易触发，也要保证安全性））
4. 运行中的梯形规划（或线性规划） （已有，但我还不知道逻辑是什么 ， 如何改为S型规划？）
5. 闭环位置控制 （已有，需要调试）
6. CAN通讯 （已有，协议目前感觉没有写的很清楚）
7. SPI读写TMC5160 （已有，待实测读取和写入实际时间）

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
| SPI3 TMC5160 读写周期 | HAL_SPI_TransmitReceive 前后 | 写单报 6.2us(40bit@6.45M)+HAL 开销≈20us；读双报含10us帧间隔≈54us | SPI3 kernel=PLL3Q 103.2MHz ÷16 = 6.45Mbit/s；TMC5160 约束 fSCK≤fCLK/2=7.5MHz（15MHz 外部时钟, ch04 §4.3）| 6.45≤7.5MHz 规格内, 裕量 14% | 每次变更都测 | 软件(SysTick→DWT) | 写 max=20us(n=29) 读 max=54us(n≈17k) | 2026-09-09 | [x] 宏版 tag0/tag1 实测 |
| TIM4 PWM 输出 (TMC_CLK) | PD14 示波器 | (待配置) | TIM4CLK=240MHz, 分频/ARR 待定 | — | 仅首次测 | 硬件(Saleae) | 软件比值: XACTUAL 17881/s=20000×fCLK/2^24 → fCLK≈15.00MHz±0.01% (SOAK r3, 非仪器, 示波器终验仍欠) | 2026-09-10 | [!] |
| USART1 串口回传 | PB14 TX | (待配置) | USART1CLK=64MHz, 波特率待定 | — | 每次变更都测 | 软件(SysTick) | | | [ ] |
| 主循环单圈 | main while(1) | (待测) | 推算 | — | 仅首次测 | 硬件(Saleae) | | | [!] |
| SpreadCycle 斩波频率 | Rsense 两端（示波器） | ~20-25kHz（TOFF=5, TBL=3, fCLK=15MHz 推算） | ch08: f≈1/(4×tOFF), tOFF=(24+32×TOFF)/fCLK | 16-30kHz | 仅首次测 | 硬件(Saleae/示波器) | | | [!] |

# 任务队列 (Task Queue) — AI 自动维护（允许为空）

- [ ] [c] 移植 F407 工程代码到 H7（11 模块归一 + SEGGER_RTT + Core 织入 + FDCAN 重写）（起 2026-08-25 | 止 2026-08-25 | 验收 待用户功能测试）
- [ ] [ ] StallGuard2 断电回零功能（上电自动回零 + 手动推位后重定位，无 Z 相光编）（起 | 止 | 验收 待定）
- [ ] 调试CAN和SPI，保证通讯实现（起 2026-09-08 | 止 进行中）※SPI 部分已完成（见下条），剩 CAN 收发验证
- [x] 测试验证SPI（U2 读写双通路+5V硬件修复后；3轮闭环；修 WriteReg tCSH 帧间隔、判据移除只写寄存器 IHOLD_IRUN、修 U%u 标签）（起 2026-09-09 11:05 | 止 2026-09-09 11:30 | 验收 待用户确认）
- [x] SPI 提速复测 6.45Mbps（CubeMX 改 PLL3Q 内核+还原 NSSP/引脚速度/FDCAN MsgRAM 回退项；宏版实测写20us/读54us 回填时序表[x]；生产版 [SPI OK] 终验通过；修 cmake_build.py 生产→宏版注入盲区）（起 2026-09-09 11:45 | 止 2026-09-09 12:06 | 验收 待用户确认）
- [x] 文件合并重构：can_drv+can_usr→drv/can.c，tmc5160_drv+tmc5160_usr→drv/tmc5160.c（去 _drv 后缀；符号保留 DRV_/USR_ 前缀不改名；can→app 反向依赖为用户 2026-09-09 显式裁决，can.h/can.c 头注豁免登记；烧录回归 [SPI OK] 行为等价）（起 2026-09-09 12:20 | 止 2026-09-09 14:22 | 验收 待用户确认）
- [✓] S2/SpreadCycle 判定实验（撤 DIAG 钩子复跑）：r5 首跑遇 TMC 无供电([SOAK DEAD] 全零读回)→r6 活性门+非零对照组(已修 CTL 盲区)→**14:32 生产配置判定成立：运转中 ds=0x11140000(s2gb=1,SG=1,CS=20) + gs=02(drv_err 每秒) → B 相驱动异常实锤；且 S2 防误触发配置已是最低敏度档(S2G_LEVEL=15/FILTER=3/delay=1500ns/TBL=54clk)→误报概率低；5160 无 GCONF.swstack(ch06.p032-033 位表核实)→软件 AB 交换不可行, 转物理判别**（起 2026-09-10 14:40 | 止 2026-09-10 14:34 | 验收 2026-09-10 通过）
- [x] DRVSTRENGTH×CS 阶梯扫描 r7/r7b：{0,3,6} 与 {0,5,7 最强} 两轮 × CS{20,8} 共 12 格 → **s2gb 全格恒报、drv_err 恒有、轴零净转(enc 167~5427 抖动)**；drvs 完全无效 → 排除"驱动电流档位"类；olb 多格同报 → B 电流不达标+桥中点被拽低组合=非烧穿型；候选收敛=① VSA 12V→11.5V 栅压稳压器(12VOUT)压差仅 0.5V 轨塌陷(与 drvs 无效自洽: 档位救不了电压幅度) ② 自举电容 CB1/CB2/CPO 损坏 ③ 37-40/BM-LA 脚区焊桥 ④ B 低边管击穿。鉴别: 24V 重跑全清=①；表量 12VOUT<10.5V=①；断电机重跑仍 s2gb=板侧②③④（起 2026-09-10 15:10 | 止 2026-09-10 15:34 | 验收 2026-09-10 通过；※用户 15:4x 补测供电 12V 静态稳定——不能排除①瞬态塌陷，24V 对照仍待做）
- [ ] [!] 电机运行排查（CAN 命令后 SpreadCycle 抖动/不转→B相s2gb+olb；SPI 降速论 09-10 证伪；**r6 生产配置(S2 开)复判: SRB 修复无效, s2gb+drv_err 运转中复燃=芯片实锤 B 相短路, 桥臂被保护关断→单相 A 驱动→100%丢步原地抖(act=178876/enc≈-1400±700 振荡)**；短路位置待判: 板侧 B 腿 vs 线缆/绕组对地(用户曾测两相绕组阻值一致, 但 S2G 查的是输出腿对地)；下一步=r7 候选鉴别（24V 重跑表 / 断电机重跑 / 表量 B 端子与 12VOUT）详见遗留任务行）（起 2026-09-09 15:40 | 止 进行中）
- [x] 保持电流降档 IHOLD 6→3(≈0.58A) + 修 IHOLD_IRUN 注释位域写反 bug + SOAK2 加 X_ENC 丢步量化；运行电流 IRUN：曾按计算推 CS=13(2.01A)，按用户裁决回退参考代码实测值 CS=20(3.02A, F407 OTPW 史) ※量化结果：act=178818 vs enc=13（±282µsteps 振荡）= **100% 丢步**；※修正：OL 检测独立于 diss2g(ch11§11.3)，r4 运转中 ola/olb=0 为有效反证，仅 S2 组被屏蔽；※后续：用户实测 IHOLD=3 锁不住 → 当日改回 6（1.01A/~0.33N·m，已编译烧录）（起 2026-09-10 12:30 | 止 2026-09-10 15:30 | 验收 2026-09-10 通过）
- [✓] SPI 时序核查（用户假设 H7 6.45Mbps 过快）：手册 ch04§4.3 对照（帧间隔/模式/边沿裕量 1%）→ SOAK 三轮迭代（r1 误选只写寄存器 ENC_CONST 教训入 memory；r2 发现无 profile 电机未转；r3 真实运转 22.4万帧写读回显 0 翻转 + GCONF 对照 OK）→ **降速论证伪**；副产品：XACTUAL 速率精确匹配推导 → fCLK=15.00MHz±0.01% 软件钉死；SPI_SOAK 已置 0 生产版编译 0E/0W（起 2026-09-10 11:40 | 止 2026-09-10 15:50 | 验收 2026-09-10 通过）
- [ ] 生产化与硬件排查遗留（起 2026-09-10 | 止 ）：① 生产版(SPI_SOAK=0)已编译**未烧录**（板断电）——上电后烧+回归 ② IHOLD=6 手转锁轴验证 ③ 24V 供电重跑 r7 表（判 12VOUT 轨塌陷 vs 板侧损伤，12V 静态稳定不排除瞬态）④ 若 24V 仍报 s2gb：拔电机线重跑分板内外+表量 B 端子对 GND+放大镜查 QFN 37-40/9-10 脚区 ⑤ CHOPCONF/SR 修复相关 DIAG 注释历史已清，CAN 命令路径复现留待「调试CAN和SPI」任务
- [c] 代码结构与命名按cl skill规范整顿（drv/algo/app分层 + S_ 命名 + 行宽≤100）（起 2026-09-08 | 止 2026-09-08）
