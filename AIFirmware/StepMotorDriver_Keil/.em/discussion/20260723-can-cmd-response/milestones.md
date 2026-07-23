# milestones: S2-can-cmd-response

## 选定方案

**方案 B: 电机控制中间层**
- 新增 `ela_motor_ctrl.c/h`，封装电机选择 + 运动执行
- `ela_can_usr` 只做协议解析和分发
- 暂不实现 CMD_PID_ADJUST (0x06)

## 子步骤

### S2-A: 电机控制中间层基础框架
- 内容：新增 `ela_motor_ctrl.c/h`，实现电机选择逻辑（单电机/全部电机）+ 基础运动接口
- 依赖：无
- 验证：编译通过，调用 `ela_motor_ctrl_move_to()` 能驱动电机转动
- 预估：S

### S2-B: 绝对位置移动 + 相对位置正反转
- 内容：实现 CMD_ABS_POS (0x01)、CMD_REL_CW (0x02)、CMD_REL_CCW (0x03)，含运动参数组选择
- 依赖：S2-A 完成
- 验证：通过 CAN 发送命令，电机按预期动作，收到启动反馈
- 预估：M

### S2-C: 速度模式 + 停止/刹车
- 内容：实现 CMD_VELOCITY (0x04)、CMD_STOP (0x05)
- 依赖：S2-A 完成
- 验证：速度模式持续旋转，停止命令立即刹车
- 预估：S

### S2-D: 集成测试 + 到位反馈
- 内容：完善到位反馈（position_reached），整体流程联调
- 依赖：S2-B、S2-C 完成
- 验证：发送绝对位置命令后，电机到位时收到到位反馈帧
- 预估：S

## 关键决策
- [2026-07-23] 暂不实现 CMD_PID_ADJUST (0x06)，待 PID 模块添加后再实现
- [2026-07-23] 采用方案 B，新增 ela_motor_ctrl 中间层解耦
