#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_SUBSCRIPTION__H__

#include <x/descriptor.h>

struct xdescriptorsubscription;

typedef struct xdescriptorsubscription xdescriptorsubscription;

struct xdescriptorsubscription
{
    struct
    {
        xsubscription * prev;
        xsubscription * next;
        xeventengine * engine;
    } enginenode;

    struct
    {
        xdescriptorsubscription * prev;
        xdescriptorsubscription * next;
        xdescriptorsubs * cntr;
        xdescriptoreventgen * generator;
    } generatornode;

    xdescriptor * descriptor;
};



#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT_SUBSCRIPTION__H__
