#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION_CONTAINER__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION_CONTAINER__H__

#include <x/descriptor/subscription.h>

struct xdescriptorsubscription_container;

typedef struct xdescriptorsubscription_container xdescriptorsubscription_container;

struct xdescriptorsubscription_container
{
    xdescriptorsubscription * head;
    xdescriptorsubscription * tail;
    xuint64                   size;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION_CONTAINER__H__
