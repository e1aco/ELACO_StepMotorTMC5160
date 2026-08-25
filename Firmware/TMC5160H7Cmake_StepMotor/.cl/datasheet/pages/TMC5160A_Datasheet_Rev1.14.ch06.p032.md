# TMC5160A_Datasheet_Rev1.14 — 第6章 · p32

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  32 
 
 
 
www.trinamic.com 
6.1 General Configuration Registers 
GENERAL CONFIGURATION REGISTERS (0X00…0X0F) 
R/W Addr n Register Description / bit names 
RW 0x00 18 GCONF 
Bit GCONF – Global configuration flags  
0 recalibrate 
1: Zero crossing recalibration during driver disable  
(via ENN or via TOFF setting) 
1 faststandstill 
Timeout for step execution until standstill detection: 
1:  Short time: 2^18 clocks 
0:  Normal time: 2^20 clocks 
2 en_pwm_mode 
1: StealthChop voltage PWM mode enabled  
(depending on velocity thresholds) . Switch from 
off to on state while in stand-still and at IHOLD= 
nominal IRUN current, only. 
3 multistep_filt 
1:  Enable step input fi ltering for StealthChop 
optimization with external step source (default=1) 
4 shaft 
1:  Inverse motor direction 
5 diag0_error (only with SD_MODE=1) 
1: Enable DIAG0 active on driver errors:  
 Over temperature ( ot), short to GND ( s2g), 
undervoltage chargepump (uv_cp) 
DIAG0 always shows the reset-status, i.e. is active low 
during reset condition. 
6 diag0_otpw (only with SD_MODE=1) 
1: Enable DIAG0 active on driver over temperature 
prewarning (otpw) 
7 diag0_stall (with SD_MODE=1) 
1: Enable DIAG0 active  on motor stall  (set 
TCOOLTHRS before using this feature) 
diag0_step (with SD_MODE=0) 
0: DIAG0 outputs interrupt signal 
1: Enable DIAG0 as STEP  output (half frequency, 
dual edge triggered) for external STEP/DIR driver 
8 diag1_stall (with SD_MODE=1) 
1: Enable DIAG1 active on motor stall  (set 
TCOOLTHRS before using this feature) 
diag1_dir (with SD_MODE=0) 
0: DIAG1 outputs position compare signal 
1: Enable DIAG1 as DIR output for external STEP/DIR 
driver 
9 diag1_index (only with SD_MODE=1) 
1: Enable DIAG1 active on index position (microstep 
look up table position 0) 
10 diag1_onstate (only with SD_MODE=1) 
1: Enable DIAG1 active when chopper is on (for the 
coil which is in the second half of the fullstep) 
11 diag1_steps_skipped (only with SD_MODE=1) 
1:  Enable output toggle when steps are skipped in 
DcStep mode (increment of LOST_STEPS). Do not 
enable in conjunction with other DIAG1 options. 
