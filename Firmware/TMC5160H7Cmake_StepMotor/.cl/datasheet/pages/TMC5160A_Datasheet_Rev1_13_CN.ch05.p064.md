# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p64

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 64
www.trinamic.com
5.4.1 ENCMODE – 编码器寄存器
0X38: ENCMODE –编码器寄存器
位 名称 备注
10 enc_sel_decimal 0 编码器预分频器二进制模式:
ENC _ CONST (小数部分) / 65536
1 编码器预分频器十进制模式:
ENC _ CONST (小数部分) / 10000
9 latch_x_act 1: 与 X_ENC 一起锁定 XACTUAL。
根据 N 通道事件的 pos_edge 和 neg_edge 配置锁定斜坡发生器位置。
8 clr_enc_x 0 当发生 N 事件时，X_ENC 仅锁存到 ENC_LATCH
1 N 事件时锁存并清除编码器计数器 X_ENC
7 neg_edge n p N 通道的敏感度
6 pos_edge 0 0 N 通道的有效电平触发 N 通道事件
0 1 向有效电平的跳变触发 N 事件有效
1 0 向非有效电平的跳变触发 N 通道有效
1 1 向有效电平及非有效电平的跳变触发 N 通道有效
5 clr_once 1:写访问后的下一个 N 事件中，锁存或锁存并清除 X_ENC
4 clr_cont 1: N 事件时，始终锁存或锁存并清除 X_ENC (每转一圈一次，建议将此设置
与 N 事件的边缘设置相结合)
3 ignore_AB 0 只有当极性与 pol_N、pol_A 和 pol_B 定义的极性匹配，N 事件发生。
1 忽略 N 通道事件的 A 和 B 极性
2 pol_N 定义 N 通道的有效极性( 0 =低有效，1 =高有效)
1 pol_B N 通道事件所需的 B 极性( 0 = 负，1 = 正)
0 pol_A N 通道事件所需的 A 极性( 0 = 负，1 = 正)
