#include "engine.h"

#include <x/descriptor/subscription.h>

extern xsubscription * xeventengine_register_client(xeventengine * engine, xclient * client)
{
    xassertion(engine == xnil || client == xnil || client->descriptor == xnil, "");
    xassertion(client->descriptor->subscription, "");

    xdescriptorSub * subscription = (xdescriptorSub *) calloc(sizeof(xdescriptorSub), 1);

    // engine or subscriptions lock
    subscription->enginenode.prev = engine->subscriptions.tail;
    if(subscription->enginenode.prev)
    {
        subscription->enginenode.prev->enginenode.next = subscription;
    }
    else
    {
        engine->subscriptions.head = subscription;
    }
    engine->subscriptions.tail = subscription;
    engine->subscriptions.size = engine->subscriptions.size + 1;
    subscription->enginenode.engine = engine;
    // engine or subscriptions unlock
    xdescriptorevent_generator_register_descriptor(subscription)
    
    // generator or subscriptions lock
    subscription->generatornode.prev = engine->generator.descriptor.tail;
    if(subscription->generatornode.prev)
    {
        subscription->generatornode.prev->generatornode.next = subscription;
    }
    else
    {
        engine->generator.descriptor.head = subscription;
    }
    engine->generator.descriptor.tail = subscription;
    engine->generator.descriptor.size = engine->generator.descriptor.size + 1;
    subscription->generatornode.generator = xaddressof(engine->generator.descriptor);
    // generator or subscriptions unlock
    client->descriptor->subscription = subscription;

    return client->descriptor->subscription;
}