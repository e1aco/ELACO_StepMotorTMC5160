# TMC5160A_Datasheet_Rev1.14 — 第5章 · p36

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  36 
 
 
 
www.trinamic.com 
GENERAL CONFIGURATION REGISTERS (0X00…0X0F) 
R/W Addr n Register Description / bit names 
11..8 BBMCLKS:  
0..15: Digital BBM time in clock cycles (typ. 83ns).  
The longer setting rules (BBMTIME vs. BBMCLKS).  
(Reset Default: OTP 4 or 2) 
17..16 OTSELECT:  
Selection of over temperature lev el for bridge disable, 
switch on after cool down to 120°C / OTPW level. 
00: 150°C 
01: 143°C 
10: 136°C (not recommended when VSA > 24V) 
11: 120°C (not recommended, no hysteresis) 
 
Hint: Adapt overtemperature threshold as required to 
protect the MOSFETs or other components on the PCB. 
(Reset Default = %00) 
19..18 DRVSTRENGTH:  
Selection of gate driver current . Adapts the gate driver 
current to the gate charge of the external MOSFETs. 
00: weak 
01: weak+TC (medium above OTPW level) 
10: medium 
11: strong  
 
Hint: Choose the lowest setting giving slopes <100ns. 
(Reset Default = %10) 
21..20 FILT_ISENSE:  
Filter time constant of sense amplifier to suppress 
ringing and coupling from second coil operation 
00: low – 100ns 
01: – 200ns 
10: – 300ns 
11: high – 400ns 
 
Hint: Increase setting if motor chopper noise  occurs 
due to cross-coupling of both coils. 
(Reset Default = %00) 
W 0x0B 8 GLOBAL 
SCALER 
7..0 Global scaling of Motor current. This value is multiplied 
to the current scaling in order to adapt a drive to a  
certain motor type. This value should be chosen before 
tuning other settings, because it also influences 
chopper hysteresis. 
 
0:  Full Scale (or write 256) 
1 … 31: Not allowed for operation 
32 … 255: 32/256 … 255/256 of maximum current.  
 
Hint: Values >128 recommended for best results 
(Reset Default = 0) 
R 0x0C 16 OFFSET_ 
READ 
15..8 Offset calibration result phase A (signed) 
7..0 Offset calibration result phase B (signed) 
  
