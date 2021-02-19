#include "queue.h"

extern xeventqueue * xeventqueue_new(void)
{
    xeventqueue * queue = (xeventqueue *) calloc(sizeof(xeventqueue), 1);

    xassertion(queue == xnil, "");

    return queue;
}

extern xeventqueue * xeventqueue_rem(xeventqueue * queue)
{
    if(queue)
    {
        xassertion(queue->size == 0, "");

        queue->sync = xsyncrem(queue->sync);
    }
    return xnil;
}

extern void xeventqueue_push(xeventqueue * queue, xevent * event)
{
    xassertion(queue == xnil || event == xnil, "");

    xassertion(event->queue || event->prev || event->next, "");

    xsynclock(queue->sync);

    event->prev = queue->tail;
    if(event->prev)
    {
        event->prev->next = event;
    }
    else
    {
        queue->head = event;
    }
    queue->tail = event;
    queue->size = queue->size + 1;

    xsyncwakeup(queue->sync, xfalse);

    xsyncunlock(queue->sync);
}

extern xevent * xeventqueue_pop(xeventqueue * queue)
{
}