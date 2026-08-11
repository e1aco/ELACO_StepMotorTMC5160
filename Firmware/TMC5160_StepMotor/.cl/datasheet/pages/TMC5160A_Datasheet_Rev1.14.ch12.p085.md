# TMC5160A_Datasheet_Rev1.14 — 第12章 · p85

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
85 
 
 
 
www.trinamic.com 
12.4 Reference Switches 
Prior to normal operation of the drive an absolute reference position must be set. The reference 
position can be found using a mechanical stop which can be detected by stall detection, or by a 
reference switch.  
In case of a linear drive, the mechanical motion range must not be left. This can be ensured also for 
abnormal situations by enabling the stop switch functions for the left and the right reference switch. 
Therefore, the ramp generator responds to a number of stop events as configured in the SW_MODE 
register. There are two ways to stop the motor: 
- 
It can be stopped abruptly, when a switch is hit. This is useful in an emergency case and for 
StallGuard based homing. 
- 
Or the motor can be softly decelerated to zero using deceleration settings (DMAX, V1, D1).  
 
Hint 
Latching of the ramp position XACTUAL to the holding register XLATCH upon a switch event gives a 
precise snapshot of the position of the reference switch. 
 
+VCC_IO
REFL
Traveler
Motor
+VCC_IO
REFR
Negative 
direction
Positive 
direction
10k
10k
22k
1nF
Optional RC filter 
(example)
 
Figure 12.4 Using reference switches (example) 
Normally open or normally closed switches can be used by programming the switch polarity or 
selecting the pullup or pull-down resistor configuration. A normally closed switch is failsafe with 
respect to an interrupt of the switch connection. Switches which can be used are: 
- 
mechanical switches,  
- 
photo interrupters, or  
- 
hall sensors.  
 
Be careful to select reference switch resistors matching your switch requirements!  
In case of long cables additional RC filtering might be required near the TMC5160 reference inputs. 
Adding an RC filter will also reduce the danger of destroying the logic level inputs by wiring faults, 
but it will add a certain delay which should be considered with respect to the application.  
 
IMPLEMENTING A HOMING PROCEDURE 
1. 
Make sure, that the home switch is not pressed, e.g. by moving away from the switch.  
2. 
Activate position latching upon the desired switch event and activate motor (soft) stop upon 
active switch. StallGuard based homing requires using a hard stop (en_softstop=0). 
3. 
Start a motion ramp into the direction of the switch. (Move to a more negative position for a left 
switch, to a more positive position for a right switch). You may timeout this motion by using a 
position ramping command. 

