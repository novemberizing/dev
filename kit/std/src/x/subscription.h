#ifndef   __NOVEMBERIZING_X__SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__SUBSCRIPTION__H__

#include <x/event.h>

struct xsubscription;

typedef struct xsubscription xsubscription;

typedef void (*xsubscription_cb)(xsubscription *);
typedef void (*xsubscription_cancel_fn)(xsubscription *, xsubscription_cb);

struct xsubscription
{
    /** INTERNAL */
    xsubscription *         prev;
    xsubscription *         next;
    xeventengine *          engine;
    xsubscription_cancel_fn cancel;
};

extern void xsubscription_cancel(xsubscription * subscription, xsubscription_cb callback);

#endif // __NOVEMBERIZING_X__SUBSCRIPTION__H__
