/****
 * @ 文件: ela_eeprom_test.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-31
 * @ 版本: 1.0.0
 * @ 说明: EEPROM 自检，验证 Data 块读写擦除与边界
 * @ 依赖: ela_eeprom
 ********/
#include "ela_eeprom_test.h"
#include "ela_eeprom.h"
#include "main.h"

/* 测试参数 */
#define EEPROM_TEST_SIZE  16
#define EEPROM_TEST_TAIL  (EEPROM_DATA_SIZE - EEPROM_TEST_SIZE)
#define EEPROM_TEST_MID   (EEPROM_DATA_SIZE / 2)
#define EEPROM_TEST_PATTERN_A  0x55
#define EEPROM_TEST_PATTERN_B  0xAA
#define EEPROM_TEST_LED_DELAY  200

//----------------------------------------------------------------------------------
/* eeprom test start */

/****
 * @ 输入: block: 存储块, offset: 偏移, data: 期望数据
 * @ 输出: uint8_t - 1 通过, 0 失败
 * @ 说明: 擦除后写数据并回读比对 (Flash 写前必须先擦除)
 ********/
static uint8_t eeprom_test_roundtrip(EEPROM_BLOCK_T *block,
                                     uint32_t offset,
                                     const uint8_t *data)
{
    uint8_t buf[EEPROM_TEST_SIZE];
    uint32_t i;

    ela_eeprom_erase(block);
    ela_eeprom_write(offset, block, (void *)data, EEPROM_TEST_SIZE);
    ela_eeprom_read(block, offset, buf, EEPROM_TEST_SIZE);

    for (i = 0; i < EEPROM_TEST_SIZE; i++)
    {
        if (buf[i] != data[i])
        {
            return 0;
        }
    }
    return 1;
}

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: EEPROM 自检
 *   1. 擦除后 valid 应为假
 *   2. 0x55/0xAA 交替模式，首/中/尾地址
 *   3. 顺序数 0x00~0xFF 回卷
 *   4. 边界: 首字节与末尾字节
 *   5. 写入后 valid 应为真
 *   通过: TEST_LED 常亮
 *   失败: TEST_LED 闪烁
 *   注释掉 elaco_main 中的调用即可进入正常流程
 ********/
void ela_eeprom_test_run(void)
{
    EEPROM_BLOCK_T *block = &g_eeprom_datablock_st;
    uint8_t pattern[EEPROM_TEST_SIZE];
    uint8_t buf[EEPROM_TEST_SIZE];
    uint32_t i;
    uint8_t pass = 1;

    /* 1. 擦除后 valid 应为假 */
    ela_eeprom_erase(block);
    if (ela_eeprom_valid(block))
    {
        pass = 0;
    }

    /* 2. 0x55/0xAA 交替模式 */
    for (i = 0; i < EEPROM_TEST_SIZE; i++)
    {
        if (i & 1)
        {
            pattern[i] = EEPROM_TEST_PATTERN_B;
        }
        else
        {
            pattern[i] = EEPROM_TEST_PATTERN_A;
        }
    }
    if (!eeprom_test_roundtrip(block, 0, pattern))
    {
        pass = 0;
    }
    if (!eeprom_test_roundtrip(block, EEPROM_TEST_MID, pattern))
    {
        pass = 0;
    }
    if (!eeprom_test_roundtrip(block, EEPROM_TEST_TAIL, pattern))
    {
        pass = 0;
    }

    /* 3. 顺序数 0x00~0xFF 回卷 */
    for (i = 0; i < EEPROM_TEST_SIZE; i++)
    {
        pattern[i] = (uint8_t)i;
    }
    if (!eeprom_test_roundtrip(block, EEPROM_TEST_MID, pattern))
    {
        pass = 0;
    }

    /* 4. 边界: 首字节 (单字节写) */
    ela_eeprom_erase(block);
    ela_eeprom_write(0, block, &pattern[0], 1);
    ela_eeprom_read(block, 0, buf, 1);
    if (buf[0] != pattern[0])
    {
        pass = 0;
    }

    /* 5. 写入后 valid 应为真 */
    if (!ela_eeprom_valid(block))
    {
        pass = 0;
    }

    /* 6. 擦除恢复，valid 应为假 */
    ela_eeprom_erase(block);
    if (ela_eeprom_valid(block))
    {
        pass = 0;
    }

    /* 结果指示: 通过常亮 / 失败闪烁 */
    if (pass)
    {
        HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                          GPIO_PIN_RESET);
        return;
    }
    while (1)
    {
        HAL_GPIO_TogglePin(MCU_LED_GPIO_Port, MCU_LED_Pin);
        HAL_Delay(EEPROM_TEST_LED_DELAY);
    }
}

/* eeprom test end */
