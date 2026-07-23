# 调试经验: TMC5160 编码器方向与偏差调试

**日期**: 2026-07-23
**类型**: debug
**模块**: ela_tmc5160_usr

---

## 问题现象

1. XACTUAL=51200（正确），X_ENC=-51230（反向且偏差大）
2. 改 ENCMODE=0x01 后电机不转
3. CAN 反馈偏差值显示 0xE78F（异常大）

## 根因分析

### 1. 编码器方向由 ENC_CONST 符号决定

TMC5160 数据手册明确说明：
> "Negating the sign of ENC_CONST allows inversion of the counting direction to match motor and encoder direction."

ENC_CONST 是 16.16 定点数，**符号位控制计数方向**。

### 2. ENCMODE 的 pol_A/pol_B 不控制计数方向

ENCMODE 寄存器 bit0 (pol_A) 和 bit1 (pol_B) **只影响 N 通道事件检测**，不影响编码器计数方向。改 ENCMODE=0x01 会影响其他功能导致电机不转。

### 3. ENC_CONST 计算

```
Factor = FSC × USC / encoder resolution
       = 200 × 256 / 4000
       = 12.8

ENC_CONST (二进制模式) = 12 × 65536 + 0.8 × 65536
                       = 786432 + 52429
                       = 838861
                       = 0x000CCCCD
```

取反后：0x000CCCCD → 0xFFF33333

## 解决方案

```c
// 修改前
ela_tmc5160_write_reg(chip, REG_ENC_CONST, 0x000CCCCD);

// 修改后（取反补偿编码器方向）
ela_tmc5160_write_reg(chip, REG_ENC_CONST, 0xFFF33333);
```

## 经验总结

1. **编码器方向**：由 ENC_CONST 符号控制，不是 ENCMODE
2. **ENCMODE pol_A/pol_B**：只影响 N 通道事件检测
3. **ENC_DEVIATION 阈值**：应大于增量编码器上电初始偏移（256 足够）
4. **调试方法**：读 XACTUAL 和 X_ENC 对比，确认方向和偏差

---

**相关文件**: `ela_tmc5160_usr.c` → `ela_tmc5160_config_encoder()`
**数据手册**: TMC5160A Datasheet Rev1.14 第 108-109 页
