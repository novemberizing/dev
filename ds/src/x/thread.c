#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

#include "log.h"
#include "thread.h"

struct __xpthread
{
    xuint32 status;
    xval parameter;
    int (*on)(struct xthread *, xval);
    int (*off)(struct xthread *, xvalget);
    int (*run)(struct xthread *);
    pthread_t * thread;
    void * result;
};

typedef struct __xpthread xpthread;

static void * __xpthread_start_routine(void * p)
{
    xthread * o = (xthread *) p;
    assertion(o == xnil, "o == xnil");

    long ret = o->run(o);

    o->status = 0;

    return (void *)(int *) ret;
}

static int __xpthread_on(struct xthread * p, xval value)
{
    int ret;
    xpthread * o = (xpthread *) p;
    assertion(o == xnil, "o == xnil");

    if(o->thread == xnil)
    {
        o->thread = (pthread_t *) calloc(sizeof(pthread_t), 1);
        assertion(o->thread == xnil, "calloc => %d", errno);
        assertion(o->parameter.ptr != xnil, "o->parameter.ptr != xnil");

        o->result = xnil;
        o->parameter = value;
        ret = pthread_create(o->thread, xnil, __xpthread_start_routine, o);
        assertion(ret != xsuccess, "pthread_create => %d", errno);
    }

    return xsuccess;
}

static int __xpthread_off(struct xthread * p, xvalget destructor)
{
    int ret;
    xpthread * o = (xpthread *) p;
    assertion(o == xnil, "o == xnil");

    if(o->thread)
    {
        o->status = xthread_status_cancelling;
        ret = pthread_join(*o->thread, &o->result);
        assertion(ret != xsuccess, "pthread_join => %d", errno);

        if(destructor)
        {
            destructor(o->parameter);
        }

        free(o->thread);
        o->thread = xnil;
    }

    return xsuccess;
}

xthread * xthreadnew(int (*run)(struct xthread *))
{
    xpthread * o = (xpthread *) calloc(sizeof(xpthread), 1);
    assertion(o == xnil, "calloc => %d", errno);

    o->run = run;
    o->on = __xpthread_on;
    o->off = __xpthread_off;

    return (xthread *) o;
}

xthread * xthreadrem(xthread * o, xvalget destructor)
{
    assertion(o == xnil, "o == xnil");

    o->off(o, destructor);

    free(o);

    return xnil;
}