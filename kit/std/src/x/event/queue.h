/**
 * @file    x/event/queue.h
 * @brief   [internal] event queue
 */
#ifndef   __NOVEMBERIZING_X__EVENT__QUEUE__H__
#define   __NOVEMBERIZING_X__EVENT__QUEUE__H__

#include <x/event.h>

struct xeventqueue
{
    xevent * head;
    xevent * tail;
    xuint64  size;
    xsync *  sync;
};

#define xeventqueue_lock(queue)                     (queue ? xsynclock(queue->sync) : xfail)
#define xeventqueue_unlock(queue)                   (queue ? xsyncunlock(queue->sync) : xfail)
#define xeventqueue_wait(queue, second, nanosecond) (queue ? xsyncwait(queue->sync, second, nanosecond) : xfail)
#define xeventqueue_wakeup(queue, all)              (queue ? xsyncwakeup(queue->sync, all) : xfail)

extern xevent * xeventqueue_del(xeventqueue * queue, xevent * event);
extern void     xeventqueue_push(xeventqueue * queue, xevent * event);
extern xevent * xeventqueue_pop(xeventqueue * queue);
extern void     xeventqueue_once(xeventqueue * queue);

#endif // __NOVEMBERIZING_X__EVENT__QUEUE__H__
