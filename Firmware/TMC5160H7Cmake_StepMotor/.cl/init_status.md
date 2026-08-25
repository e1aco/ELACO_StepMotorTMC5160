# /cl init 完成状态

## 完成项

- [x] 预检①: datasheet/ 创建, require.md 生成
- [x] 预检②: 芯片/引脚映射从 .ioc 提取填写
- [x] 全局目标访谈: CAN 双电机控制, 600rpm, 24V, 光编 4000ppr
- [x] PDF 提取: TMC5160A (EN, 章节), 57CME13 (单文件), AOD4126 (单文件)
- [x] datasheet/index.md 索引创建
- [x] .cl/ 骨架: datasheet/, memory/, sim/
- [x] module/ 骨架: drv/, usr/, test/
- [x] memory 推导: 电机参数, MOSFET 参数, TMC5160 配置, SPI/时钟树
- [x] 知识库检索: tmc5160.md 命中, drv 源码可复用

## 待办

- [ ] SPI prescaler 调整: 当前 8Mbit/s 超过 TMC5160 max 7.5MHz (15MHz CLK/2), 需改为 prescaler=16 → 4MHz
- [ ] CAN 协议定义
- [ ] 验收判据/优先级/MVP 待用户确认
- [ ] TIM4 PWM 频率/占空比配置 (15MHz 输出)
- [ ] USART1 波特率配置

## 关键推导值摘要

| 参数 | 值 | 依据 |
| :--- | :--- | :--- |
| GLOBALSCALER | 157 (0x9D) | 4A 电机, RS=0.05Ω, IFS=6.5A |
| IRUN | 31 | 满额定电流 |
| IHOLD | 22 | 70% IRUN |
| DRVSTRENGTH | 2 | AOD4126 Qgd=10nC |
| SPI prescaler | 16 (待改) | 64MHz/16=4MHz ≤ 7.5MHz max |
| TMC CLK | 15MHz | TIM4 CH3 PWM |
