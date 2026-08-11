# 调试日志

> 由 /cl run 或 /cl end 自动写入。格式见 templates/log.md。
> 项目: TMC5160_StepMotor（STM32F407ZETx + TMC5160 x2）

## 初始化

- 2026-08-05 /cl init 完成：datasheet 索引已生成，调试器=ST-LINK，经验库已挂载。
- 任务队列（require.md）:
  1. [ ] 使用定时器5实现1s的MCU_LED闪烁
  2. [ ] 调通CAN：读取ID 1AA55F42 的8字节消息并原样回发
  3. (待填) 全局目标：CAN指令控制TMC5160芯片2驱动电机2，绝对/相对位置正反转+速度模式正反转

## 2026-08-05 移植 ELACO StepMotorDriver_Keil（/cl code）

- 任务: 移植 XM\ELACO_StepMotorTMC5160\AIFirmware\StepMotorDriver_Keil\ELA_LIB → 本项目 src/，标记 [c]（Code Only，调试用户接管）。
- 命名映射: ela_* → tmc5160_*/can_*/motor_*/closed_loop/pid/queue/eeprom/timer_drv（cl 规范）。
- 分层: drv（HAL/寄存器原语）+ usr（业务逻辑）分文件；纯算法（queue/pid）归 usr。
- 目录: `module/drv/` + `module/usr/`（替代最初的 src/ 统一放置）。
- 无 app_main 模块：初始化 + 主循环直接写入 main.c；HAL 中断回调（CAN RX0 + TIM7 周期置 cl_tick_flag）移入 stm32f4xx_it.c。
- 已写入 module/: tmc5160_drv, tmc5160_usr, can_drv(+g_queue_st 移入 queue.c), can_usr, motor_ctrl, closed_loop, eeprom, timer_drv, queue, pid。
- 织入: main.c include + QUEUE_Init/DRV_CAN_Init/USR_CAN_Init/USR_TMC5160_Init/USR_MOTOR_Init/USR_CLOSEDLOOP_Init + while{USR_CAN_Process / cl_tick 消费 / USR_TMC5160_SaveConfig}；stm32f4xx_it.c 补 TIM7_IRQHandler + extern htim7 + 两回调。
- 修正: tmc_* → tmc5160_*（文件名+函数前缀 DRV_TMC5160_*/USR_TMC5160_*/TMC5160_CHIP_T）；`TMC_RegValid`→`TMC5160_RegValid`；eeprom.h bool→uint8_t。
- Include 约定: Keil Include Paths 指向 `module`，代码内用 `drv/xxx.h`、`usr/xxx.h`。
- 决策: IWDG 保持关闭；不移植测试文件；eeprom Flash 分配 Config=Sector4(0x08010000)/Data=Sector5(0x08020000)；闭环 PID 默认保守值 Kp=5/Ki=0/Kd=0；TIM7 500Hz 依据 APB1 84M/(84×2000) 待实测。
- 注意: MDK-ARM 工程需手动添加 module/ 下 .c 到 uvprojx 才可编译。

## 2026-08-05 移植版偶发卡顿排查（/cl end 接管手动调试）
- **模式**: /cl code 移植后真机调试（定位模式 MoveTo / 开环 / 闭环 OFF，仍偶发卡顿）
- **现象**: 电机定位/旋转时偶发一次顿挫；原版 ELACO 工程无此现象
- **尝试**:
  - 1. 逐项对比 20 个 module 文件（作者改 cl、逻辑等价）→ 无差异
  - 2. 对比 Core 层（main/gpio/tim/spi/usart/hal_msp）→ SPI3/TIM7/TIM4/优化等级均一致
  - 3. 对比 uvprojx 编译选项 → 仅 `<Optim>` 原版4/移植版2（用户排除）
  - 4. 对比编码器设置（ENCMODE=0x00 / ENC_CONST=0xFFF33333 / ENC_DEVIATION=256）→ 完全一致
  - 5. Flash 配置读取（magic=ELAC/mode=01 定位/closed_loop=00）→ 一致
- **根因**: `Core/Src/main.c` 中 `MX_IWDG_Init()` 被启用（前次会话决策"保持关闭"但遗漏注释），
  iwdg.c 配置 Prescaler=32/Reload=2000 → 约 2s 超时，且全工程无 `HAL_IWDG_Refresh` 喂狗
  → MCU 每 ~1.3~2.1s 看门狗复位 → 重新初始化 TMC5160（重写 CHOPCONF 触发 StealthChop
  重新校准）→ 表现为"偶发卡顿"。原版 elaco_main.c 中 `// MX_IWDG_Init();` 已注释。
- **最终方案**: 在 `Core/Src/main.c` while 主循环内加 `HAL_IWDG_Refresh(&hiwdg)`（main.c:136）
- **验证结果**: 已编译验证通过；需用户烧录后确认不再卡顿
- **经验引用**: 新增 `generalize/watchdog.md`（IWDG 启用未喂狗 → 周期性复位症状）

## 2026-08-06 任务1：CAN 调试输出（0x1AA55F44，"CAN 当串口用"）（/cl run）
- **模式**: /cl run 物理闭环，新增周期调试遥测帧
- **现象**: 需求=设置 0x1AA55F44 为调试输出；选型=把 CAN 当串口发可读文本（不依赖 8 字节命令协议），判据=周期读到可读调试帧
- **方案**: 
  - can_usr 新增 `USR_CAN_DebugTick()`：自定义轻量格式化（不依赖 printf），拼 `U1/U2 X=位置 E=编码器 S=状态 P=阶段 D=DRV_STATUS` 文本，按 8 字节切帧发 `0x1AA55F44`
  - main.c 主循环每 ~500ms 调用一次（HAL_GetTick 节流）
  - can_drv 新增 `DRV_CAN_SendWait()`：发送前等 TX 邮箱空闲，避免非阻塞 AddTxMessage 连发 9 帧邮箱满丢帧
- **尝试/调试**:
  - UV4 `-f` 命令行可烧录（exit 0），但**只下载不复位运行**（CPU 停在调试态）→ 无帧
  - 装 pyocd，`pyocd commander -t cortex_m -c reset -c go` 经 ST-Link 发复位 → 固件正常跑，遥测周期输出 ✅
  - 单次多帧仍有部分串扰/丢帧（`.cl` hex 是 EEPROM 魔数 "ELAC" 字节混入总线，疑似总线有其他数据）
- **验证结果**: 周期读到可读遥测帧 `U1 X=.. E=.. S=.. D=.. U2 ...`，判据"周期调试帧输出 OK"达成 ✅（标记 [x] 待人工验收）
- **发现的问题**: 遥测显示 S=10（SPI 异常 bit）、D=FFFFFFFF、E=0。**用户确认根因=测试时未给 TMC5160 上 24V 驱动电源**，驱动未供电故 SPI 读回全 1，属正常现象，非代码 bug；上 24V 后读数应恢复。
- **经验引用**: generalize/can_debug_printf.md（CAN 当串口）；generalize/st_link_cli.md（UV4 -f 不复位 → pyocd reset 复位 + ST-Link 探针用 pyocd）

## 2026-08-07 任务1：CAN 调试输出 + 命令协议（/cl end 验收）
- **模式**: /cl end 验收此前 /cl run 的 [x] 任务
- **状态变更**: require.md `- [x] 设置ID 1AA55F44作为调试输出并自行设置CAN协议后进行调试` → [✓]（2026-08-07 验收通过）
- **验收内容**: 周期遥测帧 0x1AA55F44（`U1 X=.. E=.. S=.. D=..`）输出正常；0x1AA55F42 命令协议 / 0x1AA55F43 反馈协议按需求文件实施，即可用（此前 24V 未上电时读回全 1 属正常）
- **涉及模块**: can_drv 新增 `DRV_CAN_SendWait()`（发送前等 TX 邮箱空闲避免丢帧，can_drv.c:105）；can_usr 新增 `USR_CAN_DebugTick()`（CAN 当串口周期遥测，can_usr.c:167）+ `CAN_DBG_TX_ID=0x1AA55F44`
- **经验引用**: generalize/can_debug_printf.md；generalize/st_link_cli.md

## 2026-08-11 任务：确认 CAN 调试帧报警源解码（/cl run 物理闭环）
- **模式**: /cl run 物理闭环（烧录 → 常驻 CAN 监听 → 判据验证）
- **判据**: CAN 调试帧 U2 段 D=0x84xxxxxx（DRV_STATUS bit26=OTPW 置位）时 A=OTPW 正确显示；U1 无报警时 A=-
- **验证结果**: 真机 24V 上电、U2 过温预警状态下，捕获 U2 D=84064000 G=00000000 A=OTPW、U1 段 G=00000000 A=-，与判据逐字一致 ✅（require.md 标记 [✓] 2026-08-11 验收通过）
- **顺带修复**: can_drv.c DRV_CAN_SendWait() 原只等 1 个 TX 邮箱空闲，同一 ID 连续多帧会被 CAN 核跨邮箱乱序仲裁 → 监控端按行还原错位（"CAN 当串口"多帧串扰根因）；改为等全部 3 个邮箱空闲（串行化发送）后重建，0 Error/0 Warning
- **遗留现象**: 行首偶见 "CALEQ=...CALE" 等字节混入（总线其他数据/EEPROM 魔数），非本固件解码逻辑问题，不阻塞判据
- **工具要点**: pyocd 0.45.1 不识别 --target stm32f407vg，用默认 cortex_m；can_monitor.py 启动需 PYTHONIOENCODING=utf-8 + PYTHONUTF8=1（否则 GBK UnicodeEncodeError）；Windows Start-Process 单字符串引号丢失坑 → 用 .cmd 启动器
- **经验引用**: generalize/can_debug_printf.md（CAN 当串口多帧还原）
## 2026-08-11 转动物理验证 + ST-Link SWO 评估
- **转动验证**: 让 U2 电机持续转动，遥测 D=DRV_STATUS 随状态翻转：静止 D=84064000（stst bit31=1、CS_ACTUAL=6），转动 D=041B4000（stst=0、CS_ACTUAL=27、stealth bit14=1），bit26 otpw 全程保持 1 → U2 持续过温预警，U1 无报警 A=-；判据稳定成立
- **ST-Link SWO 评估**: 探针=精简 ST-Link/V2（VID_0483:PID_3748，UM1075 表4 确认 20pin SWO=pin13 TDO_SWO），但精简版仅引出 SWDIO/SWCLK/GND/VDD → **无 SWO 引脚，ITM/SWO 不可用**，维持 CAN 遥测为无 UART 调试通道
- **手记**: RM0090 尚未补录（.cl/datasheet 仅 TMC5160/电机/MOSFET），后续需要 STM32F407 引脚/外设依据时再补
