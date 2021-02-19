#ifndef   __NOVEMBERIZING_X__EVENT__ENGINE__H__
#define   __NOVEMBERIZING_X__EVENT__ENGINE__H__

#include <x/event.h>
#include <x/event/queue.h>

struct xeventengine
{
    xeventqueue queue;
    xeventqueue main;
};

extern void xeventengine_processor_wakeup(xeventengine * engine, xint32 all);

#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
