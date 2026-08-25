# TMC5160A_Datasheet_Rev1.14 — 第4章 4 SPI Interface

--- [PAGE 23] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  23 
 
 
 
www.trinamic.com 
4 SPI Interface 
4.1 SPI Datagram Structure 
The TMC5160 uses 40 bit SPI™ (Serial Peripheral Interface, SPI is Trademark of Motorola) datagrams 
for communication with a microcontroller. Microcontrollers which are equipped with har dware SPI are 
typically able to communicate using integer multiples of 8 bit. The NCS line of the device must be 
handled in a way, that it stays active (low) for the complete duration of the datagram transmission. 
 
Each datagram sent to the device is composed of an address byte followed by four data bytes. This 
allows direct 32 bit data word comm unication with the register set . Each register is accessed via 32 
data bits even if it uses less than 32 data bits.  
 
For simplification, each register is specified by a one-byte address: 
- For a read access the most significant bit of the address byte is 0.  
- For a write access the most significant bit of the address byte is 1.  
 
Most registers are write -only registers, some can be read additionally, and there are also  some read 
only registers.  
 
 
4.1.1 Selection of Write / Read (WRITE_notREAD) 
The read and write selection is controlled by the MSB of the address byte (bit 39 of the SPI 
datagram). This bit is 0 for read access and 1 for write access. So, the bit named W is a 
WRITE_notREAD control bit. The active high write bit is the MSB of the ad dress byte. So, 0x80 has to 
be added to the address for a write access. The SPI interface always delivers data back to the master, 
independent of the W bit. The data transferred back is  the data read from the address which was 
transmitted with the previous datagram, if the previous access was a read access. If the previous 
access was a write access, then the data read back mirrors the previously received write data. So, the 
difference between a read and a write access is that the read access does not transf er data to the 
addressed register but it transfers the address only and its 32 data bits are dummies, and, further the 
following read or write access delivers back the data read from th e address transmitted in the 
preceding read cycle. 
 
A read access reque st datagram uses dummy write data. Read data is transferred back to the master 
with the subsequent read or write access. Hence, reading multiple registers can be done in a 
pipelined fashion. 
 
Whenever data is read from or written to the TMC 5160, the MSBs d elivered back contain the SPI 
status, SPI_STATUS, a number of eight selected status bits. 
 
SPI DATAGRAM STRUCTURE 
MSB (transmitted first) 40 bit LSB (transmitted last) 
39 ... ... 0 
→ 8 bit address 
 8 bit SPI status  → 32 bit data 
39 ... 32 31 ... 0 
→ to  TMC5160  
RW + 7 bit address 
 from  TMC5160 
8 bit SPI status 
8 bit data 8 bit data 8 bit data 8 bit data 
39 / 38 ... 32 31 ... 24 23 ... 16 15 ... 8 7 ... 0 
W 38...32 31...28 27...24 23...20 19...16 15...12 11...8 7...4 3...0 
3
9 
3
8 
3
7 
3
6 
3
5 
3
4 
3
3 
3
2 
3
1 
3
0 
2
9 
2
8 
2
7 
2
6 
2
5 
2
4 
2
3 
2
2 
2
1 
2
0 
1
9 
1
8 
1
7 
1
6 
1
5 
1
4 
1
3 
1
2 
1
1 
1
0 9 8 7 6 5 4 3 2 1 0 
--- [PAGE 24] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  24 
 
 
 
www.trinamic.com 
Example:  
For a read access to the register ( XACTUAL) with the address 0x2 1, the address byte has to 
be set to 0x2 1 in the access preceding the read access. For a wr ite access to the register 
(VACTUAL), the address byte has to be set to 0x80 + 0x22 = 0xA2. For read access, the data 
bit might have any value (-). So, one can set them to 0.  
 
action data sent to TMC5160 data received from TMC5160 
read XACTUAL → 0x2100000000  0xSS & unused data 
read XACTUAL → 0x2100000000  0xSS & XACTUAL 
write VMAX:= 0x00ABCDEF → 0xA700ABCDEF  0xSS & XACTUAL 
write VMAX:= 0x00123456 → 0xA700123456  0xSS00ABCDEF 
 
*)S: is a placeholder for the status bits SPI_STATUS 
 
4.1.2 SPI Status Bits Transferred with Each Datagram Read Back 
New status information becomes latched at the end of each access and is available with the next SPI 
transfer. 
 
SPI_STATUS – status flags transmitted with each SPI access in bits 39 to 32 
Bit Name Comment 
7 status_stop_r RAMP_STAT[1] – 1: Signals stop right switch status (motion controller 
only) 
6 status_stop_l RAMP_STAT[0] – 1: Signals stop left switch status (motion controller only) 
5 position_reached RAMP_STAT[9] – 1: Signals target position reached (motion controller only) 
4 velocity_reached RAMP_STAT[8] – 1: Signals target velocity reached (motion controller only) 
3 standstill DRV_STATUS[31] – 1: Signals motor stand still 
2 sg2 DRV_STATUS[24] – 1:  Signals StallGuard flag active 
1 driver_error GSTAT[1] – 1:  Signals driver 1 driver error (clear by reading GSTAT) 
0 reset_flag GSTAT[0] – 1: Signals, that a reset has occurred (clear by reading GSTAT) 
 
4.1.3 Data Alignment 
All data are right aligned. Some registers represent unsigned (positive) values, some represent integer 
values (signed) as two’s complement numbers, single bits or groups o f bits are represented as single 
bits respectively as integer groups.   
4.2 SPI Signals 
The SPI bus on the TMC5160 has four signals: 
- SCK – bus clock input 
- SDI – serial data input 
- SDO – serial data output 
- CSN – chip select input (active low) 
 
The slave is enabled for an SPI transaction by a low on the chip select input CSN. Bit transfer is 
synchronous to the bus clock SCK, with the slave latching the data from SDI on the rising edge of SCK 
and driving data to SDO following the falling edge. The most signifi cant bit is sent first. A minimum 
of 40 SCK clock cycles is required for a bus transaction with the TMC5160. 
If more than 40 clocks are driven, the additional bits shifted into SDI are shifted out on SDO after a 
40-clock delay through an internal shift register. This can be used for daisy chaining multiple chips. 
CSN must be low during the whole bus transaction. When CS N goes high, the contents of the internal 
shift register are latched into the internal control register and recognized as a command from the  
master to the slave. If more than 40 bits are sent, only the last 40 bits received before the rising edge 
of CSN are recognized as the command.  
--- [PAGE 25] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  25 
 
 
 
www.trinamic.com 
4.3 Timing 
The SPI interface is synchronized to the internal system clock, which limits the SPI bus clock SCK to 
half of the system clock frequency. If the system clock is based on the on-chip oscillator, an additional 
10% safety margin must be used to ensure reliable data transmission. All SPI inputs as well as the 
ENN input are internally filtered to avoid triggerin g on pulses shorter than 20ns. Figure 4.1 shows the 
timing parameters of an SPI bus transaction, and the table below specifies their values. 
 
CSN
SCK
SDI
SDO
tCC tCCtCL tCH
bit39 bit38 bit0
bit39 bit38 bit0
tDO tZC
tDU tDH
tCH
 
Figure 4.1 SPI timing 
Hint 
Usually this SPI timing is referred to as SPI MODE 3 
 
SPI interface timing  AC-Characteristics 
clock period: tCLK 
Parameter Symbol Conditions Min Typ Max Unit 
SCK valid before or after change 
of CSN tCC  10   ns 
CSN high time tCSH 
*) Min time is for 
synchronous CLK 
with SCK high one 
tCH before CSN high 
only 
tCLK*) >2tCLK+10  ns 
SCK low time tCL 
*) Min time is for 
synchronous CLK 
only 
tCLK*) >tCLK+10  ns 
SCK high time tCH 
*) Min time is for 
synchronous CLK 
only 
tCLK*) >tCLK+10  ns 
SCK frequency using internal 
clock fSCK assumes minimum 
OSC frequency   4 MHz 
SCK frequency using external 
16MHz clock fSCK assumes 
synchronous CLK   8 MHz 
SDI setup time before rising 
edge of SCK tDU  10   ns 
SDI hold time after rising edge 
of SCK tDH  10   ns 
Data out valid time after falling 
SCK clock edge tDO no capacitive load 
on SDO   tFILT+5 ns 
SDI, SCK and CSN filter delay 
time tFILT 
rising and falling 
edge 12 20 30 ns 
 
  
