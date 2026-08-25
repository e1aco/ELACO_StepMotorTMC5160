# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p170

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 170
www.trinamic.com
线性调节器 直流特性
VVS = VVSA = 24.0V
参数 符号 条件 最小值 典型值 最大值 单位
输出电压 V5VOUT TJ = 25°C 4.80 5.0 5.20 V
整个温度范围内的输出电压偏差 V5VOUT(DEV) 驱动器关闭
TJ = 全温度范围
+/-30 +/-100 mV
整个电源电压范围内的输出电压
偏差
V5VOUT(DEV) 驱动器关闭，
内部时钟
TA = 25°C
VVSA = 10V to 30V
+/-50 mV /
10V
输出电压 V12VOUT operating, internal
clock
TJ = 25°C
10.8 11.5 12.2 V
时钟振荡器和输入 时序特征
参数 符号 条件 最小值 典型值 最大值 单位
时钟振荡器频率 (工厂校准) fCLKOSC tJ=-50°C 11.7 MHz
fCLKOSC tJ=50°C 11.5 12.0 12.5 MHz
fCLKOSC tJ=150°C 12.1 MHz
外部时钟频率(工作) fCLK 4 10-16 18 MHz
外部时钟高/低电平时间 tCLKH /
tCLKL
CLK 为
0.1 VVIO / 0.9 VVIO
16 ns
触发切换到外部 CLK 的外部时钟
第一个脉冲
tCLKH /
tCLKL
CLK 高，A 版本 16 ns
触发切换到外部 CLK 的外部时钟
第一个脉冲
tCLKH /
tCLKL
CLK 高，非 A 版本 30 25 ns
外部时钟超时检测，按内部 fCLKOSC
作为计算周期
tCLKH1 CLK 高电平 32 48 cycles
fCLKOSC
