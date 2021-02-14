#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR_EPOLL__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR_EPOLL__H__

#include <sys/types.h>
#include <sys/epoll.h>

#include <x/descriptor/event/generator.h>

struct xdescriptoreventgen_epoll;

typedef struct xdescriptoreventgen_epoll xdescriptoreventgen_epoll;

struct xdescriptoreventgen_epoll
{
    xdescriptorsub * head;
    xdescriptorsub * tail;
    xuint64 size;
    xsync * sync;

    xint32 f;
    xint32 max;
    xint32 timeout;
    struct epoll_event * events;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR_EPOLL__H__
