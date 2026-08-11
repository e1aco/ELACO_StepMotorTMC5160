# TMC5160A_Datasheet_Rev1_13_CN — 第13章 COOLSTEP 操作

--- [PAGE 128] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
128
www.trinamic.com
13. CoolStep 操作
CoolStep 是一种基于电机机械负载的步进电机智能调节能耗，使其“绿色”
13.1 对用户的好处
CoolStep 实现节能，特别是对于负载变化或工作在高占空比的电机应用。即使是恒负载应用也需要
节能，因为步进电机应用需要保留30 %至50 %的扭矩工作。CoolStep 在工作是根据负载需要自动保留
扭矩。降低功耗使系统保持较冷，延长电机寿命，并降低电源和冷却部件的成本
将电机电流减小一半则功率减小4 倍
13.2 CoolStep 设置
CoolStep 由几个参数控制，但两个参数对于理解它的工作方式至关重要:
参数
描述
范围
备注
SEMIN
阈值下限。4 位无符号整数。如果SG 低于此阈值，
CoolStep 会增加两个线圈的电流。4 位SEMIN 乘以
32，对应10 位SG 值范围的下半部分。(此参数的名
称来自smarterEnergy ，它是CoolStep 的早期名
称。)
0
禁用CoolStep
1…15
阈值为SEMIN*32
SEMAX
阈值上限，4 位无符号整数。如果SG 采样值等于或
高于该阈值，CoolStep 将降低到两个线圈的电流。
上限为( SEMIN + SEMAX + 1 ) * 32
0…15
阈值为
(SEMIN+SEMAX+1)*32
图13.1 显示了CoolStep 的操作区域:
-
黑线代表SG 测量值。
-
蓝线表示电机上的机械负载。
能效
–
减少最多75%的能耗
电机发热减少
–
提高机械精度
减少冷却机构
–
电机和驱动器
更便宜的电机
–
完成工作！


<!-- detected tables -->

| 参数 | 描述 | 范围 | 备注 |
|---|---|---|---|
| SEMIN | 阈值下限。4 位无符号整数。如果SG 低于此阈值， CoolStep 会增加两个线圈的电流。4 位SEMIN 乘以 32，对应10 位SG 值范围的下半部分。(此参数的名 称来自 smarterEnergy ，它是 CoolStep 的早期名 称。) | 0 | 禁用CoolStep |
|  |  | 1…15 | 阈值为SEMIN*32 |
| SEMAX | 阈值上限，4 位无符号整数。如果SG 采样值等于或 高于该阈值，CoolStep 将降低到两个线圈的电流。 上限为( SEMIN + SEMAX + 1 ) * 32 | 0…15 | 阈值为 (SEMIN+SEMAX+1)*32 |
--- [PAGE 129] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
129
www.trinamic.com
-
红线表示电机线圈的电流
当负载增加时，SG_RESULT 下降到SEMIN 以下，CoolStep 增加电流。当负载减小时，SG_RESULT 上
升到(SEMIN + SEMAX + 1 ) * 32 以上，电流减小。
图13.1 CoolStep 根据负载调节电机电流
CoolStep 的五个控制参数和一个状态返回参数:
参数
描述
范围
备注


<!-- detected tables -->

| 参数 | 描述 | 范围 | 备注 |
|---|---|---|---|
--- [PAGE 130] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
130
www.trinamic.com
SEUP
设置电流增加步长。测量到的stallguard 2 值低于下
阈值，电流增加
0…3
步长宽度为
1, 2, 4, 8
SEDN
每次线圈电流减少时，StallGuard2 值必须等于或高
于上限阈值对应的数值
0…3
StallGuard 递减数:
32, 8, 2, 1
SEIMIN
通过调整IRUN 电流设置，设置CoolStep 操作的电
机电流下限。
0
0: IRUN 的1/2
1
1: IRUN 的1/4
TCOOL
THRS
打开CoolStep 和堵转停止功能的较低速度阈值。低
于此速度，CoolStep 将被禁用(不用于STEP / DIR 模
式)。满足速度下限条件的StallGuard2 能给出稳定
的结果。
提示:可设置和VMAX 一样，则在加速和减速阶段禁
用CoolStep。
1…
2^20-1
指定与TSTEP 速度比较的
CoolStep 阈值下限
THIGH
CoolStep 和堵转停的速度阈值上限。在此速度之
上，CoolStep 变为禁用状态。根据StallGuard2 结果
的稳定性给出速度范围。
1…
2^20-1
同时也控制其它功能，如
切换成全步
状态字
描述
范围
备注
CSACTUAL
该状态值提供由CoolStep 控制的实际电机电流标
度。该值范围为IRUN 值到SEIMIN 设定IRUN 比例
（1/2,1/4）。
0…31
1/32, 2/32, … 32/32


<!-- detected tables -->

| SEUP | 设置电流增加步长。测量到的stallguard 2 值低于下 阈值，电流增加 | 0…3 | 步长宽度为 1, 2, 4, 8 |
|---|---|---|---|
| SEDN | 每次线圈电流减少时，StallGuard2 值必须等于或高 于上限阈值对应的数值 | 0…3 | StallGuard 递减数: 32, 8, 2, 1 |
| SEIMIN | 通过调整 IRUN 电流设置，设置 CoolStep 操作的电 机电流下限。 | 0 | 0: IRUN 的1/2 |
|  |  | 1 | 1: IRUN 的1/4 |
| TCOOL THRS | 打开CoolStep 和堵转停止功能的较低速度阈值。低 于此速度，CoolStep 将被禁用(不用于STEP / DIR 模 式)。满足速度下限条件的 StallGuard2 能给出稳定 的结果。 提示:可设置和VMAX 一样，则在加速和减速阶段禁 用CoolStep。 | 1… 2^20-1 | 指定与TSTEP 速度比较的 CoolStep 阈值下限 |
| THIGH | CoolStep 和堵转停的速度阈值上限。在此速度之 上，CoolStep 变为禁用状态。根据StallGuard2 结果 的稳定性给出速度范围。 | 1… 2^20-1 | 同时也控制其它功能，如 切换成全步 |
| 状态字 | 描述 | 范围 | 备注 |
| CSACTUAL | 该状态值提供由 CoolStep 控制的实际电机电流标 度。该值范围为 IRUN 值到 SEIMIN 设定 IRUN 比例 （1/2,1/4）。 | 0…31 | 1/32, 2/32, … 32/32 |
--- [PAGE 131] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
131
www.trinamic.com
13.3 调节CoolStep
在调整CoolStep 之前，首先调整StallGuard2 阈值水平SGT，这会影响负载测量值SG_RESULT 的范
围。CoolStep 根据SG_RESULT 在+ 90°的最佳负载角附近运行电机。
电流增量速度在SEUP 中设定，电流减量速度在SEDN 中指定。它们可以单独调整，因为它们有可
能根据不同事件触发的做出不同响应需要。这些参数的设置允许线圈电流的增加比减少快得多，因为可
能是需要更快响应更严重的事件，如果响应太慢，电机可能堵转。相比之下，超过上限的反应缓慢并没
有太多风险，只是电机延时减少能量。
CoolStep 在当前标度参数IRUN 和seimin 位控制的电流范围之间运行，输出相应的电流。
13.3.1 响应时间
为了快速响应增加的电机负载，使用大的电流增量步长SEUP。如果电机负载变化缓慢，可以使用
较低的电流增量步长来避免电机振荡。如果使能sfilt 控制的滤波器，测量速率和调节速度将降低4 倍。
提示
最常见和最有益的用途是使CoolStep 适应系统在目标速度的运行，并根据此设置速度阈值。由于加
速和减速通常应该是快速的，该过程中需要全电机电流，但因持续时间短，所以对总功耗的影响很小。
13.3.2 低速和静止操作
由于CoolStep 无法测量静止和非常低速下的电机负载，斜坡发生器中要设置CoolStep 的速度阈值。
应根据应用设置。低于此阈值时，电流设置由IRUN 和IHOLD 确定。VHIGH 设置提供了阈值上限。可以
设置两个阈值作为Stallguard 2 调整过程。

