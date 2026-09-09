/*****************************************************************************
 * @文件: comm_test.c
 * @作者: cl
 * @日期: 2026-09-08
 * @版本: v1.0
 * @说明: CAN/SPI 通讯自检编排层
 *  - SPI: 上电回读 GSTAT/DRVSTATUS/CHOPCONF + GCONF 写读回显；
 *    判据 = CHOPCONF 回读匹配 + 写回显一致（IHOLD_IRUN 为只写寄存器不可回读）
 *  - CAN: ISR 中 QUEUE_Insert 计数，Heartbeat 1Hz 回显到 USART1+RTT
 * @依据: .cl/datasheet/TMC5160A_Datasheet_Rev1.14_ch04_4_spi_interface.md: SPI DATAGRAM
 *        .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch05.p038.md: IHOLD_IRUN 只写(W)
 *        .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p033.md: GSTAT/DRVSTATUS
 *        .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p032.md: CHOPCONF/IHOLD_IRUN
 *        require.md: CAN 500kbit/s, 帧 ID 0x1AA55F42→0x1AA55F43, 校验和 byte0..6
 *        .cl/memory/config.md: SPI 6.45Mbit/s (PLL3Q 103.2MHz/16), tCSH 10us, fCLK 15MHz
 * @依赖: drv/tmc5160(原 drv+usr 合并), drv/uart_dbg, drv/rtt_dbg
 ****************************************************************************/
#include "app/comm_test.h"
#include "drv/tmc5160.h"
#include "drv/uart_dbg.h"
#include "drv/rtt_dbg.h"
#include "algo/queue.h"
#include <stdio.h>

/* ==== 寄存器地址 (与 tmc5160_usr.c 一致, 编排层只读) ==== */
/* 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p032.md */
#define REG_GSTAT       0x01
#define REG_GCONF       0x00
#define REG_CHOPCONF    0x6C
#define REG_IHOLD_IRUN  0x10
#define REG_DRVSTATUS   0x6F

static volatile uint32_t s_can_rx_cnt = 0;
static uint32_t s_can_rx_cnt_shadow = 0;

/* ==== SPI 自检 ==== */

/**
 * @说明 上电 SPI 自检：读 GSTAT/DRVSTATUS/CHOPCONF
 *        + 写-读回显 GCONF (0x04→0x00) 校验写通路 + 原始字节日志
 * @判据: "[SPI OK]" 需 CHOPCONF 回读匹配且 GCONF 写-读回显成功
 *        (IHOLD_IRUN 只写不可回读, 已从判据移除, 见 ch05.p038)
 * @时钟: SPI 4Mbit/s (64MHz/16), 40bit/帧=10us, 双报+10us帧间隔≈25us
 */
void COMM_Test_SPI(void)
{
    /* 单芯重测: 芯片1未焊接，仅测 U2 (PD3 CS, PA15 ENN) */
    uint8_t chips[1] = { TMC5160_CHIP_2 };
    uint8_t i;
    uint8_t all_ok = 1;
    /* 依据 tmc5160_usr.c init 写入值: CHOPCONF=0x000181C5
     * 注: IHOLD_IRUN(0x10) 为只写寄存器, 回读恒 0, 不可作通讯判据
     * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch05.p038.md: W 0x10 IHOLD_IRUN */
    const uint32_t exp_chop = 0x000181C5UL;

    UART_DBG_Printf("[SPI CFG] U2 only prescaler16 4MHz\r\n");
    for (i = 0; i < 1; i++)
    {
        uint8_t chip = chips[i];
        uint32_t gstat, drv, chop;
        uint32_t gconf_wr, gconf_rd;
        uint8_t chip_ok = 1;
        uint8_t tx[5], rx[5];

        gstat = DRV_TMC5160_ReadReg(chip, REG_GSTAT);
        drv   = DRV_TMC5160_ReadReg(chip, REG_DRVSTATUS);
        chop  = DRV_TMC5160_ReadReg(chip, REG_CHOPCONF);

        /* 原始字节探针: 读 GSTAT 的第二报原始 rx 字节 (经 DebugTransfer) */
        tx[0] = REG_GSTAT & 0x7F;
        tx[1] = 0; tx[2] = 0; tx[3] = 0; tx[4] = 0;
        (void)DRV_TMC5160_DebugTransfer(chip, tx, rx, 5);
        UART_DBG_Printf("[SPI RAW] U%u tx=%02X %02X %02X %02X %02X "
                        "rx=%02X %02X %02X %02X %02X\r\n",
                        (unsigned)chip,
                        (unsigned)tx[0], (unsigned)tx[1], (unsigned)tx[2],
                        (unsigned)tx[3], (unsigned)tx[4],
                        (unsigned)rx[0], (unsigned)rx[1], (unsigned)rx[2],
                        (unsigned)rx[3], (unsigned)rx[4]);

        if (0xFFFFFFFF == gstat || 0xFFFFFFFF == drv ||
            0xFFFFFFFF == chop)
        {
            chip_ok = 0;
        }
        if (chop != exp_chop)
        {
            chip_ok = 0;
        }

        /* 写-读回显: GCONF 写 0x04 再读回, 再写回 0x00 (不干扰 SpreadCycle) */
        gconf_wr = 0x00000004UL;
        (void)DRV_TMC5160_WriteReg(chip, REG_GCONF, gconf_wr);
        gconf_rd = DRV_TMC5160_ReadReg(chip, REG_GCONF);
        if (gconf_rd != gconf_wr)
        {
            chip_ok = 0;
            UART_DBG_Printf("[SPI WR FAIL] U%u GCONF wr=0x%08X rd=0x%08X\r\n",
                            (unsigned)chip,
                            (unsigned)gconf_wr, (unsigned)gconf_rd);
        }
        else
        {
            UART_DBG_Printf("[SPI WR OK] U%u GCONF=0x%08X\r\n",
                            (unsigned)chip, (unsigned)gconf_rd);
        }
        (void)DRV_TMC5160_WriteReg(chip, REG_GCONF, 0x00000000UL);

        if (0 == chip_ok)
        {
            all_ok = 0;
            UART_DBG_Printf("[SPI FAIL] U%u g=0x%08X d=0x%08X c=0x%08X\r\n",
                            (unsigned)chip,
                            (unsigned)gstat, (unsigned)drv,
                            (unsigned)chop);
            RTT_DBG_Printf("[SPI FAIL] U%u g=0x%08X d=0x%08X c=0x%08X\r\n",
                           (unsigned)chip,
                           (unsigned)gstat, (unsigned)drv,
                           (unsigned)chop);
            UART_DBG_Printf("[SPI DBG] exp c=0x%08X\r\n",
                            (unsigned)exp_chop);
        }
        else
        {
            UART_DBG_Printf("[SPI OK] U%u g=0x%08X d=0x%08X c=0x%08X\r\n",
                            (unsigned)chip,
                            (unsigned)gstat, (unsigned)drv,
                            (unsigned)chop);
            RTT_DBG_Printf("[SPI OK] U%u g=0x%08X d=0x%08X c=0x%08X\r\n",
                           (unsigned)chip,
                           (unsigned)gstat, (unsigned)drv,
                           (unsigned)chop);
        }
    }

    if (all_ok)
    {
        UART_DBG_Str("[SPI OK] tested U2 link\r\n");
        RTT_DBG_Str("[SPI OK] tested U2 link\r\n");
    }
    else
    {
        UART_DBG_Str("[SPI FAIL] check wiring/CLK/SPI mode\r\n");
        RTT_DBG_Str("[SPI FAIL] check wiring/CLK/SPI mode\r\n");
    }
}

/* ==== CAN 心跳回显 ==== */

/**
 * @说明 供 stm32h7xx_it.c HAL_FDCAN_RxFifo0Callback 计数钩子调用
 *        在 ISR 中仅原子自增，不做阻塞/打印
 */
void COMM_Test_OnCanRxISR(void)
{
    s_can_rx_cnt++;
}

/**
 * @说明 主循环 1Hz 调用，回显 CAN RX 计数 + 队列深度到 USART1+RTT
 * @判据: "[CAN RX OK] cnt=..." 出现即 CAN 接收通路正常
 *        外置 PCAN 发 0x1AA55F42 后 cnt 递增即过滤器+波特率正确
 */
void COMM_Test_CAN_Heartbeat(void)
{
    uint32_t cnt = s_can_rx_cnt;

    /* 原子读 (单32位, Cortex-M7 自然对齐, 无需临界区) */
    if (cnt != s_can_rx_cnt_shadow)
    {
        s_can_rx_cnt_shadow = cnt;
        UART_DBG_Printf("[CAN RX OK] cnt=%u q_empty=%u\r\n",
                        (unsigned)cnt, (unsigned)QUEUE_IsEmpty(&g_queue_st));
        RTT_DBG_Printf("[CAN RX OK] cnt=%u q_empty=%u\r\n",
                       (unsigned)cnt, (unsigned)QUEUE_IsEmpty(&g_queue_st));
    }
}

uint32_t COMM_Test_GetCanRxCount(void)
{
    return s_can_rx_cnt;
}

