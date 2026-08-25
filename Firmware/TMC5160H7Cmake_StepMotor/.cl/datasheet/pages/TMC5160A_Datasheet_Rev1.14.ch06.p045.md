# TMC5160A_Datasheet_Rev1.14 — 第6章 · p45

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  45 
 
 
 
www.trinamic.com 
6.4 Encoder Registers 
 
Attention:  
The encoder interface is not available in Step&Direction mode, as the encoder pins serve a different 
function in that mode. 
 
 
ENCODER REGISTER SET (0X38…0X3C)  
R/W Addr n Register Description / bit names Range [Unit] 
RW 0x38 11 ENCMODE Encoder configuration and use of N channel 
See separate table! 
 
RW 0x39 32 X_ENC Actual encoder position (signed) -2^31… 
+(2^31)-1 
W 0x3A 32 ENC_CONST 
Accumulation constant (signed) 
16 bit integer part, 16 bit fractional part 
 
X_ENC accumulates 
+/- ENC_CONST / (2^16*X_ENC) (binary) 
or 
+/-ENC_CONST / (10^4*X_ENC) (decimal) 
 
ENCMODE bit enc_sel_decimal switches 
between decimal and binary setting.  
Use the sign, to match rotation direction! 
binary: 
± [µsteps/2^16] 
±(0 … 
32767.999847) 
decimal: 
±(0.0 … 
32767.9999) 
reset default = 
1.0 (=65536) 
R+ 
WC 0x3B 2 ENC_STATUS 
Encoder status information 
 
bit 0: n_event 
bit 1: deviation_warn 
 
1: Event detected.  
To clear the s tatus bit, write with a 1 bit at 
the corresponding position. 
 
Deviation_warn cannot be cleared while a 
warning still persists. Set ENC_DEVIATION 
zero to disable. 
Both bits are ORed to the interrupt output  
signal. 
 
R 0x3C 32 ENC_LATCH Encoder position X_ENC latched on N event  
W 0x3D 20 ENC_ 
DEVIATION 
Maximum number of steps deviation 
between encoder counter and XACTUAL for 
deviation warning  
Result in flag ENC_STATUS.deviation_warn 
0=Function is off.  
 
