# TMC5160A_Datasheet_Rev1_13_CN — 第6章 · p95

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
95
www.trinamic.com
STEALTHCHOP 相关参数
参数
描述
设置
备注
en_spread_
cycle
禁用StealthChop (寄存器GCONF)。
1
禁止StealthChop
0
使能StealthChop
TPWMTHRS
指定StealthChop 操作的最高速度。按照所需阈值速
度运行时，读出TSTEP 设置(两个微步之间的时
间)。
0 …
1048575
TSTEP 小于TPWMTHRS 时
StealthChop 无效
PWM_LIM
用于限制从spreadCycle 切换到StealthChop 时引起
的过冲。减小该值产生较低的电流冲击。
0 … 15
8 位幅值限幅的高4 位(缺
省12)
pwm_
autoscale
使能带电流测量的自定标模式
0 为速度前向控制模式
0
速度前向控制模式
1
带电流测量的自调节模式
pwm_
autograd
使能PWM_GRAD_AUTO 自调整
0
禁用，调用寄存器的
PWM_GRAD 参数
1
使能
PWM_FREQ
PWM 频率选择。一般最低的设置结果最佳。在每
个斩波器输出处测量的频率是有效斩波器频率
fPWM 的一半
0
fPWM=2/1024 fCLK
1
fPWM=2/683 fCLK
2
fPWM=2/512 fCLK
3
fPWM=2/410 fCLK
PWM_REG
用户定义的PWM 幅度调节比例系数，当
pwm_autoscale=1 时，比例系数越高代表调节速度
越快
1 … 15
每全步PWM_SCALE_AUTO
调节器调节0.5 到7.5 步
PWM_OFS
速度前向调节模式下用户定义的PWM 幅度(偏移
量)，也是参数自调整阶段PWM_OFFS_AUTO 初始
值。
0 … 255
PWM_OFS=0 禁用电流线
性调节
PWM_GRAD
速度前向调节模式下用户定义的PWM 幅度(梯度)，
也是参数自调节阶段PWM_GRAD_AUTO 的初始
值。
0 … 255
FREEWHEEL
当电机电流设置为零( I _ HOLD = 0 )时，静止选项。
仅在使能StealthChop 时有效。飞轮选项电机易于移
动，两个线圈短路选项对应被动制动。
0
正常操作
1
空转
2
使能低端功率管
3
使能高端功率管
PWM_SCALE
_AUTO
电流调节器确定的实际StealthChop 斩波电压PWM
修正值。在参数自整整阶段调节应接近0。
-255 …
255
(只读)在spreadCycle 中操
作时，该值将冻结


<!-- detected tables -->

| STEALTHCHOP 相关参数 |  |  |  |
|---|---|---|---|
| 参数 | 描述 | 设置 | 备注 |
| en spread _ _ cycle | 禁用StealthChop (寄存器GCONF)。 | 1 | 禁止StealthChop |
|  |  | 0 | 使能StealthChop |
| TPWMTHRS | 指定StealthChop 操作的最高速度。按照所需阈值速 度运行时，读出TSTEP 设置(两个微步之间的时 间)。 | 0 … 1048575 | TSTEP 小于TPWMTHRS 时 StealthChop 无效 |
| PWM LIM _ | 用于限制从 spreadCycle 切换到 StealthChop 时引起 的过冲。减小该值产生较低的电流冲击。 | 0 … 15 | 8 位幅值限幅的高4 位(缺 省12) |
| pwm _ autoscale | 使能带电流测量的自定标模式 0 为速度前向控制模式 | 0 | 速度前向控制模式 |
|  |  | 1 | 带电流测量的自调节模式 |
| pwm _ autograd | 使能PWM GRAD AUTO 自调整 _ _ | 0 | 禁用，调用寄存器的 PWM GRAD 参数 _ |
|  |  | 1 | 使能 |
| PWM FREQ _ | PWM 频率选择。一般最低的设置结果最佳。在每 个斩波器输出处测量的频率是有效斩波器频率 fPWM 的一半 | 0 | f =2/1024 f PWM CLK |
|  |  | 1 | f =2/683 f PWM CLK |
|  |  | 2 | f =2/512 f PWM CLK |
|  |  | 3 | f =2/410 f PWM CLK |
| PWM REG _ | 用 户 定 义 的 PWM 幅 度 调 节 比 例 系 数 ， 当 pwm autoscale=1 时，比例系数越高代表调节速度 _ 越快 | 1 … 15 | 每全步PWM SCALE AUTO _ _ 调节器调节0.5 到7.5 步 |
| PWM OFS _ | 速度前向调节模式下用户定义的 PWM 幅度(偏移 量)，也是参数自调整阶段 PWM OFFS AUTO 初始 _ _ 值。 | 0 … 255 | PWM OFS=0 禁用电流线 _ 性调节 |
| PWM GRAD _ | 速度前向调节模式下用户定义的PWM 幅度(梯度)， 也是参数自调节阶段 PWM GRAD AUTO 的初始 _ _ 值。 | 0 … 255 |  |
| FREEWHEEL | 当电机电流设置为零( I HOLD = 0 )时，静止选项。 _ 仅在使能StealthChop 时有效。飞轮选项电机易于移 动，两个线圈短路选项对应被动制动。 | 0 | 正常操作 |
|  |  | 1 | 空转 |
|  |  | 2 | 使能低端功率管 |
|  |  | 3 | 使能高端功率管 |
| PWM SCALE _ AUTO _ | 电流调节器确定的实际StealthChop 斩波电压PWM 修正值。在参数自整整阶段调节应接近0。 | -255 … 255 | (只读)在spreadCycle 中操 作时，该值将冻结 |
