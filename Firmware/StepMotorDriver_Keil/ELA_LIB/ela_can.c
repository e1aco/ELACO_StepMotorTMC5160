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
 * @ 输入: unsigned char *data: 接收数据缓冲区指针（长度至少CAN_LENGTH字节）
 * @ 输出: unsigned char: 成功返回 TRUE(0)，队列空返回 FALSE(1)
 * @ 说明: 从CAN接收队列头部读取一条消息并删除该消息，
 *        数据通过data指针返回
 ********/
unsigned char Can_ReceiveMessage(unsigned char *data)
{
    unsigned char i;
    unsigned char *p_data;

    p_data = (unsigned char *)Queue_First(&g_can_queue_st);
    if (p_data == QUEUE_NULL)
    {
        return FALSE;
    }

    for (i = 0; i < CAN_LENGTH; i++)
    {
        data[i] = p_data[i];
    }

    Queue_Delete(&g_can_queue_st);
    return TRUE;
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
    unsigned char data[CAN_LENGTH];
    unsigned char i;

    data[0] = (unsigned char)(position & 0xFF);
    data[1] = (unsigned char)((position >> 8) & 0xFF);
    data[2] = (unsigned char)((position >> 16) & 0xFF);
    data[3] = (unsigned char)((position >> 24) & 0xFF);
    data[4] = status_flags;
    data[5] = motor_sel;
    data[6] = motion_phase;

    data[7] = 0;
    for (i = 0; i < CAN_LENGTH - 1; i++) {
        data[7] += data[i];
    }

    Can_SendMessageExt(0x1AA55F43, data, CAN_LENGTH);
}

/* can usr end */
