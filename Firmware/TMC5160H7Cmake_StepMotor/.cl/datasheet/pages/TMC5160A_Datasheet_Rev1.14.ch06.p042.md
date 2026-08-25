# TMC5160A_Datasheet_Rev1.14 — 第6章 · p42

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  42 
 
 
 
www.trinamic.com 
6.3.2 Ramp Generator Driver Feature Control Register Set 
RAMP GENERATOR DRIVER FEATURE CONTROL REGISTER SET (0X30…0X36)  
R/W Addr n Register Description / bit names 
W 0x33 23 VDCMIN 
Automatic commutation DcStep becomes enabled above 
velocity V DCMIN (unsigned) (only when using internal ramp 
generator, not for STEP/DIR interface – in STEP/DIR mode, 
DcStep becomes enabled by the external signal DCEN) 
 
In this mode, the actual position is  determined by the sensor -
less motor commutation and becomes fed back to XACTUAL. In 
case the motor becomes heavily loaded, VDCMIN also is used 
as the minimum step velocity.  Activate stop on stall ( sg_stop) 
to detect step loss. 
 
0: Disable, DcStep off  
|VACT| ≥ VDCMIN ≥ 256:  
- Triggers the same actions as exceeding THIGH setting.  
- Switches on automatic commutation DcStep 
 
Hint: Also set DCCTRL parameters in order to operate DcStep. 
 
(Only bits 22… 8 are used for value and for comparison) 
RW 0x34 12 SW_MODE 
 
Switch mode configuration 
See separate table! 
R+ 
WC 0x35 14 RAMP_STAT 
 
Ramp status and switch event status 
See separate table! 
R 0x36 32 XLATCH 
Ramp generator latch posit ion, latches XACTUAL upon a 
programmable switch event (see SW_MODE). 
 
Hint: The encoder position can be latched to ENC_LATCH 
together with XLATCH to allow consistency checks. 
 
Time reference t for velocities: t = 2^24 / fCLK 
Time reference ta² for accelerations: ta² = 2^41 / (fCLK)² 
  
