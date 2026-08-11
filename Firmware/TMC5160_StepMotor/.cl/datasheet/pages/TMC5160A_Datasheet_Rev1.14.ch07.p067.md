# TMC5160A_Datasheet_Rev1.14 — 第7章 · p67

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
67 
 
 
 
www.trinamic.com 
PARAMETERS RELATED TO STEALTHCHOP 
Parameter 
Description 
Setting  Comment 
en_spread_ 
cycle 
General disable for use of StealthChop (register 
GCONF). 
1 
Do not use StealthChop 
0 
StealthChop enabled 
TPWMTHRS 
Specifies the upper velocity for operation in 
StealthChop. Entry the TSTEP reading (time 
between two microsteps) when operating at the 
desired threshold velocity. 
0 … 
1048575 
StealthChop is disabled if 
TSTEP falls TPWMTHRS   
PWM_LIM 
Limiting value for limiting the current jerk when 
switching 
from 
SpreadCycle 
to 
StealthChop. 
Reduce the value to yield a lower current jerk. 
0 … 15 
Upper four bits of 8 bit 
amplitude limit 
(Default=12) 
pwm_ 
autoscale 
Enable automatic current scaling using current 
measurement. If off, use forward controlled 
velocity-based mode. 
0 
Forward controlled mode 
1 
Automatic scaling with 
current regulator 
pwm_ 
autograd 
Enable automatic tuning of PWM_GRAD_AUTO 
0 
disable, use PWM_GRAD 
from register instead 
1 
enable 
PWM_FREQ 
PWM frequency selection. Use the lowest setting 
giving good results. The frequency measured at 
each of the chopper outputs is half of the 
effective chopper frequency fPWM. 
0 
fPWM=2/1024 fCLK 
1 
fPWM=2/683 fCLK 
2 
fPWM=2/512 fCLK 
3 
fPWM=2/410 fCLK 
PWM_REG 
User defined PWM amplitude regulation loop P-
coefficient. A higher value leads to a higher 
adaptation speed when pwm_autoscale=1. 
1 … 15 
Results in 0.5 to 7.5 steps 
for PWM_SCALE_AUTO 
regulator per fullstep 
PWM_OFS 
User defined PWM amplitude (offset) for velocity 
based scaling and initialization value for automatic 
tuning of PWM_OFFS_AUTO. 
0 … 255 PWM_OFS=0 disables 
linear current scaling 
based on current setting 
PWM_GRAD 
User defined PWM amplitude (gradient) for 
velocity based scaling and initialization value for 
automatic tuning of PWM_GRAD_AUTO. 
0 … 255  
FREEWHEEL 
Stand still option when motor current setting is 
zero (I_HOLD=0). Only available with StealthChop 
enabled. The freewheeling option makes the 
motor easy movable, while both coil short options 
realize a passive brake.  
0 
Normal operation 
1 
Freewheeling 
2 
Coil short via LS drivers 
3 
Coil short cia HS drivers 
PWM_SCALE 
_AUTO 
Read back of the actual StealthChop voltage PWM 
scaling correction as determined by the current 
regulator. Shall regulate close to 0 during tuning. 
-255 … 
255 
 
(read only) Scaling value 
becomes frozen when 
operating in SpreadCycle 
PWM_GRAD 
_AUTO 
PWM_OFS 
_AUTO 
Allow monitoring of the automatic tuning and 
determination of initial values for PWM_OFS and 
PWM_GRAD.  
0 … 255 
 
(read only) 
TOFF 
General enable for the motor driver, the actual 
value does not influence StealthChop 
0 
Driver off 
1 … 15 
Driver enabled 
TBL 
Comparator blank time. This time needs to safely 
cover the switching event and the duration of the 
ringing on the sense resistor. Choose a setting of 
1 or 2 for typical applications. For higher 
capacitive loads, 3 may be required. Lower 
settings allow StealthChop to regulate down to 
lower coil current values.  
0 
16 tCLK 
1 
24 tCLK 
2 
36 tCLK 
3 
54 tCLK 
 
 


<!-- detected tables -->

|  | PARAMETERS RELATED TO STEALTHCHOP |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Parameter |  |  | Description |  |  | Setting |  |  | Comment |  |
|  | en spread _ _ |  | General disable for use of StealthChop (register GCONF). |  |  | 1 |  |  | Do not use StealthChop |  |  |
|  | cycle |  |  |  |  | 0 |  |  | StealthChop enabled |  |  |
| TPWMTHRS | TPWMTHRS |  | Specifies the upper velocity for operation in StealthChop. Entry the TSTEP reading (time between two microsteps) when operating at the desired threshold velocity. |  |  | 0 … 1048575 |  |  | StealthChop is disabled if TSTEP falls TPWMTHRS |  |  |
| PWM LIM _ |  |  | Limiting value for limiting the current jerk when switching from SpreadCycle to StealthChop. Reduce the value to yield a lower current jerk. |  |  | 0 … 15 |  |  | Upper four bits of 8 bit amplitude limit (Default=12) |  |  |
| pwm _ autoscale |  |  | Enable automatic current scaling using current measurement. If off, use forward controlled velocity-based mode. |  |  | 0 |  |  | Forward controlled mode |  |  |
|  |  |  |  |  |  | 1 |  |  | Automatic scaling with current regulator |  |  |
| pwm _ autograd |  |  | Enable automatic tuning of PWM GRAD AUTO _ _ |  |  | 0 |  |  | disable, use PWM GRAD _ from register instead |  |  |
|  |  |  |  |  |  | 1 |  |  | enable |  |  |
| PWM FREQ _ |  |  | PWM frequency selection. Use the lowest setting giving good results. The frequency measured at each of the chopper outputs is half of the effective chopper frequency f . PWM |  |  | 0 |  |  | f =2/1024 f PWM CLK |  |  |
|  |  |  |  |  |  | 1 |  |  | f =2/683 f PWM CLK |  |  |
|  |  |  |  |  |  | 2 |  |  | f =2/512 f PWM CLK |  |  |
|  |  |  |  |  |  | 3 |  |  | f =2/410 f PWM CLK |  |  |
| PWM REG _ |  |  | User defined PWM amplitude regulation loop P- coefficient. A higher value leads to a higher adaptation speed when pwm autoscale=1. |  |  | 1 … 15 |  |  | Results in 0.5 to 7.5 steps for PWM SCALE AUTO _ _ regulator per fullstep |  |  |
| PWM OFS _ |  |  | _ User defined PWM amplitude (offset) for velocity based scaling and initialization value for automatic tuning of PWM OFFS AUTO. _ _ |  |  | 0 … 255 |  |  | PWM OFS=0 disables _ linear current scaling based on current setting |  |  |
| PWM GRAD _ |  |  | User defined PWM amplitude (gradient) for velocity based scaling and initialization value for automatic tuning of PWM GRAD AUTO. |  |  | 0 … 255 |  |  |  |  |  |
| FREEWHEEL |  |  | _ _ Stand still option when motor current setting is zero (I HOLD=0). Only available with StealthChop _ enabled. The freewheeling option makes the motor easy movable, while both coil short options realize a passive brake. |  |  | 0 |  |  | Normal operation |  |  |
|  |  |  |  |  |  | 1 |  |  | Freewheeling |  |  |
|  |  |  |  |  |  | 2 |  |  | Coil short via LS drivers |  |  |
|  |  |  |  |  |  | 3 |  |  | Coil short cia HS drivers |  |  |
| PWM SCALE _ AUTO _ |  |  | Read back of the actual StealthChop voltage PWM scaling correction as determined by the current regulator. Shall regulate close to 0 during tuning. |  |  | -255 … 255 |  |  | (read only) Scaling value becomes frozen when operating in SpreadCycle |  |  |
|  | PWM GRAD |  | Allow monitoring of the automatic tuning and determination of initial values for PWM OFS and _ PWM GRAD. _ |  |  | 0 … 255 |  |  | (read only) |  |  |
|  | _ AUTO |  |  |  |  |  |  |  |  |  |  |
|  | _ PWM OFS |  |  |  |  |  |  |  |  |  |  |
|  | _ AUTO _ |  |  |  |  |  |  |  |  |  |  |
| TOFF | TOFF |  | General enable for the motor driver, the actual value does not influence StealthChop |  |  | 0 |  |  | Driver off |  |  |
|  |  |  |  |  |  | 1 … 15 |  |  | Driver enabled |  |  |
| TBL |  |  | Comparator blank time. This time needs to safely cover the switching event and the duration of the ringing on the sense resistor. Choose a setting of 1 or 2 for typical applications. For higher capacitive loads, 3 may be required. Lower settings allow StealthChop to regulate down to lower coil current values. |  |  | 0 |  |  | 16 t CLK |  |  |
|  |  |  |  |  |  | 1 |  |  | 24 t CLK |  |  |
|  |  |  |  |  |  | 2 |  |  | 36 t CLK |  |  |
|  |  |  |  |  |  | 3 |  |  | 54 t CLK |  |  |
