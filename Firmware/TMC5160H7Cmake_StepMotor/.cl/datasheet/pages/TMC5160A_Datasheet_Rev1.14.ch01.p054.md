# TMC5160A_Datasheet_Rev1.14 — 第1章 · p54

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  54 
 
 
 
www.trinamic.com 
6.5.4 PWMCONF – Voltage PWM Mode StealthChop 
0X70: PWMCONF – VOLTAGE MODE PWM STEALTHCHOP 
Bit Name Function Comment 
31 PWM_LIM PWM automatic scale 
amplitude limit when 
switching on 
Limit for PWM_SCALE_AUTO when switching back from 
SpreadCycle to StealthChop. This value defines the upper 
limit for bits 7 to 4 of the automatic current control 
when switching back. It can be set to reduce the current 
jerk during mode change back to StealthChop. 
It does not limit PWM_GRAD or PWM_GRAD_AUTO offset. 
(Default = 12) 
30 
29 
28 
27 PWM_REG Regulation loop 
gradient 
User defined maximum PWM amplitude change pe r half 
wave when using pwm_autoscale=1. (1…15): 
1: 0.5 increments (slowest regulation) 
2: 1 increment  
3: 1.5 increments 
4: 2 increments (Reset default)) 
… 
8: 4 increments 
...  
15: 7.5 increments (fastest regulation) 
26 
25 
24 
23 - reserved set to 0 
22 - reserved set to 0 
21 freewheel1 Allows different 
standstill modes 
Stand still option when motor current setting is zero 
(I_HOLD=0).  
%00:  Normal operation 
%01:  Freewheeling 
%10:  Coil shorted using LS drivers 
%11:  Coil shorted using HS drivers 
20 freewheel0 
19 pwm_ 
autograd 
PWM automatic 
gradient adaptation 
0 Fixed value for PWM_GRAD 
(PWM_GRAD_AUTO = PWM_GRAD) 
1 Automatic tuning (only with pwm_autoscale=1) 
(Reset default)  
PWM_GRAD_AUTO is initialized with PWM_GRAD 
while pwm_autograd=0 and becomes optimized 
automatically during motion.  
Preconditions 
1. PWM_OFS_AUTO has been automatically 
initialized. This requires standstill at IRUN for 
>130ms in order to a) detect standstill b) wait > 
128 chopper cycles at IRUN and c) regulate 
PWM_OFS_AUTO so that 
-1 < PWM_SCALE_AUTO < 1 
2. Motor running and 1.5 * PWM_OFS_AUTO < 
PWM_SCALE_SUM < 4* PWM_OFS_AUTO and 
PWM_SCALE_SUM < 255.  
Time required for tuning PWM_GRAD_AUTO 
About 8 fullsteps per change of +/-1.  
Also enables use of reduced chopper frequency for 
tuning PWM_OFS_AUTO. 
18 pwm_ 
autoscale 
PWM automatic 
amplitude scaling 
0 User defined feed forward PWM amplitude. The 
current settings IRUN and IHOLD have no influence! 
The resulting PWM amplitude (limited to 0…255) is: 
PWM_OFS * ((CS_ACTUAL+1) / 32)  
+ PWM_GRAD * 256 / TSTEP 
1 Enable automatic current control (Reset default) 
