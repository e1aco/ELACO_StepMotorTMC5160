# 命令: /em build (编译)

## 功能
调用项目的编译工具链编译固件。自动检测 Keil/CMake/GCC。

## 触发
```
/em build                          # 自动检测工具链
/em build --keil                   # 强制 Keil UV4
/em build --cmake                  # 强制 CMake/GCC
/em build detect                   # 只检测工具链，不编译
```

## 调用方式

### 方式1：自动检测（推荐）
```bash
python EM-SKILL/tools/build-dispatcher/scripts/builder.py \
  --project <项目目录> \
  --skill-dir EM-SKILL
```

### 方式2：强制 Keil
```bash
python EM-SKILL/tools/build-dispatcher/scripts/builder.py \
  --project <项目目录> \
  --keil
```

### 方式3：强制 CMake/GCC
```bash
python EM-SKILL/tools/build-dispatcher/scripts/builder.py \
  --project <项目目录> \
  --cmake
```

## 工具链检测

AI 调用 builder.py 检测当前项目：

| 检测信号 | 判定工具链 |
|---------|-----------|
| `*.uvprojx` / `*.uvproj` | keil |
| `CMakeLists.txt` | cmake |
| `Makefile` + `arm-none-eabi-` | cmake |
| `sdkconfig` | esp-idf（预留） |
| `platformio.ini` | platformio（预留） |

## 参数来源

| 参数 | 来源 |
|------|------|
| `--project` | 当前工作区目录 |
| `--target` | 由 AI 根据项目设置确定 |
| 工具链路径 | 由 `/em initem` 注册（Keil UV4 路径等） |

## 结果处理

AI 从 builder.py 输出中提取以下字段记录到 HVR：

| 字段 | 作用 |
|------|------|
| 编译状态 | ✅ 成功 / ❌ 失败 |
| 工具链 | keil / cmake / ... |
| 错误数/警告数 | `错误: N  警告: N` |
| 产物路径 | `产物: file.elf (N KB)` |

## 自动决策

**编译成功 → 自动进入烧录流程**（AI 连续执行，用户只需观察物理现象）

AI 按以下顺序连续执行：

1. **编译** → 成功则自动进入步骤 2
2. **烧录** → 成功则自动进入步骤 3
3. **串口** → 抓取启动日志，用户观察物理现象并口述结果

```
编译(AI执行) → 烧录(AI执行) → 串口监控(AI抓日志) → 用户口述观察结果
```

**编译失败** → 读取编译日志 → 分析错误 → 请求用户修复

## 常见错误

- ❌ 未检测到工具链 → 运行 `/em build detect` 查看检测结果，或 `--keil` / `--cmake` 指定
- ❌ 工具链路径错误 → 运行 `/em initem` 重新配置
- ❌ 编译错误 → 显示错误行号和内容，分析原因

## 相关文件
- `EM-SKILL/tools/build-dispatcher/scripts/builder.py` - 统一编译入口
- `EM-SKILL/tools/build-dispatcher/scripts/cmake_builder.py` - CMake/GCC 编译脚本
- `EM-SKILL/plugins/embedded/tools/build-keil/scripts/keil_builder.py` - Keil 编译脚本（向后兼容）
- `EM-SKILL/plugins/embedded/commands/flash.md` - 烧录说明
- `EM-SKILL/plugins/embedded/commands/serial.md` - 串口监控说明
