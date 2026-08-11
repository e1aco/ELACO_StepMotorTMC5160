# TMC5160A_Datasheet_Rev1.14 — 第17章 · p101

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
101 
 
 
 
www.trinamic.com 
Parameter 
Description 
Range 
Comment 
vhighfs 
& 
vhighchm 
These chopper configuration flags in CHOPCONF 
need to be set for DcStep operation. As soon as 
VDCMIN becomes exceeded, the chopper becomes 
switched to fullstepping. 
0 / 1 
set to 1 for DcStep 
TOFF 
DcStep often benefits from an increased off time 
value in CHOPCONF. Settings >2 should be 
preferred. 
2… 15 
Settings 8…15 do not make 
any difference to setting 8 
for DcStep operation. 
VDCMIN 
This is the lower threshold for DcStep operation 
when using internal ramp generator. Below this 
threshold, the motor operates in normal microstep 
mode. In DcStep operation, the motor operates at 
minimum VDCMIN, even when it is completely 
blocked. Tune together with DC_TIME setting. 
 
Activation of StealthChop also disables DcStep. 
0… 2^22 0: Disable DcStep 
Set to the lower velocity 
limit for DcStep operation. 
DC_TIME 
This setting controls the reference pulse width for 
DcStep load measurement. It must be optimized 
for robust operation with maximum motor torque. 
A higher value allows higher torque and higher 
velocity, a lower value allows operation down to 
a lower velocity as set by VDCMIN. 
 
Check best setting under nominal operation 
conditions, and re-check under extreme operating 
conditions (e.g. lowest operation supply voltage, 
highest motor temperature, and highest supply 
voltage, lowest motor temperature). 
0… 1023 Lower limit for the setting 
is: tBLANK (as defined by 
TBL) in clock cycles + n 
with n in the range 1 to 
100 (for a typical motor) 
DC_SG 
This setting controls stall detection in DcStep 
mode. Increase for higher sensitivity. 
 
A stall can be used as an error condition by 
issuing a hard stop for the motor. Enable sg_stop 
flag for stopping the motor upon a stall event. 
This way the motor will be stopped once it stalls. 
0… 255 
Set slightly higher than 
DC_TIME / 16 
17.5 Measuring Actual Motor Velocity in DcStep Operation 
DcStep has the ability to reduce motor velocity in case the motor becomes slower than the target 
velocity due to mechanical load. VACTUAL shows the ramp generator target velocity. It is not 
influenced by DcStep. Measuring DcStep velocity is possible based on the position counter XACTUAL.  
 
Therefore take two snapshots of the position counter with a known time difference: 
 
𝑉𝐴𝐶𝑇𝑈𝐴𝐿𝐷𝐶𝑆𝑇𝐸𝑃= 𝑋𝐴𝐶𝑇𝑈𝐴𝐿(𝑡𝑖𝑚𝑒2) −𝑋𝐴𝐶𝑇𝑈𝐴𝐿(𝑡𝑖𝑚𝑒1)
𝑡𝑖𝑚𝑒2 −𝑡𝑖𝑚𝑒1
∗224
𝑓𝐶𝐿𝐾
 
 
Example: 
At 16.0 MHz clock frequency, a 0.954 second measurement delay would directly yield in the 
velocity value, a 9.54 ms delay would yield in 1/100 of the actual DcStep velocity.  
 
To grasp the time interval as precisely as possible, snapshot a timer each time the transmission of 
XACTUAL from the IC starts or ends. The rising edge of NCS for SPI transmission provides the most 
exact time reference. 
 


<!-- detected tables -->

|  | Parameter |  |  | Description |  |  | Range |  |  | Comment |
|---|---|---|---|---|---|---|---|---|---|---|
| vhighfs & vhighchm | vhighfs |  | These chopper configuration flags in CHOPCONF need to be set for DcStep operation. As soon as VDCMIN becomes exceeded, the chopper becomes switched to fullstepping. |  |  | 0 / 1 |  |  | set to 1 for DcStep |  |
|  | & |  |  |  |  |  |  |  |  |  |
|  | vhighchm |  |  |  |  |  |  |  |  |  |
| TOFF |  |  | DcStep often benefits from an increased off time value in CHOPCONF. Settings >2 should be preferred. |  |  | 2… 15 |  |  | Settings 8…15 do not make any difference to setting 8 for DcStep operation. |  |
| VDCMIN |  |  | This is the lower threshold for DcStep operation when using internal ramp generator. Below this threshold, the motor operates in normal microstep mode. In DcStep operation, the motor operates at minimum VDCMIN, even when it is completely blocked. Tune together with DC TIME setting. _ Activation of StealthChop also disables DcStep. |  |  | 0… 2^22 |  |  | 0: Disable DcStep Set to the lower velocity limit for DcStep operation. |  |
| DC TIME _ |  |  | This setting controls the reference pulse width for DcStep load measurement. It must be optimized for robust operation with maximum motor torque. A higher value allows higher torque and higher velocity, a lower value allows operation down to a lower velocity as set by VDCMIN. Check best setting under nominal operation conditions, and re-check under extreme operating conditions (e.g. lowest operation supply voltage, highest motor temperature, and highest supply voltage, lowest motor temperature). |  |  | 0… 1023 |  |  | Lower limit for the setting is: t (as defined by BLANK TBL) in clock cycles + n with n in the range 1 to 100 (for a typical motor) |  |
| DC SG _ |  |  | This setting controls stall detection in DcStep mode. Increase for higher sensitivity. A stall can be used as an error condition by issuing a hard stop for the motor. Enable sg stop _ flag for stopping the motor upon a stall event. This way the motor will be stopped once it stalls. |  |  | 0… 255 |  |  | Set slightly higher than DC TIME / 16 _ |  |
