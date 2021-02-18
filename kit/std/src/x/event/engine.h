#ifndef   __NOVEMBERIZING_X__EVENT__ENGINE__H__
#define   __NOVEMBERIZING_X__EVENT__ENGINE__H__

#include <x/event.h>
#include <x/event/queue.h>

struct xeventengine
{
    struct
    {
        xeventqueue main;
        xeventqueue all;
    } queue;
}

#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
