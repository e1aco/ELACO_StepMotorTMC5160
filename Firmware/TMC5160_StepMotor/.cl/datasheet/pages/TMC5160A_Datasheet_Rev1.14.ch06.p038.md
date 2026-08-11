# TMC5160A_Datasheet_Rev1.14 — 第6章 · p38

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
38 
 
 
 
www.trinamic.com 
6.2 Velocity Dependent Driver Feature Control Register Set 
VELOCITY DEPENDENT DRIVER FEATURE CONTROL REGISTER SET (0X10…0X1F)  
R/W 
Addr 
n 
Register 
Description / bit names 
W 
0x10 
5 
+ 
5 
+ 
4 
IHOLD_IRUN 
Bit 
IHOLD_IRUN – Driver current control 
4..0 IHOLD  
Standstill current (0=1/32…31=32/32) 
In combination with StealthChop mode, setting 
IHOLD=0 allows to choose freewheeling or coil 
short circuit for motor stand still. 
12..8 IRUN 
Motor run current (0=1/32…31=32/32) 
 
Hint: Choose sense resistors in a way, that normal 
IRUN is 16 to 31 for best microstep performance. 
19..16 IHOLDDELAY 
Controls the number of clock cycles for motor 
power down after a motion as soon as standstill is 
detected (stst=1) and TPOWERDOWN has expired. 
The smooth transition avoids a motor jerk upon 
power down. 
 
0:  
instant power down 
1..15:  
Delay per current reduction step in multiple 
of 2^18 clocks 
W 
0x11 
8 
TPOWER 
DOWN 
TPOWERDOWN sets the delay time after stand still (stst) of the 
motor to motor current power down. Time range is about 0 to 
4 seconds.  
Attention: A minimum setting of 2 is required to allow 
automatic tuning of StealthChop PWM_OFFS_AUTO.  
Reset Default = 10  
0…((2^8)-1) * 2^18 tCLK 
R 
0x12 
20 
TSTEP 
Actual measured time between two 1/256 microsteps derived 
from the step input frequency in units of 1/fCLK. Measured 
value is (2^20)-1 in case of overflow or stand still.  
 
All TSTEP related thresholds use a hysteresis of 1/16 of the 
compare value to compensate for jitter in the clock or the step 
frequency. The flag small_hysteresis modifies the hysteresis to 
a smaller value of 1/32. 
(Txxx*15/16)-1 or  
(Txxx*31/32)-1 is used as a second compare value for each 
comparison value. 
This means, that the lower switching velocity equals the 
calculated setting, but the upper switching velocity is higher as 
defined by the hysteresis setting. 
 
When working with the motion controller, the measured TSTEP 
for a given velocity V is in the range  
(224 / V) ≤ TSTEP ≤ 224 / V - 1. 
 
In DcStep mode TSTEP will not show the mean velocity of the 
motor, but the velocities for each microstep, which may not be 
stable and thus does not represent the real motor velocity in 
case it runs slower than the target velocity.  


<!-- detected tables -->

|  | VELOCITY DEPENDENT DRIVER FEATURE CONTROL REGISTER SET (0X10…0X1F) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | R/W |  |  | Addr |  |  | n |  |  | Register |  |  | Description / bit names |  |  |  |  |
| W |  |  | 0x10 |  |  | 5 + 5 + 4 |  |  | IHOLD IRUN _ |  |  |  | Bit |  |  | IHOLD IRUN – Driver current control |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 4..0 |  |  | _ IHOLD Standstill current (0=1/32…31=32/32) In combination with StealthChop mode, setting IHOLD=0 allows to choose freewheeling or coil short circuit for motor stand still. |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 12..8 |  |  | IRUN Motor run current (0=1/32…31=32/32) Hint: Choose sense resistors in a way, that normal IRUN is 16 to 31 for best microstep performance. |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 19..16 |  |  | IHOLDDELAY Controls the number of clock cycles for motor power down after a motion as soon as standstill is detected (stst=1) and TPOWERDOWN has expired. The smooth transition avoids a motor jerk upon power down. 0: instant power down 1..15: Delay per current reduction step in multiple of 2^18 clocks |  |  |
| W |  |  | 0x11 |  |  | 8 |  |  | TPOWER DOWN |  |  | TPOWERDOWN sets the delay time after stand still (stst) of the motor to motor current power down. Time range is about 0 to 4 seconds. Attention: A minimum setting of 2 is required to allow automatic tuning of StealthChop PWM OFFS AUTO. _ _ Reset Default = 10 0…((2^8)-1) * 2^18 t CLK |  |  |  |  |  |
| R |  |  | 0x12 |  |  | 20 |  |  | TSTEP |  |  | Actual measured time between two 1/256 microsteps derived from the step input frequency in units of 1/fCLK. Measured value is (2^20)-1 in case of overflow or stand still. All TSTEP related thresholds use a hysteresis of 1/16 of the compare value to compensate for jitter in the clock or the step frequency. The flag small hysteresis modifies the hysteresis to _ a smaller value of 1/32. (Txxx*15/16)-1 or (Txxx*31/32)-1 is used as a second compare value for each comparison value. This means, that the lower switching velocity equals the calculated setting, but the upper switching velocity is higher as defined by the hysteresis setting. When working with the motion controller, the measured TSTEP for a given velocity V is in the range (224 / V) ≤ TSTEP ≤ 224 / V - 1. In DcStep mode TSTEP will not show the mean velocity of the motor, but the velocities for each microstep, which may not be stable and thus does not represent the real motor velocity in case it runs slower than the target velocity. |  |  |  |  |  |
