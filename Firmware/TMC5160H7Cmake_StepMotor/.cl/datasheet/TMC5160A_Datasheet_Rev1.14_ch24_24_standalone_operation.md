# TMC5160A_Datasheet_Rev1.14 — 第24章 24 Standalone Operation

--- [PAGE 117] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  117 
 
 
 
www.trinamic.com 
24 Standalone Operation 
For standalone operation, no SPI interface is required to configure the TMC5160. All pins with suffix 
CFG0 to CFG6 have a special meaning in this mode and can bei tied either to VCC_IO or to GND.  
47R
47R
LSVCC_IO
TMC5160
Step&Dir input 
with microPlyer
STEP
DIR
5V Voltage 
regulator
charge pump
22n
100V
100n 
16V
CLK_IN
+VM
5VOUT
VSA
2.2µ
+VIO
DRV_ENN
GNDD
GNDA
TST_MODE
DIE PAD
VCC
opt. ext. clock
12-16MHz
3.3V or 5V
I/O voltage
100n
100n
Controller
LS
stepper
motor
N
S
BMA2
Chopper
100n
SRAH
CE
Optional use lower 
voltage down to 12V
2R2
470n
Use low inductivity SMD 
type, e.g. 1210 or 2512 
resistor for RS!
SD_MODE
SPI_MODE
opt. driver enable
B.Dwersteg, © 
TRINAMIC 2014
RS
SRAL
LA1
LA2
HA1
HA2
BMA1
HS
HS
CA1
CB
CA2
CB +VM
LS
LS
BMB2
SRBH
RS
SRBL
LB1
LB2
HB1
HB2
BMB1
HS
HS
CB1
CB
CB2
CB
+VM
Standalone mode
CPI
CPO
VCP
VS
11.5V Voltage 
regulator
12VOUT
2.2µ
mode selection
Bootstrap capacitors CB: 
220nF for MOSFETs with QG<20nC, 470nF for larger QG
470n
470n
Keep inductivity of the fat 
interconnections as small 
as possible to avoid 
undershoot of BM <-5V!
RG
RG
RG
RG RG
RG
RG
RG
Slope control resistors RG: Adapt to MOSFET to yield slopes of roughly 
100ns. Slope must be slower than bulk diode recovery time.
47R
47Rpd
+VIO
Status out
(open drain)
Configuration 
interface 
(GND or VCC_IO 
level)
CFG0
CFG1
CFG3
CFG2
DIAG0
DIAG1
Microstep Resolution 
8 / 16 / 32 / 64
unused
unused
CFG4
CFG5
CFG6 B.Dwersteg, © 
TRINAMIC 2014
Run Current Setting 
16 / 18 / 20 / 22 / 
24 / 26 / 28 / 31
spreadCycle (GND) / 
stealthChop (VCC_IO)
 Current Reduction 
Enable (VCC_IO)
 
Figure 24.1 Standalone operation with TMC5160 (pins shown with their standalone mode names) 
 
To activate standalone mode, tie pin SPI_MODE to GND  and pin SD_MODE high. In this mode, the 
driver acts as a pure STEP and DIR driver. SPI and single wire are  off. The driver works in SpreadCycle 
mode or StealthChop mode. With regard to the register set, the following settings are activated: 
 
The following settings are affected by the CFG pins in order to ensure correct configuration: 
 
CFG0/CFG1: CONFIGURATION OF MICROSTEP RESOLUTION FOR STEP INPUT 
CFG1 CFG0 Microstep Setting  
GND GND 8 microsteps, MRES=5 
GND VCC_IO 16 microsteps, MRES=4 
VCC_IO GND 32 microsteps, MRES=3 
VCC_IO VCC_IO 64 microsteps, MRES=2 
 
--- [PAGE 118] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  118 
 
 
 
www.trinamic.com 
CFG4/CFG3/CFG2: CONFIGURATION OF RUN CURRENT 
CFG4 CFG3 CFG2 IRUN Setting  
GND GND GND IRUN=16 
GND GND VCC_IO IRUN=18 
GND VCC_IO GND IRUN=20 
GND VCC_IO VCC_IO IRUN=22 
VCC_IO GND GND IRUN=24 
VCC_IO GND VCC_IO IRUN=26 
VCC_IO VCC_IO GND IRUN=28 
VCC_IO VCC_IO VCC_IO IRUN=31 
 
CFG5: SELECTION OF CHOPPER MODE 
CFG5 Chopper Setting 
GND  SpreadCycle operation. (TOFF=3) 
VCC_IO StealthChop operation. (GCONF.en_PWM_mode=1) 
 
CFG6: CONFIGURATION OF HOLD CURRENT REDUCTION 
CFG6*) Chopper Setting 
GND  No hold current reduction. IHOLD=IRUN 
VCC_IO Reduction to 50%. IHOLD=1/2 IRUN 
 
 
Hint 
Be sure to allow the motor to rest for at least 100ms (assuming a minimum of  10MHz f CLK) before 
starting a motion using StealthChop. This will allow the current regulation to set the initial motor 
current. 
 
 
*) CFG6: Attention 
CFG6 pin draws significant current (20mA) when driven to a different level than CFG5, because the 
output driver tries to make CFG6 level equal to CFG5. Therefore, a 0 Ohm resistor is required to pull 
up/down CFG6. Due to this, setting CFG6 different from C FG5 is only rec ommended with external 
VCC_IO supply at 3.3V level. 
 
 
Attention: 
DIAG outputs are not configured per default. They can be activated using the interfaces before 
switching to standalone mode.  
  
