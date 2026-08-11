# TMC5160A_Datasheet_Rev1.14 — 第8章 · p71

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
71 
 
 
 
www.trinamic.com 
the chopper frequency is stabilized at high amplitudes and low supply voltage situations, if the 
frequency gets too low. This avoids the frequency reaching the audible range. 
t
I
target current
target current - hysteresis start
target current + hysteresis start
on
sd
fd
sd
target current + hysteresis end
target current - hysteresis end
HDEC
 
Figure 8.3 SpreadCycle chopper scheme showing coil current during a chopper cycle 
Two parameters control SpreadCycle mode: 
 
Parameter 
Description 
Setting Comment 
HSTRT 
Hysteresis start setting. This value is an offset 
from the hysteresis end value HEND. 
0…7 
HSTRT=1…8 
This value adds to HEND. 
HEND 
Hysteresis end setting. Sets the hysteresis end 
value after a number of decrements. The sum 
HSTRT+HEND must be ≤16. At a current setting of 
max. 30 (amplitude reduced to 240), the sum is 
not limited. 
0…2 
-3…-1: negative HEND 
3 
0: zero HEND 
4…15 
1…12: positive HEND 
 
With HSTRT=0 and HEND=0, the hysteresis is 0 (off). 
 
EXAMPLE: 
 
A hysteresis of 4 has been chosen. You might decide to not use hysteresis decrement. In this case 
set: 
 
HEND=6 
(sets an effective end value of 6-3=3) 
HSTRT=0 
(sets minimum hysteresis, i.e. 1: 3+1=4) 
 
In order to take advantage of the variable hysteresis, we can set most of the value to the HSTRT, i.e. 
4, and the remaining 1 to hysteresis end. The resulting configuration register values are as follows: 
 
HEND=0  
(sets an effective end value of -3) 
HSTRT=6  
(sets an effective start value of hysteresis end +7: 7-3=4) 
 
Hint 
Highest motor velocities sometimes benefit from setting TOFF to 2 or 3 and a short TBL of 2 or 1. 
 
 


<!-- detected tables -->

| C E D H |  |  |  |  |
|---|---|---|---|---|
|  |  |  |  |  |
|  |  |  |  |  |
|  |  |  |  |  |
|  |  |  |  |  |
|  |  |  |  | t |
| on | sd | fd | sd |  |

|  | Parameter |  |  | Description |  |  | Setting |  |  | Comment |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
| HSTRT | HSTRT |  | Hysteresis start setting. This value is an offset from the hysteresis end value HEND. |  |  | 0…7 |  |  | HSTRT=1…8 This value adds to HEND. |  |  |
| HEND |  |  | Hysteresis end setting. Sets the hysteresis end value after a number of decrements. The sum HSTRT+HEND must be ≤16. At a current setting of max. 30 (amplitude reduced to 240), the sum is not limited. |  |  | 0…2 |  |  | -3…-1: negative HEND |  |  |
|  |  |  |  |  |  | 3 |  |  | 0: zero HEND |  |  |
|  |  |  |  |  |  | 4…15 |  |  | 1…12: positive HEND |  |  |
