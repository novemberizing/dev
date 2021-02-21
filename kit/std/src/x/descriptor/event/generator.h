#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__

#include <x/io.h>
#include <x/event.h>
#include <x/descriptor/event/generator/subscription/list.h>

struct xdescriptoreventgenerator
{
    xdescriptoreventgeneratorsubscriptionlist * alive;
    xdescriptoreventgeneratorsubscriptionlist * queue;
    xeventengine *                              engine;
};

extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine);
extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o);

extern void xdescriptoreventgenerator_call(xdescriptoreventgenerator * o);
extern void xdescriptoreventgenerator_queue_consume(xdescriptoreventgenerator * o);

extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);
extern void xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);

extern xdescriptoreventsubscription * xdescriptoreventgenerator_update(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);


#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__
