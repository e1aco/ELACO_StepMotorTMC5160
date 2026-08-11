# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p64

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
64
www.trinamic.com
5.4.1 ENCMODE – 编码器寄存器
0X38: ENCMODE –编码器寄存器
位
名称
备注
10
enc_sel_decimal
0
编码器预分频器二进制模式:
ENC _ CONST (小数部分) / 65536
1
编码器预分频器十进制模式:
ENC _ CONST (小数部分) / 10000
9
latch_x_act
1: 与X_ENC 一起锁定XACTUAL。
根据N 通道事件的pos_edge 和neg_edge 配置锁定斜坡发生器位置。
8
clr_enc_x
0
当发生N 事件时，X_ENC 仅锁存到ENC_LATCH
1
N 事件时锁存并清除编码器计数器X_ENC
7
neg_edge
n p
N 通道的敏感度
6
pos_edge
0 0
N 通道的有效电平触发N 通道事件
0 1
向有效电平的跳变触发N 事件有效
1 0
向非有效电平的跳变触发N 通道有效
1 1
向有效电平及非有效电平的跳变触发N 通道有效
5
clr_once
1:写访问后的下一个N 事件中，锁存或锁存并清除X_ENC
4
clr_cont
1: N 事件时，始终锁存或锁存并清除X_ENC (每转一圈一次，建议将此设置
与N 事件的边缘设置相结合)
3
ignore_AB
0
只有当极性与pol_N、pol_A 和pol_B 定义的极性匹配，N 事件发生。
1
忽略N 通道事件的A 和B 极性
2
pol_N
定义N 通道的有效极性( 0 =低有效，1 =高有效)
1
pol_B
N 通道事件所需的B 极性( 0 = 负，1 = 正)
0
pol_A
N 通道事件所需的A 极性( 0 = 负，1 = 正)


<!-- detected tables -->

| 0X38: ENCMODE –编码器寄存器 |  |  |  |
|---|---|---|---|
| 位 | 名称 | 备注 |  |
| 10 | enc sel decimal _ _ | 0 | 编码器预分频器二进制模式: ENC CONST (小数部分) / 65536 _ |
|  |  | 1 | 编码器预分频器十进制模式: ENC CONST (小数部分) / 10000 _ |
| 9 | latch x act _ _ | 1: 与X ENC 一起锁定XACTUAL。 _ 根据N 通道事件的pos edge 和neg edge 配置锁定斜坡发生器位置。 _ _ |  |
| 8 | clr enc x _ _ | 0 | 当发生N 事件时，X ENC 仅锁存到ENC LATCH _ _ |
|  |  | 1 | N 事件时锁存并清除编码器计数器X ENC _ |
| 7 | neg edge _ | n p | N 通道的敏感度 |
| 6 | pos edge _ | 0 0 | N 通道的有效电平触发N 通道事件 |
|  |  | 0 1 | 向有效电平的跳变触发N 事件有效 |
|  |  | 1 0 | 向非有效电平的跳变触发N 通道有效 |
|  |  | 1 1 | 向有效电平及非有效电平的跳变触发N 通道有效 |
| 5 | clr once _ | 1:写访问后的下一个N 事件中，锁存或锁存并清除X ENC _ |  |
| 4 | clr cont _ | 1: N 事件时，始终锁存或锁存并清除X ENC (每转一圈一次，建议将此设置 _ 与N 事件的边缘设置相结合) |  |
| 3 | ignore AB _ | 0 | 只有当极性与pol N、pol A 和pol B 定义的极性匹配，N 事件发生。 _ _ _ |
|  |  | 1 | 忽略N 通道事件的A 和B 极性 |
| 2 | pol N _ | 定义N 通道的有效极性( 0 =低有效，1 =高有效) |  |
| 1 | pol B _ | N 通道事件所需的B 极性( 0 = 负，1 = 正) |  |
| 0 | pol A _ | N 通道事件所需的A 极性( 0 = 负，1 = 正) |  |
