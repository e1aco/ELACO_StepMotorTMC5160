# TMC5160A_Datasheet_Rev1.14 — 第14章 14 CoolStep Operation

--- [PAGE 91] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  91 
 
 
 
www.trinamic.com 
14 CoolStep Operation 
CoolStep is an automatic smart energy optimization for stepper motors based on the motor 
mechanical load, making them “green”.  
14.1 User Benefits 
 
 
 
 
 
 
 
CoolStep allows substantial energy savings, especially for motors which see varying loads or operate 
at a high duty cycle. Because a stepper motor application needs to work with a torque reserve of 30% 
to 50%, even a constant -load application allows significant en ergy savings beca use CoolStep 
automatically enables torque reserve when required. Reducing power consumption keeps the system 
cooler, increases motor life, and allows reducing cost in the power supply and cooling components.  
 
Reducing motor current by half results in reducing power by a factor of four. 
14.2 Setting up for CoolStep 
CoolStep is controlled by several parameters, but two are critical for understanding how it works: 
 
Parameter Description Range Comment 
SEMIN 4-bit unsigned integer that sets a lower threshold. 
If SG goes below this threshold, CoolStep 
increases the current to both coils. The 4 -bit 
SEMIN value is scaled by 32 to cover the lower 
half of the range of the 10 -bit SG value. (The 
name of this paramete r is derived from 
smartEnergy, which is an earlier name f or 
CoolStep.) 
0 disable CoolStep 
1…15 threshold is SEMIN*32 
SEMAX 4-bit unsigned integer that controls an upper 
threshold. If SG is sampled equal to or above this 
threshold enough times, CoolStep decreases the 
current to both coils. The upper threshold  is 
(SEMIN + SEMAX + 1)*32. 
0…15 threshold is 
(SEMIN+SEMAX+1)*32 
 
 
Figure 14.1 shows the operating regions of CoolStep:  
- The black line represents the SG measurement value.  
- The blue line represents the mechanical load applied to the motor.  
- The red line represents the current into the motor coils.  
 
When the load increases, SG_RESULT falls below SEMIN, and CoolStep increases the current. When the 
load decreases, SG_RESULT rises above (SEMIN + SEMAX + 1) * 32, and the current is reduced. 
Energy efficiency – consumption decreased up to 75% 
Motor generates less heat – improved mechanical precision 
Less cooling infrastructure – for motor and driver 
Cheaper motor – does the job! 
--- [PAGE 92] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  92 
 
 
 
www.trinamic.com 
stallGuard2 
reading
0=maximum load
motor current increment area
motor current reduction area
stall possible
SEMIN
SEMAX+SEMIN+1
Zeit motor current
current setting I_RUN 
(upper limit)
½ or ¼ I_RUN 
(lower limit)
mechanical load
current increment due to 
increased load
slow current reduction due 
to reduced motor load
load angle optimized load angle optimized
load 
angle 
optimized
 
Figure 14.1 CoolStep adapts motor current to the load 
 
Five more parameters control CoolStep and one status value is returned: 
 
Parameter Description Range Comment 
SEUP Sets the current increment step . The current 
becomes incremented for each measured 
StallGuard2 value below the lower threshold. 
0…3 step width is 
1, 2, 4, 8  
SEDN Sets the number of StallGuard2 readings above 
the upper threshold necessary f or each current 
decrement of the motor current. 
0…3 number of StallGuard2 
measurements per 
decrement: 
32, 8, 2, 1 
SEIMIN Sets the lower motor current limit  for CoolStep 
operation by scaling the IRUN current setting.  
0 0: 1/2 of IRUN  
1 1: 1/4 of IRUN 
TCOOL 
THRS 
Lower velocity threshold  for switching on 
CoolStep and stop on stall . Below this velocity 
CoolStep becomes disabled (not used in STEP/DIR 
mode). Adapt to the lower limit of the velocity 
range where StallGuard2 gives a stable result.  
 
Hint: May be adapted to disable CoolStep during 
acceleration and deceleration phase by setting 
identical to VMAX. 
1… 
2^20-1 
Specifies lower CoolStep 
velocity by comparing 
the threshold value to 
TSTEP 
THIGH Upper velocity threshold value  for CoolStep and 
stop on st all. Above this velocity CoolStep 
becomes disabled. Adapt to the velocity range 
where StallGuard2 gives a stable result. 
1… 
2^20-1 
Also controls additional 
functions like switching 
to fullstepping. 
Status 
word 
Description Range Comment 
CSACTUAL This stat us value provides the actual motor 
current scale as controlled by CoolStep. The value 
goes up to the IRUN value and down to the 
portion of IRUN as specified by SEIMIN. 
0…31 1/32, 2/32, … 32/32 
 
  
--- [PAGE 93] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  93 
 
 
 
www.trinamic.com 
14.3 Tuning CoolStep 
Before tuning CoolStep, first tune the StallGuard2 threshold level SGT, which affects the range of the 
load measurement value SG_RESULT. CoolStep uses SG_RESULT to operate the motor near the 
optimum load angle of +90°. 
 
The current increment speed is specified in SEUP, and the current decrement spe ed is specified in 
SEDN. They can be tuned separately because they are triggered by different events that may need 
different responses. The encodings for these parameters allow the coil currents to be increased much 
more quickly than decreased, because cro ssing the lower threshold is a more serious event that may 
require a faster response. If the response is too slow, the motor may stall. In contrast, a slow 
response to crossing the upper threshold does not risk anything more serious than missing an 
opportunity to save power. 
 
CoolStep operates between limits controlled by the current scale parameter IRUN and the seimin bit. 
 
14.3.1 Response Time 
For fast response to increasing motor load, use a high current increment step SEUP. If the motor load 
changes slowly, a lower current increment step can be used to avoid motor oscillations. If the filter 
controlled by sfilt is enabled, the measurement rate and regulation speed are cut by a factor of four. 
 
Hint 
The most common and most beneficial use is to adapt CoolStep for operation at the typical system 
target operation velocity and to set the velocity thresholds according. As acceleration and 
decelerations normally shall be quick, they will require the full motor current, while they have only a 
small contribution to overall power consumption due to their short duration. 
 
14.3.2 Low Velocity and Standby Operation 
Because CoolStep is not able to measure the motor  load in standstill and at very low RPM, a lower 
velocity threshold is provided in the ramp generator. It should be set to an application specific 
default value. Below this threshold the normal current setting via IRUN respectively IHOLD is valid. An 
upper threshold is provided by the VHIGH setting. Both thresholds can be set as a result of the 
StallGuard2 tuning process. 
 
