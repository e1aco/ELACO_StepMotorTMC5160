#include "ela_can.h"

/* can drv start */

/****
 * @ 说明: 对CAN未初始化的内容进行初始化
 ********/
void Can_Init(void)
{
    // 配置筛选器
    CAN_FilterTypeDef sFilterConfig = {0};
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh =
        ((0x1AA55F42 << 3) | 0x4) >> 16;
    sFilterConfig.FilterIdLow =
        ((0x1AA55F42 << 3) | 0x4) & 0xFFFF;
    sFilterConfig.FilterMaskIdHigh = 0xFFFF;
    sFilterConfig.FilterMaskIdLow  = 0xFFFF;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(&hcan1,
            CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_CAN_Start(&hcan1) != HAL_OK)
    {
        Error_Handler();
    }
}
/* can drv end */
//----------------------------------------------------------------------------------
/* can usr start */

/****
 * @ 输入: unsigned short id, unsigned char *data,
 *        unsigned char len
 * @ 输出: HAL_StatusTypeDef
 * @ 说明: CAN发送16位标准ID消息
 ********/
HAL_StatusTypeDef Can_SendMessage(unsigned short id,
                                   unsigned char *data,
                                   unsigned char len)
{
  CAN_TxHeaderTypeDef tx_header;
  unsigned int tx_mailbox;

  tx_header.StdId = id;
  tx_header.ExtId = 0x00;
  tx_header.RTR = CAN_RTR_DATA;
  tx_header.IDE = CAN_ID_STD;
  tx_header.DLC = len;
  tx_header.TransmitGlobalTime = DISABLE;

  return HAL_CAN_AddTxMessage(&hcan1, &tx_header,
                               data, &tx_mailbox);
}


/****
 * @ 输入: unsigned int id, unsigned char *data,
 *        unsigned char len
 * @ 输出: HAL_StatusTypeDef
 * @ 说明: CAN发送加强帧ID消息
 ********/
HAL_StatusTypeDef Can_SendMessageExt(unsigned int id,
                                      unsigned char *data,
                                      unsigned char len)
{
  CAN_TxHeaderTypeDef tx_header;
  unsigned int tx_mailbox;

  tx_header.StdId = 0;
  tx_header.ExtId = id;
  tx_header.RTR = CAN_RTR_DATA;
  tx_header.IDE = CAN_ID_EXT;
  tx_header.DLC = len;
  tx_header.TransmitGlobalTime = DISABLE;

  return HAL_CAN_AddTxMessage(&hcan1, &tx_header,
                               data, &tx_mailbox);
}

/****
 * @ 输入: unsigned char *data: 接收数据缓冲区指针（长度至少QUEUE_ELEM_SIZE字节）
 * @ 输出: uint8_t: 成功返回 QUEUE_OK(0)，队列空返回 QUEUE_FULL(1)
 * @ 说明: 从CAN接收队列头部读取一条消息并删除该消息，
 *        数据通过data指针返回
 ********/
unsigned char Can_ReceiveMessage(unsigned char *data)
{
    unsigned char i;
    unsigned char *p_data;

    p_data = (unsigned char *)ela_queue_first(&g_queue_st);
    if (p_data == QUEUE_NULL_PTR)
    {
        return QUEUE_FULL;
    }

    for (i = 0; i < QUEUE_ELEM_SIZE; i++)
    {
        data[i] = p_data[i];
    }

    ela_queue_delete(&g_queue_st);
    return QUEUE_OK;
}

/****
 * @ 输入: motor_sel:电机选择(0x01~0x06)
 *        position:当前位置值
 *        status_flags:状态标志位
 *        motion_phase:运动阶段
 * @ 输出: void
 * @ 说明: 按照反馈协议(0x1AA55F43)组装CAN帧并发送
 ********/
void Can_SendFeedback(unsigned char motor_sel,
                       int position,
                       unsigned char status_flags,
                       unsigned char motion_phase)
{
    unsigned char data[QUEUE_ELEM_SIZE];
    unsigned char i;

    data[0] = (unsigned char)(position & 0xFF);
    data[1] = (unsigned char)((position >> 8) & 0xFF);
    data[2] = (unsigned char)((position >> 16) & 0xFF);
    data[3] = (unsigned char)((position >> 24) & 0xFF);
    data[4] = status_flags;
    data[5] = motor_sel;
    data[6] = motion_phase;

    data[7] = 0;
    for (i = 0; i < QUEUE_ELEM_SIZE - 1; i++) {
        data[7] += data[i];
    }

    Can_SendMessageExt(0x1AA55F43, data, QUEUE_ELEM_SIZE);
}

/****
 * @ 输入: motor_sel:电机选择(0x01~0x02)
 *        param_type:参数类型(0x01=Kp,0x02=Ki,0x03=Kd,
 *                   0x04=out_max,0x05=out_min,0x06=integral_max)
 *        param_value:参数值(Q16定点数或直接整数)
 * @ 输出: void
 * @ 说明: PID调参专用反馈,byte[4]=参数类型,byte[6]=0x06标识调参反馈
 ********/
void Can_SendPidTuningFeedback(unsigned char motor_sel,
                                unsigned char param_type,
                                int param_value)
{
    unsigned char data[QUEUE_ELEM_SIZE];
    unsigned char i;

    data[0] = (unsigned char)(param_value & 0xFF);
    data[1] = (unsigned char)((param_value >> 8) & 0xFF);
    data[2] = (unsigned char)((param_value >> 16) & 0xFF);
    data[3] = (unsigned char)((param_value >> 24) & 0xFF);
    data[4] = param_type;
    data[5] = motor_sel;
    data[6] = CMD_PID_TUNING;

    data[7] = 0;
    for (i = 0; i < QUEUE_ELEM_SIZE - 1; i++) {
        data[7] += data[i];
    }

    Can_SendMessageExt(0x1AA55F43, data, QUEUE_ELEM_SIZE);
}

/* can usr end */
