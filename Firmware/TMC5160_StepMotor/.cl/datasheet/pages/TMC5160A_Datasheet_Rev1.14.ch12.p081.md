# TMC5160A_Datasheet_Rev1.14 — 第12章 · p81

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
81 
 
 
 
www.trinamic.com 
12 Ramp Generator 
The ramp generator allows motion based on target position or target velocity. It automatically 
calculates the optimum motion profile taking into account acceleration and velocity settings. The 
TMC5160 integrates a new type of ramp generator, which offers faster machine operation compared to 
the classical linear acceleration ramps. The sixPoint ramp generator allows adapting the acceleration 
ramps to the torque curves of a stepper motor and uses two different acceleration settings each for 
the acceleration phase and for the deceleration phase. See Figure 12.2. 
12.1 Real World Unit Conversion 
The TMC5160 uses its internal or external clock signal as a time reference for all internal operations. 
Thus, all time, velocity and acceleration settings are referenced to fCLK. For best stability and 
reproducibility, it is recommended to use an external quartz oscillator as a time base, or to provide a 
clock signal from a microcontroller. 
 
The units of a TMC5160 register content are written as register[5160].  
 
PARAMETER VS. UNITS 
Parameter / Symbol 
Unit 
calculation / description / comment 
fCLK[Hz] 
[Hz] 
clock frequency of the TMC5160 in [Hz] 
s 
[s] 
second 
US 
µstep 
 
FS 
fullstep 
 
µstep velocity v[Hz] 
µsteps / s 
v[Hz] = v[5160] * ( fCLK[Hz]/2 / 2^23 ) 
µstep acceleration a[Hz/s] 
µsteps / s^2 
a[Hz/s] = a[5160] * fCLK[Hz]^2 / (512*256) / 2^24 
USC microstep count 
counts 
microstep resolution in number of microsteps 
(i.e. the number of microsteps between two 
fullsteps – normally 256) 
rotations per second v[rps]  
rotations / s 
v[rps] = v[µsteps/s] / USC / FSC 
FSC: motor fullsteps per rotation, e.g. 200 
rps acceleration a[rps/s^2] 
rotations / s^2 
a[rps/s^2] = a[µsteps/s^2] / USC / FSC 
ramp steps[µsteps] = rs 
µsteps 
rs = (v[5160])^2 / a[5160] / 2^8 
microsteps during linear acceleration ramp  
(assuming acceleration from 0 to v) 
TSTEP, T…THRS 
- 
TSTEP = fCLK / fSTEP 
The time reference for velocity thresholds is 
referred to the actual microstep frequency of 
the clock input respectively velocity v[Hz].  
 
In rare cases, the upper acceleration limit might impose a limitation to the application, e.g. when 
working with a reduced clock frequency or high gearing and low load on the motor. In order to 
increase the effective acceleration possible, the microstep resolution of the sequencer input may be 
decreased. Setting the CHOPCONF options intpol=1 and MRES=%0001 will double the motor velocity for 
the same speed setting and thus also double effective acceleration and deceleration. The motor will 
have the same smoothness, but half position resolution with this setting.  
 
Quick Start 
For a quick start, see the Quick Configuration Guide in chapter 22. 
 
 


<!-- detected tables -->

|  | PARAMETER VS. UNITS |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|
|  | Parameter / Symbol |  |  | Unit |  |  | calculation / description / comment |  |
|  | f [Hz] CLK |  | [Hz] |  |  | clock frequency of the TMC5160 in [Hz] |  |  |
|  | s |  | [s] |  |  | second |  |  |
|  | US |  | µstep |  |  |  |  |  |
|  | FS |  | fullstep |  |  |  |  |  |
|  | µstep velocity v[Hz] |  | µsteps / s |  |  | v[Hz] = v[5160] * ( f [Hz]/2 / 2^23 ) CLK |  |  |
|  | µstep acceleration a[Hz/s] |  | µsteps / s^2 |  |  | a[Hz/s] = a[5160] * f [Hz]^2 / (512*256) / 2^24 CLK |  |  |
| USC microstep count |  |  | counts |  |  | microstep resolution in number of microsteps (i.e. the number of microsteps between two fullsteps – normally 256) |  |  |
| rotations per second v[rps] |  |  | rotations / s |  |  | v[rps] = v[µsteps/s] / USC / FSC FSC: motor fullsteps per rotation, e.g. 200 |  |  |
|  | rps acceleration a[rps/s^2] |  | rotations / s^2 |  |  | a[rps/s^2] = a[µsteps/s^2] / USC / FSC |  |  |
| ramp steps[µsteps] = rs |  |  | µsteps |  |  | rs = (v[5160])^2 / a[5160] / 2^8 microsteps during linear acceleration ramp (assuming acceleration from 0 to v) |  |  |
| TSTEP, T…THRS |  |  | - |  |  | TSTEP = f / f CLK STEP The time reference for velocity thresholds is referred to the actual microstep frequency of the clock input respectively velocity v[Hz]. |  |  |
