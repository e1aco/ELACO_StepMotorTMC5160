# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p48

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
48
www.trinamic.com
5.1. 1 OTP_READ – OTP 配置存储器
OTP 存储器保存某些寄存器的加电默认值。默认情况下，所有OTP 内存位都清零。只能编程这
些位，不可清除。otp0.0 到otp0.4 为时钟出厂频率调整值，因此，这些位的状态在各个芯片之间可能会
有所不同
0X07: OTP_READ – OTP 存储器映射
位
名称
功能
备注
7
otp0.7
otp_TBL
TBL 复位缺省值:
0: TBL=%10 (~3µs)
1: TBL=%01 (~2µs)
6
otp0.6
otp_BBM
DRVCONF.BBMCLKS 复位缺省值
0: BBMCLKS=4
1: BBMCLKS=2
5
otp0.5
otp_S2_LEVEL
短路检测电平复位缺省值:
0: S2G_LEVEL = S2VS_LEVEL = 6
1: S2G_LEVEL = S2VS_LEVEL = 12
4
otp0.4
OTP_FCLKTRIM
FCLKTRIM 复位缺省值
0: 最低频率设置
31: 最高频率设置
注意:该值是出厂设置，预编程为默认时钟频率12MHz，
并且在各个芯片之间有所不同！它不能被改变。
3
otp0.3
2
otp0.2
1
otp0.1
0
otp0.0


<!-- detected tables -->

| 0X07: OTP READ – OTP 存储器映射 _ |  |  |  |
|---|---|---|---|
| 位 | 名称 | 功能 | 备注 |
| 7 | otp0.7 | otp TBL _ | TBL 复位缺省值: 0: TBL=%10 (~3µs) 1: TBL=%01 (~2µs) |
| 6 | otp0.6 | otp BBM _ | DRVCONF.BBMCLKS 复位缺省值 0: BBMCLKS=4 1: BBMCLKS=2 |
| 5 | otp0.5 | otp S2 LEVEL _ _ | 短路检测电平复位缺省值: 0: S2G LEVEL = S2VS LEVEL = 6 _ _ 1: S2G LEVEL = S2VS LEVEL = 12 _ _ |
| 4 | otp0.4 | OTP FCLKTRIM _ | FCLKTRIM 复位缺省值 0: 最低频率设置 31: 最高频率设置 注意:该值是出厂设置，预编程为默认时钟频率12MHz， 并且在各个芯片之间有所不同！它不能被改变。 |
| 3 | otp0.3 |  |  |
| 2 | otp0.2 |  |  |
| 1 | otp0.1 |  |  |
| 0 | otp0.0 |  |  |
