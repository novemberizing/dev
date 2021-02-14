#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_SUBSCRIPTIONS__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_SUBSCRIPTIONS__H__

#include <x/descriptor/subscription.h>

struct xdescriptorsubs;

typedef struct xdescriptorsubs xdescriptorsubs;

struct xdescriptorsubs
{
    xdescriptorsub * head;
    xdescriptorsub * tail;
    xuint64 size;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR_SUBSCRIPTIONS__H__
