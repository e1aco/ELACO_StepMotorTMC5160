# TMC5160A_Datasheet_Rev1.14 — 第17章 · p3

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  3 
 
 
 
www.trinamic.com 
Table of Contents 
 
1 PRINCIPLES OF OPERATION ......................... 5 
1.1 KEY CONCEPTS ................................................ 6 
1.2 CONTROL INTERFACES ..................................... 7 
1.3 SOFTWARE ...................................................... 7 
1.4 MOVING AND CONTROLLING THE MOTOR ........ 8 
1.5 AUTOMATIC STANDSTILL POWER DOWN......... 8 
1.6 STEALTHCHOP2 & SPREADCYCLE DRIVER ....... 8 
1.7 STALLGUARD2 – MECHANICAL LOAD SENSING . 
  ....................................................................... 9 
1.8 COOLSTEP – LOAD ADAPTIVE CURRENT 
CONTROL ...................................................................... 9 
1.9 DCSTEP – LOAD DEPENDENT SPEED CONTROL . 
  ..................................................................... 10 
1.10 ENCODER INTERFACE ..................................... 10 
2 PIN ASSIGNMENTS ......................................... 11 
2.1 PACKAGE OUTLINE ........................................ 11 
2.2 SIGNAL DESCRIPTIONS ................................. 12 
3 SAMPLE CIRCUITS .......................................... 15 
3.1 STANDARD APPLICATION CIRCUIT ................ 15 
3.2 EXTERNAL GATE VOLTAGE REGULATOR .......... 16 
3.3 CHOOSING MOSFETS AND SLOPE ................ 17 
3.4 TUNING THE MOSFET BRIDGE ..................... 19 
3.5 HIGHER VOLTAGE APPLICATIONS .................. 22 
4 SPI INTERFACE ................................................ 23 
4.1 SPI DATAGRAM STRUCTURE ......................... 23 
4.2 SPI SIGNALS ................................................ 24 
4.3 TIMING ......................................................... 25 
5 UART SINGLE WIRE INTERFACE ................ 26 
5.1 DATAGRAM STRUCTURE ................................. 26 
5.2 CRC CALCULATION ....................................... 28 
5.3 UART SIGNALS ............................................ 28 
5.4 ADDRESSING MULTIPLE SLAVES .................... 29 
6 REGISTER MAPPING ....................................... 31 
6.1 GENERAL CONFIGURATION REGISTERS .......... 32 
6.2 VELOCITY DEPENDENT DRIVER FEATURE 
CONTROL REGISTER SET ............................................. 38 
6.3 RAMP GENERATOR REGISTERS ....................... 40 
6.4 ENCODER REGISTERS ..................................... 45 
6.5 MOTOR DRIVER REGISTERS ........................... 47 
7 STEALTHCHOP™ .............................................. 57 
7.1 AUTOMATIC TUNING ..................................... 57 
7.2 STEALTHCHOP OPTIONS ................................ 60 
7.3 STEALTHCHOP CURRENT REGULATOR ............. 60 
7.4 VELOCITY BASED SCALING ............................ 63 
7.5 COMBINING STEALTHCHOP AND SPREADCYCLE . 
  ..................................................................... 64 
7.6 FLAGS IN STEALTHCHOP ............................... 66 
7.7 FREEWHEELING AND PASSIVE BRAKING ........ 66 
8 SPREADCYCLE AND CLASSIC CHOPPER ... 68 
8.1 SPREADCYCLE CHOPPER ................................ 69 
8.2 CLASSIC CONSTANT OFF TIME CHOPPER ...... 72 
9 SELECTING SENSE RESISTORS .................... 74 
10 VELOCITY BASED MODE CONTROL ....... 76 
11 DIAGNOSTICS AND PROTECTION......... 78 
11.1 TEMPERATURE SENSORS ................................ 78 
11.2 SHORT PROTECTION ...................................... 78 
11.3 OPEN LOAD DIAGNOSTICS ........................... 80 
12 RAMP GENERATOR ..................................... 81 
12.1 REAL WORLD UNIT CONVERSION ................. 81 
12.2 MOTION PROFILES ........................................ 82 
12.3 VELOCITY THRESHOLDS ................................. 84 
12.4 REFERENCE SWITCHES .................................. 85 
13 STALLGUARD2 LOAD MEASUREMENT ... 87 
13.1 TUNING STALLGUARD2 THRESHOLD SGT ..... 88 
13.2 STALLGUARD2 UPDATE RATE AND FILTER .... 90 
13.3 DETECTING A MOTOR STALL ......................... 90 
13.4 HOMING WITH STALLGUARD ........................ 90 
13.5 LIMITS OF STALLGUARD2 OPERATION .......... 90 
14 COOLSTEP OPERATION ............................. 91 
14.1 USER BENEFITS ............................................. 91 
14.2 SETTING UP FOR COOLSTEP .......................... 91 
14.3 TUNING COOLSTEP ....................................... 93 
15 STEP/DIR INTERFACE ................................ 94 
15.1 TIMING ......................................................... 94 
15.2 CHANGING RESOLUTION ............................... 95 
15.3 MICROPLYER AND STAND STILL DETECTION . 96 
16 DIAG OUTPUTS ........................................... 97 
16.1 STEP/DIR MODE ......................................... 97 
16.2 MOTION CONTROLLER MODE ........................ 97 
17 DCSTEP .......................................................... 99 
17.1 USER BENEFITS ............................................. 99 
17.2 DESIGNING-IN DCSTEP ................................ 99 
17.3 DCSTEP INTEGRATION WITH THE MOTION 
CONTROLLER ............................................................ 100 
17.4 STALL DETECTION IN DCSTEP MODE .......... 100 
17.5 MEASURING ACTUAL MOTOR VELOCITY IN 
DCSTEP OPERATION ................................................ 101 
17.6 DCSTEP WITH STEP/DIR INTERFACE ......... 102 
18 SINE-WAVE LOOK-UP TABLE................. 105 
18.1 USER BENEFITS ........................................... 105 
18.2 MICROSTEP TABLE ...................................... 105 
19 EMERGENCY STOP .................................... 106 
