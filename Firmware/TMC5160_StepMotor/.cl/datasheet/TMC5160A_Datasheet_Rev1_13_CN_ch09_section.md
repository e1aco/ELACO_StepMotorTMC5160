# TMC5160A_Datasheet_Rev1_13_CN — 第9章 基于速度的模式控制

--- [PAGE 107] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
107
www.trinamic.com
9. 基于速度的模式控制
TMC5160 支持不同的斩波模式和操作模式，以实现最佳电机控制。根据电机负载的不同，不同的模
式可以优化为最低噪声&高精度、最高动态或最高速度下的最大扭矩。某些功能，如CoolStep 或
Stallguard2，在一定的速度范围内是有用的。在需要宽速度范围的应用中可组合多个速度阈值实现不同
的操作模式。
图9.1 速度控制模式的选择
图9.1 显示所有可用阈值和顺序。VPWMTHRS、VHIGH 和VCOOLTHRS 由寄存器参数TPWMTHRS、
THIGH 和TCOOLTHRS 确定。每两个步进脉冲之间的时间间隔TSTEP 表示速度。在外部脉冲输入时对应电
机速度。TSTEP 单位统一按照256 微步计算。这样，当微步分辨率改变时，不必调整阈值。阈值表示相
同的电机速度，与微步设置无关。TSTEP 与这些阈值进行比较选择斩波模式或工作状态。磁滞宽度可以
设置成1 / 16 TSTEP 或者1 / 32 TSTEP，以避免在TSTEP 测量中外部干扰造成比较结果的不停切换。开关
阈值速度因磁滞宽度的设置分别提高了1/16 或者1/32 。StealthChop 阈值TPWMTHRS 没有显示，它应满
足VPWMTHRS < VCOOLTHRS。根据静止标志位置stst，电机电流为运行电流和静态保持电流。

--- [PAGE 108] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
108
www.trinamic.com
使用自动速度阈值可以针对不同的速度范围调整应用程序。CoolStep 等功能在设置中完全透明。这
样，一旦参数化，它们就不需要通过软件进行激活。
参数
描述
设置
备注
stst
电机静止标志。最后一个脉冲之后的220 个时钟后
有效。
0/1
只读，状态位
TPOWERDO
WN
电机停止( stst )到电流调整降电流的延迟时间。时
间范围约为0 至4 秒。
0…255
2^18 时钟周期的倍数对应
的时间
TSTEP
脉冲输入引脚的两个256 细分脉冲之间的实际测量
时间，单位为1 / fCLK。测量最大值为( 220 ) - 1。
0…
1048575
状态寄存器，只读。
实际测量步长时间(以tCLK
的倍数表示)
TPWMTHRS
TSTEP ≥TPWMTHRS
­
如果配置StealthChop ，则
StealthChop
PWM 使能。
­
DcStep 关闭。
0…
1048575 StealthChop 操作的上限速
度阈值
TCOOLTHRS
TCOOLTHRS ≥TSTEP ≥THIGH:
­
如果配置CoolStep ，则CoolStep 使能。
­
StealthChop 电压PWM 模式关闭。
TCOOLTHRS ≥TSTEP
­
如果已配置，堵转停止，stall 输出信号有
效。
0…
1048575
CoolStep 和stallGuard 的最
低速度阈值
THIGH
TSTEP ≤THIGH:
­
CoolStep 不使能（电机按照正常电流定标器
运行）
­
StealthChop 模式不使能
­
如果vhighchm 设置，斩波器切换成
chm=1，TFD=0 ，对应只有慢衰减的固定关
断时间的斩波模式
­
如果vhighfs 设置，电机进入全步状态，停
止检测切换到DcStep 停止检测
0…
1048575
CoolStep 和StallGuard 速度
阈值及可选的高速全步操
作的速度阈值
small_
hysteresis
步进频率信号磁滞宽度
( TSTEP * 15 / 16 ) - 1 为TSTEP 的较低速度阈值
( TSTEP * 31 / 32 ) - 1 为TSTEP 的较高速度阈值
0
1/16 磁滞宽度
1
1/21 磁滞宽度


<!-- detected tables -->

| 参数 | 描述 | 设置 | 备注 |
|---|---|---|---|
| stst | 电机静止标志。最后一个脉冲之后的 220个时钟后 有效。 | 0/1 | 只读，状态位 |
| TPOWERDO WN | 电机停止( stst )到电流调整降电流的延迟时间。时 间范围约为0 至4 秒。 | 0…255 | 2^18 时钟周期的倍数对应 的时间 |
| TSTEP | 脉冲输入引脚的两个256 细分脉冲之间的实际测量 时间，单位为1 / fCLK。测量最大值为( 220 ) - 1。 | 0… 1048575 | 状态寄存器，只读。 实际测量步长时间(以t CLK 的倍数表示) |
| TPWMTHRS | TSTEP ≥TPWMTHRS ­ 如果配置 StealthChop ，则 StealthChop PWM 使能。 ­ DcStep 关闭。 | 0… 1048575 | StealthChop 操作的上限速 度阈值 |
| TCOOLTHRS | TCOOLTHRS ≥TSTEP ≥THIGH: ­ 如果配置CoolStep ，则CoolStep 使能。 ­ StealthChop 电压PWM 模式关闭。 TCOOLTHRS ≥TSTEP ­ 如果已配置，堵转停止，stall 输出信号有 效。 | 0… 1048575 | CoolStep 和stallGuard 的最 低速度阈值 |
| THIGH | TSTEP ≤THIGH: ­ CoolStep 不使能（电机按照正常电流定标器 运行） ­ StealthChop 模式不使能 ­ 如 果 vhighchm 设 置 ， 斩 波 器 切 换 成 chm=1，TFD=0 ，对应只有慢衰减的固定关 断时间的斩波模式 ­ 如果 vhighfs 设置，电机进入全步状态，停 止检测切换到DcStep 停止检测 | 0… 1048575 | CoolStep 和StallGuard 速度 阈值及可选的高速全步操 作的速度阈值 |
| small _ hysteresis | 步进频率信号磁滞宽度 ( TSTEP * 15 / 16 ) - 1 为TSTEP 的较低速度阈值 ( TSTEP * 31 / 32 ) - 1 为TSTEP 的较高速度阈值 | 0 | 1/16 磁滞宽度 |
|  |  | 1 | 1/21 磁滞宽度 |
