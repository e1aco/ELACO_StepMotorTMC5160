# TMC5160A_Datasheet_Rev1.14 — 第5章 · p26

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
26 
 
 
 
www.trinamic.com 
5 UART Single Wire Interface 
The UART single wire interface allows the control of the TMC5160 with any microcontroller UART. It 
shares transmit and receive line like an RS485 based interface. Data transmission is secured using a 
cyclic redundancy check, so that increased interface distances (e.g. over cables between two PCBs) can 
be bridged without the danger of wrong or missed commands even in the event of electro-magnetic 
disturbance. The automatic baud rate detection and an advanced addressing scheme make this 
interface easy and flexible to use. 
5.1 Datagram Structure 
5.1.1 
Write Access 
 
UART WRITE ACCESS DATAGRAM STRUCTURE 
each byte is LSB…MSB, highest byte transmitted first 
0 … 63 
sync + reserved 
8 bit slave 
address 
RW + 7 bit 
register addr. 
32 bit data 
CRC 
0…7 
8…15 
16…23 
24…55 
56…63 
1 
0 
1 
0 
Reserved (don’t cares 
but included in CRC) 
SLAVEADDR 
register 
address 
1 
data bytes 3, 2, 1, 0 
(high to low byte) 
CRC 
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
 
A sync nibble precedes each transmission to and from the TMC5160 and is embedded into the first 
transmitted byte, followed by an addressing byte. Each transmission allows a synchronization of the 
internal baud rate divider to the master clock. The actual baud rate is adapted and variations of the 
internal clock frequency are compensated. Thus, the baud rate can be freely chosen within the valid 
range. Each transmitted byte starts with a start bit (logic 0, low level on SWP) and ends with a stop 
bit (logic 1, high level on SWP). The bit time is calculated by measuring the time from the beginning 
of start bit (1 to 0 transition) to the end of the sync frame (1 to 0 transition from bit 2 to bit 3). All 
data is transmitted byte wise. The 32 bit data words are transmitted with the highest byte first.  
 
A minimum baud rate of 9000 baud is permissible, assuming 20 MHz clock (worst case for low baud 
rate). Maximum baud rate is fCLK/16 due to the required stability of the baud clock. 
 
The slave address is determined by the register SLAVEADDR. If the external address pin NEXTADDR is 
set, the slave address becomes incremented by one. 
 
The communication becomes reset if a pause time of longer than 63 bit times between the start bits 
of two successive bytes occurs. This timing is based on the last correctly received datagram. In this 
case, the transmission needs to be restarted after a failure recovery time of minimum 12 bit times of 
bus idle time. This scheme allows the master to reset communication in case of transmission errors. 
Any pulse on an idle data line below 16 clock cycles will be treated as a glitch and leads to a timeout 
of 12 bit times, for which the data line must be idle. Other errors like wrong CRC are also treated the 
same way. This allows a safe re-synchronization of the transmission after any error conditions. 
Remark, that due to this mechanism an abrupt reduction of the baud rate to less than 15 percent of 
the previous value is not possible. 
 
Each accepted write datagram becomes acknowledged by the receiver by incrementing an internal 
cyclic datagram counter (8 bit). Reading out the datagram counter allows the master to check the 
success of an initialization sequence or single write accesses. Read accesses do not modify the 
counter. 
 
 
 


<!-- detected tables -->

| UART WRITE ACCESS DATAGRAM STRUCTURE |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | each byte is LSB…MSB, highest byte transmitted first |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| 0 … 63 |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| sync + reserved |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | 8 bit slave |  |  |  |  |  |  |  |  | RW + 7 bit register addr. |  |  |  |  | 32 bit data |  |  |  |  |  |  | CRC |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | address |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
| 0…7 |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | 8…15 |  |  |  |  |  |  |  |  | 16…23 |  |  |  |  |  | 24…55 |  |  |  |  |  |  | 56…63 |  |  |  |  |  |
| 1 |  | 0 |  | 1 |  | 0 |  | Reserved (don’t cares but included in CRC) |  |  |  |  |  |  |  | SLAVEADDR |  |  |  |  |  |  |  |  | register address |  |  |  | 1 |  | data bytes 3, 2, 1, 0 (high to low byte) |  |  |  |  |  |  | CRC |  |  |  |  |  |
|  | 0 |  | 1 |  | 2 |  | 3 |  | 4 |  | 5 |  | 6 |  | 7 |  | 8 |  |  | … |  |  | 15 |  |  | 16 |  | … |  | 23 |  | 24 |  | … |  |  | 55 |  | 56 |  | … |  | 63 |
