# 命令: /em help (帮助)

## 功能
显示帮助信息

## 触发
```
/em help [命令]
```

## 无参数时

所有命令已记录在 `SKILL.md` → **通用命令（16 个）** + **知识库命令（8 个）** 两节。

常用速查：

```
日常使用:
  /em rec             恢复项目（只读 state.md）
  /em new <描述>      新功能开发（AI 推荐三档分流）
  /em verify s<N>     验证步骤 + HVR + commit 提议
  /em stat [-v]       查看状态

知识库:
  /em req [show <文件>]  查看/读取需求文档
  /em rq <内容>          修改核心文档
  /em index              更新知识库索引
  /em mode <list|audit|add|install>  模块管理

帮助:
  /em help <命令>     查看某命令的详细定义
  /em init            首次项目初始化
```

## Git 集成（S10-D）

```
git 工作流:
  tools/git-changelog/   CHANGELOG 自动生成（Python，零依赖）
  arch (主步骤完成)      自动打 tag + 更新 CHANGELOG
  verify (HVR 完成)      提议 commit（用户确认后执行）
  problem-log close      提议 commit（用户确认后执行）

手动生成 CHANGELOG:
  python EM-SKILL/tools/git-changelog/changelog_gen.py
    --from <tag> --to <ref> --version <ver> --dry-run

Git 权限（initem.md 配置）:
  ✅ status / diff / log / add / commit / checkout -b / tag
  ❌ push（禁止，user 手动推）
```

## 有参数时
显示指定命令的详细帮助：

```
/em help rec        # rec 瘦身策略
/em help new        # new 三档分流（含启发式表）
/em help verify     # verify + 嵌入式注入
/em help sessions   # 会话浏览
/em help migrate    # .emv2/ → .em/ 深度迁移
/em help migrate-state # 一键生成 state.md
```

## 工作流细则

| 工作流 | 文件 |
|--------|------|
| HVR 工作流 | `workflows/hvr-workflow.md` |
| 讨论流程（重档）| `workflows/discussion-flow.md` |
| new 轻档 | `workflows/new-light.md` |
| new 中档 | `workflows/new-standard.md` |

## 嵌入式插件

| 资源 | 文件 |
|------|------|
| 插件清单 | `plugins/embedded/PLUGIN.md` |
| 嵌入式 verify 子流程 | `plugins/embedded/workflows/verify-embedded.md` |
| 芯片学习 | `plugins/embedded/workflows/chip-learning.md` |
| 嵌入式 HVR 模板 | `plugins/embedded/templates/hvr-template-embedded.md` |
