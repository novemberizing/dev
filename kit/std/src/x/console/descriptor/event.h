#ifndef   __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT__H__
#define   __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT__H__

#include <x/event.h>
#include <x/descriptor.h>
#include <x/console.h>

struct xconsoledescriptorevent;

typedef struct xconsoledescriptorevent xconsoledescriptorevent;

typedef void (*xconsoledescriptoreventhandler)(xconsoledescriptorevent *);

struct xconsoledescriptorevent
{
    xevent *                       prev;
    xevent *                       next;
    xeventqueue *                  queue;
    xconsoledescriptoreventhandler on;
    xconsoledescriptor *           descriptor;
};

#define xconsoledescriptorevent_init(on, descriptor) ((xconsoledescriptorevent) { xnil, xnil, xnil, on, descriptor })

#endif // __NOVEMBERIZING_X__CONSOLE__DESCRIPTOR_EVENT__H__
