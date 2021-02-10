#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR__H__

#include <x/descriptor.h>

struct xdescriptorevent_generator;

typedef struct xdescriptorevent_generator xdescriptorevent_generator;

struct xdescriptorevent_generator
{
    /** INHERITED EVENT GENERATOR */
    xeventgenerator_node * head;
    xeventgenerator_node * tail;
    xuint64 size;
    xsync * sync;
};

extern xeventgenerator_node * xdescriptorevent_generator_register_object(xdescriptorevent_generator * generator, xdescriptor * descriptor);
extern void xdescriptorevent_generator_unregister_object(xeventgenerator_node * node);
extern void xdescriptorevent_generator_once(xeventgenerator * o);

#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR__H__
