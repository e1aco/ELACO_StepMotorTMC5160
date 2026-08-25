# TMC5160A_Datasheet_Rev1.14 — 第6章 · p41

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  41 
 
 
 
www.trinamic.com 
RAMP GENERATOR MOTION CONTROL REGISTER SET (0X20…0X2D) 
R/W Addr n Register Description / bit names Range [Unit] 
W 0x2B 18 VSTOP 
Motor stop velocity (unsigned) 
 
Hint: Set VSTOP ≥ VSTART to allow positioning 
for short distances 
 
Attention: Do not set 0 in positioning mode , 
minimum 10 recommend! 
1…(2^18)-1 
[µsteps / t] 
Reset 
Default=1 
W 0x2C 16 TZEROWAIT 
Defines the w aiting time after ramping down 
to zero velocity before next movement or 
direction inversion can start. Time range is 
about 0 to 2 seconds. 
 
This setting avoids excess acceleration e.g. 
from VSTOP to -VSTART. 
0…(2^16)-1 * 
512 tCLK 
RW 0x2D 32 XTARGET 
Target position for ramp mode (signed). Write 
a new target position to this register in order 
to activate the ramp generator positioning in 
RAMPMODE=0. Initialize all velocity, 
acceleration and deceleration parameters 
before. 
 
Hint: The position is allowed  to wrap around, 
thus, XTARGET value optionally can be treated 
as an unsigned number.  
 
Hint: The maximum possible displacement is 
+/-((2^31)-1). 
 
Hint: When increasing V1, D1 or DMAX  during 
a motion, rewrite XTARGET afterwards in order 
to trigger a second  acceleration phase, if 
desired. 
-2^31… 
+(2^31)-1 
  
