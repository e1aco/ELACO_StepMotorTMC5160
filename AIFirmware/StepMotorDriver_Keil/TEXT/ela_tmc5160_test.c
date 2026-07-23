/****
 * @ 文件: ela_tmc5160_test.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-23
 * @ 版本: 1.0.0
 * @ 说明: 电机测试函数，用于验证 TMC5160 电机转动
 ********/
#include "ela_tmc5160_test.h"
#include "ela_tmc5160_usr.h"
#include "ela_tmc5160_drv.h"
#include "iwdg.h"

//----------------------------------------------------------------------------------
/* tmc5160 test start */

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 电机测试函数，测试两片 TMC5160 电机转动
 *   使用前请确保硬件连接正确
 *   注释掉 elaco_main 中的调用即可进入正常流程
 ********/
void ela_tmc5160_test_run(void)
{
    int32_t pos;

    /* 应用运动参数组 (profile 1: 低速) */
    ela_tmc5160_apply_profile(&g_tmc5160_chip2_st, 1);

    /* 测试芯片2: 正转 10000 步 */
    ela_tmc5160_move_to(&g_tmc5160_chip2_st, 10000);
    tmc5160_drv_delay_ms(2000);

    pos = ela_tmc5160_get_position(&g_tmc5160_chip2_st);
    (void)pos;

    /* 测试芯片2: 反转回原点 */
    ela_tmc5160_move_to(&g_tmc5160_chip2_st, 0);
    tmc5160_drv_delay_ms(2000);

    /* 测试完成，停止电机 */
    ela_tmc5160_stop(&g_tmc5160_chip2_st);
}

/* tmc5160 test end */
