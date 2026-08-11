# TMC5160A_Datasheet_Rev1.14 — 第6章 · p34

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
34 
 
 
 
www.trinamic.com 
GENERAL CONFIGURATION REGISTERS (0X00…0X0F) 
R/W 
Addr 
n 
Register 
Description / bit names 
W 
0x03 
8 
+ 
4 
SLAVECONF 
Bit 
SLAVECONF 
7..0 SLAVEADDR:  
These eight bits set the address of unit for the UART 
interface. The address becomes incremented by one 
when the external address pin NEXTADDR is active.  
Range: 0-253 (254 cannot be incremented), default=0 
11..8 SENDDELAY:  
0, 1:  
8 bit times (not allowed with multiple slaves)  
2, 3:  
3*8 bit times 
4, 5:  
5*8 bit times 
6, 7:  
7*8 bit times 
8, 9:  
9*8 bit times 
10, 11:  11*8 bit times 
12, 13:  13*8 bit times 
14, 15:  15*8 bit times 
R 
0x04 
8 
+ 
8 
IOIN 
Bit 
INPUT 
 Reads the state of all input pins available 
0 REFL_STEP 
1 REFR_DIR 
2 ENCB_DCEN_CFG4 
3 ENCA_DCIN_CFG5 
4 DRV_ENN 
5 ENC_N_DCO_CFG6 
6 SD_MODE (1=External step and dir source) 
7 SWCOMP_IN (Shows voltage difference of SWN and 
SWP. Bring DIAG outputs to high level with pushpull 
disabled to test the comparator.) 
31.. 
24 
VERSION: 0x30=first version of the IC 
Identical numbers mean full digital compatibility. 
W 
0x04 
1 
OUTPUT 
Bit 
OUTPUT 
 
Sets the IO output pin polarity in UART mode  
0 
In UART mode, SDO_CFG0 is an output. This bit 
programs the output polarity of this pin. Its main 
purpose it to use SDO_CFG0 as NAO next address 
output signal for chain addressing of multiple ICs. 
Hint: Reset Value is 1 for use as NAO to next IC in 
single wire chain 
W 
0x05 
32 
X_COMPARE 
Position comparison register for motion controller position 
strobe. The Position pulse is available on output SWP_DIAG1.  
 
XACTUAL = X_COMPARE:  
- 
Output signal PP (position pulse) becomes high. It 
returns to a low state, if the positions mismatch. 
W 
0x06 
 
OTP_PROG 
Bit 
OTP_PROGRAM – OTP programming  
Write access programs OTP memory (one bit at a time),  
Read access refreshes read data from OTP after a write 
2..0 OTPBIT 
Selection of OTP bit to be programmed to the selected 
byte location (n=0..7: programs bit n to a logic 1)  
5..4 
 
OTPBYTE 
Set to 00 


<!-- detected tables -->

|  | GENERAL CONFIGURATION REGISTERS (0X00…0X0F) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | R/W |  |  | Addr |  |  | n |  |  | Register |  |  | Description / bit names |  |  |  |  |
| W |  |  | 0x03 |  |  | 8 + 4 |  |  | SLAVECONF |  |  |  | Bit |  |  | SLAVECONF |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 7..0 |  |  | SLAVEADDR: These eight bits set the address of unit for the UART interface. The address becomes incremented by one when the external address pin NEXTADDR is active. Range: 0-253 (254 cannot be incremented), default=0 |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 11..8 |  |  | SENDDELAY: 0, 1: 8 bit times (not allowed with multiple slaves) 2, 3: 3*8 bit times 4, 5: 5*8 bit times 6, 7: 7*8 bit times 8, 9: 9*8 bit times 10, 11: 11*8 bit times 12, 13: 13*8 bit times 14, 15: 15*8 bit times |  |  |
| R |  |  | 0x04 |  |  | 8 + 8 |  |  | IOIN |  |  |  | Bit |  |  | INPUT |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | Reads the state of all input pins available |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 0 |  |  | REFL STEP |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 1 |  |  | _ REFR DIR |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 2 |  |  | _ ENCB DCEN CFG4 |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 3 |  |  | _ _ ENCA DCIN CFG5 |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 4 |  |  | _ _ DRV ENN |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 5 |  |  | _ ENC N DCO CFG6 _ _ _ |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 6 |  |  | SD MODE (1=External step and dir source) |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 7 |  |  | _ SWCOMP IN (Shows voltage difference of SWN and _ SWP. Bring DIAG outputs to high level with pushpull disabled to test the comparator.) |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 31.. 24 |  |  | VERSION: 0x30=first version of the IC Identical numbers mean full digital compatibility. |  |  |
| W |  |  | 0x04 |  |  | 1 |  |  | OUTPUT |  |  | Bit |  |  | OUTPUT |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | Sets the IO output pin polarity in UART mode |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 0 |  |  | In UART mode, SDO CFG0 is an output. This bit _ programs the output polarity of this pin. Its main purpose it to use SDO CFG0 as NAO next address _ output signal for chain addressing of multiple ICs. Hint: Reset Value is 1 for use as NAO to next IC in single wire chain |  |  |
| W |  |  | 0x05 |  |  | 32 |  |  | X COMPARE _ |  |  | Position comparison register for motion controller position strobe. The Position pulse is available on output SWP DIAG1. _ XACTUAL = X COMPARE: _ - Output signal PP (position pulse) becomes high. It returns to a low state, if the positions mismatch. |  |  |  |  |  |
| W |  |  | 0x06 |  |  |  |  |  | OTP PROG _ |  |  | Bit |  |  |  | OTP PROGRAM – OTP programming |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | _ Write access programs OTP memory (one bit at a time), |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | Read access refreshes read data from OTP after a write |  |
|  |  |  |  |  |  |  |  |  |  |  |  | 2..0 |  |  |  | OTPBIT |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | Selection of OTP bit to be programmed to the selected |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | byte location (n=0..7: programs bit n to a logic 1) |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | 5..4 |  |  | OTPBYTE |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | Set to 00 |  |
