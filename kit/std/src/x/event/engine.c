#include "engine.h"

#include "descriptor/event/subscription.h"

extern xeventsubscription * xeventengine_descriptor_register(xeventengine * engine, xdescriptor * descriptor)
{
    xassertion(engine == xnil || descriptor == xnil, "");

    xassertion(descriptor->subscription, "");   // 이 로직은 어떻게 처리해야 할까?

    xeventsubscription * subscription = xeventsubscription_new(engine, (xeventtarget *) descriptor, sizeof(xdescriptoreventsubscription));

    xdescriptoreventgenerator_register(engine->generators.descriptor, (xdescriptoreventsubscription *) subscription);

    return subscription;
}

extern xeventsubscription * xeventengine_descriptor_unregister(xeventengine * engine, xdescriptor * descriptor)
{
    xeventsubscription * subscription = descriptor->subscription;

    if(subscription->enginenode.engine == engine)
    {
        xdescriptoreventgenerator_unregister(engine->generators.descriptor, descriptor);    

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

    return subscription;
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
