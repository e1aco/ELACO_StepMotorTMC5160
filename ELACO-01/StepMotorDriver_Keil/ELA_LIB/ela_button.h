#ifndef _ELA_BUTTON_H_
#define _ELA_BUTTON_H_

#include "elaco_main.h"


void Button_Init(void);
void Button_ScanProc(void);

/* 按键回调 — 用户在 elaco_main.c 中实现 */
extern void OnPress(void);
extern void OnLongPress(void);


#endif
