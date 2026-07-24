# Changelog

> EM-SKILL 项目变更日志 | 由 `tools/git-changelog/changelog_gen.py` 自动生成
>
> 格式遵循 [Keep a Changelog](https://keepachangelog.com/zh-CN/1.1.0/)，
> commit 遵循 EM 自定义规范 `[Sx] type: message`。
>
> 手动重新生成：
> ```bash
> python EM-SKILL/tools/git-changelog/changelog_gen.py
> ```

## [Unreleased]

### Added
- 添加 ELA_LIB 目录结构自动生成（elaco_main.c/h 模板）
- 在 `/em init`、`/em new`、`/em mode install` 时自动创建 ELA_LIB 目录
- 添加代码规范最高优先级规则
- 在生成代码时强制检查 14 项编码规范
- 添加编码前检查流程（强制加载规范 + 查阅数据手册）
- 添加文档同步检查点（修改协议代码后必须更新文档）

### Changed
- 更新 `/em mode install` 命令，添加 ELA_LIB 目录创建和规范检查步骤
- 更新 `/em new` 命令，添加 ELA_LIB 目录检查步骤
- 更新 `/em init` 命令，在嵌入式项目初始化时创建 ELA_LIB 目录
- 更新 `/em verify` 命令，强调编码规范检查
- 更新嵌入式插件 PLUGIN.md，强调代码规范最高优先级
- 更新 `ela_rules_quick.md`，添加编码前检查和文档同步规则
- 更新 `new-standard.md` 收尾输出，添加文档同步提示

### Fixed
- 修正模板文件中的注释格式，符合 ELA_LIB 编码规范
- 修正 mode.md 中的步骤编号和输出格式

### Documentation
- 更新 SKILL.md，添加代码规范最高优先级全局约束
- 更新 README.md，添加代码规范最高优先级说明
- 更新 CHANGELOG.md，记录本次变更

### Tests

### Other
