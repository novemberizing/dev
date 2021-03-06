#include <stdlib.h>
#include <stdio.h>


#include "engine.h"

#include "../thread.h"
#include "../descriptor.h"
#include "../console/descriptor.h"
#include "../descriptor/event/generator.h"
#include "../server.h"
#include "../server/socket.h"
#include "../session.h"
#include "../session/socket.h"

#include "processor/pool.h"
#include "descriptor/event/subscription.h"


static void xeventenginecallback_internal(xeventengine * engine, xuint32 status);

extern xeventengine * xeventengine_new(void)
{
    xeventengine * engine = (xeventengine *) calloc(sizeof(xeventengine), 1);

    engine->main  = xeventqueue_new();
    engine->queue = xeventqueue_new();

    engine->generators.descriptor = xdescriptoreventgenerator_new(engine);

    return engine;
}

extern xint32 xeventengine_run(xeventengine * engine)
{
    xassertion(engine == xnil, "");

    if(engine->on == xnil)
    {
        engine->on = xeventenginecallback_internal;

        xeventengine_sync(engine, xeventprocessorpool_size(engine->processors));

        __xsynclock(engine->sync);
        // xeventengine_generators_on(engine);
        xeventgeneratorset_on(xaddressof(engine->generators));
        xeventprocessorpool_on(engine->processors);
        while(engine->cancel == xnil)
        {
            // 어느 시점에 ENGINE SYNC 의 UNLOCK/LOCK 을 수행해야 하는지 확인할 필요가 있다.
            __xsyncunlock(engine->sync);

            xeventqueue_once(engine->main);

            xeventgeneratorset_once(xaddressof(engine->generators));

            if(xeventprocessorpool_size(engine->processors) == 0)
            {
                xeventqueue_once(engine->queue);
            }

            __xsynclock(engine->sync);
        }
        xeventgeneratorset_off(xaddressof(engine->generators));
        xeventqueue_clear(engine->queue);
        xeventqueue_clear(engine->main);
        engine->on(engine, xeventenginestatus_off);
        engine->on = xnil;
        __xsyncunlock(engine->sync);
        xeventengine_sync(engine, xfalse);
    }

    return xsuccess;
}

extern void xeventengine_sync(xeventengine * engine, xint32 on)
{
    if(on)
    {
        if(engine->sync == xnil)
        {
            engine->sync = xsyncnew(xsynctype_default);
        }
    }
    else
    {
        xassertion(xeventprocessorpool_size(engine->processors) > 0, "");
        engine->sync = xsyncrem(engine->sync);
    }
    __xsynclock(engine->sync);

    xeventprocessorpool_sync(engine->processors, on);
    xdescriptoreventgenerator_sync(engine->generators.descriptor, on);
    if(on)
    {
        if(engine->subscriptions.sync == xnil)
        {
            engine->subscriptions.sync = xsyncnew(xsynctype_default);
        }
        if(engine->queue->sync == xnil)
        {
            engine->queue->sync = xsynccondinit(xsyncnew(xsynctype_default));
        }
        if(engine->main->sync == xnil)
        {
            engine->main->sync = xsyncnew(xsynctype_default);
        }
    }
    else
    {
        engine->subscriptions.sync = xsyncrem(engine->subscriptions.sync);
        engine->queue->sync = xsyncrem(engine->queue->sync);
        engine->main->sync = xsyncrem(engine->main->sync);
    }

    __xsyncunlock(engine->sync);
}

extern xeventsubscription * xeventengine_session_register(xeventengine * engine, xsession * session)
{
    xassertion(engine == xnil || session == xnil || session->descriptor == xnil, "");
    xassertion(session->descriptor->subscription, "");   // 이 로직을 어떻게 처리해야할까?

    xsessionsocketeventsubscription * subscription = (xsessionsocketeventsubscription *) xeventsubscription_new(engine, (xeventtarget *) session->descriptor, sizeof(xsessionsocketeventsubscription));

    subscription->generatornode.generator = engine->generators.descriptor;

    xdescriptoreventgenerator_register(engine->generators.descriptor, (xdescriptoreventsubscription *) subscription);

    return (xeventsubscription *) subscription;
}

extern xeventsubscription * xeventengine_session_unregister(xeventengine * engine, xsession * session)
{
    return (xeventsubscription *) xeventengine_descriptor_unregister(engine, (xdescriptor *) session->descriptor);
}

extern xeventsubscription * xeventengine_server_register(xeventengine * engine, xserver * server)
{
    xassertion(engine == xnil || server == xnil || server->descriptor == xnil, "");
    xassertion(server->descriptor->subscription, "");   // 이 로직을 어떻게 처리해야할까?

    xserversocketeventsubscription * subscription = (xserversocketeventsubscription *) xeventsubscription_new(engine, (xeventtarget *) server->descriptor, sizeof(xserversocketeventsubscription));

    subscription->generatornode.generator = engine->generators.descriptor;

    xdescriptoreventgenerator_register(engine->generators.descriptor, (xdescriptoreventsubscription *) subscription);

    return (xeventsubscription *) subscription;
}

extern xeventsubscription * xeventengine_server_unregister(xeventengine * engine, xserver * server)
{
    return (xeventsubscription *) xeventengine_descriptor_unregister(engine, (xdescriptor *) server->descriptor);
}


extern xeventsubscription * xeventengine_descriptor_register(xeventengine * engine, xdescriptor * descriptor)
{
    xassertion(engine == xnil || descriptor == xnil, "");

    xassertion(descriptor->subscription, "");   // 이 로직은 어떻게 처리해야 할까?

    xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) xeventsubscription_new(engine, (xeventtarget *) descriptor, sizeof(xdescriptoreventsubscription));

    subscription->generatornode.generator = engine->generators.descriptor;

    xdescriptoreventgenerator_register(engine->generators.descriptor, subscription);

    return (xeventsubscription *) subscription;
}

extern xeventsubscription * xeventengine_descriptor_unregister(xeventengine * engine, xdescriptor * descriptor)
{
    xdescriptoreventsubscription * subscription = descriptor->subscription;

    if(subscription->enginenode.engine == engine)
    {
        xdescriptoreventgenerator_unregister(engine->generators.descriptor, subscription);

        xeventsubscription * prev = subscription->enginenode.prev;
        xeventsubscription * next = subscription->enginenode.next;

        if(prev)
        {
            prev->enginenode.next = next;
            subscription->enginenode.prev = xnil;
        }
        else
        {
            engine->subscriptions.head = next;
        }

        if(next)
        {
            next->enginenode.prev = prev;
            subscription->enginenode.next = xnil;
        }
        else
        {
            engine->subscriptions.tail = prev;
        }

        engine->subscriptions.size = engine->subscriptions.size - 1;

        subscription->enginenode.engine = xnil;
    }
    else
    {
        xassertion(subscription->enginenode.engine != engine ,"");
    }

    return (xeventsubscription *) subscription;
}

extern void xeventengine_main_push(xeventengine * engine, xevent * event)
{
    xassertion(engine == xnil || engine->main == xnil || event == xnil, "");

    __xsynclock(engine->main->sync);
    xeventqueue_push(engine->main, event);
    __xsyncunlock(engine->main->sync);
}

extern void xeventengine_queue_push(xeventengine * engine, xevent * event)
{
    xassertion(engine == xnil || engine->queue == xnil || event == xnil, "");

    /**
     * 이벤트 큐는 항상 WAKEUP 을 수행하도록 하였다.
     * 다만, 이벤트 프로세서의 카운트가 존재할 경우만 WAKEUP 을 수행하도록 하고 싶다.
     * TODO: 고민할 것,... 시그널을 보내는 것도 아깝기는 하다.
     */
    __xsynclock(engine->queue->sync);
    xeventqueue_push(engine->queue, event);
    __xsyncwakeup(engine->queue->sync, xfalse);
    __xsyncunlock(engine->queue->sync);
}

static void xeventenginecallback_internal(xeventengine * engine, xuint32 status)
{
    // TODO: 
}

/**
 * 
 */
extern xint32 xeventengine_descriptor_dispatch(xdescriptor * descriptor)
{
    xassertion(descriptor == xnil, "");

    xdescriptoreventsubscription * subscription = descriptor->subscription;
    if(subscription)
    {
        xeventengine * engine = subscription->enginenode.engine;

        xassertion(engine == xnil, "");
        if(xeventprocessorpool_size(engine->processors) > 0)
        {
            xeventengine_queue_push(engine, (xevent *) xaddressof(descriptor->event));
            return xsuccess;
        }
    }

    return xfail;
}
