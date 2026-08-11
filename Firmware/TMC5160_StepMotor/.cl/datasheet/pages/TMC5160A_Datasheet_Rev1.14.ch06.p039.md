# TMC5160A_Datasheet_Rev1.14 — 第6章 · p39

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
39 
 
 
 
www.trinamic.com 
VELOCITY DEPENDENT DRIVER FEATURE CONTROL REGISTER SET (0X10…0X1F)  
R/W 
Addr 
n 
Register 
Description / bit names 
W 
0x13 
20 
TPWMTHRS 
This is the upper velocity for StealthChop voltage PWM mode.  
TSTEP ≥ TPWMTHRS 
- 
StealthChop PWM mode is enabled, if configured 
- 
DcStep is disabled 
W 
0x14 
20 
TCOOLTHRS 
This is the lower threshold velocity for switching on smart 
energy CoolStep and StallGuard feature. (unsigned)  
 
Set this parameter to disable CoolStep at low speeds, where it 
cannot work reliably. The stop on stall function (enable with 
sg_stop when using internal motion controller) and the stall 
output signal become enabled when exceeding this velocity. In 
non-DcStep mode, it becomes disabled again once the velocity 
falls below this threshold. 
 
TCOOLTHRS ≥ TSTEP ≥ THIGH: 
- 
CoolStep is enabled, if configured 
- 
StealthChop voltage PWM mode is disabled 
 
TCOOLTHRS ≥ TSTEP 
- 
Stop on stall is enabled, if configured 
- 
Stall output signal (DIAG0/1) is enabled, if configured 
W 
0x15 
20 
THIGH 
This velocity setting allows velocity dependent switching into 
a different chopper mode and fullstepping to maximize torque. 
(unsigned) 
The stall detection feature becomes switched off for 2-3 
electrical periods whenever passing THIGH threshold to 
compensate for the effect of switching modes. 
 
TSTEP ≤ THIGH:  
- 
CoolStep is disabled (motor runs with normal current 
scale) 
- 
StealthChop voltage PWM mode is disabled 
- 
If vhighchm is set, the chopper switches to chm=1 
with TFD=0 (constant off time with slow decay, only). 
- 
If vhighfs is set, the motor operates in fullstep mode 
and the stall detection becomes switched over to 
DcStep stall detection. 
 
Microstep velocity time reference t for velocities: TSTEP = fCLK / fSTEP 
 
 


<!-- detected tables -->

|  | VELOCITY DEPENDENT DRIVER FEATURE CONTROL REGISTER SET (0X10…0X1F) |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | R/W |  |  | Addr |  |  | n |  |  | Register |  |  | Description / bit names |  |
| W |  |  | 0x13 |  |  | 20 |  |  | TPWMTHRS |  |  | This is the upper velocity for StealthChop voltage PWM mode. TSTEP ≥ TPWMTHRS - StealthChop PWM mode is enabled, if configured - DcStep is disabled |  |  |
| W |  |  | 0x14 |  |  | 20 |  |  | TCOOLTHRS |  |  | This is the lower threshold velocity for switching on smart energy CoolStep and StallGuard feature. (unsigned) Set this parameter to disable CoolStep at low speeds, where it cannot work reliably. The stop on stall function (enable with sg stop when using internal motion controller) and the stall _ output signal become enabled when exceeding this velocity. In non-DcStep mode, it becomes disabled again once the velocity falls below this threshold. TCOOLTHRS ≥ TSTEP ≥ THIGH: - CoolStep is enabled, if configured - StealthChop voltage PWM mode is disabled TCOOLTHRS ≥ TSTEP - Stop on stall is enabled, if configured - Stall output signal (DIAG0/1) is enabled, if configured |  |  |
| W |  |  | 0x15 |  |  | 20 |  |  | THIGH |  |  | This velocity setting allows velocity dependent switching into a different chopper mode and fullstepping to maximize torque. (unsigned) The stall detection feature becomes switched off for 2-3 electrical periods whenever passing THIGH threshold to compensate for the effect of switching modes. TSTEP ≤ THIGH: - CoolStep is disabled (motor runs with normal current scale) - StealthChop voltage PWM mode is disabled - If vhighchm is set, the chopper switches to chm=1 with TFD=0 (constant off time with slow decay, only). - If vhighfs is set, the motor operates in fullstep mode and the stall detection becomes switched over to DcStep stall detection. |  |  |
