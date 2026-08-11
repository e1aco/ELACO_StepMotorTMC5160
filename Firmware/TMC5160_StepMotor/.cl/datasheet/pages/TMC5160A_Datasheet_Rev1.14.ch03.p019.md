# TMC5160A_Datasheet_Rev1.14 — 第3章 · p19

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
19 
 
 
 
www.trinamic.com 
3.4 Tuning the MOSFET Bridge 
A clean switching event is favorable to ensure low power dissipation and good EMC behavior. 
Unsuitable layout or components endanger stable operation of the circuit. Therefore, it is important to 
understand the effect of parasitic trace inductivity and MOSFET reverse recovery. 
 
Stray inductance in power routing will cause ringing whenever the opposite MOSFET is in diode 
conduction prior to switching on a low-side or high-side MOSFET. Diode conduction occurs during 
break-before make time whenever the load current is inverse to the following bridge polarity. The 
MOSFET bulk diode has a certain, type specific reverse recovery time and charge. This time typically is 
in the range of a few 10ns. During reverse recovery time, the bulk diode will cause high current flow 
across the bridge. This current is taken from the power supply filter capacitors (see thick lines Figure 
3.5). Once the diode opens parasitic inductance tries to keep the current flowing. A high, fast slope 
results and leads to ringing in all parasitic inductivities (see Figure 3.6). This may lead to bridge 
voltage undershooting the GND level as well as fast pulses on VS and all MOSFET connections. It 
must be ensured, that the driver IC does not see spikes on its BM pins to GND going below -5V. 
Severe VS ripple might overload the charge-pump circuitry. Measure the voltage directly at the driver 
pins to driver GND. The amount of undershooting depends on energy stored in parasitic inductivities 
from low side drain to low side source and via the sense resistor RS to GND.  
 
When using relatively small MOSFETs, a soft slope control requires a high gate series resistance. This 
endangers safe MOSFET switch off. Add additional diodes to ensure safe MOSFET off conditions with 
slow switch-on slopes (shown for right MOSFET pair in Figure 3.5). 
 
Figure 3.7 shows performance of the basic circuit after adapting switching slope and adding 1nF 
bridge output capacitors.  
 
LS
GNDD
GNDA
DIE PAD
LS
BMA2
SRAH
Capacitor reduces 
ringing on sense resistor.
RS
SRAL
LA1
LA2
HA1
HA2
BMA1
HS
HS
CA1
CB
CA2
CB
+VM
RG
RG
RG
RG
Coil 
out
47R
47R
RG 
RG 
Decide use and value of the additional components based on measurements of the actual circuit using the final layout!
100n
1n, 
100V
1n, 
100V
2n2
RC-Filter protects SRAH / 
SRAL and reduces spikes 
seen by the chopper
RG: Reduce slope and protect the driver against ringing in the 
interconnections between MOSFET and driver
VS
220nF
1R
Optional RC filter 
against VS ringing
4.7µF
LOW-
ESR
Additional 1A type Schottky Diodes (selected for full VM range) in combination with RG        to 1.0 Ohm) eliminate 
undershooting of BM in case of high parasitic layout inductivity, e.g. with long interconnections to MOSFETs.
470pF to a few nF output 
capacitors close to bridge 
and / or output reduce 
ringing and improve EMC
Filter capacitors placed near bridge
Optional gate diodes in combination 
with very high value of RG
 
Figure 3.5 Bridge protection options for power routing inductivity 
 
 


<!-- detected tables -->

|  | 1R 220nF Optional RC filter against VS ringing CB CA2 HA2 |
|---|---|
|  |  |
|  |  |

| BMA1 |  |  | RG |  |  |
|---|---|---|---|---|---|
| BMA2 |  |  | RG |  |  |
| LA1 |  | RG |  |  |  |
| LA2 SRAH |  |  |  |  |  |
|  |  |  |  |  |  |
|  |  | 47R 2n2 |  |  |  |
| SRAL |  |  |  |  |  |
