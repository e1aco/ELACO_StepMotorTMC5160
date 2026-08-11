# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p57

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
57
www.trinamic.com
位
名称
备注
11
en_softstop
0: 硬停
1: 软停
软停模式总是使用减速斜坡的参数DMAX、V1、D1、VSTOP 和TZEROWAIT
来停止电机。当速度符号匹配参考开关位置( REFL 表示负速度，REFR 表示
正速度)并且相应的开关停止功能被使能时，停止发生。
在马达被释放之前，硬停止也使用TZEROWAIT。
注意:不要将软停与stallguard 2 结合使用。StealthChop 模式下高速运行使用
软停。在这种情况下，必须避免硬停，因为这会导致严重的过电流。
10
sg_stop
1 :使能stallguard 2 停止(也可在DcStep 模式下使用)。停止事件后需要禁用
以释放电机。TCOOLTHRS 为对应的速度阈值。
提示: 在电机加速期间不要启用，等到电机速度超过某个值，此时
StallGuard2 会提供稳定的结果。对应的速度阈值为TCOOLTHRS。
9
en_latch_encoder
1: 参考开关事件有效时将编码器位置锁定到ENC _ LATCH。
8
latch_r_inactive
1:.当右侧参考开关输入REFR 向非有效电平跳变时，位置锁存至XLATCH。
有效电平由pol_stop_r 定义。
7
latch_r_active
1:当右侧参考开关输入REFR 向有效电平跳变时，位置锁存至XLATCH。
提示:激活latch _ r _ active，通过读status_latch_r 来检测任何虚假停止事
件。
6
latch_l_inactive
1: 当左侧参考开关输入REFL 向非有效电平跳变时，位置锁存至XLATCH。
有效电平由pol _ stop _ l 定义.
5
latch_l_active
1：当左侧参考开关输入REFL 向有效电平跳变时，位置锁存至XLATCH。
提示:激活latch_l_active，通过读status_latch_l 来检测任何虚假的停止事
件。
4
swap_lr
1: 交换左右参考开关输入REFL 和REFR
3
pol_stop_r
设置右参考开关输入的有效极性。
0 =非反转，高有效: REFR 上的高电平会停止电机。


<!-- detected tables -->

| 位 | 名称 | 备注 |
|---|---|---|
| 11 | en softstop _ | 0: 硬停 1: 软停 软停模式总是使用减速斜坡的参数DMAX、V1、D1、VSTOP 和TZEROWAIT 来停止电机。当速度符号匹配参考开关位置( REFL 表示负速度，REFR 表示 正速度)并且相应的开关停止功能被使能时，停止发生。 在马达被释放之前，硬停止也使用TZEROWAIT。 注意:不要将软停与stallguard 2 结合使用。StealthChop 模式下高速运行使用 软停。在这种情况下，必须避免硬停，因为这会导致严重的过电流。 |
| 10 | sg stop _ | 1 :使能stallguard 2 停止(也可在DcStep 模式下使用)。停止事件后需要禁用 以释放电机。TCOOLTHRS 为对应的速度阈值。 提示: 在电机加速期间不要启用，等到电机速度超过某个值，此时 StallGuard2 会提供稳定的结果。对应的速度阈值为TCOOLTHRS。 |
| 9 | en latch encoder _ _ | 1: 参考开关事件有效时将编码器位置锁定到ENC LATCH。 _ |
| 8 | latch r inactive _ _ | 1:.当右侧参考开关输入REFR 向非有效电平跳变时，位置锁存至XLATCH。 有效电平由pol stop r 定义。 _ _ |
| 7 | latch r active _ _ | 1:当右侧参考开关输入REFR 向有效电平跳变时，位置锁存至XLATCH。 提示:激活latch r active，通过读status latch r 来检测任何虚假停止事 _ _ _ _ 件。 |
| 6 | latch l inactive __ | 1: 当左侧参考开关输入REFL 向非有效电平跳变时，位置锁存至XLATCH。 有效电平由pol stop l 定义. _ _ |
| 5 | latch l active __ | 1：当左侧参考开关输入REFL 向有效电平跳变时，位置锁存至XLATCH。 提示:激活 latch l active，通过读 status latch l 来检测任何虚假的停止事 __ _ _ 件。 |
| 4 | swap lr _ | 1: 交换左右参考开关输入REFL 和REFR |
| 3 | pol stop r _ _ | 设置右参考开关输入的有效极性。 0 =非反转，高有效: REFR 上的高电平会停止电机。 |
