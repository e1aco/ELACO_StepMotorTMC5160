# TMC5160A_Datasheet_Rev1.14 — 第1章 · p6

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
6 
 
 
 
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
CB
+VM
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
RG
RG
RG
RG
RG
47R
47R
+VIO
pd
pd
pd
+VIO
Stepper driver 
Protection
& diagnostics
spreadCycle & 
stealthChop 
Chopper
programmable
sine table
4*256 entry
stallGuard2™
coolStep™
x
Control register 
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
CB
+VM
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
RG
RG
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
Chopper
programmable
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
CFG6
B.Dwersteg, © 
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
 


<!-- detected tables -->

| VM 12 02 0n V 1 10 60 Vn 100n STEP DIR CPO CPI VCP VS VSA CB2 12VOUT 11.5V Voltage TMC5160 charge pump HS HB2 CCB |  |  |  |  |  |  |
|---|---|---|---|---|---|---|
|  |  |  | 100n VS CB2 HS HB2 CB C |  |  |  |
|  | 2.2µ 5VOUT 2.2µ 2R2 VCC | regulator step multiplier 5V Voltage microPlyer™ regulator Standstill current reduction I n te r fa c e s p m o to r d r ivs ete a lth C h o pr e a d C y c le & r SPI interface spreadCycle & Contro sl er tegister pr 4o s *g i 2nr 5ea m t eam nb ta le rb yle x Ss tet Ce pa h pl o eth p C p dh e ro r ivp DIAG / INT out 6 r e r Singa ln e d wire TB R.D INw Ae Mrs It Ce g 2, 0 1© 4 T&B R .PID dNrw ioAaetMgers IncCtet o ig 2so, 0t n© i1c4 s interface coolStep™ stallGuard2™ dcStep™ mode selection | HS LS LS | CB1 B HB1 BMB1RG |  |  |
| 470n CSN SCK SDI SDO DIAG1 |  |  |  | BMB2 LB1 |  |  |
| DIAG0 k z CLK_IN IO |  |  | HS HS LS LS | HA2 CA1 HA1 CB BMA1RG BMA2 LA1 RG LA2 |  |  |
|  |  |  |  | RG LA2 |  | RG |
|  |  |  |  | SRAH 47R SRAL |  |  |

| VM 12 02 0n V 1 10 60 Vn 100n STEP DIR CPO CPI VCP VS VSA CB2 12VOUT 11.5V Voltage TMC5160 charge pump HS HB2 CCB |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|
|  |  |  |  | 1 10 60 Vn 100n VS CB2 HS HB2 CB C |  |  |  |
|  | 2.2µ 5VOUT 2.2µ 2R2 VCC | regulator step multiplier 5V Voltage microPlyer regulator Standstill current reduction (GC No Dn in f lti o eg e vrru ef Vr a la )Cct e Cio _n IO Co sn et vtr o a( ldl er ee f sag )uis ltt er pr 4o s *g i 2nr 5ea m t eam b nl ta e rb yle x Ssp s tetr Cee pa ha pl od ethC p y C p dc h e rl o ire p e& pd u 6 r v r pd B.Dwersteg, © TB R.D INw Ae Mrs It Ce g 2, 0 © 14 T&B R .PID dNrw ioAaetMgres IncCte ot ig 2so, 0t n© 1ic4 s TRINAMIC 2014 (oS pta et nu s d ro au int ) OTP mode selection |  | HS LS LS | CB1 B HB1 BMB1RG |  |  |
| 470n CFG0 CFG1 CFG2 CFG3 CFG4 CFG5 CFG6 DIAG1 DIAG0 k z CLK_IN VIO VCCIO |  |  |  |  |  |  |  |
|  |  |  |  | HS HS LS LS |  |  |  |
|  |  |  |  |  | LA1 |  |  |
|  |  |  |  |  | RG LA2 |  | RG |
|  |  |  |  |  | SRAH 47R SRAL |  |  |
|  |  |  | pd SPI_MODE DRV_ENN |  |  |  |  |
