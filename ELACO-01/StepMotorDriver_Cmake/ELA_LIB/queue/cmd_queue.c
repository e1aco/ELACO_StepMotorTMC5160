#include "cmd_queue.h"

CMD_QUEUE_T CmdQueue;


unsigned char  CmdQueue_insert(CMD_QUEUE_T *me, unsigned char *value)
{
    unsigned char i;

    if (CmdQueue_is_full(me))
    {
        return FALSE;
    }

    me->rear = (me->rear + 1) % QUEUE_SIZE;

    for (i = 0; i < CMD_LENGTH; i++)
    {
        (me->_CmdQueue)[me->rear][i] = value[i];
    }

    if (me->front == -1)
    {
        me->front = me->rear;
    }

    return TRUE;
}

unsigned char CmdQueue_delete(CMD_QUEUE_T *const me)
{
    if (CmdQueue_is_empty(me))
    {
        return FALSE;
    }
    else
    {
        if (me->front == me->rear)
        {
            me->front = -1;
            //me->rear = -1;
        }
        else
        {
            me->front = (me->front + 1) % QUEUE_SIZE;
        }

        return TRUE;
    }
}

void *CmdQueue_first(CMD_QUEUE_T *me)
{
    if (CmdQueue_is_empty(me))
    {
        return (void *)NULL1;
    }
    else
    {
        return &(me->_CmdQueue[me->front]);
    }
}

unsigned char CmdQueue_is_full(CMD_QUEUE_T *me)
{
    return me->front == (me->rear + 1) % QUEUE_SIZE;
}

unsigned char  CmdQueue_is_empty(CMD_QUEUE_T *me)
{
    return me->front == -1;
}

void CmdQueueInit(CMD_QUEUE_T *me)
{
    me->front = -1;
    me->rear = -1;
}
