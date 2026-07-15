#include <stdio.h>
#include "elaco_main.h"
#include "ela_eeprom.h"
#include "ela_button.h"
#include "iwdg.h"
#include "mb.h"

#ifdef ModTest

#include "test_freemodbus.h"
#include "test_tmc5160.h"
#include "test_speed_mode.h"
#include "test_encoder.h"

#endif

/*  主循环函数部分 */
uint8_t can_queuedata[CAN_LENGTH];

void elaco_main(void)
{
    Can_Init();   // CAN 初始化
    Timer_Init(); // 定时器初始化

    Tmc5160_Init(); // TMC5160 初始化
    g_tmc5160_chip1_st.mode = 1;
    g_tmc5160_chip2_st.mode = 1;
    Tmc5160_Mode(&g_tmc5160_chip1_st); // 设置为模式1
    Tmc5160_Mode(&g_tmc5160_chip2_st);

#ifdef ModTest
    // test_freemodbus();
    // Test_TMC5160_Comm(); // TMC5160 SPI读写测试
    // Test_Speed_Mode(); // 测试速度模式下的电机旋转
    Test_Encoder(); // 编码器验证测试
#endif

    while (1)
    {
        if (Queue_IsEmpty(&g_can_queue_st) != 0)
        {
            Can_ReceiveMessage(can_queuedata);                // CAN 接收消息处理
            Can_SendMessageExt(0x1AA55F43, can_queuedata, 8); // CAN 发送消息处理
        }
    }
}

//--------------------------------------------------------------------
/* 回调函数部分 */

/****
 * @ 原型: void HAL_TIM_PeriodElapsedCallback(
 *            TIM_HandleTypeDef *htim)
 * @ 输入: TIM_HandleTypeDef *htim: 定时器句柄指针
 * @ 输出: void
 * @ 说明: 定时器溢出中断回调函数，用于周期性任务调度
 ********/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        HAL_IWDG_Refresh(&hiwdg); // 喂狗，防止 IWDG 超时复位
        // HAL_GPIO_TogglePin(MCU_LED_GPIO_Port, MCU_LED_Pin); // LED 1s亮暗一次（500ms）
    }
}

/****
 * @ 原型: void HAL_CAN_RxFifo0MsgPendingCallback(
 *            CAN_HandleTypeDef *hcan)
 * @ 输入: CAN_HandleTypeDef *hcan: CAN句柄指针
 * @ 输出: void
 * @ 说明: CAN 接收 FIFO0 消息挂起中断回调函数
 ********/
void HAL_CAN_RxFifo0MsgPendingCallback(
    CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[CAN_LENGTH];
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0,
                             &rx_header, rx_data) == HAL_OK)
    {
        uint8_t check_code = (uint8_t)(rx_data[0] + rx_data[1] + rx_data[2] + rx_data[3] +
                                       rx_data[4] + rx_data[5] + rx_data[6]);
        if (check_code == rx_data[7])
        {
            Queue_Insert(&g_can_queue_st, rx_data);
        }
    }
}

//----------------------------------------------------------------------
/* 覆盖弱定义回调 */
/****
 * @ 原型: void OnPress(void)
 * @ 说明: 覆盖 ela_button.c 中的 __weak 定义。
 *         翻转 LED 状态并标记需要写入 EEPROM。
 ********/
void OnPress(void)
{
    ;
}

/****
 * @ 原型: void OnLongPress(void)
 * @ 说明: 覆盖 ela_button.c 中的 __weak 定义。暂不实现。
 ********/
void OnLongPress(void)
{
    ;
}
