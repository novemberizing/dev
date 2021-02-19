#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__

#include <x/io.h>
#include <x/event.h>

struct xdescriptoreventgenerator
{
    xdescriptoreventgeneratorsubscriptions * alive;
    xdescriptoreventgeneratorsubscriptions * queue;
    xeventengine *                           engine;
};

extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine);
extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o);

extern xdescriptoreventsubscription * xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);
extern xdescriptoreventsubscription * xdescriptoreventgenerator_update(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);
extern xdescriptoreventsubscription * xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);


// return (xeventsubscription *) xdescriptoreventgenerator_register(engine->generators.descriptor, descriptor);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__
