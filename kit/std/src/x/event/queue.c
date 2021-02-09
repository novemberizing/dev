#include "queue.h"

extern xevent * xeventqueue_del(xeventqueue * queue, xevent * event)
{
    xassertion(queue == xnil || event == xnil, "queue or event is null");

    if(event->node.container == queue)
    {
        xevent * prev = event->node.prev;
        xevent * next = event->node.next;

        if(prev)
        {
            prev->node.next = next;
        }
        else
        {
            queue->head = next;
        }

        if(next)
        {
            next->node.prev = prev;
        }
        else
        {
            queue->tail = prev;
        }

        queue->size = queue->size - 1;

        event->node.prev = xnil;
        event->node.next = xnil;
        event->node.container = xnil;

        return xnil;
    }
    else if(event->node.container == xnil)
    {
        xcheck(event->node.container == xnil, "event's queue is not exist");
    }
    else
    {
        xassertion(event->node.container != queue, "event's queue is not queue");
    }

    return xnil;
}

extern void     xeventqueue_push(xeventqueue * queue, xevent * event)
{
    xassertion(queue == xnil || event == xnil, "queue or event is null");
    
    if(event->node.container == xnil)
    {
        event->node.container = queue;

        event->node.prev = queue->tail;
        if(event->node.prev)
        {
            event->node.prev->node.next = event;
        }
        else
        {
            queue->head = event;
        }
        queue->tail = event;
        queue->size = queue->size + 1;

        xassertion(event->node.next, "invalid queue (critical)");
    }
    else if(event->node.container == queue)
    {
        xcheck(event->node.container == queue, "queue is already push");
    }
    else
    {
        xassertion(event->node.container != queue, "queue is not node's container");
    }
}

extern xevent * xeventqueue_pop(xeventqueue * queue)
{
    xassertion(queue == xnil, "queue is null");

    xevent * event = queue->head;
    if(event)
    {
        queue->head = event->node.next;
        if(queue->head)
        {
            queue->head->node.prev = xnil;
        }
        else
        {
            queue->tail = xnil;
        }
        queue->size = queue->size - 1;

        event->node.next = xnil;
        event->node.container = xnil;

        xassertion(event->node.prev, "event queue is invalid (critical)");
    }
    return event;
}

extern void     xeventqueue_once(xeventqueue * queue)
{
    xassertion(queue == xnil, "queue is null");

    xeventqueue_lock(queue);
    xuint64 total = queue->size;
    for(xuint64 i = 0; i < total; i++)
    {
        xevent * event = xeventqueue_pop(queue);
        xeventqueue_unlock(queue);

        xeventon(event);
        /**
         * 이벤트가 일회성이고, 메모리에서 해제되어야 한다고 하면,
         * 어떻게 처리해야 하는가?
         */

        xeventqueue_lock(queue);
    }
    xeventqueue_unlock(queue);
}