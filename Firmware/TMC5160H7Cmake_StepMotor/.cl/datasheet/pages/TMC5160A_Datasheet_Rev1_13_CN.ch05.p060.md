# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p60

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 60
www.trinamic.com
R/W 位 名称 备注
R 13 status_sg 1 : CoolStep 驱动器或 DcStep 单元（如果使能)产生的有效 StallGuard2
输入信号。
提示:轮询此标志时，可能会错过堵转事件–激活 sg_stop 以确保不会错
过失速事件。
R+
WC
12 second_move 1:表明自动斜坡需要反向移动，例如由于运行中的参数变化
(写“1”以清除)
R 11 t_zerowait_
active
1:电机停止后 TZEROWAIT 有效的时间段。在此期间，电机处于静止状
态
R 10 vzero 1: 实际速度为 0。
R 9 position_
reached
1: 到达了目标位置。
当 XACTUAL 和 XTARGET 匹配时，此标志会被设置。
R 8 velocity_
reached
1: 达到了目标速度。
当 VACTUAL 和 VMAX 匹配时，此标志会被设置。
R+
WC
7 event_pos_
reached
1: 目标位置已经到达(position_reached 变为有效)事件。
(写入“1”以清除标志和中断条件)
该位与中断输出信号进行或运算。
R+
WC
6 event_stop_
sg
1 : StallGuard 2 停止事件。
复位寄存器将清除堵转状态，电机可能会重新启动运动，除非运动控
制器已经停止。
(写入“1”以清除标志和中断条件)
该位与中断输出信号进行或运算。
R 5 event_stop_r 1 : 右停止（参考）开关有效产生的停止事件。
可以通过将 RAMP _ MODE 设置为保持模式或通过命令向相反方向移动
来去除停止条件和中断条件。在 soft_stop 模式下，该条件将保持激活
状态，直到电机停止向停止开关方向运动。禁用停止开关或停止功能
也会清除标记，但电机将继续运动。
该位与中断输出信号进行或运算。
