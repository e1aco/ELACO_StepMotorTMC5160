# TMC5160A_Datasheet_Rev1.14 — 第6章 · p37

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
37 
 
 
 
www.trinamic.com 
6.1.1 
OTP_READ – OTP configuration memory 
The OTP memory holds power up defaults for certain registers. All OTP memory bits are cleared to 0 
by default. Programming only can set bits, clearing bits is not possible. Factory tuning of the clock 
frequency affects otp0.0 to otp0.4. The state of these bits therefore may differ between individual ICs. 
 
0X07: OTP_READ – OTP MEMORY MAP 
Bit 
Name 
Function 
Comment 
7 
otp0.7 
otp_TBL 
Reset default for TBL: 
0: TBL=%10 (~3µs) 
1: TBL=%01 (~2µs) 
6 
otp0.6 
otp_BBM 
Reset default for DRVCONF.BBMCLKS 
0: BBMCLKS=4 
1: BBMCLKS=2 
5 
otp0.5 
otp_S2_LEVEL 
Reset default for Short detection Levels:  
0: S2G_LEVEL = S2VS_LEVEL = 6 
1: S2G_LEVEL = S2VS_LEVEL = 12 
4 
otp0.4 
OTP_FCLKTRIM 
Reset default for FCLKTRIM 
0: lowest frequency setting 
31: highest frequency setting  
Attention: This value is pre-programmed by factory clock 
trimming to the default clock frequency of 12MHz and 
differs between individual ICs! It should not be altered. 
3 
otp0.3 
2 
otp0.2 
1 
otp0.1 
0 
otp0.0 
 
 


<!-- detected tables -->

|  | 0X07: OTP READ – OTP MEMORY MAP _ |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Bit |  |  | Name |  |  | Function |  |  | Comment |  |
| 7 |  |  | otp0.7 |  |  | otp TBL _ |  |  | Reset default for TBL: 0: TBL=%10 (~3µs) 1: TBL=%01 (~2µs) |  |  |
| 6 |  |  | otp0.6 |  |  | otp BBM _ |  |  | Reset default for DRVCONF.BBMCLKS 0: BBMCLKS=4 1: BBMCLKS=2 |  |  |
| 5 |  |  | otp0.5 |  |  | otp S2 LEVEL _ _ |  |  | Reset default for Short detection Levels: 0: S2G LEVEL = S2VS LEVEL = 6 _ _ 1: S2G LEVEL = S2VS LEVEL = 12 |  |  |
| 4 |  |  | otp0.4 |  |  | OTP FCLKTRIM _ |  |  | _ _ Reset default for FCLKTRIM 0: lowest frequency setting 31: highest frequency setting Attention: This value is pre-programmed by factory clock trimming to the default clock frequency of 12MHz and differs between individual ICs! It should not be altered. |  |  |
|  | 3 |  | otp0.3 |  |  |  |  |  |  |  |  |
|  | 2 |  | otp0.2 |  |  |  |  |  |  |  |  |
|  | 1 |  | otp0.1 |  |  |  |  |  |  |  |  |
| 0 | 0 |  | otp0.0 |  |  |  |  |  |  |  |  |
