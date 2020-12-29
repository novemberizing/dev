#ifndef   __NOVEMBERIZING_X__SYNC__H__
#define   __NOVEMBERIZING_X__SYNC__H__

#include <x/type.h>

struct xsync
{
    xuint32 type;
    int (*on)(struct xsync *, int cond);
    int (*off)(struct xsync *);
    int (*lock)(struct xsync *);
    int (*unlock)(struct xsync *);
    int (*wait)(struct xsync *, const struct timespec *);
    int (*wakeup)(struct xsync *, int);
};

typedef struct xsync xsync;

#define xsync_type_empty            0
#define xsync_type_mutex            1

#define xsyncon(o, cond) do {                                           \
    assertion(o->on(o, cond) != xsuccess, "[sync] fail to on");         \
} while(0)

#define xsyncoff(o) do {                                                \
    assertion(o->off(o) != xsuccess, "[sync] fail to off");             \
} while(0)

#define xsynclock(o) do {                                               \
    assertion(o->lock(o) != xsuccess, "[sync] fail to lock");           \
} while(0)

#define xsyncunlock(o) do {                                             \
    assertion(o->unlock(o) != xsuccess, "[sync] fail to unlock");       \
} while(0)

#define xsyncwait(o, timespec) do {                                     \
    assertion(o->wait(o, timespec) != xsuccess, "[sync] fail to wait"); \
} while(0)

#define xsyncwakeup(o, all) do {                                        \
    assertion(o->wakeup(o, all) != xsuccess, "[sync] fail to wakeup");  \
} while(0)

extern xsync * xsyncnew(xuint32 type);
extern xsync * xsyncrem(xsync * o);

#endif // __NOVEMBERIZING_X__SYNC__H__
