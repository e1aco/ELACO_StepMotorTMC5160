# TMC5160A_Datasheet_Rev1.14 — 第22章 QUICK CONFIGURATION GUIDE

--- [PAGE 111] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
111 
 
 
 
www.trinamic.com 
22 Quick Configuration Guide 
This guide is meant as a practical tool to come to a first configuration and do a minimum set of 
measurements and decisions for tuning the driver. It does not cover all advanced functionalities, but 
concentrates on the basic function set to make a motor run smoothly. Once the motor runs, you may 
decide to explore additional features, e.g. freewheeling and further functionality in more detail. A 
current probe on one motor coil is a good aid to find the best settings, but it is not a must.  
 
CURRENT SETTING AND FIRST STEPS WITH STEALTHCHOP 
 
Current Setting
Set I_RUN as desired up 
to 31, I_HOLD  70% of 
I_RUN or lower
Set I_HOLD_DELAY to 1 
to 15 for smooth 
standstill current decay 
Set TPOWERDOWN up 
to 255 for delayed 
standstill current 
reduction
Configure Chopper to 
test current settings
Check hardware 
setup and motor 
RMS current
GCONF
set en_pwm_mode
stealthChop 
Configuration
PWMCONF
set pwm_autoscale, 
set pwm_autograd
PWMCONF
select PWM_FREQ with 
regard to fCLK for 20-
40kHz PWM frequency
CHOPCONF
Enable chopper using basic 
config., e.g.: TOFF=5, TBL=2, 
HSTART=4, HEND=0
Move the motor by 
slowly accelerating 
from 0 to VMAX 
operation velocity
Is performance 
good up to VMAX?
Select a velocity 
threshold for switching 
to spreadCycle chopper 
and set TPWMTHRS
N
SC2
Y
Execute 
automatic 
tuning 
procedure AT
Set GLOBALSCALER as 
required to reach 
maximum motor current 
at I_RUN=31
 
Figure 22.1 Current setting and first steps with StealthChop 
 
 
 
 


<!-- detected tables -->

|  | Execute automatic tuning procedure AT |  |
|---|---|---|

|  | Move the motor by slowly accelerating from 0 to VMAX operation velocity |  |
|---|---|---|
--- [PAGE 112] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
112 
 
 
 
www.trinamic.com 
TUNING STEALTHCHOP AND SPREADCYCLE 
 
SC2
Try motion above 
TPWMTRHRS, if 
used
Coil current  
overshoot upon 
deceleration?
PWMCONF
decrease PWM_LIM (do 
not go below about 5)
Y
Optimize spreadCycle 
configuration if TPWMTHRS 
used
N
Go to motor stand 
still and check 
motor current at 
IHOLD=IRUN
Stand still current 
too high?
N
CHOPCONF, PWMCONF
decrease TBL or PWM 
frequency and check 
impact on motor motion
Y
GCONF
en_pwm_mode=0
spreadCycle 
Configuration
CHOPCONF
Enable chopper using basic 
config.: TOFF=5, TBL=2, 
HSTART=0, HEND=0
Move the motor by 
slowly accelerating 
from 0 to VMAX 
operation velocity
Monitor sine wave motor 
coil currents with current 
probe at low velocity
CHOPCONF
increase HEND (max. 15)
Current zero 
crossing smooth?
N
Move motor very slowly or 
try at stand still
CHOPCONF
decrease TOFF (min. 2), 
try lower / higher TBL or 
reduce motor current
Audible Chopper 
noise?
Y
Y
Move motor at medium 
velocity or up to max. 
velocity
N
Audible Chopper 
noise?
CHOPCONF
decrease HEND and 
increase HSTART (max. 
7)
Y
Finished or enable 
coolStep
 
Figure 22.2 Tuning StealthChop and SpreadCycle 
 
 

--- [PAGE 113] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
113 
 
 
 
www.trinamic.com 
MOVING THE MOTOR USING THE MOTION CONTROLLER 
 
RAMPMODE
set velocity_positive
Set AMAX=1000, set 
VMAX=100000 or 
different values
Motor moves, change 
VMAX as desired
Move Motor
Configure Ramp 
Parameters
RAMPMODE
set position
Start Velocity
Set VSTART=0. Higher 
velcoity for abrupt start 
(limited by motor).
Stop Velocity
Set VSTOP=10, but not 
below VSTART. Higher 
velocity for abrupt stop.
Configure ramp 
parameters
Move to Target
Set XTARGET
New on-the-fly 
target?
Y
Event_POS_
reached active?
N
N
Y
Target is reached
Change of any 
parameter desired?
N
Set motion 
parameter as 
desired
Y
Set acceleration A1 as 
desired by application
Determine velocity, 
where max. motor 
torque or current sinks 
appreciably, write to V1
AMAX: Set lower 
acceleration than A1 to 
allow motor to 
accelerate up to VMAX
Set desired maximum 
velocity to VMAX
DMAX: Use same value 
as AMAX or higher
D1: Use same value as 
A1 or higher
Set TZEROWAIT to allow 
motor to recover from 
jump VSTOP to 0, before 
going to VSTART
Is VSTOP relevant 
(>>10)?
N
Y
Set TPOWERDOWN time 
not smaller than TZERO-
WAIT time. Min. value is 
TZEROWAIT/512
Ready to Move to 
Target
 
Figure 22.3 Moving the motor using the motion controller 
 
 
 


<!-- detected tables -->

| Move Motor |  |
|---|---|
| RAMPMODE set velocity positive _ |  |
|  |  |
| Set AMAX=1000, set VMAX=100000 or different values |  |
| Motor moves, change VMAX as desired |  |

|  | Configure ramp parameters |  |
|---|---|---|
--- [PAGE 114] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
114 
 
 
 
www.trinamic.com 
ENABLING COOLSTEP (ONLY IN COMBINATION WITH SPREADCYCLE) 
 
Enable coolStep
Move the motor by 
slowly accelerating 
from 0 to VMAX 
operation velocity
Does SG_RESULT go down 
to 0 with load?
Monitor SG_RESULT value 
during medium velocity and 
check response with 
mechanical load
Is coil current sine-
shaped at VMAX?
Decrease VMAX
N
Y
Increase SGT
Y
COOLCONF
Enable coolStep basic config.: 
SEMIN=1, all other 0
N
Set THIGH
To match TSTEP at 
VMAX for upper 
coolStep velocity limit
Set TCOOLTHRS
slightly above TSTEP at 
the selected velocity for 
lower velocity limit
Monitor CS_ACTUAL during 
motion in velocity range 
and check response with 
mechanical load
Does CS_ACTUAL reach 
IRUN with load before 
motor stall?
Increase SEMIN or 
choose narrower 
velocity limits
N
C2
C2
Monitor CS_ACTUAL and 
motor torque during rapid 
mechanical load increment 
within application limits
Does CS_ACTUAL reach 
IRUN with load before 
motor stall?
Increase SEUP
N
Finished
 
Figure 22.4 Enabling CoolStep (only in combination with SpreadCycle) 


<!-- detected tables -->

|  | Move the motor by slowly accelerating from 0 to VMAX operation velocity |  |
|---|---|---|
--- [PAGE 115] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
115 
 
 
 
www.trinamic.com 
SETTING UP DCSTEP 
 
Enable dcStep
Does the motor reach 
VMAX and have good 
torque?
Start the motor at the 
targeted velocity VMAX and 
try to apply load
Increase DC_TIME
N
Y
CHOPCONF
Make sure, that TOFF is not less 
than 3. Use lowest good TBL.
Set vhighfs and vhighchm
Set TCOOLTHRS
to match TSTEP at a velocity 
slightly above VDCMIN for lower 
stallGuard velocity limit
Set VDCMIN
to about 5% to 20% of 
the desired operation 
velocity
DCCTRL 
Set DC_TIME depending on TBL: 
%00: 17; %01: 25 
%10: 37; %11: 55
Does the motor reach 
VDCMIN without step loss?
Restart the motor and try to 
slow it down to VDCMIN by 
applying load
Decrease DC_TIME 
or increase TOFF
or increase VDCMIN
N
Y
DCCTRL
Set DC_SG to 1 + 1/16 
the value of DC_TIME
SW_MODE
Enable sg_stop to stop 
the motor upon stall 
detection
Finished or configure 
dcStep stall detection
Configure dcStep Stall 
Detection
Does the motor stop upon 
the first stall?
Slow down the motor to 
VDCMIN by applying load. 
Further increase load to 
stall the motor.
Increase DC_SG
N
Y
Read out RAMP_STAT to 
clear event_stop_sg and 
restart the motor
Accelerate the motor from 
0 to VMAX
Does the motor stop during 
acceleration?
Decrease 
TCOOLTHRS to raise 
the lower velocity 
for stallGuard
Y
N
Finished
 
Figure 22.5 Setting up DcStep 
 
 
 

