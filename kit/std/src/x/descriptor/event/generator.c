#include "generator.h"

#include "subscription.h"

extern xdescriptoreventsubscription * xdescriptoreventgenerator_register(xdescriptoreventgenerator * generator, xdescriptoreventsubscription * subscription)
{
    xassertion(generator == xnil || subscription == xnil, "");

    xassertion(subscription->generatornode.subscriptions ||
               subscription->generatornode.next ||
               subscription->generatornode.prev, "");

    


    return subscription;
}