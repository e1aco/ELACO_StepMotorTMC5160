# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p50

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 50
www.trinamic.com
速度相关的驱动特性控制寄存器 (0X10…0X1F)
R/W 地址 位 寄存器 描述 / 位名称
R 0x12 20 TSTEP
两个步进输入信号之间的实际测量时间，以 1 / fCLK 及 256 微步
为单位。测量范围为( 2^20 ) – 1 以防溢出或电机进入静止状态。
所有与 TSTEP 相关的阈值使用比较值的 1 / 16 的滞环来补偿时钟
或步进频率中的抖动。small_hysteresis 标志将滞环修改为较小 1
/ 32。
((Txxx*15/16)-1
或 (Txxx*31/32)-1 作为第二个比较值
这意味着，切换速度的低值等于计算的设置，但切换速度的高
值高于定义的磁滞设置。
当运动控制器有效时，对于给定速度 V，测量的 TSTEP 在
(224 / V) ≤ TSTEP ≤ 224 / V - 1 范围内
在 DcStep 模式下，TSTEP 不是电机的平均速度，而是每个微步
的速度。 微步速度可能不稳定，而且因为运行速度低于目标速
度，所以不对应实际电机速度。
W 0x13 20 TPWMTHRS
StealthChop 电压 PWM 模式的上限速度。
TSTEP ≥ TPWMTHRS
­ 如果配置了 StealthChop ，则 StealthChop PWM 使能，
­ DcStep 禁用
