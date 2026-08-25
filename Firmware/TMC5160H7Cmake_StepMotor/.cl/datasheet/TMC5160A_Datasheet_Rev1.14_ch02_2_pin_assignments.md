# TMC5160A_Datasheet_Rev1.14 — 第2章 2 Pin Assignments

--- [PAGE 11] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  11 
 
 
 
www.trinamic.com 
2 Pin Assignments 
2.1 Package Outline 
25
26
3724
DRV_ENN
CPO
HA2
BMA1
CA2
VSA
LA1
LA2
VCP
REFL_STEP
CB1
HB1
ENCA_DCIN_CFG5
LB2
HB2
ENCB_DCEN_CFG4
1
TST_MODE
REFR_DIR
VCC_IO
SDO_CFG0
SDI_CFG1
SCK_CFG2
CSN_CFG3
DIAG1_SWP
SRAH
GNDA
12VOUT
SD_MODE
CB2
VS
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
36
35
34
33
32
31
30
29
28
27
48
47
46
45
44
43
42
41
40
39
38
BMB113
CPI
VCC
5VOUT
PAD = GNDD, GNDP
12
SPI_MODE
BMB2
ENCN_DCO_CFG6
DIAG0_SWN
SRAL
HA1
CA1
TMC5160-TA
TQFP-48
SRBL
SRBH
BMA2
LB1
CLK
GNDD
GNDD
 
Figure 2.1 TMC5160-TA package and pinning TQFP-EP 48 (7x7mm² body, 9x9mm² with leads) 
B. Dwersteg, TRINAMIC 2012TMC5160-WA
QFN56 8mm x 8mm
0.5 pitch
1
2
3
4
5
6
7
8
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
37
36
35
34
33
32
31
30
29
47
45
44
43
46
39
42
41
40
28
12
9
10
11
24
25
27
26
38
REFL_STEP
CLK
ENCA_DCIN_CFG5
ENCB_DCEN_CFG4
REFR_DIR
VCC_IO
SDO_CFG0
SDI_CFG1
SCK_CFG2
CSN_CFG3
SD_MODE
SPI_MODE
PAD = GNDD, GNDP
VSA
CB1
HB1
TST_MODE
SRAH
GNDA
12VOUT
BMB1
5VOUT
SRAL
SRBL
SRBH
DRV_ENN
CPO
HA2
CA2
BMA2
VCP
DIAG1_SWP
VS
CPI
VCC
ENCN_DCO_CFG6
DIAG0_SWN
HA1
BMA1
LA2
LB2
HB2
CB2
LB1
BMB2
CA1
LA1
GNDD
 
Figure 2.2 TMC5160-WA package and pinning QFN-WA (8x8mm²) 
--- [PAGE 12] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  12 
 
 
 
www.trinamic.com 
2.2 Signal Descriptions 
 
Pin TQFP QFN Type Function 
HB1 1 2  High side gate driver output. 
CB1 2 3  Bootstrap capacitor positive connection. 
12VOUT 3 4  
Output of internal 11.5V gate voltage regulator and supply pin 
of low side gate drivers. Attach 2.2µF to 10µF ceramic 
capacitor to GND plane near to pin for best performance. Use 
at least 10 times more capacity than for bootstrap capacitors. 
In case an external gate vo ltage supply is available, tie VSA 
and 12VOUT to the external supply. 
VSA 4 5  Analog supply voltage for 11.5V and 5V regulator. Normally 
tied to VS. Provide a 100nF filtering capacitor. 
5VOUT 5 6  
Output of internal 5V regulator. Attach 2.2µF to 10µF ce ramic 
capacitor to GNDA near to pin for best performance. Output 
for VCC supply of the chip.  
GNDA 6 7  Analog GND. Connect to GND plane near pin. 
SRAL 7 8 AI 
Sense resistor GND connection for phase A. Connect to the 
GND side of the sense resistor in ord er to compensate for 
voltage drop on the GND interconnection. 
SRAH 8 9 AI 
Sense resistor for phase A. Connect to the upper side of the 
sense resistor. A Kelvin connection is preferred with high 
motor currents. Symmetrical RC -Filtering may be added for 
SRAL and SRAH to eliminate high frequency switching spikes 
from other drives or switching of coil B. 
SRBH 9 10 AI 
Sense resistor for phase B. Connect to the upper side of the 
sense resistor. A  Kelvin connection is preferred with high 
motor currents. Symmetri cal RC -Filtering may be added for 
SRBL and SRBH to eliminate high frequency switching spikes 
from other drives or switching of coil A. 
SRBL 10 11 AI 
Sense resistor GND connection for phase B. Connect to the 
GND side of the sense resistor in order to compe nsate for 
voltage drop on the GND interconnection. 
TST_MODE 11 12 DI Test mode input. Tie to GND using short wire. 
CLK 12 13 DI 
CLK input. Tie to GND using short wire for internal cl ock or 
supply external clock. Internal clock -fail over circuit protects 
against loss of external clock signal. 
CSN_CFG3 13 14 DI SPI chip select input (negative active) (SPI_MODE=1) or 
Configuration input (SPI_MODE=0) 
SCK_CFG2 14 15 DI SPI serial clock input (SPI_MODE=1) or 
Configuration input (SPI_MODE=0) 
SDI_CFG1 15 16 DI 
SPI data input (SPI_MODE=1) or  
Configuration input (SPI_MODE=0) or  
Next address input (NAI) for single wire interface. 
SDO_CFG0 16 17 DIO 
SPI data output (tristate) (SPI_MODE=1) or  
Configuration input (SPI_MODE=0) or  
Next address output (NAO) for single wire interface. 
REFL_STEP 17 18 DI Left reference input (for internal ramp generator) or 
STEP input when (SD_MODE=1). 
REFR_DIR 18 19 DI Right reference input (for internal ramp generator) or 
DIR input (SD_MODE=1). 
GNDD 19, 
30 
25, 
Pad  Digital GND. Connect to GND plane near pin. 
VCC_IO 20 20  3.3V to 5V IO supply voltage for all digital pins. 
--- [PAGE 13] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  13 
 
 
 
www.trinamic.com 
Pin TQFP QFN Type Function 
SD_MODE 21 21 DI 
Mode selection input. When tied low, the internal ramp 
generator generates step pulses. When tied high, the STEP/DIR 
inputs control the driver . SD_MODE=0 and SPI_MODE=0  enable 
UART operation. 
SPI_MODE 22 22 DI 
(pd) 
Mode selection input. When tied low with SD_MODE=1, the 
chip is in standalone mode and pins have their CFG functions. 
When tied high, the SPI interface is enabled. Integrated pull 
down resistor. 
ENCB_DCEN_ 
CFG4 23 23 DI 
(pd) 
Encoder B-channel input (when using internal ramp generator) 
or 
DcStep enable input (SD_MODE=1, SPI_MODE=1) – leave open 
or tie to GND for normal operation in this mode (no DcStep).  
Configuration input (SPI_MODE=0) 
ENCA_DCIN_ 
CFG5 24 24 DI 
(pd) 
Encoder A-channel input (when using internal ramp generator) 
or 
DcStep gating input for axis synchronization (SD_MODE=1, 
SPI_MODE=1) or 
Configuration input (SPI_MODE=0) 
ENCN_DCO_ 
CFG6 25 26 DIO 
Encoder N-channel input (SD_MODE=0) or  
DcStep ready output (SD_MODE=1). 
With SD_MODE=0, pull to GND or VCC_IO, if the pin is not used 
for an encoder.  
DIAG0_SWN 26 27 
DIO 
(pu+ 
pd) 
Diagnostics output DIAG0.  
Interrupt or STEP output for motion controller (SD_MODE=0, 
SPI_MODE=1). 
Use external pullup resistor with 47k or less in open drain 
mode.  
Single wire I/O (negative) (only with SD_MODE=0 and 
SPI_MODE=0) 
DIAG1_SWP 27 28 DIO 
(pd) 
Diagnostics output DIAG1.  
Position compare or DIR output for motion controller 
(SD_MODE=0, SPI_MODE=1). 
Use external pullup resistor with 47k or less in open drain 
mode. 
Single wire I/O (positive) (only with SD_MODE=0 and 
SPI_MODE=0) 
DRV_ENN 28 29 DI 
Enable input. The power stage becomes switched off (all 
motor outputs floating) when this pin becomes d riven to a 
high level. 
VCC 29 30  
5V supply input for digital circuitry within chip. Provide 100nF 
or bigger capacitor to GND (GND plane) near pin. Shall be 
supplied by 5VOUT. A 2.2 or 3.3 Ohm resistor is recommended 
for d ecoupling noise from 5VOUT. When using an external 
supply, make sure, that VCC comes up before or in parallel to 
5VOUT or VCC_IO, whichever comes up later! 
CPO 31 31  Charge pump capacitor output. 
CPI 32 32  Charge pump capacitor in put. Tie to CPO using 22nF 100V 
capacitor. 
VS 33 33  
Motor supply voltage. Provide filtering capacity near pin with 
short loop to GND plane. Must be tied to the positive bridge 
supply voltage. 
VCP 34 34  Charge pump voltage. Tie to VS using 100nF capacitor. 
CA2 35 35  Bootstrap capacitor positive connection. 
HA2 36 36  High side gate driver output. 
--- [PAGE 14] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  14 
 
 
 
www.trinamic.com 
Pin TQFP QFN Type Function 
BMA2 37 37  Bridge Center and bootstrap capacitor negative connection. 
LA2 38 38  Low side gate driver output. 
LA1 39 39  Low side gate driver output. 
BMA1 40 40  Bridge Center and bootstrap capacitor negative connection. 
HA1 41 41  High side gate driver output. 
CA1 42 42  Bootstrap capacitor positive connection. 
CB2 43 43  Bootstrap capacitor positive connection. 
HB2 44 44  High side gate driver output. 
BMB2 45 45  Bridge Center and bootstrap capacitor negative connection. 
LB2 46 46  Low side gate driver output. 
LB1 47 47  Low side gate driver output. 
BMB1 48 1  Bridge Center and bootstrap capacitor negative connection. 
Exposed die 
pad - -  
Connect the exposed die pad to a GND plane. Provide as many 
as possible vias for heat transfer to GND plane. Serves as GND 
pin for the low side gate drivers. Ensure low loop inductivity 
to sense resistor GND. 
 
*(pd) denominates a pin with pulldown resistor 
* All digital pins DI, DIO and DO use VCC_IO level and contain protection diodes to GND and VCC_IO 
* All digital inputs DI and DIO have internal Schmitt-Triggers 
 
  
