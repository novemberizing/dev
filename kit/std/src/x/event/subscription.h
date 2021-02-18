#ifndef   __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__

#include <x/event/engine.h>

struct xeventsubscription;

typedef struct xeventsubscription xeventsubscription;

struct xeventsubscription
{
    xeventsubscription * prev;
    xeventsubscription * next;
    xeventengine *       engn;
};

#endif // __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__
