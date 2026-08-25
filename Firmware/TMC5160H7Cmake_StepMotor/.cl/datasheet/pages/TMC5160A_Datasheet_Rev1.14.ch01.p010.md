# TMC5160A_Datasheet_Rev1.14 — 第1章 · p10

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  10 
 
 
 
www.trinamic.com 
1.9 DcStep – Load Dependent Speed Control 
DcStep allows the motor to run near its load limit and at its velocity limit without losing a step. If 
the mechanical load on the motor increases to the stalling load , the motor automatically decreases 
velocity so that it can still drive the load. With this feat ure, the motor will never stall. In addition to 
the increased torque at a lower velocity, dynamic inertia will allow the motor to overcome mechanical 
overloads by decel erating. DcStep directly integrates with the ramp generator, so that the target 
position will be reached, even if the motor velocity needs to be decreased due to increased 
mechanical load. A dynamic range of up to factor 10 or more can be covered by DcStep without any 
step loss. By optimizing the motion velocity in high load situations, this feature further enhances 
overall system efficiency. 
 
Benefits are: 
- Motor does not loose steps in overload conditions 
- Application works as fast as possible 
- Highest possible acceleration automatically 
- Highest energy efficiency at speed limit 
- Highest possible motor torque using fullstep drive 
- Cheaper motor does the job 
 
1.10 Encoder Interface 
The TMC5160 provides an encoder interface for external in cremental encoders. The encode r provides 
automatic checking for step loss and can be used for homing of the motion controller (alternatively to 
reference switches). A programmable prescaler allows the adaptation of the encoder resolution to the 
motor resolution. A 32 bit encoder counter is provided. 
  
