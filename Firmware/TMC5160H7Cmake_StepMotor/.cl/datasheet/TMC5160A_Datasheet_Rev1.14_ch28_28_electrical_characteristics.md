# TMC5160A_Datasheet_Rev1.14 — 第28章 28 Electrical Characteristics

--- [PAGE 120] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  120 
 
 
 
www.trinamic.com 
27 Absolute Maximum Ratings 
The maximum ratings may not be exceeded under any circumstances. Operating the circuit at or near 
more than one maximum rating at a time for exten ded periods shall be avoided by application 
design. 
 
Parameter Symbol Min Max Unit 
Supply voltage operating with inductive load VVS, VVSA -0.5 60 V 
Supply and bridge voltage short time peak (limited by 
peak voltage on charge pump output and Cxx pins*) VVSMAX  64 V 
VSA when different from VS VVSAMAX -0.5 60 V 
Peak voltages on Cxx bootstrap pins and VCP VCxCP  76 V 
Supply voltage V12 V12VOUT -0.5 14 V 
Peak voltages on BM pins (due to stray inductivity) VBMx -6 VVS+6 V 
Peak voltages on Cxx bootstrap pins relative to BM VCxBMx -0.5 16 V 
I/O supply voltage on VCC_IO VVIO -0.5 5.5 V 
digital VCC supply voltage (normally supplied by 5VOUT) VVCC -0.5 5.5 V 
Logic input voltage VI -0.5 VVIO+0.5 V 
Maximum current to / from digital pins 
and analog low voltage I/Os (short time peak current) 
IIO  +/-500 mA 
5V regulator output current (internal plus external load) I5VOUT  30 mA 
5V regulator continuous power dissipation (VVSA-5V) * I5VOUT P5VOUT  1 W 
12V regulator output current (internal plus external load) I12VOUT  20 mA 
12V regulator cont. power dissipation (VVM-12V) * I12VOUT P12VOUT  0.5 W 
Junction temperature TJ -50 150 °C 
Storage temperature TSTG -55 150 °C 
ESD-Protection for interface pins (Human body model, 
HBM) 
VESDAP  4 kV 
ESD-Protection for handling (Human body model, HBM) VESD  1 kV 
 
*) Stray inductivity of power routing will lead to ringing of the supply voltage when driving an 
inductive load. This ringing results from the fast switching slopes of the driver outputs in 
combination with reverse recovery of the body diodes of the output  driver MOSFETs. Even small trace 
inductivities as well as stray inductivity of sense resistors can easily generate a few volts of ringing  
leading to temporary voltage overshoot . This should be considered when worki ng near the maximum 
voltage.  
 
28 Electrical Characteristics 
28.1 Operational Range 
Parameter Symbol Min Max Unit 
Junction temperature TJ -40 125 °C 
Supply voltage for motor and bridge VVS 10 55 V 
Supply voltage VSA VVSA 10 50 V 
Supply voltage  for VSA and 12OUT (internal gate voltage 
regulator bridged) 
V12VOUT, 
VVSA 
10 13 V 
Lower Supply voltage (reduced spec, short to GND 
protection not functional ), lower limit depending on 
MOSFETs gate threshold voltage and load current 
VVS 
8  V 
I/O supply voltage on VCC_IO VVIO 3.00 5.25 V 
 
  
--- [PAGE 121] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  121 
 
 
 
www.trinamic.com 
28.2 DC and Timing Characteristics 
DC characteristics contain the spread of values guaranteed within the specified supply voltage range 
unless otherwise specified. Typical values represent the average value of all parts measured at +25°C. 
Temperature variation also causes stray to some values. A device with typical values will not leave 
Min/Max range within the full temperature range. 
 
Power supply current DC-Characteristics 
VVS = VVSA = 24.0V 
Parameter Symbol Conditions Min Typ Max Unit 
Total supply current, driver 
disabled IVS + IVSA 
IS fCLK=12MHz / internal 
clock 
 18 24 mA 
VSA supply current (VS and VSA 
separated) 
IVSA fCLK=12MHz / internal 
clock, driver disabled 
 15  mA 
Total supply current, operating, 
MOSFETs AOD4126, IVS + IVSA 
IS fCLK=12MHz, 23.4kHz 
chopper, no load 
 25  mA 
Internal current consumption 
from 5V supply on VCC pin 
IVCC fCLK=12MHz  10  mA 
Internal current consumption 
from 5V supply on VCC pin 
IVCC fCLK=16MHz  12.5  mA 
IO supply current on VCC_IO 
(typ. at 5V) 
IVIO no load on outputs, 
inputs at VIO or GND 
Excludes pullup / 
pull-down resistors 
 15 30 µA 
 
Motor driver section DC- and Timing-Characteristics 
VVS = 24.0V; Tj=50°C 
Parameter Symbol Conditions Min Typ Max Unit 
RDSON lowside off driver RONL Gate off  1.8 3 Ω 
RDSON highside off driver RONH Gate off  2.2 3.5 Ω 
Gate drive current low side 
MOSFET turning on at 2V VGS 
ISLPON0 DRVSTRENGTH=0  200  mA 
ISLPON2 DRVSTRENGTH=2  400  mA 
ISLPON3 DRVSTRENGTH=3  600  mA 
Gate drive current high side 
MOSFET turning on at 2V VGS 
ISLPON0 DRVSTRENGTH=0  150  mA 
ISLPON2 DRVSTRENGTH=2  300  mA 
ISLPON3 DRVSTRENGTH=3  450  mA 
BBM time via internal delay (start 
of gate switching off to start of 
gate switching on) 
tBBM0 BBMCLKS=0 
BBMTIME=0 
75 100  ns 
tBBM16 BBMTIME=16  200  ns 
tBBM16 BBMTIME=24  375 500 ns 
 
Charge pump DC-Characteristics 
Parameter Symbol Conditions Min Typ Max Unit 
Charge pump output voltage VVCP-VVS operating V12VOUT -
2 
V12VOUT -
1 
 V 
Charge pump voltage threshold 
for undervoltage detection 
VVCP-VVS rising, using internal 
5V regulator voltage 
4.5 5 6.5 V 
Charge pump frequency fCP   1/16 
fCLKOSC 
  
 
--- [PAGE 123] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  123 
 
 
 
www.trinamic.com 
Detector levels DC-Characteristics 
Parameter Symbol Conditions Min Typ Max Unit 
VVSA undervoltage threshold for 
RESET 
VUV_VSA VVSA rising 3.6 4 4.6 V 
V5VOUT undervoltage threshold for 
RESET 
VUV_5VOUT V5VOUT rising  3.5  V 
VVCC_IO undervoltage threshold for 
RESET 
VUV_VIO VVCC_IO rising (delay 
typ. 10µs) 
2.0 2.5 3.0 V 
VVCC_IO undervoltage detector 
hysteresis 
VUV_VIOHYST   0.3  V 
Overtemperature prewarning 
120°C 
TOTPW Temperature rising 100 120 140 °C 
Overtemperature shutdown  
136 °C 
TOT136 Temperature rising  136  °C 
Overtemperature shutdown  
143 °C 
TOT143 Temperature rising  143  °C 
Overtemperature shutdown  
150 °C 
TOT150 Temperature rising 135 150 170 °C 
 
Sense resistor voltage levels DC-Characteristics 
fCLK=16MHz 
Parameter Symbol Conditions Min Typ Max Unit 
Sense input peak threshold 
voltage (low sensitivity)  
(VSRxH-VSRxL) 
VSRT GLOBALSCALER=0 
csactual=31 
sin_x=248 
Hyst.=0; IBRxy=0 
 325  mV 
Sense input tolerance / motor 
current full scale tolerance  
-using internal reference 
ICOIL GLOBALSCALER=0 -5  +5 % 
 
Digital pins DC-Characteristics 
Parameter Symbol Conditions Min Typ Max Unit 
Input voltage low level VINLO  -0.3  0.3 VVIO V 
Input voltage high level VINHI  0.7 VVIO  VVIO+0.3 V 
Input Schmitt trigger hysteresis VINHYST   0.12 
VVIO 
 V 
Output voltage low level VOUTLO IOUTLO = 2mA   0.2 V 
Output voltage high level VOUTHI IOUTHI = -2mA VVIO-0.2   V 
Input leakage current IILEAK  -10  10 µA 
Pullup / pull-down resistors RPU/RPD  132 166 200 kΩ 
Digital pin capacitance C   3.5  pF 
 
28.3 Thermal Characteristics 
The following table shall give an idea on the thermal resistance of the package. The thermal 
resistance for a four layer board will provide a good idea on a typical application. Actual therm al 
characteristics will depend on the PCB layout, PCB type and PCB size.  The thermal resistance will 
benefit from thicker CU (inner) layers for spreading heat horizontally within the PCB. Also, air flow will 
reduce thermal resistance. 
 
