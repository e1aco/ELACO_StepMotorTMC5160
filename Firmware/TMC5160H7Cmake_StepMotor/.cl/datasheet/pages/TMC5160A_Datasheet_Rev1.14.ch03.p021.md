# TMC5160A_Datasheet_Rev1.14 — 第3章 · p21

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  21 
 
 
 
www.trinamic.com 
BRIDGE OPTIMIZATION EXAMPLE 
A stepper driver for 6A of motor current has been designed using the MOSF ET AOD4126 in the 
standard schematic. 
The MOSFETs have a low gate capac itance and offer roughly 50ns slope time at the lowest driver 
strength setting. At lowest driver strength setting, switching quality is best  (Figure 3.6), but still 
shows a lot of ringing . Low side gate resistors have been added to slightly increase switching slope 
time following high-side bulk diode conduction by increasing the effect of Gate -Drain (Miller) charge. 
High side gate resistors have been added for s ymmetry. Tests show ed, that 1nF output capacitors 
dramatically reduce ringing of the power bridge following bulk diode conduction  (Figure 3.7). Figure 
3.8 shows the actual components and values after optimization. 
 
LS
GNDD
GNDA
DIE PAD
LS
BMA2
SRAH
50m, 
2512SRAL
LA1
LA2
HA1
HA2
BMA1
HS
HS
CA1
470n
CA2
470n +VM
4.7µF
10R 10R
10R
Coil 
out
47R
47R
1n, 
100V
1n, 
100V10R
4x AOD4126
 
Figure 3.8 Example for bridge with tuned components (see scope shots) 
 
BRIDGE LAYOUT CONSIDERATIONS 
- Tune the bridge layout for minimum loop inductivity. A compact layout is best.  
- Keep MOSFET gate connections short and straight and avoid loop inductivity between BM and 
corresponding HS driver pin. Loop inductance is minimized with parallel traces, or adjacent traces 
on adjacent layers. A wider trace reduces inductivity (don’t use minimum trace width). 
- Minimize the length of the sense resistor  connection to low-side MOSFET source , and place the 
TMC5160 near the sense resistor’s GND connection, with its GND connections directly connected to 
the same GND plane. 
- Optimize switching behavior by tuning gate current setting and gate resistors. Add MOSFET bridge 
output capacitors (470pF to a few nF) to reduce ringing. 
- Measure the performance of the bridge by probing BM pins directly at the bridge or at the 
TMC5160 using a short GND tip on the scope probe rather than a GND cable, if available. 
 
