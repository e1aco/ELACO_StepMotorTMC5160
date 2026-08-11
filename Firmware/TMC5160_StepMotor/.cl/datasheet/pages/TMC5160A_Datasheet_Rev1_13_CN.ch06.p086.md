# TMC5160A_Datasheet_Rev1_13_CN — 第6章 · p86

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
86
www.trinamic.com
注意：
修改GLOBALSCALER 或VS 电压会使参数自调整过程的结果无效。下一个AT#1 阶段开始之前，电机电流调节不能补
偿电源的变化。参数自调整只要在以后的操作中完成AT # 1 和AT # 2，就适应变化的条件。
6.2
StealthChop 选项
电压PWM有效值要根据电机转速调节才能保证电机目标电流。几个因素会影响达到电机目标电流
所需的电压值:电机电阻、反电动势(与速度成正比)以及实际供电电压。TMC5160提供了两种PWM调节模
式：带电流反馈调节的参数自调整( AT ) (pwm_autoscale = 1, pwm_autograd = 1)和速度前馈控制模式
(pwm_autoscale = 0 )。速度前馈控制模式不会对电源电压的变化或电机堵转等事件作出反应，但它提供
非常稳定的幅值。它不使用也不需要任何电流测量手段。当电机类型和电源电压是已知时，速度前馈控
制是完美的。我们推荐自动模式，除非在给定的运行条件下电流调节不满足。
推荐根据实际应用的电机类型和供电设置初始调整参数，此外自动调整模式能对参数变化做出相应，如
电机供电或者温度改变。
仅在已知电机和运行条件下考虑。在这种情况下，需要通过接口进行编程。参数PWM_GRAD 和
PWM_OFS 可以在参数自调整模式下确定。
根据外部时钟频率，设置分频器参数配置StealthChop 2的PWM频率。大多数应用的最佳PWM调制频
率在20 – 50KHz范围内，该频率段平衡了电流纹波、高速与动态功耗的关系。
STEALTHCHOP PWM 频率选择
时钟频率
fCLK
PWM_FREQ=%00
fPWM=2/1024 fCLK
PWM_FREQ=%01
fPWM=2/683 fCLK
PWM_FREQ=%10
fPWM=2/512 fCLK
PWM_FREQ=%11
fPWM=2/410 fCLK
18MHz
35.2kHz
52.7kHz
70.3kHz
87.8kHz
16MHz
31.3kHz
46.9kHz
62.5kHz
78.0kHz
12MHz (internal)
23.4kHz
35.1kHz
46.9kHz
58.5kHz
10MHz
19.5kHz
29.3kHz
39.1kHz
48.8kHz
8MHz
15.6kHz
23.4kHz
31.2kHz
39.0kHz
表6.1 PWM 频率选择-绿色/浅绿色:推荐
6.3
StealthChop 电流调节器
在StealthChop 电压PWM模式下，电流自定标功能(pwm_autoscale = 1, pwm_auto_grad = 1 )能自动调
节电机电流到所需的电流设置。电流自定标用作参数自调整( AT )的一部分，可以跟踪电机参数的变化。
芯片在斩波器导通时间内测量电机电流，通过比例调节器调节PWM_SCALE_AUTO，以使电机电流与目标
电流匹配。PWM_REG是该调节器的比例系数。通常，比例系数应当尽可能小以满足稳定和软调节性能
高的要求，但是比例系数必须足够大能快速跟随电机目标电流的变化(例如VREF的变化)。在参数自调整
的第二步AT# 2，PWM_REG同时补偿电机速度的变化。因此，AT # 2期间的加速度越高，PWM_REG设置
需要随之增大。用户需要根据系统选择归零适合的速度和加速度，通常来说电流自定标比例调节寄存器


<!-- detected tables -->

| STEALTHCHOP PWM 频率选择 |  |  |  |  |
|---|---|---|---|---|
| 时钟频率 f CLK | PWM FREQ=%00 _ f =2/1024 f PWM CLK | PWM FREQ=%01 _ f =2/683 f PWM CLK | PWM FREQ=%10 _ f =2/512 f PWM CLK | PWM FREQ=%11 _ f =2/410 f PWM CLK |
| 18MHz | 35.2kHz | 52.7kHz | 70.3kHz | 87.8kHz |
| 16MHz | 31.3kHz | 46.9kHz | 62.5kHz | 78.0kHz |
| 12MHz (internal) | 23.4kHz | 35.1kHz | 46.9kHz | 58.5kHz |
| 10MHz | 19.5kHz | 29.3kHz | 39.1kHz | 48.8kHz |
| 8MHz | 15.6kHz | 23.4kHz | 31.2kHz | 39.0kHz |
