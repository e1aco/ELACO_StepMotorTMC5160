# TMC5160A_Datasheet_Rev1.14 — 第0章 

--- [PAGE 1] ---
 
 
POWER DRIVER FOR STEPPER MOTORS 
 
  INTEGRATED CIRCUITS 
 
TRINAMIC Motion Control GmbH & Co. KG 
 
Hamburg, Germany 
TMC5160 / TMC5160A DATASHEET 
 
 
 
 
 
 
  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
   
 
 
 
 
    
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
FEATURES AND BENEFITS 
2-phase stepper motors up to 20A coil current (external MOSFETs) 
Motion Controller with SixPoint™ ramp  
Step/Dir Interface with microstep interpolation MicroPlyer™ 
Voltage Range 8 … 60V DC  
SPI & Single Wire UART  
Encoder Interface and 2x Ref.-Switch Input 
Highest Resolution 256 microsteps per full step 
StealthChop2™ for quiet operation and smooth motion  
Resonance Dampening for mid-range resonances 
spreadCycle™ highly dynamic motor control chopper 
dcStep™ load dependent speed control 
StallGuard2™ high precision sensorless motor load detection 
CoolStep™ current control for energy savings up to 75% 
Passive Braking and freewheeling mode  
Full Protection & Diagnostics 
Compact Size 7x7mm2 (body) TQFP48 package / 8x8mm² QFN  
 
APPLICATIONS 
Robotics & Industrial Drives 
Textile, Sewing Machines 
Packing Machines 
Factory & Lab Automation 
High-speed 3D Printers 
Liquid Handling 
Medical 
Office Automation 
CCTV 
ATM, Cash Recycler 
Pumps and Valves 
DESCRIPTION 
The TMC5160 / TMC5160A is a high-power 
stepper motor controller and driver IC 
with serial communication interfaces. It 
combines a flexible ramp generator for 
automatic target positioning with indus-
tries’ most advanced stepper motor 
driver. Using external transistors, highly 
dynamic, high torque drives can be 
realized. Based on TRINAMICs sophisti-
cated 
SpreadCycle 
and 
StealthChop 
choppers, the driver ensures absolutely 
noiseless operation combined with maxi-
mum efficiency and best motor torque. 
High integration, high energy efficiency 
and a small form factor enable miniatu-
rized and scalable systems for cost 
effective solutions. The complete solution 
reduces learning curve to a minimum 
while giving best performance in class. 
Universal high voltage controller/driver for two-phase bipolar stepper motor. StealthChop™ for quiet 
movement. External MOSFETs for up to 20A motor current per coil. With Step/Dir Interface and SPI.  
BLOCK DIAGRAM 

--- [PAGE 2] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
2 
 
 
 
www.trinamic.com 
APPLICATION EXAMPLES: HIGH VOLTAGE – MULTIPURPOSE USE 
The TMC5160 scores with complete motion controlling features, powerful external MOSFET driver stages, 
and high-quality current regulation. It offers a versatility that covers a wide spectrum of applications from 
battery powered, high efficiency systems up to embedded applications with 20A motor current per coil. The 
TMC5160 contains the complete intelligence which is required to drive a motor. Receiving target positions, 
the TMC5160 manages motor movement. Based on TRINAMICs unique features StallGuard2, CoolStep, 
DcStep, SpreadCycle, and StealthChop, it optimizes drive performance. It trades off velocity vs. motor 
torque, optimizes energy efficiency, smoothness of the drive, and noiselessness. The small form factor of 
the TMC5160 keeps costs down and allows for miniaturized layouts. Extensive support at the chip, board, 
and software levels enables rapid design cycles and fast time-to-market with competitive products. High 
energy efficiency and reliability deliver cost savings in related systems such as power supplies and cooling. 
For smaller designs, the compatible, integrated TMC5130 driver provides 1.4A of motor current. 
 
CPU
TMC5160
High-Level 
Interface
SPI
CPU
High-Level 
Interface
TMC5160
TMC5160
More TMC5160 or TMC5130 or TMC5072
SPI or 
UART 
MINIATURIZED DESIGN FOR ONE STEPPER MOTOR
COMPACT DESIGN FOR MULTIPLE STEPPER MOTORS 
M
Encoder
Ref.
Switches
M
M
Addr.
Addr.
NCS signal for SPI
Chaining 
with UART
 
 
ORDER CODES 
Order code 
PN 
Description 
Size [mm2] 
TMC5160A-TA 
00-0179 stepper controller/driver for external MOSFETs; TQFP48  
7 x 7 (body) 
TMC5160A-WA 
00-0192 stepper controller/driver f. ext. MOSFETs; wett. QFN8x8 
8 x 8  
TMC5160A-xx-T 
…-T 
-T denotes tape on reel packing (xx= TA or WA) 
 
TMC5160-EVAL 
40-0138 Evaluation board for TMC5160 (/A) 
85 x 55 
LANDUNGSBRÜCKE 40-0167 Baseboard for TMC5160-EVAL and further boards.  
85 x 55 
ESELSBRÜCKE 
40-0098 Connector board fitting to Landungsbrücke 
61 x 38 
 
Hint: TMC5160 in this manual always refers to both, the TMC5160A and TMC5160, unless explicitly noted 
with “non-A-version” or “A-version”. The A-version compatibly replaces the non-A-version. 
An ABN encoder interface with scaler unit 
and two reference switch inputs are used to 
ensure correct motor movement.  Automatic 
interrupt upon deviation is available. 
An application with 2 stepper motors is 
shown. Additionally, the ABN Encoder 
interface and two reference switches can be 
used for each motor. A single CPU controls 
the whole system, as there are no real time 
tasks required to move a motor. The CPU-
board and the controller / driver boards are 
highly economical and space saving.   
 
The TMC5160-EVAL is part of TRINAMICs 
universal evaluation board system which 
provides a convenient handling of the 
hardware as well as a user-friendly 
software 
tool 
for 
evaluation. 
The 
TMC5160 
evaluation 
board 
system 
consists 
of 
three 
parts: 
LANDUNGSBRÜCKE 
(base 
board), 
ESELSBRÜCKE (connector board including 
several test points), and TMC5160-EVAL.  


<!-- detected tables -->

|  |  |
|---|---|
| TMC5160 |  |

| SPI or CPU UART NCS signal for SPI | CPU |  | SPI or UART |  | TMC5160 Addr. Chaining |  | M M |
|---|---|---|---|---|---|---|---|
|  |  |  |  |  |  |  |  |
|  |  |  |  |  | with UART TMC5160 Addr. |  |  |
|  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |

|  |  |
|---|---|
| TMC5160 Addr. |  |

| Order code |  |  | PN |  | Description |  |  | Size [mm2] |  |
|---|---|---|---|---|---|---|---|---|---|
| TMC5160A-TA |  | 00-0179 |  | stepper controller/driver for external MOSFETs; TQFP48 |  |  | 7 x 7 (body) |  |  |
| TMC5160A-WA |  | 00-0192 |  | stepper controller/driver f. ext. MOSFETs; wett. QFN8x8 |  |  | 8 x 8 |  |  |
| TMC5160A-xx-T |  | …-T |  | -T denotes tape on reel packing (xx= TA or WA) |  |  |  |  |  |
| TMC5160-EVAL |  | 40-0138 |  | Evaluation board for TMC5160 (/A) |  |  | 85 x 55 |  |  |
| LANDUNGSBRÜCKE |  | 40-0167 |  | Baseboard for TMC5160-EVAL and further boards. |  |  | 85 x 55 |  |  |
| ESELSBRÜCKE |  | 40-0098 |  | Connector board fitting to Landungsbrücke |  |  | 61 x 38 |  |  |
--- [PAGE 3] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
3 
 
 
 
www.trinamic.com 
Table of Contents 
 
1 
PRINCIPLES OF OPERATION ......................... 5 
1.1 
KEY CONCEPTS ................................................ 6 
1.2 
CONTROL INTERFACES ..................................... 7 
1.3 
SOFTWARE ...................................................... 7 
1.4 
MOVING AND CONTROLLING THE MOTOR ........ 8 
1.5 
AUTOMATIC STANDSTILL POWER DOWN......... 8 
1.6 
STEALTHCHOP2 & SPREADCYCLE DRIVER ....... 8 
1.7 
STALLGUARD2 – MECHANICAL LOAD SENSING . 
 
 ....................................................................... 9 
1.8 
COOLSTEP – LOAD ADAPTIVE CURRENT 
CONTROL ...................................................................... 9 
1.9 
DCSTEP – LOAD DEPENDENT SPEED CONTROL . 
 
 ..................................................................... 10 
1.10 
ENCODER INTERFACE ..................................... 10 
2 
PIN ASSIGNMENTS ......................................... 11 
2.1 
PACKAGE OUTLINE ........................................ 11 
2.2 
SIGNAL DESCRIPTIONS ................................. 12 
3 
SAMPLE CIRCUITS .......................................... 15 
3.1 
STANDARD APPLICATION CIRCUIT ................ 15 
3.2 
EXTERNAL GATE VOLTAGE REGULATOR .......... 16 
3.3 
CHOOSING MOSFETS AND SLOPE ................ 17 
3.4 
TUNING THE MOSFET BRIDGE ..................... 19 
3.5 
HIGHER VOLTAGE APPLICATIONS .................. 22 
4 
SPI INTERFACE ................................................ 23 
4.1 
SPI DATAGRAM STRUCTURE ......................... 23 
4.2 
SPI SIGNALS ................................................ 24 
4.3 
TIMING ......................................................... 25 
5 
UART SINGLE WIRE INTERFACE ................ 26 
5.1 
DATAGRAM STRUCTURE ................................. 26 
5.2 
CRC CALCULATION ....................................... 28 
5.3 
UART SIGNALS ............................................ 28 
5.4 
ADDRESSING MULTIPLE SLAVES .................... 29 
6 
REGISTER MAPPING ....................................... 31 
6.1 
GENERAL CONFIGURATION REGISTERS .......... 32 
6.2 
VELOCITY DEPENDENT DRIVER FEATURE 
CONTROL REGISTER SET ............................................. 38 
6.3 
RAMP GENERATOR REGISTERS ....................... 40 
6.4 
ENCODER REGISTERS ..................................... 45 
6.5 
MOTOR DRIVER REGISTERS ........................... 47 
7 
STEALTHCHOP™ .............................................. 57 
7.1 
AUTOMATIC TUNING ..................................... 57 
7.2 
STEALTHCHOP OPTIONS ................................ 60 
7.3 
STEALTHCHOP CURRENT REGULATOR ............. 60 
7.4 
VELOCITY BASED SCALING ............................ 63 
7.5 
COMBINING STEALTHCHOP AND SPREADCYCLE . 
 
 ..................................................................... 64 
7.6 
FLAGS IN STEALTHCHOP ............................... 66 
7.7 
FREEWHEELING AND PASSIVE BRAKING ........ 66 
8 
SPREADCYCLE AND CLASSIC CHOPPER ... 68 
8.1 
SPREADCYCLE CHOPPER ................................ 69 
8.2 
CLASSIC CONSTANT OFF TIME CHOPPER ...... 72 
9 
SELECTING SENSE RESISTORS .................... 74 
10 
VELOCITY BASED MODE CONTROL ....... 76 
11 
DIAGNOSTICS AND PROTECTION......... 78 
11.1 
TEMPERATURE SENSORS ................................ 78 
11.2 
SHORT PROTECTION ...................................... 78 
11.3 
OPEN LOAD DIAGNOSTICS ........................... 80 
12 
RAMP GENERATOR ..................................... 81 
12.1 
REAL WORLD UNIT CONVERSION ................. 81 
12.2 
MOTION PROFILES ........................................ 82 
12.3 
VELOCITY THRESHOLDS ................................. 84 
12.4 
REFERENCE SWITCHES .................................. 85 
13 
STALLGUARD2 LOAD MEASUREMENT ... 87 
13.1 
TUNING STALLGUARD2 THRESHOLD SGT ..... 88 
13.2 
STALLGUARD2 UPDATE RATE AND FILTER .... 90 
13.3 
DETECTING A MOTOR STALL ......................... 90 
13.4 
HOMING WITH STALLGUARD ........................ 90 
13.5 
LIMITS OF STALLGUARD2 OPERATION .......... 90 
14 
COOLSTEP OPERATION ............................. 91 
14.1 
USER BENEFITS ............................................. 91 
14.2 
SETTING UP FOR COOLSTEP .......................... 91 
14.3 
TUNING COOLSTEP ....................................... 93 
15 
STEP/DIR INTERFACE ................................ 94 
15.1 
TIMING ......................................................... 94 
15.2 
CHANGING RESOLUTION ............................... 95 
15.3 
MICROPLYER AND STAND STILL DETECTION . 96 
16 
DIAG OUTPUTS ........................................... 97 
16.1 
STEP/DIR MODE ......................................... 97 
16.2 
MOTION CONTROLLER MODE ........................ 97 
17 
DCSTEP .......................................................... 99 
17.1 
USER BENEFITS ............................................. 99 
17.2 
DESIGNING-IN DCSTEP ................................ 99 
17.3 
DCSTEP INTEGRATION WITH THE MOTION 
CONTROLLER ............................................................ 100 
17.4 
STALL DETECTION IN DCSTEP MODE .......... 100 
17.5 
MEASURING ACTUAL MOTOR VELOCITY IN 
DCSTEP OPERATION ................................................ 101 
17.6 
DCSTEP WITH STEP/DIR INTERFACE ......... 102 
18 
SINE-WAVE LOOK-UP TABLE................. 105 
18.1 
USER BENEFITS ........................................... 105 
18.2 
MICROSTEP TABLE ...................................... 105 
19 
EMERGENCY STOP .................................... 106 

--- [PAGE 4] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
4 
 
 
 
www.trinamic.com 
20 
ABN INCREMENTAL ENCODER 
INTERFACE .............................................................. 107 
20.1 
ENCODER TIMING ....................................... 108 
20.2 
SETTING THE ENCODER TO MATCH MOTOR 
RESOLUTION ............................................................ 108 
20.3 
CLOSING THE LOOP .................................... 109 
21 
DC MOTOR OR SOLENOID .................... 110 
21.1 
SOLENOID OPERATION ............................... 110 
22 
QUICK CONFIGURATION GUIDE ......... 111 
23 
GETTING STARTED .................................. 116 
23.1 
INITIALIZATION EXAMPLES ......................... 116 
24 
STANDALONE OPERATION .................... 117 
25 
EXTERNAL RESET ...................................... 119 
26 
CLOCK OSCILLATOR AND INPUT ........ 119 
26.1 
USING THE INTERNAL CLOCK...................... 119 
26.2 
USING AN EXTERNAL CLOCK ....................... 119 
27 
ABSOLUTE MAXIMUM RATINGS .......... 120 
28 
ELECTRICAL CHARACTERISTICS .......... 120 
28.1 
OPERATIONAL RANGE ................................ 120 
28.2 
DC AND TIMING CHARACTERISTICS ........... 121 
28.3 
THERMAL CHARACTERISTICS........................ 123 
29 
LAYOUT CONSIDERATIONS................... 125 
29.1 
EXPOSED DIE PAD ...................................... 125 
29.2 
WIRING GND ............................................ 125 
29.3 
WIRING BRIDGE SUPPLY ............................ 125 
29.4 
SUPPLY FILTERING ...................................... 125 
29.5 
LAYOUT EXAMPLE ....................................... 126 
30 
PACKAGE MECHANICAL DATA .............. 128 
30.1 
DIMENSIONAL DRAWINGS TQFP48-EP ..... 128 
30.2 
DIMENSIONAL DRAWINGS QFN-WA ......... 130 
30.3 
PACKAGE CODES ......................................... 131 
31 
DESIGN PHILOSOPHY ............................. 132 
32 
DISCLAIMER ............................................... 132 
33 
ESD SENSITIVE DEVICE.......................... 132 
34 
DESIGNED FOR SUSTAINABILITY ....... 132 
35 
TABLE OF FIGURES .................................. 133 
36 
REVISION HISTORY ................................. 134 
37 
REFERENCES ............................................... 134 

