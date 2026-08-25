# TMC5160A_Datasheet_Rev1.14 — 第6章 · p43

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  43 
 
 
 
www.trinamic.com 
6.3.2.1 SW_MODE – Reference Switch & StallGuard2 Event Configuration Register 
0X34: SW_MODE – REFERENCE SWITCH AND STALLGUARD2 EVENT CONFIGURATION REGISTER 
Bit Name Comment 
11 en_softstop 0: Hard stop 
1: Soft stop 
 
The soft stop mode always uses the deceleration ramp settings DMAX, V1, 
D1, VSTOP and TZEROWAIT for stopping the motor. A stop occurs when 
the velocity sign matches the reference switch position (REFL for negative 
velocities, REFR for positive velocities) and the respecti ve switch stop 
function is enabled.  
 
A hard stop also uses TZEROWAIT before the motor becomes released. 
 
Attention: Do not use soft stop in combination with StallGuard2. Use soft 
stop for StealthChop operation at high velocity . In this case, hard stop 
must be avoided, as it could result in severe overcurrent. 
10 sg_stop 1: Enable stop by StallGuard2 (also available in DcStep mode). Disable to 
release motor after stop event. Program TCOOLTHRS for velocity threshold. 
 
Hint: Do not enable during motor spin -up, wait until the motor velocity 
exceeds a certain value, where StallGuard2 delivers a stable result.  This 
velocity threshold should be programmed using TCOOLTHRS. 
9 en_latch_encoder 1: Latch encoder position to ENC_LATCH upon reference switch event. 
8 latch_r_inactive 1: Activates latching of the position to XLATCH upon an inactive going 
edge on the right reference switch input REFR.  The active level is defined 
by pol_stop_r. 
7 latch_r_active 1: Activates latching of the position to XLATCH upon an active going edge 
on the right reference switch input REFR. 
 
Hint: Activate latch_r_active to detect any spurious stop event by reading 
status_latch_r. 
6 latch_l_inactive 1: Activates latching of the position to XLATCH upon an inactive going 
edge on the left r eference switch input REFL.  The active level is defined 
by pol_stop_l. 
5 latch_l_active 1: Activates latching of the position to XLATCH upon an active going edge 
on the left reference switch input REFL. 
 
Hint: Activate latch_l_active to detect any spuriou s stop event by reading 
status_latch_l. 
4 swap_lr 1: Swap the left and the right reference switch input REFL and REFR 
3 pol_stop_r Sets the active polarity of the right reference switch input  
0=non-inverted, high active: a high level on REFR stops the motor 
1=inverted, low active: a low level on REFR stops the motor 
2 pol_stop_l Sets the active polarity of the left reference switch input  
0=non-inverted, high active: a high level on REFL stops the motor 
1=inverted, low active: a low level on REFL stops the motor 
1 stop_r_enable 1: Enables automatic motor stop during active right reference switch input 
 
Hint: The motor restarts in case the stop switch becomes released. 
0 stop_l_enable 1: Enables automatic motor stop during active left reference switch input 
 
Hint: The motor restarts in case the stop switch becomes released. 
 
  
