# TMC5160A_Datasheet_Rev1.14 — 第18章 18 Sine-Wave Look-up Table

--- [PAGE 105] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  105 
 
 
 
www.trinamic.com 
18 Sine-Wave Look-up Table 
The TMC5160 driver provides a programmable look-up table for storing the microstep current wave. As 
a default, the table  is pre-programmed with a sine wave, which is a good starting point for most 
stepper motors. Reprogramming the table to a motor specific wave allows drastically improved 
microstepping especially with low-cost motors. 
18.1 User Benefits 
 
 
 
 
18.2 Microstep Table 
In order to minimize required memory and the amount of data to be programmed, only a quarter of 
the wave becomes stored. The internal microstep table maps the microstep wave from 0° to 90° . It 
becomes symmetrically extended to 360°. When reading out the ta ble the 10-bit microstep counter  
MSCNT addresses the fully e xtended wave table . The table is stored in an incremental fashion, using 
each one bit per entry. Therefore only 256 bits (ofs00 to ofs255) are required to store the quarter 
wave. These bits are ma pped to eight 32 bit registers. Each ofs bit controls the ad dition of an 
inclination Wx or Wx+1 when advancing one step in the table . When Wx is 0, a 1 bit in the table at 
the actual microstep position means “add one” when advancing to the next microstep. As the wave 
can have a higher inclination than 1, the base i nclinations Wx can be programmed to -1, 0, 1, or 2 
using up to four flexible programmable segments within the quarter wave. This way even negative 
inclination can be realized. The four inclination  segments are controlled by the position registers X1 
to X3. Inclination segment 0 goes from microstep position 0 to X1-1 and its base inclination is 
controlled by W0, segment 1 goes from X1 to X2-1 with its base inclination controlled by W1, etc.  
 
When modifying the wave, care must be taken to ensure a smooth and symmetrical zero transition 
when the quarter wave becomes expanded to a full wave. The maximum resulting swing of the wave 
should be adjusted to a range of -248 to 248, in order to give the best possible  resolution while 
leaving headroom for the hysteresis based chopper to add an offset.  
 
MSCNT
y
256
256
248
-248
512 768 00 X1 X3X2
W0: +2/+3
W1: +1/+2
W2: +0/+1
W3: -1/+0
LUT stores 
entries 0 to 255
255
START_SIN
START_SIN90
 
Figure 18.1 LUT programming example 
  
Microstepping – extremely improved with low cost motors 
Motor – runs smooth and quiet 
Torque – reduced mechanical resonances yields improved torque 
