# TMC5160A_Datasheet_Rev1.14 — 第5章 · p29

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
29 
 
 
 
www.trinamic.com 
5.4 Addressing Multiple Slaves 
ADDRESSING ONE OR TWO SLAVES 
If only one or two TMC5160 are addressed by a master using a single UART interface, a hardware 
address selection can be done by setting the NAI pins of both devices to different levels.  
ADDRESSING UP TO 255 SLAVES 
A different approach can address any number of devices by using the input NAI as a selection pin. 
Addressing up to 255 units is possible.  
 
Master CPU 
(µC with UART, 
software 
switches TXD to 
hi-Z for 
receiving)
TMC5160
#1
NAI
NAO
SWIOP
SWION
TMC5160
#2
NAI
SWIOP
SWION
NAO
TMC5160
#3
NAI
SWIOP
SWION
TXD
address 0, NAO is high
address 1
address 1
program to address 254 & set NAO low
address 0, NAO is high
address 1
address 254
program to address 253 & set NAO low
address 0
address 254
address 253
program to address 252 & set NAO low
RIDLE
+VIO
RIDLE forces stop bit level in idle conditions, 
3k3 is sufficient with 14 slaves
RXD
Addressing phase 1:
Addressing phase 2:
Addressing phase 3:
Addressing phase 4:
EXAMPLE FOR ADDRESSING UP TO 255 TMC5160
Addressing phase X:
continue procedure 
 
Figure 5.1 Addressing multiple TMC5160 via single wire interface using chaining 
PROCEED AS FOLLOWS: 
- 
Tie the NAI pin of your first TMC5160 to GND.  
- 
Interconnect NAO output of the first TMC5160 to the next drivers NAI pin. Connect further 
drivers in the same fashion.  
- 
Now, the first driver responds to address 0. Following drivers are set to address 1.  
- 
Program the first driver to its dedicated slave address. Note: once a driver is initialized with 
its slave address, its NAO output, which is tied to the next drivers NAI has to be programmed 
to logic 0 in order to differentiate the next driver from all following devices.  
- 
Now, the second driver is accessible and can get its slave address. Further units can be 
programmed to their slave addresses sequentially.  
 


<!-- detected tables -->

| TMC5160 TMC5160 TMC5160 NAI #1 NAI #2 NAI #3 NAO NAO +VIO SWIOP SWION SWIOP SWION SWIOP SWION Master CPU RIDLE (µC with UART, TXD software switches TXD to RXD hi-Z for receiving) RIDLE forces stop bit level in idle conditions, 3k3 is sufficient with 14 slaves | TMC5160 #1 | NAI | TMC5160 #2 | NAI | TMC5160 #3 |  |
|---|---|---|---|---|---|---|
| Master CPU (µC with UART, software switches TXD to hi-Z for receiving) |  |  |  |  |  |  |
