#include <stdlib.h>
#include <stdio.h>


#include "engine.h"

#include "thread.h"
#include "descriptor.h"
#include "console/descriptor.h"
#include "descriptor/event/generator.h"
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

        xeventengine_sync(engine, xeventengine_processor_pool_size(engine));

        xsynclock(engine->sync);
        xeventengine_generators_on(engine);
        xeventengine_processors_on(engine);
        while(engine->cancel == xnil)
        {
            // 어느 시점에 ENGINE SYNC 의 UNLOCK/LOCK 을 수행해야 하는지 확인할 필요가 있다.
            xsyncunlock(engine->sync);

            xeventengine_main_consume(engine);
            xeventengine_queue_consume(engine);
            xeventengine_generators_once(engine);
            xeventengine_main_process(engine);

            xsynclock(engine->sync);
        }
        xeventengine_generators_off(engine);
        xeventengine_queue_clear(engine);
        xeventengine_main_clear(engine);
        engine->on(engine, xeventenginestatus_off);
        engine->on = xnil;
        xsyncunlock(engine->sync);
        xeventengine_sync(engine, xfalse);
    }

    return xsuccess;
}

extern void xeventengine_main_consume(xeventengine * engine)
{
    xassertion(engine == xnil, "");

    xsynclock(engine->main->sync);
    xuint64 total = engine->main->size;
    for(xuint64 i = 0; i < total; i++)
    {
        xevent * event = xeventqueue_pop(engine->main);
        if(event)
        {
            xsyncunlock(engine->main->sync);
            event->on(event);
            xsynclock(engine->main->sync);
        }
        break;
    }
    xsyncunlock(engine->main->sync);
}

extern void xeventengine_queue_consume(xeventengine * engine)
{
    xassertion(engine == xnil, "");

    xsynclock(engine->queue->sync);
    xuint64 total = engine->queue->size;
    for(xuint64 i = 0; i < total; i++)
    {
        xevent * event = xeventqueue_pop(engine->queue);
        if(event)
        {
            xsyncunlock(engine->queue->sync);
            event->on(event);
            xsynclock(engine->queue->sync);
        }
        break;
    }
    xsyncunlock(engine->queue->sync);
}

extern void xeventengine_generators_once(xeventengine * engine)
{
    xassertion(engine == xnil, "");

    xdescriptoreventgenerator_once(engine->generators.descriptor);

    // TODO: THE OTHER GENERATOR ONCE ...
}

extern void xeventengine_processors_on(xeventengine * engine)
{
    if(engine)
    {
        xeventprocessorpool_on(engine->processors);
    }
}

extern void xeventengine_generators_on(xeventengine * engine)
{
    xassertion(engine == xnil, "");
    xassertion(engine->generators.descriptor == xnil, "");

    xdescriptoreventgenerator_on(engine->generators.descriptor);
}

extern void xeventengine_main_process(xeventengine * engine)
{
    // TODO:
    if(engine)
    {
    }
}

extern xuint64 xeventengine_processor_pool_size(xeventengine * engine)
{
    return engine && engine->processors ? engine->processors->size : 0;
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
    xsynclock(engine->sync);

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

    xsyncunlock(engine->sync);
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

    xsynclock(engine->main->sync);
    xeventqueue_push(engine->main, event);
    xsyncunlock(engine->main->sync);
}

extern xevent * xeventengine_main_pop(xeventengine * engine)
{
    xassertion(engine == xnil || engine->main == xnil, "");

    xsynclock(engine->main->sync);
    xevent * event = xeventqueue_pop(engine->main);
    xsyncunlock(engine->main->sync);

    return event;
}

extern void xeventengine_queue_push(xeventengine * engine, xevent * event)
{
    xassertion(engine == xnil || engine->queue == xnil || event == xnil, "");

    /**
     * 이벤트 큐는 항상 WAKEUP 을 수행하도록 하였다.
     * 다만, 이벤트 프로세서의 카운트가 존재할 경우만 WAKEUP 을 수행하도록 하고 싶다.
     * TODO: 고민할 것,... 시그널을 보내는 것도 아깝기는 하다.
     */
    xsynclock(engine->queue->sync);
    xeventqueue_push(engine->queue, event);
    xsyncwakeup(engine->queue->sync, xfalse);
    xsyncunlock(engine->queue->sync);
}

extern xevent * xeventengine_queue_pop(xeventengine * engine)
{
    xassertion(engine == xnil || engine->queue == xnil, "");
    /**
     * WAIT 을 수행하지 않는 이유는 이 코드는 이벤트 프로세서에 정의되어 있고,
     * 이 함수가 호출되는 곳은 엔진의 메인 이벤트 루프에서 호출되기 때문이다.
     */
    xsynclock(engine->queue->sync);
    xevent * event = xeventqueue_pop(engine->queue);
    xsyncunlock(engine->queue->sync);

    return event;
}

static void xeventenginecallback_internal(xeventengine * engine, xuint32 status)
{
    // TODO: 
}

extern void xeventengine_main_clear(xeventengine * engine)
{
    xsynclock(engine->main->sync);
    while(engine->main->size > 0)
    {
        xevent * event = xeventqueue_pop(engine->main);
        xsyncunlock(engine->main->sync);
        if(event)
        {
            event->on(event);
        }
        xsynclock(engine->main->sync);
    }
    xsyncunlock(engine->main->sync);
}

extern void xeventengine_queue_clear(xeventengine * engine)
{
    xsynclock(engine->queue->sync);
    while(engine->queue->size > 0)
    {
        xevent * event = xeventqueue_pop(engine->queue);
        xsyncunlock(engine->queue->sync);
        if(event)
        {
            event->on(event);
        }
        xsynclock(engine->queue->sync);
    }
    xsyncunlock(engine->queue->sync);
}

extern void xeventengine_generators_off(xeventengine * engine)
{
    xassertion(engine == xnil, "");

    xdescriptoreventgenerator_off(engine->generators.descriptor);
}

extern xint32 xengineengine_descriptor_dispatch(xdescriptor * descriptor)
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
