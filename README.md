# ELACO_StepMotorTMC5160

## 这是一个基于TMC5160的步进电机驱动项目

其中包含了原理图PCB以及源代码。

## 当前状态：

### 2026.07.08

- [x] 查看example内的文件内容(关于tmc5160的)
- [ ] 对TMC5160的SPI进行配置和通讯
- [ ] 测试freemodbus

### 2026.07.07

- [x] 移植freemodbus

  配置一个串口（开启串口中断），配置一个定时器（开启定时器中断）

  移植freemodbus的文件入项目

  分别修改port.c，portserial.c和porttimer.c文件内容

- [x] 增加freemodbus移植内容以及测试函数。（测试函数也可以作为一个example来看）

- [x] 做了移植，但还未测试

对CAN进行了测试

### 2026.07.06

- [x] 焊接硬件

#### 目前存在的一些问题

1. CE3电容的PCB封装有点问题，正负极反了