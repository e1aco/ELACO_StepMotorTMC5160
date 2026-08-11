# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p63

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
63
www.trinamic.com
R/W
地址
n
寄存器
描述/ 位名称
范围[单位]
RW
0x38
11
ENCMODE
编码器和N 通道配置
请另见表格！
RW
0x39
32
X_ENC
实际编码器位置(有符号)
-2^31…
+(2^31)-1
W
0x3A
32
ENC_CONST
编码器累加常数(有符号)
16 位整数部分，16 位小数部分
X_ENC 累加
+ / - ENC _ CONST / ( 2^ 16 * X _ ENC ) (二进制)
或者
+ / - ENC _ CONST / ( 10 ^ 4 * X _ ENC ) (十进制)
ENCMODE 的enc_sel_decima 位选择十进制和
二进制设置
符号匹配旋转方向！
二进制:
± [µsteps/2^16]
±(0 …
32767.999847)
十进制:
±(0.0 …
32767.9999)
reset default = 1.0
(=65536)
R+
WC
0x3B
2
ENC_STATUS
编码器状态信息
位0 : n_event
位1 : deviation_warn
1 :检测到事件。
要清除状态位，请在相应位置写入1 位。
报警只要存在，则无法清除Deviation_warn。
ENC_DEVIATION 设置为零代表关闭该功能。
两个位都与中断输出信号进行或运算。
R
0x3C
32
ENC_LATCH
N 事件时锁存编码器位置X_ENC
W
0x3D
20
ENC_
DEVIATION
编码器计数器和XACTUAL 之间的最大步长偏
差，用于产生偏差报警，对应的标志
ENC_STATUS.deviation_warn 有效。
0 =功能关闭。


<!-- detected tables -->

| R/W | 地址 | n | 寄存器 | 描述/ 位名称 | 范围[单位] |
|---|---|---|---|---|---|
| RW | 0x38 | 11 | ENCMODE | 编码器和N 通道配置 请另见表格！ |  |
| RW | 0x39 | 32 | X ENC _ | 实际编码器位置(有符号) | -2^31… +(2^31)-1 |
| W | 0x3A | 32 | ENC CONST _ | 编码器累加常数(有符号) 16 位整数部分，16 位小数部分 X ENC 累加 _ + / - ENC CONST / ( 2^ 16 * X ENC ) (二进制) _ _ 或者 + / - ENC CONST / ( 10 ^ 4 * X ENC ) (十进制) _ _ ENCMODE 的enc sel decima 位选择十进制和 _ _ 二进制设置 符号匹配旋转方向！ | 二进制: ± [µsteps/2^16] ±(0 … 32767.999847) 十进制: ±(0.0 … 32767.9999) reset default = 1.0 (=65536) |
| R+ WC | 0x3B | 2 | ENC STATUS _ | 编码器状态信息 位0 : n event _ 位1 : deviation warn _ 1 :检测到事件。 要清除状态位，请在相应位置写入1 位。 报警只要存在，则无法清除Deviation warn。 _ ENC DEVIATION 设置为零代表关闭该功能。 _ 两个位都与中断输出信号进行或运算。 |  |
| R | 0x3C | 32 | ENC LATCH _ | N 事件时锁存编码器位置X ENC _ |  |
| W | 0x3D | 20 | ENC _ DEVIATION | 编码器计数器和XACTUAL 之间的最大步长偏 差，用于产生偏差报警，对应的标志 ENC STATUS.deviation warn 有效。 _ _ 0 =功能关闭。 |  |
