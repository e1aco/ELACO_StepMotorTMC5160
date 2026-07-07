#include <stdio.h>
#include "elaco_main.h"
#include "ela_eeprom.h"
#include "ela_button.h"
#include "iwdg.h" 
#include "mb.h"

/*
 * 现阶段：
 * 1. 串口接收不定长数据
 * 2. CAN 发送与接收
 * 3.TIM4_CH1给14Mhz频率的方波,计算值是对的，但是测试没测出来
 * 4.驱动芯片的功能转换

 * 后续内容：
 * 1.SPI配置
 * 2.对两个驱动芯片的SPI配置（CS）
 */

#define LED_STORE_ADDR  0    // LED在g_eeprom_datablock_st中的存储偏移
#define STORE_DELAY_MS  500  // 按键按下后延迟500ms再写入EEPROM

/* -1- 开始 主循环函数部分 */

/****
 * @ 原型: void elaco_main(void)
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 主循环函数，完成外设初始化后进入无限循环
 ********/
void elaco_main(void)
{
    Can_Init(); // CAN 初始化
    Timer_Init(); // 定时器初始化

//    Tmc5160_Init(); // TMC5160 初始化
//    Tmc5160_Mode(&g_tmc5160_chip1_st);
//    Tmc5160_Mode(&g_tmc5160_chip2_st);

    Button_Init(); // 按键初始化
    
    eMBInit(MB_RTU, 0x01, 0, 115200, MB_PAR_NONE); // Modbus RTU 初始化
    eMBEnable(); // 启用 Modbus RTU


    while (1)
    {
        HAL_IWDG_Refresh(&hiwdg);   // 喂狗，防止 IWDG 超时复位
        eMBPoll(); // Modbus RTU 主循环
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
        Button_ScanProc(); // 按键扫描（5ms周期）
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
    CAN_HandleTypeDef *hcan) {
  CAN_RxHeaderTypeDef rx_header;
  uint8_t rx_data[CAN_LENGTH];
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0,
                           &rx_header, rx_data) == HAL_OK)
  {
    Can_SendMessageExt(0x1AA55F02, rx_data, 8);
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
