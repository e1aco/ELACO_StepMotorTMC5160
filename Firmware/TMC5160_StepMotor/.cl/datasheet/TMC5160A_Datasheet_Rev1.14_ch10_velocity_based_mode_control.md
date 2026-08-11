# TMC5160A_Datasheet_Rev1.14 — 第10章 VELOCITY BASED MODE CONTROL

--- [PAGE 76] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
76 
 
 
 
www.trinamic.com 
10 Velocity Based Mode Control 
The TMC5160 allows the configuration of different chopper modes and modes of operation for 
optimum motor control. Depending on the motor load, the different modes can be optimized for 
lowest noise & high precision, highest dynamics, or maximum torque at highest velocity. Some of the 
features like CoolStep or StallGuard2 are useful in a limited velocity range. A number of velocity 
thresholds allow combining the different modes of operation within an application requiring a wide 
velocity range.  
 
option
option
option
option
option
option
option
microstep
microstep
high velocity fullstep
microstep + coolStep
microstep + coolStep
microstepping
microstepping
motor stand still
motor going to standby
motor in standby
motor in standby
v
t
VPWMTHRS+Δ 
VPWMTHRS
0
VCOOLTHRS+Δ 
VHIGH+Δ 
VACTUAL
~1/TSTEP
VCOOLTHRS
VHIGH
current
TZEROWAIT
RMS current
I_HOLD
I_RUN
dI * IHOLDDELAY
coolStep current reduction
stealthChop
spreadCycle
const. Toff
Chopper mode
TRINAMIC, B. Dwersteg, 14.3.14
 
Figure 10.1 Choice of velocity dependent modes 
Figure 10.1 shows all available thresholds and the required ordering. VPWMTHRS, VHIGH and 
VCOOLTHRS are determined by the settings TPWMTHRS, THIGH and TCOOLTHRS. The velocity is 
described by the time interval TSTEP between each two step pulses. This allows determination of the 
velocity when an external step source is used. TSTEP always becomes normalized to 256 
microstepping. This way, the thresholds do not have to be adapted when the microstep resolution is 
changed. The thresholds represent the same motor velocity, independent of the microstep settings. 
TSTEP becomes compared to these threshold values. A hysteresis of 1/16 TSTEP resp. 1/32 TSTEP is 
applied to avoid continuous toggling of the comparison results when a jitter in the TSTEP 
measurement occurs. The upper switching velocity is higher by 1/16, resp. 1/32 of the value set as 
threshold. The StealthChop threshold TPWMTHRS is not shown. It can be included with VPWMTHRS < 
VCOOLTHRS. The motor current can be programmed to a run and a hold level, dependent on the 
standstill flag stst.  
 
Using automatic velocity thresholds allows tuning the application for different velocity ranges. 
Features like CoolStep will integrate completely transparently in your setup. This way, once 
parameterized, they do not require any activation or deactivation via software. 
 


<!-- detected tables -->

| Chopper mode |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
| stealthChop |  |  |  |  |  |  |  |  |  |  |  |
| spreadCycle | option |  |  |  | option |  |  | option |  |  |  |
| const. Toff option option v VHIGH+Δ coolStep VHIGH standby microstepping microstep VCOOLTHRS+Δ + in microstep VCOOLTHRS motor VPWMTHRS+Δ VPWMTHRS 0 current I RUN _ I HOLD _ | option |  | option |  |  | option |  | option |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  | by |  |
|  |  |  |  | ep | ep | ep |  |  |  | d |  |
|  | standby | ostep | tepping | + coolSt | ity fullst | + coolSt | tepping | ostep | tand still | g to stan | standby |
|  | in | cr | s | p | oc | p | s | cr | s | n | in |
|  | otor | mi | micro | oste | vel | oste | micro | mi | otor | goi | otor |
|  |  |  |  | cr | h | cr |  |  | m | or |  |
|  | m |  |  | mi | hig | mi |  |  |  | mot | m |
|  |  |  |  |  |  |  |  |  |  |  | t |
|  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  | IT | AY |  |
--- [PAGE 77] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
77 
 
 
 
www.trinamic.com 
Parameter 
Description 
Setting Comment 
stst 
This flag indicates motor stand still in each operation 
mode. This occurs 2^20 clocks after the last step pulse. 
0/1 
Status bit, read only 
TPOWER 
DOWN 
This is the delay time after stand still (stst) of the 
motor to motor current power down. Time range 
is about 0 to 4 seconds. 
0…255 
Time in multiples of 2^18 
tCLK 
TSTEP 
Actual 
measured 
time 
between 
two 
1/256 
microsteps derived from the step input frequency 
in units of 1/fCLK. Measured value is (2^20)-1 in 
case of overflow or stand still.  
0… 
1048575 
Status register, read only. 
Actual measured step time 
in multiple of tCLK 
TPWMTHRS 
TSTEP ≥ TPWMTHRS 
- 
StealthChop PWM mode is enabled, if 
configured 
- 
DcStep is disabled 
0… 
1048575 
Setting to control the 
upper velocity threshold 
for operation in 
StealthChop 
TCOOLTHRS 
TCOOLTHRS ≥ TSTEP ≥ THIGH: 
- 
CoolStep is enabled, if configured 
- 
StealthChop 
voltage 
PWM 
mode 
is 
disabled 
 
TCOOLTHRS ≥ TSTEP 
- 
Stop on stall and stall output signal is 
enabled, if configured 
0… 
1048575 
Setting to control the 
lower velocity threshold 
for operation with 
CoolStep and StallGuard 
THIGH 
TSTEP ≤ THIGH:  
- 
CoolStep is disabled (motor runs with 
normal current scale) 
- 
StealthChop 
voltage 
PWM 
mode 
is 
disabled 
- 
If vhighchm is set, the chopper switches 
to chm=1 with TFD=0 (constant off time 
with slow decay, only). 
- 
If vhighfs is set, the motor operates in 
fullstep mode and the stall detection 
becomes switched over to DcStep stall 
detection. 
0… 
1048575 
Setting to control the 
upper threshold for 
operation with CoolStep 
and StallGuard as well as 
optional high velocity step 
mode 
small_ 
hysteresis 
Hysteresis for step frequency comparison based 
on 
TSTEP 
(lower 
velocity 
threshold) 
and 
(TSTEP*15/16)-1 respectively (TSTEP*31/32)-1 (upper 
velocity threshold) 
0 
Hysteresis is 1/16 
1 
Hysteresis is 1/32 
vhighfs 
This bit enables switching to fullstep, when VHIGH 
is exceeded. Switching takes place only at 45° 
position. The fullstep target current uses the 
current value from the microstep table at the 45° 
position. 
0 
No switch to fullstep 
1 
Fullstep at high velocities 
vhighchm 
This bit enables switching to chm=1 and fd=0, when 
VHIGH is exceeded. This way, a higher velocity can 
be achieved. Can be combined with vhighfs=1. If set, 
the TOFF setting automatically becomes doubled 
during high velocity operation in order to avoid 
doubling of the chopper frequency. 
0 
No change of chopper 
mode 
1 
Classic const. Toff chopper 
at high velocities 
en_pwm_ 
mode 
 
StealthChop voltage PWM enable flag (depending 
on velocity thresholds). Switch from off to on 
state while in stand still, only.  
0 
No StealthChop 
1 
StealthChop below 
VPWMTHRS 
 
 


<!-- detected tables -->

|  | Parameter |  |  | Description |  |  | Setting |  |  | Comment |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
| stst | stst |  | This flag indicates motor stand still in each operation mode. This occurs 2^20 clocks after the last step pulse. |  |  | 0/1 |  |  | Status bit, read only |  |  |
| TPOWER DOWN |  |  | This is the delay time after stand still (stst) of the motor to motor current power down. Time range is about 0 to 4 seconds. |  |  | 0…255 |  |  | Time in multiples of 2^18 t CLK |  |  |
| TSTEP |  |  | Actual measured time between two 1/256 microsteps derived from the step input frequency in units of 1/fCLK. Measured value is (2^20)-1 in case of overflow or stand still. |  |  | 0… 1048575 |  |  | Status register, read only. Actual measured step time in multiple of t CLK |  |  |
| TPWMTHRS |  |  | TSTEP ≥ TPWMTHRS - StealthChop PWM mode is enabled, if configured - DcStep is disabled |  |  | 0… 1048575 |  |  | Setting to control the upper velocity threshold for operation in StealthChop |  |  |
| TCOOLTHRS |  |  | TCOOLTHRS ≥ TSTEP ≥ THIGH: - CoolStep is enabled, if configured - StealthChop voltage PWM mode is disabled TCOOLTHRS ≥ TSTEP - Stop on stall and stall output signal is enabled, if configured |  |  | 0… 1048575 |  |  | Setting to control the lower velocity threshold for operation with CoolStep and StallGuard |  |  |
| THIGH |  |  | TSTEP ≤ THIGH: - CoolStep is disabled (motor runs with normal current scale) - StealthChop voltage PWM mode is disabled - If vhighchm is set, the chopper switches to chm=1 with TFD=0 (constant off time with slow decay, only). - If vhighfs is set, the motor operates in fullstep mode and the stall detection becomes switched over to DcStep stall detection. |  |  | 0… 1048575 |  |  | Setting to control the upper threshold for operation with CoolStep and StallGuard as well as optional high velocity step mode |  |  |
| small _ hysteresis |  |  | Hysteresis for step frequency comparison based on TSTEP (lower velocity threshold) and (TSTEP*15/16)-1 respectively (TSTEP*31/32)-1 (upper velocity threshold) |  |  | 0 |  |  | Hysteresis is 1/16 |  |  |
|  |  |  |  |  |  | 1 |  |  | Hysteresis is 1/32 |  |  |
| vhighfs |  |  | This bit enables switching to fullstep, when VHIGH is exceeded. Switching takes place only at 45° position. The fullstep target current uses the current value from the microstep table at the 45° position. |  |  | 0 |  |  | No switch to fullstep |  |  |
|  |  |  |  |  |  | 1 |  |  | Fullstep at high velocities |  |  |
| vhighchm |  |  | This bit enables switching to chm=1 and fd=0, when VHIGH is exceeded. This way, a higher velocity can be achieved. Can be combined with vhighfs=1. If set, the TOFF setting automatically becomes doubled during high velocity operation in order to avoid doubling of the chopper frequency. |  |  | 0 |  |  | No change of chopper mode |  |  |
|  |  |  |  |  |  | 1 |  |  | Classic const. Toff chopper at high velocities |  |  |
| en pwm _ _ mode |  |  | StealthChop voltage PWM enable flag (depending on velocity thresholds). Switch from off to on state while in stand still, only. |  |  | 0 |  |  | No StealthChop |  |  |
|  |  |  |  |  |  | 1 |  |  | StealthChop below VPWMTHRS |  |  |
