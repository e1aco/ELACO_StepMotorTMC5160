# TMC5160A_Datasheet_Rev1.14 — 第17章 · p103

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  103 
 
 
 
www.trinamic.com 
+IMAX
-IMAX
0
STEP
DC_EN
DC_OUT
DCO signals that the driver is not ready for new steps. In this case, the controller does not react to this information.
Actual motor velocity
0
VDCMIN
dcStep enabled continuosly
VTARGET
Phase
Current
(one phase 
shown)
Theoretical sine 
wave 
corresponding to 
fullstep pattern
Steps from STEP input 
skipped by the driver due 
to light motor overload
LOSTSTEPS 0 2 4 8 12 16 20 22 24
LOSTSTEPS would count down if 
motion direction is negative
Light motor overload reduces 
effective motor velocity
 
Figure 17.3 Motor moving slower than STEP input due to light overload. LOSTSTEPS incremented 
 
17.6.2 DCO Interface to Motion Controller 
In STEP/DIR mode, DC EN enables DcStep. It is up to  the external motion controller to enable DcStep 
either, once a minimum step velocity is exceeded within the motion ramp , or to use the automatic 
threshold VDCMIN for DcStep enable.  
 
The STEP/DIR interface works in microstep resolution, even if the internal step execution is based on 
fullstep. This way, no switching to a different mode of operation is required within the moti on 
controller. The DcStep output DCO signals if the motor is ready for the next step based on the DcStep 
measurement of the motor. If the motor has not yet mechanically taken the last step, this step cannot 
be executed, and the driver stops automatically  before execution of the next fullstep . This situation is 
signaled by DCO. The external motion controller shall sto p step generation if DCOUT is low and wait 
until it becomes high again . Figure 17.5 shows this principle . The driver buffers steps during the 
waiting period up to the number of microstep setting minus one. In case, DCOUT does not go high 
within the lower step limit time e.g. due to a severe motor overload, a step can be enforced: override 
the stop status by a long STEP pulse with min. 1024 system clocks length. When using internal clock, 
a pulse length of minimum 125µs is recommended.  
 
µC or Motion 
Controller TMC5160
STEP
DCO
DIR
DCEN
DCIN
Optional axis 
synchronization
 
Figure 17.4 Full signal interconnection for DcStep 
 
