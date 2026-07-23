/****
 * @ 文件: ela_can_drv.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.1.0
 * @ 说明: CAN HAL 驱动层，过滤器 + 中断接收 + 发送封装
 ********/
#include "ela_can_drv.h"

/* module hlp start */

/* module hlp end */
//----------------------------------------------------------------------------------
/* module drv start */

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 配置 CAN 过滤器，仅接收 ID 0x1AA55F42（扩展帧）
 ********/
static void can_filter_config(void)
{
    CAN_FilterTypeDef filter;

    filter.FilterBank = 0;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;

    /* 扩展帧 ID 放入 FilterId: ID[28:13] -> High, ID[12:0]<<3 | IDE<<2 -> Low */
    filter.FilterIdHigh = (CAN_RX_ID >> 13) & 0xFFFF;
    filter.FilterIdLow  = ((CAN_RX_ID & 0x1FFF) << 3) | (1 << 2);

    /* 掩码: 全部位必须匹配 */
    filter.FilterMaskIdHigh = 0xFFFF;
    filter.FilterMaskIdLow  = 0xFFFC;

    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterActivation = ENABLE;
    filter.SlaveStartFilterBank = 14;

    HAL_CAN_ConfigFilter(&hcan1, &filter);
}

/****
 * @ 输入: id: 发送帧 ID（扩展帧）; data: 8字节数据指针
 * @ 输出: uint8_t: 0=成功, 1=发送失败
 * @ 说明: 封装 HAL_CAN_AddTxMessage，非阻塞发送
 ********/
static uint8_t can_send_msg(uint32_t id, uint8_t *data)
{
    CAN_TxHeaderTypeDef tx_header;
    uint32_t tx_mailbox;

    tx_header.ExtId = id;
    tx_header.IDE = CAN_ID_EXT;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = CAN_DATA_LEN;
    tx_header.TransmitGlobalTime = DISABLE;

    if (HAL_CAN_AddTxMessage(&hcan1, &tx_header, data, &tx_mailbox) != HAL_OK)
    {
        return 1;
    }
    return 0;
}

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 启动 CAN 中断接收（RX0 中断）
 ********/
static void can_start_rx(void)
{
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

/* module drv end */
//----------------------------------------------------------------------------------
/* module usr start */

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: CAN 驱动初始化：过滤器 + 启动中断接收
 ********/
void ela_can_drv_init(void)
{
    can_filter_config();
    can_start_rx();
}

/****
 * @ 输入: id: 发送帧 ID（扩展帧）; data: 8字节数据指针
 * @ 输出: uint8_t: 0=成功, 1=发送失败
 * @ 说明: 对外发送接口，调用 drv 层
 ********/
uint8_t ela_can_drv_send(uint32_t id, uint8_t *data)
{
    return can_send_msg(id, data);
}

/* module usr end */
