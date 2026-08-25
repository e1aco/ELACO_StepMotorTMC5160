# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p172

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 172
www.trinamic.com
采样电阻电压电平 直流特性
fCLK=16MHz
参数 符号 条件 最小值 典型值 最大值 单位
采样电阻输入峰值阈值电压
(低敏感度)
(VSRxH-VSRxL)
VSRT GLOBALSCALER=0
csactual=31
sin_x=248
Hyst.=0; IBRxy=0
325 mV
采样电阻输入公差/电机电流满量
程公差
-内部参考
ICOIL GLOBALSCALER=0 -5 +5 %
数字脚 直流特性
参数 符号 条件 最小值 典型值 最大值 单位
输入电压低电平 VINLO -0.3 0.3 VVIO V
输入电压高电平 VINHI 0.7 VVIO VVIO+0.
3
V
输入施密特触发器磁滞 VINHYST 0.12
VVIO
V
输出电压低电平 VOUTLO IOUTLO = 2mA 0.2 V
输出电压高电平 VOUTHI IOUTHI = -2mA VVIO-0.2 V
输入漏电流 IILEAK -10 10 µA
上拉/下拉电阻 RPU/RPD 132 166 200 kΩ
数字管脚电容 C 3.5 pF
26.3 热特性
下表将给出热阻相关信息。四层板有助于系统热阻设计。实际的热特性将取决于 PCB 布局、PCB 类
型和 PCB 尺寸。热阻将受益于较厚的 CU (内部)层，用于在 PCB 内水平散热。此外，气流将降低热阻。
