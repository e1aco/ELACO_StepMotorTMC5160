# 命令: /em index (更新知识库索引)

## 功能
重新扫描 Require/ 文件夹，更新 `require-index.md` 索引文件。

## 触发
```
/em index              # 更新所有文档索引
/em index <文件名>     # 重新索引指定文件
```

## 执行流程

1. 扫描 `Require/` 文件夹下所有文件
2. 对 `.lnk` 文件: 解析快捷方式目标 → 读取目标 `.md` → 提取章节标题和行范围
3. 对 `.md` 文件: 提取 `#` / `##` / `###` 标题，记录行号范围
4. 对 `.pdf` 文件: 调用 `tools/pdf_reader.py index Require/<文件>.pdf`
5. 生成/更新 `<STATE_DIR>/require-index.md`
6. 输出: `✅ 索引已更新: N 个文档`

## 何时需要更新

| 场景 | 说明 |
|------|------|
| `/em rq` 修改文档后 | 自动触发 |
| `/em result` 留痕后 | 自动触发 |
| 手动添加/删除 Require/ 文件 | 需手动执行 `/em index` |
| PDF 文件内容变化 | 需手动执行 `/em index` |

## 索引内容

```markdown
# Require 知识库索引

## 文档清单
| 文件 | 类型 | 摘要 |

## 内容定位
### 核心文档（.lnk 目标）
| 行范围 | 内容 |
### TMC5160A_Datasheet_Rev1.14.pdf
| 页范围 | 内容 |

## 常用速查
<!-- 高频参数直接放这里 -->
```

## 相关文件
- `templates/require-index.md` — 索引模板
- `commands/req.md` — 知识库管理
- `tools/pdf_reader.py` — PDF 索引生成
