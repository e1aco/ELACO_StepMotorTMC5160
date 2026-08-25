# TMC5160A_Datasheet_Rev1.14 — 第3章 · p17

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  17 
 
 
 
www.trinamic.com 
3.3 Choosing MOSFETs and Slope 
The selection of power MOSFETs depend s on a number of f actors, like package size,  on-resistance, 
voltage rating and supplier. It is not true, that larger, lower RDSon MOSFETs will always be better, as 
a larger device also has higher capacitances and may add more ringing in trace inductance and power 
dissipation in the gate drive circuitry. Adapt the MOSFET s to the required motor voltage (adding 5-10V 
of reserve to the peak supply voltage) and to the desired maximum current, in a way that resistive 
power dissipation still is low for the thermal capabilities of the chosen MOSFET package. The TMC5160 
drives the MOSFET gates with roughly 10V,  so normal, 10V  specified types are sufficient.  Logic level 
FETs (4.5V specified RDSon) will also work , but may be more critical with regard to bridge cross -
conduction due to lower VGS(th).  
 
The gate drive current and MOSFET gate resistors R G (optional) determine switching behavior and 
should basically be adapted to the MOSFET gate -drain charge (Miller charge ). Figure 3.3 shows the 
influence of the Mill er charge on the switching event . Figure 3.4 additionally shows the switching 
events in different load situations (load pulling the ou tput up or down), and the required bridge 
brake-before-make time.  
The following table shall ser ve as a thumb rule  for programming the MOSFET driver current 
(DRVSTRENGTH setting) and the selection of gate resistors: 
 
MOSFET MILLER CHARGE VS. DRVSTRENGTH AND RG 
Miller Charge 
[nC] (typ.) 
DRVSTRENGTH 
setting 
Value of RG [Ω] 
<10 0 ≤ 15 
10…20 0 or 1 ≤ 10 
20…40 1 or 2 ≤ 7.5 
40…60 2 or 3 ≤ 5 
>60 3 ≤ 2.7 
 
The TMC5160 provides increased gate -off drive current to avoid bridge cross -conduction induced by 
high dV/dt. This protection will be less efficient with gate resistors exceeding the values given in t he 
table. Therefore, for larger values of R G, a parallel  diode may be required to ensure keeping the 
MOSFET safely off during switching events. 
 
MOSFET gate charge vs. switching event
QG – Total gate charge (nC)
VGS – Gate to source voltage (V)
10
8
6
4
2
0
0 5 10 15 20 25
VDS – Drain to source voltage (V)
25
20
15
10
5
0
VM
QMILLER
 
Figure 3.3 Miller charge determines switching slope 
Hints 
- Choose modern MOSFETs with fast and soft recovery bulk diode and low reverse recovery charge.  
- A small, SMD MOSFET package allows compacter routing and reduces parasitic inductance effects.  
