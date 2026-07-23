# 调试经验: TMC5160 过温与失步检测

**日期**: 2026-07-23
**类型**: debug
**模块**: ela_tmc5160_usr

---

## 问题现象

CAN反馈状态值 0x05/0x06/0x07 频繁出现：
- bit2=1 (过温)
- bit1=1 (失步)

但电机实际运行正常，没有明显抖动或位置偏差。

## 根因分析

### 过温问题
- DRV_STATUS bit25=otpw (过温预警告), bit26=ot (过温)
- TMC5160芯片温度确实过高
- 可能原因：电流太大、散热不足、负载过重

### 失步误报
- ENC_STATUS.bit1 (deviation_warn) 是编码器偏差报警
- 当 XACTUAL 与 X_ENC 偏差超过 ENC_DEVIATION 阈值时置位
- 当前阈值 256 (≈0.5°)，可能太小导致误报
- 电机运行正常说明实际没有失步，只是编码器噪声触发了报警

## 解决方案

### 过温
1. 降低电流：IRUN 16→10, IHOLD 6→4
2. 硬件：加强散热（散热片、导热硅脂）

### 失步误报
增大 ENC_DEVIATION 阈值（当前256，建议512或1024）

## DRV_STATUS 位域

```
bit25: otpw (over temperature pre-warning)
bit26: ot (over temperature)
bits [25:16]: SG_RESULT (StallGuard2 result)
```

## 经验总结

1. **过温检测**: DRV_STATUS bit25/26 指示温度状态
2. **失步检测**: ENC_STATUS.bit1 是编码器偏差报警，不是直接的失步检测
3. **误报处理**: 编码器噪声可能导致偏差报警，需要适当增大阈值
4. **状态值解读**: 0x05=到位+过温, 0x06=失步+过温, 0x07=到位+失步+过温

---

**相关文件**: `ela_tmc5160_usr.c` → `ela_tmc5160_get_status_flags()`
