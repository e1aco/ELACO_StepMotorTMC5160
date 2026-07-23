---
name: em-skill
description: 项目开发管家 - 通用核（HVR 工作流 + state.md 瘦身 + new 三档分流 + Require 知识库 + 内置 PDF 读取）+ 双插件架构（embedded 嵌入式 + learning 学习模式）。支持通用/嵌入式/学习三类项目。
version: 3.4.0
---

# EM-SKILL

> 项目开发管家 | 通用核 + 嵌入式插件 + 学习模式 | superpower 风格 new 三档分流

你接收到的参数：`$ARGUMENTS`

---

## 快速开始

```
1. /em help              # 看所有命令
2. /em rec               # 恢复当前项目（只读 state.md，≤50 行）
3. /em new <描述>        # 新功能开发（AI 推荐档位）
```

**首次进入项目**：

| 场景 | 命令 |
|------|------|
| 全新项目 | `/em init <name>` |
| 存量项目（无 `.em/`）| `/em si <path>` |
| 恢复已有项目 | `/em rec` |
| 旧版 `.emv2/` 升级 | `/em migrate` |
| 老项目体感瘦身 | `/em migrate-state` |

---

## 通用命令（17 个）

| 命令 | 用途 |
|------|------|
| `/em rec` | **恢复项目**（只读 state.md ≤50 行） |
| `/em stat` | 查看状态（默认极简；`-v` 全景） |
| `/em sessions` | 浏览会话历史（按需） |
| `/em init` | 初始化项目（自动识别类型） |
| `/em si` | 存量接入 |
| `/em new` | **新功能开发**（三档分流：轻/中/重） |
| `/em disc` | 进入讨论模式（重档独立触发） |
| `/em verify` | 步骤验证 + HVR + commit 提议 |
| `/em result` | 记录验证结果 |
| `/em sw` | 跨项目切换 |
| `/em arch` | 归档已完成步骤 |
| `/em sum` | 生成上下文摘要 |
| `/em pi` | 项目索引 |
| `/em gi` | 全局索引 |
| `/em help` | 帮助 |
| `/em migrate` | `.emv2/` → `.em/` 深度迁移 |
| `/em migrate-state` | 一键生成 state.md（瘦身） |

### 知识库命令

| 命令 | 用途 |
|------|------|
| `/em req` | 列出 Require/ 文档 |
| `/em req show <文件>` | 读取文档内容（PDF 用 marker 高精度引擎） |
| `/em req install` | 安装 PDF 读取依赖 |
| `/em rq <内容>` | 修改需求文档（.lnk 核心文档或其他文件） |
| `/em index` | 更新知识库索引 |
| `/em mode list` | 列出可复用模块 |
| `/em mode add <模块>` | 从模块库导入模块到 ELA_LIB/ |
| `/em mode audit <模块>` | 按规则审核模块 |

> **子命令路由约定**：AI 执行任一通用命令时，读取 `commands/<cmd>.md`。
> 通用核不维护命令-文件路由表，约定即可（统一前缀 `commands/`）。

### 插件命令

插件列表见 `plugins/INDEX.md`，每个插件声明自己的命令和工作流。
命令匹配：直接匹配（`build`）或前缀拼接（`learn teach` → `learn-teach`）。

---

## 项目类型

EM-SKILL 提供三类项目支持：

### 通用项目（默认）
通用软件开发，走 HVR 三档分流（轻→quick-plan / 中→brainstorm+milestones / 重→5 阶段 disc）。
详见 `commands/new.md`

### 嵌入式项目
触发 `/em initem` 或 `/em build/flash/serial` 时懒加载，注入烧录/串口/编译子流程。
详见 `plugins/embedded/PLUGIN.md`

### 学习模式项目
触发 `/em learn teach/kb/status` 时懒加载，交互式教学 + 知识库沉淀检索。
详见 `plugins/learning/PLUGIN.md`

### Require 知识库（通用核内置）

所有项目类型共享，零额外依赖（PDF 工具内置于 `tools/`）。

- **`Require/` 文件夹**：存放项目需求文档、数据手册、参考资料
- **`require-index.md`**：轻量索引（≤50 行），`/em rec` 时自动加载
- **`.lnk` 快捷方式**：Require/ 下的 `.lnk` 文件是**项目核心文档**，包含开发进度 + 技术参数（CAN协议、寄存器配置、硬件设计等），`/em result` 通过后自动追加进度留痕
- **内置 PDF 读取**：`tools/pdf_reader.py`（基于 marker 37.7k stars）
  - 最高精度 PDF→Markdown 转换（表格/公式/多栏布局）
  - 可选 LLM 增强模式
  - 无需安装外部 skill

详见：[`commands/req.md`](commands/req.md)

### ELA_LIB 编码规范（按需加载）

嵌入式项目代码规范，**不加载到 `/em rec`**，仅在写代码时按需读取。

| 文件 | 行数 | 何时加载 |
|------|------|----------|
| `references/ela_rules_quick.md` | ~50 行 | `/em new`、`/em verify` 时自动加载（精简速查） |
| `references/ela_rules.md` | 339 行 | 需要细节时按需加载（完整规范） |

**设计原则**: rec 不读 → new/verify 读精简版 → 需要细节再读完整版。省 ~350 行 token。

### 模块复用

模块库（`modules/MODULES.md`）提供 A~E 五级模块（A=零 HAL 直接复用，E=项目专属）。
安装自动递归解析依赖。审核/入库/安装见 `/em mode`。
详见 `commands/mode.md` | `modules/MODULES.md`

---

## 状态目录布局

```
<STATE_DIR>/.em/
├── state.md / require-index.md / project.json / project-spec.md
├── decisions.md / problem-log.md
├── sessions/       # 每会话一文件
├── discussion/     # <YYYYMMDD>-<slug>/{quick-plan,brainstorm,milestones,split,...}.md
├── checkpoints/    # HVR 文件
├── history/        # 归档
└── logs/           # 串口/编译日志
```

## 全局约束

### 资料查找优先级

查找技术参数时，按以下顺序，找到即停：

```
1. 项目核心文档（.lnk 目标的 .md）← 优先，最精准
2. 知识库 debug/ — 之前踩过的坑（如已启用学习模式）
3. Require/ 下的其他 .md 文件
4. Require/ 下的 .pdf 文件（pdf_reader.py）
5. 问用户是否需要网上搜索
```

### 禁止自动访问外部网页

文件读取失败或缺失时，**必须先问用户**：

```
⚠️ 无法读取: <文件名>
   原因: <具体原因>

   是否需要我到网上搜索相关资料？[y/n]
```

- 用户确认 `y` → 才能用 webfetch/websearch
- 未确认 → 停止，不搜索

### require-index.md 维护规则

`require-index.md` 是知识库入口，控制在 ≤50 行，`/em rec` 自动加载。

**触发更新**（任一即执行 `/em index`）：

| 触发点 | 自动/手动 |
|--------|-----------|
| `/em result` 通过 + 留痕后 | ✅ 自动（result.md step 11） |
| `/em rq` 修改核心文档后 | ✅ 自动（rq.md step 4） |
| 手动新增/删除 Require/ 文件 | ⚡ 手动 `/em index` |
| PDF 内容变更 | ⚡ 手动 `/em index` |

**索引内容结构**（严格按模板 `templates/require-index.md`）：

```markdown
## 文档清单
| 文件 | 类型 | 摘要 |          ← 所有 Require/ 文件

## 内容定位
### <核心文档.md>                         ← .lnk 目标
| 行范围 | 内容 |                         ← ## 章节标题 + 行号

### <数据手册.pdf>
| 页范围 | 内容 |                         ← PDF 目录/章节
```

**行范围映射规则**：
- `.md` 文件：按 `##`/`###` 标题分节，记录 `L12-L35` 格式的行号范围
- 留痕追加内容后，**后续章节的行号偏移必须重新计算**
- `.lnk` 核心文档优先，排在文档清单最前
- 超过 50 行时，只保留最新 5 个文档的定位 + 常用速查（删除旧文档定位）

**未找到 `.lnk` 时不阻塞**：无快捷方式文件时跳过留痕，不阻断流程。

### 代码规范最高优先级

**所有生成的代码必须严格符合 ELA_LIB 编码规范**（`references/ela_rules.md`）。这是最高优先级规则，不可妥协。

**执行要求**：
1. **生成代码前**：必须加载 `references/ela_rules_quick.md`（嵌入式项目）
2. **生成代码时**：严格遵循命名、注释、格式、分层等所有规范
3. **生成代码后**：必须进行 14 项规范检查（`/em mode audit` 流程）
4. **不符合规范的代码**：必须立即修正，禁止提交

**关键规范速查**：
- 文件：`ela_` 前缀
- 函数：`ela_模块_动作_细节`（对外），`模块_动作_细节`（static）
- 变量：`g_`（全局），`s_`（静态），`g_` + `_st`（结构体全局）
- 注释：`/**** @输入/@输出/@说明 ****/` 格式
- 分层：hlp/drv/usr/cac 区段，只有 drv 能碰 HAL
- 格式：4 空格缩进，Egyptian 大括号，≤84 字符行宽，CRLF

### Keil 工程文件同步（嵌入式项目强制）

**凡是 Keil 项目（检测到 `.uvprojx` / `.uvproj`），每次生成新代码文件时，必须同步到 Keil 工程：**

```
新增 .c 文件后
  ↓
执行 keil-config 工作流：
    1. 扫描 ELA_LIB/*.c
    2. 把新 .c 添加到 .uvprojx 的 ELA_LIB 组（只增不删）
    3. 确认 IncludePath 包含 ../ELA_LIB
```

**触发节点**（任一满足即执行）：
1. `/em new` 生成新模块后 ← 已有，保持
2. 编码阶段（plan → verify 之间）AI **创建**了新 .c 文件 ← 新增，立即执行
3. `/em verify` 验证通过，涉及**新文件**时 ← 新增，自动检查并提示

**执行方式**：
- AI 直接调 `keil_config.py`（注册在 `plugins/embedded/tools/keil-config/`）
- 命令：`python <脚本路径>/keil_config.py --scan <项目目录>`
- 脚本不可用时，输出操作步骤让用户手动执行 `/em keil-config`

**关键规则**：
- `.h` 文件不加入工程组（通过 IncludePath 自动找到）
- 只增不删，不修改 ELA_LIB 组外的任何内容

---

## 详细文档

commands/  workflows/  templates/  plugins/  tools/git-changelog/

---

查看详细: `/em help <命令>`
