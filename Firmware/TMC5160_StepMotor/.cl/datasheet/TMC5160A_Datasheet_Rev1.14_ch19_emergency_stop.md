# TMC5160A_Datasheet_Rev1.14 — 第19章 EMERGENCY STOP

--- [PAGE 106] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
106 
 
 
 
www.trinamic.com 
When the microstep sequencer advances within the table, it calculates the actual current values for 
the motor coils with each microstep and stores them to the registers CUR_A and CUR_B. However the 
incremental coding requires an absolute initialization, especially when the microstep table becomes 
modified. Therefore CUR_A and CUR_B become initialized whenever MSCNT passes zero. 
 
Two registers control the starting values of the tables: 
- 
As the starting value at zero is not necessarily 0 (it might be 1 or 2), it can be programmed 
into the starting point register START_SIN.  
- 
In the same way, the start of the second wave for the second motor coil needs to be stored 
in START_SIN90. This register stores the resulting table entry for a phase shift of 90° for a 2-
phase motor. 
 
Hint 
Refer chapter 6.5 for the register set and for the default table function stored in the drivers. The 
default table is a good base for realizing an own table. 
The TMC5160-EVAL comes with a calculation tool for own waves. 
 
 
Initialization example for the default microstep table: 
 
MSLUT[0]= %10101010101010101011010101010100 = 0xAAAAB554 
MSLUT[1]= %01001010100101010101010010101010 = 0x4A9554AA 
MSLUT[2]= %00100100010010010010100100101001 = 0x24492929 
MSLUT[3]= %00010000000100000100001000100010 = 0x10104222 
MSLUT[4]= %11111011111111111111111111111111 = 0xFBFFFFFF 
MSLUT[5]= %10110101101110110111011101111101 = 0xB5BB777D 
MSLUT[6]= %01001001001010010101010101010110 = 0x49295556 
MSLUT[7]= %00000000010000000100001000100010 = 0x00404222 
 
MSLUTSEL= 0xFFFF8056: 
X1=128, X2=255, X3=255 
W3=%01, W2=%01, W1=%01, W0=%10 
 
MSLUTSTART= 0x00F70000: 
START_SIN_0= 0, START_SIN90= 247 
 
19 Emergency Stop 
The driver provides a negative active enable pin ENN to safely switch off all power MOSFETs. This 
allows putting the motor into freewheeling. Further, it is a safe hardware function whenever an 
emergency-stop not coupled to software is required. Some applications may require the driver to be 
put into a state with active holding current or with a passive braking mode. This is possible by 
programming the pin ENCA_DCIN to act as a step disable function. Set GCONF flag stop_enable to 
activate this option. Whenever ENCA_DCIN becomes pulled up, the motor will stop abruptly and go to 
the power down state, as configured via IHOLD, IHOLDDELAY and StealthChop standstill options. 
Disabling the driver via ENN will require three clock cycles to safely switch off the driver.  

