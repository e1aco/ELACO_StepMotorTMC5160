# TMC5160A_Datasheet_Rev1.14 — 第7章 · p64

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  64 
 
 
 
www.trinamic.com 
PWM scaling
(PWM_SCALE_SUM)
Velocity
PWM_OFS
PWM reaches 
max. amplitude
255
0
PWM_GRAD
Motor current
Nominal current
(e.g. sine wave RMS)
Current drops 
(depends on 
motor load)
Constant motor 
RMS current 
0
VPWMMAX
 
Figure 7.6 Velocity based PWM scaling (pwm_autoscale=0) 
 
Hint 
The values for PWM_OFS and PWM_GRAD can easily be optimized by tracing the motor current with a  
current probe on the oscilloscope. Alternatively, automatic tuning determines these values and they 
can be read out from PWM_OFS_AUTO and PWM_GRAD_AUTO. 
 
UNDERSTANDING THE BACK EMF CONSTANT OF A MOTOR  
The back EMF constant is the voltage a motor generates when turned with a certain velocity. Often 
motor datasheets do not specify this value, as it can be deducted from motor torque and coil current 
rating. Within SI units, the numeric value of the back EMF constant C BEMF has the same numeric value 
as the numeric value of the torque constant. For example, a motor wi th a torque constant of 1 Nm/A 
would have a C BEMF of 1V/rad/s. Turning such a motor with 1 rps (1 rps = 1 revolution per second = 
6.28 rad/s) generates a back EMF voltage of 6.28V. Thus, the back EMF constant can be calculated as: 
 
𝐶𝐵𝐸𝑀𝐹 [ 𝑉
𝑟𝑎𝑑/𝑠] = 𝐻𝑜𝑙𝑑𝑖𝑛𝑔𝑇𝑜𝑟𝑞𝑢𝑒[𝑁𝑚]
2 ∗ 𝐼𝐶𝑂𝐼𝐿𝑁𝑂𝑀[𝐴]  
 
ICOILNOM is the motor’s rated phase current for the specified holding torque 
HoldingTorque is the motor specific holding torque, i.e. the  torque reached at I COILNOM on both coils. 
The torque unit is [Nm] where 1Nm = 100Ncm = 1000mNm. 
The voltage is valid as RMS voltage per coil, thus the nominal current is multiplied by 2 in this 
formula, since the nominal current assumes a full step position, with two coils operating.  
 
7.5 Combining StealthChop and SpreadCycle 
For applications requiring high velocity motion , SpreadCycle may bring more stable operation in the 
upper velocity range. To combine no-noise operation with highest dynamic performance, the TMC5160 
allows combining StealthChop and SpreadCycle based on a velocity threshold ( Figure 7.7). With this, 
StealthChop is only active at low velocities.  
 
