#ifndef   __NOVEMBERIZING_X__EVENT__QUEUE__H__
#define   __NOVEMBERIZING_X__EVENT__QUEUE__H__

#include <x/event.h>
#include <x/sync.h>

struct xeventqueue
{
    xevent * head;
    xevent * tail;
    xsync *  sync;
    xuint64  size;
};

extern xeventqueue * xeventqueue_new(void);
extern xeventqueue * xeventqueue_rem(xeventqueue * queue);

extern xevent * xeventqueue_push(xeventqueue * queue, xevent * event);
extern xevent * xeventqueue_pop(xeventqueue * queue);

#endif // __NOVEMBERIZING_X__EVENT__QUEUE__H__
