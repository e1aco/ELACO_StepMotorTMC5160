# 命令: /em new (新功能开发) — superpower 风格三档分流

## 功能
进入新功能开发流程。**借鉴 superpower 的「brainstorm → plan → execute」精神**，三档分流避免轻量需求被重流程拖累。

## 触发
```
/em new <功能描述>           # AI 推荐档位，用户确认
/em new <功能描述> --light   # 强制轻档
/em new <功能描述> --std     # 强制中档（默认）
/em new <功能描述> --deep    # 强制重档（原 5 阶段 disc）
```

## 三档总览

| 档位 | 适用 | 产出文件 | 时长 | 工作流 |
|------|------|---------|------|--------|
| **轻 light** | < 2h 工作量、单文件改动、bugfix、调参 | `quick-plan.md` (1) | ~5 min | `workflows/new-light.md` |
| **中 standard**（默认）| 跨模块特性、需设计但非系统级 | `brainstorm.md` + `milestones.md` (2) | ~15 min | `workflows/new-standard.md` |
| **重 deep** | 系统级、新外设、协议栈、状态机重构 | 5 个文件（split/req/hardware/brainstorm/milestones）| ~45 min | `workflows/discussion-flow.md`（沿用）|

## 档位推荐启发式

AI 收到 `<功能描述>` 后，按以下规则推荐：

| 信号 | 加分到 |
|------|--------|
| 描述 ≤ 30 字 | 轻 |
| 关键词：修复 / fix / 调整 / 优化 / 改进 / 重命名 | 轻 |
| 关键词：实现 / 接入 / 集成 / 添加模块 | 中 |
| 关键词：架构 / 系统 / 协议栈 / 状态机 / 重构 / 新硬件 | 重 |
| 描述含多个并列名词（"A、B、C 都要做"）| 中或重 |
| **嵌入式项目** + 涉及新外设/芯片 | 重（强制走硬件对齐阶段）|

**默认**: 中档。

## 执行流程（总入口）

1. **【状态目录】** `get_state_dir()` → `<STATE_DIR>`；不存在提示 `/em init`
2. **【步骤号分配】** 读 `<STATE_DIR>/state.md` 或 `project-spec.md` 步骤表，取最大 S + 1
3. **【档位选择】**
   - 命令带 `--light/--std/--deep` → 直接采用
   - 否则按启发式推荐，输出：
     ```
     🆕 新功能: <描述>
        分配步骤: S<N>
        推荐档位: <轻|中|重>   理由: <一句话>
        其他档位: /em new ... --light | --std | --deep
        ━━━━━━━━━━━━━━━━━━━━━━━━━━━━
        输入 `继续` 采用推荐档位，或输入 `轻/中/重` 改档。
     ```
4. **【模块联想】**（模块库匹配）
   - 读 `modules/MODULES.md`，扫描所有模块的**功能说明**和**关键词**

   **匹配策略（两阶段）**：

   **阶段一：关键词表匹配**（优先）
   ```
   需求描述中含以下关键词 → 联想对应模块：
   「电机/马达/Motor/PID/闭环/步进」 → ela_pid, ela_tmc5160
   「队列/缓冲/Buffer/Queue/FIFO」   → ela_queue
   「按键/Button/Key/输入/按钮」     → ela_button
   「串口/UART/Serial/通信」         → ela_uart
   ```
   命中 → 直接输出推荐。

   **阶段二：AI 语义联想兜底**（关键词表未命中时）
   - AI 逐条阅读 `MODULES.md` 中每个模块的**功能说明**和**等级**
   - 用自己的语义理解判断当前需求描述与哪个模块匹配
   - 示例：需求"需要做位置闭环控制" → 即使关键词表没有"闭环控制"，AI 也能从模块说明中联想到 `ela_pid`
   - 输出格式同关键词表匹配

   **输出推荐**：
   ```
   📦 模块联想：以下模块可能适用于此需求

     推荐 | 模块          | 等级 | 依赖        | 说明
     🔵   | ela_pid       | A    | ela_queue   | 增量 PID 控制器
     🔵   | ela_tmc5160   | C    | 无          | TMC5160 驱动

     输入 `y` 安装推荐模块，`n` 跳过，或指定 `ela_pid` 单选。
   ```
   - 用户确认后 → 检查 ELA_LIB 目录是否存在（不存在则创建并生成 elaco_main.c/h）→ 执行 `mode install`（含递归解析依赖，自底向上安装）
   - 安装结果记入讨论目录：
     ```
     ✅ 已安装: ela_queue → ELA_LIB/
     ✅ 已安装: ela_pid → ELA_LIB/
     📁 已创建 ELA_LIB 目录结构（含 elaco_main.c/h）
     ```
   - 跳过不影响后续流程，用户随时可以手动 `/em mode install`
   - 📝 **自动扩展关键词表**：AI 在阶段二（语义联想）命中模块后，**自动追加**新映射到阶段一的关键词表中：
     ```
     # 追加到关键词表（下次可直接命中）
     「温湿度/湿度/SHT30/温度传感器」→ ela_sht30
     ```
     用 Edit 工具直接更新本文件的关键词表段，下次命中无需重复语义联想。

5. **【加载对应工作流文件】**（披露式按需加载，不一次性灌入所有）
   - 轻 → 立即读 `workflows/new-light.md`
   - 中 → 立即读 `workflows/new-standard.md`
   - 重 → 立即读 `workflows/discussion-flow.md`（沿用 5 阶段）
5.5 **【加载编码规范】**（嵌入式项目时）
   - **必须加载** `references/ela_rules_quick.md`（~50 行精简速查）
   - 仅在项目 `project.json.type == "embedded"` 时加载
   - **所有生成的代码必须符合规范**，不符合则立即修正
5.75 **【编码前准备】**（嵌入式项目时，合并 drv 决策 + Keil 预配置）

   **A. drv 文件决策**
   - AI **必须**判断当前模块是否需要涉及引脚/外设配置：
     ```
     需求描述
       ↓
     是否涉及硬件操作（GPIO/SPI/UART/I2C/TIM/ADC/DAC/中断等）？
     ├── 否 → 单文件 ela_xxx.c/h（纯 hlp/usr，如 ela_queue、ela_pid）
     └── 是 → 拆分为两文件：
             ├── ela_xxx_drv.c/h  ← HAL 原语 + 引脚/外设宏定义
             └── ela_xxx_usr.c/h  ← 业务逻辑（include ela_xxx_drv.h）

     ⚠️ 不确定？→ 一律先按有硬件拆两文件，确认纯软件后再合并
     ```
   - 满足任意一条即需要 drv 文件：调用 HAL、读写寄存器、操作物理引脚、配置外设时序、涉及中断/DMA
   - 输出决策结果到讨论文件，明确列出文件结构和引脚依赖
   - 参考：`ela_tmc5160_drv.c/h` + `ela_tmc5160_usr.c/h` 的分拆模式

   **B. Keil 工程预配置**（Keil 项目时）
   - 检查 `.uvprojx` 是否已有 `ELA_LIB` 组和 `../ELA_LIB` IncludePath
   - 无 → 先初始化好组结构和路径（空组也可以）
   - 有 → 跳过，等代码生成后增量添加新文件

6. **【按工作流执行】** 详见对应 workflow 文件
   - **编码后自动动作**（Keil 项目且 **新增** 了 .c 文件时）：
     - 执行 `keil-config` 将新文件同步到 `.uvprojx` 的 ELA_LIB 组
     - 输出：`✅ ela_xxx.c 已添加到 .uvprojx ELA_LIB 组`
7. **【不再单独 keil-config】**（已在步骤 5.75B + 6 编码后自动动作中覆盖）
8. **【收尾】** 更新 `state.md`（下一步动作 = `/em verify s<N>`），写入 `project-spec.md` 步骤表

## 公共规则

- **步骤编号**：`S<数字>`，废弃不复用
- **讨论目录**：`<STATE_DIR>/discussion/<YYYYMMDD>-<slug>/`
- **进度文件**：`status.json` 标记当前阶段（轻档可省）
- **强制约束**：流程未完成（如重档 5 阶段没走完）禁止 `/em verify`/`/em result`

## 输出格式（确认阶段后）

```
🆕 S<N>: <功能描述>
档位:   <轻|中|重>
讨论ID: <YYYYMMDD>-<slug>

━━━━━━━━━━━━━━━━━━━━━━━━━━━━
<工作流首阶段提示，由对应 workflow 文件给出>
```

## 设计原则
- **superpower 精神**：先 brainstorm → 再 plan → 再 execute
- **三档分流**：避免轻量需求被重流程拖累
- **披露式加载**：每档独立 workflow 文件，按选档加载
- **现有重档保留**：原 5 阶段 disc 完整保留，零破坏
- **嵌入式自动加档**：涉及硬件外设自动推荐 deep（保留嵌入式严谨性）

## 相关文件
- `workflows/new-light.md` — 轻档流程（新）
- `workflows/new-standard.md` — 中档流程（新，brainstorm + milestones）
- `workflows/discussion-flow.md` — 重档 5 阶段流程（沿用）
- `commands/disc.md` — 单独触发讨论模式（可继续重档）
- `commands/state.md` — 步骤号读自 state.md
