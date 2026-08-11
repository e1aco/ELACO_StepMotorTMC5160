# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p75

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
75
www.trinamic.com
5.5.3 COOLCONF –智能电流控制CoolStep 和StallGuard2
0X6D: COOLCONF –智能电流控制COOLSTEP 和STALLGUARD2
位
名称
功能
备注
…
-
保留
设置0
24
sfilt
StallGuard2 滤波器使能
0
标准模式，StallGuard2 的高时间分辨率
1
滤波模式，StallGuard2 信号每四个全步更新一次(三
相电机的六个全步)仅用于补偿电机级与级之间不一
致
23
-
保留
设置0
22
sgt6
StallGuard2 阈值
该值控制堵转输出的StallGuard2 电平，并设置读出的最
佳测量范围。值越低，灵敏度越高。零是大多数电机的启
动值。
-64 to +63:
较高的值会降低StallGuard2 的敏感度，并需
要更多扭矩来指示堵转。
21
sgt5
20
sgt4
19
sgt3
18
sgt2
17
sgt1
16
sgt0


<!-- detected tables -->

| 0X6D: COOLCONF –智能电流控制COOLSTEP 和STALLGUARD2 |  |  |  |  |
|---|---|---|---|---|
| 位 | 名称 | 功能 | 备注 |  |
| … | - | 保留 | 设置0 |  |
| 24 | sfilt | StallGuard2 滤波器使能 | 0 | 标准模式，StallGuard2 的高时间分辨率 |
|  |  |  | 1 | 滤波模式，StallGuard2 信号每四个全步更新一次(三 相电机的六个全步)仅用于补偿电机级与级之间不一 致 |
| 23 | - | 保留 | 设置0 |  |
| 22 | sgt6 | StallGuard2 阈值 | 该值控制堵转输出的StallGuard2 电平，并设置读出的最 佳测量范围。值越低，灵敏度越高。零是大多数电机的启 动值。 -64 to +63: 较高的值会降低StallGuard2 的敏感度，并需 要更多扭矩来指示堵转。 |  |
| 21 | sgt5 |  |  |  |
| 20 | sgt4 |  |  |  |
| 19 | sgt3 |  |  |  |
| 18 | sgt2 |  |  |  |
| 17 | sgt1 |  |  |  |
| 16 | sgt0 |  |  |  |
