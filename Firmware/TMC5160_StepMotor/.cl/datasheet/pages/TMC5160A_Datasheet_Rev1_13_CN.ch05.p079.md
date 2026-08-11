# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p79

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
79
www.trinamic.com
0X70: PWMCONF –电压脉宽调制模式STEALTHCHOP
位
名称
功能
备注
15
PWM_
GRAD
用户定义的梯度值
用于调节PWM 幅值的速度相关梯度；
PWM_GRAD * 256 / TSTEP
这个值被加到PWM_AMPL 中，以补偿速度相关的电机反
电动势。
设置PWM_GRAD 作为自动缩放的初始值，可加快自调节
过程。先设置pwm_autoscale=0，根据特定应用设置
PWM_GRAD。之后设置pwm_autoscale=1。完成后使能
StealthChop 。
提示:
初始调节，读PWM_GRAD_AUTO 得到所需的初始值。
14
13
12
11
10
9
8
7
PWM_
OFS
用户定义的幅值(偏移
量)
用户定义的PWM 振幅偏移( 0 - 255 )，与静止状态下的全
电机电流(CS_ACTUAL = 31 )相关。
(复位缺省值= 30 )
设置PWM _ OFS 作为自动缩放的初始值，可加快自调节
过程。先设置pwm_autoscale=0，根据特定应用设置
PWM_OFS。之后设置pwm_autoscale=1。完成后使能
StealthChop 。
PWM_OFS = 0 将关闭电机电流缩小到低于电机特定的较
低测量阈值。此设置应仅在某些条件下使用，例如当电源
电压可以上下变化两倍或更多倍时。它可以防止电机超出
调节范围，也可以防止电压低于调整的下限。
PWM_OFS > 0 允许自动缩放到低PWM 占空比，甚至低于
较低的调节阈值。这可实现在实际(保持)电流定标器(寄存
器IHOLD_IRUN)上产生较低（静止）电流。
6
5
4
3
2
1
0


<!-- detected tables -->

| 0X70: PWMCONF –电压脉宽调制模式STEALTHCHOP |  |  |  |
|---|---|---|---|
| 位 | 名称 | 功能 | 备注 |
| 15 | PWM _ GRAD | 用户定义的梯度值 | 用于调节PWM 幅值的速度相关梯度； PWM GRAD * 256 / TSTEP _ 这个值被加到PWM AMPL 中，以补偿速度相关的电机反 _ 电动势。 设置PWM GRAD 作为自动缩放的初始值，可加快自调节 _ 过程。先设置pwm autoscale=0，根据特定应用设置 _ PWM GRAD。之后设置pwm autoscale=1。完成后使能 _ _ StealthChop 。 提示: 初始调节，读PWM GRAD AUTO 得到所需的初始值。 _ _ |
| 14 |  |  |  |
| 13 |  |  |  |
| 12 |  |  |  |
| 11 |  |  |  |
| 10 |  |  |  |
| 9 |  |  |  |
| 8 |  |  |  |
| 7 | PWM _ OFS | 用户定义的幅值(偏移 量) | 用户定义的PWM 振幅偏移( 0 - 255 )，与静止状态下的全 电机电流(CS ACTUAL = 31 )相关。 _ (复位缺省值= 30 ) 设置PWM OFS 作为自动缩放的初始值，可加快自调节 _ 过程。先设置pwm autoscale=0，根据特定应用设置 _ PWM OFS。之后设置pwm autoscale=1。完成后使能 _ _ StealthChop 。 PWM OFS = 0 将关闭电机电流缩小到低于电机特定的较 _ 低测量阈值。此设置应仅在某些条件下使用，例如当电源 电压可以上下变化两倍或更多倍时。它可以防止电机超出 调节范围，也可以防止电压低于调整的下限。 PWM OFS > 0 允许自动缩放到低PWM 占空比，甚至低于 _ 较低的调节阈值。这可实现在实际(保持)电流定标器(寄存 器IHOLD IRUN)上产生较低（静止）电流。 _ |
| 6 |  |  |  |
| 5 |  |  |  |
| 4 |  |  |  |
| 3 |  |  |  |
| 2 |  |  |  |
| 1 |  |  |  |
| 0 |  |  |  |
