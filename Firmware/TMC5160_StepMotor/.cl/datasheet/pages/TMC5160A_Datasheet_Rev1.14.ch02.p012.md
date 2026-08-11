# TMC5160A_Datasheet_Rev1.14 — 第2章 · p12

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
12 
 
 
 
www.trinamic.com 
2.2 Signal Descriptions 
 
Pin 
TQFP 
QFN 
Type 
Function 
HB1 
1 
2 
 
High side gate driver output. 
CB1 
2 
3 
 
Bootstrap capacitor positive connection. 
12VOUT 
3 
4 
 
Output of internal 11.5V gate voltage regulator and supply pin 
of low side gate drivers. Attach 2.2µF to 10µF ceramic 
capacitor to GND plane near to pin for best performance. Use 
at least 10 times more capacity than for bootstrap capacitors. 
In case an external gate voltage supply is available, tie VSA 
and 12VOUT to the external supply. 
VSA 
4 
5 
 
Analog supply voltage for 11.5V and 5V regulator. Normally 
tied to VS. Provide a 100nF filtering capacitor. 
5VOUT 
5 
6 
 
Output of internal 5V regulator. Attach 2.2µF to 10µF ceramic 
capacitor to GNDA near to pin for best performance. Output 
for VCC supply of the chip.  
GNDA 
6 
7 
 
Analog GND. Connect to GND plane near pin. 
SRAL 
7 
8 
AI 
Sense resistor GND connection for phase A. Connect to the 
GND side of the sense resistor in order to compensate for 
voltage drop on the GND interconnection. 
SRAH 
8 
9 
AI 
Sense resistor for phase A. Connect to the upper side of the 
sense resistor. A Kelvin connection is preferred with high 
motor currents. Symmetrical RC-Filtering may be added for 
SRAL and SRAH to eliminate high frequency switching spikes 
from other drives or switching of coil B. 
SRBH 
9 
10 
AI 
Sense resistor for phase B. Connect to the upper side of the 
sense resistor. A Kelvin connection is preferred with high 
motor currents. Symmetrical RC-Filtering may be added for 
SRBL and SRBH to eliminate high frequency switching spikes 
from other drives or switching of coil A. 
SRBL 
10 
11 
AI 
Sense resistor GND connection for phase B. Connect to the 
GND side of the sense resistor in order to compensate for 
voltage drop on the GND interconnection. 
TST_MODE 
11 
12 
DI 
Test mode input. Tie to GND using short wire. 
CLK 
12 
13 
DI 
CLK input. Tie to GND using short wire for internal clock or 
supply external clock. Internal clock-fail over circuit protects 
against loss of external clock signal. 
CSN_CFG3 
13 
14 
DI 
SPI chip select input (negative active) (SPI_MODE=1) or 
Configuration input (SPI_MODE=0) 
SCK_CFG2 
14 
15 
DI 
SPI serial clock input (SPI_MODE=1) or 
Configuration input (SPI_MODE=0) 
SDI_CFG1 
15 
16 
DI 
SPI data input (SPI_MODE=1) or  
Configuration input (SPI_MODE=0) or  
Next address input (NAI) for single wire interface. 
SDO_CFG0 
16 
17 
DIO 
SPI data output (tristate) (SPI_MODE=1) or  
Configuration input (SPI_MODE=0) or  
Next address output (NAO) for single wire interface. 
REFL_STEP 
17 
18 
DI 
Left reference input (for internal ramp generator) or 
STEP input when (SD_MODE=1). 
REFR_DIR 
18 
19 
DI 
Right reference input (for internal ramp generator) or 
DIR input (SD_MODE=1). 
GNDD 
19, 
30 
25, 
Pad 
 
Digital GND. Connect to GND plane near pin. 
VCC_IO 
20 
20 
 
3.3V to 5V IO supply voltage for all digital pins. 


<!-- detected tables -->

|  | Pin |  |  | TQFP |  |  | QFN |  |  | Type |  |  | Function |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | HB1 |  | 1 |  |  | 2 |  |  |  |  |  | High side gate driver output. |  |  |
|  | CB1 |  | 2 |  |  | 3 |  |  |  |  |  | Bootstrap capacitor positive connection. |  |  |
| 12VOUT |  |  | 3 |  |  | 4 |  |  |  |  |  | Output of internal 11.5V gate voltage regulator and supply pin of low side gate drivers. Attach 2.2µF to 10µF ceramic capacitor to GND plane near to pin for best performance. Use at least 10 times more capacity than for bootstrap capacitors. In case an external gate voltage supply is available, tie VSA and 12VOUT to the external supply. |  |  |
| VSA |  |  | 4 |  |  | 5 |  |  |  |  |  | Analog supply voltage for 11.5V and 5V regulator. Normally tied to VS. Provide a 100nF filtering capacitor. |  |  |
| 5VOUT |  |  | 5 |  |  | 6 |  |  |  |  |  | Output of internal 5V regulator. Attach 2.2µF to 10µF ceramic capacitor to GNDA near to pin for best performance. Output for VCC supply of the chip. |  |  |
|  | GNDA |  | 6 |  |  | 7 |  |  |  |  |  | Analog GND. Connect to GND plane near pin. |  |  |
| SRAL |  |  | 7 |  |  | 8 |  |  | AI |  |  | Sense resistor GND connection for phase A. Connect to the GND side of the sense resistor in order to compensate for voltage drop on the GND interconnection. |  |  |
| SRAH |  |  | 8 |  |  | 9 |  |  | AI |  |  | Sense resistor for phase A. Connect to the upper side of the sense resistor. A Kelvin connection is preferred with high motor currents. Symmetrical RC-Filtering may be added for SRAL and SRAH to eliminate high frequency switching spikes from other drives or switching of coil B. |  |  |
| SRBH |  |  | 9 |  |  | 10 |  |  | AI |  |  | Sense resistor for phase B. Connect to the upper side of the sense resistor. A Kelvin connection is preferred with high motor currents. Symmetrical RC-Filtering may be added for SRBL and SRBH to eliminate high frequency switching spikes from other drives or switching of coil A. |  |  |
| SRBL |  |  | 10 |  |  | 11 |  |  | AI |  |  | Sense resistor GND connection for phase B. Connect to the GND side of the sense resistor in order to compensate for voltage drop on the GND interconnection. |  |  |
|  | TST MODE |  | 11 |  |  | 12 |  |  | DI |  |  | Test mode input. Tie to GND using short wire. |  |  |
| _ CLK |  |  | 12 |  |  | 13 |  |  | DI |  |  | CLK input. Tie to GND using short wire for internal clock or supply external clock. Internal clock-fail over circuit protects against loss of external clock signal. |  |  |
| CSN CFG3 _ |  |  | 13 |  |  | 14 |  |  | DI |  |  | SPI chip select input (negative active) (SPI MODE=1) or _ Configuration input (SPI MODE=0) |  |  |
| SCK CFG2 _ |  |  | 14 |  |  | 15 |  |  | DI |  |  | _ SPI serial clock input (SPI MODE=1) or _ Configuration input (SPI MODE=0) |  |  |
| SDI CFG1 _ |  |  | 15 |  |  | 16 |  |  | DI |  |  | _ SPI data input (SPI MODE=1) or _ Configuration input (SPI MODE=0) or _ Next address input (NAI) for single wire interface. |  |  |
| SDO CFG0 _ |  |  | 16 |  |  | 17 |  |  | DIO |  |  | SPI data output (tristate) (SPI MODE=1) or _ Configuration input (SPI MODE=0) or _ Next address output (NAO) for single wire interface. |  |  |
| REFL STEP _ |  |  | 17 |  |  | 18 |  |  | DI |  |  | Left reference input (for internal ramp generator) or STEP input when (SD MODE=1). _ |  |  |
| REFR DIR _ |  |  | 18 |  |  | 19 |  |  | DI |  |  | Right reference input (for internal ramp generator) or DIR input (SD MODE=1). _ |  |  |
| GNDD |  |  | 19, 30 |  |  | 25, Pad |  |  |  |  |  | Digital GND. Connect to GND plane near pin. |  |  |
|  | VCC IO |  | 20 |  |  | 20 |  |  |  |  |  | 3.3V to 5V IO supply voltage for all digital pins. |  |  |
