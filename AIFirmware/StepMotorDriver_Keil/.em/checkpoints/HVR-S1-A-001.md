# 人工验证请求 [HVR-S1-A-001]

**验证类型**: 代码规范 + 编译验证
**所属步骤**: S1-A ela_can_drv — HAL 驱动层
**前置条件**: ela_queue 已安装
**芯片**: STM32F407ZET6
**调试器**: SWD

---

## 一、嵌入式执行记录

| 步骤 | 工具 | 结果 | 关键产物/字段 |
|------|------|------|---------------|
| 编译 | Keil | ⬜ 待用户执行 | 用户手动编译验证 |
| 烧录 | — | ⬜ 跳过 | S1-A 仅验证编译 |
| 串口 | — | ⬜ 跳过 | S1-A 无串口输出 |

---

## 二、编码规范检查（AI 已完成）

| 检查项 | ela_can_drv.h | ela_can_drv.c | elaco_main.c |
|--------|:---:|:---:|:---:|
| 文件头注释 | ✅ | ✅ | ✅ |
| 头文件保护 | ✅ ELA_CAN_DRV_H | — | — |
| 头文件独立 | ✅ 不含 elaco_main.h | — | — |
| 函数命名 | — | ✅ 外:ela_/static:can_ | ✅ elaco_main |
| 变量命名 | — | ✅ | ✅ |
| 宏命名 | ✅ 全大写 | — | — |
| 注释格式 | — | ✅ | ✅ |
| 分层标记 | ✅ hlp | ✅ hlp/drv/usr | ✅ hlp/drv/usr/cac |
| drv 唯一碰 HAL | — | ✅ | ✅ (cac区段回调) |
| 无 Magic Number | ✅ | ✅ | ✅ |

---

## 三、操作清单（人工执行）

### 步骤 1：Keil 编译
- [ ] 将 `ELA_LIB/ela_can_drv.c` 和 `ELA_LIB/ela_queue.c` 加入 Keil 工程
- [ ] 将 `ELA_LIB/` 加入 Include Paths
- [ ] 将 `Core/Src/elaco_main.c` 加入 Keil 工程
- [ ] 编译，检查 0 Error

### 步骤 2：功能验证（S1-C 阶段）
- [ ] 烧录后用 CAN 分析仪发送 ID=0x1AA55F42 帧，确认能接收
- [ ] 确认无其他 ID 帧被接收

---

## 四、预期结果

- Keil 编译 0 Error, 0 Warning
- 过滤器仅接收 CAN ID 0x1AA55F42
- 发送帧 ID 为 0x1AA55F43

---

## 五、结论

- [ ] ✅ 通过
- [ ] ❌ 失败
- [ ] ⚠️ 部分通过（备注）：________________

---

**提交结果命令**：
- 通过：`/em result s1-a-通过`
- 失败：`/em result s1-a-失败-<现象描述>`
