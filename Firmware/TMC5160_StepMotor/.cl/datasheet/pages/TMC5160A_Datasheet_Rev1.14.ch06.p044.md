# TMC5160A_Datasheet_Rev1.14 — 第6章 · p44

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
44 
 
 
 
www.trinamic.com 
6.3.2.2 RAMP_STAT – Ramp & Reference Switch Status Register 
0X35: RAMP_STAT – RAMP AND REFERENCE SWITCH STATUS REGISTER 
R/W 
Bit 
Name 
Comment 
R 
13 
status_sg 
1: Signals an active StallGuard2 input from the CoolStep driver or 
from the DcStep unit, if enabled. 
  
Hint: When polling this flag, stall events may be missed – activate 
sg_stop to be sure not to miss the stall event. 
R+ 
WC 
12 
second_move 
1: Signals that the automatic ramp required moving back in the 
opposite direction, e.g. due to on-the-fly parameter change 
(Write ‘1’ to clear) 
R 
11 
t_zerowait_ 
active 
1: Signals, that TZEROWAIT is active after a motor stop. During this 
time, the motor is in standstill. 
R 
10 
vzero 
1: Signals, that the actual velocity is 0. 
R 
9 
position_ 
reached 
1: Signals, that the target position is reached.  
This flag becomes set while XACTUAL and XTARGET match. 
R 
8 
velocity_ 
reached 
1: Signals, that the target velocity is reached.  
This flag becomes set while VACTUAL and VMAX match. 
R+ 
WC 
7 
event_pos_ 
reached 
1: 
Signals, 
that 
the 
target 
position 
has 
been 
reached 
(position_reached becoming active). 
(Write ‘1’ to clear flag and interrupt condition) 
This bit is ORed to the interrupt output signal. 
R+ 
WC 
6 
event_stop_ 
sg 
1: Signals an active StallGuard2 stop event. 
Resetting the register will clear the stall condition and the motor 
may re-start motion, unless the motion controller has been stopped. 
(Write ‘1’ to clear flag and interrupt condition) 
This bit is ORed to the interrupt output signal. 
R 
5 
event_stop_r 
1: Signals an active stop right condition due to stop switch.  
The stop condition and the interrupt condition can be removed by 
setting RAMP_MODE to hold mode or by commanding a move to the 
opposite direction. In soft_stop mode, the condition will remain 
active until the motor has stopped motion into the direction of the 
stop switch. Disabling the stop switch or the stop function also 
clears the flag, but the motor will continue motion. 
This bit is ORed to the interrupt output signal. 
4 
event_stop_l 
1: Signals an active stop left condition due to stop switch. 
The stop condition and the interrupt condition can be removed by 
setting RAMP_MODE to hold mode or by commanding a move to the 
opposite direction. In soft_stop mode, the condition will remain 
active until the motor has stopped motion into the direction of the 
stop switch. Disabling the stop switch or the stop function also 
clears the flag, but the motor will continue motion. 
This bit is ORed to the interrupt output signal. 
R+ 
WC 
3 
status_latch_r 
1: Latch right ready  
(enable position latching using SW_MODE settings 
latch_r_active or latch_r_inactive)  
(Write ‘1’ to clear) 
2 
status_latch_l 
1: Latch left ready  
(enable position latching using SW_MODE settings 
latch_l_active or latch_l_inactive)  
(Write ‘1’ to clear) 
R 
1 
status_stop_r 
Reference switch right status (1=active) 
0 
status_stop_l 
Reference switch left status (1=active) 
 
 
 


<!-- detected tables -->

|  | 0X35: RAMP STAT – RAMP AND REFERENCE SWITCH STATUS REGISTER _ |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  | R/W |  |  | Bit |  |  | Name |  |  | Comment |  |
| R |  |  | 13 |  |  | status sg _ |  |  | 1: Signals an active StallGuard2 input from the CoolStep driver or from the DcStep unit, if enabled. Hint: When polling this flag, stall events may be missed – activate sg stop to be sure not to miss the stall event. |  |  |
| R+ WC |  |  | 12 |  |  | second move _ |  |  | _ 1: Signals that the automatic ramp required moving back in the opposite direction, e.g. due to on-the-fly parameter change (Write ‘1’ to clear) |  |  |
| R |  |  | 11 |  |  | t zerowait _ _ active |  |  | 1: Signals, that TZEROWAIT is active after a motor stop. During this time, the motor is in standstill. |  |  |
| R |  |  |  | 10 |  | vzero |  |  | 1: Signals, that the actual velocity is 0. |  |  |
| R |  |  | 9 | 9 |  | position _ reached |  |  | 1: Signals, that the target position is reached. This flag becomes set while XACTUAL and XTARGET match. |  |  |
| R |  |  | 8 |  |  | velocity _ reached |  |  | 1: Signals, that the target velocity is reached. This flag becomes set while VACTUAL and VMAX match. |  |  |
| R+ WC |  |  | 7 |  |  | event pos _ _ reached |  |  | 1: Signals, that the target position has been reached (position reached becoming active). _ (Write ‘1’ to clear flag and interrupt condition) This bit is ORed to the interrupt output signal. |  |  |
| R+ WC |  |  | 6 |  |  | event stop _ _ sg |  |  | 1: Signals an active StallGuard2 stop event. Resetting the register will clear the stall condition and the motor may re-start motion, unless the motion controller has been stopped. (Write ‘1’ to clear flag and interrupt condition) This bit is ORed to the interrupt output signal. |  |  |
| R |  |  | 5 |  |  | event stop r _ _ |  |  | 1: Signals an active stop right condition due to stop switch. The stop condition and the interrupt condition can be removed by setting RAMP MODE to hold mode or by commanding a move to the _ opposite direction. In soft stop mode, the condition will remain _ active until the motor has stopped motion into the direction of the stop switch. Disabling the stop switch or the stop function also clears the flag, but the motor will continue motion. This bit is ORed to the interrupt output signal. |  |  |
|  |  |  | 4 |  |  | event stop l _ _ |  |  | 1: Signals an active stop left condition due to stop switch. The stop condition and the interrupt condition can be removed by setting RAMP MODE to hold mode or by commanding a move to the _ opposite direction. In soft stop mode, the condition will remain _ active until the motor has stopped motion into the direction of the stop switch. Disabling the stop switch or the stop function also clears the flag, but the motor will continue motion. This bit is ORed to the interrupt output signal. |  |  |
| R+ WC |  |  | 3 |  |  | status latch r _ _ |  |  | 1: Latch right ready (enable position latching using SW MODE settings _ latch r active or latch r inactive) _ _ _ _ (Write ‘1’ to clear) |  |  |
|  |  |  | 2 |  |  | status latch l _ _ |  |  | 1: Latch left ready (enable position latching using SW MODE settings _ latch l active or latch l inactive) __ __ (Write ‘1’ to clear) |  |  |
| R |  |  |  | 1 |  | status stop r |  |  | Reference switch right status (1=active) |  |  |
|  |  |  |  | 0 |  | _ _ status stop l |  |  | Reference switch left status (1=active) |  |  |
