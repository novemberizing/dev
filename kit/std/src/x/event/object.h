#ifndef   __NOVEMBERIZING_X__EVENT_OBJECT__H__
#define   __NOVEMBERIZING_X__EVENT_OBJECT__H__

#include <x/subscription.h>

#define xeventobjectmask_void   (0x00000000u)
#define xeventobjectstatus_void (0x00000000u)

struct xeventobject;

typedef struct xeventobject xeventobject;

struct xeventobject
{
    xsubscription * subscription;
    xsync *         sync;
    xuint32         mask;
    xuint32         status;
};

#define xeventobjectlock(o)                         (o->sync ? xsynclock(o->sync) : xsuccess)
#define xeventobjectunlock(o)                       (o->sync ? xsyncunlock(o->sync) : xsuccess)
#define xeventobjectwait(o, second, nanosecond)     (o->sync ? xsyncwait(o->sync, second, nanosecond) : xsuccess)
#define xeventobjectwakeup(o, all)                  (o->sync ? xsyncwakeup(o->sync, all) : xsuccess)

#define xeventobjectstatus_has(o, status)           (o->status & status)
#define xeventobjectstatus_add(o, status)           (o->status |= status)
#define xeventobjectstatus_del(o, status)           (o->status &= (~status))

#define xeventobjectmask_has(o, mask)               (o->mask & mask)
#define xeventobjectmask_add(o, mask)               (o->mask |= mask)
#define xeventobjectmask_del(o, mask)               (o->mask &= (~mask))

extern xeventobject * xeventobjectnew(xuint64 size);
extern xeventobject * xeventobjectrem(xeventobject * o);

#endif // __NOVEMBERIZING_X__EVENT_OBJECT__H__
