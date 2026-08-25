# TMC5160A_Datasheet_Rev1.14 — 第3章 · p16

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  16 
 
 
 
www.trinamic.com 
 
Attention 
In case VSA is supplied by a different voltage source, mak e sure that VSA does not drop out during 
motor operation. The motor driver should be disabled in case VSA becomes switched off before VS. 
Hard switching edges on VSA might result in bridge cross -conduction otherwise. It is safest to derive 
VSA voltage from VS supply. 
3.2 External Gate Voltage Regulator 
At high suppl y voltages  like 48V , the internal gate voltage regulator and the internal 5V regulator 
have considerable power dissipation , especially with high MOSFET gate charges, high chopper 
frequency or high system clock frequency >12MHz . A good thermal coupling of t he heat slug to the 
system PCB GND plane is required to dissipate heat. Still, the thermal thresholds will be lowered 
significantly by self-heating. To reduce power dissipation, supply an external gate driver voltage to the 
TMC5160. Figure 3.2 shows the r equired connection.  The internal gate voltage regulator becomes 
disabled in this constellation. 12V +/-1V are recommended for best results.  
 
5V Voltage 
regulator
+VG
5VOUT
VSA
2.2µ
VCC
2.2µ
12V Gate Voltage
2R2
470n
11.5V Voltage 
regulator
12VOUT
 
Figure 3.2 External gate voltage supply 
 
Hint 
With MOSFETs above 50nC of total gate charge, chopper frequency >40kHz , or at clock frequency 
>12MHz, it is recommended to use a VSA supply not higher than 40V.  
 
  
