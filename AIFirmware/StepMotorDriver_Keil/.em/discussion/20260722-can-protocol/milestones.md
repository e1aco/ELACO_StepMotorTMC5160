# milestones: S1-can-protocol

## 选定方案

方案 B: ela_can_drv + ela_can_usr 分层

## 子步骤

### S1-A: ela_can_drv — HAL 驱动层
- 内容：过滤器配置（仅接收 0x1AA55F42）、中断接收注册、发送封装
- 依赖：无
- 预估：S

### S1-B: ela_can_usr — 协议解析层
- 内容：命令码解析（0x01~0x06）、校验和验证、反馈帧组装、队列对接
- 依赖：S1-A 完成
- 预估：M

### S1-C: elaco_main 集成
- 内容：elaco_main 调用 drv 初始化、主循环调用 usr 处理、CAN 中断回调入队
- 依赖：S1-A + S1-B 完成
- 预估：S

### S1-D: Keil 工程配置
- 内容：ELA_LIB 组添加所有文件、IncludePath 添加 ../ELA_LIB
- 依赖：S1-A + S1-B + S1-C 完成
- 预估：S
