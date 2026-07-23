/****
 * @ 文件: ela_can_drv.h
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.1.0
 * @ 说明: CAN HAL 驱动层，过滤器 + 中断接收 + 发送封装
 ********/
#ifndef ELA_CAN_DRV_H
#define ELA_CAN_DRV_H

#include "main.h"
#include "can.h"

/* module hlp start */

#define CAN_RX_ID       0x1AA55F42
#define CAN_TX_ID       0x1AA55F43
#define CAN_DATA_LEN    8

/* module hlp end */

void     ela_can_drv_init(void);
uint8_t  ela_can_drv_send(uint32_t id, uint8_t *data);

#endif
