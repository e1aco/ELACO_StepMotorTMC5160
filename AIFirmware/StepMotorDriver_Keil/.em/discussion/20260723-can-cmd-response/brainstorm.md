# brainstorm: S2-can-cmd-response

## 需求理解

当前 `ela_can_usr.c` 已实现 CAN 命令解析框架（校验和验证、命令分发、反馈发送），但 6 个命令码的实际执行逻辑都是 `TODO`。需要实现：

1. **CMD_ABS_POS (0x01)**: 绝对位置移动 + 运动参数组选择
2. **CMD_REL_CW (0x02)**: 相对位置正转
3. **CMD_REL_CCW (0x03)**: 相对位置反转
4. **CMD_VELOCITY (0x04)**: 速度模式持续旋转
5. **CMD_STOP (0x05)**: 停止/刹车
6. **CMD_PID_ADJUST (0x06)**: PID 参数在线调参

输入数据：`cmd.value`（目标位置/速度/步数）、`cmd.motor`（电机选择 0x01/0x02/0x06）、`cmd.param`（参数组/PID类型）

## 候选方案

### 方案 A: 直接在 switch-case 中调用 TMC5160 API

- 思路：在 `ela_can_usr_process()` 的 switch-case 中直接调用 `ela_tmc5160_*` 函数
- 优点：简单直接，改动最小
- 缺点 / 风险：
  - `ela_can_usr.c` 直接依赖 `ela_tmc5160_usr.h`，耦合度高
  - 电机选择逻辑（单电机/全部电机）散落在各 case 中
  - PID 调参需要额外的参数存储模块
- 预估工作量：S

### 方案 B: 提取电机控制中间层

- 思路：新增 `ela_motor_ctrl.c/h`，封装电机选择 + 运动执行，`ela_can_usr` 只做协议解析
- 优点：
  - 解耦 CAN 协议与电机驱动
  - 电机选择逻辑集中处理（单电机/全部电机）
  - 便于后续扩展（如添加限位保护、运动状态管理）
- 缺点 / 风险：
  - 多一个文件，略增复杂度
- 预估工作量：M

### 方案 C: 在 ela_tmc5160_usr 中扩展命令接口

- 思路：在 `ela_tmc5160_usr.c` 中新增 `ela_tmc5160_exec_cmd()` 统一入口
- 优点：命令执行逻辑与 TMC5160 驱动紧耦合，内聚性好
- 缺点 / 风险：
  - `ela_tmc5160_usr` 本应是业务逻辑层，不应感知 CAN 协议
  - 违反分层原则（usr 不应知道命令码）
- 预估工作量：S

## 推荐

**方案 B**，理由：解耦合理，电机选择逻辑集中处理，便于后续扩展 PID 参数存储和运动状态管理。

## 关键技术点

- 电机选择：`cmd.motor == MOTOR_ALL` 时需遍历两片芯片
- 运动参数组：通过 `cmd.param` 选择预定义的速度/加速度参数
- PID 调参：需要一个轻量参数存储（可以是 RAM 变量，也可以是 EEPROM）
- 反馈时机：根据协议，CMD_ABS_POS/REL_CW/REL_CCW 需要发送启动反馈 + 到位反馈
