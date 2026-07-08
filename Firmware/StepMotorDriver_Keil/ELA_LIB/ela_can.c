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
        ((0x1AA55F12 << 3) | 0x4) >> 16;
    sFilterConfig.FilterIdLow =
        ((0x1AA55F12 << 3) | 0x4) & 0xFFFF;
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
 * @ 原型: HAL_StatusTypeDef Can_SendMessage(
 *            unsigned short id, unsigned char *data,
 *            unsigned char len)
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
 * @ 原型: HAL_StatusTypeDef Can_SendMessageExt(
 *            unsigned int id, unsigned char *data,
 *            unsigned char len)
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

/* can usr end */
