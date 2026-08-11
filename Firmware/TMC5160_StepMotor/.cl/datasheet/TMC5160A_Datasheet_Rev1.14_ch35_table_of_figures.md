# TMC5160A_Datasheet_Rev1.14 — 第35章 TABLE OF FIGURES

--- [PAGE 133] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
133 
 
 
 
www.trinamic.com 
35 Table of Figures 
FIGURE 1.1 TMC5160 BASIC APPLICATION BLOCK DIAGRAM (MOTION CONTROLLER) ................................................................. 5 
FIGURE 1.2 TMC5160 STEP/DIR APPLICATION DIAGRAM ......................................................................................................... 6 
FIGURE 1.3 TMC5160 STANDALONE DRIVER APPLICATION DIAGRAM ......................................................................................... 6 
FIGURE 1.4 AUTOMATIC MOTOR CURRENT POWER DOWN .......................................................................................................... 8 
FIGURE 1.5 ENERGY EFFICIENCY WITH COOLSTEP (EXAMPLE) ...................................................................................................... 9 
FIGURE 2.1 TMC5160-TA PACKAGE AND PINNING TQFP-EP 48 (7X7MM² BODY, 9X9MM² WITH LEADS) ............................... 11 
FIGURE 2.2 TMC5160-WA PACKAGE AND PINNING QFN-WA (8X8MM²) ............................................................................... 11 
FIGURE 3.1 STANDARD APPLICATION CIRCUIT ........................................................................................................................... 15 
FIGURE 3.2 EXTERNAL GATE VOLTAGE SUPPLY ........................................................................................................................... 16 
FIGURE 3.3 MILLER CHARGE DETERMINES SWITCHING SLOPE .................................................................................................... 17 
FIGURE 3.4 SLOPES, MILLER PLATEAU AND BLANK TIME ........................................................................................................... 18 
FIGURE 3.5 BRIDGE PROTECTION OPTIONS FOR POWER ROUTING INDUCTIVITY ......................................................................... 19 
FIGURE 3.6 RINGING OF OUTPUT (BLUE) AND GATE VOLTAGES (YELLOW, CYAN) WITH UNTUNED BRIGE ................................... 20 
FIGURE 3.7 SWITCHING EVENT WITH OPTIMIZED COMPONENTS (WITHOUT / AFTER BULK DIODE CONDUCTION) ........................ 20 
FIGURE 3.8 EXAMPLE FOR BRIDGE WITH TUNED COMPONENTS (SEE SCOPE SHOTS) ................................................................... 21 
FIGURE 3.9 EXTERNAL GATE DRIVER EXAMPLE .......................................................................................................................... 22 
FIGURE 4.1 SPI TIMING ............................................................................................................................................................ 25 
FIGURE 5.1 ADDRESSING MULTIPLE TMC5160 VIA SINGLE WIRE INTERFACE USING CHAINING ................................................ 29 
FIGURE 5.2 ADDRESSING MULTIPLE TMC5160 VIA THE DIFFERENTIAL INTERFACE, ADDITIONAL FILTERING FOR NAI .............. 30 
FIGURE 7.1 MOTOR COIL SINE WAVE CURRENT WITH STEALTHCHOP (MEASURED WITH CURRENT PROBE) .................................. 57 
FIGURE 7.2 STEALTHCHOP2 AUTOMATIC TUNING PROCEDURE ................................................................................................... 59 
FIGURE 7.3 SCOPE SHOT: GOOD SETTING FOR PWM_REG ....................................................................................................... 61 
FIGURE 7.4 SCOPE SHOT: TOO SMALL SETTING FOR PWM_REG DURING AT#2 ....................................................................... 61 
FIGURE 7.5 SUCCESSFULLY DETERMINED PWM_GRAD(_AUTO) AND PWM_OFS(_AUTO) ................................................... 61 
FIGURE 7.6 VELOCITY BASED PWM SCALING (PWM_AUTOSCALE=0) ......................................................................................... 64 
FIGURE 7.7 TPWMTHRS FOR OPTIONAL SWITCHING TO SPREADCYCLE ................................................................................... 65 
FIGURE 8.1 CHOPPER PHASES ................................................................................................................................................... 68 
FIGURE 8.2 NO LEDGES IN CURRENT WAVE WITH SUFFICIENT HYSTERESIS (MAGENTA: CURRENT A, YELLOW & BLUE: SENSE 
RESISTOR VOLTAGES A AND B) ......................................................................................................................................... 70 
FIGURE 8.3 SPREADCYCLE CHOPPER SCHEME SHOWING COIL CURRENT DURING A CHOPPER CYCLE ............................................ 71 
FIGURE 8.4 CLASSIC CONST. OFF TIME CHOPPER WITH OFFSET SHOWING COIL CURRENT .......................................................... 72 
FIGURE 8.5 ZERO CROSSING WITH CLASSIC CHOPPER AND CORRECTION USING SINE WAVE OFFSET .......................................... 72 
FIGURE 10.1 CHOICE OF VELOCITY DEPENDENT MODES ............................................................................................................. 76 
FIGURE 11.1 SHORT DETECTION ................................................................................................................................................ 79 
FIGURE 12.1 RAMP GENERATOR VELOCITY TRACE SHOWING CONSEQUENT MOVE IN NEGATIVE DIRECTION ................................ 82 
FIGURE 12.2 ILLUSTRATION OF OPTIMIZED MOTOR TORQUE USAGE WITH TMC5160 RAMP GENERATOR ................................... 83 
FIGURE 12.3 RAMP GENERATOR VELOCITY DEPENDENT MOTOR CONTROL ................................................................................... 84 
FIGURE 12.4 USING REFERENCE SWITCHES (EXAMPLE) .............................................................................................................. 85 
FIGURE 13.1 FUNCTION PRINCIPLE OF STALLGUARD2 .............................................................................................................. 87 
FIGURE 13.2 EXAMPLE: OPTIMUM SGT SETTING AND STALLGUARD2 READING WITH AN EXAMPLE MOTOR ............................... 89 
FIGURE 14.1 COOLSTEP ADAPTS MOTOR CURRENT TO THE LOAD ............................................................................................... 92 
FIGURE 15.1 STEP AND DIR TIMING, INPUT PIN FILTER ......................................................................................................... 94 
FIGURE 15.2 MICROPLYER MICROSTEP INTERPOLATION WITH RISING STEP FREQUENCY (EXAMPLE: 16 TO 256) ..................... 96 
FIGURE 16.1 DIAG OUTPUTS IN STEP/DIR MODE .................................................................................................................. 97 
FIGURE 16.2 DIAG OUTPUTS WITH SD_MODE=0 ................................................................................................................... 98 
FIGURE 17.1 DCSTEP EXTENDED APPLICATION OPERATION AREA .............................................................................................. 99 
FIGURE 17.2 VELOCITY PROFILE WITH IMPACT BY OVERLOAD SITUATION ............................................................................... 100 
FIGURE 17.3 MOTOR MOVING SLOWER THAN STEP INPUT DUE TO LIGHT OVERLOAD. LOSTSTEPS INCREMENTED ................ 103 
FIGURE 17.4 FULL SIGNAL INTERCONNECTION FOR DCSTEP .................................................................................................... 103 
FIGURE 17.5 DCO INTERFACE TO MOTION CONTROLLER – STEP GENERATOR STOPS WHEN DCO IS ASSERTED ........................ 104 
FIGURE 18.1 LUT PROGRAMMING EXAMPLE ............................................................................................................................ 105 
FIGURE 20.1 OUTLINE OF ABN SIGNALS OF AN INCREMENTAL ENCODER ................................................................................ 107 
FIGURE 22.1 CURRENT SETTING AND FIRST STEPS WITH STEALTHCHOP .................................................................................. 111 
FIGURE 22.2 TUNING STEALTHCHOP AND SPREADCYCLE ........................................................................................................ 112 

