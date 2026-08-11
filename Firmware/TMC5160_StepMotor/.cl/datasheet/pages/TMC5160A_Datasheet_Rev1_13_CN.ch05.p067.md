# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p67

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
67
www.trinamic.com
驱动寄存器组(0X6C…0X7F)
R/W
地址
n
寄存器
描述/ 位名称
范围[单位]
RW
0x6C
32
CHOPCONF
斩波器和驱动配置
请另见表格
复位缺省值=
0x10410150
W
0x6D
25
COOLCONF
CoolStep 智能电流控制寄存器
和stallGuard 2 配置
请另见表格
W
0x6E
24
DCCTRL
DcStep ( DC )自动换向配置寄存器
(通过引脚DCEN 或VDCMIN 使能) :
9… 0 位:
DC_TIME: 换相中PWM 导通时间的
上限(DC_TIME * 1 / fCLK )。应略高
大于有效消影时间TBL。
23… 16 位: DC_SG: DcStep 模式下，DcStep
StallGuard2 失步检测的最大PWM
导通时间(DC_SG * 16/fCLK)
应略高于DC_TIME/16
0=禁用
提示:高细分或插值运算，DcStep 可产生更好
的stallGuard 信号
如果使能vhighchm，则DC _ SG 在速度高于高
于VHIGH 在VHIGH 以上也可用。为了获得最
佳结果，需设置vhighchm。
R
0x6F
32
DRV_
STATUS
StallGuard2 值和驱动错误标志
请另见表格！
W
0x70
22
PWMCONF
电压PWM 模式斩波器配置
请另见表格！
复位缺省值=
0xC40C001E
R
0x71
9+8
PWM_SCALE
斩波调幅器的结果。这些值可用于监控自动
PWM 幅度调节( 255 =最大值电压)。
bit 7… 0
PWM_SCALE_SUM:
实际脉宽调制占空比。该值用于
缩放从正弦波表中读取的值
CUR_A 和CUR_B。
0…255


<!-- detected tables -->

| 驱动寄存器组(0X6C…0X7F) |  |  |  |  |  |  |
|---|---|---|---|---|---|---|
| R/W | 地址 | n | 寄存器 | 描述/ 位名称 |  | 范围[单位] |
| RW | 0x6C | 32 | CHOPCONF | 斩波器和驱动配置 请另见表格 |  | 复位缺省值= 0x10410150 |
| W | 0x6D | 25 | COOLCONF | CoolStep 智能电流控制寄存器 和stallGuard 2 配置 请另见表格 |  |  |
| W | 0x6E | 24 | DCCTRL | DcStep ( DC )自动换向配置寄存器 (通过引脚DCEN 或VDCMIN 使能) : 9… 0 位: DC TIME: 换相中PWM 导通时间的 _ 上限(DC TIME * 1 / fCLK )。应略高 _ 大于有效消影时间TBL。 23… 16 位: DC SG: DcStep 模式下， DcStep _ StallGuard2 失步检测的最大 PWM 导通时间(DC SG * 16/f ) _ CLK 应略高于DC TIME/16 _ 0=禁用 提示:高细分或插值运算，DcStep 可产生更好 的stallGuard 信号 如果使能vhighchm，则DC SG 在速度高于高 _ 于VHIGH 在VHIGH 以上也可用。为了获得最 佳结果，需设置vhighchm。 |  |  |
| R | 0x6F | 32 | DRV _ STATUS | StallGuard2 值和驱动错误标志 请另见表格！ |  |  |
| W | 0x70 | 22 | PWMCONF | 电压PWM 模式斩波器配置 请另见表格！ |  | 复位缺省值= 0xC40C001E |
| R | 0x71 | 9+8 | PWM SCALE _ | 斩波调幅器的结果。这些值可用于监控自动 PWM 幅度调节( 255 =最大值电压)。 |  |  |
|  |  |  |  | bit 7… 0 | PWM SCALE SUM: _ _ 实际脉宽调制占空比。该值用于 缩放从正弦波表中读取的值 CUR A 和CUR B。 _ _ | 0…255 |
