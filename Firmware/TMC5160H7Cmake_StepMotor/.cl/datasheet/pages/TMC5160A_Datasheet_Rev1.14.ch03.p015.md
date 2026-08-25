# TMC5160A_Datasheet_Rev1.14 — 第3章 · p15

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  15 
 
 
 
www.trinamic.com 
3 Sample Circuits 
The following sample circuits show the required external components in different operation and 
supply modes. The connection of the bus interface and further digital signals are left out for clarity. 
3.1 Standard Application Circuit 
47R
47R
LS
VCC_IO
TMC5160
SPI interface
CSN
SCK
SDO
SDI
reference switch 
processing
REFL/STEP
REFR/DIR
DIAG / INT out 
and
Single wire 
interface
5V Voltage 
regulator
charge pump
22n
100V
100n 
16V
DIAG0/SWN
CLK_IN
DIAG1/SWP
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
Encoder 
unit
A B N
ENCB_DCEN
ENCA_DCIN
ENCN_DCO
Encoder input / 
dcStep control in S/D 
mode
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
Both GND: UART mode
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
47R
+VIO
pd pd pd
+VIO
 
Figure 3.1 Standard application circuit 
The standard application circuit uses a minim um set of additional components. Eight MOSFETs are 
selected for the desired current, voltage and package type. Two sense resis tors set the motor coil 
current. See chapter 9 to choose the right value for sense resistors. Use low  ESR capacitors for 
filtering the power supply. A minimum capacity of 100µF per ampere of coil current near to the power 
bridge is recommended for best performance. The capacitors need  to cope with the current ripple 
caused by chopper operation. Current ri pple in the supply capacitors also depends on the power 
supply internal resistance and cable length. VCC_IO can be supplied from 5VOUT, or from an external 
source, e.g. a 3.3V regulator. In order to minimize linear voltage regulator power dissipat ion of th e 
internal 5V and 11.5V voltage regulators in applications where VM is high, a different (lower) supply 
voltage should be used for VSA (see chapter 3.2).  
 
Basic layout hints 
Place sense resistors and all filter capacitors as cl ose as possible to the power MOSFETs. Place the 
TMC5160 near to the MOSFETs and use short interconnection lines in order to minimize parasitic trace 
inductance. Use a solid common GND for all GND , GNDA and GNDD  connections, also for sense 
resistor GND. Connect 5VOUT filtering capacitor directly to 5VOUT and GNDA pin. See layout hints for 
more details. Low ESR electrolytic capacitors are recommended for VS filtering.  
 
Hint 
In safety critical applications, V S and the bridge may be supplied by a separate, swi tched supply in 
order to realize safe torque off. Make sure that the slope at VS does not exceed 1V/µs.  
