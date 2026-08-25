# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p51

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 51
www.trinamic.com
速度相关的驱动特性控制寄存器 (0X10…0X1F)
R/W 地址 位 寄存器 描述 / 位名称
W 0x14 20 TCOOLTHRS
使能 CoolStep 和 stallGuard 功能的下限速度(无符号)。
设置此参数则在低速时禁用 CoolStep，因为低速时不能可靠工
作。在超过该速度时堵转停止功能(当内部运动控制器工作时，
使能 sg_stop)和堵转输出信号有效。在非 DcStep 模式下，一旦
速度降到这个阈值以下，它就会再次被禁用。
TCOOLTHRS ≥ TSTEP ≥ THIGH:
­ CoolStep 使能(如果已配置)
­ StealthChop voltage PWM 模式禁用
TCOOLTHRS ≥ TSTEP
­ 使能堵转停止，如果被配置
­ 使能堵转输出信号(DIAG0/1 ) (如果配置)
W 0x15 20 THIGH
该速度阈值允许系统切换到不同的斩波模式和全步来产生最大
扭矩(无符号)。每当通过 THIGH 阈值时，堵转检测功能会关闭 2
- 3 个电周期，以补偿切换模式的影响。
TSTEP ≤ THIGH:
­ CoolStep 被禁用(电机按设定的正常电流运行)
­ StealthChop 电压 PWM 模式被禁用
­ 如果设置了 vhighchm，斩波器将切换到 chm = 1，TFD =
0 (只有慢衰减的恒定关闭时间)
­ 如果设置了 vhighfs，电机以全步模式运行，堵转检测切
换到 DcStep 堵转检测
微步速度的时间基准: TSTEP = fCLK / fSTEP
