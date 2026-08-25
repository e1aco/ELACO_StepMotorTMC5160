# TMC5160A_Datasheet_Rev1.14 — 第5章 · p27

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  27 
 
 
 
www.trinamic.com 
5.1.2 Read Access 
 
UART READ ACCESS REQUEST DATAGRAM STRUCTURE 
each byte is LSB…MSB, highest byte transmitted first 
sync + reserved 8 bit slave address RW + 7 bit register 
address CRC 
0...7 8…15 16…23 24…31 
1 0 1 0 Reserved (don’t cares 
but included in CRC) SLAVEADDR register address 0 CRC 
0 
1 
2 
3 
4 
5 
6 
7 
8 
… 
15 
16 
… 
23 
24 
… 
31 
 
The read access request datagram structure is identical to the write access datagram structure, but 
uses a lower number of user bits. Its function is the addressing of the slave and the trans mission of 
the desired register address for the read access. Th e TMC5160 responds with the same baud rate as 
the master uses for the read request. 
 
In order to ensure a clean bus transition from the master to the slave, the TMC 5160 does not 
immediately send the reply to a read access, but it uses a programmable delay time after which the 
first reply byte becomes sent following a read request. This delay time can be set in multiples of 
eight bit times using SENDDELAY time setting (default=8 bit times) accord ing to the needs of the 
master. In a multi -slave system, set SENDDELAY to min. 2 for all slaves. Otherwise a non -addressed 
slaves might detect a transmission error upon read access to a different slave. 
 
UART READ ACCESS REPLY DATAGRAM STRUCTURE 
each byte is LSB…MSB, highest byte transmitted first 
0 ...... 63 
sync + reserved 8 bit slave 
address 
RW + 7 bit 
register addr. 32 bit data CRC 
0…7 8…15 16…23 24…55 56…63 
1 0 1 0 reserved (0) 0xFF register 
address 0 data bytes 3, 2, 1, 0 
(high to low byte) CRC 
0 
1 
2 
3 
4 
5 
6 
7 
8 
… 
15 
16 
… 
23 
24 
… 
55 
56 
… 
63 
 
The read response is sent to the master using address code %1111. The transmitter becomes switched 
inactive four bit times after the last bit is sent.  
 
Address %1111 1111 is reserved for read accesses going to the master. A slave cannot use this 
address. 
  
