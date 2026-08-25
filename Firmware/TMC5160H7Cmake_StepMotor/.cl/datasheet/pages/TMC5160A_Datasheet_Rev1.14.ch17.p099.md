# TMC5160A_Datasheet_Rev1.14 — 第17章 · p99

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  99 
 
 
 
www.trinamic.com 
17 DcStep 
DcStep is an automatic commutation mode for the stepper motor. It allows the stepper to run with 
its target velocity as commanded by the ramp generator as long as it can cope with the load. In case 
the motor becomes overloaded, it slows down to a velocity, where  the motor can still drive the load. 
This way, the stepper motor never stalls and can drive heavy loads as fast as possible. Its higher 
torque available at lower velocity, plus dynamic torque from its flywheel mass allow compensating 
for mechanical torque peaks. In case the motor becomes completely blocked, the stall flag becomes 
set. 
17.1 User Benefits 
 
  
 
 
 
 
17.2 Designing-In DcStep 
In a classical application, the operation area is limited by the maximum torque required at maximum 
application velocity. A safety margin of up to 50% torque is required, in order to compensate for 
unforeseen load peaks, torque loss due to resonance and ag ing of mechanical components. DcStep 
allows using up to the full available motor  torque. Even higher short time dynamic loads can be 
overcome using motor and application flywheel mass without the danger of a motor stall. With 
DcStep the nominal application  load can be extended to a higher torque only limited by the safety 
margin near the holding torque area (which is the highest torque the motor can provide). 
Additionally, maximum application velocity can be increased up to the actually reachable motor 
velocity. 
 
Classic operation area
with safety margin
torque
velocity [RPM]
dcStep operation - no step loss can occur
additional flywheel mass torque reserve
microstep 
operation
0
MNOM1
MMAX
VDCMIN
VMAX
MNOM: Nominal torque required by application
MMAX: Motor pull-out torque at v=0
application area
max. motor torquesafety margin
dcStep extended
Safety margin: Classical application operation area is limited by a certain 
percentage of motor pull-out torque
MNOM2
 
Figure 17.1 DcStep extended application operation area 
 
Quick Start 
For a quick start, see the Quick Configuration Guide in chapter 22. 
For detail configuration procedure see Application Note AN003 - DcStep 
  
Motor – never loses steps 
Application – works as fast as possible 
Acceleration – automatically as high as possible 
Energy efficiency – highest at speed limit 
Cheaper motor – does the job! 
