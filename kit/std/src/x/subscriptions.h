#ifndef   __NOVEMBERIZING_X__SUBSCRIPTIONS__H__
#define   __NOVEMBERIZING_X__SUBSCRIPTIONS__H__

#include <x/event.h>

struct xsubscriptions;

typedef struct xsubscriptions xsubscriptions;

struct xsubscriptions
{
    xsubscription * head;
    xsubscription * tail;
    xuint64         size;
};

#endif // __NOVEMBERIZING_X__SUBSCRIPTIONS__H__
