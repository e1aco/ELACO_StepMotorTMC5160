#ifndef _ELA_CAN_H_
#define _ELA_CAN_H_

#include "elaco_main.h"

void Can_Init(void);
HAL_StatusTypeDef Can_SendMessage(unsigned short id,
                                   unsigned char *data,
                                   unsigned char len);
HAL_StatusTypeDef Can_SendMessageExt(unsigned int id,
                                      unsigned char *data,
                                      unsigned char len);
unsigned char Can_ReceiveMessage(unsigned char *data);
void Can_SendFeedback(unsigned char motor_sel,
                       int position,
                       unsigned char status_flags,
                       unsigned char motion_phase);
void Can_SendPidTuningFeedback(unsigned char motor_sel,
                                unsigned char param_type,
                                int param_value);

#endif
