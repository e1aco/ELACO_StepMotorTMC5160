# TMC5160A_Datasheet_Rev1.14 — 第6章 · p40

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  40 
 
 
 
www.trinamic.com 
6.3 Ramp Generator Registers 
6.3.1 Ramp Generator Motion Control Register Set 
RAMP GENERATOR MOTION CONTROL REGISTER SET (0X20…0X2D) 
R/W Addr n Register Description / bit names Range [Unit] 
RW 0x20 2 RAMPMODE 
RAMPMODE: 
0: Positioning mode (using all A, D and V 
parameters) 
1: Velocity mode to positive VMAX (using 
AMAX acceleration) 
2: Velocity mode to neg ative VMAX (using 
AMAX acceleration) 
3: Hold mode (velocity remains unchanged, 
unless stop event occurs) 
0…3 
RW 0x21 32 XACTUAL 
Actual motor position (signed) 
 
Hint: This value normally should only be 
modified, when homing the drive. In 
positioning mode, modifying the register 
content will start a motion. 
-2^31… 
+(2^31)-1 
R 0x22 24 VACTUAL 
Actual motor velocity from ramp generator 
(signed) 
 
The sign matches the motion direction. A 
negative sign means motion to lower 
XACTUAL. 
+-(2^23)-1 
[µsteps / t]  
W 0x23 18 VSTART 
Motor start velocity (unsigned) 
 
For universal use, s et VSTOP ≥ VSTART. This is 
not required if the motion distance is sufficient 
to ensure deceleration from VSTART to VSTOP. 
0…(2^18)-1 
[µsteps / t] 
W 0x24 16 A1 First acceleration between VSTART and V1 
(unsigned) 
0…(2^16)-1 
[µsteps / ta²] 
W 0x25 20 V1 
First acceleration / deceleration phase 
threshold velocity (unsigned) 
 
0: Disables A1 and D1 phase, use AMAX, DMAX 
only 
0…(2^20)-1 
[µsteps / t] 
W 0x26 16 AMAX 
Second acceleration between V1 and VMAX 
(unsigned) 
 
This is the acceleration and deceleration value 
for velocity mode. 
0…(2^16)-1 
[µsteps / ta²] 
W 0x27 23 VMAX 
Motion ramp  target velocity (for positioning 
ensure VMAX ≥ VSTART) (unsigned) 
 
This is the target velocity in velocity mode. It 
can be changed any time during a motion. 
0…(2^23)-512 
[µsteps / t] 
W 0x28 16 DMAX Deceleration between VMAX and V1 (unsigned) 0…(2^16)-1 
[µsteps / ta²] 
W 0x2A 16 D1 
Deceleration betwe en V1 and VSTOP 
(unsigned) 
 
Attention: Do not set 0 in positioning mode, 
even if V1=0! 
1…(2^16)-1 
[µsteps / ta²] 
