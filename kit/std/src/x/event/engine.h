#ifndef   __NOVEMBERIZING_X__EVENT__ENGINE__H__
#define   __NOVEMBERIZING_X__EVENT__ENGINE__H__

#include <x/event.h>
#include <x/event/queue.h>

#include <x/descriptor.h>

#include <x/descriptor/event/generator.h>

struct xeventengine
{
    xeventqueue *                                      queue;
    xeventqueue *                                      main;
    struct { xeventsubscription * head;
             xeventsubscription * tail;
             xsync * sync;
             xuint64 size;                           } subscriptions;
    struct { xdescriptoreventgenerator * descriptor; } generators;
    
};

extern xeventsubscription * xeventengine_register_descriptor(xeventengine * engine, xdescriptor * descriptor);

extern void xeventengine_main_push(xeventengine * engine, xevent * event);
extern xevent * xeventengine_main_pop(xeventengine * engine);

extern void xeventengine_queue_push(xeventengine * engine, xevent * event);
extern xevent * xeventengine_queue_pop(xeventengine * engine);


#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
