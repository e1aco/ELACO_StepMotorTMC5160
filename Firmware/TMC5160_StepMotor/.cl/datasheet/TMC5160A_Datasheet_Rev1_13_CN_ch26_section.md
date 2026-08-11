# TMC5160A_Datasheet_Rev1_13_CN — 第26章 电气特性

--- [PAGE 167] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
167
www.trinamic.com
5V 调节器连续功耗(VVSA-5V) * I5VOUT
P5VOUT
1
W
12V 调节器输出电流(内部加外部负载)
I12VOUT
20
mA
12V 调节器连续功耗(VVM-12V) * I12VOUT
P12VOUT
0.5
W
结点温度
TJ
-50
150
°C
存储温度
TSTG
-55
150
°C
接口引脚的ESD 保护(人体模型, HBM)
VESDAP
4
kV
操作的ESD 保护(人体模型, HBM)
VESD
1
kV
* )当驱动感应负载时，电源布线的杂散电感将导致电源电压振铃。这种振铃是由驱动器输出的快速切换
斜率与输出驱动器MOSFETs 的反向恢复体二极管产生的。即使很小的迹线电感以及感测电阻器的杂散电
感也可以容易地产生几伏特的振铃，导致暂时的电压过冲。工作在最大电压附近时应考虑这一点
26. 电气特性
26.1 操作范围
参数
符号
最小值
最大值
单位
节点温度
TJ
-40
125
°C
电机及桥臂供电电压
VVS
10
55
V
VSA 供电电压
VVSA
10
50
V
VSA 和12OUT (供内部桥接内部栅极电压调节器)的电源电压
V12VOUT,
VVSA
10
13
V
最低电源电压(规格降低，对GND 短路保护不起作用)，下限
取决于MOSFETs 栅极阈值电压和负载电流
VVS
8
V
VCC_IO 上的输入/输出电源电压
VVIO
3.00
5.25
V


<!-- detected tables -->

| 5V 调节器连续功耗(V -5V) * I VSA 5VOUT | P 5VOUT |  | 1 | W |
|---|---|---|---|---|
| 12V 调节器输出电流(内部加外部负载) | I 12VOUT |  | 20 | mA |
| 12V 调节器连续功耗(V -12V) * I VM 12VOUT | P 12VOUT |  | 0.5 | W |
| 结点温度 | T J | -50 | 150 | °C |
| 存储温度 | T STG | -55 | 150 | °C |
| 接口引脚的ESD 保护(人体模型, HBM) | V ESDAP |  | 4 | kV |
| 操作的ESD 保护(人体模型, HBM) | V ESD |  | 1 | kV |

| 参数 | 符号 | 最小值 | 最大值 | 单位 |
|---|---|---|---|---|
| 节点温度 | T J | -40 | 125 | °C |
| 电机及桥臂供电电压 | V VS | 10 | 55 | V |
| VSA 供电电压 | V VSA | 10 | 50 | V |
| VSA 和12OUT (供内部桥接内部栅极电压调节器)的电源电压 | V , 12VOUT V VSA | 10 | 13 | V |
| 最低电源电压(规格降低，对GND 短路保护不起作用)，下限 取决于MOSFETs 栅极阈值电压和负载电流 | V VS | 8 |  | V |
| VCC IO 上的输入/输出电源电压 _ | V VIO | 3.00 | 5.25 | V |
--- [PAGE 168] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
168
www.trinamic.com
26.2 直流特性和时序
除非另有规定，直流特性包含在指定电源电压范围内保证的范围值。典型值为+ 25℃下测量的平
均值。温度变化也会导致偏离某些值。芯片的典型值在全温度范围内工作在最小/最大范围之间。
供电电流
直流特性
VVS = VVSA = 24.0V
参数
符号
条件
最小值
典型值
最大值
单位
总电源电流，驱动器禁用IVS + IVSA
IS
fCLK=12MHz / 内部时
钟
18
24
mA
VSA 电源电流( VS 和VSA 分开)
IVSA
fCLK=12MHz /内部时
钟, 驱动器禁用
15
mA
总电源电流，工作，MOSFETs
AOD4126, IVS + IVSA
IS
fCLK=12MHz, 23.4kHz
斩波器，无负载
25
mA
VCC 引脚上5V 电源的内部电流消
耗
IVCC
fCLK=12MHz
10
mA
VCC 引脚上5V 电源的内部电流消
耗
IVCC
fCLK=16MHz
12.5
mA
VCC_IO 上的IO 电源电流(典型值
5V )
IVIO
无负载输出，VIO 或
GND 输入
不包括上拉/下拉电
阻
15
30
µA


<!-- detected tables -->

| 供电电流 | 直流特性 V = V = 24.0V VS VSA |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| 总电源电流，驱动器禁用I + I VS VSA | I S | f =12MHz / 内部时 CLK 钟 |  | 18 | 24 | mA |
| VSA 电源电流( VS 和VSA 分开) | I VSA | f =12MHz /内部时 CLK 钟, 驱动器禁用 |  | 15 |  | mA |
| 总电源电流，工作，MOSFETs AOD4126, I + I VS VSA | I S | f =12MHz, 23.4kHz CLK 斩波器，无负载 |  | 25 |  | mA |
| VCC 引脚上5V 电源的内部电流消 耗 | I VCC | f =12MHz CLK |  | 10 |  | mA |
| VCC 引脚上5V 电源的内部电流消 耗 | I VCC | f =16MHz CLK |  | 12.5 |  | mA |
| VCC IO 上的IO 电源电流(典型值 _ 5V ) | I VIO | 无负载输出，VIO 或 GND 输入 不包括上拉/下拉电 阻 |  | 15 | 30 | µA |
--- [PAGE 169] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
169
www.trinamic.com
电机驱动器部分
直流特性和时序
VVS = 24.0V; Tj=50°C
参数
符号
条件
最小值
典型值
最大值
单位
RDSON 低侧驱动器
RONL
栅极关断
1.8
3
Ω
RDSON 高侧驱动器
RONH
栅极关断
2.2
3.5
Ω
低侧MOSFET 在2V VGS 下导通栅
极驱动电流
ISLPON0
DRVSTRENGTH=0
200
mA
ISLPON2
DRVSTRENGTH=2
400
mA
ISLPON3
DRVSTRENGTH=3
600
mA
高侧MOSFET 在2V VGS 下导通栅
极驱动电流
ISLPON0
DRVSTRENGTH=0
150
mA
ISLPON2
DRVSTRENGTH=2
300
mA
ISLPON3
DRVSTRENGTH=3
450
mA
内部延迟的BBM 时间(从栅极关
闭开始到栅极导通)
tBBM0
BBMCLKS=0
BBMTIME=0
75
100
ns
tBBM16
BBMTIME=16
200
ns
tBBM16
BBMTIME=24
375
500
ns
电荷泵
直流特性
参数
符号
条件
最小值
典型值
最大值
单位
电荷泵输出电压
VVCP-VVS
工作
V12VOUT
-2
V12VOUT
-1
V
用于欠压检测的电荷泵电压阈值
VVCP-VVS
上升，内部5V 调节
器电压
4.5
5
6.5
V
电荷泵频率
fCP
1/16
fCLKOSC


<!-- detected tables -->

| 电机驱动器部分 | 直流特性和时序 V = 24.0V; Tj=50°C VS |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| RDS 低侧驱动器 ON | R ONL | 栅极关断 |  | 1.8 | 3 | Ω |
| RDS 高侧驱动器 ON | R ONH | 栅极关断 |  | 2.2 | 3.5 | Ω |
| 低侧MOSFET 在2V V 下导通栅 GS 极驱动电流 | I SLPON0 | DRVSTRENGTH=0 |  | 200 |  | mA |
|  | I SLPON2 | DRVSTRENGTH=2 |  | 400 |  | mA |
|  | I SLPON3 | DRVSTRENGTH=3 |  | 600 |  | mA |
| 高侧MOSFET 在2V V 下导通栅 GS 极驱动电流 | I SLPON0 | DRVSTRENGTH=0 |  | 150 |  | mA |
|  | I SLPON2 | DRVSTRENGTH=2 |  | 300 |  | mA |
|  | I SLPON3 | DRVSTRENGTH=3 |  | 450 |  | mA |
| 内部延迟的BBM 时间(从栅极关 闭开始到栅极导通) | t BBM0 | BBMCLKS=0 BBMTIME=0 | 75 | 100 |  | ns |
|  | t BBM16 | BBMTIME=16 |  | 200 |  | ns |
|  | t BBM16 | BBMTIME=24 |  | 375 | 500 | ns |

| 电荷泵 | 直流特性 |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| 电荷泵输出电压 | V -V VCP VS | 工作 | V 12VOUT -2 | V 12VOUT -1 |  | V |
| 用于欠压检测的电荷泵电压阈值 | V -V VCP VS | 上升，内部5V 调节 器电压 | 4.5 | 5 | 6.5 | V |
| 电荷泵频率 | f CP |  |  | 1/16 f CLKOSC |  |  |
--- [PAGE 170] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
170
www.trinamic.com
线性调节器
直流特性
VVS = VVSA = 24.0V
参数
符号
条件
最小值
典型值
最大值
单位
输出电压
V5VOUT
TJ = 25°C
4.80
5.0
5.20
V
整个温度范围内的输出电压偏差
V5VOUT(DEV)
驱动器关闭
TJ = 全温度范围
+/-30
+/-100
mV
整个电源电压范围内的输出电压
偏差
V5VOUT(DEV)
驱动器关闭，
内部时钟
TA = 25°C
VVSA = 10V to 30V
+/-50
mV /
10V
输出电压
V12VOUT
operating, internal
clock
TJ = 25°C
10.8
11.5
12.2
V
时钟振荡器和输入
时序特征
参数
符号
条件
最小值
典型值
最大值
单位
时钟振荡器频率(工厂校准)
fCLKOSC
tJ=-50°C
11.7
MHz
fCLKOSC
tJ=50°C
11.5
12.0
12.5
MHz
fCLKOSC
tJ=150°C
12.1
MHz
外部时钟频率(工作)
fCLK
4
10-16
18
MHz
外部时钟高/低电平时间
tCLKH /
tCLKL
CLK 为
0.1 VVIO / 0.9 VVIO
16
ns
触发切换到外部CLK 的外部时钟
第一个脉冲
tCLKH /
tCLKL
CLK 高，A 版本
16
ns
触发切换到外部CLK 的外部时钟
第一个脉冲
tCLKH /
tCLKL
CLK 高，非A 版本
30
25
ns
外部时钟超时检测，按内部fCLKOSC
作为计算周期
tCLKH1
CLK 高电平
32
48
cycles
fCLKOSC


<!-- detected tables -->

| 线性调节器 | 直流特性 V = V = 24.0V VS VSA |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| 输出电压 | V 5VOUT | T = 25°C J | 4.80 | 5.0 | 5.20 | V |
| 整个温度范围内的输出电压偏差 | V 5VOUT(DEV) | 驱动器关闭 T = 全温度范围 J |  | +/-30 | +/-100 | mV |
| 整个电源电压范围内的输出电压 偏差 | V 5VOUT(DEV) | 驱动器关闭， 内部时钟 T = 25°C A V = 10V to 30V VSA |  |  | +/-50 | mV / 10V |
| 输出电压 | V 12VOUT | operating, internal clock T = 25°C J | 10.8 | 11.5 | 12.2 | V |

| 时钟振荡器和输入 | 时序特征 |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| 时钟振荡器频率(工厂校准) | f CLKOSC | t=-50°C J |  | 11.7 |  | MHz |
|  | f CLKOSC | t=50°C J | 11.5 | 12.0 | 12.5 | MHz |
|  | f CLKOSC | t=150°C J |  | 12.1 |  | MHz |
| 外部时钟频率(工作) | f CLK |  | 4 | 10-16 | 18 | MHz |
| 外部时钟高/低电平时间 | t / CLKH t CLKL | CLK 为 0.1 V / 0.9 V VIO VIO | 16 |  |  | ns |
| 触发切换到外部CLK 的外部时钟 第一个脉冲 | t / CLKH t CLKL | CLK 高，A 版本 | 16 |  |  | ns |
| 触发切换到外部CLK 的外部时钟 第一个脉冲 | t / CLKH t CLKL | CLK 高，非A 版本 | 30 | 25 |  | ns |
| 外部时钟超时检测，按内部f CLKOSC 作为计算周期 | t CLKH1 | CLK 高电平 | 32 |  | 48 | cycles f CLKOSC |
--- [PAGE 171] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
171
www.trinamic.com
短路检测
直流特性
参数
符号
条件
最小值
典型值
最大值
单位
对GND 短路/对VS 检测器短路延
迟(从栅极开关开始到短路检测)
包括100ns 滤波时间
tSD0
FILT_ISENSE=0
S2xx_LEVEL=6
shortdelay=0
0.5
0.85
1.1
µs
tSD1
shortdelay=1
1.1
1.6
2.2
µs
短路检测电平S2VS (测量包括采
样电阻电压跌落)
VBM
S2VS_LEVEL=15
1.4
1.56
1.72
V
S2VS_LEVEL=6
0.55
0.625
0.70
V
短路检测电平
VS - VBM
S2G_LEVEL=15;
VS<52V
1.2
1.56
1.9
V
S2G_LEVEL=15;
VS<55V
0.85
V
S2G_LEVEL=6;
VS<50V
0.46
0.625
0.80
V
检测电平
直流特性
参数
符号
条件
最小值
典型值
最大值
单位
VVSA 复位欠压阈值
VUV_VSA
VVSA 上升
3.6
4
4.6
V
V5VOUT 复位欠压阈值
VUV_5VOUT
V5VOUT 上升
3.5
V
VVCC_IO 复位欠压阈值
VUV_VIO
VVCC_IO 上升(delay typ.
10µs)
2.0
2.5
3.0
V
VVCC_IO 欠压检测器磁滞
VUV_VIOHYST
0.3
V
过温预警120°C
TOTPW
温度上升
100
120
140
°C
过温关断
136 °C
TOT136
温度上升
136
°C
过温关断
143 °C
TOT143
温度上升
143
°C
过温关断
150 °C
TOT150
温度上升
135
150
170
°C


<!-- detected tables -->

| 短路检测 | 直流特性 |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| 对GND 短路/对VS 检测器短路延 迟(从栅极开关开始到短路检测) 包括100ns 滤波时间 | t SD0 | FILT ISENSE=0 _ S2xx LEVEL=6 _ shortdelay=0 | 0.5 | 0.85 | 1.1 | µs |
|  | t SD1 | shortdelay=1 | 1.1 | 1.6 | 2.2 | µs |
| 短路检测电平S2VS (测量包括采 样电阻电压跌落) | V BM | S2VS LEVEL=15 _ | 1.4 | 1.56 | 1.72 | V |
|  |  | S2VS LEVEL=6 _ | 0.55 | 0.625 | 0.70 | V |
| 短路检测电平 | V - V S BM | S2G LEVEL=15; _ VS<52V | 1.2 | 1.56 | 1.9 | V |
|  |  | S2G LEVEL=15; _ VS<55V | 0.85 |  |  | V |
|  |  | S2G LEVEL=6; _ VS<50V | 0.46 | 0.625 | 0.80 | V |

| 检测电平 | 直流特性 |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| V 复位欠压阈值 VSA | V UV VSA _ | V 上升 VSA | 3.6 | 4 | 4.6 | V |
| V 复位欠压阈值 5VOUT | V UV 5VOUT _ | V 上升 5VOUT |  | 3.5 |  | V |
| V 复位欠压阈值 VCC IO _ | V UV VIO _ | V 上升(delay typ. VCC IO _ 10µs) | 2.0 | 2.5 | 3.0 | V |
| V 欠压检测器磁滞 VCC IO _ | V UV VIOHYST _ |  |  | 0.3 |  | V |
| 过温预警120°C | T OTPW | 温度上升 | 100 | 120 | 140 | °C |
| 过温关断 136 °C | T OT136 | 温度上升 |  | 136 |  | °C |
| 过温关断 143 °C | T OT143 | 温度上升 |  | 143 |  | °C |
| 过温关断 150 °C | T OT150 | 温度上升 | 135 | 150 | 170 | °C |
--- [PAGE 172] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
172
www.trinamic.com
采样电阻电压电平
直流特性
fCLK=16MHz
参数
符号
条件
最小值
典型值
最大值
单位
采样电阻输入峰值阈值电压
(低敏感度)
(VSRxH-VSRxL)
VSRT
GLOBALSCALER=0
csactual=31
sin_x=248
Hyst.=0; IBRxy=0
325
mV
采样电阻输入公差/电机电流满量
程公差
-内部参考
ICOIL
GLOBALSCALER=0
-5
+5
%
数字脚
直流特性
参数
符号
条件
最小值
典型值
最大值
单位
输入电压低电平
VINLO
-0.3
0.3 VVIO
V
输入电压高电平
VINHI
0.7 VVIO
VVIO+0.
3
V
输入施密特触发器磁滞
VINHYST
0.12
VVIO
V
输出电压低电平
VOUTLO
IOUTLO = 2mA
0.2
V
输出电压高电平
VOUTHI
IOUTHI = -2mA
VVIO-0.2
V
输入漏电流
IILEAK
-10
10
µA
上拉/下拉电阻
RPU/RPD
132
166
200
kΩ
数字管脚电容
C
3.5
pF
26.3 热特性
下表将给出热阻相关信息。四层板有助于系统热阻设计。实际的热特性将取决于PCB 布局、PCB 类
型和PCB 尺寸。热阻将受益于较厚的CU (内部)层，用于在PCB 内水平散热。此外，气流将降低热阻。


<!-- detected tables -->

| 采样电阻电压电平 | 直流特性 f =16MHz CLK |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| 采样电阻输入峰值阈值电压 (低敏感度) (V -V ) SRxH SRxL | V SRT | GLOBALSCALER=0 csactual=31 sin x=248 _ Hyst.=0; I =0 BRxy |  | 325 |  | mV |
| 采样电阻输入公差/电机电流满量 程公差 -内部参考 | I COIL | GLOBALSCALER=0 | -5 |  | +5 | % |

| 数字脚 | 直流特性 |  |  |  |  |  |
|---|---|---|---|---|---|---|
| 参数 | 符号 | 条件 | 最小值 | 典型值 | 最大值 | 单位 |
| 输入电压低电平 | V INLO |  | -0.3 |  | 0.3 V VIO | V |
| 输入电压高电平 | V INHI |  | 0.7 V VIO |  | V +0. VIO 3 | V |
| 输入施密特触发器磁滞 | V INHYST |  |  | 0.12 V VIO |  | V |
| 输出电压低电平 | V OUTLO | I = 2mA OUTLO |  |  | 0.2 | V |
| 输出电压高电平 | V OUTHI | I = -2mA OUTHI | V -0.2 VIO |  |  | V |
| 输入漏电流 | I ILEAK |  | -10 |  | 10 | µA |
| 上拉/下拉电阻 | R /R PU PD |  | 132 | 166 | 200 | kΩ |
| 数字管脚电容 | C |  |  | 3.5 |  | pF |
--- [PAGE 173] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
173
www.trinamic.com
参数
符号
条件
典型值
单位
典型功耗
PD
StealthChop 或者spreadCycle, 40 or
20kHz 斩波器, 24V, 内部供电调节器
0.6
W
多层板上与环境的热阻
RTMJA
如JEDEC EIA JESD51 - 5 和JESD51 - 7 中
定义的两个信号层和两个电源层板
( 2s2p )
(FR4, 35µm CU, 70mm x 133mm,
d=1.5mm)
21
K/W
到板上的热阻
RTJB
距离封装引引脚1 毫米范围内测量的
PCB 温度
8
K/W
到外壳的热阻
RTJC
J 封装的散热片对应的结温
3
K/W
表26.1 TQFP48-EP 封装的热特性
实际布局中的热阻可以通过芯片待机功耗引起的发热来测试。不接电机时，在电源上看到的所有功
率都是芯片产生。


<!-- detected tables -->

| 参数 | 符号 | 条件 | 典型值 | 单位 |
|---|---|---|---|---|
| 典型功耗 | P D | StealthChop 或者spreadCycle, 40 or 20kHz 斩波器, 24V, 内部供电调节器 | 0.6 | W |
| 多层板上与环境的热阻 | R TMJA | 如JEDEC EIA JESD51 - 5 和JESD51 - 7 中 定义的两个信号层和两个电源层板 ( 2s2p ) (FR4, 35µm CU, 70mm x 133mm, d=1.5mm) | 21 | K/W |
| 到板上的热阻 | R TJB | 距离封装引引脚1 毫米范围内测量的 PCB 温度 | 8 | K/W |
| 到外壳的热阻 | R TJC | J 封装的散热片对应的结温 | 3 | K/W |
