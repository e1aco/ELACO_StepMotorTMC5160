# TMC5160A_Datasheet_Rev1.14 — 第1章 · p6

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  6 
 
 
 
www.trinamic.com 
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
STEP
DIR
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
DIAG0
CLK_IN
DIAG1
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
LS
stepper
motor
N
S
BMA2
100n
SRAH
CE
2R2
470n
DCEN
DCIN
DCO
dcStep control
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
CPI
CPO
VCP
VS
11.5V Voltage 
regulator
12VOUT
2.2µ
mode selection
470n
470n
RG
RG
RG
RG RG
RG
RG
RG
47R
47R
+VIO
pd pd pd
+VIO
Stepper driver 
Protection
& diagnostics
spreadCycle & 
stealthChop 
Chopperprogrammable
sine table
4*256 entry
stallGuard2™
coolStep™
xControl register 
set
Interface
dcStep™
spreadCycle & 
stealthChop 
motor driver
B.Dwersteg, © 
TRINAMIC 2014
step multiplier
microPlyer™ 
Standstill 
current 
reduction
 
Figure 1.2 TMC5160 STEP/DIR application diagram 
47R
47R
LS
TMC5160
STEP
DIR
5V Voltage 
regulator
charge pump
22n
100V
100n 
16V
+VM
5VOUT
VSA
2.2µ
DRV_ENN
GNDD
GNDA
TST_MODE
DIE PAD
VCC
100n
LS
stepper
motor
N
S
BMA2
100n
SRAH
CE
2R2
470n
dcStep control
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
CPI
CPO
VCP
VS
11.5V Voltage 
regulator
12VOUT
2.2µ
470n
470n
RG
RG
RG
RG RG
RG
RG
RG
47R
47R
Stepper driver 
Protection
& diagnostics
spreadCycle & 
stealthChop 
Chopperprogrammable
sine table
4*256 entry
x
Control register 
set (default 
values)
B.Dwersteg, © 
TRINAMIC 2014
step multiplier
microPlyer  
Standstill 
current 
reduction
VCC_IO
CLK_IN
+VIO
opt. ext. clock
12-16MHz
3.3V or 5V
I/O voltage
100n
SD_MODE
SPI_MODE
Standalone mode
mode selection
pd
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
pd
pd
OTP
 
Figure 1.3 TMC5160 standalone driver application diagram 
1.1 Key Concepts 
The TMC5160 implements advanced features which are exclusive to TRINAMIC products. These features 
contribute toward greater precision, greater energy efficiency, higher reliability, smoother motion, and 
cooler operation in many stepper motor applications. 
 
