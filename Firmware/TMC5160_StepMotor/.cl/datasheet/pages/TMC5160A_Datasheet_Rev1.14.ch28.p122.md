# TMC5160A_Datasheet_Rev1.14 — 第28章 · p122

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
122 
 
 
 
www.trinamic.com 
Linear regulator 
DC-Characteristics 
VVS = VVSA = 24.0V 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
Output voltage 
V5VOUT 
TJ = 25°C 
4.80 
5.0 
5.20 
V 
Deviation of output voltage over 
the full temperature range 
V5VOUT(DEV) drivers disabled 
TJ = full range 
 
+/-30 
+/-100 
mV 
Deviation of output voltage over 
the full supply voltage range 
V5VOUT(DEV) drivers disabled, 
internal clock  
TA = 25°C 
VVSA = 10V to 30V 
 
 
+/-50 
mV / 
10V 
Output voltage 
V12VOUT 
operating, internal 
clock 
TJ = 25°C 
10.8 
11.5 
12.2 
V 
 
Clock oscillator and input 
Timing-Characteristics 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
Clock oscillator frequency 
(factory calibrated) 
fCLKOSC 
tJ=-50°C 
 
11.7 
 
MHz 
fCLKOSC 
tJ=50°C 
11.5 
12.0 
12.5 
MHz 
fCLKOSC 
tJ=150°C 
 
12.1 
 
MHz 
External clock frequency 
(operating) 
fCLK 
 
4 
10-16 
18 
MHz 
External clock high / low level 
time  
tCLKH / 
tCLKL 
CLK driven to  
0.1 VVIO / 0.9 VVIO 
16 
 
 
ns 
External clock first pulse to 
trigger switching to external CLK 
tCLKH / 
tCLKL 
CLK driven high 
A-version 
16 
 
 
ns 
External clock first pulse to 
trigger switching to external CLK 
tCLKH / 
tCLKL 
CLK driven high 
non-A-version only 
30 
25 
 
ns 
External clock timeout detection 
in cycles of internal fCLKOSC 
tCLKH1 
CLK driven high 
32 
 
48 
cycles 
fCLKOSC 
 
Short detection 
DC-Characteristics 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
Short to GND / Short to VS 
detector delay (Start of gate 
switch on to short detected) 
Including 100ns filtering time 
tSD0 
FILT_ISENSE=0 
S2xx_LEVEL=6 
shortdelay=0 
0.5 
0.85 
1.1 
µs 
tSD1 
shortdelay=1 
1.1 
1.6 
2.2 
µs 
Short detector level S2VS 
(measurement includes drop in 
sense resistor) 
VBM 
S2VS_LEVEL=15 
1.4 
1.56 
1.72 
V 
S2VS_LEVEL=6 
0.55 
0.625 
0.70 
V 
Short detector level S2G 
VS - VBM 
S2G_LEVEL=15; 
VS<52V 
1.2 
1.56 
1.9 
V 
S2G_LEVEL=15; 
VS<55V 
0.85 
 
 
V 
S2G_LEVEL=6;  
VS<50V 
0.46 
0.625 
0.80 
V 
 


<!-- detected tables -->

| Linear regulator |  |  |  | DC-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  |  |  |  | V = V = 24.0V VS VSA |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
|  | Output voltage |  | V 5VOUT |  |  | T = 25°C J |  |  | 4.80 |  |  | 5.0 |  |  | 5.20 |  |  | V |  |  |
|  | Deviation of output voltage over |  | V 5VOUT(DEV) |  |  | drivers disabled T = full range J |  |  |  |  |  | +/-30 |  |  | +/-100 |  |  | mV |  |  |
|  | the full temperature range |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| Deviation of output voltage over the full supply voltage range | Deviation of output voltage over |  | V 5VOUT(DEV) |  |  | drivers disabled, internal clock T = 25°C A V = 10V to 30V VSA |  |  |  |  |  |  |  |  | +/-50 |  |  | mV / 10V |  |  |
|  | the full supply voltage range |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| Output voltage |  |  | V 12VOUT |  |  | operating, internal clock T = 25°C J |  |  | 10.8 |  |  | 11.5 |  |  | 12.2 |  |  | V |  |  |

|  | Clock oscillator and input |  |  | Timing-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
| Clock oscillator frequency (factory calibrated) | Clock oscillator frequency |  | f CLKOSC |  |  | t=-50°C J |  |  |  |  |  | 11.7 |  |  |  |  |  | MHz |  |  |
|  | (factory calibrated) |  | f CLKOSC |  |  | t=50°C J |  |  | 11.5 |  |  | 12.0 |  |  | 12.5 |  |  | MHz |  |  |
|  |  |  | f CLKOSC |  |  | t=150°C J |  |  |  |  |  | 12.1 |  |  |  |  |  | MHz |  |  |
|  | External clock frequency |  | f CLK |  |  |  |  |  | 4 |  |  | 10-16 |  |  | 18 |  |  | MHz |  |  |
|  | (operating) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | External clock high / low level |  | t / CLKH t CLKL |  |  | CLK driven to 0.1 V / 0.9 V VIO VIO |  |  | 16 |  |  |  |  |  |  |  |  | ns |  |  |
|  | time |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | External clock first pulse to |  | t / CLKH t CLKL |  |  | CLK driven high A-version |  |  | 16 |  |  |  |  |  |  |  |  | ns |  |  |
|  | trigger switching to external CLK |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | External clock first pulse to |  | t / CLKH t CLKL |  |  | CLK driven high non-A-version only |  |  | 30 |  |  | 25 |  |  |  |  |  | ns |  |  |
|  | trigger switching to external CLK |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | External clock timeout detection |  | t CLKH1 |  |  | CLK driven high |  |  | 32 |  |  |  |  |  | 48 |  |  | cycles f CLKOSC |  |  |
|  | in cycles of internal f CLKOSC |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |

|  | Short detection |  |  | DC-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
|  | Short to GND / Short to VS |  | t SD0 |  |  | FILT ISENSE=0 _ S2xx LEVEL=6 _ shortdelay=0 |  |  | 0.5 |  |  | 0.85 |  |  | 1.1 |  |  | µs |  |  |
|  | detector delay (Start of gate |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | switch on to short detected) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Including 100ns filtering time |  | t SD1 |  |  | shortdelay=1 |  |  | 1.1 |  |  | 1.6 |  |  | 2.2 |  |  | µs |  |  |
|  | Short detector level S2VS |  | V BM |  |  | S2VS LEVEL=15 |  |  | 1.4 |  |  | 1.56 |  |  | 1.72 |  |  | V |  |  |
|  | (measurement includes drop in |  |  |  |  | _ S2VS LEVEL=6 _ |  |  | 0.55 |  |  | 0.625 |  |  | 0.70 |  |  | V |  |  |
|  | sense resistor) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| Short detector level S2G | Short detector level S2G |  | V - V S BM |  |  | S2G LEVEL=15; _ VS<52V |  |  | 1.2 |  |  | 1.56 |  |  | 1.9 |  |  | V |  |  |
|  |  |  |  |  |  | S2G LEVEL=15; _ VS<55V |  |  | 0.85 |  |  |  |  |  |  |  |  | V |  |  |
|  |  |  |  |  |  | S2G LEVEL=6; _ VS<50V |  |  | 0.46 |  |  | 0.625 |  |  | 0.80 |  |  | V |  |  |
