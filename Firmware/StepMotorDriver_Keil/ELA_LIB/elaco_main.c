#include <stdio.h>
#include "elaco_main.h"
#include "ela_eeprom.h"
#include "ela_button.h"
#include "ela_tmc5160.h"
#include "ela_pid.h"
#include "iwdg.h"
#include "mb.h"

#ifdef ModTest

#include "test_freemodbus.h"
#include "test_tmc5160.h"
#include "test_speed_mode.h"
#include "test_encoder.h"

#endif

/*  主循环函数部分 */
uint8_t can_queuedata[QUEUE_ELEM_SIZE];

static void Motor_ProcessCmd(uint8_t *data);
static void Motor_CheckArrival(void);
static void Motor_CheckError(void);
void Motor_PidProc(void);

/* PID控制实例 */
PID_T g_pid_motor1_st;  /* 电机1 PID控制器 */
PID_T g_pid_motor2_st;  /* 电机2 PID控制器 */
volatile unsigned char g_pid_flag;  /* PID控制周期标志(10kHz) */

/* 异常检测状态 - 记录上次已发送的异常标志(bit1-4) */
static unsigned char g_m1_err_sent;
static unsigned char g_m2_err_sent;
volatile unsigned char g_err_chk_flag;  // 定时器置位，主循环检测

void elaco_main(void)
{
    Can_Init();   // CAN 初始化
    Timer_Init(); // 定时器初始化
    Tmc5160_Init(); // TMC5160 初始化（含模式配置、基础寄存器、使能驱动）

    /* 初始化PID控制器 */
    Pid_Init(&g_pid_motor1_st);
    Pid_Init(&g_pid_motor2_st);

    /* 启动PID控制定时器(TIM9, 1kHz) */
    HAL_TIM_Base_Start_IT(&htim9);

#ifdef ModTest
    // test_freemodbus();
    // Test_TMC5160_Comm(); // TMC5160 SPI读写测试
    // Test_Speed_Mode(); // 测试速度模式下的电机旋转
    // Test_Encoder();      // 编码器验证测试
#endif

    while (1)
    {
        if (0 == Can_ReceiveMessage(can_queuedata))
        {
            Motor_ProcessCmd(can_queuedata);
        }

        /* PID控制周期(10kHz) */
        // if (g_pid_flag)
        // {
        //     g_pid_flag = 0;
        //     Motor_PidProc();
        // }

        Motor_CheckArrival(); // 轮询电机到位状态并发送反馈
        // Motor_CheckError();   // 检测电机异常并发送反馈
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
 * @ 输入: motor_sel:电机选择(0x01~0x02)
 * @ 输出: PID_T *:PID结构体指针,NULL表示无效电机号
 * @ 说明: 根据电机号获取对应的PID控制器
 ********/
static PID_T *Motor_GetPid(unsigned char motor_sel)
{
    switch (motor_sel) {
        case 0x01: return &g_pid_motor1_st;
        case 0x02: return &g_pid_motor2_st;
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
    PID_T *pid = Motor_GetPid(motor);

    if (NULL == chip) return;

    switch (cmd) {
        case CMD_ABS_POSITION: /* 绝对位置(PID闭环) */
            Pid_SetTarget(pid, value);
            Pid_Start(pid);
            chip->move_pending = 1;
            break;
        case CMD_REL_FORWARD: /* 相对位置正转(PID闭环) */
            Pid_SetTarget(pid,
                          Tmc5160_GetEncoderPosition(chip) + value);
            Pid_Start(pid);
            chip->move_pending = 1;
            break;
        case CMD_REL_REVERSE: /* 相对位置反转(PID闭环) */
            Pid_SetTarget(pid,
                          Tmc5160_GetEncoderPosition(chip) - value);
            Pid_Start(pid);
            chip->move_pending = 1;
            break;
        case CMD_VELOCITY_MODE: /* 速度模式(开环) */
            Tmc5160_SetVelocity(chip, value);
            break;
        case CMD_STOP: /* 停止/刹车 */
            Pid_Stop(pid);
            Tmc5160_StopMotor(chip);
            chip->move_pending = 0;
            break;
        case CMD_PID_TUNING: /* PID调参 */
            switch (profile) { /* 复用字节[6]作为参数类型 */
                case PID_PARAM_KP:
                    pid->kp = value;
                    break;
                case PID_PARAM_KI:
                    pid->ki = value;
                    break;
                case PID_PARAM_KD:
                    pid->kd = value;
                    break;
                case PID_PARAM_OUT_MAX:
                    pid->out_max = value;
                    break;
                case PID_PARAM_OUT_MIN:
                    pid->out_min = value;
                    break;
                case PID_PARAM_INT_MAX:
                    pid->integral_max = value;
                    break;
                default:
                    break;
            }
            /* PID调参专用反馈: byte[4]=参数类型, byte[6]=0x06 */
            Can_SendPidTuningFeedback(motor, profile, value);
            return; /* 跳过通用反馈 */
        default:
            return;
    }

    /* 0x01/0x02/0x03 立即发启动反馈，到位后再发一次
       0x04/0x05 仅立即发送一次 */

    Can_SendFeedback(motor,
                     Tmc5160_GetPosition(chip),
                     Tmc5160_GetStatusFlags(chip),
                     Tmc5160_GetMotionPhase(chip));
}

/****
 * @ 说明: 轮询检查电机是否到位(PID模式下由Motor_PidProc处理)
 *        开环模式下仍保留此函数用于兼容
 ********/
static void Motor_CheckArrival(void)
{
    unsigned char motor;
    unsigned char flags;
    TMC5160_T *chips[2] = { &g_tmc5160_chip1_st,
                            &g_tmc5160_chip2_st };

    for (motor = 0; motor < 2; motor++) {
        TMC5160_T *chip = chips[motor];
        PID_T *pid = (motor == 0) ? &g_pid_motor1_st
                                  : &g_pid_motor2_st;

        /* PID模式下由Motor_PidProc处理到位 */
        if (pid->active) continue;

        if (0 == chip->move_pending) continue;

        if (1 == (Tmc5160_GetRampStat(chip) & (1 << 9)))
        {
            chip->move_pending = 0;

            flags = Tmc5160_GetStatusFlags(chip);

            /* 到位后验证编码器偏差 */
            if (0 != Tmc5160_CheckPosition(chip, 0)) {
                flags |= 0x02;  /* 标记偏差异常(bit1) */
            }

            Can_SendFeedback(chip->chip_number,
                             Tmc5160_GetPosition(chip),
                             flags,
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
 * @ 说明: PID控制处理(10kHz调用)
 *        读取编码器位置,计算PID输出,写入TMC5160速度寄存器
 ********/
void Motor_PidProc(void)
{
    unsigned char i = 1;
    unsigned char motors[2] = {0x01, 0x02};
    TMC5160_T *chips[2] = {&g_tmc5160_chip1_st,
                           &g_tmc5160_chip2_st};
    PID_T *pids[2] = {&g_pid_motor1_st,
                      &g_pid_motor2_st};


        PID_T *pid = pids[i];
        /* 读取编码器当前位置 */
        int actual = Tmc5160_GetEncoderPosition(chips[i]);

        /* PID计算,输出速度 */
        int velocity = Pid_Calc(pid, actual);

        /* 写入TMC5160速度模式 */
        Tmc5160_SetVelocity(chips[i], velocity);

        /* 到位判定: 误差小于阈值时停止PID (±1°精度) */
        if (pid->error > -11 && pid->error < 11)
        {
            Pid_Stop(pid);
            Tmc5160_StopMotor(chips[i]);
            chips[i]->move_pending = 0;

            /* 发送到位反馈 */
            Can_SendFeedback(motors[i],
                             Tmc5160_GetPosition(chips[i]),
                             Tmc5160_GetStatusFlags(chips[i]),
                             0x10); /* bit4=静止锁轴 */
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
    if (htim->Instance == TIM9) // PID控制 10kHz
    {
        // g_pid_flag = 1;
        Motor_PidProc();
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
    uint8_t rx_data[QUEUE_ELEM_SIZE];
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0,
                             &rx_header, rx_data) == HAL_OK)
    {
        uint8_t check_code = (uint8_t)(rx_data[0] + rx_data[1] + rx_data[2] + rx_data[3] +
                                       rx_data[4] + rx_data[5] + rx_data[6]);
        if (check_code == rx_data[7])
        {
            ela_queue_insert(&g_queue_st, rx_data);
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
