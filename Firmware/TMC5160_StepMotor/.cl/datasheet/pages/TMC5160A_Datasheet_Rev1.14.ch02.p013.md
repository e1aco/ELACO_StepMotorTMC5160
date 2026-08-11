# TMC5160A_Datasheet_Rev1.14 — 第2章 · p13

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
13 
 
 
 
www.trinamic.com 
Pin 
TQFP 
QFN 
Type 
Function 
SD_MODE 
21 
21 
DI 
Mode selection input. When tied low, the internal ramp 
generator generates step pulses. When tied high, the STEP/DIR 
inputs control the driver. SD_MODE=0 and SPI_MODE=0 enable 
UART operation. 
SPI_MODE 
22 
22 
DI 
(pd) 
Mode selection input. When tied low with SD_MODE=1, the 
chip is in standalone mode and pins have their CFG functions. 
When tied high, the SPI interface is enabled. Integrated pull 
down resistor. 
ENCB_DCEN_ 
CFG4 
23 
23 
DI 
(pd) 
Encoder B-channel input (when using internal ramp generator) 
or 
DcStep enable input (SD_MODE=1, SPI_MODE=1) – leave open 
or tie to GND for normal operation in this mode (no DcStep).  
Configuration input (SPI_MODE=0) 
ENCA_DCIN_ 
CFG5 
24 
24 
DI 
(pd) 
Encoder A-channel input (when using internal ramp generator) 
or 
DcStep gating input for axis synchronization (SD_MODE=1, 
SPI_MODE=1) or 
Configuration input (SPI_MODE=0) 
ENCN_DCO_ 
CFG6 
25 
26 
DIO 
Encoder N-channel input (SD_MODE=0) or  
DcStep ready output (SD_MODE=1). 
With SD_MODE=0, pull to GND or VCC_IO, if the pin is not used 
for an encoder.  
DIAG0_SWN 
26 
27 
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
DIAG1_SWP 
27 
28 
DIO 
(pd) 
Diagnostics output DIAG1.  
Position compare or DIR output for motion controller 
(SD_MODE=0, SPI_MODE=1). 
Use external pullup resistor with 47k or less in open drain 
mode. 
Single wire I/O (positive) (only with SD_MODE=0 and 
SPI_MODE=0) 
DRV_ENN 
28 
29 
DI 
Enable input. The power stage becomes switched off (all 
motor outputs floating) when this pin becomes driven to a 
high level. 
VCC 
29 
30 
 
5V supply input for digital circuitry within chip. Provide 100nF 
or bigger capacitor to GND (GND plane) near pin. Shall be 
supplied by 5VOUT. A 2.2 or 3.3 Ohm resistor is recommended 
for decoupling noise from 5VOUT. When using an external 
supply, make sure, that VCC comes up before or in parallel to 
5VOUT or VCC_IO, whichever comes up later! 
CPO 
31 
31 
 
Charge pump capacitor output. 
CPI 
32 
32 
 
Charge pump capacitor input. Tie to CPO using 22nF 100V 
capacitor. 
VS 
33 
33 
 
Motor supply voltage. Provide filtering capacity near pin with 
short loop to GND plane. Must be tied to the positive bridge 
supply voltage. 
VCP 
34 
34 
 
Charge pump voltage. Tie to VS using 100nF capacitor. 
CA2 
35 
35 
 
Bootstrap capacitor positive connection. 
HA2 
36 
36 
 
High side gate driver output. 


<!-- detected tables -->

|  | Pin |  |  | TQFP |  |  | QFN |  |  | Type |  |  | Function |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| SD MODE _ |  |  | 21 |  |  | 21 |  |  | DI |  |  | Mode selection input. When tied low, the internal ramp generator generates step pulses. When tied high, the STEP/DIR inputs control the driver. SD MODE=0 and SPI MODE=0 enable _ _ UART operation. |  |  |
| SPI MODE _ |  |  | 22 |  |  | 22 |  |  | DI (pd) |  |  | Mode selection input. When tied low with SD MODE=1, the _ chip is in standalone mode and pins have their CFG functions. When tied high, the SPI interface is enabled. Integrated pull down resistor. |  |  |
| ENCB DCEN _ _ CFG4 |  |  | 23 |  |  | 23 |  |  | DI (pd) |  |  | Encoder B-channel input (when using internal ramp generator) or DcStep enable input (SD MODE=1, SPI MODE=1) – leave open _ _ or tie to GND for normal operation in this mode (no DcStep). Configuration input (SPI MODE=0) |  |  |
| ENCA DCIN _ _ CFG5 |  |  | 24 |  |  | 24 |  |  | DI (pd) |  |  | _ Encoder A-channel input (when using internal ramp generator) or DcStep gating input for axis synchronization (SD MODE=1, _ SPI MODE=1) or _ Configuration input (SPI MODE=0) |  |  |
| ENCN DCO _ _ CFG6 |  |  | 25 |  |  | 26 |  |  | DIO |  |  | _ Encoder N-channel input (SD MODE=0) or _ DcStep ready output (SD MODE=1). _ With SD MODE=0, pull to GND or VCC IO, if the pin is not used _ _ for an encoder. |  |  |
| DIAG0 SWN _ |  |  | 26 |  |  | 27 |  |  | DIO (pu+ pd) |  |  | Diagnostics output DIAG0. Interrupt or STEP output for motion controller (SD MODE=0, _ SPI MODE=1). _ Use external pullup resistor with 47k or less in open drain mode. Single wire I/O (negative) (only with SD MODE=0 and _ SPI MODE=0) _ |  |  |
| DIAG1 SWP _ |  |  | 27 |  |  | 28 |  |  | DIO (pd) |  |  | Diagnostics output DIAG1. Position compare or DIR output for motion controller (SD MODE=0, SPI MODE=1). _ _ Use external pullup resistor with 47k or less in open drain mode. Single wire I/O (positive) (only with SD MODE=0 and _ SPI MODE=0) _ |  |  |
| DRV ENN _ |  |  | 28 |  |  | 29 |  |  | DI |  |  | Enable input. The power stage becomes switched off (all motor outputs floating) when this pin becomes driven to a high level. |  |  |
| VCC |  |  | 29 |  |  | 30 |  |  |  |  |  | 5V supply input for digital circuitry within chip. Provide 100nF or bigger capacitor to GND (GND plane) near pin. Shall be supplied by 5VOUT. A 2.2 or 3.3 Ohm resistor is recommended for decoupling noise from 5VOUT. When using an external supply, make sure, that VCC comes up before or in parallel to 5VOUT or VCC IO, whichever comes up later! |  |  |
|  | CPO |  | 31 |  |  | 31 |  |  |  |  |  | _ Charge pump capacitor output. |  |  |
| CPI |  |  | 32 |  |  | 32 |  |  |  |  |  | Charge pump capacitor input. Tie to CPO using 22nF 100V capacitor. |  |  |
| VS |  |  | 33 |  |  | 33 |  |  |  |  |  | Motor supply voltage. Provide filtering capacity near pin with short loop to GND plane. Must be tied to the positive bridge supply voltage. |  |  |
|  | VCP |  | 34 |  |  | 34 |  |  |  |  |  | Charge pump voltage. Tie to VS using 100nF capacitor. |  |  |
|  | CA2 |  | 35 |  |  | 35 |  |  |  |  |  | Bootstrap capacitor positive connection. |  |  |
|  | HA2 |  | 36 |  |  | 36 |  |  |  |  |  | High side gate driver output. |  |  |
