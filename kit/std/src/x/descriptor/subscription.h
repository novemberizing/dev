#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_EVENT_SUBSCRIPTION__H__

#include <x/descriptor.h>

struct xdescriptorsub
{
    struct
    {
        xsubscription * prev;
        xsubscription * next;
        xeventengine * engine;
    } enginenode;

    struct
    {
        xdescriptorsub * prev;
        xdescriptorsub * next;
        xdescriptorsubs * cntr;
        xdescriptoreventgen * generator;
    } generatornode;

    xdescriptor * descriptor;
};



#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT_SUBSCRIPTION__H__
