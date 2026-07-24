# EM-SKILL — 嵌入式项目开发管家

**EM-SKILL 是一个 Claude Code Skill，专为嵌入式 MCU 开发设计的人-AI 协作框架。**

核心特色：HVR 人机协作验证、三档分流（轻/中/重）、多工具链编译（Keil/CMake/GCC）、14 项并行代码审核、自动留痕。

---

## 快速安装

```bash
# 1. 克隆到 Claude Skills 目录
cp -r EM-SKILL ~/.claude/skills/em-skill

# 2. 进入你的嵌入式项目目录
cd your-project

# 3. 初始化项目
/em init my_project --type=embedded

# 4. 初始化工具链路径（首次）
/em initem
```

---

## 使用指南

### 1. 日常开发流程

#### 场景：新功能开发

```bash
/em new "添加 CAN 通信"
```

AI 会做三件事：
1. **三档分流** — 自动判断复杂度，推荐轻/中/重档
2. **模块联想** — 匹配已有模块库（ela_uart、ela_queue 等）
3. **启动讨论** — 重档需求走 5 阶段讨论

输出示例：
```
🆕 新功能: 添加 CAN 通信
   分配步骤: S3
   推荐档位: 重（deep）  理由: 涉及新外设（CAN）+ 协议栈
   其他档位: /em new ... --light | --std | --deep
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━
   输入 `继续` 采用推荐档位，或输入 `轻/中/重` 改档。
```

> **在 ≥3 子系统时**（如同时涉及通信+控制+测量），brainstorm 阶段会**自动启动并行子 Agent**——每个子系统由独立 AI 代理同时调研方案，然后汇总防冲突。

#### 场景：验证代码

```bash
/em verify s3
```

三件并行执行：
```
Agent-A: 编译（自动识别 Keil 或 CMake 工具链）
Agent-B: 静态分析（14 项规范检查 + 编译标志检查）
Agent-C: 代码审查（逻辑正确性 + 边界条件）
```

> 这个阶段 AI 还会自动检查项目是否启用了 `-Wall -Werror`（GCC）或等效的 Keil 警告标志。

#### 场景：硬件验证

```bash
# 人类烧录固件 → 观察物理现象 → 提交结果
/em result s3-通过

# 或：失败了提交现象描述
/em result s3-失败-LED不闪
```

通过后 AI 会自动：
- ✅ 更新 HVR 文件并推进下一步
- ✅ 自动留痕到项目核心文档（Require/*.lnk）
- ✅ 更新知识库索引
- ✅ 提示是否沉淀经验

---

### 2. 编译与工具链

#### 自动检测（日常推荐）

```bash
/em build
```

AI 自动检测项目特征：

| 检测信号 | 使用工具链 |
|---------|-----------|
| `*.uvprojx` / `*.uvproj` | Keil UV4 |
| `CMakeLists.txt` + arm-gcc | CMake + make/ninja |
| `Makefile` + `arm-none-eabi-` | CMake 兼容层 |
| 无信号 | 提示用户指定 |

#### 指定工具链

```bash
/em build --keil       # 强制 Keil 编译
/em build --cmake      # 强制 CMake 编译
/em build detect       # 只检测，不编译
```

#### 烧录与串口

```bash
/em flash       # OpenOCD 烧录（自动检测调试器）
/em serial      # 串口监控（抓取启动日志）
```

---

### 3. 代码审核

#### 并行审核（默认）

```bash
/em mode audit ela_pid
```

4 组子 Agent 同时检查 14 项规范：
```
Agent-1（命名组）: 函数/变量/类型/宏命名
Agent-2（注释组）: 文件头/保护名/函数注释
Agent-3（格式组）: 段标记/drv 区段/代码格式/Magic Number
Agent-4（安全组）: 头文件独立/宏命名/volatile
```

约 3 分钟出结果（传统串行约 10 分钟）。

#### 串行审核（降级）

```bash
/em mode audit ela_pid --serial
```

---

### 4. 知识库管理

```bash
# 查看所有需求文档
/em req

# 读取具体文档
/em req show ELACO_StepMotorTMC5160.md

# 读取 PDF 数据手册
/em req show TMC5160A_Datasheet.pdf

# 修改核心文档（自动留痕）
/em rq 在 CAN 协议部分添加命令码 0x07

# 重新生成索引
/em index
```

资料查找优先级（找到即停）：
```
1. 核心文档（Require/*.lnk）← 最优先
2. 知识库 debug/（学习模式）
3. Require/ 下其他 .md
4. Require/ 下 .pdf（内置 Docling/marker 引擎）
5. 问用户：需不需要上网搜？
```

---

### 5. 验证失败处理

如果验证不通过，直接告诉 AI 看到了什么现象：

```bash
/em result s1-a-失败-CAN总线无信号
```

AI 会自动执行：

```
🔴 验证结果: 失败

1. 更新 HVR → 失败 + 日志摘要
2. 🔄 状态: 🔁 返工中
3. 读取 logs/ 下的最新日志
4. 自动创建 problem-log.md 条目
5. 进入问题讨论:

   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━
   基于日志分析，可能原因：
     A. CAN 收发器未使能（最常见）
     B. 波特率不匹配（250k vs 125k）
     C. GPIO 复用功能未配置
   
   请确认或补充观察...
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

修复后重新走 verify → result 流程：

```bash
# 修改代码后
/em verify s1-a            # 重新验证
# 硬件验证通过后
/em result s1-a-通过        # 提交通过
# 原问题自动闭环
```

> 失败时 AI **不会擅自改代码**——它分析原因、列出可能方案、等你确认后再改。这是 HVR 的设计原则：**AI 提议，人决策。**

### 6. 学习模式（知识沉淀与检索）

学习模式插件提供交互式教学和知识库沉淀，**适用于所有项目类型**。

#### 启用学习模式

```bash
# 方式1：初始化时指定
/em init my_learning --type=learning

# 方式2：现有项目直接使用（首次会自动询问启用）
/em learn teach "STM32 TIM 定时器"
```

#### 交互式教学

```bash
# 主题模式：让 AI 调研并教学
/em learn teach "FreeRTOS 任务优先级与调度"

# 文档模式：基于数据手册生成课程
/em learn teach --doc TMC5160A_Datasheet.pdf

# 继续上次课程
/em learn teach continue
```

教学流程：讲解 → 示例 → 练习 → 反馈 → 复习

#### 知识库沉淀

每次 `/em result` 通过后，AI 会询问是否沉淀经验：

```bash
💡 是否将此次经验沉淀到知识库？(Y/n)
```

选择类型：

| 类型 | 用途 | 示例 |
|------|------|------|
| `debug` | 调试经验 | "CAN 总线无信号：检查收发器使能引脚" |
| `concept` | 技术要点 | "TMC5160 速度模式 vs 位置模式区别" |
| `snippet` | 代码片段 | "SPI DMA 循环收发模板" |

沉淀后自动归类到 `.em/learning/kb/`，下次遇到问题时优先搜索：

```bash
# 查看知识库
/em learn kb

# 搜索经验
/em learn kb search CAN 无信号

# 查看学习进度
/em learn status
```

---

### 7. 项目初始化

```bash
# 新项目
/em init motor_ctrl

# 存量代码接入
/em si /path/to/existing-project

# 恢复已有项目
/em rec
```

`/em init` 调用 `builder.py detect` 自动检测项目类型：

| builder.py 返回值 | 推荐类型 |
|---------|---------|
| `keil` | embedded |
| `cmake`（含交叉编译链）| embedded |
| `iar` / `esp_idf` / `platformio` | embedded |
| 全无 + 扫到 `.ioc`/`.ino`/`system_*.c` | embedded |
| 全无 | general |

---

### 8. 模块管理

模块分 A~E 五级（A=零移植，E=项目专属）：

```bash
# 列出可用模块
/em mode list

# 审核模块（14 项并行检查）
/em mode audit ela_queue

# 安装模块到项目（自动递归解析依赖）
/em mode install ela_pid
```

安装时自动：
- 解析模块依赖（如 ela_pid → ela_queue）
- 创建 ELA_LIB 目录结构
- 更新 elaco_main.h 的 include
- 14 项规范检查

---

## 新手场景速查

| 你的状态 | 执行 |
|---------|------|
| **全新项目** | `/em init my_project` → `/em new "第一个功能"` |
| **接手旧代码** | `/em si .` → `/em rec` |
| **写了一个文件要验证** | `/em verify s1` |
| **验证通过** | `/em result s1-通过` |
| **要加个小功能** | `/em new "修 BAUD 率计算 bug" --light` |
| **编译报错** | `/em build --keil`（或 `--cmake`）|
| **想导入现成模块** | `/em mode install ela_queue` |
| **要查数据手册** | `/em req show TMC5160A_Datasheet.pdf` |
| **验证失败** | `/em result s1-失败-CAN无信号` → AI 分析原因→修复→重新 verify |
| **沉淀经验** | `/em result` 通过后 → `y` → 选 `debug`/`concept`/`snippet` |
| **学习新知识** | `/em learn teach "FreeRTOS 调度"` |
| **忘记命令了** | `/em help` |

---

## 概念速览

### HVR 工作流（核心创新）

HVR（Human Verification Request）解决"AI 能写代码但摸不到硬件"的矛盾：

```
AI: 生成 HVR 文件 → 编译 → 烧录 → 抓串口日志
                                              ↓
人类: 执行物理操作 → 观察 LED/波形/电机 → 口述给 AI
                                              ↓
AI: 分析结果 → 更新 HVR → 推进/返工
```

### 三档分流

| 档位 | 适用 | 耗时 | 产出文件 |
|------|------|------|---------|
| **light** | bugfix、调参、单文件 | ~5 min | 1 个 quick-plan |
| **standard** | 跨模块特性 | ~15 min | brainstorm + milestones |
| **deep** | 新外设、协议栈、重构 | ~45 min | 5 阶段讨论文件 |

### 子 Agent 并行调度

| 场景 | 并行数 | 说明 |
|------|--------|------|
| 14 项代码审核 | 4 | 命名/注释/格式/安全四组同时跑 |
| ≥3 子系统 brainstorm | 3 | 每子系统独立 AI 调研方案 |
| verify 编译+分析+审查 | 3 | 编译/静态分析/代码审查同时 |

> 子 Agent 失败→自动降级串行，不阻断流程。

---

## 目录结构

```
EM-SKILL/
├── SKILL.md                     # 技能入口
├── README.md                    # 本文件
├── commands/                    # 命令定义（17 个通用命令）
│   ├── new.md / verify.md / mode.md / build.md / ...
├── workflows/                   # 工作流
│   ├── hvr-workflow.md
│   ├── new-light.md / new-standard.md
│   └── discussion-flow.md
├── references/
│   ├── ela_rules.md             # 完整编码规范（380+ 行）
│   └── ela_rules_quick.md       # 编码规范速查（≤70 行）
├── templates/                   # 状态文件模板
├── modules/                     # 模块库（A~E 五级）
│   ├── MODULES.md
│   └── ela_queue.c/h
├── plugins/                     # 插件
│   ├── embedded/                # 嵌入式插件（编译/烧录/串口）
│   └── learning/                # 学习模式插件（教学/知识库）
├── tools/
│   ├── build-dispatcher/        # 统一编译入口（Keil/CMake/GCC）
│   ├── build-keil/              # Keil 编译脚本
│   ├── flash-openocd/           # 烧录脚本
│   ├── serial-mcp/              # 串口 GUI + MCP server
│   └── serial-monitor/          # 串口 CLI 抓日志
├── docs/
│   ├── PLUGIN-SPEC.md           # 插件规范 v1.0
│   └── subagent-principles.md   # 子 Agent 调度原则
└── CHANGELOG.md
```

---

## 相关文档

| 想看什么 | 看哪个 |
|---------|--------|
| 全部命令 | `SKILL.md` |
| 快速开始 | 本文件 |
| 编码规范 | `references/ela_rules_quick.md` |
| 插件开发 | `docs/PLUGIN-SPEC.md` |
| 子 Agent | `docs/subagent-principles.md` |
| HVR 细则 | `workflows/hvr-workflow.md` |
| 模块库 | `modules/MODULES.md` |
