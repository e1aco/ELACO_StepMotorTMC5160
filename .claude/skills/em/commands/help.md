# 命令: /em help (帮助)

## 功能
显示帮助信息

## 触发
```
/em help [命令]
```

## 无参数时

所有命令已记录在 `SKILL.md` → **通用命令（17 个）** + **知识库命令（8 个）** + **插件命令** 三节。

### 快速参考

| 场景 | 命令 | 说明 |
|------|------|------|
| **恢复项目** | `/em rec` | 只读 state.md（≤50 行），按需查详情 |
| **新功能** | `/em new <描述>` | AI 推荐三档分流（轻/中/重） |
| **讨论** | `/em disc [步骤]` | 5 阶段讨论流程（重档需求） |
| **验证** | `/em verify s<N>` | 生成 HVR + 编译/烧录/串口 + commit 提议 |
| **提交结果** | `/em result s<N>-通过/失败` | 自动留痕 + 推进下一步 |
| **状态** | `/em stat [-v]` | 极简/详细状态 |
| **模块管理** | `/em mode <list\|audit\|add\|install>` | 14 项审核并行化 |
| **知识库** | `/em req [show <文件>]` | 查看/读取需求文档 |

### 新增强项（v3.4+）

```
并行审核:
  /em mode audit <模块>              ← 默认并行（4 组子 Agent）
  /em mode audit <模块> --serial     ← 传统串行

多工具链编译:
  /em build                           ← 自动检测 Keil/CMake/GCC
  /em build --keil                    ← 强制 Keil
  /em build --cmake                   ← 强制 CMake
  /em build detect                    ← 只检测工具链

编译时检查（verify 自动执行）:
  ✅ 编译器标志检查（-Wall -Werror 等）
  ✅ Cppcheck / PC-Lint 集成
  ✅ MISRA-C 子集 6 项检查

初始化:
  /em init <name>                     ← 自动检测 Keil/CMake/Makefile
```

### 嵌入式插件

```
/em initem         工具初始化（路径注册）
/em build          编译（自动检测工具链）
/em flash          烧录（OpenOCD）
/em serial         串口监控
```

## 有参数时

显示指定命令的详细帮助：

```
/em help rec        # rec 瘦身策略
/em help new        # new 三档分流 + 子 Agent 并行调度
/em help verify     # verify 流程 + 编译时检查 + 并行执行通道
/em help build      # 多工具链编译
/em help mode       # 14 项并行审核
/em help sessions   # 会话浏览
/em help migrate    # .emv2/ → .em/ 深度迁移
/em help migrate-state # 一键生成 state.md
```

## Git 集成（S10-D）

```
git 工作流:
  tools/git-changelog/        CHANGELOG 自动生成（Python，零依赖）
  arch (主步骤完成)           自动打 tag + 更新 CHANGELOG
  verify (HVR 完成)           提议 commit（用户确认后执行）
  problem-log close           提议 commit（用户确认后执行）

手动生成 CHANGELOG:
  python EM-SKILL/tools/git-changelog/changelog_gen.py
    --from <tag> --to <ref> --version <ver> --dry-run

Git 权限（initem.md 配置）:
  ✅ status / diff / log / add / commit / checkout -b / tag
  ❌ push（禁止，user 手动推）
```

## 设计约定

| 约定 | 说明 |
|------|------|
| 步骤编号 | `S<N>` 编号，废弃不复用 |
| 讨论目录 | `<STATE_DIR>/discussion/<YYYYMMDD>-<slug>/` |
| 状态目录 | `.em/` 优先，回退 `.emv2/` |
| 编码规范 | `references/ela_rules_quick.md` 编码前必读 |
| 子 Agent | 仅≥3 子系统或 14 项审核时启用，失败自动降级串行 |
| 外部搜索 | ⛔ 禁止自动访问，必须先问用户 |

## 工作流细则

| 工作流 | 文件 |
|--------|------|
| HVR 工作流 | `workflows/hvr-workflow.md` |
| 讨论流程（重档）| `workflows/discussion-flow.md` |
| new 轻档 | `workflows/new-light.md` |
| new 中档 | `workflows/new-standard.md` |
| 子 Agent 调度 | `docs/subagent-principles.md` |

## 嵌入式插件

| 资源 | 文件 |
|------|------|
| 插件清单 | `plugins/embedded/PLUGIN.md` |
| 嵌入式 verify 子流程 | `plugins/embedded/workflows/verify-embedded.md` |
| 芯片学习 | `plugins/embedded/workflows/chip-learning.md` |
| 嵌入式 HVR 模板 | `plugins/embedded/templates/hvr-template-embedded.md` |
| 统一编译入口 | `tools/build-dispatcher/scripts/builder.py` |
