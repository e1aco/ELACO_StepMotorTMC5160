# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p39

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
39
www.trinamic.com
5.1
通用配置寄存器
通用配置寄存器(0X00…0X0F)
R/W
地址
n
寄存器
描述/ 位名称
RW
0x00
17
GCONF
Bit
GCONF – 全局配置标志
0
recalibrate
1:
不使能驱动器期间的过零重新校准(通过ENN 或
TOFF 设置)
1
faststandstill
超过该时间没有步进信号输入则产生静止标志:
1:
短时间长度: 2^18 时钟
0:
正常时间长度: 2^20 时钟
2
en_pwm_mode
1:
使能StealthChop 电压PWM 模式(取决于速度阈
值)。仅在静止状态下及IHOLD =标称IRUN 电流时
进行从断开到导通的切换。
3
multistep_filt
1:
使用外部步进STEP 输入源时候，使能StealthChop
的步进STEP 输入滤波器优化性能(缺省=1)
4
shaft
1:
电机反向
5
diag0_error (仅SD_MODE=1)
1:
使能DIAG0 在驱动器遇到以下故障时输出故障指示
信号: 过温( ot )、对地短路( s2g )、电荷泵欠压( uv _
CP )
DIAG0 总是显示复位状态，即在复位状态期间为有效的
低电平
6
diag0_otpw (仅SD_MODE=1)
1:
使能DIAG0 输出驱动器过热预警( otpw )指示信号
7
diag0_stall (SD_MODE=1)
1:
使能DIAG0 输出电机堵转有效信号(在使用此功能
之前设置TCOOLTHRS)
diag0_step (SD_MODE=0)
0:
DIAG0 输出中断信号


<!-- detected tables -->

| 通用配置寄存器(0X00…0X0F) |  |  |  |  |  |
|---|---|---|---|---|---|
| R/W | 地址 | n | 寄存器 | 描述/ 位名称 |  |
| RW | 0x00 | 17 | GCONF | Bit | GCONF – 全局配置标志 |
|  |  |  |  | 0 | recalibrate 1: 不使能驱动器期间的过零重新校准(通过 ENN 或 TOFF 设置) |
|  |  |  |  | 1 | faststandstill 超过该时间没有步进信号输入则产生静止标志: 1: 短时间长度: 2^18 时钟 0: 正常时间长度: 2^20 时钟 |
|  |  |  |  | 2 | en pwm mode _ _ 1: 使能 StealthChop 电压 PWM 模式 (取决于速度阈 值)。仅在静止状态下及 IHOLD =标称IRUN 电流时 进行从断开到导通的切换。 |
|  |  |  |  | 3 | multistep filt _ 1: 使用外部步进STEP 输入源时候，使能StealthChop 的步进STEP 输入滤波器优化性能(缺省=1) |
|  |  |  |  | 4 | shaft 1: 电机反向 |
|  |  |  |  | 5 | diag0 error (仅SD MODE=1) _ _ 1: 使能DIAG0 在驱动器遇到以下故障时输出故障指示 信号: 过温( ot )、对地短路( s2g )、电荷泵欠压( uv _ CP ) DIAG0 总是显示复位状态，即在复位状态期间为有效的 低电平 |
|  |  |  |  | 6 | diag0 otpw (仅SD MODE=1) _ _ 1: 使能DIAG0 输出驱动器过热预警( otpw )指示信号 |
|  |  |  |  | 7 | diag0 stall (SD MODE=1) _ _ 1: 使能DIAG0 输出电机堵转有效信号(在使用此功能 之前设置TCOOLTHRS) diag0 step (SD MODE=0) _ _ 0: DIAG0 输出中断信号 |
