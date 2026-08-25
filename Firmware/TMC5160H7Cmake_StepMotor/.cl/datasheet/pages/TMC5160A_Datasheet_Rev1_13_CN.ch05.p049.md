# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p49

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 49
www.trinamic.com
5.2 与速度相关的驱动特性控制寄存器
速度相关的驱动特性控制寄存器 (0X10…0X1F)
R/W 地址 位 寄存器 描述 / 位名称
W 0x10
5
+
5
+
4
IHOLD_IRUN
位 IHOLD_IRUN – 驱动电流控制
4..0 IHOLD
静止状态下电机电流 (0=1/32…31=32/32)
StealthChop 模式下，设置 IHOLD = 0 可配置电机静止
状态为飞轮模式或线圈短路模式。
12..8 IRUN
电机运行电流(0=1/32…31=32/32)
提示:选择适合的采样电阻，建议 IRUN 设置范围是
16 到 31，以获得最佳的微步性能。
19..16 IHOLDDELAY
设置电机检测到静止状态( stst = 1 )及 TPOWERDOWN
之后电流开始下降过程的时钟周期数。避免电机没有
真正停下来时电流变化造成的电机跳动。
0: 瞬间降电流
1..15: 每 2^18 个时钟倍数的时间衰减电流
W 0x11 8
TPOWER
DOWN
TPOWERDOWN 是电机静止标志（stst）有效到电机开始降电流
之间的延时时间。时间范围约为 0 至 4 秒
注意:要求最小设置为 2，以允许自动校正 StealthChop
PWM_OFFS_AUTO。
复位缺省值 10
0…((2^8)-1) * 2^18 tCLK
