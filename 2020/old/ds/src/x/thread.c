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

static int __xthreadpool_routine(struct xthread * o)
{
    xthreadpool * pool = (xthreadpool *) o->parameter.ptr;
    assertion(pool == xnil, "pool == xnil");

    while((o->status & xthread_status_cancelling) != xthread_status_cancelling)
    {
        xsynclock(pool->queue->sync);
        while(pool->queue->size > 0)
        {
            xlistnode * node = pool->queue->head;
            xlistpop(pool->queue, xnil);
            xsyncunlock(pool->queue->sync);
            if(node)
            {
            }
            xsynclock(pool->queue->sync);
        }
        if(pool->queue->size == 0)
        {
            xsyncwait(pool->queue->sync, xnil);
        }
        xsyncunlock(pool->queue->sync);
    }

    return xsuccess;
}

xthreadpool * xthreadpoolnew(xuint32 n)
{
    xthreadpool * o = (xthreadpool *) calloc(sizeof(xthreadpool), 1);
    assertion(o == xnil, "calloc => %d", errno);

    o->threads = xlistnew();
    o->idles = xlistnew();
    o->idles->sync = xsyncnew(xsync_type_mutex);
    xsyncon(o->idles->sync, true);
    o->queue = xlistnew();
    o->queue->sync = xsyncnew(xsync_type_mutex);
    xsyncon(o->queue->sync, true);

    for(xuint32 i = 0; i < n; i++)
    {
        xthread * thread = xthreadnew(__xthreadpool_routine);
        xlistpush(o->threads, xvalgenptr(thread));
        xthreadon(thread, xvalgenptr(o));
        xlistpush(o->idles, xvalgenptr(thread));
    }

    return o;
}

xthreadpool * xthreadpoolrem(xthreadpool * o)
{
    assertion(o == xnil, "o == xnil");

    while(o->threads->head)
    {
        xthread * thread = (xthread *) o->threads->head->value.ptr;
        thread->status = (thread->status | xthread_status_cancelling);
    }
    xsyncwakeup(o->queue->sync, true);
    while(o->threads->head)
    {
        xthread * thread = (xthread *) o->threads->head->value.ptr;
        xthreadrem(thread, xnil);
        xlistpop(o->threads, xnil);
    }
    xlistrem(o->threads, xnil);
    xlistrem(o->idles, xnil);
    xlistrem(o->queue, xnil);

    free(o);

    return xnil;
}

xthread * xthreadpoolget(xthreadpool * o)
{
    xsynclock(o->idles->sync);
    xthread * thread = xlistpop(o->idles, xnil);
    xsyncunlock(o->idles->sync);
    return thread;
}