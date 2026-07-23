# 命令: /em req (知识库管理)

## 功能
查看和管理 Require/ 文件夹下的需求文档和参考资料。

## 触发
```
/em req              # 列出所有文档
/em req show <文件>  # 读取某个文档（或指定行/页范围）
/em req index        # 重新生成索引
/em req install      # 安装 PDF 读取依赖
```

## 工具位置
PDF 读取工具: `tools/pdf_reader.py`（基于 marker 37.7k stars，最高精度）

## 执行流程

### /em req（列出文档）
1. 读 `<STATE_DIR>/require-index.md`（若存在）
2. 输出文档清单表格 + 常用速查区
3. 提示: `/em req show <文件名>` 查看详情

### /em req show <文件名>
1. 读 `<STATE_DIR>/require-index.md` 定位目标文件
2. 根据文件类型:
   - `.md` / `.lnk` → 读取对应行范围（默认全部，可指定 `--from N --to M`）
   - `.pdf` → 调用 `tools/pdf_reader.py`:
     ```
     # 自动选择引擎（推荐，优先 Docling）
     python tools/pdf_reader.py convert Require/<文件> --pages <范围> --engine auto

     # 使用 Docling 引擎（更好的表格/代码提取）
     python tools/pdf_reader.py convert Require/<文件> --pages <范围> --engine docling

     # 使用 marker 引擎（默认，支持图片提取）
     python tools/pdf_reader.py convert Require/<文件> --pages <范围>

     # 快速读取（PyMuPDF 备用）
     python tools/pdf_reader.py extract Require/<文件> --pages <范围>

     # 全文搜索
     python tools/pdf_reader.py search Require/<文件> "关键词"
     ```
3. 输出内容

### /em req index（重建索引）
1. 扫描 `Require/` 文件夹
2. 对 `.md` 文件: 提取 section headers，生成行范围映射
3. 对 `.lnk` 文件: 解析快捷方式目标，按 `.md` 处理
4. 对 `.pdf` 文件: 调用 `tools/pdf_reader.py index`:
   ```
   python tools/pdf_reader.py index Require/<文件>.pdf
   ```
   该命令自动读取 PDF 目录结构，生成页码范围映射
5. 生成 `<STATE_DIR>/require-index.md`
6. 输出: `✅ 索引已更新: N 个文档`

### /em req install（安装依赖）
```
python tools/pdf_reader.py install
```
安装 marker-pdf + pymupdf。可选参数:
- `--docling`: 安装 Docling 引擎（更好的表格/代码提取）
- `--use-llm`: 安装 LLM 增强支持

## 索引生成规则

| 文件类型 | 处理方式 |
|----------|----------|
| `*.lnk` | **核心文档**：解析 Windows 快捷方式 → 读取目标 `.md`。包含开发进度 + 技术参数（协议/寄存器/硬件），是项目最重要的参考 |
| `*.md` | 扫描 `#` / `##` / `###` 标题，记录行号范围 |
| `*.pdf` | 调用 `pdf_reader.py index` → 自动提取目录结构 + 页码范围 |
| 其他 | 仅记录文件名和大小 |

**开发文档检测**: 若 `Require/` 下无 `.lnk` 文件 → 生成索引时输出提示:
```
⚠️ Require/ 下未找到 .lnk 快捷方式文件
   请将项目开发文档的快捷方式放入 Require/ 文件夹（.lnk 格式）。
   该文件用于 AI 自动留痕（每次验证通过后追加开发进度）。
```

## PDF 读取精度说明

| 引擎 | 命令 | 精度 | 速度 | 适用场景 |
|------|------|------|------|----------|
| **marker (默认)** | `convert` | 高 (76%+) | 中 | 通用技术文档、图片提取 |
| **Docling** | `convert --engine docling` | 高 | 中 | 表格密集型文档、代码块、中文文档 |
| **自动选择** | `convert --engine auto` | 高 | 中 | 推荐：优先 Docling，fallback 到 marker |
| **marker + LLM** | `convert --use-llm` | 最高 | 慢 | 复杂表格、跨页合并、公式 |
| **PyMuPDF** | `extract` | 中等 | 快 | 快速浏览、简单文本 |

**推荐**:
- 一般技术文档: `convert --engine auto`（自动选择最佳引擎）
- 表格密集型文档（寄存器表、引脚定义）: `convert --engine docling`
- 需要最高精度: `convert --use-llm`（LLM 增强）

**安装 Docling（可选）**:
```bash
python tools/pdf_reader.py install --docling
```

## 设计原则
- 索引 ≤ 50 行，控制 token 消耗
- 详细内容按需加载，不预读
- PDF 用 marker 引擎保证精度
- 文档变更后需手动 `/em req index` 更新

## 文件缺失处理规则

**严禁自动去网页查找**。当文件读取失败或缺失时，必须先问用户：

```
⚠️ 无法读取: <文件名>
   原因: <具体原因: 文件不存在/PDF 解析失败/依赖未安装>

   建议操作:
   1. 检查文件路径是否正确
   2. 运行 `/em req install` 安装 PDF 依赖
   3. 手动将文件放入 Require/ 文件夹

   是否需要我到网上搜索相关资料？[y/n]
```

- 用户确认 `y` → 才能用 webfetch/websearch 搜索
- 用户确认 `n` 或未回复 → 停止，不搜索
- **任何情况下都不允许未经确认就自动访问外部网页**

## 资料查找优先级

当需要查找技术参数（协议、寄存器、引脚、配置等）时，按以下顺序：

```
1. 项目核心文档（.lnk 目标的 .md 文件）← 优先，最全最快
   ↓ 找不到
2. Require/ 下的其他 .md 文件
   ↓ 找不到
3. Require/ 下的 .pdf 文件（调用 pdf_reader.py）
   ↓ 找不到
4. 问用户是否需要网上搜索
```

**原因**: 核心文档已包含项目定制的参数（CAN协议、寄存器映射、硬件配置），比原始 PDF 更精准。

## 相关文件
- `tools/pdf_reader.py` — PDF 读取工具（marker + PyMuPDF）
- `templates/require-index.md` — 索引模板
- `commands/rec.md` — 恢复时加载索引
- `commands/init.md` — 初始化时扫描 Require/
