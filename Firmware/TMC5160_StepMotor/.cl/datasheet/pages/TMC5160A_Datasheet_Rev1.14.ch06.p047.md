# TMC5160A_Datasheet_Rev1.14 — 第6章 · p47

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
47 
 
 
 
www.trinamic.com 
6.5 Motor Driver Registers 
MICROSTEPPING CONTROL REGISTER SET (0X60…0X6B)  
R/W 
Addr 
n 
Register 
Description / bit names 
Range [Unit] 
W 
0x60 
32 
MSLUT[0] 
 
microstep 
table entries 
0…31 
Each bit gives the difference between entry x 
and entry x+1 when combined with the cor-
responding MSLUTSEL W bits: 
0: W= %00: -1 
 
%01: +0  
 
%10: +1 
 
%11: +2   
1: W= %00: +0 
 
%01: +1  
 
%10: +2 
 
%11: +3 
This is the differential coding for the first 
quarter of a wave. Start values for CUR_A and 
CUR_B are stored for MSCNT position 0 in 
START_SIN and START_SIN90.  
ofs31, ofs30, …, ofs01, ofs00 
…  
ofs255, ofs254, …, ofs225, ofs224 
32x 0 or 1 
reset default= 
sine wave 
table 
W 
0x61 
… 
0x67 
7 
x 
32 
MSLUT[1...7] 
 
microstep 
table entries 
32…255 
7x 
32x 0 or 1 
reset default= 
sine wave 
table 
W 
0x68 
32 
MSLUTSEL 
This register defines four segments within 
each quarter MSLUT wave. Four 2 bit entries 
determine the meaning of a 0 and a 1 bit in 
the corresponding segment of MSLUT.  
See separate table! 
0<X1<X2<X3 
reset default= 
sine wave 
table 
W 
0x69 
8 
+ 
8 
MSLUTSTART 
bit 7… 0: 
START_SIN 
bit 23… 16: START_SIN90 
START_SIN gives the absolute current at 
microstep table entry 0. 
START_SIN90 gives the absolute current for 
microstep table entry at positions 256.   
Start values are transferred to the microstep 
registers CUR_A and CUR_B, whenever the 
reference position MSCNT=0 is passed.  
START_SIN  
reset default 
=0 
 
START_SIN90  
reset default 
=247 
R 
0x6A 
10 
MSCNT 
Microstep counter. Indicates actual position 
in the microstep table for CUR_A. CUR_B uses 
an offset of 256 (2 phase motor). 
Hint: Move to a position where MSCNT is 
zero before re-initializing MSLUTSTART or 
MSLUT and MSLUTSEL. 
0…1023 
R 
0x6B 
9 
+ 
9 
MSCURACT 
bit 8… 0: 
CUR_A (signed):  
 
Actual 
microstep 
current 
for 
motor phase A as read from 
MSLUT (not scaled by current)  
bit 24… 16: CUR_B (signed): 
 
Actual 
microstep 
current 
for 
motor phase B as read from 
MSLUT (not scaled by current)  
+/-0...255 
 
 
 


<!-- detected tables -->

|  | MICROSTEPPING CONTROL REGISTER SET (0X60…0X6B) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | R/W |  |  | Addr |  |  | n |  |  | Register |  |  | Description / bit names |  |  | Range [Unit] |  |
| W |  |  | 0x60 |  |  | 32 |  |  | MSLUT[0] microstep table entries 0…31 |  |  | Each bit gives the difference between entry x and entry x+1 when combined with the cor- responding MSLUTSEL W bits: 0: W= %00: -1 %01: +0 %10: +1 %11: +2 1: W= %00: +0 %01: +1 %10: +2 %11: +3 This is the differential coding for the first quarter of a wave. Start values for CUR A and _ CUR B are stored for MSCNT position 0 in _ START SIN and START SIN90. _ _ ofs31, ofs30, …, ofs01, ofs00 … ofs255, ofs254, …, ofs225, ofs224 |  |  | 32x 0 or 1 reset default= sine wave table |  |  |
| W |  |  | 0x61 … 0x67 |  |  | 7 x 32 |  |  | MSLUT[1...7] microstep table entries 32…255 |  |  |  |  |  | 7x 32x 0 or 1 reset default= sine wave table |  |  |
| W |  |  | 0x68 |  |  | 32 |  |  | MSLUTSEL |  |  |  | This register defines four segments within |  | 0<X1<X2<X3 reset default= sine wave table |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | each quarter MSLUT wave. Four 2 bit entries |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | determine the meaning of a 0 and a 1 bit in |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | the corresponding segment of MSLUT. |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | See separate table! |  |  |  |  |
| W |  |  | 0x69 |  |  | 8 + 8 |  |  | MSLUTSTART |  |  | bit 7… 0: START SIN _ bit 23… 16: START SIN90 _ START SIN gives the absolute current at _ microstep table entry 0. START SIN90 gives the absolute current for _ microstep table entry at positions 256. Start values are transferred to the microstep registers CUR A and CUR B, whenever the _ _ reference position MSCNT=0 is passed. |  |  | START SIN _ reset default =0 START SIN90 _ reset default =247 |  |  |
| R |  |  | 0x6A |  |  | 10 |  |  | MSCNT |  |  | Microstep counter. Indicates actual position in the microstep table for CUR A. CUR B uses _ _ an offset of 256 (2 phase motor). Hint: Move to a position where MSCNT is zero before re-initializing MSLUTSTART or MSLUT and MSLUTSEL. |  |  | 0…1023 |  |  |
| R |  |  | 0x6B |  |  | 9 + 9 |  |  | MSCURACT |  |  | bit 8… 0: CUR A (signed): _ Actual microstep current for motor phase A as read from MSLUT (not scaled by current) bit 24… 16: CUR B (signed): _ Actual microstep current for motor phase B as read from MSLUT (not scaled by current) |  |  | +/-0...255 |  |  |
