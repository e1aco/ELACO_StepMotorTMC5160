# TMC5160A_Datasheet_Rev1.14 — 第7章 · p59

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
59 
 
 
 
www.trinamic.com 
AT#1
Stand still
AT#2
Homing
Ready
Power Up
stealthChop2 regulates to nominal 
current and stores result to 
PWM_OFS_AUTO
(Requires stand still for >130ms)
N
PWM_GRAD_AUTO becomes 
initialized upon power up
Driver Enabled?
N
Standstill re- 
duction enabled?
Y
Issue (at least) a single step 
pulse and stop again, to 
power motor to run current
Y
Driver Enabled?
N
Y
Move the motor, e.g. for homing. 
Include a constant, medium velocity 
ramp segment.
Store PWM_GRAD_AUTO to 
CPU memory for faster 
tuning procedure
Option with interface
PWM_
GRAD_AUTO 
initialized from 
CPU?
N
Y
stealthChop2 regulates to nominal 
current and optimizes PWM_GRAD_AUTO
(requires 8 fullsteps per change of 1, 
typically a few 100 fullsteps in sum)
stealthChop2 settings are optimized!
stealthChop2 keeps tuning during 
subsequent motion and stand still periods 
adapting to motor heating, supply 
variations, etc.
 
Figure 7.2 StealthChop2 automatic tuning procedure 
 
Attention 
Modifying GLOBALSCALER or VS voltage invalidates the result of the automatic tuning process. Motor 
current regulation cannot compensate significant changes until next AT#1 phase. Automatic tuning 
adapts to changed conditions whenever AT#1 and AT#2 conditions are fulfilled in the later operation. 


<!-- detected tables -->

|  | Store PWM GRAD AUTO to _ _ CPU memory for faster tuning procedure |  |
|---|---|---|
