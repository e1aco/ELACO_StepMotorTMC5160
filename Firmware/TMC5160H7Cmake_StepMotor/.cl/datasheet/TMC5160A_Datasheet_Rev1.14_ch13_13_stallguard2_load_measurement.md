# TMC5160A_Datasheet_Rev1.14 — 第13章 13 StallGuard2 Load Measurement

--- [PAGE 87] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  87 
 
 
 
www.trinamic.com 
13 StallGuard2 Load Measurement 
StallGuard2 provides an accurate measure ment of the load on the moto r. It can be used for stall 
detection as well as other uses at loads below those which stall the motor, such as CoolStep load-
adaptive current reduction. The StallGuard2 measurement value changes linearly over a wide range of 
load, velocity, and current se ttings, as shown in Figure 13.1. At maximum motor load, the value goes 
to zero or near to zero. This corresponds to a load angle of 90° between the magnetic field of the 
coils and magnets in the rotor. This also is the most energy-efficient point of operation for the motor. 
motor load 
(% max. torque)
stallGuard2 
reading
100
200
300
400
500
600
700
800
900
1000
0 10 20 30 40 50 60 70 80 90 100
Start value depends 
on motor and 
operating conditions
Motor stalls above this point. 
Load angle exceeds 90° and 
available torque sinks.
stallGuard value reaches zero 
and indicates danger of stall. 
This point is set by stallGuard 
threshold value SGT.
 
Figure 13.1 Function principle of StallGuard2 
Parameter Description Setting Comment 
SGT This signed value  controls the StallGuard2 
threshold level for stall detection and sets the 
optimum measurement range for readout. A 
lower value gives a higher sensitivity. Zero is the 
starting value working with most motors. A 
higher value makes StallGuard2 less sensitive and 
requires more torque to indicate a stall. 
0 indifferent value 
+1… +63 less sensitivity 
-1… -64 higher sensitivity 
sfilt Enables the StallGuard2 filter for more precision 
of the measurement. If set, reduces the 
measurement frequency to one measu rement per 
electrical period of the motor (4 fullsteps). 
0 standard mode 
1 filtered mode 
Status word Description Range Comment 
SG_RESULT This is the StallGuard2 result. A higher reading 
indicates less mechanical load. A lower reading 
indicates a highe r load and thus a higher load 
angle. Tune the SGT setting to show a SG_RESULT 
reading of roughly 0 to 100 at maximum load 
before motor stall. 
0… 1023 0: highest load 
low value: high load 
high value: less load 
 
Hint 
In order to use StallGuard2 and CoolStep, the StallGuard2 sensitivity should first be tuned using the 
SGT setting! 
  
--- [PAGE 88] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  88 
 
 
 
www.trinamic.com 
13.1 Tuning StallGuard2 Threshold SGT 
The StallGuard2 value SG_RESULT is affected by motor -specific characteristics and application -specific 
demands on load and velocity . Therefore the easiest way to tune the StallGuard2 threshold SGT for a 
specific motor type and operating conditions is interactive tuning in the actual application.  
INITIAL PROCEDURE FOR TUNING STALLGUARD SGT 
1. Operate the motor at the normal operation velocity for your application and monitor SG_RESULT. 
2. Apply slowly increasing mechanical load to the motor. If the motor stalls before SG_RESULT 
reaches zero, decrease SGT. If SG_RESULT reaches zero before the motor stalls, increase SGT. A 
good SGT starting value is zero. SGT is signed, so it can have negative or positive values. 
3. Set TCOOLTHRS to a value above TSTEP and enable sg_stop to enable the stop on stall feature. 
Make sure, that the motor is safely stopped whenever it is stalled. Increase SGT if the motor 
becomes stopped before a stall occurs.  Restart the motor by disabling sg_stop or by reading and 
writing back the RAMP_STAT register (write+clear function). 
4. The optimum setting is reached when SG_RESULT is between 0 and roughly 100 at increasing load 
shortly before the  motor stalls, and SG_RESULT increases by 100 or more without load. SGT in 
most cases can be tuned for a certain motion velocity or a velocity range . Make sure, that the 
setting works reliable in a certain range (e. g. 80% to 120% of desired velocity) and a lso under 
extreme motor conditions (lowest and highest applicable temperature). 
OPTIONAL PROCEDURE ALLOWING AUTOMATIC TUNING OF SGT 
The basic idea behind the SGT setting is a factor, which compensates the StallGuard measurement for 
resistive losses inside the motor. At standstill and very low velocities, resistive losses are the main 
factor for the balance of energy in the motor, because mechanical power is zero or near to zero. This 
way, SGT can be set to an optimum at near zero velocity. This algorithm is especially useful for tuning 
SGT within the application to give the best result independent of environment conditions, motor 
stray, etc.  
 
1. Operate the motor at low velocity < 10 RPM (i.e. a few to a few fullsteps p er second) and target 
operation current a nd supply voltage. In this velocity range, there is not much  dependence of 
SG_RESULT on the motor load, because the motor does not generate significant back EMF. 
Therefore, mechanical load will not make a big difference on the result.  
2. Switch on sfilt. Now increase SGT starting from 0 to a value, where SG_RESULT starts rising. With 
a high SGT, SG_RESULT will rise up to the maximum value . Reduce again to the highest value, 
where SG_RESULT stays at 0. Now the SGT value is set as sensibly as possible. When you  see 
SG_RESULT increasing at higher velocities, there will be useful stall detection.  
 
The upper velocity for the stall detection with this setting is determined by the velocity, where the 
motor back EMF approaches  the supply voltage and the motor current  starts dropping when further 
increasing velocity. 
 
SG_RESULT goes to zero when the motor stalls and the ramp generator can be programmed to stop 
the motor upon a stall event by enabling sg_stop in SW_MODE. Set TCOOLTHRS to match the lower 
velocity threshold where StallGuard delivers a good result in order to use sg_stop.  
 
The power supply voltage also affects SG_RESULT, so tighter voltage regulation results in more 
accurate values. StallGuard measurement has a high resolution, and there are a few ways to enhance 
its accuracy, as described in the following sections. 
 
Quick Start 
For a quick start, see the Quick Configuration Guide in chapter 22. 
For detail procedure see Application Note AN002 - Parameterization of StallGuard2 & CoolStep 
 
--- [PAGE 89] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  89 
 
 
 
www.trinamic.com 
13.1.1 Variable Velocity Limits TCOOLTHRS and THIGH 
The SGT setting chosen as a result of the previously described SGT tuning can be used for a certain 
velocity range. Outside this range, a stall may not be detected safely, and CoolStep might not give the 
optimum result.  
 
back EMF reaches 
supply voltage
optimum 
SGT setting
Motor RPM
(200 FS motor)
stallGuard2 
reading at 
no load
2
4
6
8
10
12
14
16
100
200
300
400
500
600
700
800
900
1000
18
20
0 0 50 100 150 200 250 300 350 400 450 500 550 600
lower limit for stall 
detection
good operation 
range with single 
SGT setting
 
Figure 13.2 Example: optimum SGT setting and StallGuard2 reading with an example motor 
In many applications, operation at or near a single operation point is used most of the time and a 
single setting is sufficient. The driver provides a lower and an upper velocity threshold to match this. 
The stall detection is disabled outside the determined operation point, e.g. during acceleration phases 
preceding a sensorl ess homing procedure  when setting TCOOLTHRS to a matching value. An upp er 
limit can be specified by THIGH. 
 
In some applications, a velocity dependent tuning of the SGT value can be expedient, using a small 
number of support points and linear interpolation.  
 
13.1.2 Small Motors with High Torque Ripple and Resonance 
Motors with a high detent torque show an increased variation of the StallGuard2 measurement value 
SG with varying motor currents, especially at low currents. For these motors, the current dependency 
should be checked for best result.  
 
13.1.3 Temperature Dependence of Motor Coil Resistance 
Motors working over a wide temperature range may require temperature correction, because motor 
coil resistance increases with rising temperature. This can be corrected as a linear reduction of SGT at 
increasing temperature, as motor efficiency is reduced. 
 
13.1.4 Accuracy and Reproducibility of StallGuard2 Measurement 
In a production environment, it may be desirable to use a fixed SGT value within an application for 
one motor type. Most of the unit -to-unit variation in StallGuard2 measurements results from manu -
facturing tolerances in motor construction. The measurement error of StallGuard2 – provided that all 
other parameters remain stable – can be as low as: 
 
𝑠𝑡𝑎𝑙𝑙𝐺𝑢𝑎𝑟𝑑 𝑚𝑒𝑎𝑠𝑢𝑟𝑒𝑚𝑒𝑛𝑡 𝑒𝑟𝑟𝑜𝑟 = ±𝑚𝑎𝑥(1, |𝑆𝐺𝑇|) 
--- [PAGE 90] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  90 
 
 
 
www.trinamic.com 
13.2 StallGuard2 Update Rate and Filter 
The StallGuard2 measurement value SG_RESULT is updated with each full step of the motor. This is 
enough to safely detect a stall, because a stall  always means the loss of four full steps. In a practical 
application, especially when using CoolStep, a more precise measurement might be more important 
than an update for each fullstep because the mechanical load never changes instantaneously from 
one step to the next. For these applications, the sfilt bit enables a filtering funct ion over four load 
measurements. The filter should always be enabled when high -precision measurement is required. It 
compensates for variations in motor construction, for exampl e due to misalignment of the phase A to 
phase B magnets. The filter should be disabled when rapid response  to increasing load is required 
and for best results of sensorless homing using StallGuard. 
13.3 Detecting a Motor Stall 
For best stall detection, work wit hout StallGuard filtering (sfilt=0). To safely detect a motor stall the 
stall threshold must be determined using a specific SGT setting. Therefore, the maximum load needs 
to be determined, which the motor can drive without stalling . At the same time,  monitor the 
SG_RESULT value at this load, e.g. some value within the range 0 to 100. The stall threshold should be 
a value safely within the operating limits, to allow for parameter stray. The response at an SGT 
setting at or near 0 gives some idea on the quality of the signal: Check the SG value without load and 
with maximum load. They should show a difference of at least 100 or a few 100, which shall be large 
compared to the offset. If you set the SGT value in a way, that a reading of 0 occurs at maximum 
motor load, the stall can be automatically detected by the motion controller to issue a motor stop.  In 
the moment of the step resulting in a step loss, the lowest reading will be visible. After the step loss, 
the motor will vibrate and show a higher SG_RESULT reading. 
13.4 Homing with StallGuard 
The homing of a linear drive requires moving the motor into the direction of a hard stop. As 
StallGuard needs a certain velocity to work (as set by TCOOLTHRS), make sure that the start point is 
far enough away from the hard stop to provide the distance required for the acceleration phase. After 
setting up SGT and the ramp generator registers, start a motion into the direction of the hard stop 
and activate the stop on stall function  (set sg_stop in SW_MODE). Once a stall is d etected, the ramp 
generator stop s motion and set s VACTUAL zero, stopping the motor . The stop condition also is 
indicated by the flag StallGuard in DRV_STATUS. After setting up new motion parameters in order to 
prevent the motor from restarting right away, StallGuard can be disabled, or the motor can be re -
enabled by reading  and writing back  RAMP_STAT. The write and clear function of the event_stop_sg 
flag in RAMP_STAT restarts the motor after expiration of TZEROWAIT in case the motion parameters 
have not been modified. Best results are yielded at 30% to 70% of nominal motor current and 
typically 1 to 5 RPS (motors smaller than NEMA17 may require higher velocities).  
13.5 Limits of StallGuard2 Operation 
StallGuard2 does not operate reliably at extreme motor velo cities: Very low motor velocities (for many 
motors, less than one revolution per second) generate a low back EMF and make the measurement 
unstable and dependent on environment conditions (temperature, etc.). The automatic tuning 
procedure described above w ill compensate for this. Other conditions will also lead to extreme 
settings of SGT and poor response of the measurement value SG_RESULT to the motor load. 
 
Very high motor velocities, in which the full sinusoidal current is not driven into the motor coils  also 
leads to poor response. These velocities are typically characterized by the motor back EMF reaching 
the supply voltage.  
