# TMC5160A_Datasheet_Rev1.14 — 第7章 · p57

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  57 
 
 
 
www.trinamic.com 
7 StealthChop™ 
StealthChop is an extremely quiet mode of operation for stepper motors. It is based on a 
voltage mode PWM. In case of standstill and at low velocities, the motor  is absolutely 
noiseless. Thus, StealthChop operated stepper motor applications are very suitable for 
indoor or home use. The motor operates absolutely free of vibration at low velocities. 
With StealthChop, the motor current is applied by driving a certain  effective voltage into the coil,  
using a voltage mode PWM. With the enhanced StealthChop2, the driver automatically adapts to the 
application for best performance. No more configurations are required. Optional configuration allows 
for tuning the setting i n special cases, or for storing i nitial values for the automatic adaptation 
algorithm. For high velocity drives SpreadCycle should be considered in combination with 
StealthChop. 
 
Figure 7.1 Motor coil sine wave current with StealthChop (measured with current probe) 
 
7.1 Automatic Tuning 
StealthChop2 integrates an automatic tuning procedure  (AT), which adapts the most important 
operating parameters to the motor automatically. This way, StealthChop2 allows high motor dynamics 
and supports powering down the motor to very low currents. Just two steps have to be respected by 
the motion controller for best results: Start with the motor in standstill, but powered with nominal 
run current (AT#1). Move th e motor at a mediu m velocity, e.g. as part of a homing procedure (AT#2). 
Figure 7.2 shows the tuning procedure.  
Border conditions for AT#1 and AT#2 are shown in the following table:  
 

