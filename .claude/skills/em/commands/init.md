# 命令: /em init (项目初始化)

> **通用核版本**：先选项目类型，嵌入式特征自动加载 embedded 插件流程。

## 功能
从零开始新项目，生成 `<STATE_DIR>/` 标准结构。

## 触发
```
/em init <项目名称>                # 自动检测类型，给推荐
/em init <项目名称> --type=general  # 强制通用
/em init <项目名称> --type=embedded # 强制嵌入式（加载 embedded 插件）
```

## 执行流程（总入口）

1. **【目录检测】** 当前目录已有 `.em/` 或 `.emv2/` → 提示「项目已初始化」+ 给 `/em rec` 建议
2. **【类型判定】**
   - 命令带 `--type=...` → 直接采用
   - 否则按下表启发式扫描，给推荐：

| 信号（任一命中）| 推荐类型 |
|------|---------|
| `*.uvprojx` / `*.uvproj` | embedded（Keil） |
| `*.ioc` | embedded（CubeMX） |
| `sdkconfig` + `main/CMakeLists.txt` | embedded（ESP-IDF） |
| `platformio.ini` | embedded（PlatformIO） |
| `*.ino` | embedded（Arduino） |
| `*.eww` / `*.ewp` | embedded（IAR） |
| `system_<stm32\|gd32\|ch32>f?xx.c` / `startup_*.s` | embedded |
| Makefile 含 `arm-none-eabi-` 等交叉编译链 | embedded |
| 上述均无 | general |

   - 输出推荐 + 让用户确认：
     ```
     📋 项目类型判定
        扫描结果: <匹配的特征，或"未命中"> 
        推荐类型: <general|embedded>
        ━━━━━━━━━━━━━━━━━━━━━━━━━━━━
        输入 `继续` 采用推荐，或 `general` / `embedded` 改选。
     ```

3. **【创建 `<STATE_DIR>/`】** 新项目默认 `.em/`：
   ```
   .em/
   ├── state.md           # 最小状态文件（rec 默认只读）
   ├── project.json       # { type, name, created, embedded?, plugins }
   ├── project-spec.md    # 项目规格单（最简骨架，仅 Meta + 步骤表）
   ├── decisions.md       # 决策日志（空表头）
   ├── problem-log.md     # 问题追踪（空表头）
   ├── sessions/          # 会话历史目录（每会话一文件）
   ├── discussion/        # 讨论目录
   ├── checkpoints/       # HVR 目录
   ├── history/           # 归档目录
   └── logs/              # 日志目录（嵌入式串口日志等）
   ```

4. **【按类型分支】**
   - **general**：到此结束 → 提示 `/em new <第一个功能>`
   - **embedded**：
     - 加载 `plugins/embedded/commands/initem.md`（工具初始化）
     - 加载 `plugins/embedded/workflows/chip-learning.md`（芯片选择 + chips.json 学习）
     - 写 `project.json.embedded = { chip, toolchain, interface }`
     - **创建 ELA_LIB 目录结构**：
       - 创建 `ELA_LIB/` 目录
       - 创建 `TEXT/` 目录（弱化测试文件夹，与 ELA_LIB 同级）
       - 从模板生成 `elaco_main.c` 和 `elaco_main.h`
       - 模板路径：`plugins/embedded/templates/elaco_main_template.c/h`
       - 日期自动替换为当前日期（YYYY-MM-DD 格式）
     - **修改 CubeMX main.c**：在 `USER CODE BEGIN 2` 区域添加 `elaco_main();` 调用
       - CubeMX `main.c` 保留 `main()` + 外设初始化，不修改其他内容
       - `elaco_main()` 提供主循环和应用逻辑
     - **配置 Keil 工程**：检测 `.uvprojx` 是否存在
       - 存在 → 自动执行 `keil-config` 工作流
       - 不存在 → 提示用户：
         ```
         ⚠️ 暂未检测到 Keil 工程文件 (.uvprojx)
            请在 Keil 中新建工程后再执行 /em keil-config
         ```
       - 将 `ELA_LIB/*.c` 添加到 .uvprojx 的 ELA_LIB 组
       - 将 `../ELA_LIB` 添加到 IncludePath
     - 完成后回到这里输出报告

4.5 **【加载项目知识库】**
   - 扫描 `Require/` 文件夹（存在时执行）
   - **检测开发文档快捷方式**:
     - 查找 `Require/*.lnk` 文件
     - 有 → 解析快捷方式目标，读取目标 `.md` 文件
     - 该文件是**项目核心文档**，包含：开发进度日志、CAN协议定义、寄存器配置、硬件设计参数等
     - 将其内容结构（行范围/章节）记入 `require-index.md`，便于按需定位
     - **无** → 输出提示:
       ```
       ⚠️ Require/ 下未找到 .lnk 快捷方式文件
          请将项目核心文档（开发日志+技术参数）的快捷方式放入 Require/（.lnk 格式）。
          该文件是项目最重要的参考，AI 编码时会按需查阅。
       ```
   - 对其他 `.md` 文件: 提取 section headers，生成行范围映射
   - 对 `.pdf` 文件: 调用内置 PDF 工具生成索引
     ```bash
     python tools/pdf_reader.py index Require/<文件>.pdf
     # 自动读取 PDF 目录结构，输出页码范围映射
     # 若工具未安装，先运行: python tools/pdf_reader.py install
     ```
   - 生成 `<STATE_DIR>/require-index.md`（≤50 行）
   - 写 `project.json.require_dir = "Require"`
   - 不存在 `Require/` → 创建空目录 + 提示放入文档

5. **【更新全局索引】** `~/.claude/embedded-projects-index.md`（沿用名称，含通用+嵌入式所有项目）

6. **【写 state.md】** 首次状态：
   - 当前步骤: `S0`（待 `/em new` 创建第一个步骤）
   - 下一步动作: `/em new <功能描述>`

7. **【输出初始化完成报告】**

## 输出格式

### general 项目

```
✅ 通用项目初始化完成

项目: <名称>
路径: <绝对路径>
类型: general
状态目录: .em/

📁 已创建文件:
  state.md / project.json / project-spec.md / decisions.md / problem-log.md
  sessions/ / discussion/ / checkpoints/ / history/ / logs/

━━━━━━━━━━━━━━━━━━━━━━━━━━━━
下一步:
  /em new <功能描述>   # 进入新功能开发（默认中档 superpower 风格）
━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### embedded 项目

```
✅ 嵌入式项目初始化完成

项目: <名称>
类型: embedded
芯片: <型号>
工具链: <Keil|IAR|GCC>
状态目录: .em/

📁 已创建文件: (同上)
🔌 已加载插件: plugins/embedded/ (PLUGIN.md)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━
下一步:
  /em initem    # 工具初始化（首次使用 / 配置工具路径）
  /em new ...   # 新功能开发
━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## 设计原则

- ✅ 类型先选，能力按需加载（披露式）
- ✅ 通用项目零嵌入式负担
- ✅ 嵌入式项目 init 时自动跑插件初始化流
- ✅ 全局索引统一管理（不区分类型）
- ✅ Require/ 知识库自动索引，按需加载不浪费 token
- ⛔ **文件缺失时禁止自动访问外部网页**，必须先问用户是否需要搜索

## 双轨制兼容（旧版回退）

新项目统一创建 `.em/`。所有命令读取项目状态用 `get_state_dir()`：

```python
def get_state_dir(project_root: str) -> str | None:
    em_dir   = os.path.join(project_root, '.em')
    emv2_dir = os.path.join(project_root, '.emv2')
    if os.path.isdir(em_dir):   return em_dir
    if os.path.isdir(emv2_dir): return emv2_dir
    return None
```

存量 `.emv2/` 项目可用 `/em migrate` 升级。

## 相关文件
- `commands/rec.md` — 恢复时也读 `project.json` 决定是否加载嵌入式插件
- `commands/migrate.md` — 存量 `.emv2/` → `.em/` 迁移
- `plugins/embedded/PLUGIN.md` — 嵌入式插件清单
- `plugins/embedded/commands/initem.md` — 嵌入式工具初始化
- `plugins/embedded/workflows/chip-learning.md` — 芯片学习/识别
