# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p57

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 57
www.trinamic.com
位 名称 备注
11 en_softstop 0: 硬停
1: 软停
软停模式总是使用减速斜坡的参数 DMAX、V1、D1、VSTOP 和 TZEROWAIT
来停止电机。当速度符号匹配参考开关位置( REFL 表示负速度，REFR 表示
正速度)并且相应的开关停止功能被使能时，停止发生。
在马达被释放之前，硬停止也使用 TZEROWAIT。
注意:不要将软停与 stallguard 2 结合使用。StealthChop 模式下高速运行使用
软停。在这种情况下，必须避免硬停，因为这会导致严重的过电流。
10 sg_stop 1 :使能 stallguard 2 停止(也可在 DcStep 模式下使用)。停止事件后需要禁用
以释放电机。TCOOLTHRS 为对应的速度阈值。
提 示 : 在 电 机 加 速 期 间 不 要 启 用 ， 等 到 电 机 速 度 超 过 某 个 值 ， 此 时
StallGuard2 会提供稳定的结果。对应的速度阈值为 TCOOLTHRS。
9 en_latch_encoder 1: 参考开关事件有效时将编码器位置锁定到 ENC _ LATCH。
8 latch_r_inactive 1:.当右侧参考开关输入 REFR 向非有效电平跳变时，位置锁存至 XLATCH。
有效电平由 pol_stop_r 定义。
7 latch_r_active 1:当右侧参考开关输入 REFR 向有效电平跳变时，位置锁存至 XLATCH。
提示:激活 latch _ r _ active，通过读 status_latch_r 来检测任何虚假停止事
件。
6 latch_l_inactive 1: 当左侧参考开关输入 REFL 向非有效电平跳变时，位置锁存至 XLATCH。
有效电平由 pol _ stop _ l 定义.
5 latch_l_active 1：当左侧参考开关输入 REFL 向有效电平跳变时，位置锁存至 XLATCH。
提示:激活 latch_l_active，通过读 status_latch_l 来检测任何虚假的停止事
件。
4 swap_lr 1: 交换左右参考开关输入 REFL 和 REFR
3 pol_stop_r 设置右参考开关输入的有效极性 。
0 =非反转，高有效: REFR 上的高电平会停止电机 。
