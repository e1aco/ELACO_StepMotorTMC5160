#include "test_tmc5160.h"

/* IOIN寄存器位定义 (TMC5160 datasheet §IOIN, 模式1: SD=0,SPI=1) */
#define TMC5160_IOIN_SPI_MODE_BIT    (1 << 2)

/* 测试状态返回值 */
#define TEST_OK              0
#define TEST_FAIL_IOIN       1
#define TEST_FAIL_IFCNT      2
#define TEST_FAIL_GCONF      3

/* LED闪烁延时 (ms) */
#define LED_FAST_MS          100
#define LED_SLOW_MS          500

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
 * @ 输入: void
 * @ 输出: void
 * @ 说明: LED慢闪，表示测试失败，阻塞在此处便于调试
 ********/
static void Led_Fail(void)
{
    while (1) {
        HAL_GPIO_TogglePin(MCU_LED_GPIO_Port, MCU_LED_Pin);
        HAL_Delay(LED_SLOW_MS);
    }
}

/****
 * @ 输入: CHIP_T: 待测芯片结构体指针
 * @ 输出: TEST_OK(0)=通过, 非0=失败码
 * @ 说明: 对单颗TMC5160执行SPI通讯测试 (仅模式1: SD=0,SPI=1)
 *        子测试:
 *          1.IOIN读→验证返回值有效且SPI_MODE=1
 *          2.IFCNT连读两次→验证计数器递增
 *          3.GCONF写读→验证数据回读一致(可选的)
 ********/
static unsigned char Test_SingleChip(TMC5160_T *CHIP_T)
{
    unsigned int ioin_val;
    unsigned int ifcnt_1;
    unsigned int ifcnt_2;
    unsigned int gconf_orig;
    unsigned int gconf_test;
    unsigned int gconf_rd;
    unsigned char retry;

    /* ---- 1. IOIN读测试 ---- */
    retry = 0;
    while (retry < TMC5160_TEST_RETRY_COUNT) {
        ioin_val = Tmc5160_ReadReg(CHIP_T, TMC5160_IOIN);
        if (0xFFFFFFFF != ioin_val) {
            break;
        }
        retry++;
    }
    if (0xFFFFFFFF == ioin_val) {
        return TEST_FAIL_IOIN;
    }
    /* 验证SPI_MODE位为1 (仅支持模式1: SD=0, SPI=1) */
    if (0 == (ioin_val & TMC5160_IOIN_SPI_MODE_BIT)) {
        return TEST_FAIL_IOIN;
    }

    /* ---- 2. IFCNT递增验证 ---- */
    ifcnt_1 = Tmc5160_ReadReg(CHIP_T, TMC5160_IFCNT);
    ifcnt_2 = Tmc5160_ReadReg(CHIP_T, TMC5160_IFCNT);
    /* IFCNT每次SPI访问自动递增, 两次连续读应不同 */
    if (ifcnt_1 == ifcnt_2) {
        return TEST_FAIL_IFCNT;
    }

#if TMC5160_TEST_GCONF_ENABLE
    /* ---- 3. GCONF写读验证 ---- */
    gconf_orig = Tmc5160_ReadReg(CHIP_T, TMC5160_GCONF);
    if (0xFFFFFFFF == gconf_orig) {
        return TEST_FAIL_GCONF;
    }
    /* 翻转bit17(multistep_filt)做写读测试 */
    gconf_test = gconf_orig ^ (1 << 17);
    Tmc5160_WriteReg(CHIP_T, TMC5160_GCONF, gconf_test);
    gconf_rd = Tmc5160_ReadReg(CHIP_T, TMC5160_GCONF);
    if (gconf_test != gconf_rd) {
        return TEST_FAIL_GCONF;
    }
    /* 恢复GCONF原值 */
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
 *        子测试: IOIN读 + IFCNT递增 + GCONF写读
 ********/
unsigned char Test_TMC5160_Comm_Chip1(void)
{
    unsigned char result;

    result = Test_SingleChip(&g_tmc5160_chip1_st);
    if (TEST_OK != result) {
        Led_Fail();
    }
    return result;
}

/****
 * @ 输入: void
 * @ 输出: 0=通过, 非0=失败
 * @ 说明: 测试芯片2 SPI通讯 (仅模式1)
 *        子测试: IOIN读 + IFCNT递增 + GCONF写读
 ********/
unsigned char Test_TMC5160_Comm_Chip2(void)
{
    unsigned char result;

    result = Test_SingleChip(&g_tmc5160_chip2_st);
    if (TEST_OK != result) {
        Led_Fail();
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
//        Led_Fail();
//        return result;
//    }

    /* 测试芯片2 */
    result = Test_SingleChip(&g_tmc5160_chip2_st);
    if (TEST_OK != result) {
        Led_Fail();
        return result;
    }

    /* 全部通过 */
    Led_Pass();
    return TEST_OK;
}

/* test_tmc5160 usr end */
