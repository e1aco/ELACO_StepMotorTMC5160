/*****************************************************************************
 * @文件: rtt_dbg.c
 * @作者: cl
 * @日期: 2026-08-25
 * @版本: v1.0
 * @说明: SEGGER RTT 调试输出封装（替代 CAN 调试帧 0x1AA55F44）
 * @依赖: SEGGER_RTT 库（SEGGER_RTT.c + SEGGER_RTT.h + RTT/SEGGER_RTT_ASM_ARMv7M.S）
 * @平台: STM32F407 (Cortex-M4F)
 * @注意: 需在 Keil 工程中添加 SEGGER RTT 源文件，并定义 SEGGER_RTT_CONFIGURE_BUFFER=1
 *        或在 RTT_Conf.h 中配置缓冲区大小
 ****************************************************************************/
#include "drv/rtt_dbg.h"
#include <stdarg.h>
#include <stdio.h>

/* SEGGER RTT 头文件（库自带） */
#include "SEGGER_RTT.h"

/* ==== 接口实现 ==== */

/**
 * @说明 初始化 RTT，配置上行缓冲区（MCU→PC 方向）
 *       默认缓冲区 1024 字节，可在 RTT_Conf.h 改 SEGGER_RTT_BUFFER_SIZE
 */
void RTT_DBG_Init(void)
{
    SEGGER_RTT_Init();
}

/**
 * @输入 str: '\0' 结尾文本
 * @说明 写文本到 RTT Channel 0
 */
void RTT_DBG_Str(const char *str)
{
    SEGGER_RTT_WriteString(RTT_DBG_CHANNEL, str);
}

/**
 * @输入 fmt: printf 格式串
 * @说明 格式化输出（复用 SEGGER_RTT_vprintf，零额外 RAM 占用）
 */
void RTT_DBG_Printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    SEGGER_RTT_vprintf(RTT_DBG_CHANNEL, fmt, &ap);
    va_end(ap);
}

/**
 * @说明 刷新（RTT 后台自动刷，此函数为空实现，保留接口兼容）
 */
void RTT_DBG_Flush(void)
{
    /* RTT 后台由 J-Link 自动读取，无需显式刷新 */
}
