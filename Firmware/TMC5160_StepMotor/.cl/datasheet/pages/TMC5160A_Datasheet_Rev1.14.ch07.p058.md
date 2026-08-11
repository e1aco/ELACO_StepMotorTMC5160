# TMC5160A_Datasheet_Rev1.14 — 第7章 · p58

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
58 
 
 
 
www.trinamic.com 
AUTOMATIC TUNING TIMING AND BORDER CONDITIONS 
Step 
Parameter 
Conditions 
Required Duration 
AT#1 
 
PWM_ 
OFS_AUTO 
- 
Motor in standstill and actual current scale (CS) is 
identical to run current (IRUN).  
- 
If standstill reduction is enabled, an initial step 
pulse switches the drive back to run current, or set 
IHOLD to IRUN.  
- 
Pin VS at operating level. 
Attention: Driver may reduce chopper frequency during 
AT#1. Use reduced standstill current IHOLD<IRUN to 
prevent extended periods of time at lower chopper 
frequency 
≤ 2^20+2*2^18 tCLK,  
≤ 130ms  
(with internal clock) 
AT#2  
 
PWM_ 
GRAD_AUTO 
- 
Move motor at a velocity, where a significant 
amount of back EMF is generated and where the full 
run current can be reached. Conditions:  
- 
1.5 * PWM_OFS_AUTO 
< 
PWM_SCALE_SUM 
< 
4 * PWM_OFS_AUTO  
- 
PWM_SCALE_SUM < 255.  
Hint: A typical range is 60-300 RPM.  
8 fullsteps are required 
for a change of +/-1.  
For a typical motor with 
PWM_GRAD_AUTO 
optimum at 50 or less, up 
to 
400 
fullsteps 
are 
required when starting 
from default value 0. 
 
Hint: 
Determine best conditions for automatic tuning with the evaluation board. 
Use application specific parameters for PWM_GRAD and PWM_OFS for initialization in firmware to provide 
initial tuning parameters. 
Monitor PWM_SCALE_AUTO going down to zero during the constant velocity phase in AT#2 tuning. This 
indicates a successful tuning. 
 
Attention:  
Operating in StealthChop without proper tuning can lead to high motor currents during a deceleration 
ramp, especially with low resistive motors and fast deceleration settings. Follow the automatic tuning 
process and check optimum tuning conditions using the evaluation board. It is recommended to use 
an initial value for settings PWM_OFS and PWM_GRAD determined per motor type. 
Protect the power stage and supply by additionally tuning the overcurrent protection. 
 
Known Limitations TMC5160 non-A-version only:  
Successful completion of AT#1 tuning phase is not safely detected by the TMC5160. It will require 
multiple motor start / stop events to safely detect completion. 
Successful determination is mandatory for AT#2: Tuning of PWM_GRAD will not start when AT#1 has 
not completed.  
Successful completion of AT#1 and AT#2 only can be checked by monitoring PWM_SCALE_AUTO 
approaching 0 during AT#2 motion.  
 
Solution a):  
Complete automatic tuning phase AT#1 process, by using a slow-motion sequence which leads to 
standstill detection in between of each two steps. Use a velocity of 8 (6 Hz) or lower and execute 
minimum 10 steps during AT#1 phase. 
 
Solution b): 
Store initial parameters for PWM_GRAD_AUTO for the application. Therefore, use the motor and 
operating conditions determined for the application and do a complete automatic tuning sequence 
(refer to a)). Store the resulting PWM_GRAD_AUTO value and use it for initialization of PWM_GRAD. 
With this, tuning of AT#2 phase is not mandatory in the application and can be skipped. Automatic 
tuning will further optimize settings during operation. Combine with a) if desired. 
 


<!-- detected tables -->

|  | AUTOMATIC TUNING TIMING AND BORDER CONDITIONS |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Step |  |  | Parameter |  |  | Conditions |  |  | Required Duration |  |
| AT#1 | AT#1 |  | PWM _ OFS AUTO _ |  |  | - Motor in standstill and actual current scale (CS) is identical to run current (IRUN). - If standstill reduction is enabled, an initial step pulse switches the drive back to run current, or set IHOLD to IRUN. - Pin VS at operating level. Attention: Driver may reduce chopper frequency during AT#1. Use reduced standstill current IHOLD<IRUN to prevent extended periods of time at lower chopper frequency |  |  | ≤ 2^20+2*2^18 t , CLK ≤ 130ms (with internal clock) |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |
| AT#2 |  |  | PWM _ GRAD AUTO _ |  |  | - Move motor at a velocity, where a significant amount of back EMF is generated and where the full run current can be reached. Conditions: - 1.5 * PWM OFS AUTO < PWM SCALE SUM < _ _ _ _ 4 * PWM OFS AUTO _ _ - PWM SCALE SUM < 255. _ _ Hint: A typical range is 60-300 RPM. |  |  | 8 fullsteps are required for a change of +/-1. For a typical motor with PWM GRAD AUTO _ _ optimum at 50 or less, up to 400 fullsteps are required when starting from default value 0. |  |  |
