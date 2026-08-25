# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p171

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 171
www.trinamic.com
短路检测 直流特性
参数 符号 条件 最小值 典型值 最大值 单位
对 GND 短路/对 VS 检测器短路延
迟(从栅极开关开始到短路检测)
包括 100ns 滤波时间
tSD0 FILT_ISENSE=0
S2xx_LEVEL=6
shortdelay=0
0.5 0.85 1.1 µs
tSD1 shortdelay=1 1.1 1.6 2.2 µs
短路检测电平 S2VS (测量包括采
样电阻电压跌落)
VBM S2VS_LEVEL=15 1.4 1.56 1.72 V
S2VS_LEVEL=6 0.55 0.625 0.70 V
短路检测电平 VS - VBM S2G_LEVEL=15;
VS<52V
1.2 1.56 1.9 V
S2G_LEVEL=15;
VS<55V
0.85 V
S2G_LEVEL=6;
VS<50V
0.46 0.625 0.80 V
检测电平 直流特性
参数 符号 条件 最小值 典型值 最大值 单位
VVSA 复位欠压阈值 VUV_VSA VVSA 上升 3.6 4 4.6 V
V5VOUT 复位欠压阈值 VUV_5VOUT V5VOUT 上升 3.5 V
VVCC_IO 复位欠压阈值 VUV_VIO VVCC_IO 上升(delay typ.
10µs)
2.0 2.5 3.0 V
VVCC_IO 欠压检测器磁滞 VUV_VIOHYST 0.3 V
过温预警 120°C TOTPW 温度上升 100 120 140 °C
过温关断
136 °C
TOT136 温度上升 136 °C
过温关断
143 °C
TOT143 温度上升 143 °C
过温关断
150 °C
TOT150 温度上升 135 150 170 °C
