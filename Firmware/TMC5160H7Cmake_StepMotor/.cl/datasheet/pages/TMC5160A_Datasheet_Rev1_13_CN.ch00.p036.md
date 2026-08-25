# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p36

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 36
www.trinamic.com
4.3 时序
SPI 接口单元与内部系统时钟同步，最高 SPI 时钟 SCK 为系统时钟频率的一半。如果系统时钟基于片
上振荡器，则必须使用额外的 10 %安全裕度来确保可靠的数据传输。所有 SPI 输入以及 ENN 输入都经过
内部滤波，以避免被短于 20ns 的脉冲触发。图 4.1 显示了 SPI 总线传送的时序参数，下表为对应的电气
参数。
图 4.1 SPI 时序
提示
通常 TMC5160 SPI 时序指的是 SPI 模式 3
SPI 接口时序 交流特性
时钟周期: tCLK
参数 符号 条件 最小值 典型值 最大值 单位
SCK 在 CSN 变化前或变化后有效
时间 tCC 10 ns
CSN 高电平时间 tCSH
* )最小时间仅用于
同步 CLK，在 CSN
高电平前 SCK 至少
保持一个 tCH 高电平
时间
tCLK*) >2tCLK+10 ns
SCK 低电平时间 tCL
* ) 最小时间仅用于
同步时钟 tCLK*) >tCLK+10 ns
SCK 高电平时间 tCH
* ) 最小时间仅用于
同步时钟 tCLK*) >tCLK+10 ns
内部时钟的 SCK 频率 fSCK 假设最小振荡频率 4 MHz
外部 16M 时钟的 SCK 频率 fSCK 假设为同步时钟 8 MHz
