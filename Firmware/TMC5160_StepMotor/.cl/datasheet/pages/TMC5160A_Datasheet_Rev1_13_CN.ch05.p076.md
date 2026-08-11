# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p76

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
76
www.trinamic.com
15
seimin
智能电流控制的最小电
流
0: 1/2 电流设置(IRUN)
1: 1/4 电流设置(IRUN)
14
sedn1
电流下降速率
%00: StallGuard2 值每增加32，电流减少1
%01: StallGuard2 值每增加8，电流减少1
%10: StallGuard2 值增加2，电流减少1
%11: StallGuard2 值增加1，电流减少1
13
sedn0
12
-
保留
设置0
11
semax3
智能电流控制的
StallGuard2 磁滞值
如果StallGuard2 结果等于或高于( SEMIN + SEMAX + 1 ) *
32，则电机电流变小以节省能量。
% 0000…% 1111 : 0…15
10
semax2
9
semax1
8
semax0
7
-
保留
设置0
6
seup1
电流上升步长
每测得的stallguard 2 参数对应的电流增量步长
%00 … %11: 1, 2, 4, 8
5
seup0
4
-
保留
设置0
3
semin3
智能电流控制的最小
stallguard 2 值及智能电
流使能
如果stallguard 2 的结果低于SEMIN * 32，则电机电流会
增加以减小电机负载角。
%0000: 智能电流控制CoolStep 关闭
%0001 … %1111: 1 … 15
2
semin2
1
semin1
0
semin0


<!-- detected tables -->

| 15 | seimin | 智能电流控制的最小电 流 | 0: 1/2 电流设置(IRUN) 1: 1/4 电流设置(IRUN) |
|---|---|---|---|
| 14 | sedn1 | 电流下降速率 | %00: StallGuard2 值每增加32，电流减少1 %01: StallGuard2 值每增加8，电流减少1 %10: StallGuard2 值增加2，电流减少1 %11: StallGuard2 值增加1，电流减少1 |
| 13 | sedn0 |  |  |
| 12 | - | 保留 | 设置0 |
| 11 | semax3 | 智能电流控制的 StallGuard2 磁滞值 | 如果StallGuard2 结果等于或高于( SEMIN + SEMAX + 1 ) * 32，则电机电流变小以节省能量。 % 0000…% 1111 : 0…15 |
| 10 | semax2 |  |  |
| 9 | semax1 |  |  |
| 8 | semax0 |  |  |
| 7 | - | 保留 | 设置0 |
| 6 | seup1 | 电流上升步长 | 每测得的stallguard 2 参数对应的电流增量步长 %00 … %11: 1, 2, 4, 8 |
| 5 | seup0 |  |  |
| 4 | - | 保留 | 设置0 |
| 3 | semin3 | 智能电流控制的最小 stallguard 2 值及智能电 流使能 | 如果stallguard 2 的结果低于SEMIN * 32，则电机电流会 增加以减小电机负载角。 %0000: 智能电流控制CoolStep 关闭 %0001 … %1111: 1 … 15 |
| 2 | semin2 |  |  |
| 1 | semin1 |  |  |
| 0 | semin0 |  |  |
