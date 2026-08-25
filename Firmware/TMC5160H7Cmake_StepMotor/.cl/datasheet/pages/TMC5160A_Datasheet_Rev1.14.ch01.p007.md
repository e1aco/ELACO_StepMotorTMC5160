# TMC5160A_Datasheet_Rev1.14 — 第1章 · p7

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  7 
 
 
 
www.trinamic.com 
StealthChop2™ No-noise, high -precision chopper algorithm for inaudible motion and inaudible 
standstill of the motor. Allows faster motor acceleration and deceleration than 
StealthChop™ and extends StealthChop to low stand still motor currents. 
SpreadCycle™ High-precision chopper algorit hm for highly dynamic motion and absolutely clean 
current wave. Low noise, low resonance and low vibration chopper. 
DcStep™ Load dependent speed control. The motor moves as fast as possible and never loses 
a step.   
StallGuard2™ Sensorless stall detection and mechanical load measurement. 
CoolStep™ Load-adaptive current control reducing energy consumption by as much as 75%. 
MicroPlyer™ Microstep interpolator for obtaining full 256 microstep smoothness with lower 
resolution step inputs starting from fullstep 
In addition to these performance enhancements, TRINAMIC motor drivers offer safeguards to detect 
and protect against shorted outputs, output open -circuit, overtemperature, and undervoltage 
conditions for enhancing safety and recovery from equipment malfunctions. 
1.2 Control Interfaces 
The TMC 5160 supports both, an SPI interface and a UART based single wire interface with CRC 
checking. Additionally, a standalone mode is provided for pure STEP/DIR operation without use of the 
serial interface. Selection of the ac tual interface is done via the configuration pin s SPI_MODE and 
SD_MODE, which can be hardwired to GND or VCC_IO depending on the desired interface.  
 
1.2.1 SPI Interface 
The SPI interface is a bit -serial interface synchronous to a bus clock. For every bit sent f rom the bus 
master to the bus slave  another bit is sent simultaneously from the slave to the master. 
Communication between an SP I master and the TMC 5160 slave always consists of sending one 40-bit 
command word and receiving one 40-bit status word. 
 
The SPI command rate typically is a few commands per complete motor motion. 
 
1.2.2 UART Interface 
The single wire interface allows differential operation similar to RS485 (using SWP and SWN) or single 
wire interfacing (leaving open SWN).  It can be driven by any standar d UART. No baud rate 
configuration is required. 
1.3 Software 
From a software point of view the TMC 5160 is a  peripheral with a number  of control and status 
registers. Most of them can either be written only or read only. Some of the registers allow both read 
and write access. In case read -modify-write access is desired for a write only register, a shadow 
register can be realized in master software. 
  
