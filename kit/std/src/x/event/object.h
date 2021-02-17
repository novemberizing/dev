#ifndef   __NOVEMBERIZING_X__EVENT_OBJECT__H__
#define   __NOVEMBERIZING_X__EVENT_OBJECT__H__

#include <x/subscription.h>

struct xeventobject
{
    xsubscription * subscription;
    xsync *         sync;
    xuint32         mask;
    xuint32         status;
};

typedef struct xeventobject xeventobject;

#define xeventobject_lock(o)                        (o->sync ? xsynclock(o->sync) : xsuccess)
#define xeventobject_unlock(o)                      (o->sync ? xsyncunlock(o->sync) : xsuccess)
#define xeventobject_wait(o, second, nanosecond)    (o->sync ? xsyncwait(o->sync, second, nanosecond) : xsuccess)
#define xeventobject_wakeup(o, all)                 (o->sync ? xsyncwakeup(o->sync, all) : xsuccess)

#define xeventobject_status_has(o, status)          (o->status & status)
#define xeventobject_status_add(o, status)          (o->status |= status)
#define xeventobject_status_del(o, status)          (o->status &= (~status))

#define xeventobject_mask_has(o, mask)              (o->mask & mask)
#define xeventobject_mask_add(o, mask)              (o->mask |= mask)
#define xeventobject_mask_del(o, mask)              (o->mask &= (~mask))

#endif // __NOVEMBERIZING_X__EVENT_OBJECT__H__
