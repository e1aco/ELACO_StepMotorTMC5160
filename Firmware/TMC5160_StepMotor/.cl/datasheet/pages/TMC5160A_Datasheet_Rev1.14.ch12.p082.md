# TMC5160A_Datasheet_Rev1.14 — 第12章 · p82

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
82 
 
 
 
www.trinamic.com 
12.2 Motion Profiles 
For the ramp generator register set, please refer to the chapter 6.3. 
 
12.2.1 Ramp Mode 
The ramp generator delivers two phase acceleration and two phase deceleration ramps with 
additional programmable start and stop velocities (see Figure 12.1).  
 
 
 
 
 
 
 
The two different sets of acceleration and deceleration can be combined freely. A common transition 
speed V1 allows for velocity dependent switching between both acceleration and deceleration 
settings. A typical use case will use lower acceleration and deceleration values at higher velocities, as 
the motors torque declines at higher velocity. When considering friction in the system, it becomes 
clear, that typically deceleration of the system is quicker than acceleration. Thus, deceleration values 
can be higher in many applications. This way, operation speed of the motor in time critical 
applications can be maximized.  
As target positions and ramp parameters may be changed any time during the motion, the motion 
controller will always use the optimum (fastest) way to reach the target, while sticking to the 
constraints set by the user. This way it might happen, that the motion becomes automatically 
stopped, crosses zero and drives back again. This case is flagged by the special flag second_move. 
 
12.2.2 Start and Stop Velocity 
When using increased levels of start- and stop velocity, it becomes clear, that a subsequent move into 
the opposite direction would provide a jerk identical to VSTART+VSTOP, rather than only VSTART. As 
the motor probably is not able to follow this, you can set a time delay for a subsequent move by 
setting TZEROWAIT. An active delay time is flagged by the flag t_zerowait_active. Once the target 
position is reached, the flag position_reached becomes active. 
 
v
t
acceleration phase
deceleration phase
motor 
stop
VSTOP
VSTART
0
V1
VMAX
AMAX
DMAX
D1
A1
-A1
TZEROWAIT
acceleration 
phase
VACTUAL
 
Figure 12.1 Ramp generator velocity trace showing consequent move in negative direction 
 
Note 
The start velocity can be set to zero, if not used.  
The stop velocity can be set to ten (or down to one), if not used.  
Take care to set VSTOP identical to or above VSTART. This ensures that even a short motion can 
be terminated successfully at the target position.  


<!-- detected tables -->

| motor stop | acceleration phase | deceleration phase |  | acceleration phase t -A1 |
|---|---|---|---|---|
|  | A M A X | X A M D |  |  |
|  | A1 | D1 |  |  |
|  |  |  |  |  |
|  |  |  |  |  |
| TZEROWAIT VACTUAL |  |  |  |  |
