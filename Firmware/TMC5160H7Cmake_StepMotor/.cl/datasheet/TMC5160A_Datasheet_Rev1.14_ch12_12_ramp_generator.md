# TMC5160A_Datasheet_Rev1.14 — 第12章 12 Ramp Generator

--- [PAGE 81] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  81 
 
 
 
www.trinamic.com 
12 Ramp Generator 
The ramp generator allows m otion based on target position or target velocity. It automatically 
calculates the optimum  motion profile taking into account acceleration and velocity settings. The 
TMC5160 integrates a new type of ramp generator, which offers faster machine operation com pared to 
the classical linear acceleration ramps. The sixPoint ramp generator allows adapt ing the acceleration 
ramps to the torque curves of a stepper motor and uses two different acceleration settings each for 
the acceleration phase and for the deceleration phase. See Figure 12.2. 
12.1 Real World Unit Conversion 
The TMC5160 uses its internal or external clock signal as a time reference for all internal operations. 
Thus, all time, velocity and acceleration settings are r eferenced to f CLK. For best stability and 
reproducibility, it is recommended to use an external quartz oscillator as a time base, or to provide a 
clock signal from a microcontroller. 
 
The units of a TMC5160 register content are written as register[5160].  
 
PARAMETER VS. UNITS 
Parameter / Symbol Unit calculation / description / comment 
fCLK[Hz] [Hz] clock frequency of the TMC5160 in [Hz] 
s [s] second 
US µstep  
FS fullstep  
µstep velocity v[Hz] µsteps / s v[Hz] = v[5160] * ( fCLK[Hz]/2 / 2^23 ) 
µstep acceleration a[Hz/s] µsteps / s^2 a[Hz/s] = a[5160] * fCLK[Hz]^2 / (512*256) / 2^24 
USC microstep count counts 
microstep resolution in number of microsteps 
(i.e. the number of microsteps between two 
fullsteps – normally 256) 
rotations per second v[rps]  rotations / s v[rps] = v[µsteps/s] / USC / FSC 
FSC: motor fullsteps per rotation, e.g. 200 
rps acceleration a[rps/s^2] rotations / s^2 a[rps/s^2] = a[µsteps/s^2] / USC / FSC 
ramp steps[µsteps] = rs µsteps 
rs = (v[5160])^2 / a[5160] / 2^8 
microsteps during linear acceleration ramp  
(assuming acceleration from 0 to v) 
TSTEP, T…THRS - 
TSTEP = fCLK / fSTEP 
The time reference for velocity thresholds is 
referred to the actual microstep frequency of 
the clock input respectively velocity v[Hz].  
 
In rare cases, the upper acceleration limit might impose a limitation to the application, e.g. when 
working with a reduced clock frequency  or high gearing and low load on the motor . In order to 
increase the effective acceleration possible , the microstep resolution of the sequencer input may be 
decreased. Setting the CHOPCONF options intpol=1 and MRES=%0001 will double the motor velocity for 
the same speed setting and thus also double effective acceleration and deceleration. The motor will 
have the same smoothness, but half position resolution with this setting.  
 
Quick Start 
For a quick start, see the Quick Configuration Guide in chapter 22. 
  
--- [PAGE 82] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  82 
 
 
 
www.trinamic.com 
12.2 Motion Profiles 
For the ramp generator register set, please refer to the chapter 6.3. 
 
12.2.1 Ramp Mode 
The ramp generator delivers two phase acceleration and two phase decelerati on ramps with 
additional programmable start and stop velocities (see Figure 12.1).  
 
 
 
 
 
 
 
The two different sets of acceleration and deceleration can be combined freely. A common transition 
speed V1 allows for velocity dependent switching between both acceleration and deceleration 
settings. A typical use case will use lower acceleration and deceleration values at higher velocities, as 
the motors torque declines at higher velocity. When considering friction in the system, it becomes 
clear, that typically deceleration of the system is quicker than acceleration. Thus, deceleration values 
can be higher in many applications. This way, ope ration speed of the motor in time critical 
applications can be maximized.  
As target positions and ramp parame ters may be changed any time during the motion, the motion 
controller will always use the optimum (fastest) way to reach the target, while stickin g to the 
constraints set by the user. This way it might happen, that the motion becomes automatically 
stopped, crosses zero and drives back again. This case is flagged by the special flag second_move. 
 
12.2.2 Start and Stop Velocity 
When using increased levels of start- and stop velocity, it becomes clear, that a subsequent move into 
the opposite direction would provide a jerk identical to VSTART+VSTOP, rather than only VSTART. As 
the motor probably is not able to follow this, you can set a time delay for a subseq uent move by 
setting TZEROWAIT. An active delay time is flagged by the flag t_zerowait_active. Once the target  
position is reached, the flag position_reached becomes active. 
 
v
t
acceleration phase deceleration phasemotor 
stop
VSTOP
VSTART
0
V1
VMAX
AMAX DMAX
D1
A1
-A1
TZEROWAIT
acceleration 
phase
VACTUAL
 
Figure 12.1 Ramp generator velocity trace showing consequent move in negative direction 
 
Note 
The start velocity can be set to zero, if not used.  
The stop velocity can be set to ten (or down to one), if not used.  
Take care to set VSTOP identical to or above VSTART. This ensures that even a short motion  can 
be terminated successfully at the target position.  
--- [PAGE 83] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  83 
 
 
 
www.trinamic.com 
Torque for VSTART Torque available for 
AMAX
Torque available for acceleration A1
Torque required 
for static loads
torque
velocity [RPM]
0
MFRICT
MMAX
VMAX
MFRICT Portion of torque required for friction and static load within the system
MMAX Motor pull-out torque at v=0
motor torque
MNOM2
high acceleration
reduced accel.
V1
MNOM1
MNOM1/2 Torque available at V1 resp. VMAX
Motor torque used in acceleration phase
high deceleration
reduced decel.2xMFRICT
Overall torque usable for deceleration
VSTART
 
Figure 12.2 Illustration of optimized motor torque usage with TMC5160 ramp generator 
 
12.2.3 Velocity Mode 
For the ease of use, velocity mode movements do not use the different acceleration and deceleration 
settings. You need to set VMAX and AMAX only for velocity mode. The ramp generator always uses 
AMAX to accelerate or decelerate to VMAX in this mode.  
In order to decelerate the motor to stand still, it is sufficient to set VMAX to zero. The flag vzero 
signals standstill of the motor. The flag velocity_reached always signals, that the target velocity has 
been reached.  
 
12.2.4 Early Ramp Termination 
In cases where users can interact with a system, some applications require terminating a motion by 
ramping down to zero velocity before the target position has been reached.  
 
OPTIONS TO TERMINATE MOTION USING ACCELERATION SETTINGS:  
a) Switch to velocity mode, set VMAX=0 and AMAX to the desired deceleration  value. This will stop 
the motor using a linear ramp.  
b) For a stop in positioning mode, set VSTART=0 and VMAX=0. VSTOP is not used in this case. The 
driver will use AMAX and A1 (as determined by V1) for going to zero velocity, unless the ramp is 
already in the deceleration phase to stop at the target position.  
c) For a stop using D1, DMAX and VSTOP, trigger the deceleration phase  by copying XACTUAL to 
XTARGET. Set TZEROWAIT sufficiently to allow the CPU to interact during this time . The driver will 
decelerate and eventually come to a stop. Poll the actual velocity to terminate motion during 
TZEROWAIT time using option a) or b). 
d) Activate a stop switch. This can b e done by means of the hardware input, e.g. using a wired 'OR' 
to the stop switch input. If you do not use the hardware input and have tied t he REFL and REFR 
to a fixed level, enable  the stop function ( stop_l_enable, stop_r_enable) and use the inverting 
function (pol_stop_l, pol_stop_r) to simulate the switch activation. 
 
--- [PAGE 84] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  84 
 
 
 
www.trinamic.com 
12.2.5 Application Example: Joystick Control 
Applications like surveillance came ras can be optimally enhanced using the motion controller: while 
joystick commands operate the motor at a user defined velocity, the target ramp generator ensures 
that the valid motion range never is left.  
 
REALIZE JOYSTICK CONTROL 
1. Use positioning mode in order to control the motion direction and to set the motion limit(s). 
2. Modify VMAX at any time in the range VSTART to your maximum value. With VSTART=0, you can 
also stop motion by setting VMAX=0. The motion controller will use A1 and AMAX as determined 
by V1 to adapt velocity for ramping up and ramping down.  
3. In case you do not modify the acceleration settings, you do not need to rewrite XTARGET, just 
modify VMAX.  
4. DMAX, D1 and VSTOP only become used when the ramp controller slows down due to reaching 
the target position, or when the target position has been modified to point to the other direction. 
12.3 Velocity Thresholds 
The ramp generator provides a number of velocity thresholds coupled with the actual velocity 
VACTUAL. The different ranges allow programming the motor to the optimum step mode, coil current 
and acceleration settings. Most applications will not require all of the thresholds, but in principle all 
modes can be combined as shown in Figure 12.1. VHIGH and VCOOLTHRS are determin ed by the 
settings THIGH and TCOOLTHRS in order to allow determination of the velocity when an external step 
source is used. TSTEP becomes compared to these threshold values. A hysteresis of 1/16 TSTEP resp. 
1/32 TSTEP is applied to avoid continuous toggli ng of the comparison results when a jitter in the 
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
AMAX DMAX
D1A1
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
--- [PAGE 85] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  85 
 
 
 
www.trinamic.com 
12.4 Reference Switches 
Prior to normal operation of the drive an absolute reference position must be set. The r eference 
position can be found using a mechanical stop which can be detected by stall detection, or by a 
reference switch.  
In case of a linear drive, the mechanical motion range must not be left. This can be ensured also for 
abnormal situations by enabling the stop switch functions for the left and the right reference switch. 
Therefore, the ramp generator responds t o a number of stop events as configured in the SW_MODE 
register. There are two ways to stop the motor: 
- It can be stopped abruptly, when a switch is hit. This is useful in an emergency case and for 
StallGuard based homing. 
- Or the motor can be softly decelerated to zero using deceleration settings (DMAX, V1, D1).  
 
Hint 
Latching of the ramp position XACTUAL to the holding register XLATCH upon a switch event gives a 
precise snapshot of the position of the reference switch. 
 
+VCC_IO
REFL
Traveler
Motor
+VCC_IO
REFR
Negative 
direction
Positive 
direction
10k10k
22k
1nF
Optional RC filter 
(example)
 
Figure 12.4 Using reference switches (example) 
Normally open or normally closed switches ca n be used by programming the switch polarity or 
selecting the pullup or pull -down resistor configuration. A normally closed switch is failsafe with 
respect to an interrupt of the switch connection. Switches which can be used are: 
- mechanical switches,  
- photo interrupters, or  
- hall sensors.  
 
Be careful to select reference switch resistors matching your switch requirements!  
In case of long cables additional RC filtering might be required near the TMC 5160 reference inputs. 
Adding an RC filter will also reduce the danger of destroying the logic level inputs by wiring faults, 
but it will add a certain delay which should be considered with respect to the application.  
 
IMPLEMENTING A HOMING PROCEDURE 
1. Make sure, that the home switch is not pressed, e.g. by moving away from the switch.  
2. Activate position latching upon the desired switch event and activate motor (soft) stop upon 
active switch. StallGuard based homing requires using a hard stop (en_softstop=0). 
3. Start a motion ramp into the direction of the switch. (Move to a more negative position for a left 
switch, to a more positive position for a right switch). You may timeout this moti on by using a 
position ramping command. 
--- [PAGE 86] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  86 
 
 
 
www.trinamic.com 
4. As soon as the switch is hit, the pos ition becomes latched and the motor is stopped. Wait until 
the motor is in standstill again by polling the actual velocity VACTUAL or checking vzero or the 
standstill flag.  
5. Switch the ramp generator to hold mode and calculate the difference between the latched 
position and the actual position. For StallGuard based homing or when using hard stop, XACTUAL 
stops exactly at the home position, so there is no difference (0). 
6. Write the calculated difference into the actual position register. Now, homing is fini shed. A move 
to position 0 will bring back the motor exactly to the switching point. In case StallGuard was 
used for homing, read and write back RAMP_STAT to clear the StallGuard stop event event_stop_sg 
and release the motor from the stop condition.  
 
HOMING WITH A THIRD SWITCH 
Some applications use an additional home switch, which operates independently of the mechanical 
limit switches. The encoder functionality of the TMC51 60 provides an additional source for position 
latching. It allows using the N channel input to snapshot XACTUAL with a rising or falling edge event, 
or both. This function also provides an interrupt output. 
 
1. Activate the latching function ( ENCMODE: Set ignoreAB, clr_cont, neg_edge or pos_edge and 
latch_x_act). The latching function can then trigger the interrupt output (check by reading n_event 
in ENC_STATUS when interrupt is signaled at DIAG0). 
2. Move to the direction, where the N channel switch should be. I n case the motor hits a stop 
switch (REFL or REFR) before the home switch is detected, reverse the motion direction. 
3. Read out XLATCH once the switch has been triggered. It gives the position of the switch event. 
4. After detection of the switch event, stop the motor, and subtract XLATCH from the actual position. 
Read and write back ENC_STAT to clear the status flags. (A detailed description of the required 
steps is in the homing procedure above.)   
