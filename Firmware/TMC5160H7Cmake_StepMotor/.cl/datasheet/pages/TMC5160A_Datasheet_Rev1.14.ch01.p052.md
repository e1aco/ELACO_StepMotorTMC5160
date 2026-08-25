# TMC5160A_Datasheet_Rev1.14 — 第1章 · p52

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  52 
 
 
 
www.trinamic.com 
0X6C: CHOPCONF – CHOPPER CONFIGURATION 
Bit Name Function Comment 
11 fd3 TFD [3] chm=1: 
MSB of fast decay time setting TFD 
10 hend3 HEND 
hysteresis low value 
OFFSET 
sine wave offset 
chm=0 
 
%0000 … %1111:  
Hysteresis is -3, -2, -1, 0, 1, …, 12  
(1/512 of this setting adds to current setting) 
This is the hysteresis value which becomes 
used for the hysteresis chopper. 
9 hend2 
8 hend1 
7 hend0 
chm=1 %0000 … %1111:  
Offset is -3, -2, -1, 0, 1, …, 12 
This is the sine wave offset and 1/512 of the 
value becomes added to the absolute value 
of each sine wave entry. 
6 hstrt2 HSTRT 
hysteresis start value 
added to HEND 
 
chm=0 
 
 
%000 … %111:  
Add 1, 2, …, 8 to hysteresis low value HEND 
(1/512 of this setting adds to current setting) 
Attention: Effective HEND+HSTRT ≤ 16. 
Hint: Hysteresis decrement is done each 16 
clocks 
5 hstrt1 
4 hstrt0 
TFD [2..0] 
fast decay time setting 
chm=1 Fast decay time setting (MSB:  fd3): 
%0000 … %1111: 
Fast decay time setting TFD with  
NCLK= 32*TFD (%0000: slow decay only) 
3 toff3 TOFF off time 
and driver enable 
Off time setting controls duration of slow decay phase 
NCLK= 24 + 32*TOFF 
%0000: Driver disable, all bridges off 
%0001: 1 – use only with TBL ≥ 2 
%0010 … %1111: 2 … 15 
2 toff2 
1 toff1 
0 toff0 
  
