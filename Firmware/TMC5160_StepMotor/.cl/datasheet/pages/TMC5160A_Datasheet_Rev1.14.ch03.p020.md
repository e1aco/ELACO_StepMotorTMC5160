# TMC5160A_Datasheet_Rev1.14 — 第3章 · p20

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
20 
 
 
 
www.trinamic.com 
 
ENSURE RELIABLE OPERATION 
- 
Use SMD MOSFETs and short interconnections 
- 
Provide sufficient power filtering capacity close to the bridge and close to VS pin 
- 
Tune MOSFET switching slopes (measure switch-on event at MOSFET gate) to be slower than the 
MOSFET bulk diode reverse recovery time. This will reduce cross conduction.  
- 
Add optional gate resistors close to MOSFET gate and output capacitors to ensure clean switching 
and reliable operation by minimizing ringing. Figure 3.5  shows the options plus some variations. 
- 
Some MOSFETs eliminate reverse recovery charge by integrating a fast diode from source to drain. 
 
 
    
 
Figure 3.6 Ringing of output (blue) and Gate voltages (Yellow, Cyan) with untuned brige 
    
 
 
    
 
Figure 3.7 Switching event with optimized components (without / after bulk diode conduction) 
 

