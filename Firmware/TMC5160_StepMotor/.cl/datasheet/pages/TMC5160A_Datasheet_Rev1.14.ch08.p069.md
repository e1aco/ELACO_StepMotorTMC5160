# TMC5160A_Datasheet_Rev1.14 — 第8章 · p69

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
69 
 
 
 
www.trinamic.com 
Three parameters are used for controlling both chopper modes: 
8.1 SpreadCycle Chopper 
The SpreadCycle (patented) chopper algorithm is a precise and simple to use chopper mode which 
automatically determines the optimum length for the fast-decay phase. The SpreadCycle will provide 
superior microstepping quality even with default settings. Several parameters are available to 
optimize the chopper to the application. 
 
Each chopper cycle is comprised of an on phase, a slow decay phase, a fast decay phase and a 
second slow decay phase (see Figure 8.3). The two slow decay phases and the two blank times per 
chopper cycle put an upper limit to the chopper frequency. The slow decay phases typically make up 
for about 30%-70% of the chopper cycle in standstill and are important for low motor and driver 
power dissipation.  
 
Calculation of a starting value for the slow decay time TOFF: 
 
EXAMPLE:  
 
Target Chopper frequency: 25kHz.  
Assumption: Two slow decay cycles make up for 50% of overall chopper cycle time 
 
𝑡𝑂𝐹𝐹=
1
25𝑘𝐻𝑧∗50
100 ∗1
2 = 10µ𝑠 
For the TOFF setting this means: 
𝑇𝑂𝐹𝐹= (𝑡𝑂𝐹𝐹∗𝑓𝐶𝐿𝐾−12)/32 
 
With 12 MHz clock this gives a setting of TOFF=3.0, i.e. 3.  
With 16 MHz clock this gives a setting of TOFF=4.25, i.e. 4 or 5.  
 
The hysteresis start setting forces the driver to introduce a minimum amount of current ripple into 
the motor coils. The current ripple must be higher than the current ripple which is caused by resistive 
losses in the motor in order to give best microstepping results. This will allow the chopper to 
precisely regulate the current both for rising and for falling target current. The time required to 
introduce the current ripple into the motor coil also reduces the chopper frequency. Therefore, a 
higher hysteresis setting will lead to a lower chopper frequency. The motor inductance limits the 
Parameter 
Description 
Setting Comment 
TOFF 
Sets the slow decay time (off time). This setting also 
limits the maximum chopper frequency. 
 
For operation with StealthChop, this parameter is not 
used, but it is required to enable the motor. In case of 
operation with StealthChop only, any setting is OK. 
 
Setting this parameter to zero completely disables all 
driver transistors and the motor can free-wheel. 
0 
chopper off 
1…15  
off time setting  
NCLK= 24 + 32*TOFF 
(1 will work with minimum 
blank time of 24 clocks) 
TBL 
Selects the comparator blank time. This time needs to 
safely cover the switching event and the duration of the 
ringing on the sense resistor. For most applications, a 
setting of 1 or 2 is good. For highly capacitive loads, 
e.g. when filter networks are used, a setting of 2 or 3 
will be required. 
0 
16 tCLK 
1 
24 tCLK 
2 
36 tCLK 
3 
54 tCLK 
chm 
Selection of the chopper mode 
0 
SpreadCycle 
1 
classic const. off time 
TPFD 
Adds passive fast decay time after bridge polarity 
change. Starting from 0, increase value, in case the 
motor suffers from mid-range resonances.  
0…15 
Fast decay time in multiple 
of 128 clocks (128 clocks 
are roughly 10µs) 


<!-- detected tables -->

|  | Parameter |  |  | Description |  |  | Setting |  |  | Comment |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
| TOFF | TOFF |  | Sets the slow decay time (off time). This setting also limits the maximum chopper frequency. For operation with StealthChop, this parameter is not used, but it is required to enable the motor. In case of operation with StealthChop only, any setting is OK. Setting this parameter to zero completely disables all driver transistors and the motor can free-wheel. |  |  | 0 |  |  | chopper off |  |  |
|  |  |  |  |  |  | 1…15 |  |  | off time setting N = 24 + 32*TOFF CLK (1 will work with minimum blank time of 24 clocks) |  |  |
| TBL |  |  | Selects the comparator blank time. This time needs to safely cover the switching event and the duration of the ringing on the sense resistor. For most applications, a setting of 1 or 2 is good. For highly capacitive loads, e.g. when filter networks are used, a setting of 2 or 3 will be required. |  |  | 0 |  |  | 16 t CLK |  |  |
|  |  |  |  |  |  | 1 |  |  | 24 t CLK |  |  |
|  |  |  |  |  |  | 2 |  |  | 36 t CLK |  |  |
|  |  |  |  |  |  | 3 |  |  | 54 t CLK |  |  |
| chm |  |  | Selection of the chopper mode |  |  | 0 |  |  | SpreadCycle |  |  |
|  |  |  |  |  |  | 1 |  |  | classic const. off time |  |  |
| TPFD |  |  | Adds passive fast decay time after bridge polarity change. Starting from 0, increase value, in case the motor suffers from mid-range resonances. |  |  | 0…15 |  |  | Fast decay time in multiple of 128 clocks (128 clocks are roughly 10µs) |  |  |
