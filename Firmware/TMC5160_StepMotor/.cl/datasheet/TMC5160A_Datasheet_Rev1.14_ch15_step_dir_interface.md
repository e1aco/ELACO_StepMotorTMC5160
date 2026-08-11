# TMC5160A_Datasheet_Rev1.14 — 第15章 STEP/DIR INTERFACE

--- [PAGE 94] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
94 
 
 
 
www.trinamic.com 
15 STEP/DIR Interface 
The STEP and DIR inputs provide a simple, standard interface compatible with many existing motion 
controllers. The MicroPlyer STEP pulse interpolator brings the smooth motor operation of high-
resolution microstepping to applications originally designed for coarser stepping. In case an external 
step source is used, the complete integrated motion controller can be switched off. The only motion 
controller registers remaining active in this case are the current settings in register IHOLD_IRUN.  
15.1 Timing 
Figure 15.1 shows the timing parameters for the STEP and DIR signals, and the table below gives 
their specifications. When the dedge mode bit in the CHOPCONF register is set, both edges of STEP 
are active. If dedge is cleared, only rising edges are active. STEP and DIR are sampled and 
synchronized to the system clock. An internal analog filter removes glitches on the signals, such as 
those caused by long PCB traces. If the signal source is far from the chip, and especially if the signals 
are carried on cables, the signals should be filtered or differentially transmitted. 
  
+VCC_IO
SchmittTrigger
0.44 VCC_IO
0.56 VCC_IO
83k
C
Input filter
R*C = 20ns +-30%
STEP 
or DIR
Input
Internal 
Signal
DIR
STEP
tDSH
tSH
tSL
tDSU
Active edge 
(DEDGE=0)
Active edge 
(DEDGE=0)
 
Figure 15.1 STEP and DIR timing, Input pin filter 
 
STEP and DIR interface timing  
AC-Characteristics 
clock period is tCLK 
Parameter 
Symbol 
Conditions 
Min 
Typ 
Max 
Unit 
step frequency (at maximum 
microstep resolution) 
fSTEP 
dedge=0 
 
 
½ fCLK 
 
dedge=1 
 
 
¼ fCLK 
 
fullstep frequency 
fFS 
 
 
 
fCLK/512 
 
STEP input low time *) 
tSL 
 
max(tFILTSD, 
tCLK+20) 
100 
 
ns 
STEP input high time *) 
tSH 
 
max(tFILTSD, 
tCLK+20) 
100 
 
ns 
DIR to STEP setup time 
tDSU 
 
20 
 
 
ns 
DIR after STEP hold time 
tDSH 
 
20 
 
 
ns 
STEP and DIR spike filtering time 
*) 
tFILTSD 
rising and falling 
edge 
13 
20 
30 
ns 
STEP and DIR sampling relative 
to rising CLK input 
tSDCLKHI 
before rising edge 
of CLK input 
 
tFILTSD 
 
ns 
 
*) These values are valid with full input logic level swing, only. Asymmetric logic levels will increase 
filtering delay tFILTSD, due to an internal input RC filter. 
 
 


<!-- detected tables -->

| DIR |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
|  |  |  |  |  |  |  |  |
| t DSU STEP |  |  | t SH |  | t SL | t DSH |  |
|  |  |  |  |  |  |  |  |

| STEP and DIR interface timing |  |  |  | AC-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  |  |  |  | clock period is t CLK |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
| step frequency (at maximum microstep resolution) | step frequency (at maximum |  | f STEP |  |  | dedge=0 |  |  |  |  |  |  |  |  | ½ f CLK |  |  |  |  |  |
|  | microstep resolution) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  | dedge=1 |  |  |  |  |  |  |  |  | ¼ f CLK |  |  |  |  |  |
|  | fullstep frequency |  | f FS |  |  |  |  |  |  |  |  |  |  |  | f /512 CLK |  |  |  |  |  |
| STEP input low time *) | STEP input low time *) |  | t SL |  |  |  |  |  | max(tFILTSD, tCLK+20) |  |  | 100 |  |  |  |  |  | ns |  |  |
| STEP input high time *) |  |  | t SH |  |  |  |  |  | max(tFILTSD, tCLK+20) |  |  | 100 |  |  |  |  |  | ns |  |  |
|  | DIR to STEP setup time |  | t DSU |  |  |  |  |  | 20 |  |  |  |  |  |  |  |  | ns |  |  |
|  | DIR after STEP hold time |  | t DSH |  |  |  |  |  | 20 |  |  |  |  |  |  |  |  | ns |  |  |
|  | STEP and DIR spike filtering time |  | t FILTSD |  |  | rising and falling edge |  |  | 13 |  |  | 20 |  |  | 30 |  |  | ns |  |  |
|  | *) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | STEP and DIR sampling relative |  | t SDCLKHI |  |  | before rising edge of CLK input |  |  |  |  |  | t FILTSD |  |  |  |  |  | ns |  |  |
|  | to rising CLK input |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
--- [PAGE 95] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
95 
 
 
 
www.trinamic.com 
15.2 Changing Resolution 
The TMC5160 includes an internal microstep table with 1024 sine wave entries to generate sinusoidal 
motor coil currents. These 1024 entries correspond to one electrical revolution or four fullsteps. The 
microstep resolution setting determines the step width taken within the table. Depending on the DIR 
input, the microstep counter is increased (DIR=0) or decreased (DIR=1) with each STEP pulse by the 
step width. The microstep resolution determines the increment respectively the decrement. At 
maximum resolution, the sequencer advances one step for each step pulse. At half resolution, it 
advances two steps. Increment is up to 256 steps for fullstepping. The sequencer has special 
provision to allow seamless switching between different microstep rates at any time. When switching 
to a lower microstep resolution, it calculates the nearest step within the target resolution and reads 
the current vector at that position. This behavior especially is important for low resolutions like 
fullstep and halfstep, because any failure in the step sequence would lead to asymmetrical run when 
comparing a motor running clockwise and counterclockwise. 
 
EXAMPLES: 
Fullstep:  
Cycles through table positions: 128, 384, 640 and 896 (45°, 135°, 225° and 315° electrical 
position, both coils on at identical current). The coil current in each position 
corresponds to the RMS-Value (0.71 * amplitude). Step size is 256 (90° electrical) 
Half step: 
The first table position is 64 (22.5° electrical), Step size is 128 (45° steps) 
Quarter step: The first table position is 32 (90°/8=11.25° electrical), Step size is 64 (22.5° steps) 
 
This way equidistant steps result and they are identical in both rotation directions. Some older drivers 
also use zero current (table entry 0, 0°) as well as full current (90°) within the step tables. This kind of 
stepping is avoided because it provides less torque and has a worse power dissipation in driver and 
motor.  
 
Step position 
table position 
current coil A 
current coil B 
Half step 0 
64 
38.3% 
92.4% 
Full step 0 
128 
70.7% 
70.7% 
Half step 1 
192 
92.4% 
38.3% 
Half step 2 
320 
92.4% 
-38.3% 
Full step 1 
384 
70.7% 
-70.7% 
Half step 3 
448 
38.3% 
-92.4% 
Half step 4 
576 
-38.3% 
-92.4% 
Full step 2 
640 
-70.7% 
-70.7% 
Half step 5 
704 
-92.4% 
-38.3% 
Half step 6 
832 
-92.4% 
38.3% 
Full step 3 
896 
-70.7% 
70.7% 
Half step 7 
960 
-38.3% 
92.4% 
 
 
 


<!-- detected tables -->

|  | Step position |  |  | table position |  |  | current coil A |  |  | current coil B |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Half step 0 |  | 64 |  |  | 38.3% |  |  | 92.4% |  |  |
|  | Full step 0 |  | 128 |  |  | 70.7% |  |  | 70.7% |  |  |
|  | Half step 1 |  | 192 |  |  | 92.4% |  |  | 38.3% |  |  |
|  | Half step 2 |  | 320 |  |  | 92.4% |  |  | -38.3% |  |  |
|  | Full step 1 |  | 384 |  |  | 70.7% |  |  | -70.7% |  |  |
|  | Half step 3 |  | 448 |  |  | 38.3% |  |  | -92.4% |  |  |
|  | Half step 4 |  | 576 |  |  | -38.3% |  |  | -92.4% |  |  |
|  | Full step 2 |  | 640 |  |  | -70.7% |  |  | -70.7% |  |  |
|  | Half step 5 |  | 704 |  |  | -92.4% |  |  | -38.3% |  |  |
|  | Half step 6 |  | 832 |  |  | -92.4% |  |  | 38.3% |  |  |
|  | Full step 3 |  | 896 |  |  | -70.7% |  |  | 70.7% |  |  |
|  | Half step 7 |  | 960 |  |  | -38.3% |  |  | 92.4% |  |  |
--- [PAGE 96] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
96 
 
 
 
www.trinamic.com 
15.3 MicroPlyer and Stand Still Detection 
For each active edge on STEP, MicroPlyer produces microsteps at 256x resolution, as shown in Figure 
15.2. It interpolates the time in between of two step impulses at the step input based on the last 
step interval. This way, from 2 microsteps (128 microstep to 256 microstep interpolation) up to 256 
microsteps (full step input to 256 microsteps) are driven for a single step pulse.  
 
Enable MicroPlyer by setting the intpol bit in the CHOPCONF register.  
GCONF.faststandstill allows reduction of standstill detection time to 2^18 clocks (~20ms) 
 
The step rate for the interpolated 2 to 256 microsteps is determined by measuring the time interval of 
the previous step period and dividing it into up to 256 equal parts. The maximum time between two 
microsteps corresponds to 220 (roughly one million system clock cycles), for an even distribution of 
256 microsteps. At 12 MHz system clock frequency, this results in a minimum step input frequency of 
12 Hz for MicroPlyer operation (50 Hz with faststandstill = 1). A lower step rate causes the STST bit to 
be set, which indicates a standstill event. At that frequency, microsteps occur at a rate of (system 
clock frequency)/216 ~ 256 Hz. When a stand still is detected, the driver automatically switches the 
motor to holding current IHOLD. 
 
Hint 
MicroPlyer only works perfectly with a stable STEP frequency. Do not use the dedge option if the STEP 
signal does not have a 50% duty cycle. 
 
STEP
Interpolated 
microstep
Active edge 
(dedge=0)
Active edge 
(dedge=0)
Active edge 
(dedge=0)
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
32
Active edge 
(dedge=0)
STANDSTILL 
(stst) active
33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50
Motor
angle
52 53 54 55 56 57 58 59 60 61 62 63 64 65 66
51
2^20 tCLK
 
Figure 15.2 MicroPlyer microstep interpolation with rising STEP frequency (Example: 16 to 256) 
In Figure 15.2, the first STEP cycle is long enough to set the standstill bit stst. This bit is cleared on 
the next STEP active edge. Then, the external STEP frequency increases. After one cycle at the higher 
rate MicroPlyer adapts the interpolated microstep rate to the higher frequency. During the last cycle at 
the slower rate, MicroPlyer did not generate all 16 microsteps, so there is a small jump in motor 
angle between the first and second cycles at the higher rate. With the flag GCONF.faststandstill 
enabled, standstill detection is after 2^18 clocks (rather than 2^20 clocks) without step pulse. This 
allows faster current reduction for energy saving in drives with short stand still times.  
 
 


<!-- detected tables -->

|  |  |  |  |  |
|---|---|---|---|---|
| STEP |  |  |  |  |
|  |  |  |  |  |
| rpolated icrostep |  | 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 | 16 17 18 19 20 21 22 23 3233 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 | 49 505152 53 54 55 56 57 58 59 60 61 62 63 64 65 66 |
| Motor angle |  |  |  |  |
|  |  | 2^20 tCLK |  |  |
