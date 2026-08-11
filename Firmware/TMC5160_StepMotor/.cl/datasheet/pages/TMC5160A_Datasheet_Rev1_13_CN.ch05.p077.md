# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p77

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
77
www.trinamic.com
5.5.4 PWMCONF – 电压脉宽调制模式StealthChop
0X70: PWMCONF –电压脉宽调制模式STEALTHCHOP
位
名称
功能
备注
31
PWM_LIM
使能后，PWM 自动缩
放的最大幅度
当从spreadCycle 切换回StealthChop 时，
PWM_SCALE_AUTO 的最大限幅。该值定义了切换回时自
动电流控制的第7 位至第4 位的上限。设置该参数为在模
式转换回StealthChop 时降低电流的过冲。
它不限制PWM_GRAD 或PWM_GRAD 偏移量。
(默认值= 12 )
30
29
28
27
PWM_REG
调节回路梯度值
当pwm_autoscale = 1 时，用户定义的每半波对应的最大
PWM 调节幅度:
( 1…15 )
1 : 0.5 增量(最慢调节)
2 : 1 增量
3 : 1.5 增量
4 : 2 增量(复位缺省值)
……
8 : 4 增量
...
15 : 7.5 增量(最快调节)
26
25
24
23
-
保留
设置0
22
-
保留
设置0
21
freewheel1
允许不同的静止模式
当电机电流设置为零(I_HOLD=0)时，静止选项。
% 00 :正常操作
% 01 :空转
% 10 :LS 驱动器线圈短路
% 11 :HS 驱动器线圈短路
20
freewheel0
19
pwm_
autograd
PWM 自动调节梯度
0
PWM_GRAD 的固定值
(PWM_GRAD_AUTO = PWM_GRAD)


<!-- detected tables -->

| 0X70: PWMCONF –电压脉宽调制模式STEALTHCHOP |  |  |  |  |
|---|---|---|---|---|
| 位 | 名称 | 功能 | 备注 |  |
| 31 | PWM LIM _ | 使能后，PWM 自动缩 放的最大幅度 | 当从spreadCycle 切换回StealthChop 时， PWM SCALE AUTO 的最大限幅。该值定义了切换回时自 _ _ 动电流控制的第7 位至第4 位的上限。设置该参数为在模 式转换回StealthChop 时降低电流的过冲。 它不限制PWM GRAD 或PWM GRAD 偏移量。 _ _ (默认值= 12 ) |  |
| 30 |  |  |  |  |
| 29 |  |  |  |  |
| 28 |  |  |  |  |
| 27 | PWM REG _ | 调节回路梯度值 | 当pwm autoscale = 1 时，用户定义的每半波对应的最大 _ PWM 调节幅度: ( 1…15 ) 1 : 0.5 增量(最慢调节) 2 : 1 增量 3 : 1.5 增量 4 : 2 增量(复位缺省值) …… 8 : 4 增量 ... 15 : 7.5 增量(最快调节) |  |
| 26 |  |  |  |  |
| 25 |  |  |  |  |
| 24 |  |  |  |  |
| 23 | - | 保留 | 设置0 |  |
| 22 | - | 保留 | 设置0 |  |
| 21 | freewheel1 | 允许不同的静止模式 | 当电机电流设置为零(I HOLD=0)时，静止选项。 _ % 00 :正常操作 % 01 :空转 % 10 :LS 驱动器线圈短路 % 11 :HS 驱动器线圈短路 |  |
| 20 | freewheel0 |  |  |  |
| 19 | pwm _ autograd | PWM 自动调节梯度 | 0 | PWM GRAD 的固定值 _ (PWM GRAD AUTO = PWM GRAD) _ _ _ |
