# TMC5160A_Datasheet_Rev1.14 — 第1章 · p5

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
5 
 
 
 
www.trinamic.com 
1 Principles of Operation 
The TMC5160 motion controller and driver chip is an intelligent power component interfacing between 
CPU and a high power stepper motor. All stepper motor logic is completely within the TMC5160. No 
software is required to control the motor – just provide target positions. The TMC5160 offers a 
number of unique enhancements which are enabled by the system-on-chip integration of driver and 
controller. The SixPoint ramp generator of the TMC5160 uses StealthChop, DcStep, CoolStep, and 
StallGuard2 automatically to optimize every motor movement. The TMC5160 ideally extends the 
TMC2100, TMC2130 and TMC5130 family to higher voltages and higher motor currents.  
 
THE TMC5160 OFFERS THREE BASIC MODES OF OPERATION: 
MODE 1: Full Featured Motion Controller & Driver 
All stepper motor logic is completely within the TMC5160. No software is required to control the 
motor – just provide target positions. Enable this mode by tying low pin SD_MODE. 
 
MODE 2: Step & Direction Driver 
An external high-performance S-ramp motion controller like the TMC4361 or a central CPU generates 
step & direction signals synchronized to other components like additional motors within the system. 
The TMC5160 takes care of intelligent current and mode control and delivers feedback on the state of 
the motor. The MicroPlyer automatically smoothens motion. Tie SD_MODE high. 
 
MODE 3: Simple Step & Direction Driver 
The TMC5160 positions the motor based on step & direction signals. The MicroPlyer automatically 
smoothens motion. No CPU interaction is required; configuration is done by hardware pins. Basic 
standby current control can be done by the TMC5160. Optional feedback signals allow error detection 
and synchronization. Enable this mode by tying pin SPI_MODE low and SD_MODE high. 
 
 
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
Ref. switch 
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
Encoder 
unit
A
B
N
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
linear 6 point 
RAMP generator
Step & 
Direction pulse 
generation
Control register 
set
Interface
dcStep™
coolStep & 
stealthChop 
motor driver
B.Dwersteg, © 
TRINAMIC 2014
Motion control
 
Figure 1.1 TMC5160 basic application block diagram (motion controller) 


<!-- detected tables -->

| REFL/STEP REFR/DIR VM 12 02 0n V 1 10 60 Vn 100n CPO CPI VCP VS VSA CB2 12VOUT 11.5V Voltage Ref. switch TMC5160 charge pump HS HB2 CCB |  |  |  |  |  |  |
|---|---|---|---|---|---|---|
|  |  |  | 100n CB2 HS HB2 CB C |  |  |  |
|  | 2.2µ 5VOUT 2.2µ 2R2 VCC | regulator processing 5V Voltage regulator HS Step & linear 6 point Direction pulse RAMP generator generation LS M o tio n c o n tr o l m o to r d r ivs ete a lth C h oc po o lS te p & r LS SPI interface spreadCycle & Contro sl er tegister pr 4o s *g i 2nr 5ea m t eam nb ta le rb yle x Ss tet Ce pa h pl o eth p C p dh e ro r ivp I n te r fa c e DIAG / INT out 6 r e r Si in ng ta eln e rf d aw ci ere TB R.D INw Ae Mrs It Ce g 2, 0 1© 4 T&B R .PID dNrw ioAaetMgers IncCtet o ig 2so, 0t n© i1c4 s HS coolStep™ HS stallGuard2™ dcStep™ LS LS Encoder unit mode selection A B N | HS LS LS | CB1 B HB1 BMB1RG |  |  |
| 470n CSN SCK SDI SDO DIAG1/SWP |  |  |  | BMB2 LB1 |  |  |
| DIAG0/SWN k z CLK_IN IO VCCIO |  |  |  | HA2 CA1 HA1 CB BMA1RG BMA2 LA1 RG |  |  |
