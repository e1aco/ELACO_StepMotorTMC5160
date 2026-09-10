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
tmc5160_globalscaler = 256(复位默认, 未写)  依据: init 代码未写 GLOBALSCALER, GS=256→满量程 IFS=VFS/RS=6.5A, 电流全靠 CS 分频; 早期推导 157+CS31 方案未采用 日期: 2026-09-10 来源: 代码核对
tmc5160_irun = 20                   依据: (20+1)/32×6.5/√2=3.02A RMS; 实测 CS=27(4A) 双机满流过热 OTPW→热致 S2 误触发, 降 20 后 150 轮浸泡 0 次 日期: 2026-09-01 来源: 实测校准
tmc5160_ihold = 3                   依据: (3+1)/32×6.5/√2=0.576A RMS, 保持力矩≈0.19N·m; 用户 2026-09-10 定案"静止发热大"从 6(1.0A) 降档 日期: 2026-09-10 来源: 用户定值
tmc5160_ihold_delay = 8             依据: IHOLDDELAY[19:16]=8 → 2^18×8/15MHz=140ms 后降至 IHOLD (09-10 代码核对: 旧记录"DELAY=6"系注释位域写反误读, 实际代码一直=8) 日期: 2026-09-10 来源: 代码核对
tmc5160_tpowerdown = 128            依据: 推荐值, 约 1-2 秒延迟 日期: 2026-08-24 来源: 推导

## TMC5160 时钟
tmc5160_clk_source = external        依据: PD14 TIM4_CH3 PWM 输出 日期: 2026-08-24 来源: 你
tmc5160_clk_freq = 15 MHz           依据: require.md TIM4 PWM 配置; 软件比值验证: SOAK r3 稳态 XACTUAL 每秒恒差 17881 = 20000×15e6/2^24 精确匹配 → fCLK=15.00MHz±0.01% (示波器终验仍待做) 日期: 2026-09-10 来源: 推导+软件实测
tmc5160_spi_max_sck = 7.5 MHz       依据: TMC5160 datasheet ch4: fSCK = fCLK/2 = 15/2 日期: 2026-08-24 来源: 推导

## TMC5160 SPI 配置
tmc5160_spi_mode = 3                 依据: TMC5160 datasheet ch4 SPI MODE 3 (CPOL=HIGH, CPHA=2EDGE) 日期: 2026-08-24 来源: 推导
tmc5160_spi_datasize = 8-bit         依据: TMC5160 40-bit datagram = 8-bit addr + 32-bit data 日期: 2026-08-24 来源: 推导
stm32_spi_prescaler = 16             依据: SPI3 kernel=PLL3Q 103.2MHz ÷16 = 6.45MHz (≤7.5MHz 上限) 日期: 2026-09-09 来源: 实测校准
stm32_spi_baudrate = 6.45 Mbit/s     依据: PLL3Q 103.2MHz/16; CubeMX 2026-09-09 改配置后 [SPI OK] 复测通过, 写帧20us/读双报54us 实测 日期: 2026-09-09 来源: 实测校准
stm32_spi_kernel_clk = 103.2 MHz     依据: PLL3: HSE8MHz/M5=1.6 ×N129=206.4 VCO ÷Q2 日期: 2026-09-09 来源: CubeMX+推导

## TMC5160 通讯事实 (2026-09-09 SPI 验证轮沉淀)
tmc5160_ihold_irun_readable = false   依据: IHOLD_IRUN(0x10) 只写寄存器, 回读恒0, 不可作回读判据; TPOWERDOWN(0x11) 同 W (.cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch05.p038.md) 日期: 2026-09-09 来源: datasheet+实测
tmc5160_enc_const_readable = false    依据: ENC_CONST(0x3A) 标 W (ch06.p045), 回读恒0, 与 IHOLD_IRUN 同类; SPI 保真测试需 RW 寄存器时选 XTARGET(0x2D, ch06.p041 RW) 日期: 2026-09-10 来源: datasheet+实测(SOAK r1 教训)
tmc5160_spi_fidelity_6p45M = verified 依据: 2026-09-10 SOAK r3, U2 真实运转(VACTUAL=20000 恒速, CS_ACTUAL=20 满载流)噪声工况下 XTARGET 写读回显 222170 帧 + 静置 2000 帧 + GCONF 对照, 合计 0 bit 翻转 → 6.45Mbps 位保真成立, "H7 比 F407 快导致 SPI 位翻转"假设证伪 日期: 2026-09-10 来源: 实测
u2_bphase_s2gb_confirmed = true       依据: 2026-09-10 r7/r7b 扫描: DRVSTRENGTH{0,5,7 最强}×CS{20,8} 全 12 格 s2gb(ds bit28) 恒报 + GSTAT.drv_err 恒有 + olb 多格同报 + 轴零净转 → 驱动电流档位论排除(drvs 调寄存器的幅度救不了)；s2gb 语义=高边导通时 BMA/BMB 桥中点电压异常低(ch02 p13-14 HB/CB/BM 脚定义+Figure 11.1)，olb=电流不达标 → 组合=B 桥实际不导通且桥中点被拽低；候选=VSA=12V 时 11.5V 栅压稳压器(12VOUT)压差仅 0.5V 轨塌陷 / 桥中点自举电容(CB1/CB2)损坏 / 焊桥拉低 LA-BM 相邻脚(37-40 脚区) / B 低边管击穿。鉴别：24V 重跑全清=轨问题；表量 12VOUT<10.5V 静态=轨问题；断电机重跑仍 s2gb=板侧 日期: 2026-09-10 来源: 实测(r6+r7b)+ch02/ch11
tmc5160_spi_all_zero_reads = chip_no_power_or_no_clk  依据: 2026-09-10 r5/r6 实测——TMC5160 无 VM(24V) 供电时 MISO 恒 0, 全部寄存器读回 0x00000000(非 0xFFFFFFFF), 连 DRV_STATUS.stst(静止必1)都为 0; 判活必须用"非零签名"(CHOPCONF 应=init 写入值)而非等值回显(死芯片读 0 会让 GCONF=0 对照组假通过) 日期: 2026-09-10 来源: 实测
tmc5160_spi_status_byte = 0x38 静止正常  依据: 回复帧 byte[39:32]=SPI_STATUS(bit5 pos_reached|bit4 vel_reached|bit3 standstill|bit1 drv_err|bit0 reset), 非 sync 字节, 静止态=0x38 (ch04 §4.1.2) 日期: 2026-09-09 来源: datasheet+实测
tmc5160_tCSH_us = 10                  依据: tCSH>2×tCLK+10ns=510ns@4MHz, drv WriteReg/ReadReg 帧后加 10us 间隔 (ch04 §4.3 表) 日期: 2026-09-09 来源: datasheet, drv 已实施
u1_chip_populated = false             依据: comm_test 注释"芯片1未焊接", boot 自检仅测 U2 (PD3 CS) 日期: 2026-09-09 来源: 你(硬件)

## 编码器配置
encoder_ppr = 1000 PPR               依据: 实测 ENC_CONST=12.8 反推 200×256/12.8=4000cpr÷4=1000PPR 日期: 2026-09-01 来源: 你实测
encoder_cpr = 4000 counts/rev        依据: 1000PPR ×4 正交解码 日期: 2026-09-01 来源: 推导
encoder_resolution = 0.09°/count     依据: 360°/4000 日期: 2026-09-01 来源: 推导
encoder_enc_const = 12.8             依据: TMC5160 ENC_CONST = FSC×USC/cpr = 200×256/4000 日期: 2026-09-01 来源: 推导
encoder_encmodes = 0x00              依据: 源工程 tmc5160_usr.c ENCMODE 写入值 日期: 2026-09-01 来源: 源工程
encoder_tol = 256 microsteps         依据: TMC5160_ENC_TOLERANCE 定义 日期: 2026-09-01 来源: 源工程
motor_fullsteps_per_rev = 200        依据: 1.8° 步距角 日期: 2026-08-24 来源: 电机规格书
motor_microsteps = 256               依据: CHOPCONF MRES 配置 日期: 2026-08-24 来源: 推导
motor_counts_per_rev = 51200         依据: 200×256=51200 微步/圈（实测确认）日期: 2026-09-01 来源: 你实测

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
