# TMC5160A_Datasheet_Rev1.14 — 第12章 · p83

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
83 
 
 
 
www.trinamic.com 
Torque for VSTART
Torque available for 
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
MFRICT 
Portion of torque required for friction and static load within the system
MMAX 
Motor pull-out torque at v=0
motor torque
MNOM2
high acceleration
reduced accel.
V1
MNOM1
MNOM1/2 Torque available at V1 resp. VMAX
Motor torque used in acceleration phase
high deceleration
reduced decel.
2xMFRICT
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
a) Switch to velocity mode, set VMAX=0 and AMAX to the desired deceleration value. This will stop 
the motor using a linear ramp.  
b) For a stop in positioning mode, set VSTART=0 and VMAX=0. VSTOP is not used in this case. The 
driver will use AMAX and A1 (as determined by V1) for going to zero velocity, unless the ramp is 
already in the deceleration phase to stop at the target position.  
c) 
For a stop using D1, DMAX and VSTOP, trigger the deceleration phase by copying XACTUAL to 
XTARGET. Set TZEROWAIT sufficiently to allow the CPU to interact during this time. The driver will 
decelerate and eventually come to a stop. Poll the actual velocity to terminate motion during 
TZEROWAIT time using option a) or b). 
d) Activate a stop switch. This can be done by means of the hardware input, e.g. using a wired 'OR' 
to the stop switch input. If you do not use the hardware input and have tied the REFL and REFR 
to a fixed level, enable the stop function (stop_l_enable, stop_r_enable) and use the inverting 
function (pol_stop_l, pol_stop_r) to simulate the switch activation. 
 


<!-- detected tables -->

|  | high deceleration 2xM FRICT m o to to r rq u e high acceleration | reduced decel. | VMAX |
|---|---|---|---|
| Torque for VSTART |  | reduced accel. |  |
|  | Torque available for acceleration A1 |  |  |
|  |  | Torque available for AMAX |  |
|  | VSTART Torque required for static loads | V1 |  |
