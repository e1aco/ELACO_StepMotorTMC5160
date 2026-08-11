# TMC5160A_Datasheet_Rev1.14 — 第28章 · p123

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
123 
 
 
 
www.trinamic.com 
Detector levels 
DC-Characteristics 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
VVSA undervoltage threshold for 
RESET 
VUV_VSA 
VVSA rising 
3.6 
4 
4.6 
V 
V5VOUT undervoltage threshold for 
RESET 
VUV_5VOUT 
V5VOUT rising 
 
3.5 
 
V 
VVCC_IO undervoltage threshold for 
RESET 
VUV_VIO 
VVCC_IO rising (delay 
typ. 10µs) 
2.0 
2.5 
3.0 
V 
VVCC_IO undervoltage detector 
hysteresis 
VUV_VIOHYST  
 
0.3 
 
V 
Overtemperature prewarning 
120°C 
TOTPW 
Temperature rising 
100 
120 
140 
°C 
Overtemperature shutdown  
136 °C 
TOT136 
Temperature rising 
 
136 
 
°C 
Overtemperature shutdown  
143 °C 
TOT143 
Temperature rising 
 
143 
 
°C 
Overtemperature shutdown  
150 °C 
TOT150 
Temperature rising 
135 
150 
170 
°C 
 
Sense resistor voltage levels 
DC-Characteristics 
fCLK=16MHz 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
Sense input peak threshold 
voltage (low sensitivity)  
(VSRxH-VSRxL) 
VSRT 
GLOBALSCALER=0 
csactual=31 
sin_x=248 
Hyst.=0; IBRxy=0 
 
325 
 
mV 
Sense input tolerance / motor 
current full scale tolerance  
-using internal reference 
ICOIL 
GLOBALSCALER=0 
-5 
 
+5 
% 
 
Digital pins 
DC-Characteristics 
Parameter 
Symbol Conditions 
Min 
Typ 
Max 
Unit 
Input voltage low level 
VINLO 
 
-0.3 
 
0.3 VVIO 
V 
Input voltage high level 
VINHI 
 
0.7 VVIO 
 
VVIO+0.3 
V 
Input Schmitt trigger hysteresis 
VINHYST 
 
 
0.12 
VVIO 
 
V 
Output voltage low level 
VOUTLO 
IOUTLO = 2mA 
 
 
0.2 
V 
Output voltage high level 
VOUTHI 
IOUTHI = -2mA 
VVIO-0.2 
 
 
V 
Input leakage current 
IILEAK 
 
-10 
 
10 
µA 
Pullup / pull-down resistors 
RPU/RPD 
 
132 
166 
200 
kΩ 
Digital pin capacitance 
C 
 
 
3.5 
 
pF 
 
28.3 Thermal Characteristics 
The following table shall give an idea on the thermal resistance of the package. The thermal 
resistance for a four layer board will provide a good idea on a typical application. Actual thermal 
characteristics will depend on the PCB layout, PCB type and PCB size. The thermal resistance will 
benefit from thicker CU (inner) layers for spreading heat horizontally within the PCB. Also, air flow will 
reduce thermal resistance. 
 


<!-- detected tables -->

|  | Detector levels |  |  | DC-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
|  | V undervoltage threshold for VSA |  | V UVVSA _ |  |  | V rising VSA |  |  | 3.6 |  |  | 4 |  |  | 4.6 |  |  | V |  |  |
|  | RESET |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | V undervoltage threshold for 5VOUT |  | V UV5VOUT _ |  |  | V rising 5VOUT |  |  |  |  |  | 3.5 |  |  |  |  |  | V |  |  |
|  | RESET |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | V undervoltage threshold for VCCIO |  | V UVVIO _ |  |  | V rising (delay VCCIO _ typ. 10µs) |  |  | 2.0 |  |  | 2.5 |  |  | 3.0 |  |  | V |  |  |
|  | _ RESET |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | V undervoltage detector VCCIO |  | V UVVIOHYST _ |  |  |  |  |  |  |  |  | 0.3 |  |  |  |  |  | V |  |  |
|  | _ hysteresis |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Overtemperature prewarning |  | T OTPW |  |  | Temperature rising |  |  | 100 |  |  | 120 |  |  | 140 |  |  | °C |  |  |
|  | 120°C |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Overtemperature shutdown |  | T OT136 |  |  | Temperature rising |  |  |  |  |  | 136 |  |  |  |  |  | °C |  |  |
|  | 136 °C |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Overtemperature shutdown |  | T OT143 |  |  | Temperature rising |  |  |  |  |  | 143 |  |  |  |  |  | °C |  |  |
|  | 143 °C |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Overtemperature shutdown |  | T OT150 |  |  | Temperature rising |  |  | 135 |  |  | 150 |  |  | 170 |  |  | °C |  |  |
|  | 150 °C |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |

| Sense resistor voltage levels |  |  |  | DC-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  |  |  |  | f =16MHz CLK |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
| Sense input peak threshold voltage (low sensitivity) (V -V ) SRxH SRxL | Sense input peak threshold |  | V SRT |  |  | GLOBALSCALER=0 csactual=31 sin x=248 _ Hyst.=0; I =0 BRxy |  |  |  |  |  | 325 |  |  |  |  |  | mV |  |  |
|  | voltage (low sensitivity) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | (V -V ) SRxH SRxL |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | Sense input tolerance / motor |  | I COIL |  |  | GLOBALSCALER=0 |  |  | -5 |  |  |  |  |  | +5 |  |  | % |  |  |
|  | current full scale tolerance |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|  | -using internal reference |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |

|  | Digital pins |  |  | DC-Characteristics |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Parameter |  |  | Symbol |  |  | Conditions |  |  | Min |  |  | Typ |  |  | Max |  |  | Unit |  |
|  | Input voltage low level |  | V INLO |  |  |  |  |  | -0.3 |  |  |  |  |  | 0.3 V VIO |  |  | V |  |  |
|  | Input voltage high level |  | V INHI |  |  |  |  |  | 0.7 V VIO |  |  |  |  |  | V +0.3 VIO |  |  | V |  |  |
| Input Schmitt trigger hysteresis | Input Schmitt trigger hysteresis |  | V INHYST |  |  |  |  |  |  |  |  | 0.12 V VIO |  |  |  |  |  | V |  |  |
|  | Output voltage low level |  | V OUTLO |  |  | I = 2mA OUTLO |  |  |  |  |  |  |  |  | 0.2 |  |  | V |  |  |
|  | Output voltage high level |  | V OUTHI |  |  | I = -2mA OUTHI |  |  | V -0.2 VIO |  |  |  |  |  |  |  |  | V |  |  |
|  | Input leakage current |  | I ILEAK |  |  |  |  |  | -10 |  |  |  |  |  | 10 |  |  | µA |  |  |
|  | Pullup / pull-down resistors |  | R /R PU PD |  |  |  |  |  | 132 |  |  | 166 |  |  | 200 |  |  | kΩ |  |  |
|  | Digital pin capacitance |  | C |  |  |  |  |  |  |  |  | 3.5 |  |  |  |  |  | pF |  |  |
