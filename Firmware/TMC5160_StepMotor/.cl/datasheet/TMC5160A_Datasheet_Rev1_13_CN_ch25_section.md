# TMC5160A_Datasheet_Rev1_13_CN — 第25章 最大电气参数

--- [PAGE 166] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
166
www.trinamic.com
25. 最大电气参数
任何情况下都不得超过最高限制。系统设计应避免超过最大额定值或在接近最大额定值的情况下长
时间运行电路
参数
符号
最小值
最大值
单位
感性负载下最大供电电压
VVS, VVSA
-0.5
60
V
电源和功率桥臂电压短时峰值(受电荷泵输出和Cxx 引脚上的
峰值电压限制* )
VVSMAX
64
V
VSA （与VS 不是一路供电）
VVSAMAX
-0.5
60
V
Cxx 自举引脚和VCP 引脚上的峰值电压
VCxCP
76
V
V12OUT 供电电压
V12VOUT
-0.5
14
V
BM 引脚上的峰值电压(由于杂散电感)
VBMx
-6
VVS+6
V
Cxx 自举引脚上相对于BM 的峰值电压
VCxBMx
-0.5
16
V
VCC_IO 对应的IO 口供电电压
VVIO
-0.5
5.5
V
数字VCC 供电电压(一般由5VOUT 供电)
VVCC
-0.5
5.5
V
逻辑输入电压
VI
-0.5
VVIO+0.5
V
数字引脚的最大电流
和模拟低电压I/Os (短时间峰值电流)
IIO
+/-500
mA
5V 调节器输出电流(内部加外部负载)
I5VOUT
30
mA


<!-- detected tables -->

| 参数 | 符号 | 最小值 | 最大值 | 单位 |
|---|---|---|---|---|
| 感性负载下最大供电电压 | V , V VS VSA | -0.5 | 60 | V |
| 电源和功率桥臂电压短时峰值(受电荷泵输出和Cxx 引脚上的 峰值电压限制* ) | V VSMAX |  | 64 | V |
| VSA （与VS 不是一路供电） | V VSAMAX | -0.5 | 60 | V |
| Cxx 自举引脚和VCP 引脚上的峰值电压 | V CxCP |  | 76 | V |
| V12OUT 供电电压 | V 12VOUT | -0.5 | 14 | V |
| BM 引脚上的峰值电压(由于杂散电感) | V BMx | -6 | V +6 VS | V |
| Cxx 自举引脚上相对于BM 的峰值电压 | V CxBMx | -0.5 | 16 | V |
| VCC IO 对应的IO 口供电电压 _ | V VIO | -0.5 | 5.5 | V |
| 数字VCC 供电电压(一般由5VOUT 供电) | V VCC | -0.5 | 5.5 | V |
| 逻辑输入电压 | V I | -0.5 | V +0.5 VIO | V |
| 数字引脚的最大电流 和模拟低电压I/Os (短时间峰值电流) | I IO |  | +/-500 | mA |
| 5V 调节器输出电流(内部加外部负载) | I 5VOUT |  | 30 | mA |
