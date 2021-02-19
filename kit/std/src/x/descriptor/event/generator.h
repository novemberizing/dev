#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__

#include <x/io.h>

struct xdescriptoreventgenerator
{
    xdescriptoreventgeneratorsubscriptions * alive;
    xdescriptoreventgeneratorsubscriptions * queue;
};

extern xdescriptoreventsubscription * xdescriptoreventgenerator_register(xdescriptoreventgenerator * generator, xdescriptoreventsubscription * subscription);


// return (xeventsubscription *) xdescriptoreventgenerator_register(engine->generators.descriptor, descriptor);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR__H__
