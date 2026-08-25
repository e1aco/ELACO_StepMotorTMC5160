# TMC5160A_Datasheet_Rev1.14 — 第1章 · p77

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  77 
 
 
 
www.trinamic.com 
Parameter Description Setting Comment 
stst This flag indicates motor stand still in each operation 
mode. This occurs 2^20 clocks after the last step pulse. 
0/1 Status bit, read only 
TPOWER 
DOWN 
This is the delay time after stand still ( stst) of the 
motor to motor current po wer down. Time range 
is about 0 to 4 seconds. 
0…255 Time in multiples of 2^18 
tCLK 
TSTEP Actual measured time between two 1/256 
microsteps derived from the step input frequency 
in units of 1/fCLK. Measured value is (2 ^20)-1 in 
case of overflow or stand still.  
0… 
1048575 
Status register, read only. 
Actual measured step time 
in multiple of tCLK 
TPWMTHRS TSTEP ≥ TPWMTHRS 
- StealthChop PWM mode is enabled, if 
configured 
- DcStep is disabled 
0… 
1048575 
Setting to control the 
upper velocity threshold 
for operation in 
StealthChop 
TCOOLTHRS TCOOLTHRS ≥ TSTEP ≥ THIGH: 
- CoolStep is enabled, if configured 
- StealthChop voltage PWM mode is 
disabled 
 
TCOOLTHRS ≥ TSTEP 
- Stop on stall and stall output signal is 
enabled, if configured 
0… 
1048575 
Setting to control the 
lower velocity threshold 
for operation with 
CoolStep and StallGuard 
THIGH TSTEP ≤ THIGH:  
- CoolStep is disabled (mo tor runs with 
normal current scale) 
- StealthChop voltage PWM mode is 
disabled 
- If vhighchm is set, the chopper switches 
to chm=1 with TFD=0 (constant off time 
with slow decay, only). 
- If vhighfs is set, the motor operates in 
fullstep mode  and the stall detect ion 
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
on TSTEP (lower velocity threshold) and 
(TSTEP*15/16)-1 respectively (TSTEP*31/32)-1 (upper 
velocity threshold) 
0 Hysteresis is 1/16 
1 Hysteresis is 1/32 
vhighfs This bit enables switching to fullstep, when VHIGH 
is exceeded. Switching takes place only  at 45° 
position. The fullstep target current uses the 
current value from the microstep table at the 45° 
position. 
0 No switch to fullstep 
1 Fullstep at high velocities 
vhighchm This bit enables switching to chm=1 and fd=0, when 
VHIGH is exceeded. This  way, a higher velocity can 
be achieved. Can be combined with vhighfs=1. If set, 
the TOFF setting automatically becomes doubled 
during high velocity operation in order to avoid 
doubling of the chopper frequency. 
0 No change of chopper 
mode 
1 Classic const. Toff chopper 
at high velocities 
en_pwm_ 
mode 
 
StealthChop voltage PWM enable flag (depending 
on velocity thresholds). Switch from off to on 
state while in stand still, only.  
0 No StealthChop 
1 StealthChop below 
VPWMTHRS 
 
 
