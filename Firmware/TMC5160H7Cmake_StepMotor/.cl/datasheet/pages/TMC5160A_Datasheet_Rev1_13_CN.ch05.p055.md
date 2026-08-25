# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p55

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 55
www.trinamic.com
5.3.2 斜坡发生器驱动特性控制寄存器组
斜坡发生器驱动特性控制寄存器组 (0X30…0X36)
R/W 地址 n 寄存器 描述/位名称
W 0x33 23 VDCMIN
大于 VDCMIN (无符号)自动切换到 DcStep (仅当使用内部斜坡发
生器有效时，而非 STEP / DIR 模式时——STEP / DIR 模式下，
DcStep 由外部信号 DCEN 启用)
在这种模式下，实际位置由无传感器的电机换向确定，并反馈
给 XACTUAL。如果电机负载很大，VDCMIN 也用作最小速度。激
活堵转停止(sg_stop )以检测失步。
0: 禁用，关闭 DcStep
|VACT| ≥ VDCMIN ≥ 256:
­ 触发与大于 THIGH 相同的动作
­ 切换到自动换向 DcStep 工作方式
提示: 需设置 DCCTRL 参数来操作 DcStep。
(只有位 22…8 用于比较值)
RW 0x34 12
SW_MODE 开关模式配置
请另见表格!
R+
WC
0x35 14
RAMP_STAT 斜坡状态和开关事件状态
请另见表格!
R 0x36 32 XLATCH
斜坡发生器锁存位置，当设置的开关事件条件满足时锁存
XACTUAL(参见 SW_MODE )。
提示:可将编码器位置与 XLATCH 一起锁定到 ENC_LATCH，便于一
致性检查。
速度的时间基准 t: t = 2^24 / fCLK
加速度的时间基准 ta²: ta² = 2^41 / (fCLK)²
