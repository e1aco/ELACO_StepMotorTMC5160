# TMC5160A_Datasheet_Rev1.14 — 第5章 · p35

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  35 
 
 
 
www.trinamic.com 
GENERAL CONFIGURATION REGISTERS (0X00…0X0F) 
R/W Addr n Register Description / bit names 
15..8 OTPMAGIC 
Set to 0xbd to enable programming. A programming 
time of minimum 10ms per bit is recommended (check 
by reading OTP_READ).  
R 0x07  OTP_READ 
Bit OTP_READ (Access to OTP memory result and update) 
See separate table! 
7..0 OTP0 byte 0 read data 
RW 0x08 5 FACTORY_ 
CONF 
4..0 FCLKTRIM (Reset default: OTP) 
0…31: Lowest to highest clock frequency. Check at 
charge pump output. The frequency spa n is not 
guaranteed, but it is tested, that tuning to 12MHz 
internal clock is possible. The devices come preset to 
12MHz clock frequency by OTP programming. 
(Reset Default: OTP) 
W 0x09 19 SHORT_ 
CONF 
Bit SHORT_CONF 
3..0 S2VS_LEVEL:  
Short to VS detector level for lowside FETs. Checks for 
voltage drop in LS MOSFET and sense resistor.  
4 (highest sensitivity) … 15 (lowest sensitivity)  
 
Hint: Settings from 1 to 3 will trigger during normal 
operation due to voltage drop on sense resistor. 
(Reset Default: OTP 6 or 12) 
11..8 S2G_LEVEL:  
Short to GND detector level for highside FETs. Checks 
for voltage drop on high side MOSFET 
2 (highest sensitivity) … 15 (lowest sensitivity)  
Attention: Settings below 6 not recommended at >52 V 
operation – false detection might result 
(Reset Default: OTP 6 or 12) 
17..16 SHORTFILTER:  
Spike filtering bandwidth for short detection  
0 (lowest, 100ns), 1 (1µs), 2 (2µs) 3 (3µs) 
Hint: A good PCB layout will allow using setting 0. 
Increase value, if erroneous short detection occurs.  
(Reset Default = %01) 
18 shortdelay: Short detection delay  
0=750ns: normal, 1=1500ns: high 
The short detection delay shall cover the bridge 
switching time. 0 will work for most applications. 
(Reset Default = 0) 
W 0x0A 22 DRV_CONF 
Bit DRV_CONF 
4..0 BBMTIME:  
Break-Before make delay 
0=shortest (100ns) … 16 (200ns) … 24=longest (375ns) 
>24 not recommended, use BBMCLKS instead 
 
Hint: Choose the lowest setting safely covering the 
switching event  in order to avoid bridge cross -
conduction. Add roughly 30% of reserve. 
(Reset Default = 0) 
