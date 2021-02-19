#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__

#include <x/io.h>
#include <x/event.h>
#include <x/event/subscription.h>

// struct xdescriptorsubscription;

// typedef struct xdescriptorsubscription xdescriptorsubscription;

struct xdescriptoreventsubscription
{
    xdescriptor *                                                      descriptor;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;                                  } enginenode;
    struct { xdescriptoreventsubscription * prev;
             xdescriptoreventsubscription * next;
             xdescriptoreventgenerator * generator;
             xdescriptoreventgeneratorsubscriptions * subscriptions; } generatornode;
};
#endif // __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__
