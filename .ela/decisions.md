# 架构决策记录

## ADR-001: CAN PID调参命令码 0x06
- **日期**: 2026-07-21
- **决策**: 新增0x06命令码用于PID在线调参
- **影响**: elaco_main.c switch分支增加case 0x06
