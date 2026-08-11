# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p78

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
78
www.trinamic.com
0X70: PWMCONF –电压脉宽调制模式STEALTHCHOP
位
名称
功能
备注
1
自调节(仅pwm_autoscale = 1 ) (复位缺省值)
当pwm_autograd=0，PWM_GRAD 初始化
PWM_GRAD_AUTO，并在运动过程中自动优化。
前提条件：
1.
PWM_OFS_AUTO 自动初始化。这需要电机以
IRUN 电流至少>130 毫秒，以便
a ) 检测停止
b ) 按照IRUN 电流等待时间大于128 个斩波周期
c )调节PWM_OFS_AUTO，满足
- 1 < PWM_SCALE_AUTO <1
2.
电机运行和1.5 * PWM _ OFS _ AUTO <PWM _
SCALE _ SUM <4 * PWM _ OFS _ AUTO 和PWM _
SCALE _ SUM <255。
调节PWM_GRAD_AUTO 所需的时间
每次变化+ / - 1 需要8 个全步时间。
支持降低的斩波频率来调节PWM_OFS_AUTO。
18
pwm_
autoscale
PWM 自动电流调节
0
用户定义的前馈PWM 幅度。当前IRUN 和IHOLD 设
置对此没有影响！
产生的PWM 振幅(0…255 之间)为:
PWM_OFS * ((CS_ACTUAL+1) / 32)
+ PWM_GRAD * 256 / TSTEP
1
使能自动电流控制(复位缺省值)
17
pwm_freq
1
PWM 频率
%00:
fPWM=2/1024 fCLK (复位缺省值)
%01:
fPWM=2/683 fCLK
%10:
fPWM=2/512 fCLK
%11:
fPWM=2/410 fCLK
16
pwm_freq
0


<!-- detected tables -->

| 0X70: PWMCONF –电压脉宽调制模式STEALTHCHOP |  |  |  |  |
|---|---|---|---|---|
| 位 | 名称 | 功能 | 备注 |  |
|  |  |  | 1 | 自调节(仅pwm autoscale = 1 ) (复位缺省值) _ 当pwm autograd=0，PWM GRAD 初始化 _ _ PWM GRAD AUTO，并在运动过程中自动优化。 _ _ 前提条件： 1. PWM OFS AUTO 自动初始化。这需要电机以 _ _ IRUN 电流至少>130 毫秒，以便 a ) 检测停止 b ) 按照IRUN 电流等待时间大于128 个斩波周期 c )调节PWM OFS AUTO，满足 _ _ - 1 < PWM SCALE AUTO <1 _ _ 2. 电机运行和1.5 * PWM OFS AUTO <PWM _ _ _ SCALE SUM <4 * PWM OFS AUTO 和PWM _ _ _ _ SCALE SUM <255。 _ 调节PWM GRAD AUTO 所需的时间 _ _ 每次变化+ / - 1 需要8 个全步时间。 支持降低的斩波频率来调节PWM OFS AUTO。 _ _ |
| 18 | pwm _ autoscale | PWM 自动电流调节 | 0 | 用户定义的前馈PWM 幅度。当前IRUN 和IHOLD 设 置对此没有影响！ 产生的PWM 振幅(0…255 之间)为: PWM OFS * ((CS ACTUAL+1) / 32) _ _ + PWM GRAD * 256 / TSTEP _ |
|  |  |  | 1 | 使能自动电流控制(复位缺省值) |
| 17 | pwm freq _ 1 | PWM 频率 | %00: f PWM=2/1024 f (复位缺省值) CLK %01: f =2/683 f PWM CLK %10: f =2/512 f PWM CLK %11: f =2/410 f PWM CLK |  |
| 16 | pwm freq _ 0 |  |  |  |
