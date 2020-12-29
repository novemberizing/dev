#ifndef   __NOVEMBERIZING_X__THREAD__H__
#define   __NOVEMBERIZING_X__THREAD__H__

#include <x/type.h>
#include <x/val.h>
#include <x/list.h>

struct xthread
{
    xuint32 status;
    xval parameter;
    int (*on)(struct xthread *, xval);
    int (*off)(struct xthread *, xvalget);
    int (*run)(struct xthread *);
};

typedef struct xthread xthread;

#define xthread_status_cancelling   0x80000000U

#define xthreadon(o, value) do {                        \
    assertion(o->on(o, value) != xsuccess, "o->on()");  \
} while(0)

#define xthreadoff(o, destructor) do {                  \
    assertion(o->off(o) != xsuccess, "o->off()");       \
} while(0)

extern xthread * xthreadnew(int (*run)(struct xthread *));
extern xthread * xthreadrem(xthread * o, xvalget destructor);

struct xthreadpool
{
    xlist * threads;
    xlist * idles;
    xlist * queue;
};

typedef struct xthreadpool xthreadpool;

extern xthreadpool * xthreadpoolnew(xuint32 n);
extern xthreadpool * xthreadpoolrem(xthreadpool * o);
extern xthread * xthreadpoolget(xthreadpool * o);

#endif // __NOVEMBERIZING_X__THREAD__H__
