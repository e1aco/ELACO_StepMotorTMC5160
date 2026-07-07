/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_2TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_11TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

	// 配置筛选器
	CAN_FilterTypeDef sFilterConfig = {0};                              // 过滤器配置结构体
	sFilterConfig.FilterBank = 0;                                       // 筛选器组编号，0-13
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;                   // 列表模式
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;                  // 32位模式
	sFilterConfig.FilterIdHigh         =  ((0x1AA55F12 << 3) | 0x4) >> 16;    // ID(验证码)的高16位
	sFilterConfig.FilterIdLow          =  ((0x1AA55F12 << 3) | 0x4) & 0xFFFF; // ID(验证码)的低16位
	sFilterConfig.FilterMaskIdHigh     =  0xFFFF;	// 掩码模式，并且ID全匹配
	sFilterConfig.FilterMaskIdLow      =  0xFFFF; // 
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;                  // 分配到 FIFO 0
	sFilterConfig.FilterActivation = ENABLE;                            // 使能筛选器
	sFilterConfig.SlaveStartFilterBank = 14;                          // 单CAN控制器，无需从机

	// 初始化筛选器
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	{
		//printf("CAN1初始化失败\r\n");
		Error_Handler();
	}

	// 使能接收中断
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		Error_Handler();
	}

  if (HAL_CAN_Start(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* 发送CAN报文（标准帧，11位ID） */ 
HAL_StatusTypeDef CAN_SendMessage(uint16_t id, uint8_t *data, uint8_t len) {
  CAN_TxHeaderTypeDef tx_header;
  uint32_t tx_mailbox;

  tx_header.StdId = id;              // 标准标识符（11位）
  tx_header.ExtId = 0x00;            // 扩展标识符（29位，不用）
  tx_header.RTR = CAN_RTR_DATA;      // 数据帧（非远程帧）
  tx_header.IDE = CAN_ID_STD;        // 标准帧
  tx_header.DLC = len;               // 数据长度（0~8字节）
  tx_header.TransmitGlobalTime = DISABLE;

  return HAL_CAN_AddTxMessage(&hcan1, &tx_header, data, &tx_mailbox);
}


/* 发送CAN报文（增强帧，29位ID）*/
HAL_StatusTypeDef CAN_SendMessage_EXT(uint32_t id, uint8_t *data, uint8_t len)
{
  CAN_TxHeaderTypeDef tx_header;
  uint32_t tx_mailbox;

  tx_header.StdId = 0;               // 标准标识符（11位，增强帧不用）
  tx_header.ExtId = id;              // 扩展标识符（29位）
  tx_header.RTR = CAN_RTR_DATA;      // 数据帧（非远程帧）
  tx_header.IDE = CAN_ID_EXT;        // 增强帧（扩展帧）
  tx_header.DLC = len;               // 数据长度（0~8字节）
  tx_header.TransmitGlobalTime = DISABLE;

  return HAL_CAN_AddTxMessage(&hcan1, &tx_header, data, &tx_mailbox);
}

/* USER CODE END 1 */

