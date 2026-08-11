# TMC5160A_Datasheet_Rev1.14 — 第6章 · p55

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
55 
 
 
 
www.trinamic.com 
0X70: PWMCONF – VOLTAGE MODE PWM STEALTHCHOP 
Bit 
Name 
Function 
Comment 
17 
pwm_freq1 PWM frequency 
selection 
%00:  fPWM=2/1024 fCLK (Reset default) 
%01:  fPWM=2/683 fCLK 
%10:  fPWM=2/512 fCLK 
%11:  fPWM=2/410 fCLK 
16 
pwm_freq0 
15 
PWM_ 
GRAD 
User defined amplitude 
gradient 
Velocity dependent gradient for PWM amplitude:  
PWM_GRAD * 256 / TSTEP  
This value is added to PWM_AMPL to compensate for 
the velocity-dependent motor back-EMF.  
 
Use PWM_GRAD as initial value for automatic scaling to 
speed up the automatic tuning process. To do this, set 
PWM_GRAD to the determined, application specific value, 
with 
pwm_autoscale=0. 
Only 
afterwards, 
set 
pwm_autoscale=1. Enable StealthChop when finished.  
 
Hint: 
After initial tuning, the required initial value can be read 
out from PWM_GRAD_AUTO. 
14 
13 
12 
11 
10 
9 
8 
7 
PWM_ 
OFS 
User defined amplitude 
(offset) 
User defined PWM amplitude offset (0-255) related to full 
motor current (CS_ACTUAL=31) in stand still.  
(Reset default=30) 
 
Use PWM_OFS as initial value for automatic scaling to 
speed up the automatic tuning process. To do this, set 
PWM_OFS to the determined, application specific value, 
with 
pwm_autoscale=0. 
Only 
afterwards, 
set 
pwm_autoscale=1. Enable StealthChop when finished.  
  
PWM_OFS = 0 will disable scaling down motor current 
below a motor specific lower measurement threshold. 
This setting should only be used under certain 
conditions, i.e. when the power supply voltage can vary 
up and down by a factor of two or more. It prevents 
the motor going out of regulation, but it also prevents 
power down below the regulation limit. 
 
PWM_OFS > 0 allows automatic scaling to low PWM duty 
cycles even below the lower regulation threshold. This 
allows low (standstill) current settings based on the 
actual (hold) current scale (register IHOLD_IRUN).  
6 
5 
4 
3 
2 
1 
0 
 
 


<!-- detected tables -->

|  | 0X70: PWMCONF – VOLTAGE MODE PWM STEALTHCHOP |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Bit |  |  | Name |  |  | Function |  |  | Comment |  |
|  | 17 |  | pwm freq1 _ |  |  | PWM frequency selection |  |  | %00: f =2/1024 f (Reset default) PWM CLK %01: f =2/683 f PWM CLK %10: f =2/512 f PWM CLK %11: f =2/410 f PWM CLK |  |  |
| 16 | 16 |  | pwm freq0 _ |  |  |  |  |  |  |  |  |
| 15 |  |  | PWM _ GRAD |  |  | User defined amplitude gradient |  |  | Velocity dependent gradient for PWM amplitude: PWM GRAD * 256 / TSTEP _ This value is added to PWM AMPL to compensate for _ the velocity-dependent motor back-EMF. Use PWM GRAD as initial value for automatic scaling to _ speed up the automatic tuning process. To do this, set PWM GRAD to the determined, application specific value, _ with pwm autoscale=0. Only afterwards, set _ pwm autoscale=1. Enable StealthChop when finished. _ Hint: After initial tuning, the required initial value can be read out from PWM GRAD AUTO. |  |  |
| 14 |  |  |  |  |  |  |  |  |  |  |  |
| 13 |  |  |  |  |  |  |  |  |  |  |  |
| 12 |  |  |  |  |  |  |  |  |  |  |  |
|  | 11 |  |  |  |  |  |  |  |  |  |  |
|  | 10 |  |  |  |  |  |  |  |  |  |  |
|  | 9 |  |  |  |  |  |  |  |  |  |  |
| 8 | 8 |  |  |  |  |  |  |  |  |  |  |
| 7 |  |  | PWM _ OFS |  |  | User defined amplitude (offset) |  |  | _ _ User defined PWM amplitude offset (0-255) related to full motor current (CS ACTUAL=31) in stand still. _ (Reset default=30) Use PWM OFS as initial value for automatic scaling to _ speed up the automatic tuning process. To do this, set PWM OFS to the determined, application specific value, _ with pwm autoscale=0. Only afterwards, set _ pwm autoscale=1. Enable StealthChop when finished. _ PWM OFS = 0 will disable scaling down motor current _ below a motor specific lower measurement threshold. This setting should only be used under certain conditions, i.e. when the power supply voltage can vary up and down by a factor of two or more. It prevents the motor going out of regulation, but it also prevents power down below the regulation limit. PWM OFS > 0 allows automatic scaling to low PWM duty _ cycles even below the lower regulation threshold. This allows low (standstill) current settings based on the actual (hold) current scale (register IHOLD IRUN). _ |  |  |
| 6 |  |  |  |  |  |  |  |  |  |  |  |
| 5 |  |  |  |  |  |  |  |  |  |  |  |
| 4 |  |  |  |  |  |  |  |  |  |  |  |
|  | 3 |  |  |  |  |  |  |  |  |  |  |
|  | 2 |  |  |  |  |  |  |  |  |  |  |
|  | 1 |  |  |  |  |  |  |  |  |  |  |
| 0 | 0 |  |  |  |  |  |  |  |  |  |  |
