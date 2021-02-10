#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR_EPOLL__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR_EPOLL__H__

#include <sys/types.h>
#include <sys/epoll.h>

#include <x/descriptor/event/generator.h>

struct xdescriptorevent_generator_epoll;

typedef struct xdescriptorevent_generator_epoll xdescriptorevent_generator_epoll;

struct xdescriptorevent_generator_epoll
{
    /** INHERITED EVENT GENERATOR */
    xeventgenerator_node * head;
    xeventgenerator_node * tail;
    xuint64 size;
    xsync * sync;
    /** DESCRIPTOR EVENT GENERATOR EPOLL MEMBER */
    int f;
    int maxevents;
    int timeout;
    struct epoll_event * events;
};

extern xint32 xdescriptorevent_generator_epoll_register_descriptor(int f, xdescriptor * descriptor);
extern xint32 xdescriptorevent_generator_epoll_unregister_descriptor(int f, xdescriptor * descriptor);
extern xint32 xdescriptorevent_generator_epoll_create(xdescriptorevent_generator_epoll * generator);

#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR_EPOLL__H__
