# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p66

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
66
www.trinamic.com
微步控制寄存器(0X60…0X6B)
R/W
地址
n
寄存器
描述/位名称
范围[单位]
R
0x6B
9
+
9
MSCURACT
bit 8… 0:
CUR_A (有符号):
MSLUT 中电机A 相的实际微步电流(未
按电流缩放)
bit 24… 16:
CUR_B (有符号):
MSLUT 中电机B 相的实际微步电流(未
按电流缩放)
+/-0...255


<!-- detected tables -->

| 微步控制寄存器(0X60…0X6B) |  |  |  |  |  |
|---|---|---|---|---|---|
| R/W | 地址 | n | 寄存器 | 描述/位名称 | 范围[单位] |
| R | 0x6B | 9 + 9 | MSCURACT | bit 8… 0: CUR A (有符号): _ MSLUT 中电机A 相的实际微步电流(未 按电流缩放) bit 24… 16: CUR B (有符号): _ MSLUT 中电机B 相的实际微步电流(未 按电流缩放) | +/-0...255 |
