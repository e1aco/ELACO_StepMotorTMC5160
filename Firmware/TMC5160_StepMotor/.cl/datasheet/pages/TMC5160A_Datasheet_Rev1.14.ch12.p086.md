# TMC5160A_Datasheet_Rev1.14 — 第12章 · p86

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
86 
 
 
 
www.trinamic.com 
4. 
As soon as the switch is hit, the position becomes latched and the motor is stopped. Wait until 
the motor is in standstill again by polling the actual velocity VACTUAL or checking vzero or the 
standstill flag.  
5. 
Switch the ramp generator to hold mode and calculate the difference between the latched 
position and the actual position. For StallGuard based homing or when using hard stop, XACTUAL 
stops exactly at the home position, so there is no difference (0). 
6. 
Write the calculated difference into the actual position register. Now, homing is finished. A move 
to position 0 will bring back the motor exactly to the switching point. In case StallGuard was 
used for homing, read and write back RAMP_STAT to clear the StallGuard stop event event_stop_sg 
and release the motor from the stop condition.  
 
HOMING WITH A THIRD SWITCH 
Some applications use an additional home switch, which operates independently of the mechanical 
limit switches. The encoder functionality of the TMC5160 provides an additional source for position 
latching. It allows using the N channel input to snapshot XACTUAL with a rising or falling edge event, 
or both. This function also provides an interrupt output. 
 
1. 
Activate the latching function (ENCMODE: Set ignoreAB, clr_cont, neg_edge or pos_edge and 
latch_x_act). The latching function can then trigger the interrupt output (check by reading n_event 
in ENC_STATUS when interrupt is signaled at DIAG0). 
2. 
Move to the direction, where the N channel switch should be. In case the motor hits a stop 
switch (REFL or REFR) before the home switch is detected, reverse the motion direction. 
3. 
Read out XLATCH once the switch has been triggered. It gives the position of the switch event. 
4. 
After detection of the switch event, stop the motor, and subtract XLATCH from the actual position. 
Read and write back ENC_STAT to clear the status flags. (A detailed description of the required 
steps is in the homing procedure above.)  
 

