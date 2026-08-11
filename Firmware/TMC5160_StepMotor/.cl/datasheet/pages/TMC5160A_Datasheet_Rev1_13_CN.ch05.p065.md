# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p65

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
65
www.trinamic.com
5.5
电机驱动寄存器
微步控制寄存器(0X60…0X6B)
R/W
地址
n
寄存器
描述/位名称
范围[单位]
W
0x60
32
MSLUT[0]
微步表入口
0…31
根据MSLUTSEL W 的设置，条目x 和条目x + 1 之间
的差值:
0: W=
%00: -1
%01: +0
%10: +1
%11: +2
1: W=
%00: +0
%01: +1
%10: +2
%11: +3
这是第一个四分之一波的差分编码。CUR_A 和
CUR_B
的起始值存储在START_SIN
和
START_SIN90 中的MSCNT 位置0。
ofs31, ofs30, …, ofs01, ofs00
…
ofs255, ofs254, …, ofs225, ofs224
32x 0 or 1
复位缺省= 正弦
表
W
0x61
…
0x67
7
x
32
MSLUT[1...7]
microstep
table entries
32…255
7x
32x 0 or 1
复位缺省= 正弦
表
W
0x68
32
MSLUTSEL
该寄存器定义了MSLUT 正弦波1/4 周期内的四个
段。四个2 位条目确定了MSLUT 表中对应段的位
宽。
参见单独的表！
0<X1<X2<X3
复位缺省值= 正
弦表
W
0x69
8
+
8
MSLUTSTART
7… 0 位: START_SIN
b23… 16 位: START_SIN90
START _ SIN 给出了微步表位置0 的绝对电流。
START _ SIN90 给出了微步表位置256 的绝对电流。
当参考位置MSCNT = 0 时，起始值赋给微步寄存器
CUR_A 和CUR _ B。
START_SIN
复位缺省值=0
START_SIN90
复位缺省值=247
R
0x6A
10
MSCNT
微步计数器。指示CUR _ A 微步表中的实际位置。
CUR _ B 的偏移量为256 (两相电机)。
提示:先将电机移动到MSCT 为零的位置，再重新初
始化MSLUTSTART 或MSLUT 和MSLUTSEL。
0…1023


<!-- detected tables -->

| 微步控制寄存器(0X60…0X6B) |  |  |  |  |  |
|---|---|---|---|---|---|
| R/W | 地址 | n | 寄存器 | 描述/位名称 | 范围[单位] |
| W | 0x60 | 32 | MSLUT[0] 微步表入口 0…31 | 根据MSLUTSEL W 的设置，条目x 和条目x + 1 之间 的差值: 0: W= %00: -1 %01: +0 %10: +1 %11: +2 1: W= %00: +0 %01: +1 %10: +2 %11: +3 这是第一个四分之一波的差分编码。CUR A 和 _ CUR B 的 起 始 值 存 储 在 START SIN 和 _ _ START SIN90 中的MSCNT 位置0。 _ ofs31, ofs30, …, ofs01, ofs00 … ofs255, ofs254, …, ofs225, ofs224 | 32x 0 or 1 复位缺省= 正弦 表 |
| W | 0x61 … 0x67 | 7 x 32 | MSLUT[1...7] microstep table entries 32…255 |  | 7x 32x 0 or 1 复位缺省= 正弦 表 |
| W | 0x68 | 32 | MSLUTSEL | 该寄存器定义了MSLUT 正弦波1/4 周期内的四个 段。四个2 位条目确定了MSLUT 表中对应段的位 宽。 参见单独的表！ | 0<X1<X2<X3 复位缺省值= 正 弦表 |
| W | 0x69 | 8 + 8 | MSLUTSTART | 7… 0 位: START SIN _ b23… 16 位: START SIN90 _ START SIN 给出了微步表位置0 的绝对电流。 _ START SIN90 给出了微步表位置256 的绝对电流。 _ 当参考位置MSCNT = 0 时，起始值赋给微步寄存器 CUR A 和CUR B。 _ _ | START SIN _ 复位缺省值=0 START SIN90 _ 复位缺省值=247 |
| R | 0x6A | 10 | MSCNT | 微步计数器。指示CUR A 微步表中的实际位置。 _ CUR B 的偏移量为256 (两相电机)。 _ 提示:先将电机移动到MSCT 为零的位置，再重新初 始化MSLUTSTART 或MSLUT 和MSLUTSEL。 | 0…1023 |
