# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p61

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 61
www.trinamic.com
4 event_stop_l 1:左停止（参考）开关有效产生的停止时间。
可以通过将 RAMP _ MODE 设置为保持模式或通过命令向相反方向移动
来去除停止条件和中断条件。在 soft_stop 模式下，该条件将保持激活
状态，直到电机停止向停止开关方向运动。禁用停止开关或停止功能
也会清除标记，但电机将继续运动。
该位与中断输出信号进行或运算
R+
WC
3 status_latch_r 1 :右锁存就绪
(设置 SW_MODE 寄存器使能位置锁存
latch_r_active 或 latch_r_inactive)
(写“1”清除)
2 status_latch_l 1 :左锁存就绪
(设置 SW_MODE 寄存器使能位置锁存
latch_l_active 或 latch_l_inactive)
(写“1”清除)
R 1 status_stop_r 右参考开关状态( 1 =有效)
0 status_stop_l 左参考开关状态( 1 =有效)
