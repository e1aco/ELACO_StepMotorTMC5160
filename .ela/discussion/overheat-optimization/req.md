# 过温优化 — 阶段 2：需求对齐

## 目标（验收标准）

1. CAN 状态标志 **bit2（过温）消除**，即 DRV_STATUS bit25/26 不再置位，芯片结温 <143°C（期望余量：<120°C）
2. 电机额定电流 1.5A 前提下，**运行电流不降低运动性能**（不堵转、不丢步）
3. 静止保持力矩保留（IHOLD>0），但待机发热显著下降
4. 不影响既有功能：定位、速度、编码器校验、闭环 PID、EEPROM 配置

## 涉及接口

### 寄存器（usr 层常量，ela_tmc5160_usr.c 顶部）

| 寄存器 | 地址 | 现状 | 目标 |
|--------|------|------|------|
| REG_IHOLD_IRUN | 0x10 | `(4<<16)|(10<<8)|6` | IRUN 按电机额定标定；IHOLD 待机最小化 |
| REG_TPOWERDOWN | 0x11 | **未写**（默认 10） | 显式写入，静止延迟后降 IHOLD |
| REG_COOLCONF | 0x6D | **未写**（默认 0，CoolStep 关） | 保守启用 |
| REG_TCOOLTHRS | 0x14 | 未写 | CoolStep/StallGuard 阈值（速度上限） |
| REG_CHOPCONF | 0x6C | 0x000101C5 | 保持或微调 |
| REG_GCONF | 0x00 | 0x04 (StealthChop) | 保持 |

### 需要新增的寄存器常量

```
REG_GLOBAL_SCALER  0x0B   /* 全局电流缩放，如需 */
REG_COOLCONF       0x6D   /* CoolStep/StallGuard2 配置 */
REG_TCOOLTHRS      0x14   /* 速度阈值：低于此速 CoolStep 生效 */
```

## 现有函数改动面

| 函数 | 文件 | 改动 |
|------|------|------|
| `ela_tmc5160_init()` | ela_tmc5160_usr.c:187 | 写入 TPOWERDOWN/COOLCONF/TCOOLTHRS；调整 IHOLD_IRUN 数值 |
| （可选）新增 `ela_tmc5160_set_current()` | ela_tmc5160_usr.c/.h | 运行时电流标定接口（为后续电机参数化预留） |

## 电流量级核对（数据手册 Rev1.14 §9）

```
I_RMS = (CS/32) × V_FS / R_SENSE        （GLOBAL_SCALER=0 视为 256=全量程）
V_FS ≈ 0.25V（VSRT 电气特性）  R_SENSE = 0.05Ω（BOM: R10/R22/R51/R64 50mR）

IRUN=10 → (10/32)×0.25/0.05 = 1.56A RMS（峰值 2.2A）   ← 现配置
IHOLD=4  → (4/32)×0.25/0.05  = 0.62A RMS（峰值 0.88A）  ← 现配置

代码注释「I_full ≈ 203mA / 运行 65mA」与 BOM 采样电阻矛盾，系计算错误（差 ~7.7 倍）。
```

## 约束

- 电机额定 ≥1.5A（用户确认），IRUN=10 的 1.56A RMS 在额定范围内，但**芯片温度来自双轴满载 + 待机持续电流**，需靠 TPOWERDOWN 降待机电流 + CoolStep 减轻载电流
- 无 IWDG 激活（main.c 中 MX_IWDG_Init 注释）——与本任务无关，不引入
- 暂不涉及 DRV_CONF.OTSELECT：150°C 已是最低安全档位（OTSELECT=00），降低档位只会让芯片更早关断，不解决根源
- 测试规范同 EEPROM：无 printf，用 TEST_LED(PA2) 或 CAN 状态指示（本任务不新增测试文件，靠现有 CAN bit2 验证）
