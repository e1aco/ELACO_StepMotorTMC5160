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
#include "main.h"
#include <stdio.h>

/* ==== 寄存器地址 (与 tmc5160_usr.c 一致, 编排层只读) ==== */
/* 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p032.md */
#define REG_GSTAT       0x01
#define REG_GCONF       0x00
#define REG_CHOPCONF    0x6C
#define REG_IHOLD_IRUN  0x10
#define REG_DRV_CONF    0x0A
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

/* ==== SPI 位保真浸泡 (SOAK, 2026-09-10 电机排查轮 r2) ==== */
/* 目的: 验证 H7 6.45Mbps 相对 F407 2.625Mbps 是否过快 → 写帧位翻转
 * 判据背景: ch04 §4.3 tCH/tCL > tCLK+10ns=76.7ns@15MHz, 6.45M 半周期 77.5ns
 *   裕量仅 1% (F407 2.625M 时 190.5ns ≈ 2.5x), 需实测证伪/证实
 * 依据 .cl/datasheet/TMC5160A_Datasheet_Rev1.14_ch04_4_spi_interface.md §4.3 */
#define REG_XTARGET     0x2D
/* r2 测试寄存器 = XTARGET (RW): RAMPMODE=1 时被忽略、RAMPMODE=0+VMAX=0 时
 * 速度上限 0 → 两阶段写图样均不改变电机行为
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p041.md: RW 0x2D XTARGET */
/* r1 教训: ENC_CONST(0x3A) 实为只写(W), 回读恒 0——r1 全部 rd=00000000 是
 * 芯片系统行为非位翻转, 与 IHOLD_IRUN 同类
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p045.md: W 0x3A */
#define SOAK_VEL        20000
/* 速度模式测试档: 20000 µsteps/t, t=2^24/fCLK
 * 推导: 20000×15e6/16777216=17881 µsteps/s ÷ 51200 µsteps/rev
 *       = 0.349 rev/s ×60 ≈ 21 rpm (低速敏感档; 实测每秒 17881 精确匹配,
 *         同步钉死 fCLK=15.00MHz±0.01%)
 * 依据 .cl/memory/config.md tmc5160_clk_freq=15MHz + motor_counts_per_rev=51200 */
#define SOAK1_ROUNDS    250U
#define SOAK2_MS        10000U

/* 8 图样覆盖全 32 位翻转; 排除 0xFFFFFFFF(读失败哨兵, 无法区分) */
static const uint32_t s_soak_words[8] = {
    0x00000000UL, 0x55555555UL, 0xAAAAAAAAUL, 0x0F0F0F0FUL,
    0xF0F0F0F0UL, 0x12345678UL, 0x87654321UL, 0xFFFFFFFEUL,
};
static uint32_t s_soak_err_shown;

/**
 * @输入 chip: 芯片号; wr: 图样
 * @输出 0=一致, 1=失配/写失败
 * @说明 写 XTARGET 后双报读回比对; xor 值定位翻转位簇(LSB 簇=SCK 边沿裕量)
 */
static uint8_t S_SoakCheck(uint8_t chip, uint32_t wr)
{
    uint32_t rd;

    if (TMC5160_OK != DRV_TMC5160_WriteReg(chip, REG_XTARGET, wr))
    {
        return 1;
    }
    rd = DRV_TMC5160_ReadReg(chip, REG_XTARGET);
    if (rd == wr)
    {
        return 0;
    }
    if (s_soak_err_shown < 10U)
    {
        s_soak_err_shown++;
        UART_DBG_Printf("[SOAK ERR] wr=%08lX rd=%08lX xor=%08lX\r\n",
                        (unsigned long)wr, (unsigned long)rd,
                        (unsigned long)(wr ^ rd));
    }
    return 1;
}

/* ==== r7 DRVSTRENGTH×电流阶梯扫描 (12V VM 下判别 s2gb 误报机制) ====
 * 背景: 用户 2026-09-10 确认 VM=12V(全局目标记录为 24V) → 高边栅极泵抬升裕量
 *   压缩, AOD4126 Rds_on 规格条件 VGS=10V; 现 DRVSTRENGTH=0(最弱)+S2G 检测窗
 *   1500ns → 高边未完全开足的 Vds 被"压降检测器"误报为短路
 * S2G=高边电压降监测非电阻测量
 * 依据 .cl/datasheet/TMC5160A_Datasheet_Rev1.14_ch11_11_diagnostics_and_protection.md
 *   Figure 11.1; 档位表 .cl/datasheet/pages/...ch03.p017.md 表3.3
 * s2gb 锁桥后需 ENN 翻转重启(ch11: disable and re-enable the driver)
 * DRV_CONF/IHOLD_IRUN 只写不读回
 * 依据 .cl/datasheet/pages/...ch05.p038.md */
#define SOAK3_RUN_MS    1000U

/* r7b: 用户 2026-09-10 要求试最强档——0(现产线值)与 7(最大) 之间取 0/5/7
 * ch03.p017 表3.3 对 Qgd=10nC 推荐 0-1 档, 强档会增加振铃, 仅作判别非常态 */
static const uint8_t s_soak3_drvs[3] = {0U, 5U, 7U};
static const uint8_t s_soak3_cs[2]   = {20U, 8U};

/**
 * @输入 chip: 芯片号; drvs: DRVSTRENGTH[2:0]; cs: IRUN[11:8]
 * @输出 无(串口两行: 位移+故障字)
 * @说明 单格=设参→ENN re-arm→速度模式 1s→采 ds/GSTAT→停车钉位
 */
static void S_Soak3Cell(uint8_t chip, uint8_t drvs, uint8_t cs)
{
    TMC5160_CHIP_T *c = &g_tmc5160_chip2_st;
    uint32_t ds;
    uint32_t gs;
    uint32_t ferr;
    uint32_t t0;
    int32_t p0;
    int32_t p1;
    int32_t e0;

    /* BBMCLKS[11:7]=8 与 init 写入(0x400)一致, [2:0]=drvs */
    (void)DRV_TMC5160_WriteReg(chip, REG_DRV_CONF, (8UL << 7) | (uint32_t)drvs);
    (void)DRV_TMC5160_WriteReg(chip, REG_IHOLD_IRUN,
                               (8UL << 16) | ((uint32_t)cs << 8) | 6UL);
    DRV_TMC5160_Disable(chip);
    DRV_TMC5160_DelayMs(5);
    DRV_TMC5160_Enable(chip);
    DRV_TMC5160_DelayMs(5);
    USR_TMC5160_ApplyProfile(c, 4);
    p0 = USR_TMC5160_GetPosition(c);
    e0 = USR_TMC5160_GetEncoderPosition(c);
    USR_TMC5160_SetVelocity(c, SOAK_VEL);
    ferr = 0;
    t0 = HAL_GetTick();
    while ((HAL_GetTick() - t0) < SOAK3_RUN_MS)
    {
        ferr += S_SoakCheck(chip, 0x5A5A5A5AUL);
    }
    ds = USR_TMC5160_GetDrvStatus(c);
    gs = USR_TMC5160_GetGStat(c);
    p1 = USR_TMC5160_GetPosition(c);
    USR_TMC5160_Stop(c);
    USR_TMC5160_MoveTo(c, p1);
    UART_DBG_Printf("[SOAK3] drvs=%u cs=%u act=%ld enc=%ld ferr=%lu\r\n",
                    (unsigned)drvs, (unsigned)cs, (long)(p1 - p0),
                    (long)(USR_TMC5160_GetEncoderPosition(c) - e0),
                    (unsigned long)ferr);
    UART_DBG_Printf("[SOAK3 ds] %08lX gs=%02lX%s\r\n",
                    (unsigned long)ds, (unsigned long)gs,
                    (0U != (ds & (1UL << 28))) ? " S2GB!" : "");
}

/**
 * @说明 SPI 位保真 r7: 活性门 + GCONF 非零对照组 + SOAK1 静置 2000 帧
 *       + DRVSTRENGTH×CS 六格阶梯扫描(每格真实运转 1s, 回传 act/enc/ds/gs)
 * @判据 [SOAK DEAD/ALIVE] [SOAK1 ...] [SOAK3]+[SOAK3 ds]×6;
 *       s2gb 随 drvs↑/cs↓ 消失 → 高边开足问题(驱动能力/12V 裕量);
 *       恒报 → 自举回路/真短路; 拔电机线重跑可再分板内外
 * @安全 每格结束 Stop+位置钉回; 扫描尾恢复生产值(DRVS=0/CS=20)并 re-arm
 */
void COMM_Test_SPI_Soak(void)
{
    uint8_t chip = TMC5160_CHIP_2;
    uint32_t r;
    uint32_t k;
    uint32_t err;
    uint32_t n;
    uint32_t ctl;
    int32_t pos;

    UART_DBG_Str("[SOAK] r7 drvs-scan 12V-VM U2 only\r\n");

    /* -- r6 活性门: CHOPCONF 应回读 init 写入的 0x000181C5(非零签名);
     *    全 0/全 F = 芯片无响应(V5V/VM 缺电、PD14 时钟丢失或 SPI 总线故障),
     *    先判活性再做协议测试——r5 教训: GCONF=0 与死芯片回读 0 无法区分 -- */
    ctl = DRV_TMC5160_ReadReg(chip, REG_CHOPCONF);
    if (0x000181C5UL != ctl)
    {
        UART_DBG_Printf("[SOAK DEAD] chop=%08lX exp=000181C5 check V5V/VM/PD14\r\n",
                        (unsigned long)ctl);
        return;
    }
    UART_DBG_Printf("[SOAK ALIVE] chop=%08lX\r\n", (unsigned long)ctl);

    /* -- 对照组: GCONF 读→写 0x04→读校验(非零图样)→写回原值, 双向写通路 -- */
    ctl = DRV_TMC5160_ReadReg(chip, REG_GCONF);
    (void)DRV_TMC5160_WriteReg(chip, REG_GCONF, 0x04UL);
    if (DRV_TMC5160_ReadReg(chip, REG_GCONF) == 0x04UL)
    {
        UART_DBG_Printf("[SOAK CTL OK] gconf0=00000004 g=%08lX\r\n",
                        (unsigned long)ctl);
    }
    else
    {
        UART_DBG_Printf("[SOAK CTL FAIL] gconf0=00000004 g=%08lX\r\n",
                        (unsigned long)ctl);
    }
    (void)DRV_TMC5160_WriteReg(chip, REG_GCONF, ctl);

    /* -- 锁轴: VMAX=0+位置模式钉当前位, 使 SOAK1 图样写入无效化 -- */
    pos = USR_TMC5160_GetPosition(&g_tmc5160_chip2_st);
    USR_TMC5160_Stop(&g_tmc5160_chip2_st);
    USR_TMC5160_MoveTo(&g_tmc5160_chip2_st, pos);

    /* -- SOAK1 静置: 250 轮 × 8 图样 = 2000 写读回显, 预计 ~150ms -- */
    err = 0;
    n = 0;
    s_soak_err_shown = 0;
    for (r = 0; r < SOAK1_ROUNDS; r++)
    {
        for (k = 0; k < 8U; k++)
        {
            err += S_SoakCheck(chip, s_soak_words[k]);
            n++;
        }
    }
    UART_DBG_Printf("[SOAK1 %s] n=%lu err=%lu\r\n",
                    (0U == err) ? "PASS" : "FAIL",
                    (unsigned long)n, (unsigned long)err);

    /* -- r7 阶梯扫描: DRVSTRENGTH{0,3,6} × IRUN{20,8} 六格, 每格运转 1s --
     * 判读见 S_Soak3Cell 头注; 扫描尾恢复生产值并 re-arm */
    for (r = 0; r < 3U; r++)
    {
        for (k = 0; k < 2U; k++)
        {
            S_Soak3Cell(chip, s_soak3_drvs[r], s_soak3_cs[k]);
        }
    }

    (void)DRV_TMC5160_WriteReg(chip, REG_DRV_CONF, 0x00000400UL);
    (void)DRV_TMC5160_WriteReg(chip, REG_IHOLD_IRUN,
                               (8UL << 16) | (20UL << 8) | 6UL);
    DRV_TMC5160_Disable(chip);
    DRV_TMC5160_DelayMs(5);
    DRV_TMC5160_Enable(chip);
    pos = USR_TMC5160_GetPosition(&g_tmc5160_chip2_st);
    USR_TMC5160_Stop(&g_tmc5160_chip2_st);
    USR_TMC5160_MoveTo(&g_tmc5160_chip2_st, pos);
    UART_DBG_Str("[SOAK] done, hold at pos\r\n");
}

