# TMC5160A_Datasheet_Rev1.14 — 第21章 DC MOTOR OR SOLENOID

--- [PAGE 110] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
110 
 
 
 
www.trinamic.com 
21 DC Motor or Solenoid 
The TMC5160 can drive one or two DC motors using one coil output per DC motor. Either a torque 
limited operation, or a voltage based velocity control with optional torque limit is possible. 
  
CONFIGURATION AND CONTROL 
Set the flag direct_mode in the GCONF register. In direct mode, the coil current polarity and coil 
current, respectively the PWM duty cycle become controlled by register XTARGET (0x2D). Bits 8..0 
control motor A and Bits 24..16 control motor B PWM. Additionally to this setting, the current limit is 
scaled by IHOLD. The STEP/DIR inputs and the motion controller are not used in this mode.  
 
PWM DUTY CYCLE VELOCITY CONTROL 
In order to operate the motor at different velocities, use the StealthChop voltage PWM mode in the 
following configuration:  
en_pwm_mode = 1, pwm_autoscale = 0, PWM_OFS = 255, PWM_GRAD = 4, IHOLD = 31  
Set TOFF > 0 to enable the driver.  
In this mode the driver behaves like a 4-quadrant power supply. The direct mode setting of PWM A 
and PWM B using XTARGET controls motor voltage, and thus the motor velocity. Setting the 
corresponding PWM bits between -255 and +255 (signed, two’s complement numbers) will vary motor 
voltage from -100% to 100%. With pwm_autoscale = 0, current sensing is not used and the sense 
resistors should be eliminated or 150mΩ or less to avoid excessive voltage drop when the motor 
becomes heavily loaded up to 2.5A. Especially for higher current motors, make sure to slowly 
accelerate and decelerate the motor in order to avoid overcurrent or triggering driver overcurrent 
detection. 
 
To activate optional motor freewheeling, set IHOLD = 0 and FREEWHEEL = %01. 
 
ADDITIONAL TORQUE LIMIT 
In order to additionally take advantage of the motor current limitation (and thus torque controlled 
operation) in StealthChop mode, use automatic current scaling (pwm_autoscale = 1, PWM_OFS = 30). 
The actual current limit is given by IHOLD and scaled by the respective motor PWM amplitude, e.g. 
PWM = 128 yields in 50% motor velocity and 50% of the current limit set by IHOLD. In case two DC 
motors are driven in voltage PWM mode, note that the automatic current regulation will work only 
for the motor which has the higher absolute PWM setting. The PWM of the second motor also will be 
scaled down in case the motor with higher PWM setting reaches its current limitation.  
 
PURELY TORQUE LIMITED OPERATION 
For a purely torque limited operation of one or two motors, spread cycle chopper individually 
regulates motor current for both full bridge motor outputs. When using SpreadCycle, the upper motor 
velocity is limited by the supply voltage only (or as determined by the load on the motor). 
21.1 Solenoid Operation 
The same way, one or two solenoids (i.e. magnetic coil actuators) can be operated using SpreadCycle 
chopper. For solenoids, it is often desired to have an increased current for a short time after 
switching on, and reduce the current once the magnetic element has switched. This is automatically 
possible by taking advantage of the automatic current scaling (IRUN, IHOLD, IHOLDDELAY and 
TPOWERDOWN). The current scaling in direct_mode is still active, but will not be triggered if no step 
impulse is supplied. Therefore, a step impulse must be given to the STEP input whenever one of the 
coils shall be switched on. This will increase the current for both coils at the same time. 
 
 

