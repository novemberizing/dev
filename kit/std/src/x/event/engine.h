#ifndef   __NOVEMBERIZING_X__EVENT__ENGINE__H__
#define   __NOVEMBERIZING_X__EVENT__ENGINE__H__

#include <x/event.h>
#include <x/event/queue.h>

struct xeventengine
{
    xeventqueue * queue;
    xeventqueue * main;
};

extern void xeventengine_main_push(xeventengine * engine, xevent * event);
extern xevent * xeventengine_main_pop(xeventengine * engine);

extern void xeventengine_queue_push(xeventengine * engine, xevent * event);
extern xevent * xeventengine_queue_pop(xeventengine * engine);


#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
