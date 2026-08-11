# TMC5160A_Datasheet_Rev1_13_CN — 第6章 · p91

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
91
www.trinamic.com
图6.6 基于速度的PWM 定标( pwm _autoscale= 0 )
提示：
可通过示波器的电流探头测量电机电流进一步优化PWM_OFS 和PWM_GRAD 。
也可以通过参数自调整从寄存器PWM_OFS_AUTO 和PWM_GRAD_AUTO 读出。
了解电机的反电势系数
反电势系数是电机以一定速度转动时产生的电压。电机规格书通常不列出此值，可从电机转矩和线
圈电流额定值中计算得到。在标准国际单位制（SI）中，反电势常数CBEMF 的数值和转矩常数的数值是一
致。转矩常数为1 Nm / A 的电机将具有1V / rad / s 的反电势系数，用1 rps ( 1 rps=每秒1 转= 6.28 弧度/
秒)转动，电机产生6.28v 的反电势电压。因此，反电势系数可以计算为:
CBEMF
V
rad/s = HoldingTorque Nm
2 כ ICOILNOM[A]
ICOILNOM 是保持转矩下电机的额定相电流
HoldingTorques是电机特定的保持转矩，即在两个线圈上电流为ICOILNOM达到的转矩。转矩单位为
[Nm] 。1Nm = 100Ncm = 1000mNm。
电压是每个线圈的均值有效电压, 因为电流在全步位置，两相都通电流，因此在该公式中，系数乘
以2。

