/*****************************************************************************
 * @文件: cl_config.h
 * @作者: cl
 * @日期: 2026-09-09
 * @版本: v1.0
 * @说明: 工程编译期特性开关（调试通道唯一门控源）
 *        DBG_OPEN = 总闸: 0 → 无视通道配置，全部调试输出关闭
 *        UART_DBG / RTT_DBG = 通道开关: 1 开 / 0 关
 *        关闭时接口层用空宏剥除调用（编译期零开销，实参不求值）
 * @消费: drv/uart_dbg.h、drv/rtt_dbg.h（本头经两 .h include 生效）；
 *        SPI_SOAK 由 Core/Src/main.c 上电测试段消费
 * @现状: UART 开（115200 回传主通道）；RTT 关（用户 2026-09-09 决定，
 *        无 J-Link 在位；接口与实现保留，重开只需 RTT_DBG→1）
 ****************************************************************************/
#ifndef CL_CONFIG_H
#define CL_CONFIG_H

#define DBG_OPEN    1

/* SPI 位保真浸泡诊断（2026-09-10 电机排查轮：验证 6.45Mbps 相对 F407
 * 2.625Mbps 是否过快致位翻转）：1=上电自动跑 SOAK1/SOAK2，0=生产版关闭
 * 实现见 module/app/comm_test.c COMM_Test_SPI_Soak()
 * 2026-09-10 验收置 0（结论=降速论证伪，见 .cl/memory/ 与 log.md） */
#define SPI_SOAK    0

#if DBG_OPEN
#define UART_DBG    1   /* USART1 调试输出 (PB14/PB15, 115200) */
#define RTT_DBG     0   /* SEGGER RTT 输出 —— 当前关闭 */
#else
#define UART_DBG    0
#define RTT_DBG     0
#endif

#endif /* CL_CONFIG_H */
