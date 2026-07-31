# 快速计划: EEPROM 启动自检

## 目标
新增 TEXT/ela_eeprom_test.c/h 弱化测试，启动时对 Data 块执行完整功能 + 边界自检，结果人眼观察（LED/返回值），验证 ela_eeprom 模块 read/write/valid/erase 四个接口。

## 改动清单
1. **新增** `TEXT/ela_eeprom_test.h` — 声明 `ela_eeprom_test_run(void)`
2. **新增** `TEXT/ela_eeprom_test.c` — 自检实现：
   - 擦除 Data 块 → `ela_eeprom_valid` 应返回 false
   - 写/读 0x55、0xAA 模式（首、中、末地址）
   - 写/读顺序数 0x00~0xFF 回卷序列
   - 边界：偏移 0 与 area_size 尾部写入越界保护检查
   - 写后回读校验，任一失败置测试失败标记
   - 结果通过 `ela_eeprom_test_pass` 状态（TEST_LED 指示）
3. **修改** `ELA_LIB/elaco_main.c` — 加 `#include "ela_eeprom_test.h"` + 注释形式的调用行（测试完删除）
4. **同步** `MDK-ARM/StepMotorDriver_Keil.uvprojx` — TEXT 组加入 ela_eeprom_test.c

## 注意事项
- 仅操作 `g_eeprom_datablock_st`（0x08020000），**严禁**触碰 Calib 块
- 测试会破坏 Data 块现有数据（当前无业务使用，安全）
- 擦除需 Flash 解锁/锁定，禁止在 ISR 调用
- 遵循 ela_rules：UTF-8、4 空格、行宽 ≤84、段标记 `/* eeprom test start/end */`
- 弱化测试：不写断言/日志/printf，人眼观察 TEST_LED 或返回值
