# .cl/datasheet 索引（由 /cl init 生成）

> 提取引擎: pdf_extract.py (technical / pymupdf_tables)，章节按目录边界(EN) 分割
> 生成日期: 2026-08-05
> 用途: 代码生成时寄存器/时序/引脚依据溯源（引用 `<file>`，见文末引用格式）
> 读取协议: 先读本 index 定位章节/页文件 → 按需 Read 目标文件；禁止整读 >4k token 文件。

## 文档清单

| 文件 | 来源 PDF | 页数 | 约 tokens | 说明 / 权威性 |
|------|----------|------|-----------|------|
| `TMC5160A_Datasheet_Rev1.14.*`（ch 分章 + pages/ 逐页） | datasheet/TMC5160A_Datasheet_Rev1.14.pdf | 134 | ~115k | TMC5160A 数据手册 **EN（权威，优先引用）** |
| `TMC5160A_Datasheet_Rev1_13_CN.*`（ch 分章 + pages/ 逐页） | datasheet/TMC5160A_Datasheet_Rev1_13_CN.pdf | 189 | ~68k | TMC5160A 中文版（仅对照语义时按需读） |
| `57CME13 MS31.md` | datasheet/57CME13 MS31.pdf | 1 | ~0.3k | 57 步进电机规格（电机2 型号） |
| `C457934_场效应管(MOSFET)_AOD4126_规格书_WJ290500.md` | datasheet/C457934_..._AOD4126_..._WJ290500.PDF | 7 | ~5k | 外置 MOSFET AOD4126（功率级） |

## TMC5160A（EN，权威）章节导航

> 大章（>4k token）拆为 `pages/<base>.chNN.pXXX.md` 逐页文件；小章为整章文件。
> 页码 = PDF 页码（逐页文件页号即文件名 `.pXXX`；整章文件内以 `--- [PAGE n] ---` 标注）。

| 章 | 主题 | 页码 | 文件 |
|----|------|------|------|
| 0 | 封面/特性/目录 | 1-4 | `TMC5160A_Datasheet_Rev1.14_ch00_front.md` |
| 1 | 概述/关键概念 | 5-10 | `pages/*.ch01.p005` ~ `p010` |
| 2 | 引脚布局与描述 | 11-14 | `pages/*.ch02.p011` ~ `p014` |
| 3 | 应用电路/MOSFET/斜率 | 15-22 | `pages/*.ch03.p015` ~ `p022` |
| 4 | SPI 接口（数据帧/时序） | 23-25 | `TMC5160A_Datasheet_Rev1.14_ch04_spi_interface.md` |
| 5 | 单线 UART 接口 | 26-30 | `pages/*.ch05.p026` ~ `p030` |
| 6 | **寄存器映射**（见下） | 31-56 | `pages/*.ch06.p031` ~ `p056` |
| 7 | StealthChop | 57-67 | `pages/*.ch07.p057` ~ `p067` |
| 8 | SpreadCycle 斩波器 | 68-73 | `pages/*.ch08.p068` ~ `p073` |
| 9 | 采样电阻选择 | 74-75 | `..._ch09_selecting_sense_resistors.md` |
| 10 | 速度模式控制 | 76-77 | `..._ch10_velocity_based_mode_control.md` |
| 11 | 诊断与保护 | 78-80 | `..._ch11_diagnostics_and_protection.md` |
| 12 | 斜坡发生器（单位换算/运动曲线） | 81-86 | `pages/*.ch12.p081` ~ `p086` |
| 13 | StallGuard2 负载测量 | 87-90 | `..._ch13_stallguard2_load_measurement.md` |
| 14 | CoolStep | 91-93 | `..._ch14_coolstep_operation.md` |
| 15 | STEP/DIR 接口 | 94-96 | `..._ch15_step_dir_interface.md` |
| 16 | DIAG 输出 | 97-98 | `..._ch16_diag_outputs.md` |
| 17 | 微步查表/细分 | 99-104 | `pages/*.ch17.p099` ~ `p104` |
| 18-24 | 其余（正弦表/急停/接口/直流电机/快速配置/起步/独立运行） | 105-118 | `..._ch1X_*.md`（整章） |
| 26 | 时钟/晶振输入 | 119 | `..._ch26_clock_oscillator_and_input.md` |
| 28 | 电气特性 | 120-124 | `pages/*.ch28.p120` ~ `p124` |
| 29 | 布局考虑 | 125-127 | `..._ch29_layout_considerations.md` |
| 30+ | 封装/其他 | 128+ | `..._ch3X_*.md`（整章） |

## 第6章 寄存器映射 → 关键寄存器定位（EN）

> 引用格式：`// 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p032.md: GCONF`

| 寄存器 | 地址 | 所在页文件（ch06） | 说明 |
|--------|------|---------------------|------|
| GCONF | 0x00 | p032 | 全局配置（en_pwm_mode、shaft、diag_*） |
| GSTAT | 0x01 | p033 | 全局状态（reset/uv_cp/drv_err） |
| TPOWERDOWN | 0x11 | p038 | 静止降流延迟 |
| TCOOLTHRS | 0x14 | p032/p039/p043 | 速度阈值 |
| RAMPMODE | 0x20 | p040 | 运动模式（0=位置、1=速度正、2=速度负、3=保持） |
| XACTUAL | 0x21 | p034/p040/p042 | 实际位置 |
| VSTART | 0x23 | p040 | 起始速度 |
| A1 | 0x24 | p040 | 第一段加速度 |
| V1 | 0x25 | p040 | 第一段目标速度 |
| AMAX | 0x26 | p040 | 第二段加速度 |
| VMAX | 0x27 | p040/p044 | 最大速度 |
| DMAX | 0x28 | p040 | 第二段减速度 |
| D1 | 0x2A | p040 | 第一段减速度 |
| VSTOP | 0x2B | p041 | 停止速度 |
| TZEROWAIT | 0x2C | p041 | 归零等待时间 |
| XTARGET | 0x2D | p041 | 目标位置 |
| IHOLD_IRUN | 0x10 | p038 | 保持/运行电流 |
| VDCMIN | 0x33 | p042 | 直流电机最小电压 |
| SW_MODE | 0x34 | p042 | 参考开关配置 |
| RAMP_STAT | 0x35 | p042 | 斜坡状态（位置事件） |
| ENCMODE | 0x38 | p045 | 编码器模式 |
| X_ENC | 0x39 | p045 | 编码器实际位置 |
| ENC_CONST | 0x3A | p045 | 编码器累加常数 |
| ENC_STATUS | 0x3B | p045 | 编码器状态 |
| ENC_LATCH | 0x3C | p045 | 编码器锁存 |
| ENC_DEVIATION | 0x3D | p045 | 编码器偏差阈值 |
| CHOPCONF | 0x6C | p048/p051/p052 | 斩波器配置（细分/TOFF） |
| COOLCONF | 0x6D | p048/p053/p056 | CoolStep/StallGuard |
| DRV_STATUS | 0x6F | p033/p056 | 驱动诊断（ot/s2g/uv_cp） |
| PWMCONF | 0x70 | p048/p054/p055 | StealthChop PWM |

> 写访问：地址需加 0x80（`Add 0x80 to the address Addr for write accesses`，见 ch06.p031）。
> 读回头 8 bit 为 SPI_STATUS（见 ch04）。

## 引用格式规范

- 整章文件：`// 依据 .cl/datasheet/TMC5160A_Datasheet_Rev1.14_ch04_spi_interface.md 第4章: SPI 数据帧结构`
- 逐页文件：`// 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p032.md: GCONF 寄存器`
- 小文档：`// 依据 .cl/datasheet/57CME13 MS31.md: 电机规格`
