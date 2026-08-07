# Require 知识库索引

> 本项目知识库，AI 优先读取本索引定位文档。资料优先级：`ELA_LIB/require.md` → `KNOWLEDGE/**/*.md`（转换产物）→ `DATASHEET/*.pdf`（原始 PDF）。

## 核心文档
- **`ELA_LIB/require.md`** (116行) ← 项目需求核心文档
  - L1-10: 硬件配置（采样电阻 0.05R / 电机 / 驱动器 / MOS）
  - L11-19: 驱动芯片工作模式（本方案使用模式1：SD_MODE=0, SPI_MODE=1）
  - L21-67: CAN 接收命令协议（命令码 0x01~0x08 / 运动参数组 / PID 参数类型）
  - L68-116: CAN 反馈响应协议（运动反馈 / 调参反馈 / 发送规则）

## 数据手册转换产物（`KNOWLEDGE/`，按组件分类）
| 文件 | 组件 | 内容 | 来源 PDF |
|------|------|------|----------|
| `TMC5160A/registers.md` | 驱动IC | 全部 57 个寄存器（地址总览 + 位定义表），SPI 时序 | TMC5160A 中文手册「寄存器」章节 |
| `TMC5160A/hw-design.md` | 驱动IC | 操作模式/引脚/示例电路/MOSFET 选型/DRV_CONF/SPI 时序/电气参数 | TMC5160A 中文手册「硬件设计」章节 |
| `TMC5160A/sw-design.md` | 驱动IC | DRV_STATUS/StealthChop/spreadCycle/StallGuard2/CoolStep/DcStep/编码器 | TMC5160A 中文手册「软件功能」章节 |
| `MOSFET/AOD4126.md` | MOS管 | 100V N-MOS 全部电气参数（驱动桥臂用） | AOD4126 数据手册 |
| `Motor/57CME13.md` | 电机 | 57CME13 闭环步进电机规格卡 | 57CME13 MS31 图纸 |

## 原始 PDF（`DATASHEET/`）
- **TMC5160A_Datasheet_Rev1.13_CN.pdf**: TMC5160A 中文数据手册（已转换为 `TMC5160A/` 下 3 个 md）
- **TMC5160A_Datasheet_Rev1.14.pdf**: TMC5160A 英文数据手册（内容与中文版重叠，已由中文版替代）
- **AOD4126 MOSFET规格书**: 栅极驱动 MOS 管参数（已转换为 md）
- **57CME13 MS31.pdf**: 步进电机机械图纸（仅尺寸，电气规格以厂家手册为准）

## 使用指引
- 查寄存器位定义 → `TMC5160A/registers.md`
- 查电路/引脚/MOSFET 选型 → `TMC5160A/hw-design.md` + `MOSFET/AOD4126.md`
- 查斩波模式/运动控制功能 → `TMC5160A/sw-design.md`
- 查电机规格 → `Motor/57CME13.md`
