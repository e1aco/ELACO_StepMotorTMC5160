# 领域术语表 (CONTEXT)

## EEPROM 测试
| 术语 | 定义 |
|------|------|
| EEPROM | STM32F4 内部 Flash 模拟的 EEPROM，非外部 I2C/SPI 芯片 |
| Data 块 | g_eeprom_datablock_st，0x08020000 起 128KB，用于数据存储测试 |
| Calib 块 | g_eeprom_caliblock_st，0x08010000 起 64KB，TMC5160 配置，测试不触碰 |
| 弱化测试 | ela_xxx_test 系列，位于 TEXT/，启动时调用，人眼观察结果 |
