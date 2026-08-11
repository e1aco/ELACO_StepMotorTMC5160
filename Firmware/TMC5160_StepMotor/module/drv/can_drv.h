/*****************************************************************************
 * @文件: can_drv.h
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v1.0
 * @说明: CAN 硬件驱动层（过滤器/中断接收/发送封装）
 * @平台: STM32F407 (CAN1, 500kbps)
 * @依赖: HAL_CAN
 ****************************************************************************/
#ifndef CAN_DRV_H
#define CAN_DRV_H

#include "main.h"
#include "can.h"

/* ==== 协议常量 ==== */
#define CAN_RX_ID       0x1AA55F42
#define CAN_TX_ID       0x1AA55F43
#define CAN_DATA_LEN    8

/* ==== 接口 ==== */
void    DRV_CAN_Init(void);
uint8_t DRV_CAN_Send(uint32_t id, uint8_t *data);
uint8_t DRV_CAN_SendWait(uint32_t id, uint8_t *data);

#endif /* CAN_DRV_H */
