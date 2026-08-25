# TMC5160A_Datasheet_Rev1.14 — 第1章 · p53

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  53 
 
 
 
www.trinamic.com 
6.5.3 COOLCONF – Smart Energy Control CoolStep and StallGuard2 
0X6D: COOLCONF – SMART ENERGY CONTROL COOLSTEP AND STALLGUARD2 
Bit Name Function Comment 
… - reserved set to 0 
24 sfilt 
 
StallGuard2 filter 
enable 
0 Standard mode, high time resolution for 
StallGuard2 
1 Filtered mode, StallGuard2 signal updated for each 
four fullsteps (resp. six fullsteps for 3 phase motor) 
only to compensate for motor pole tolerances 
23 - reserved set to 0 
22 sgt6 StallGuard2 threshold 
value 
This signed value controls StallGuard2 level for s tall 
output and sets the optimum measurement range for 
readout. A lower value gives a higher sensitivity. Zero is 
the starting value working with most motors.  
-64 to +63:  A hig her value makes StallGuard2 less 
sensitive and requires more torque to 
indicate a stall. 
21 sgt5 
20 sgt4 
19 sgt3 
18 sgt2 
17 sgt1 
16 sgt0 
15 seimin minimum current for 
smart current control 
0: 1/2 of current setting (IRUN) 
1: 1/4 of current setting (IRUN) 
14 sedn1 current down step 
speed 
%00: For each 32 StallGuard2 values decrease by one 
%01: For each 8 StallGuard2 values decrease by one 
%10: For each 2 StallGuard2 values decrease by one 
%11: For each StallGuard2 value decrease by one 
13 sedn0 
12 - reserved set to 0 
11 semax3 StallGuard2 hysteresis 
value for smart current 
control 
If the StallGuard2 result is equal to or above 
(SEMIN+SEMAX+1)*32, the motor current becomes 
decreased to save energy. 
%0000 … %1111: 0 … 15 
10 semax2 
9 semax1 
8 semax0 
7 - reserved set to 0 
6 seup1 current up step width Current increment steps per measured StallGuard2 value  
%00 … %11: 1, 2, 4, 8 5 seup0 
4 - reserved set to 0 
3 semin3 minimum StallGuard2 
value for smart current 
control and 
smart current enable 
If the StallGuard2 result falls below SEMIN*32, the motor 
current becomes increased to reduce motor load angle. 
%0000: smart current control CoolStep off 
%0001 … %1111: 1 … 15 
2 semin2 
1 semin1 
0 semin0 
 
  
