# TMC5160A_Datasheet_Rev1.14 — 第12章 · p84

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
84 
 
 
 
www.trinamic.com 
12.2.5 Application Example: Joystick Control 
Applications like surveillance cameras can be optimally enhanced using the motion controller: while 
joystick commands operate the motor at a user defined velocity, the target ramp generator ensures 
that the valid motion range never is left.  
 
REALIZE JOYSTICK CONTROL 
1. 
Use positioning mode in order to control the motion direction and to set the motion limit(s). 
2. 
Modify VMAX at any time in the range VSTART to your maximum value. With VSTART=0, you can 
also stop motion by setting VMAX=0. The motion controller will use A1 and AMAX as determined 
by V1 to adapt velocity for ramping up and ramping down.  
3. 
In case you do not modify the acceleration settings, you do not need to rewrite XTARGET, just 
modify VMAX.  
4. 
DMAX, D1 and VSTOP only become used when the ramp controller slows down due to reaching 
the target position, or when the target position has been modified to point to the other direction. 
12.3 Velocity Thresholds 
The ramp generator provides a number of velocity thresholds coupled with the actual velocity 
VACTUAL. The different ranges allow programming the motor to the optimum step mode, coil current 
and acceleration settings. Most applications will not require all of the thresholds, but in principle all 
modes can be combined as shown in Figure 12.1. VHIGH and VCOOLTHRS are determined by the 
settings THIGH and TCOOLTHRS in order to allow determination of the velocity when an external step 
source is used. TSTEP becomes compared to these threshold values. A hysteresis of 1/16 TSTEP resp. 
1/32 TSTEP is applied to avoid continuous toggling of the comparison results when a jitter in the 
TSTEP measurement occurs. The upper switching velocity is higher by 1/16, resp. 1/32 of the value set 
as threshold. The StealthChop threshold TPWMTHRS is not shown. It can be included with VPWMTHRS 
< VCOOLTHRS. 
 
high velocity fullstep
microstep   +    coolStep
microstep   +    coolStep
microstepping
microstepping
motor stand still
motor going to standby
motor in standby
motor in standby
v
t
VSTOP
VSTART
0
V1
VMAX
AMAX
DMAX
D1
A1
VACTUAL
VCOOLTHRS
VHIGH
current
TZEROWAIT
RMS current
I_HOLD
I_RUN
dI * IHOLDDELAY
coolStep current reduction
 
Figure 12.3 Ramp generator velocity dependent motor control 
The velocity thresholds for the different chopper modes and sensorless operation features are coupled 
to the time between each two microsteps TSTEP. 


<!-- detected tables -->

|  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|
| y |  | Step | ep | Step |  |  | dby | y |
| standb | epping | + cool A M A X | ity fullst | cool + X A M D | epping | and still | to stan | standb |
| motor in | microst | A1 ostep | gh veloc | ostep D1 | microst | motor st | or going | motor in |
|  |  | micr | hi | micr |  |  | mot |  |
|  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  | t |  |
|  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  | IT | AY |  |
