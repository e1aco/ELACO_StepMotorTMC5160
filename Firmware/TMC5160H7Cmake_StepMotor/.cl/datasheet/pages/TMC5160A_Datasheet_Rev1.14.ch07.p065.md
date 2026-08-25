# TMC5160A_Datasheet_Rev1.14 — 第7章 · p65

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  65 
 
 
 
www.trinamic.com 
Running low speed
optionoption
Running low speed
Running high speed
motor stand still
motor going to standby
motor in standby
motor in standby
v
t
TSTEP < TPWMTHRS*16/16
TSTEP > TPWMTHRS
0
VACTUAL
~1/TSTEP
current
TPOWERDOWN
RMS current
I_HOLD
I_RUN
dI * IHOLDDELAY
stealthChop
spreadCycle
Chopper mode
TRINAMIC, B. Dwersteg, 14.3.14
 
Figure 7.7 TPWMTHRS for optional switching to SpreadCycle 
As a first step, both chopper principles should be parameterized and optimized individually. In a next 
step, a transfer velocity has to be fixed. For example, StealthChop operation is used for precise low 
speed positioning, while SpreadCycle shall be used for highly dynamic motion. TPWMTHRS determines 
the transition vel ocity. Read out TSTEP when moving at the desired velocity and program the 
resulting value to TPWMTHRS. Use a low transfer velocity to avoid a jerk at the switching point.  
A jerk occurs when switching at higher velocities, because the back -EMF of the motor  (which rises 
with the velocity) causes a phase shift of up to 90° between motor voltage and motor current. So 
when switching at higher velocities between voltage PWM and current PWM mode, this jerk will occur 
with increased intensity. A high jerk may even produce a temporary overcurrent condition (depending 
on the motor coil resistance). At low velocities (e.g. 1 to a few 10 RPM), it can be completely 
neglected for most motors. Therefore, consider the switching jerk when choosing TPWMTHRS. Set 
TPWMTHRS zero if you want to work with StealthChop only. 
When enabling the StealthChop mode the first time using automatic current regulation, the motor 
must be at st and still in order to allow a proper current regulation. When the drive switches to 
StealthChop at a higher velocity, StealthChop logic stores the last current regulation setting until the 
motor returns to a lower velocity again. This way, the regulation h as a known starting point when 
returning to a lower velocity, where StealthChop becomes re-enabled. Therefore, neither the velocity 
threshold nor the supply voltage must be considerably changed during the phase while the chopper 
is switched to a different mode, because otherwise the motor might lose steps or the instantaneous 
current might be too high or too low. 
A motor stall or a sudden change in the motor velocity may lead to the driver detecting a short 
circuit or to a state of automatic current regulat ion, from which it cannot recover. Clear the error flags 
and restart the motor from zero velocity to recover from this situation. 
 
Hint 
Start the motor from standstill when switching on StealthChop the first time and keep it stopped for 
at least 128 chopper periods to allow StealthChop to do initial standstill current control.  
