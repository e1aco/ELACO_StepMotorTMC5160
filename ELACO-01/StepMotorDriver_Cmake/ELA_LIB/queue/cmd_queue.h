#ifndef _CMD_QUEUE_H_
#define _CMD_QUEUE_H_

#define QUEUE_SIZE 48 // 队列大小
#define CMD_LENGTH 8 // 每条命令的长度（包括校验位）
#define NULL1 0x00 // 定义一个特殊的NULL值，表示队列为空
#define FALSE 1 // 定义一个特殊的FALSE值，表示操作失败
#define TRUE 0 // 定义一个特殊的TRUE值，表示操作成功

typedef struct CMD_QUEUE
{
    unsigned char _CmdQueue[QUEUE_SIZE][CMD_LENGTH];
    signed char front;	/* point to first element */
    signed char rear;	/* point to last empty element */

} CMD_QUEUE_T;

extern CMD_QUEUE_T CmdQueue;


unsigned char CmdQueue_insert(CMD_QUEUE_T *me, unsigned char *value);
unsigned char CmdQueue_delete(CMD_QUEUE_T *me);
void *CmdQueue_first(CMD_QUEUE_T *me);
unsigned char CmdQueue_is_full(CMD_QUEUE_T *me);
unsigned char CmdQueue_is_empty(CMD_QUEUE_T *me);
void CmdQueueInit(CMD_QUEUE_T *me);

#endif






