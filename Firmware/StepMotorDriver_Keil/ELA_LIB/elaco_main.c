#include <stdio.h>
#include "elaco_main.h"
#include "ela_eeprom.h"
#include "ela_button.h"
#include "ela_tmc5160.h"
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

static void Motor_ProcessCmd(uint8_t *data);
static void Motor_CheckArrival(void);
static void Motor_CheckError(void);

/* 异常检测状态 - 记录上次已发送的异常标志(bit1-4) */
static unsigned char g_m1_err_sent;
static unsigned char g_m2_err_sent;
volatile unsigned char g_err_chk_flag;  // 定时器置位，主循环检测

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
    // Test_Encoder();      // 编码器验证测试
#endif

    while (1)
    {
        if (0 != Queue_IsEmpty(&g_can_queue_st))
        {
            if (0 == Can_ReceiveMessage(can_queuedata))
            {
                Motor_ProcessCmd(can_queuedata);
            }
        }

        Motor_CheckArrival(); // 轮询电机到位状态并发送反馈
        Motor_CheckError();   // 检测电机异常并发送反馈
    }
}

//----------------------------------------------------------------------
/* motor cac start */

#define MOTOR_SEL_BOTH  0x06

/****
 * @ 输入: motor_sel:电机选择(0x01~0x02)
 * @ 输出: TMC5160_T *:芯片结构体指针,NULL表示无效电机号
 * @ 说明: 根据协议电机号获取对应的TMC5160芯片结构体指针
 ********/
static TMC5160_T *Motor_GetChip(unsigned char motor_sel)
{
    switch (motor_sel) {
        case 0x01: return &g_tmc5160_chip1_st;
        case 0x02: return &g_tmc5160_chip2_st;
        default:   return NULL;
    }
}

/****
 * @ 输入: motor:电机选择 cmd:命令码 value:位置/速度值
 *        profile:运动参数组ID
 * @ 输出: void
 * @ 说明: 对单个电机执行CAN命令,完成后自动发送CAN反馈
 ********/
static void Motor_ExecOne(unsigned char motor,
                           unsigned char cmd,
                           int value,
                           unsigned char profile)
{
    TMC5160_T *chip = Motor_GetChip(motor);

    if (NULL == chip) return;

    switch (cmd) {
        case 0x01:
            Tmc5160_ApplyProfile(chip, profile);
            Tmc5160_MoveTo(chip, value);
            chip->move_pending = 1; // 到位后再发一次反馈
            break;
        case 0x02:
            Tmc5160_ApplyProfile(chip, profile);
            Tmc5160_MoveBy(chip, value);
            chip->move_pending = 1; // 到位后再发一次反馈
            break;
        case 0x03:
            Tmc5160_ApplyProfile(chip, profile);
            Tmc5160_SetVelocity(chip, value);
            break;
        case 0x04:
            Tmc5160_StopMotor(chip);
            chip->move_pending = 0; // 取消到位等待
            break;
        default:
            return;
    }

    /* 0x01/0x02 立即发启动反馈，到位后再发一次
       0x03/0x04 仅立即发送一次 */
    Can_SendFeedback(motor,
                     Tmc5160_GetPosition(chip),
                     Tmc5160_GetStatusFlags(chip),
                     Tmc5160_GetMotionPhase(chip));
}

/****
 * @ 说明: 轮询检查电机是否到位，到位后发送CAN反馈
 ********/
static void Motor_CheckArrival(void)
{
    unsigned char motor;
    TMC5160_T *chips[2] = { &g_tmc5160_chip1_st,
                            &g_tmc5160_chip2_st };

    for (motor = 0; motor < 2; motor++) {
        TMC5160_T *chip = chips[motor];

        if (0 == chip->move_pending) continue;

        if (1 == (Tmc5160_GetRampStat(chip) & (1 << 9)))
        {
            chip->move_pending = 0;
            Can_SendFeedback(chip->chip_number,
                             Tmc5160_GetPosition(chip),
                             Tmc5160_GetStatusFlags(chip),
                             Tmc5160_GetMotionPhase(chip));
        }
    }
}

/****
 * @ 说明: 定时器触发的异常检测,检测到bit1-4(堵转/过温/驱动错误/
 *        SPI通讯异常)变化时立即发送CAN反馈
 ********/
static void Motor_CheckError(void)
{
    unsigned char flags, err_bits;

    if (0 == g_err_chk_flag) return;
    g_err_chk_flag = 0;

    /* 电机1 */
    flags = Tmc5160_GetStatusFlags(&g_tmc5160_chip1_st);
    err_bits = flags & 0x1E; // bit1-4(堵转/过温/驱动错误/SPI通讯异常)
    if (err_bits != g_m1_err_sent) {
        g_m1_err_sent = err_bits;
        if (0 != err_bits) {
            Can_SendFeedback(0x01,
                             Tmc5160_GetPosition(&g_tmc5160_chip1_st),
                             flags,
                             Tmc5160_GetMotionPhase(&g_tmc5160_chip1_st));
        }
    }

    /* 电机2 */
    flags = Tmc5160_GetStatusFlags(&g_tmc5160_chip2_st);
    err_bits = flags & 0x1E;
    if (err_bits != g_m2_err_sent) {
        g_m2_err_sent = err_bits;
        if (0 != err_bits) {
            Can_SendFeedback(0x02,
                             Tmc5160_GetPosition(&g_tmc5160_chip2_st),
                             flags,
                             Tmc5160_GetMotionPhase(&g_tmc5160_chip2_st));
        }
    }
}

/****
 * @ 输出: void
 * @ 说明: 解析CAN命令协议帧,根据命令码和电机号执行操作
 ********/
static void Motor_ProcessCmd(uint8_t *data)
{
    int value;
    unsigned char cmd    = data[4];
    unsigned char motor  = data[5];
    unsigned char profile = data[6];

    value = (int)(data[0] | (data[1] << 8) |
                  (data[2] << 16) | (data[3] << 24));

    if (MOTOR_SEL_BOTH == motor) { // 如果是两台电机一起操作
        Motor_ExecOne(0x01, cmd, value, profile);
        Motor_ExecOne(0x02, cmd, value, profile);
    } else {
        Motor_ExecOne(motor, cmd, value, profile); // 否则只操作某一个电机
    }
}

/* motor cac end */
//----------------------------------------------------------------------
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
        g_err_chk_flag = 1;       // 触发异常检测
        // HAL_GPIO_TogglePin(MCU_LED_GPIO_Port, MCU_LED_Pin);
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
