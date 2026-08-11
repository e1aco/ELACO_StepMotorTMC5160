# TMC5160A_Datasheet_Rev1.14 — 第28章 · p121

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
121 
 
 
 
www.trinamic.com 
28.2 DC and Timing Characteristics 
DC characteristics contain the spread of values guaranteed within the specified supply voltage range 
unless otherwise specified. Typical values represent the average value of all parts measured at +25°C. 
Temperature variation also causes stray to some values. A device with typical values will not leave 
Min/Max range within the full temperature range. 
 
Power supply current 
DC-Characteristics 
VVS = VVSA = 24.0V 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
Total supply current, driver 
disabled IVS + IVSA 
IS 
fCLK=12MHz / internal 
clock 
 
18 
24 
mA 
VSA supply current (VS and VSA 
separated) 
IVSA 
fCLK=12MHz / internal 
clock, driver disabled 
 
15 
 
mA 
Total supply current, operating, 
MOSFETs AOD4126, IVS + IVSA 
IS 
fCLK=12MHz, 23.4kHz 
chopper, no load 
 
25 
 
mA 
Internal current consumption 
from 5V supply on VCC pin 
IVCC 
fCLK=12MHz 
 
10 
 
mA 
Internal current consumption 
from 5V supply on VCC pin 
IVCC 
fCLK=16MHz 
 
12.5 
 
mA 
IO supply current on VCC_IO 
(typ. at 5V) 
IVIO 
no load on outputs, 
inputs at VIO or GND 
Excludes pullup / 
pull-down resistors 
 
15 
30 
µA 
 
Motor driver section 
DC- and Timing-Characteristics 
VVS = 24.0V; Tj=50°C 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
RDSON lowside off driver 
RONL 
Gate off 
 
1.8 
3 
Ω 
RDSON highside off driver 
RONH 
Gate off 
 
2.2 
3.5 
Ω 
Gate drive current low side 
MOSFET turning on at 2V VGS 
ISLPON0 
DRVSTRENGTH=0 
 
200 
 
mA 
ISLPON2 
DRVSTRENGTH=2 
 
400 
 
mA 
ISLPON3 
DRVSTRENGTH=3 
 
600 
 
mA 
Gate drive current high side 
MOSFET turning on at 2V VGS 
ISLPON0 
DRVSTRENGTH=0 
 
150 
 
mA 
ISLPON2 
DRVSTRENGTH=2 
 
300 
 
mA 
ISLPON3 
DRVSTRENGTH=3 
 
450 
 
mA 
BBM time via internal delay (start 
of gate switching off to start of 
gate switching on) 
tBBM0 
BBMCLKS=0 
BBMTIME=0 
75 
100 
 
ns 
tBBM16 
BBMTIME=16 
 
200 
 
ns 
tBBM16 
BBMTIME=24 
 
375 
500 
ns 
 
Charge pump 
DC-Characteristics 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
Charge pump output voltage 
VVCP-VVS 
operating 
V12VOUT -
2 
V12VOUT -
1 
 
V 
Charge pump voltage threshold 
for undervoltage detection 
VVCP-VVS 
rising, using internal 
5V regulator voltage 
4.5 
5 
6.5 
V 
Charge pump frequency 
fCP 
 
 
1/16 
fCLKOSC 
 
 
 


<!-- detected tables -->

| Power supply current |  |  |  | DC-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  |  |  |  | V = V = 24.0V VS VSA |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
|  | Total supply current, driver |  | I S |  |  | f =12MHz / internal CLK clock |  |  |  |  |  | 18 |  |  | 24 |  |  | mA |  |  |
|  | disabled I + I VS VSA |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | VSA supply current (VS and VSA |  | I VSA |  |  | f =12MHz / internal CLK clock, driver disabled |  |  |  |  |  | 15 |  |  |  |  |  | mA |  |  |
|  | separated) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Total supply current, operating, |  | I S |  |  | f =12MHz, 23.4kHz CLK chopper, no load |  |  |  |  |  | 25 |  |  |  |  |  | mA |  |  |
|  | MOSFETs AOD4126, I + I VS VSA |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Internal current consumption |  | I VCC |  |  | f =12MHz CLK |  |  |  |  |  | 10 |  |  |  |  |  | mA |  |  |
|  | from 5V supply on VCC pin |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Internal current consumption |  | I VCC |  |  | f =16MHz CLK |  |  |  |  |  | 12.5 |  |  |  |  |  | mA |  |  |
|  | from 5V supply on VCC pin |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| IO supply current on VCC IO _ (typ. at 5V) | IO supply current on VCC IO |  | I VIO |  |  | no load on outputs, inputs at V or GND IO Excludes pullup / pull-down resistors |  |  |  |  |  | 15 |  |  | 30 |  |  | µA |  |  |
|  | _ (typ. at 5V) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |

| Motor driver section |  |  |  | DC- and Timing-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  |  |  |  | V = 24.0V; Tj=50°C VS |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
|  | RDS lowside off driver ON |  | R ONL |  |  | Gate off |  |  |  |  |  | 1.8 |  |  | 3 |  |  | Ω |  |  |
|  | RDS highside off driver ON |  | R ONH |  |  | Gate off |  |  |  |  |  | 2.2 |  |  | 3.5 |  |  | Ω |  |  |
| Gate drive current low side MOSFET turning on at 2V V GS | Gate drive current low side |  | I SLPON0 |  |  | DRVSTRENGTH=0 |  |  |  |  |  | 200 |  |  |  |  |  | mA |  |  |
|  | MOSFET turning on at 2V V GS |  | I SLPON2 |  |  | DRVSTRENGTH=2 |  |  |  |  |  | 400 |  |  |  |  |  | mA |  |  |
|  |  |  | I SLPON3 |  |  | DRVSTRENGTH=3 |  |  |  |  |  | 600 |  |  |  |  |  | mA |  |  |
| Gate drive current high side MOSFET turning on at 2V V GS |  |  | I SLPON0 |  |  | DRVSTRENGTH=0 |  |  |  |  |  | 150 |  |  |  |  |  | mA |  |  |
|  |  |  | I SLPON2 |  |  | DRVSTRENGTH=2 |  |  |  |  |  | 300 |  |  |  |  |  | mA |  |  |
|  |  |  | I SLPON3 |  |  | DRVSTRENGTH=3 |  |  |  |  |  | 450 |  |  |  |  |  | mA |  |  |
| BBM time via internal delay (start of gate switching off to start of gate switching on) |  |  | t BBM0 |  |  | BBMCLKS=0 BBMTIME=0 |  |  | 75 |  |  | 100 |  |  |  |  |  | ns |  |  |
|  |  |  | t BBM16 |  |  | BBMTIME=16 |  |  |  |  |  | 200 |  |  |  |  |  | ns |  |  |
|  |  |  | t BBM16 |  |  | BBMTIME=24 |  |  |  |  |  | 375 |  |  | 500 |  |  | ns |  |  |

|  | Charge pump |  |  | DC-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
| Charge pump output voltage | Charge pump output voltage |  | V -V VCP VS |  |  | operating |  |  | V - 12VOUT 2 |  |  | V - 12VOUT 1 |  |  |  |  |  | V |  |  |
|  | Charge pump voltage threshold |  | V -V VCP VS |  |  | rising, using internal 5V regulator voltage |  |  | 4.5 |  |  | 5 |  |  | 6.5 |  |  | V |  |  |
|  | for undervoltage detection |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| Charge pump frequency | Charge pump frequency |  | f CP |  |  |  |  |  |  |  |  | 1/16 f CLKOSC |  |  |  |  |  |  |  |  |
