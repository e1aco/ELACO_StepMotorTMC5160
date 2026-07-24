/****
 * @ 文件: ela_closed_loop.h
 * @ 作者: ELACO
 * @ 日期: 2026-07-23
 * @ 版本: 1.0.0
 * @ 说明: 闭环控制模块，PID + 编码器反馈
 ********/
#ifndef ELA_CLOSED_LOOP_H
#define ELA_CLOSED_LOOP_H

#include <stdint.h>

/* 闭环模式 */
#define CLOSED_LOOP_OFF     0
#define CLOSED_LOOP_ON      1

void ela_closed_loop_init(void);
void ela_closed_loop_enable(uint8_t motor);
void ela_closed_loop_disable(uint8_t motor);
void ela_closed_loop_tick(uint8_t motor);
uint8_t ela_closed_loop_get_mode(uint8_t motor);

#endif
