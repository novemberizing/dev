/**
 * @file    x/event.h
 * @brief   [internal]
 */
#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xeventqueue;

typedef struct xevent xevent;
typedef struct xeventqueue xeventqueue;

typedef void (*xeventhandler)(xevent *);

struct xevent
{
    struct
    {
        xevent * prev;
        xevent * next;
        xeventqueue * container;
    } node;
    xeventhandler on;
};

#define xeventon(event) do { event->on(event); } while(0)

#endif // __NOVEMBERIZING_X__EVENT__H__
