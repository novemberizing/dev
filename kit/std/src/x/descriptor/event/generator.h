#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR__H__

#include <x/descriptor.h>
#include <x/descriptor/subscriptions.h>

struct xdescriptoreventgen;

typedef struct xdescriptoreventgen xdescriptoreventgen;

struct xdescriptoreventgen
{
    struct
    {
        xdescriptorsubs alive;
        xdescriptorsubs queue;
    } subscriptions;
};

extern xdescriptorsub * xdescriptoreventgen_register(xdescriptoreventgen * o, xdescriptor * descriptor);
extern xsubscription * xdescriptoreventgen_unregister(xdescriptoreventgen * o, xsubscription * sub);
extern void xdescriptoreventgen_once(xdescriptoreventgen * o);

#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR__H__
