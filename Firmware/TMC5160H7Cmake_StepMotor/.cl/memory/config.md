# .cl/memory/ — 配置推导值

## 电机参数 (57CME13)
motor_phases = 2                    依据: 电机规格书 日期: 2026-08-24 来源: 推导
motor_hold_torque = 1.3 N·m         依据: 电机规格书 日期: 2026-08-24 来源: 推导
motor_step_angle = 1.8°             依据: 电机规格书 (200 steps/rev) 日期: 2026-08-24 来源: 推导
motor_rated_current = 4 A           依据: 电机规格书 日期: 2026-08-24 来源: 推导
motor_phase_resistance = 0.42 Ω     依据: 电机规格书 日期: 2026-08-24 来源: 推导
motor_phase_inductance = 1.6 mH     依据: 电机规格书 日期: 2026-08-24 来源: 推导
motor_rotor_inertia = 3e-5 kg·m²   依据: 电机规格书 0.3kg·cm² 转换 日期: 2026-08-24 来源: 推导
motor_weight = 0.8 kg               依据: 电机规格书 日期: 2026-08-24 来源: 推导

## MOSFET 参数 (AOD4126)
mosfet_vds = 100 V                  依据: AOD4126 规格书 日期: 2026-08-24 来源: 推导
mosfet_id_max = 43 A                依据: AOD4126 规格书 @VGS=10V 日期: 2026-08-24 来源: 推导
mosfet_rds_on = 24 mΩ               依据: AOD4126 规格书 @VGS=10V, typ 日期: 2026-08-24 来源: 推导
mosfet_qg = 28 nC (typ)             依据: AOD4126 规格书 日期: 2026-08-24 来源: 推导
mosfet_qgd = 10 nC (typ)            依据: AOD4126 规格书 日期: 2026-08-24 来源: 推导
mosfet_vgs_th = 3.3 V (typ)         依据: AOD4126 规格书 日期: 2026-08-24 来源: 推导

## TMC5160 驱动配置
tmc5160_rs = 0.05 Ω                依据: 硬件资源池 日期: 2026-08-24 来源: 你
tmc5160_vfs = 0.325 V               依据: TMC5160 datasheet ch28 感应电阻峰值阈值 (VSRT) 日期: 2026-08-24 来源: 推导
tmc5160_ifs = 6.5 A                 依据: VFS/RS = 0.325/0.05 日期: 2026-08-24 来源: 推导
tmc5160_globalscaler = 157          依据: (CS=31时) I=(32/32)×(GS+1)/256×IFS → GS+1=4×256/6.5≈157.5 日期: 2026-08-24 来源: 推导
tmc5160_irun = 31                   依据: 满额定电流 4A 需最大 CS 日期: 2026-08-24 来源: 推导
tmc5160_ihold = 22                  依据: IHOLD ≈ 70%×IRUN = 0.7×31≈22 日期: 2026-08-24 来源: 推导
tmc5160_ihold_delay = 6             依据: 推荐值, 平滑停转电流衰减 日期: 2026-08-24 来源: 推导
tmc5160_tpowerdown = 128            依据: 推荐值, 约 1-2 秒延迟 日期: 2026-08-24 来源: 推导

## TMC5160 时钟
tmc5160_clk_source = external        依据: PD14 TIM4_CH3 PWM 输出 日期: 2026-08-24 来源: 你
tmc5160_clk_freq = 15 MHz           依据: require.md TIM4 PWM 配置 日期: 2026-08-24 来源: 你
tmc5160_spi_max_sck = 7.5 MHz       依据: TMC5160 datasheet ch4: fSCK = fCLK/2 = 15/2 日期: 2026-08-24 来源: 推导

## TMC5160 SPI 配置
tmc5160_spi_mode = 3                 依据: TMC5160 datasheet ch4 SPI MODE 3 (CPOL=HIGH, CPHA=2EDGE) 日期: 2026-08-24 来源: 推导
tmc5160_spi_datasize = 8-bit         依据: TMC5160 40-bit datagram = 8-bit addr + 32-bit data 日期: 2026-08-24 来源: 推导
stm32_spi_prescaler = 16             依据: SPI3CLK=64MHz / 16 = 4MHz (≤7.5MHz max) 日期: 2026-08-24 来源: 推导
stm32_spi_baudrate = 4 Mbit/s        依据: 64MHz/16 日期: 2026-08-24 来源: 推导

## TMC5160 栅极驱动
tmc5160_drvstrength = 2              依据: AOD4126 Qgd=10nC, 中等驱动强度平衡开关速度与EMI 日期: 2026-08-24 来源: 推导
tmc5160_bbmtime = 16                 依据: 死区时间 200ns typ, 防止直通 日期: 2026-08-24 来源: 推导

## 斩波器配置 (初始值, 待实测调优)
chopper_toff = 5                     依据: Quick Configuration Guide 推荐起始值 日期: 2026-08-24 来源: 推导
chopper_tbl = 2                      依据: Quick Configuration Guide 推荐起始值 日期: 2026-08-24 来源: 推导
chopper_hstart = 4                   依据: Quick Configuration Guide 推荐起始值 日期: 2026-08-24 来源: 推导
chopper_hend = 0                     依据: Quick Configuration Guide 推荐起始值 日期: 2026-08-24 来源: 推导

## STM32 时钟树
stm32_hse = 8 MHz                    依据: CubeMX .ioc 日期: 2026-08-24 来源: 推导
stm32_sysclk = 480 MHz               依据: PLL1: 8MHz/1×120/2 日期: 2026-08-24 来源: 推导
stm32_hclk = 240 MHz                 依据: HPRE=DIV2 日期: 2026-08-24 来源: 推导
stm32_apb1 = 120 MHz                 依据: D2PPRE1=DIV2 日期: 2026-08-24 来源: 推导
stm32_apb2 = 120 MHz                 依据: D2PPRE2=DIV2 日期: 2026-08-24 来源: 推导
stm32_tim4clk = 240 MHz              依据: APB1=120MHz, APB1 timer×2 日期: 2026-08-24 来源: 推导
stm32_spi3clk = 64 MHz               依据: PCLK3=120MHz, SPI3CLK=CLKP 日期: 2026-08-24 来源: 推导
stm32_usart1clk = 64 MHz             依据: HSI 源 日期: 2026-08-24 来源: 推导
stm32_fdcanclk = 8 MHz               依据: HSE 直接 日期: 2026-08-24 来源: 推导
