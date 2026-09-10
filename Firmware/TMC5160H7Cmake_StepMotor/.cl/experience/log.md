# 调试日志

> **滚动窗口**：log.md 只存「活性记录 + 最近进行中」——已封存条目随 `/cl end` 精简删除（git 历史兜底）。
> **价值三层模型**：结论层→require.md/.cl/memory；条件层→诊断案例或 details/tools；过程层→本文件。
> **精简判据/提升规则** 见 templates/log.md。

## [2026-09-10 15:50] 任务: SPI 时序核查（6.45Mbps 降速论）— /cl end 验收通过
- **模式**: /cl run (全自动闭环，SOAK 三轮迭代)
- **现象**: H7 电机 CAN 命令后抖动不转；用户假设=H7 SPI 6.45Mbps 比 F407 2.625Mbps 过快致位翻转
- **尝试**:
  - 第1轮: SOAK 用 ENC_CONST 写读回显 → FAIL 87.5%、rd 恒 0x00000000 → 查 ch06.p045 发现该寄存器标 **W（只写）**，回读恒 0 是芯片行为非翻转——测试寄存器选错（违规①）
  - 第2轮: 换 RW 寄存器 XTARGET（ch06.p041）→ SOAK2 FAIL 但 v=0/act=0 → boot 后未 ApplyProfile，AMAX/A1 复位默认 0 斜坡无法加速，"噪声工况"实为空转
  - 第3轮: 组4+速度模式自证运动 → **222217 帧写读回显 err=0 + 静置 2000 帧 err=0 + GCONF 对照 OK → 降速论证伪**
- **最终方案**: 无需改 SPI；结论与裕量记录入 memory（tmc5160_spi_fidelity_6p45M）
- **验证结果**: ✅ 运转中 22.4 万帧 0 位翻转；✅ 副产品：XACTUAL 稳态 17881/s = 20000×15e6/2^24 精确匹配 → **fCLK=15.00MHz±0.01% 软件钉死**（时序表 TIM4 条目注记，示波器终验仍欠）
- **经验引用**: 详见下方任务2「经验引用」与 memory 三条沉淀
- **提示词压缩**: `[STM32H750/CMake/openocd] [TMC5160 SPI3 6.45M+TIM4 15MHz] [回读判据先查访问类型+非零签名] [XTARGET 8图样浸泡 err=0] [SOAK 固件+memory 结论]`

## [2026-09-10 15:50] 任务: 电机运行排查（B 相驱动异常，进行中→硬件侧遗留）
- **模式**: /cl run（判定实验 r4→r7b 共 6 版固件）
- **现象**: U2 速度模式直调（绕开 CAN）：VACTUAL=20000 恒定、XACTUAL 线性推进，但轴原地抖（X_ENC 净位移 167~5427 微步=100% 丢步）；DS 解码 bit28 **s2gb=1** 恒报 + GSTAT.drv_err=1
- **尝试**:
  - r4(静音+屏蔽S2): "无故障"假象 → 修正：OL 检测独立于 diss2g（ch11§11.3），屏蔽 S2 时 ds 无故障不构成功率级证据
  - r5: 全 FAIL 且**所有读回恒 0（连 stst 都没有）**→ 假说=芯片无响应，非协议问题
  - r6: 加活性门（CHOPCONF 非零签名）→ [SOAK DEAD] 实锤 r5 期间 **TMC 无供电**；用户上电后 [SOAK ALIVE]，生产配置复判 s2gb 复燃（SRB 硬件修复无效）
  - r7/r7b: DRVSTRENGTH×CS 12 格阶梯 → **全格 s2gb，最强档 7 也无效** → 排除"驱动电流档位"类
- **最终方案**: 软件侧排查穷尽。根因候选收敛（未验证，不结案）：① VSA=12V→12VOUT(11.5V 栅压)压差仅 0.5V 瞬态塌陷（与 drvs 无效自洽：档位救电流不救电压）② 自举电容 CB1/CB2/CPO 损坏 ③ QFN 37-40（BMA2/LA2/LA1/BMA1）脚区焊桥 ④ B 低边管击穿。鉴别顺序：24V 重跑→断电机重跑→表量 12VOUT/B 端子→放大镜焊点
- **验证结果**: ⚠️ 未结案（判据②不满足：根因未经修复后现象消失验证）
- **经验引用**:
  - memory 4 条：all-zero=缺电签名 / ENC_CONST 只写 / spi_fidelity verified / u2_bphase_s2gb_confirmed
  - 诊断案例**暂不入库**（根因未验证），待 24V/断线鉴别收敛后按 end.md 判据入 knowledge/cases/
  - 拟固化 skill 规则（待用户确认）：① codegen——回读判据寄存器必须查 R/W 属性列+非零签名，复位默认 0 的寄存器禁止做"等值自检测试"（本次烧 2 轮：ENC_CONST + GCONF=0 CTL 盲区）② flash.md——Verified OK ≠ 复位成功，以 boots 计数为准，无 boot 立即显式 --reset（15:36 openocd 通道静默丢复位）
  - 工具环境坑：本机 E 盘迁走后 CubeCLT/ninja/openocd 全失效，CMakeCache 报"different directory"需 --clean；已装 winget Ninja 1.13.2 + xPack OpenOCD 0.12.0-7；项目 .cl/capture/start_mon.ps1 回退路径已由 E:/Desktop/XM/cl_skill 修正为 C:/Users/admin/Desktop/XM/SESkill/cl；13:46 烧录 init-fail 曾误归因 SWD 速率（实为板未通电），--speed 500 仅保守值非规则
- **提示词压缩**: `[TMC5160 外部MOS B桥不导通] [s2gb+olb同报+drvs/CS阶梯全无效] [全零读回=缺电, 只写寄存器回读恒0] [24V对照+拔线二分定板内外] [12格签名表+候选清单]`
