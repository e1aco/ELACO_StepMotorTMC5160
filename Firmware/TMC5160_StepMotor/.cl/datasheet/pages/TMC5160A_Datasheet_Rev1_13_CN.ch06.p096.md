# TMC5160A_Datasheet_Rev1_13_CN — 第6章 · p96

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
96
www.trinamic.com
PWM_GRAD
_AUTO
PWM_OFS
_AUTO
参数自调整阶段PWM_OFS 和PWM_GRAD 的返回
值，或者是PWM_OFS 和PWM_GRAD 初始值的确定
0 … 255
(只读)
TOFF
电机驱动器使能，实际值不影响StealthChop 性能
0
驱动器输出禁止
1 … 15
驱动器输出使能
TBL
比较器消隐时间。该时间应大于功率管开关事件和
采样电阻上振铃的持续时间。典型应用一般设置1
或2。对于较高的电容性负载，可能需要3。较低
的设置允许StealthChop 调节到较低的线圈电流值。
0
16 tCLK
1
24 tCLK
2
36 tCLK
3
54
CLK


<!-- detected tables -->

| PWM GRAD _ AUTO _ PWM OFS _ AUTO _ | 参数自调整阶段 PWM OFS 和 PWM GRAD 的返回 _ _ 值，或者是PWM OFS 和PWM GRAD 初始值的确定 _ _ | 0 … 255 | (只读) |
|---|---|---|---|
| TOFF | 电机驱动器使能，实际值不影响StealthChop 性能 | 0 | 驱动器输出禁止 |
|  |  | 1 … 15 | 驱动器输出使能 |
| TBL | 比较器消隐时间。该时间应大于功率管开关事件和 采样电阻上振铃的持续时间。典型应用一般设置1 或 2。对于较高的电容性负载，可能需要 3。较低 的设置允许StealthChop 调节到较低的线圈电流值。 | 0 | 16 t CLK |
|  |  | 1 | 24 t CLK |
|  |  | 2 | 36 t CLK |
|  |  | 3 | 54 CLK |
