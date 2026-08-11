# TMC5160A_Datasheet_Rev1_13_CN — 第6章 · p87

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
87
www.trinamic.com
的最小设置是足够的( PWM _ REG = 1 )。PWM_REG设置应根据所需的最快加速度和减速度优化(比较图
6.3和图6.4 )。监测加速阶段电机电流，如图6.5所示，可以判断AT# 2阶段设置的PWM_REG以及参数自调
整过程(或者非自定标过程PWM_OFS和PWM_GRAD)参数是否适合。
图6.3 示波器: PWM_REG 优化设置
图6.4 示波器:在AT # 2 期间，PWM _ REG 的设置太小

