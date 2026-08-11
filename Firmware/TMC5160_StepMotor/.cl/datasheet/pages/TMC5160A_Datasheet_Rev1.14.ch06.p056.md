# TMC5160A_Datasheet_Rev1.14 — 第6章 · p56

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
56 
 
 
 
www.trinamic.com 
6.5.5 
DRV_STATUS – StallGuard2 Value and Driver Error Flags 
0X6F: DRV_STATUS – STALLGUARD2 VALUE AND DRIVER ERROR FLAGS 
Bit 
Name 
Function 
Comment 
31 
stst 
standstill indicator 
This flag indicates motor stand still in each operation mode. 
This occurs 2^20 clocks after the last step pulse. 
30 
olb 
open load indicator 
phase B 
1: Open load detected on phase A or B. 
Hint: This is just an informative flag. The driver takes no action 
upon it. False detection may occur in fast motion and 
standstill. Check during slow motion, only. 
29 
ola 
open load indicator 
phase A 
28 
s2gb 
short to ground 
indicator phase B 
1: Short to GND detected on phase A or B. The driver becomes 
disabled. The flags stay active, until the driver is disabled by 
software (TOFF=0) or by the ENN input. 
27 
s2ga 
short to ground 
indicator phase A 
26 
otpw 
overtemperature pre-
warning flag 
1: Overtemperature pre-warning threshold is exceeded. 
The overtemperature pre-warning flag is common for both 
bridges. 
25 
ot 
overtemperature flag 
1: Overtemperature limit has been reached. Drivers become 
disabled until otpw is also cleared due to cooling down of the 
IC. 
The overtemperature flag is common for both bridges. 
24 
StallGuard 
StallGuard2 status 
1: Motor stall detected (SG_RESULT=0) or DcStep stall in DcStep 
mode. 
23 
- 
reserved 
Ignore these bits 
22 
21 
20 
CS 
ACTUAL 
actual motor current / 
smart energy current 
Actual current control scaling, for monitoring smart energy 
current scaling controlled via settings in register COOLCONF, or 
for monitoring the function of the automatic current scaling. 
19 
18 
17 
16 
15 
fsactive 
full step active 
indicator 
1: Indicates that the driver has switched to fullstep as defined 
by chopper mode settings and velocity thresholds.  
14 
stealth 
StealthChop indicator 
1: Driver operates in StealthChop mode 
13 
s2vsb 
short to supply 
indicator phase B 
1: Short to supply detected on phase A or B. The driver 
becomes disabled. The flags stay active, until the driver is 
disabled by software (TOFF=0) or by the ENN input. Sense 
resistor voltage drop is included in the measurement! 
12 
s2vsa 
short to supply 
indicator phase A 
11 
- 
reserved 
Ignore this bit 
10 
- 
reserved 
Ignore this bit 
9 
SG_ 
RESULT 
StallGuard2 result 
respectively PWM on 
time for coil A in stand 
still for motor 
temperature detection 
Mechanical load measurement: 
The StallGuard2 result gives a means to measure mechanical 
motor load. A higher value means lower mechanical load. A 
value of 0 signals highest load. With optimum SGT setting, 
this is an indicator for a motor stall. The stall detection 
compares SG_RESULT to 0 in order to detect a stall. SG_RESULT 
is used as a base for CoolStep operation, by comparing it to a 
programmable upper and a lower limit. It is not applicable in 
StealthChop mode. 
StallGuard2 works best with microstep operation or DcStep. 
Temperature measurement: 
In standstill, no StallGuard2 result can be obtained. SG_RESULT 
shows the chopper on-time for motor coil A instead. Move the 
motor to a determined microstep position at a certain current 
setting to get a rough estimation of motor temperature by a 
reading the chopper on-time. As the motor heats up, its coil 
resistance rises and the chopper on-time increases.  
8 
7 
6 
5 
4 
3 
2 
1 
0 
 


<!-- detected tables -->

|  | 0X6F: DRV STATUS – STALLGUARD2 VALUE AND DRIVER ERROR FLAGS _ |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Bit |  |  | Name |  |  | Function |  |  | Comment |  |
| 31 |  |  | stst |  |  | standstill indicator |  |  | This flag indicates motor stand still in each operation mode. This occurs 2^20 clocks after the last step pulse. |  |  |
| 30 |  |  | olb |  |  | open load indicator phase B |  |  | 1: Open load detected on phase A or B. Hint: This is just an informative flag. The driver takes no action upon it. False detection may occur in fast motion and standstill. Check during slow motion, only. |  |  |
| 29 |  |  | ola |  |  | open load indicator phase A |  |  |  |  |  |
| 28 |  |  | s2gb |  |  | short to ground indicator phase B |  |  | 1: Short to GND detected on phase A or B. The driver becomes disabled. The flags stay active, until the driver is disabled by software (TOFF=0) or by the ENN input. |  |  |
| 27 |  |  | s2ga |  |  | short to ground indicator phase A |  |  |  |  |  |
| 26 |  |  | otpw |  |  | overtemperature pre- warning flag |  |  | 1: Overtemperature pre-warning threshold is exceeded. The overtemperature pre-warning flag is common for both bridges. |  |  |
| 25 |  |  | ot |  |  | overtemperature flag |  |  | 1: Overtemperature limit has been reached. Drivers become disabled until otpw is also cleared due to cooling down of the IC. The overtemperature flag is common for both bridges. |  |  |
| 24 |  |  | StallGuard |  |  | StallGuard2 status |  |  | 1: Motor stall detected (SG RESULT=0) or DcStep stall in DcStep _ mode. |  |  |
| 23 |  |  | - |  |  | reserved |  |  | Ignore these bits |  |  |
| 22 |  |  |  |  |  |  |  |  |  |  |  |
| 21 |  |  |  |  |  |  |  |  |  |  |  |
| 20 |  |  | CS ACTUAL |  |  | actual motor current / smart energy current |  |  | Actual current control scaling, for monitoring smart energy current scaling controlled via settings in register COOLCONF, or for monitoring the function of the automatic current scaling. |  |  |
|  | 19 |  |  |  |  |  |  |  |  |  |  |
|  | 18 |  |  |  |  |  |  |  |  |  |  |
|  | 17 |  |  |  |  |  |  |  |  |  |  |
|  | 16 |  |  |  |  |  |  |  |  |  |  |
| 15 |  |  | fsactive |  |  | full step active indicator |  |  | 1: Indicates that the driver has switched to fullstep as defined by chopper mode settings and velocity thresholds. |  |  |
| 14 |  |  | stealth |  |  | StealthChop indicator |  |  | 1: Driver operates in StealthChop mode |  |  |
| 13 |  |  | s2vsb |  |  | short to supply indicator phase B |  |  | 1: Short to supply detected on phase A or B. The driver becomes disabled. The flags stay active, until the driver is disabled by software (TOFF=0) or by the ENN input. Sense resistor voltage drop is included in the measurement! |  |  |
| 12 |  |  | s2vsa |  |  | short to supply indicator phase A |  |  |  |  |  |
|  | 11 |  | - |  |  | reserved |  |  | Ignore this bit |  |  |
|  | 10 |  | - |  |  | reserved |  |  | Ignore this bit |  |  |
|  | 9 |  | SG _ RESULT |  |  | StallGuard2 result respectively PWM on time for coil A in stand still for motor temperature detection |  |  | Mechanical load measurement: The StallGuard2 result gives a means to measure mechanical motor load. A higher value means lower mechanical load. A value of 0 signals highest load. With optimum SGT setting, this is an indicator for a motor stall. The stall detection compares SG RESULT to 0 in order to detect a stall. SG RESULT _ _ is used as a base for CoolStep operation, by comparing it to a programmable upper and a lower limit. It is not applicable in StealthChop mode. StallGuard2 works best with microstep operation or DcStep. Temperature measurement: In standstill, no StallGuard2 result can be obtained. SG RESULT _ shows the chopper on-time for motor coil A instead. Move the motor to a determined microstep position at a certain current setting to get a rough estimation of motor temperature by a reading the chopper on-time. As the motor heats up, its coil resistance rises and the chopper on-time increases. |  |  |
|  | 8 |  |  |  |  |  |  |  |  |  |  |
| 7 |  |  |  |  |  |  |  |  |  |  |  |
| 6 |  |  |  |  |  |  |  |  |  |  |  |
| 5 |  |  |  |  |  |  |  |  |  |  |  |
| 4 |  |  |  |  |  |  |  |  |  |  |  |
|  | 3 |  |  |  |  |  |  |  |  |  |  |
|  | 2 |  |  |  |  |  |  |  |  |  |  |
|  | 1 |  |  |  |  |  |  |  |  |  |  |
| 0 | 0 |  |  |  |  |  |  |  |  |  |  |
