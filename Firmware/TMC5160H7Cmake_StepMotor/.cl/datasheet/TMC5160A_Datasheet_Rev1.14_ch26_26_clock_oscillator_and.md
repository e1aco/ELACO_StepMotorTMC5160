# TMC5160A_Datasheet_Rev1.14 — 第26章 26 Clock Oscillator and Input

--- [PAGE 119] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  119 
 
 
 
www.trinamic.com 
25 External Reset 
The chip is loaded with default v alues during power on via its internal power -on reset. In order to 
reset the chip to power on defaults, any of the supply voltages monitored by internal reset circuitry 
(VSA, +5VOUT or VCC_IO) must be cycled. VCC is not monitored.  Therefore VCC must not be switched 
off during operation of the chip. As +5VOUT is the output of the internal voltage regulator, it cannot 
be cycled via an external source except by cycling VSA. It is easiest and safest to cycle VCC_IO in order 
to completely reset the chip . Also, current consumed from VCC_IO is low and therefore it has simple 
driving requirements. Due to the input protection diodes not allowing the digital inputs to rise above 
VCC_IO level, all inputs must be driven low during this reset operation. When this is not possible, an 
input protection resistor may be used to limit current flowing into the related inputs.  
 
In case, VCC becomes supplied by an external source, make sure that VCC is at a stable value above 
the lower operation limit once the reset ends. This no rmally is satis fied when generating a 3.3V 
VCC_IO from the +5V supply supplying the VCC pin, because it will then come up with a certain delay.  
 
26 Clock Oscillator and Input 
The clock is the timing reference for all functions: the chopper, the velocity, the  acceleration control, 
etc. Many parameters are scaled with the clock frequency, thus a precise reference allows a more 
deterministic result. The factory-trimmed on-chip clock oscillator provides timing in case no external 
clock is easily available.  
26.1 Using the Internal Clock 
Directly tie the CLK input to GND near to the IC if the internal clock oscillator is to be used.  It will be 
sufficient for applications, where a velocity precision of roughly +-4% is tolerable. 
26.2 Using an External Clock 
When an external c lock is available, a frequency of 1 0 MHz to 16 MHz is recommended for optimum 
performance. The duty cycle of the clock signal is uncritical, as long as minimum high or low input 
time for the pin is satisfied (refer to electrical characteristics). Up to 18  MHz can be used, when the 
clock duty cycle is 50%. Make sure, that the clock source supplies clean CMOS output logic levels and 
steep slopes when using a high clock fre quency. The external clock input is enabled with the second 
positive polarity seen on the CLK input.  
 
Hint 
Switching off the external clock frequency prevents the driver from operating normally. Therefore  an 
internal watchdog switches back to internal clo ck in case the external signal is missing for more than 
roughly 32 internal clock cycles. 
 
26.2.1 Considerations on the Frequency 
A higher frequency allows faster step rates, faster SPI operation and higher chopper frequencies. On 
the other hand, it causes more  power dissipation in the TMC 5160 digital core and 5V voltage 
regulator. Generally a frequ ency of 1 0 MHz to 1 2 MHz should be sufficient for most applications. At 
higher clock frequency, the VSA supply voltage should be connected to a lower voltage for 
applications working at more than 24V nominal supply voltage. For reduced requirements concerning 
the motor dynamics, a clock frequency of down to 8 MHz (or even lower) can be considered.  
