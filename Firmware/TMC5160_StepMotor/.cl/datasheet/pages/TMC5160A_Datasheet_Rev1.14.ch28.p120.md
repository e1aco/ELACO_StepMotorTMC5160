# TMC5160A_Datasheet_Rev1.14 — 第28章 · p120

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
120 
 
 
 
www.trinamic.com 
27 Absolute Maximum Ratings 
The maximum ratings may not be exceeded under any circumstances. Operating the circuit at or near 
more than one maximum rating at a time for extended periods shall be avoided by application 
design. 
 
Parameter 
Symbol 
Min 
Max 
Unit 
Supply voltage operating with inductive load 
VVS, VVSA 
-0.5 
60 
V 
Supply and bridge voltage short time peak (limited by 
peak voltage on charge pump output and Cxx pins*) 
VVSMAX 
 
64 
V 
VSA when different from VS 
VVSAMAX 
-0.5 
60 
V 
Peak voltages on Cxx bootstrap pins and VCP 
VCxCP 
 
76 
V 
Supply voltage V12 
V12VOUT 
-0.5 
14 
V 
Peak voltages on BM pins (due to stray inductivity) 
VBMx 
-6 
VVS+6 
V 
Peak voltages on Cxx bootstrap pins relative to BM 
VCxBMx 
-0.5 
16 
V 
I/O supply voltage on VCC_IO 
VVIO 
-0.5 
5.5 
V 
digital VCC supply voltage (normally supplied by 5VOUT) 
VVCC 
-0.5 
5.5 
V 
Logic input voltage 
VI 
-0.5 
VVIO+0.5 
V 
Maximum current to / from digital pins 
and analog low voltage I/Os (short time peak current) 
IIO 
 
+/-500 
mA 
5V regulator output current (internal plus external load) 
I5VOUT 
 
30 
mA 
5V regulator continuous power dissipation (VVSA-5V) * I5VOUT 
P5VOUT 
 
1 
W 
12V regulator output current (internal plus external load) 
I12VOUT 
 
20 
mA 
12V regulator cont. power dissipation (VVM-12V) * I12VOUT 
P12VOUT 
 
0.5 
W 
Junction temperature 
TJ 
-50 
150 
°C 
Storage temperature 
TSTG 
-55 
150 
°C 
ESD-Protection for interface pins (Human body model, 
HBM) 
VESDAP 
 
4 
kV 
ESD-Protection for handling (Human body model, HBM) 
VESD 
 
1 
kV 
 
*) Stray inductivity of power routing will lead to ringing of the supply voltage when driving an 
inductive load. This ringing results from the fast switching slopes of the driver outputs in 
combination with reverse recovery of the body diodes of the output driver MOSFETs. Even small trace 
inductivities as well as stray inductivity of sense resistors can easily generate a few volts of ringing 
leading to temporary voltage overshoot. This should be considered when working near the maximum 
voltage.  
 
28 Electrical Characteristics 
28.1 Operational Range 
Parameter 
Symbol 
Min 
Max 
Unit 
Junction temperature 
TJ 
-40 
125 
°C 
Supply voltage for motor and bridge 
VVS 
10 
55 
V 
Supply voltage VSA 
VVSA 
10 
50 
V 
Supply voltage for VSA and 12OUT (internal gate voltage 
regulator bridged) 
V12VOUT, 
VVSA 
10 
13 
V 
Lower Supply voltage (reduced spec, short to GND 
protection not functional), lower limit depending on 
MOSFETs gate threshold voltage and load current 
VVS 
8 
 
V 
I/O supply voltage on VCC_IO 
VVIO 
3.00 
5.25 
V 
 
 
 


<!-- detected tables -->

| Parameter |  |  | Symbol |  |  | Min |  |  | Max |  |  | Unit |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Supply voltage operating with inductive load |  | V , V VS VSA |  |  | -0.5 |  |  | 60 |  |  | V |  |  |
| Supply and bridge voltage short time peak (limited by peak voltage on charge pump output and Cxx pins*) |  | V VSMAX |  |  |  |  |  | 64 |  |  | V |  |  |
| VSA when different from VS |  | V VSAMAX |  |  | -0.5 |  |  | 60 |  |  | V |  |  |
| Peak voltages on Cxx bootstrap pins and VCP |  | V CxCP |  |  |  |  |  | 76 |  |  | V |  |  |
| Supply voltage V12 |  | V 12VOUT |  |  | -0.5 |  |  | 14 |  |  | V |  |  |
| Peak voltages on BM pins (due to stray inductivity) |  | V BMx |  |  | -6 |  |  | V +6 VS |  |  | V |  |  |
| Peak voltages on Cxx bootstrap pins relative to BM |  | V CxBMx |  |  | -0.5 |  |  | 16 |  |  | V |  |  |
| I/O supply voltage on VCC IO |  | V VIO |  |  | -0.5 |  |  | 5.5 |  |  | V |  |  |
| _ digital VCC supply voltage (normally supplied by 5VOUT) |  | V VCC |  |  | -0.5 |  |  | 5.5 |  |  | V |  |  |
| Logic input voltage |  | V I |  |  | -0.5 |  |  | V +0.5 VIO |  |  | V |  |  |
| Maximum current to / from digital pins and analog low voltage I/Os (short time peak current) |  | I IO |  |  |  |  |  | +/-500 |  |  | mA |  |  |
| 5V regulator output current (internal plus external load) |  | I 5VOUT |  |  |  |  |  | 30 |  |  | mA |  |  |
| 5V regulator continuous power dissipation (V -5V) * I VSA 5VOUT |  | P 5VOUT |  |  |  |  |  | 1 |  |  | W |  |  |
| 12V regulator output current (internal plus external load) |  | I 12VOUT |  |  |  |  |  | 20 |  |  | mA |  |  |
| 12V regulator cont. power dissipation (V -12V) * I VM 12VOUT |  | P 12VOUT |  |  |  |  |  | 0.5 |  |  | W |  |  |
| Junction temperature |  | T J |  |  | -50 |  |  | 150 |  |  | °C |  |  |
| Storage temperature |  | T STG |  |  | -55 |  |  | 150 |  |  | °C |  |  |
| ESD-Protection for interface pins (Human body model, HBM) |  | V ESDAP |  |  |  |  |  | 4 |  |  | kV |  |  |
| ESD-Protection for handling (Human body model, HBM) |  | V ESD |  |  |  |  |  | 1 |  |  | kV |  |  |

| Parameter |  |  | Symbol |  |  | Min |  |  | Max |  |  | Unit |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Junction temperature |  | T J |  |  | -40 |  |  | 125 |  |  | °C |  |  |
| Supply voltage for motor and bridge |  | V VS |  |  | 10 |  |  | 55 |  |  | V |  |  |
| Supply voltage VSA |  | V VSA |  |  | 10 |  |  | 50 |  |  | V |  |  |
| Supply voltage for VSA and 12OUT (internal gate voltage |  | V , 12VOUT V VSA |  |  | 10 |  |  | 13 |  |  | V |  |  |
| regulator bridged) |  |  |  |  |  |  |  |  |  |  |  |  |  |
| Lower Supply voltage (reduced spec, short to GND |  | V VS |  |  | 8 |  |  |  |  |  | V |  |  |
| protection not functional), lower limit depending on |  |  |  |  |  |  |  |  |  |  |  |  |  |
| MOSFETs gate threshold voltage and load current |  |  |  |  |  |  |  |  |  |  |  |  |  |
| I/O supply voltage on VCC IO |  | V VIO |  |  | 3.00 |  |  | 5.25 |  |  | V |  |  |
