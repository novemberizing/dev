#ifndef   __NOVEMBERIZING_X__EVENT__ENGINE__H__
#define   __NOVEMBERIZING_X__EVENT__ENGINE__H__

#include <x/event.h>
#include <x/server.h>
#include <x/client.h>
#include <x/session.h>
#include <x/descriptor.h>
#include <x/subscription.h>
#include <x/subscriptions.h>

#include <x/time/event/generator.h>
#include <x/signal/event/generator.h>
#include <x/descriptor/event/generator.h>

struct xeventengine;

typedef struct xeventengine xeventengine;

struct xeventengine
{
    struct
    {
        xdescriptoreventgen        descriptor;
        xtimeevent_generator       time;
        xsignalevent_generator     signal;
    } generator;

    xsubscriptions subscriptions;
};

extern xeventengine * xeventengine_new(void);
extern xeventengine * xeventengine_rem(xeventengine * engine);

extern xsubscription * xeventengine_unregister(xeventengine * engine, xsubscription * subscription);

extern xsubscription * xeventengine_register_server(xeventengine * engine, xserver * server);

extern xsubscription * xeventengine_register_client(xeventengine * engine, xclient * client);

extern xsubscription * xeventengine_register_time(xeventengine * engine, xint64 second, xint64 nanosecond, void * object);
extern xsubscription * xeventengine_register_signal(xeventengine * engine, xint32 number, void * object);

extern void xeventengine_event_push(xeventengine * engine, xuint32 category, xuint32 event, void * object);

/** INTERNAL USE */
extern xsubscription * xeventengine_register_session(xeventengine * engine, xsession * session);

#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
