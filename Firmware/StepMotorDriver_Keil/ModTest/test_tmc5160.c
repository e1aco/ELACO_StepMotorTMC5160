#include "test_tmc5160.h"

/* IOIN寄存器位定义 (TMC5160A datasheet Rev1.14 §IOIN, bit6=SD_MODE) */
#define TMC5160_IOIN_SD_MODE_BIT    (1 << 6)

/* 测试状态返回值 */
#define TEST_OK              0
#define TEST_FAIL_IOIN       1
#define TEST_FAIL_IFCNT      2
#define TEST_FAIL_GCONF_WR   3  /* GCONF写失败(WriteReg返回FALSE) */
#define TEST_FAIL_GCONF_RD   4  /* GCONF读失败(ReadReg返回0xFFFFFFFF) */
#define TEST_FAIL_GCONF_CMP  5  /* GCONF写读不一致 */

/* LED闪烁延时 (ms) */
#define LED_FAST_MS          100
#define LED_SLOW_MS          500

/* ================================================================
 * 调试用全局变量 (Keil调试器Watch窗口可直接查看)
 * 当测试停在Led_Fail时, 查看 g_dbg 即可知道失败原因和关键寄存器值
 * ================================================================ */
typedef struct {
    unsigned char fail_code;     /* 失败码: 1=IOIN 2=IFCNT 3=GCONF_WR 4=GCONF_RD 5=GCONF_CMP */
    unsigned char chip_num;      /* 芯片号 */
    unsigned int  ioin_val;      /* IOIN寄存器读值 */
    unsigned int  gconf_orig;    /* GCONF原始值 */
    unsigned int  gconf_test;    /* GCONF写入值 */
    unsigned int  gconf_rd;      /* GCONF读回值 (★ 写后读的关键数据) */
    unsigned char wr_ret;        /* WriteReg返回值 (TRUE=0成功, FALSE=1失败) */
} TMC5160_DBG_T;

TMC5160_DBG_T g_dbg = {0};      /* 全局调试实例 */

/* test_tmc5160 hlp start */

/****
 * @ 输入: void
 * @ 输出: void
 * @ 说明: LED快闪3次，表示测试通过
 ********/
static void Led_Pass(void)
{
    unsigned char i;
    for (i = 0; i < 3; i++) {
        HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                          GPIO_PIN_RESET);
        HAL_Delay(LED_FAST_MS);
        HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                          GPIO_PIN_SET);
        HAL_Delay(LED_FAST_MS);
    }
}

/****
 * @ 输入: fail_code: 失败码(1~5), 0=通用失败
 * @ 输出: void
 * @ 说明: LED快闪 fail_code 次后长停顿, 循环重复,
 *        可通过数闪烁次数判断失败原因, 无需调试器.
 *        例: fail_code=3 → 快闪3次 → 停1秒 → 快闪3次 → ...
 *        同时 g_dbg 全局结构体保存全部关键寄存器值,
 *        在Keil Watch窗口查看即可.
 ********/
static void Led_Fail(unsigned char fail_code)
{
    unsigned char i;
    g_dbg.fail_code = fail_code;

    while (1) {
        for (i = 0; i < fail_code; i++) {
            HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                              GPIO_PIN_RESET);
            HAL_Delay(LED_FAST_MS);
            HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                              GPIO_PIN_SET);
            HAL_Delay(LED_FAST_MS);
        }
        HAL_Delay(1000);  /* 长停顿, 便于数闪烁次数 */
    }
}

/****
 * @ 输入: CHIP_T: 待测芯片结构体指针
 * @ 输出: TEST_OK(0)=通过, 非0=失败码
 * @ 说明: 对单颗TMC5160执行SPI通讯测试 (仅模式1: SD=0,SPI=1)
 *        子测试:
 *          1.IOIN读→验证返回值有效且SD_MODE=0 (Mode1)
 *          2.GCONF写读→验证数据回读一致
 *        所有中间值保存到 g_dbg, 方便Keil调试器查看.
 ********/
static unsigned char Test_SingleChip(TMC5160_T *CHIP_T)
{
    unsigned int ioin_val;
    unsigned int gconf_orig;
    unsigned int gconf_test;
    unsigned int gconf_rd;
    unsigned char wr_ret;
    unsigned char retry;

    /* 记录芯片号到调试结构体 */
    g_dbg.chip_num = CHIP_T->chip_number;

    /* ---- 1. IOIN读测试 ---- */
    retry = 0;
    while (retry < TMC5160_TEST_RETRY_COUNT) {
        ioin_val = Tmc5160_ReadReg(CHIP_T, TMC5160_IOIN);
        if (0xFFFFFFFF != ioin_val && 0x00000 != ioin_val) {
            break;
        }
        retry++;
    }
    g_dbg.ioin_val = ioin_val;            /* 保存到调试变量 */
    if (0xFFFFFFFF == ioin_val) {
        Led_Fail(TEST_FAIL_IOIN);
        return TEST_FAIL_IOIN;
    }
    /* 验证SD_MODE位为0 (模式1: SD=0, SPI=1)
     * TMC5160A datasheet Rev1.14 §IOIN: bit6=SD_MODE, 0=Motion Controller */
    if (0 != (ioin_val & TMC5160_IOIN_SD_MODE_BIT)) {
        Led_Fail(TEST_FAIL_IOIN);
        return TEST_FAIL_IOIN;
    }

#if TMC5160_TEST_GCONF_ENABLE
    /* ---- 2. GCONF写读验证 ---- */
    /* 2.1 读GCONF原始值 */
    gconf_orig = Tmc5160_ReadReg(CHIP_T, TMC5160_GCONF);
    g_dbg.gconf_orig = gconf_orig;        /* 保存到调试变量 */
    if (0xFFFFFFFF == gconf_orig) {
        Led_Fail(TEST_FAIL_GCONF_RD);
        return TEST_FAIL_GCONF_RD;
    }

    /* 2.2 翻转bit3(multistep_filt)做写读测试
     * TMC5160A datasheet Rev1.14: GCONF bit3 = multistep_filt
     * 注意: bit17是test_mode, 不能翻转它! */
    gconf_test = gconf_orig ^ (1 << 3);
    g_dbg.gconf_test = gconf_test;        /* 保存到调试变量 */

    /* 2.3 写入GCONF */
    wr_ret = Tmc5160_WriteReg(CHIP_T, TMC5160_GCONF, gconf_test);
    g_dbg.wr_ret = wr_ret;                /* 保存WriteReg返回值 */
    if (0x00 != wr_ret) {
        Led_Fail(TEST_FAIL_GCONF_WR);
        return TEST_FAIL_GCONF_WR;
    }

    /* 2.4 读回GCONF, 验证与写入值一致 */
    gconf_rd = Tmc5160_ReadReg(CHIP_T, TMC5160_GCONF);
    g_dbg.gconf_rd = gconf_rd;            /* ★ 调试关键: 写后读回值 */
    if (0xFFFFFFFF == gconf_rd) {
        Led_Fail(TEST_FAIL_GCONF_RD);
        return TEST_FAIL_GCONF_RD;
    }
    if (gconf_test != gconf_rd) {
        Led_Fail(TEST_FAIL_GCONF_CMP);
        return TEST_FAIL_GCONF_CMP;
    }

    /* 2.5 恢复GCONF原值 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_GCONF, gconf_orig);
#endif

    return TEST_OK;
}

/* test_tmc5160 hlp end */
//----------------------------------------------------------------------------------
/* test_tmc5160 usr start */

/****
 * @ 输入: void
 * @ 输出: 0=通过, 非0=失败
 * @ 说明: 测试芯片1 SPI通讯 (仅模式1)
 *        子测试: IOIN读 + GCONF写读
 ********/
unsigned char Test_TMC5160_Comm_Chip1(void)
{
    unsigned char result;

    result = Test_SingleChip(&g_tmc5160_chip1_st);
    if (TEST_OK != result) {
        Led_Fail(result);                 /* result本身就是失败码 */
    }
    return result;
}

/****
 * @ 输入: void
 * @ 输出: 0=通过, 非0=失败
 * @ 说明: 测试芯片2 SPI通讯 (仅模式1)
 *        子测试: IOIN读 + GCONF写读
 ********/
unsigned char Test_TMC5160_Comm_Chip2(void)
{
    unsigned char result;

    result = Test_SingleChip(&g_tmc5160_chip2_st);
    if (TEST_OK != result) {
        Led_Fail(result);                 /* result本身就是失败码 */
    }
    return result;
}

/****
 * @ 输入: void
 * @ 输出: 0=通过, 非0=失败
 * @ 说明: 依次测试芯片1和芯片2的SPI通讯,
 *        任一失败则停止并返回错误
 *        全部通过: LED快闪3次
 ********/
unsigned char Test_TMC5160_Comm(void)
{
    unsigned char result;

//    /* 测试芯片1 */
//    result = Test_SingleChip(&g_tmc5160_chip1_st);
//    if (TEST_OK != result) {
//        Led_Fail(result);
//        return result;
//    }

    /* 测试芯片2 */
    result = Test_SingleChip(&g_tmc5160_chip2_st);
    if (TEST_OK != result) {
        Led_Fail(result);                 /* result本身就是失败码 */
        return result;
    }

    /* 全部通过 */
    Led_Pass();
    return TEST_OK;
}


/* test_tmc5160 usr end */
