/****
 * @ 文件: ela_queue.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-21
 * @ 版本: 3.0.0
 * @ 说明: 通用循环队列模块，零硬件依赖，可直接复用
 ********/
#include "ela_queue.h"

/* module hlp start */

/* module hlp end */
//----------------------------------------------------------------------------------
/* module drv start */

/* module drv end */
//----------------------------------------------------------------------------------
/* module usr start */

QUEUE_T g_queue_st;

/****
 * @ 输入: me: 队列结构体指针
 * @ 输出: uint8_t: 队列满返回 QUEUE_FULL(1)，未满返回 QUEUE_OK(0)
 * @ 说明: 判断队列是否已满
 ********/
uint8_t ela_queue_is_full(QUEUE_T *me)
{
    return me->count >= QUEUE_SIZE;
}

/****
 * @ 输入: me: 队列结构体指针
 * @ 输出: uint8_t: 队列空返回 QUEUE_EMPTY(2)，非空返回 QUEUE_OK(0)
 * @ 说明: 判断队列是否为空
 ********/
uint8_t ela_queue_is_empty(QUEUE_T *me)
{
    return me->count == 0;
}

/****
 * @ 输入: me: 队列结构体指针
 * @ 输出: uint8_t: 当前队列中的元素个数
 * @ 说明: 获取队列元素个数
 ********/
uint8_t ela_queue_get_count(QUEUE_T *me)
{
    return me->count;
}

/****
 * @ 输入: me: 队列结构体指针;
 *        value: 待插入的数据指针
 * @ 输出: uint8_t: 成功返回 QUEUE_OK(0)，队列满返回 QUEUE_FULL(1)
 * @ 说明: 将一个命令数据插入到队列尾部
 ********/
uint8_t ela_queue_insert(QUEUE_T *me, uint8_t *value)
{
    uint8_t i;

    if (me->count >= QUEUE_SIZE)
    {
        return QUEUE_FULL;
    }

    for (i = 0; i < QUEUE_ELEM_SIZE; i++)
    {
        me->_queue[me->tail][i] = value[i];
    }

    me->tail = (me->tail + 1) % QUEUE_SIZE;
    me->count++;

    return QUEUE_OK;
}

/****
 * @ 输入: me: 队列结构体指针
 * @ 输出: uint8_t: 成功返回 QUEUE_OK(0)，队列空返回 QUEUE_EMPTY(2)
 * @ 说明: 从队列头部删除一个命令数据
 ********/
uint8_t ela_queue_delete(QUEUE_T *me)
{
    if (me->count == 0)
    {
        return QUEUE_EMPTY;
    }

    me->head = (me->head + 1) % QUEUE_SIZE;
    me->count--;

    return QUEUE_OK;
}

/****
 * @ 输入: me: 队列结构体指针
 * @ 输出: void *: 返回队列头部元素地址，队列空返回 QUEUE_NULL_PTR
 * @ 说明: 获取队列头部第一个数据的地址，不移除
 ********/
void *ela_queue_first(QUEUE_T *me)
{
    if (me->count == 0)
    {
        return QUEUE_NULL_PTR;
    }

    return &me->_queue[me->head];
}

/****
 * @ 输入: me: 队列结构体指针
 * @ 输出: void
 * @ 说明: 初始化队列
 ********/
void ela_queue_init(QUEUE_T *me)
{
    me->head  = 0;
    me->tail  = 0;
    me->count = 0;
}

/* module usr end */
