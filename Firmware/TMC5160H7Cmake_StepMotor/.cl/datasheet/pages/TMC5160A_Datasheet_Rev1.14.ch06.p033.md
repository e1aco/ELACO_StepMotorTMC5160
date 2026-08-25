# TMC5160A_Datasheet_Rev1.14 — 第6章 · p33

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  33 
 
 
 
www.trinamic.com 
GENERAL CONFIGURATION REGISTERS (0X00…0X0F) 
R/W Addr n Register Description / bit names 
12 diag0_int_pushpull  
0: SWN_DIAG0 is open collector output (active low) 
1: Enable SWN_DIAG0 push pull output (active high) 
13 diag1_poscomp_pushpull  
0: SWP_DIAG1 is open collector output (active low) 
1: Enable SWP_DIAG1 push pull output (active high) 
14 small_hysteresis 
0: Hysteresis for step frequency comparison is 1/16 
1: Hysteresis for step frequency comparison is 1/32 
15 stop_enable 
0:  Normal operation 
1: Emergency stop: ENCA_DCIN stops the sequencer 
when tied high (no steps become executed by 
the sequencer, motor goes to standstill state).  
16 direct_mode 
0:  Normal operation 
1: Motor coil currents and polarity directly 
programmed via serial interface: Register XTARGET 
(0x2D) specifies signed coil A current (bits 8..0) 
and coil B current (bits 24..16).  In this mode, the 
current is scaled by IHOLD setting. Velocity based 
current regulation of StealthChop is not available 
in this mode.  The automatic StealthChop current 
regulation will work only for low stepper motor 
velocities. 
17 test_mode 
0:  Normal operation 
1: Enable analog test output on pin ENCN_DCO. 
IHOLD[1..0] selects the function of ENCN_DCO:  
0…2: T120, DAC, VDDH 
Hint: Not for user, set to 0 for normal operation! 
R+ 
WC 0x01 3 GSTAT 
Bit GSTAT – Global status flags  
(Re-Write with ‘1’ bit to clear respective flags) 
0 reset 
1:  Indicates that the IC has been reset. All registers 
have been cleared to reset values. 
1 drv_err  
1:  Indicates, that the driver has been shut down 
due to overtemperature or short circuit detection . 
Read DRV_STATUS for details. The flag can only 
be cleared when  the temperature  is below the 
limit again. 
2 uv_cp 
1: Indicates an undervoltage on the charge pump. 
The driver is disabled during undervoltage . This 
flag is latched for information.  
R 0x02 8 IFCNT 
Interface transmission counter. This register becomes 
incremented with each successful UART interface write access. 
It can be read out to check the serial transmission for lost 
data. Read accesses do not change the content. Disabled in SPI 
operation. The counter wraps around from 255 to 0. 
 
 
