# TMC5160A_Datasheet_Rev1.14 — 第5章 · p30

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
30 
 
 
 
www.trinamic.com 
Master CPU 
(µC with RS485
tranceiver)
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
TMC5160
#3
SWIOP
SWION
A
B
Addressing phase 1:
address 0, NAO high
address 1
address 1
Addressing phase 2:
program to address 254 & set NAO low
address 0, NAO high
address 1
Addressing phase 3:
address 254
program to address 253 & set NAO low
address 0, NAO high
Addressing phase 4:
address 254
address 253
program to address 252 & set NAO low
1k
+VIO
NAO
NAI
EXAMPLE FOR ADDRESSING UP TO 255 TMC5160
Addressing phase X:
continue procedure 
RTERM
RTERM
RFILT
CFILT
RFILT
CFILT
 
Figure 5.2 Addressing multiple TMC5160 via the differential interface, additional filtering for NAI 
A different scheme (not shown) uses bus switches (like 74HC4066) to connect the bus to the next unit 
in the chain without using the NAI input. The bus switch can be controlled in the same fashion, using 
the NAO output to enable it (low level shall enable the bus switch). Once the bus switch is enabled it 
allows addressing the next bus segment. As bus switches add a certain resistance, the maximum 
number of nodes will be reduced. 
 
It is possible to mix different styles of addressing in a system. For example, a system using two 
boards with each two TMC5160 can have both devices on a board with a different level on NEXTADDR, 
while the next board is chained using analog switches separating the bus until the drivers on the first 
board have been programmed. 
 
 
 
 


<!-- detected tables -->

|  |  | SWIOP |  | SWIOP |  | SWIOP |  |
|---|---|---|---|---|---|---|---|
|  | RTERM |  |  |  |  |  |  |
