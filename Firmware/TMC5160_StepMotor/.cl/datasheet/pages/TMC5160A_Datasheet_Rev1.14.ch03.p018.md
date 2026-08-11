# TMC5160A_Datasheet_Rev1.14 — 第3章 · p18

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
18 
 
 
 
www.trinamic.com 
MOSFET drivers
Lx
BMx
Hx
0V
V12VOUT
0V
0V
VVM
VVM+V12VOUT
VVM
Load pulling BMx down
Load pulling BMx up
tBBM
tBBM
Miller plateau
Hx-
BMx
0V
VCX-VBMx
Miller plateau
Effective break-before-make time
-1.2V
Output 
slope
Output 
slope
tBBM
 
Figure 3.4 Slopes, Miller plateau and blank time 
 
The following DRV_CONF parameters allow adapting the driver to the MOSFET bridge: 
 
Parameter 
Description 
Setting Comment 
BBMTIME 
 
Break-before-make time setting to ensure non-
overlapping switching of high-side and low-side 
MOSFETs. BBMTIME allows fine tuning of times in 
increments shorter than a clock period.  
For higher times, use BBMCLKS. 
0…24 
time[ns] 
100ns*32/(32-BBMTIME) 
 
Ensure ~30% headroom 
Reset Default: 0 
BBMCLKS 
Like BBMTIME, but in multiple of a clock cycle. 
The longer setting rules (BBMTIME vs. BBMCLKS).  
0…15 
0: off 
Reset Default: OTP 4 or 2 
DRV_ 
STRENGTH 
Selection of gate driver current. Adapts the gate 
driver current to the gate charge of the external 
MOSFETs. 
0…3 
Reset Default = 2 
FILT_ISENSE Filter time constant of sense amplifier to suppress 
ringing and coupling from second coil operation 
Hint: Increase setting if motor chopper noise 
occurs due to cross-coupling of both coils. 
(Reset Default = %00) 
0…3 
00: ~100ns (reset default) 
01: ~200ns 
10: ~300ns 
11: ~400ns 
 
DRV_CONF Parameters 
Use the lowest gate driver strength setting DRVSTRENGTH giving favorable switching slopes, before 
increasing the value of the gate series resistors. A slope time of nominal 40ns to 80ns is absolutely 
sufficient and will normally be covered by the shortest possible Break-Before-Make time setting 
(BBMTIME=0, BBMCLKS=0). 
In case slower slopes have to be used, e.g. with large MOSFETs, ensure that the break-before-make 
time (BBMTIME, optionally use BBMCLKS for times >200ns) sufficiently covers the switching event, in 
order to avoid bridge cross conduction. The shortest break-before-make time, safely covering the 
switching event, gives best results. Add roughly 30% of reserve, to cover production stray of MOSFETs 
and driver. 
 
 


<!-- detected tables -->

| Lx | V 12VOUT |  |  |  |  |  |  |  |  |  |  |  |  |  | Miller plateau |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | 0V |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| V VM BMx 0V -1.2V |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  | Output slope |  |  |  |  | Output slope |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| V VM Hx | +V 12VOUT |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | V VM |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | 0V |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| V -V CX BMx Hx- BMx 0V t BBM Effective break-before-make time |  |  |  |  | Miller plateau |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  |  |  |  | t t BBM BBM |  |  |  |  |  |  |  |  |  |  |  |

|  | Parameter |  |  | Description |  |  | Setting |  |  | Comment |
|---|---|---|---|---|---|---|---|---|---|---|
| BBMTIME | BBMTIME |  | Break-before-make time setting to ensure non- overlapping switching of high-side and low-side MOSFETs. BBMTIME allows fine tuning of times in increments shorter than a clock period. For higher times, use BBMCLKS. |  |  | 0…24 |  |  | time[ns] 100ns*32/(32-BBMTIME) Ensure ~30% headroom Reset Default: 0 |  |
|  |  |  |  |  |  |  |  |  |  |  |
| BBMCLKS |  |  | Like BBMTIME, but in multiple of a clock cycle. The longer setting rules (BBMTIME vs. BBMCLKS). |  |  | 0…15 |  |  | 0: off Reset Default: OTP 4 or 2 |  |
| DRV _ STRENGTH |  |  | Selection of gate driver current. Adapts the gate driver current to the gate charge of the external MOSFETs. |  |  | 0…3 |  |  | Reset Default = 2 |  |
| FILT ISENSE _ |  |  | Filter time constant of sense amplifier to suppress ringing and coupling from second coil operation Hint: Increase setting if motor chopper noise occurs due to cross-coupling of both coils. (Reset Default = %00) |  |  | 0…3 |  |  | 00: ~100ns (reset default) 01: ~200ns 10: ~300ns 11: ~400ns |  |
