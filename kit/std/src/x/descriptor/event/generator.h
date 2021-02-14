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
        xdescriptorsubs open;
        xdescriptorsubs close;
    } subscriptions;
};

extern xdescriptorsub * xdescriptoreventgen_register(xdescriptoreventgen * o, xdescriptor * descriptor);

#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT_GENERATOR__H__
