# TMC5160A_Datasheet_Rev1.14 — 第8章 · p70

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
70 
 
 
 
www.trinamic.com 
ability of the chopper to follow a changing motor current. Further the duration of the on phase and 
the fast decay must be longer than the blanking time, because the current comparator is disabled 
during blanking.  
 
It is easiest to find the best setting by starting from a low hysteresis setting (e.g. HSTRT=0, HEND=0) 
and increasing HSTRT, until the motor runs smoothly at low velocity settings. This can best be 
checked when measuring the motor current either with a current probe or by probing the sense 
resistor voltages (see Figure 8.2). Checking the sine wave shape near zero transition will show a small 
ledge between both half waves in case the hysteresis setting is too small. At medium velocities (i.e. 
100 to 400 fullsteps per second), a too low hysteresis setting will lead to increased humming and 
vibration of the motor.  
 
 
Figure 8.2 No ledges in current wave with sufficient hysteresis (magenta: current A, yellow & 
blue: sense resistor voltages A and B) 
A too high hysteresis setting will lead to reduced chopper frequency and increased chopper noise but 
will not yield any benefit for the wave shape. 
 
Quick Start 
For a quick start, see the Quick Configuration Guide in chapter 22. 
For detail procedure see Application Note AN001 - Parameterization of SpreadCycle 
 
As experiments show, the setting is quite independent of the motor, because higher current motors 
typically also have a lower coil resistance. Therefore choosing a low to medium default value for the 
hysteresis (for example, effective hysteresis = 4) normally fits most applications. The setting can be 
optimized by experimenting with the motor: A too low setting will result in reduced microstep 
accuracy, while a too high setting will lead to more chopper noise and motor power dissipation. 
When measuring the sense resistor voltage in motor standstill at a medium coil current with an 
oscilloscope, a too low setting shows a fast decay phase not longer than the blanking time. When 
the fast decay time becomes slightly longer than the blanking time, the setting is optimum. You can 
reduce the off-time setting, if this is hard to reach. 
 
The hysteresis principle could in some cases lead to the chopper frequency becoming too low, e.g. 
when the coil resistance is high when compared to the supply voltage. This is avoided by splitting 
the hysteresis setting into a start setting (HSTRT+HEND) and an end setting (HEND). An automatic 
hysteresis decrementer (HDEC) interpolates between both settings, by decrementing the hysteresis 
value stepwise each 16 system clocks. At the beginning of each chopper cycle, the hysteresis begins 
with a value which is the sum of the start and the end values (HSTRT+HEND), and decrements during 
the cycle, until either the chopper cycle ends or the hysteresis end value (HEND) is reached. This way, 

