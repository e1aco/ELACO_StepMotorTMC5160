# TMC5160A_Datasheet_Rev1.14 — 第17章 · p102

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
102 
 
 
 
www.trinamic.com 
17.6 DcStep with STEP/DIR Interface 
The TMC5160 provides two ways to use DcStep when interfaced to an external motion controller. The 
first way gives direct control of the DcStep step execution to the external motion controller, which 
must react to motor overload and is allowed to override a blocked motor situation. The second way 
assumes that the external motion controller cannot directly react to DcStep signals. The TMC5160 
automatically reduces the motor velocity or stops the motor upon overload. In order to allow the 
motion controller to react to the reduced real motor velocity in this mode, the counter LOST_STEPS 
gives the number of steps which have been commanded, but not taken by the motor controller. The 
motion controller can later on read out LOST_STEPS and drive any missing number of steps. In case of 
a blocked motor it tries moving it with the minimum velocity as programmed by VDCMIN. 
 
Enabling DcStep automatically sets the chopper to constant TOFF mode with slow decay only. This 
way, no re-configuration is required when switching from microstepping mode to DcStep and back.  
 
DcStep operation is controlled by three pins in STEP and DIR mode:  
 
- DCEN –  Forces the driver to DcStep operation if high. A velocity based activation of DcStep is 
controlled by TPWMTHRS when using StealthChop operation for low velocity settings. 
In this case, DcStep is disabled while in StealthChop mode, i.e. at velocities below the 
StealthChop switching velocity. 
- DCO – Informs the motion controller when motor is not ready to take a new step (low level). 
The motion controller shall react by delaying the next step until DCO becomes high. 
The sequencer can buffer up to the effective number of microsteps per fullstep to allow 
the motion controller to react to assertion of DCO. In case the motor is blocked this 
wait situation can be terminated after a timeout by providing a long > 1024 clock STEP 
input, or via the internal VDCMIN setting.  
- DCIN – Commands the driver to wait with step execution and to disable DCO. This input can be 
used for synchronization of multiple drivers operating with DcStep. 
 
17.6.1 Using LOST_STEPS for DcStep Operation 
This is the simplest possibility to integrate DcStep with an external motion controller: The external 
motion controller enables DcStep using DCEN or the internal velocity threshold. The TMC5160 tries to 
follow the steps. In case it needs to slow down the motor, it counts the difference between incoming 
steps on the STEP signal and steps going to the motor. The motion controller can read out the 
difference and compensate for the difference after the motion or on a cyclic basis. Figure 17.3 shows 
the principle (simplified). 
 
In case the motor driver needs to postpone steps due to detection of a mechanical overload in 
DcStep, and the motion controller does not react to this by pausing the step generation, LOST_STEPS 
becomes incremented or decremented (depending on the direction set by DIR) with each step which 
is not taken. This way, the number of lost steps can be read out and executed later on or be 
appended to the motion. As the driver needs to slow down the motor while the overload situation 
persists, the application will benefit from a high microstepping resolution, because it allows more 
seamless acceleration or deceleration in DcStep operation. In case the application is completely 
blocked, VDCMIN sets a lower limit to the step execution. If the motor velocity falls below this limit, 
however an unknown number of steps is lost and the motor position is not exactly known any more. 
DCIN allows for step synchronization of two drivers: it stops the execution of steps if low and sets 
DCO low. 
 

