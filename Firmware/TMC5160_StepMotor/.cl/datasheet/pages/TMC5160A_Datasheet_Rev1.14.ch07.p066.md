# TMC5160A_Datasheet_Rev1.14 — 第7章 · p66

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
66 
 
 
 
www.trinamic.com 
7.6 Flags in StealthChop 
As StealthChop uses voltage mode driving, status flags based on current measurement respond 
slower, respectively the driver reacts delayed to sudden changes of back EMF, like on a motor stall. 
 
Attention 
A motor stall, or abrupt stop of the motion during operation in StealthChop can lead to a overcurrent 
condition. Depending on the previous motor velocity, and on the coil resistance of the motor, it 
significantly increases motor current for a time of several 10ms. With low velocities, where the back 
EMF is just a fraction of the supply voltage, there is no danger of triggering the short detection.  
 
Hint 
Tune low side driver overcurrent detection to safely trigger upon motor stall, when using 
StealthChop. This will avoid high peak current draw from the power supply. 
 
7.6.1 
Open Load Flags 
In StealthChop mode, status information is different from the cycle-by-cycle regulated SpreadCycle 
mode. OLA and OLB show if the current regulation sees that the nominal current can be reached on 
both coils.  
- 
A flickering OLA or OLB can result from asymmetries in the sense resistors or in the motor 
coils.  
- 
An interrupted motor coil leads to a continuously active open load flag for the coil.  
- 
One or both flags are active, if the current regulation did not succeed in scaling up to the full 
target current within the last few fullsteps (because no motor is attached or a high velocity 
exceeds the PWM limit).  
 
If desired, do an on-demand open load test using the SpreadCycle chopper, as it delivers the safest 
result. With StealthChop, PWM_SCALE_SUM can be checked to detect the correct coil resistance.  
 
7.6.2 
PWM_SCALE_SUM Informs about the Motor State 
Information about the motor state is available with automatic scaling by reading out 
PWM_SCALE_SUM. As this parameter reflects the actual voltage required to drive the target current into 
the motor, it depends on several factors: motor load, coil resistance, supply voltage, and current 
setting. Therefore, an evaluation of the PWM_SCALE_SUM value allows checking the motor operation 
point. When reaching the limit (255), the current regulator cannot sustain the full motor current, e.g. 
due to a drop in supply volage.  
7.7 Freewheeling and Passive Braking 
StealthChop provides different options for motor standstill. These options can be enabled by setting 
the standstill current IHOLD to zero and choosing the desired option using the FREEWHEEL setting. 
The desired option becomes enabled after a time period specified by TPOWERDOWN and IHOLDDELAY. 
Current regulation becomes frozen once the motor target current is at zero current in order to ensure 
a quick startup. With the freewheeling options, both freewheeling and passive braking can be 
realized. Passive braking is an effective eddy current motor braking, which consumes a minimum of 
energy, because no active current is driven into the coils. However, passive braking will allow slow 
turning of the motor when a continuous torque is applied.  
 
Hint 
Operate the motor within your application when exploring StealthChop. Motor performance often is 
better with a mechanical load, because it prevents the motor from stalling due mechanical oscillations 
which can occur without load. 
 

