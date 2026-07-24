# 命令: /em verify (步骤验证)

> **通用核版本**：流程控制、HVR 文件生成、commit 提议。
> 嵌入式项目自动加载 `plugins/embedded/workflows/verify-embedded.md` 注入编译/烧录/串口子流程。

## 功能
生成人工验证请求 (HVR)，提议 commit。

## 触发
```
/em verify s<编号>    # 如 /em verify s7 或 /em verify s7-a
```

步骤参数使用 `/em new` 分配的 S 编号。

## 执行流程（通用）

1. **【状态目录】** `get_state_dir()` → `<STATE_DIR>`
2. **【项目类型】** 读 `<STATE_DIR>/project.json` 的 `type` 字段
3. **【加载编码规范】**（嵌入式项目时）
   - **必须加载** `references/ela_rules_quick.md`（~50 行精简速查）
   - 仅在 `project.json.type == "embedded"` 时加载
   - **所有生成的代码必须符合规范**，不符合则立即修正
4. **【更新状态】**
   - `state.md`: 当前步骤 → `S<N>` 🔄 验证中
   - `project-spec.md` 步骤表对应行状态同步
5. **【生成 HVR】** 见下方「HVR 模板」

5.5 **【编译时检查（编译器标志）】**（嵌入式项目且在并行执行通道启用前执行）

   在编译前，先检查项目的编译器标志配置：

   ```
   ━━━ 编译器标志检查 ━━

   A. GCC 标志检查（CMake 项目）
      □ -Wall -Wextra ......... ✅ / ⚠️ 推荐添加
      □ -Werror ............... ✅ / ⚠️ 推荐添加（警告升错误）
      □ -Wunused ............. ✅ / ⚠️ 推荐添加
      □ -Wconversion ......... ✅ / ⚠️ 推荐添加（检测隐式类型转换）

   B. Keil 等效标志（Keil 项目）
      □ --diag_warning ...... ✅ / ⚠️ 推荐添加
      □ --diag_error ........ ✅ / ⚠️ 推荐添加
   ━━━━━━━━━━━━━━━━━━━━━━━━━━
   ```

   **产出**：结果写入 `<STATE_DIR>/checkpoints/compiler-flags_<step>.md`

   > MISRA-C 子集检查已合并到 Agent-B（静态分析），不在本步骤重复执行。
6. **【并行执行通道】**（deep 档 verify 时启用，子步骤验证可跳过）

   以下三步**互不依赖**，通过子 Agent 并发执行：

   ```
   主 Agent: 分配 3 组并行任务
     ├─ Agent-A: 编译（调用 build-dispatcher，自动识别工具链）
     ├─ Agent-B: 静态分析（14 项规范检查 + MISRA-C 子集 + 编译警告检查）
     └─ Agent-C: 回顾性代码审查（逻辑正确性 + 边界条件 + 资源竞争）
   ```

   各 Agent 独立写入对应文件：

   ```
   logs/build_<step>_<timestamp>.log      ← Agent-A
   checkpoints/audit_<step>.md            ← Agent-B
   checkpoints/review_<step>.md           ← Agent-C
   ```

   **汇总规则**：
   - 三路完成 → 汇总到 HVR 的「自动化执行记录」区段
   - 任一路失败 → 该路标记 ❌ + 错误摘要计入 HVR，**不阻断其他路**
   - 全部失败或环境不支持并行 → 降级为串行

   详见 `docs/subagent-principles.md`

6. **【嵌入式注入】** 如 `type == "embedded"` → 加载 `plugins/embedded/workflows/verify-embedded.md` 执行编译/烧录/串口三连，结果记入 HVR 的「嵌入式执行记录」区段

   > **并行兼容**：如果步骤 6 中 Agent-A（编译）已完成，此处**跳过编译**，直入烧录+串口。
7. **【输出验证清单】** 列出待用户确认的检查点
7.5 **【Keil 工程同步】**（Keil 项目且有新增 .c 文件时）
   - 扫描 `ELA_LIB/` 是否有**新增** `.c` 文件（对比 git 或当前会话记录）
   - 有新增 → 执行 `keil-config` 工作流（见 `plugins/embedded/workflows/keil-config.md`）
   - 无新增 → 跳过
   - 输出同步结果：
     ```
     🔧 Keil 工程同步:
       ✅ 无新增 .c 文件，跳过
       或
       ✅ ela_xxx.c  已添加到 .uvprojx ELA_LIB 组
     ```
7.6 **【文档同步检查】**（修改协议相关代码时）
   - 检查本次修改是否涉及 CAN 协议、寄存器配置、接口定义等
   - 涉及 → 同步更新 `Require/*.lnk` 指向的协议文档
   - 不涉及 → 跳过
   - 输出检查结果：
     ```
     📝 文档同步:
       ✅ 无协议相关修改，跳过
       或
       ✅ ELACO_StepMotorTMC5160.md 已更新（新增命令码 0x07/0x08）
     ```
8. **【提议 commit】** 见下方「commit 提议」

## HVR 文件

- 路径：`<STATE_DIR>/checkpoints/HVR-<步骤>-<序号>.md`
- **模板选择**（按 `project.json.type` 自动）：
  - `general` → `templates/hvr-template.md`（通用模板，无嵌入式三连）
  - `embedded` → `plugins/embedded/templates/hvr-template-embedded.md`（含「嵌入式执行记录」表 + 工具执行记录 + 共同决策段）
- 流程细则与字段说明：`workflows/hvr-workflow.md`

## commit 提议（S10-D 集成）

HVR 文件 + 工具执行结果记录完成后，AI **不直接 commit**，而是输出"提议"：

```
━━━━━━━━━━━━━━━━━━━━━━━━━━
💡 提议 commit  (S10-D Git 集成)
━━━━━━━━━━━━━━━━━━━━━━━━━━
建议 commit message:
  [S<step>] feat: verify <步骤描述> with HVR-<序号>

待提交文件:
  M  <STATE_DIR>/checkpoints/HVR-<步骤>-<序号>.md
  M  <STATE_DIR>/state.md
  M  <STATE_DIR>/project-spec.md

确认提交？[y/n/edit]
━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### 用户响应

| 输入 | 行为 |
|------|------|
| `y` / `确认` | `git add` + `git commit -m "..."` |
| `n` / `取消` | 跳过 |
| `edit` / `修改为: ...` | 用新 message 重提议 |
| `amend` | 加入上一次 commit（需用户已 commit 过） |

### 执行约束

- ✅ 允许 `git status` / `git add` / `git commit -m "..."`
- ❌ 禁止 `git push`（必须拒绝并提示手动 push）
- ❌ 禁止 `--no-verify` / `--force` 等破坏性选项
- ❌ 禁止 `git commit --amend` 改写历史

### 提议规则

- `commit message` 必须以 `[S<n>]` 开头
- type 推断：HVR 通过 → `feat`；修复 → `fix`；仅文档 → `docs`
- subject ≤ 50 字符；body 可选（解释 HVR 关键结论）

### 跳过条件

- 工作区无变更
- 仅日志/构建产物（应在 `.gitignore` 中）
- 用户明确说"暂不提交"

## 相关文件
- `workflows/hvr-workflow.md` — HVR 模板与流程图
- `plugins/embedded/workflows/verify-embedded.md` — 嵌入式 verify 子流程（仅 type=embedded 加载）
- `commands/result.md` — 验证结果记录
