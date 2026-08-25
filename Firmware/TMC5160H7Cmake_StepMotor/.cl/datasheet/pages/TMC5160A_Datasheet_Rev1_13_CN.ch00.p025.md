# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p25

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 25
www.trinamic.com
驱动器需根据 MOSFET 参数配置 以下 DRV _ CONF 参数:
参数 描述 设置 备注
BBMTIME 死区时间，确保同一桥臂的高端和低端 MOSFET 不
会直通 。BBMTIME 是更高频率的调节死区时间设
置，允许比时钟周期更快的调节时间。
需要更长的时间，选择 BBMCLKS。
0…24 时间[ns]
100ns*32/(32-BBMTIME)
确保~30% headroom
复位缺省: 0
BBMCLKS BBMTIME 类似功能，也是死区时间设置，以多个时
钟周期为单位。
设置 较长的 死区时间 ( BBMTIME 与 BBMCLKS 的区
别 )。
0…15 0: 关闭
复位缺省: OTP 4 or 2
DRV_
STRENGTH
栅极驱动电流的选择。根据外部 MOSFET 的栅极电
荷设置栅极驱动电流。
0…3 复位缺省 = 2
FILT_ISENSE 采样电阻运放的滤波时间常数，以补偿另一个线圈
操作的振铃和耦合
提示:如果两个线圈交叉耦合产生电机斩波器噪声，
则增加设置。 (重置默认值= % 00 )
0…3 00: ~100ns (复位缺省)
01: ~200ns
10: ~300ns
11: ~400ns
DRV_CONF 参数
在增加栅极串联电阻值之前，将 DRVSTRENGTH 栅极驱动强度设置最低会给出有利的开关斜率。
40ns 到 80ns 的斜率时间是绝对足够的，通常最短的死区时间设置( BBMTIME = 0，BBMCLKS = 0 )会大于
这个时间。
如果大的 MOSFET 需要较慢的斜率，要确保死区时间( BBMTIME，200ns 以上时间可用 BBMCLKS)
充分覆盖开关事件，以避免桥臂直通短路。最短的 BBM 时间大于安全切换，效果最佳。控制大约 30 %
的余量，以弥补 MOSFET 和驱动器的生产批次造成的不一致性。
