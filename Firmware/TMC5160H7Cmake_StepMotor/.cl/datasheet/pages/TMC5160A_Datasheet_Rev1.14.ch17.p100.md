# TMC5160A_Datasheet_Rev1.14 — 第17章 · p100

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  100 
 
 
 
www.trinamic.com 
17.3 DcStep Integration with the Motion Controller 
DcStep requires only a few settings. It directly feeds back motor motion to the ramp generator, so 
that it becomes seamlessly integrated into the motion ramp, even if the motor becomes overloaded 
with respect to the target velocity. DcStep operates the motor in fullstep mode at the ramp generator 
target velocity VACTUAL or at reduced velocity if the motor becomes overloaded. It requires settin g 
the minimum operation velocity VDCMIN. VDCMIN shall be set to the lowest operating  velocity where 
DcStep gives a reliable detection of motor operation. The motor never stalls unless it becomes braked 
to a velocity below VDCMIN. In case the velocity should fall below this value, the motor would restart 
once its load is released, unless t he stall detection becomes enabled (se t sg_stop). Stall detection is 
covered by StallGuard2. 
 
v
t
dcStep active
VDCMIN
0
V1
VMAX
AMAX DMAX
D1A1
Nominal ramp profile Ramp profile with torque overload and same target position
overload
 
Figure 17.2 Velocity profile with impact by overload situation 
 
Hint 
DcStep requires that the phase polarity of the sine wave is positive within the MSCNT range 768 to 
255 and negative within 256 to 767. The cosine polarity must be positive from 0 to 511 and negative 
from 512 to 1023. A phase shift by 1 would disturb DcStep operation. Therefore it is advised to work 
with the default wave. Please refer chapter 18.2 for an initialization with the default table. 
17.4 Stall Detection in DcStep Mode 
While DcStep is able to decelerate the motor upon overload, it cannot avo id a stall in every operation 
situation. Once the motor is blocked, or it becomes decelerated below a motor dependent minimum 
velocity where the motor operation cannot safely be detec ted any more, the motor may stall and 
loose steps. In order to safely det ect a step loss and avoid restarting of the motor, the stop on stall 
can be enabled (set flag sg_stop). In this case VACTUAL becomes set to zero once the motor is stalled. 
It remains stopped until reading the RAMP_STAT status flags. The flag event_stop_sg shows the active 
stop condition.  A StallGuard2 load value also is  available during DcStep operation. The range of 
values is limited to 0 to 255, in certain situations up to 511 will b e read out . In order to enable 
StallGuard, also set TCOOLTHRS corresponding to a velocity slightly above VDCMIN or up to VMAX. 
 
Stall detection in this mode may trigger falsely due to resonances, when flywheel loads are loosely 
coupled to the motor axis. 
