# TMC5160A_Datasheet_Rev1.14 — 第9章 SELECTING SENSE RESISTORS

--- [PAGE 74] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
74 
 
 
 
www.trinamic.com 
9 Selecting Sense Resistors 
The TMC5160 provides several means to set the motor current: Sense resistors, GLOBALSCALER and 
currentscale CS. To adapt a drive to the motor, choose a sense-resistor value fitting or slightly 
exceeding the maximum desired current at 100% settings of the scalers. Fine-tune the current to the 
specific motor via the 8 bit GLOBALSCALER. Situation specific motor current adaptation is done by 5 
bit scalers (actual scale can be read via CS), controlled by CoolStep, run- and hold current (IRUN, 
IHOLD). This makes the CS control compatible to other TRINAMIC ICs.  
 
Set the desired maximum motor current by selecting an appropriate value for the sense resistor. The 
following table shows the RMS current values which are reached using standard resistors. 
 
CHOICE OF RSENSE AND RESULTING MAX. MOTOR CURRENT 
WITH GLOBALSCALER=0 (RESP. VALUE 256) 
RSENSE [Ω] 
RMS current [A] 
(CS=31) 
Sine wave peak 
current [A] (CS=31) 
0.22 
1.1 
1.5 
0.15 
1.6 
2.2 
0.12 
2.0 
2.8 
0.10 
2.3 
3.3 
0.075 
3.1 
4.4 
0.066 
3.5 
5.0 
0.050 
4.7 
6.6 
0.033 
7.1 
10.0 
0.022 
10.6 
15.0 
 
Sense resistors should be carefully selected. The full motor current flows through the sense resistors. 
Due to chopper operation the sense resistors see pulsed current from the MOSFET bridges. Therefore, 
a low-inductance type such as film or composition resistors is required to prevent voltage spikes 
causing ringing on the sense voltage inputs leading to unstable measurement results. Also, a low-
inductance, low-resistance PCB layout is essential. A massive ground plane is best. Please also refer to 
layout considerations in chapter 29. 
 
The sense resistor sets the upper current which can be set by software settings IRUN, IHOLD and 
GLOBALSCALER. Choose the sense resistor value so that the maximum desired current (or slightly 
more) flows at the maximum current setting (GLOBALSCALER = 256 (setting 0) and IRUN = 31). 
 
CALCULATION OF RMS CURRENT 
𝐼𝑅𝑀𝑆= 𝐺𝐿𝑂𝐵𝐴𝐿𝑆𝐶𝐴𝐿𝐸𝑅
256
∗𝐶𝑆+ 1
32
∗
𝑉𝐹𝑆
𝑅𝑆𝐸𝑁𝑆𝐸
∗1
√2
 
 
The momentary motor current is calculated by: 
 
𝐼𝑀𝑂𝑇= 𝐺𝐿𝑂𝐵𝐴𝐿𝑆𝐶𝐴𝐿𝐸𝑅
256
∗𝐶𝑈𝑅𝐴/𝐵
248
∗𝐶𝑆+ 1
32
∗
𝑉𝐹𝑆
𝑅𝑆𝐸𝑁𝑆𝐸
 
 
GLOBALSCALER is the global current scaler. A setting of 0 is treated as full scale (256). 
CS is the current scale setting as set by the IHOLD and IRUN and CoolStep. 
VFS is the full scale voltage (please refer to electrical characteristics, VSRT). 
CURA/B is the actual value from the internal sine wave table.  
248 is the amplitude of the internal sine wave table. 
 
The sense resistor needs to be able to conduct the peak motor coil current in motor standstill 
conditions, unless standby power is reduced. Under normal conditions, the sense resistor conducts 


<!-- detected tables -->

|  | CHOICE OF R AND RESULTING MAX. MOTOR CURRENT SENSE |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
|  | WITH GLOBALSCALER=0 (RESP. VALUE 256) |  |  |  |  |  |  |
| R [Ω] SENSE | R [Ω] SENSE |  | RMS current [A] |  |  | Sine wave peak |  |
|  |  |  | (CS=31) |  |  | current [A] (CS=31) |  |
| 0.22 |  | 1.1 |  |  | 1.5 |  |  |
| 0.15 |  | 1.6 |  |  | 2.2 |  |  |
| 0.12 |  | 2.0 |  |  | 2.8 |  |  |
| 0.10 |  | 2.3 |  |  | 3.3 |  |  |
| 0.075 |  | 3.1 |  |  | 4.4 |  |  |
| 0.066 |  | 3.5 |  |  | 5.0 |  |  |
| 0.050 |  | 4.7 |  |  | 6.6 |  |  |
| 0.033 |  | 7.1 |  |  | 10.0 |  |  |
| 0.022 |  | 10.6 |  |  | 15.0 |  |  |
--- [PAGE 75] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
75 
 
 
 
www.trinamic.com 
less than the coil RMS current, because no current flows through the sense resistor during the slow 
decay phases. 
 
CALCULATION OF PEAK SENSE RESISTOR POWER DISSIPATION 
𝑃𝑅𝑆𝑀𝐴𝑋= 𝐼𝐶𝑂𝐼𝐿
2 ∗𝑅𝑆𝐸𝑁𝑆𝐸 
 
Hint 
For best precision of current setting, it is advised to measure and fine tune the current in the 
application. Choose the sense resistors to the next value covering the desired motor current. Set IRUN 
to 31 corresponding 100% of the desired motor current and fine-tune motor current using 
GLOBALSCALER. 
 
Attention 
Be sure to use a symmetrical sense resistor layout and short and straight sense resistor traces of 
identical length. Well matching sense resistors ensure best performance. 
A compact layout with massive ground plane is best to avoid parasitic resistance effects. 
 
 
Parameter 
Description 
Setting  Comment 
IRUN 
Current scale when motor is running. Scales coil 
current values as taken from the internal sine 
wave table. For high precision motor operation, 
work with a current scaling factor in the range 16 
to 31, because scaling down the current values 
reduces the effective microstep resolution by 
making microsteps coarser. This setting also 
controls the maximum current value set by 
CoolStep. 
0 … 31  
 
scaling factor 
1/32, 2/32, … 32/32 
IHOLD 
Identical to IRUN, but for motor in stand still. 
IHOLD 
DELAY 
Allows smooth current reduction from run current 
to hold current. IHOLDDELAY controls the number 
of clock cycles for motor power down after 
TZEROWAIT in increments of 2^18 clocks: 0=instant 
power down, 1..15: Current reduction delay per 
current step in multiple of 2^18 clocks. 
 
Example: When using IRUN=31 and IHOLD=16, 15 
current steps are required for hold current 
reduction. A IHOLDDELAY setting of 4 thus results 
in a power down time of 4*15*2^18 clock cycles, 
i.e. roughly one second at 16MHz. 
0 
instant IHOLD 
1 … 15 
 
 
1*218 … 15*218  
clocks per current  
decrement 
GLOBAL 
SCALER 
Allows fine control of the motor current range 
setting 
0 … 255 scales in 1/256 steps 
0=full scale 
 
 


<!-- detected tables -->

|  | Parameter |  |  | Description |  |  | Setting |  |  | Comment |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
| IRUN | IRUN |  | Current scale when motor is running. Scales coil current values as taken from the internal sine wave table. For high precision motor operation, work with a current scaling factor in the range 16 to 31, because scaling down the current values reduces the effective microstep resolution by making microsteps coarser. This setting also controls the maximum current value set by CoolStep. |  |  | 0 … 31 |  |  | scaling factor 1/32, 2/32, … 32/32 |  |  |
|  | IHOLD |  | Identical to IRUN, but for motor in stand still. |  |  |  |  |  |  |  |  |
| IHOLD DELAY | IHOLD |  | Allows smooth current reduction from run current to hold current. IHOLDDELAY controls the number of clock cycles for motor power down after TZEROWAIT in increments of 2^18 clocks: 0=instant power down, 1..15: Current reduction delay per current step in multiple of 2^18 clocks. Example: When using IRUN=31 and IHOLD=16, 15 current steps are required for hold current reduction. A IHOLDDELAY setting of 4 thus results in a power down time of 4*15*2^18 clock cycles, i.e. roughly one second at 16MHz. |  |  | 0 |  |  | instant IHOLD |  |  |
|  | DELAY |  |  |  |  | 1 … 15 |  |  | 1*218 … 15*218 clocks per current decrement |  |  |
| GLOBAL SCALER |  |  | Allows fine control of the motor current range setting |  |  | 0 … 255 |  |  | scales in 1/256 steps 0=full scale |  |  |
