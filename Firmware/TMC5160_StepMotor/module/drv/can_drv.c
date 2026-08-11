/*****************************************************************************
 * @文件: can_drv.c
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v2.0
 * @说明: CAN 硬件驱动层（过滤器/中断接收/发送封装）
 * @注意: CAN RX0 中断回调在 stm32f4xx_it.c 中实现（HAL 惯例）
 * @平台: STM32F407 (CAN1, 500kbps)
 * @依赖: HAL_CAN
 ****************************************************************************/
#include "drv/can_drv.h"

/* ==== drv 层 ==== */

/**
 * @输入 无
 * @输出 无
 * @说明 配置 CAN 过滤器，仅接收扩展帧 ID 0x1AA55F42
 */
static void CAN_FilterConfig(void)
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

/**
 * @输入 id: 发送帧 ID(扩展帧); data: 8字节数据指针
 * @输出 0=成功, 1=发送失败
 * @说明 封装 HAL_CAN_AddTxMessage，非阻塞发送
 */
static uint8_t CAN_SendMsg(uint32_t id, uint8_t *data)
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

/**
 * @输入 无
 * @输出 无
 * @说明 启动 CAN 中断接收（RX0 中断）
 */
static void CAN_StartRx(void)
{
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

/* ==== 接口实现 ==== */

/**
 * @输入 无
 * @输出 无
 * @说明 CAN 驱动初始化：过滤器 + 启动中断接收
 */
void DRV_CAN_Init(void)
{
    CAN_FilterConfig();
    CAN_StartRx();
}

/**
 * @输入 id: 发送帧 ID(扩展帧); data: 8字节数据指针
 * @输出 0=成功, 1=发送失败
 * @说明 对外发送接口
 */
uint8_t DRV_CAN_Send(uint32_t id, uint8_t *data)
{
    return CAN_SendMsg(id, data);
}

/**
 * @输入 id: 发送帧 ID(扩展帧); data: 8字节数据指针
 * @输出 0=成功, 1=发送失败
 * @说明 串行化发送：等全部 3 个 TX 邮箱空闲（上一帧已完整发出）再发下一帧。
 *        仅等 1 个空闲时，同一 ID 连续多帧会被 CAN 核跨邮箱乱序仲裁，
 *        监控端按行还原时会错位（"CAN 当串口" 多帧遥测串扰根因）。
 */
uint8_t DRV_CAN_SendWait(uint32_t id, uint8_t *data)
{
    uint32_t timeout = 100000;

    while ((3 != HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)) && (0 != timeout))
    {
        timeout--;
    }
    return CAN_SendMsg(id, data);
}
