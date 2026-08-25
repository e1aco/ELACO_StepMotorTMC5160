# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p65

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 65
www.trinamic.com
5.5 电机驱动寄存器
微步控制寄存器(0X60…0X6B)
R/W 地址 n 寄存器 描述/位名称 范围[单位]
W 0x60 32
MSLUT[0]
微步表入口
0…31
根据 MSLUTSEL W 的设置，条目 x 和条目 x + 1 之间
的差值:
0: W= %00: -1
%01: +0
%10: +1
%11: +2
1: W= %00: +0
%01: +1
%10: +2
%11: +3
这 是 第 一 个 四 分 之 一 波 的 差 分 编 码 。 CUR_A 和
CUR_B 的 起 始 值 存 储 在 START_SIN 和
START_SIN90 中的 MSCNT 位置 0。
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
W 0x68 32 MSLUTSEL
该寄存器定义了 MSLUT 正弦波 1/4 周期内的四个
段。四个 2 位条目确定了 MSLUT 表中对应段的位
宽。
参见单独的表！
0<X1<X2<X3
复位缺省值= 正
弦表
W 0x69
8
+
8
MSLUTSTART
7… 0 位: START_SIN
b23… 16 位: START_SIN90
START _ SIN 给出了微步表位置 0 的绝对电流。
START _ SIN90 给出了微步表位置 256 的绝对电流。
当参考位置 MSCNT = 0 时，起始值赋给微步寄存器
CUR_A 和 CUR _ B。
START_SIN
复位缺省值 =0
START_SIN90
复位缺省值=247
R 0x6A 10 MSCNT
微步计数器。指示 CUR _ A 微步表中的实际位置。
CUR _ B 的偏移量为 256 (两相电机)。
提示:先将电机移动到 MSCT 为零的位置，再重新初
始化 MSLUTSTART 或 MSLUT 和 MSLUTSEL。
0…1023
