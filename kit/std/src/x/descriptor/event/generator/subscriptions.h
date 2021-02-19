#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_SUBSCRIPTIONS__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_SUBSCRIPTIONS__H__

#include <x/io.h>
#include <x/sync.h>

struct xdescriptoreventgeneratorsubscriptions
{
    xdescriptoreventsubscription * head;
    xdescriptoreventsubscription * tail;
    xsync *                        sync;
    xuint64                        size;
};

extern xdescriptoreventgeneratorsubscriptions * xdescriptoreventgeneratorsubscriptions_new(void);
extern xdescriptoreventgeneratorsubscriptions * xdescriptoreventgeneratorsubscriptions_rem(xdescriptoreventgeneratorsubscriptions * subscriptions);

extern void xdescriptoreventgeneratorsubscriptions_push(xdescriptoreventgeneratorsubscriptions * subscriptions, xdescriptoreventsubscription * subscription);
extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptions_del(xdescriptoreventgeneratorsubscriptions * subscriptions, xdescriptoreventsubscription * subscription);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__EVENT_GENERATOR_SUBSCRIPTIONS__H__
