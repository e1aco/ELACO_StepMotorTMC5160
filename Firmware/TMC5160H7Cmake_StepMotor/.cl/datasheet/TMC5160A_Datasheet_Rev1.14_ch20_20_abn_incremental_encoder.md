# TMC5160A_Datasheet_Rev1.14 — 第20章 20 ABN INCREMENTAL ENCODER

--- [PAGE 4] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  4 
 
 
 
www.trinamic.com 
20 ABN INCREMENTAL ENCODER 
INTERFACE .............................................................. 107 
20.1 ENCODER TIMING ....................................... 108 
20.2 SETTING THE ENCODER TO MATCH MOTOR 
RESOLUTION ............................................................ 108 
20.3 CLOSING THE LOOP .................................... 109 
21 DC MOTOR OR SOLENOID .................... 110 
21.1 SOLENOID OPERATION ............................... 110 
22 QUICK CONFIGURATION GUIDE ......... 111 
23 GETTING STARTED .................................. 116 
23.1 INITIALIZATION EXAMPLES ......................... 116 
24 STANDALONE OPERATION .................... 117 
25 EXTERNAL RESET ...................................... 119 
26 CLOCK OSCILLATOR AND INPUT ........ 119 
26.1 USING THE INTERNAL CLOCK...................... 119 
26.2 USING AN EXTERNAL CLOCK ....................... 119 
27 ABSOLUTE MAXIMUM RATINGS .......... 120 
28 ELECTRICAL CHARACTERISTICS .......... 120 
28.1 OPERATIONAL RANGE ................................ 120 
28.2 DC AND TIMING CHARACTERISTICS ........... 121 
28.3 THERMAL CHARACTERISTICS........................ 123 
29 LAYOUT CONSIDERATIONS................... 125 
29.1 EXPOSED DIE PAD ...................................... 125 
29.2 WIRING GND ............................................ 125 
29.3 WIRING BRIDGE SUPPLY ............................ 125 
29.4 SUPPLY FILTERING ...................................... 125 
29.5 LAYOUT EXAMPLE ....................................... 126 
30 PACKAGE MECHANICAL DATA .............. 128 
30.1 DIMENSIONAL DRAWINGS TQFP48-EP ..... 128 
30.2 DIMENSIONAL DRAWINGS QFN-WA ......... 130 
30.3 PACKAGE CODES ......................................... 131 
31 DESIGN PHILOSOPHY ............................. 132 
32 DISCLAIMER ............................................... 132 
33 ESD SENSITIVE DEVICE.......................... 132 
34 DESIGNED FOR SUSTAINABILITY ....... 132 
35 TABLE OF FIGURES .................................. 133 
36 REVISION HISTORY ................................. 134 
37 REFERENCES ............................................... 134 
--- [PAGE 107] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  107 
 
 
 
www.trinamic.com 
20 ABN Incremental Encoder Interface 
The TMC5160 is equipped with an incremental encoder interface for ABN encoders. The encoder inputs 
are multiplexed with other signals in order to keep the pin  count of the device low. The basic 
selection of the peripheral configuration is set by the register GCONF. The use of the N channel is 
optional, as some applications might use a reference switch or stall detection rather than an encoder 
N channel for posi tion r eferencing. The encoders give positions via digital incremental quadrature 
signals (usually named A and B) and a clear signal (usually named N for null or Z for zero).  
 
N SIGNAL 
The N signal can be used to clear the position counter or to take a sna pshot. To continuously monitor 
the N channel and trigger clearing of the encoder position or latching of the position, where the N 
channel event has been detected, set the flag clr_cont. Alternatively it is possible to react to the next 
encoder N channel e vent o nly, and automatically disable the clearing or latching of the encoder 
position after the first N signal event (flag clr_once). This might be desired because the encoder gives 
this signal once for each revolution.  
 
Some encoders require a validation of the N signal by a certain configuration of A and B polarity. This 
can be controlled by pol_A and pol_B flags in the ENCMODE register. For example, when both pol_A 
and pol_B are set, an active N-event is only accepted during a high polarity of both, A and B channel. 
 
For clearing the encoder position ENC_POS with the next active N event set  clr_enc_x = 1 and 
clr_once = 1 or clr_cont = 1. 
 
A
B
t
Position -4 -3 -2 -1 0 5 64321 7
N
 
Figure 20.1 Outline of ABN signals of an incremental encoder 
 
THE ENCODER CONSTANT ENC_CONST  
The encoder constant ENC_CONST is added to or subtracted from the encoder counter on each polarity 
change of the quadrature signals AB of the incremental encoder. The encoder constant ENC_CONST 
represents a signed fixed point number (16.16) to facilitate the generic adaption between mo tors and 
encoders. In decimal mode, the lower 16 bits represent a number between 0 and 9999. For stepper 
motors equipped with incremental encoders the fixed number represen tation allows very comfortable 
parameterization. Additionally, mechanical gearing ca n easily be taken into account. Negating the sign 
of ENC_CONST allows inversion of the counting direction to match motor and encoder direction. 
 
Examples:  
- Encoder factor of 1.0: ENC_CONST = 0x0001.0x0000 = FACTOR.FRACTION 
- Encoder factor of -1.0: ENC_CONST = 0xFFFF.0x0000. This is the two’s complement of 0x00010000. 
It equals (2^16-(FACTOR+1)).(2^16-FRACTION) 
- Decimal mode encoder factor 25.6: 00025.6000 = 0x0019.0x1770 = FACTOR.DECIMALS 
--- [PAGE 108] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  108 
 
 
 
www.trinamic.com 
- Decimal mode encoder factor -25.6: 0xFFE6.4000 = 0xFFE6.0x0FAO. This equals (2^16-
(FACTOR+1)).(10000-DECIMALS) 
 
THE ENCODER COUNTER X_ENC 
The encoder counter X_ENC holds the current encoder position ready for read out. Different modes 
concerning handling of the signals A, B, and N take into account active low and active high signals 
found with different types of encoders. For more details please refer to the registe r mapping in 
section 6.4. 
 
THE REGISTER ENC_STATUS 
The register ENC_STATUS holds the status concerning the event of an encoder clear upon an N 
channel signals. The register ENC_LATCH stores the actual encoder position on an N signal event. 
20.1 Encoder Timing 
The encoder inputs use analog and digital filtering to ensure reliable operation even with increased 
cable length. The maximum continuous counting rate is limited by input filtering to 2/3 of fCLK. 
 
Encoder interface timing  AC-Characteristics 
clock period is tCLK 
Parameter Symbol Conditions Min Typ Max Unit 
Encoder counting frequency fCNT   <2/3 fCLK fCLK  
A/B/N input low time tABNL  3 tCLK+20   ns 
A/B/N input high time tABNH  3 tCLK+20   ns 
A/B/N spike filtering time tFILTABN Rising and falling 
edge 
 3 tCLK   
20.2 Setting the Encoder to Match Motor Resolution 
Encoder example settings for motor parameters: USC=256 µsteps, 200 fullstep motor 
Factor = FSC*USC / encoder resolution 
 
ENCODER EXAMPLE SETTINGS FOR A 200 FULLSTEP MOTOR WITH 256 MICROSTEPS 
Encoder resolution Required encoder factor Comment 
200 256  
360 142.2222  
= 9320675.5555 / 2^16  
= 1422222.2222 / 10000 
No exact match possible! 
500 102.4 
= 6710886.4 / 2^16 
= 1024000 / 10000 
 
Exact match with decimal setting 
1000 51.2 Exact match with decimal setting 
1024 50  
4000 12.8 Exact match with decimal setting 
4096 12.5  
16384 3.125  
 
Example: 
The encoder constant register shall be programmed to 51.2 in decimal mode. Therefore, set 
𝐸𝑁𝐶_𝐶𝑂𝑁𝑆𝑇 = 51 ∗ 216 + 0.2 ∗ 10000  
--- [PAGE 109] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  109 
 
 
 
www.trinamic.com 
20.3 Closing the Loop 
Depending on the application, an encoder can be used for different purpose s. Medical applications 
often require an additional and independent monitoring  to detect hard or soft failure. Upon failure, 
the machine can be stopped and restarted manually . Use ENC_DEVIATION setting and interrupt to 
safely detect a step loss failure / mismatch between motor and encoder.  
 
Less critical applications may use the encoder to detect failure, stop the motors upon st ep loss and 
restart automatically. A different use of the encoder allows increased positioning precision by 
positioning directly to encoder positions. The application can modify target positions based on th e 
deviation, or even regularly update the actual position with the encoder position.  
 
To realize a directly encoder based commutation, TRINAMIC offers the new S-ramp closed loop motion 
controller TMC4361.  
