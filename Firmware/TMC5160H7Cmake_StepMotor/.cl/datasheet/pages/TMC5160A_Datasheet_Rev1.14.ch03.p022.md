# TMC5160A_Datasheet_Rev1.14 — 第3章 · p22

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  22 
 
 
 
www.trinamic.com 
3.5  Higher Voltage Applications 
Some applications require higher voltage tolerance, than the TMC5160 can directly support. For peak 
voltages above 60V , use an external gate driver IC  boosting the TMC5160 gate driver outputs . Figure 
3.9 shows a sample circuit . It  uses one external gate-driver IC for each half -bridge, to boost the 
TMC5160 outputs. BBM control still is done by TMC5160 . These ICs are 12V tolerant, so the TMC51 60 
output signals can be directly used for driving  their control inputs. The BM pins however need to be 
kept near GND, in order to yield a GND -related high side control signal. By attaching BM to the 
respective sense resistor, the short to VS protection st ill can react to overcurrent conditions. Limit 
short detection voltage drop to 0.5V…0.8V to avoid high side outputs to reach a too high level. High -
side short protection has to be disabled u sing CHOPCONF.diss2g, as it cannot work in this circuit 
configuration.  
Keep layout and all interconnections compact, in order to avoid disturbance by parasitic effects. Also 
consult application notes for the selected gate driver ICs.  
 
47R
47R
One bridge shown
5V Voltage 
regulator
charge pump
22n
100V
100n 
16V
+12V
5VOUT
VSA
2.2µ
VCC
100n
stepper
motor
N
S
Chopper
2.2u
CE
8-14V for gate driving
2R2
470n
B.Dwersteg, © 
TRINAMIC 2014
LS
LS
BMB2
SRBH
RS
SRBL
LB1
LB2
HB1
HB2
BMB1
HS
HS
CB1
CB2
+VM
CPI
CPO
VCP
VS
11.5V Voltage 
regulator
12VOUT
2.2µ
470n
Keep inductivity of the fat 
interconnections as small 
as possible!
RG
RG
Motor voltage that exceeds 
drive capabilities of TMC5160, 
e.g. 60V-100V
12V level gate 
control signals
1n-2.2n
Low-Side over-
current sensing @ Rs
Gate drive shown for 
one half bridge
LM5109 
gate 
driver
HI
LI
HO
LO
VDD
VSS
100n
1µ
HS
HB
22n
22k
12V
Charge pump for high 
dutycycle support
 
Figure 3.9 External Gate Driver Example 
  
