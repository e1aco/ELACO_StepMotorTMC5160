# TMC5160A_Datasheet_Rev1.14 — 第1章 · p9

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
9 
 
 
 
www.trinamic.com 
can be pre-configured via the interface. StealthChop2 allows high motor dynamics, by reacting at once 
to a change of motor velocity.  
For highest dynamic applications, SpreadCycle is an option to StealthChop2. It can be enabled via 
input pin (standalone mode) or via SPI or UART interface. StealthChop2 and SpreadCycle may even be 
used in a combined configuration for the best of both worlds: StealthChop2 for no-noise stand still, 
silent and smooth performance, SpreadCycle at higher velocity for high dynamics and highest peak 
velocity at low vibration.  
SpreadCycle is an advanced cycle-by-cycle chopper mode. It offers smooth operation and good 
resonance dampening over a wide range of speed and load. The SpreadCycle chopper scheme 
automatically integrates and tunes fast decay cycles to guarantee smooth zero crossing performance. 
Benefits of using StealthChop2: 
- 
Significantly improved microstepping with low cost motors 
- 
Motor runs smooth and quiet 
- 
Absolutely no standby noise 
- 
Reduced mechanical resonance yields improved torque 
1.7 StallGuard2 – Mechanical Load Sensing 
StallGuard2 provides an accurate measurement of the load on the motor. It can be used for stall 
detection as well as other uses at loads below those which stall the motor, such as CoolStep load-
adaptive current reduction. This gives more information on the drive allowing functions like 
sensorless homing and diagnostics of the drive mechanics.  
1.8 CoolStep – Load Adaptive Current Control 
CoolStep drives the motor at the optimum current. It uses the StallGuard2 load measurement 
information to adjust the motor current to the minimum amount required in the actual load situation. 
This saves energy and keeps the components cool. 
Benefits are: 
- 
Energy efficiency 
power consumption decreased up to 75% 
- 
Motor generates less heat 
improved mechanical precision 
- 
Less or no cooling 
improved reliability 
- 
Use of smaller motor 
less torque reserve required → cheaper motor does the job 
 
Figure 1.5 shows the efficiency gain of a 42mm stepper motor when using CoolStep compared to 
standard operation with 50% of torque reserve. CoolStep is enabled above 60RPM in the example. 
0
0,1
0,2
0,3
0,4
0,5
0,6
0,7
0,8
0,9
0
50
100
150
200
250
300
350
Efficiency
Velocity [RPM]
Efficiency with coolStep
Efficiency with 50% torque reserve
 
Figure 1.5 Energy efficiency with CoolStep (example) 

