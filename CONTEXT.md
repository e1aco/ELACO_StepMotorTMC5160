# 领域术语表 (CONTEXT)

## EEPROM 测试
| 术语 | 定义 |
|------|------|
| EEPROM | STM32F4 内部 Flash 模拟的 EEPROM，非外部 I2C/SPI 芯片 |
| Data 块 | g_eeprom_datablock_st，0x08020000 起 128KB，用于数据存储测试 |
| Calib 块 | g_eeprom_caliblock_st，0x08010000 起 64KB，TMC5160 配置，测试不触碰 |
| 弱化测试 | ela_xxx_test 系列，位于 TEXT/，启动时调用，人眼观察结果 |

## 过温优化
| 术语 | 定义 |
|------|------|
| 采样电阻 | BOM R10/R22/R51/R64，50mR/3W，每轴 A/B 相各一 |
| IRUN/IHOLD | TMC5160 运行/保持电流刻度，CS=IRUN/32 × V_FS/R_SENSE |
| I_RMS | (CS/32) × 0.25V / 0.05Ω，IRUN=10 → 1.56A RMS，IHOLD=1 → 0.16A |
| TPOWERDOWN | 静止后降流延迟，2^18 tCLK 单位，40 ≈ 873ms |
| CoolStep | TMC5160 轻载自动降流，保守配置最小 IRUN/4 |
