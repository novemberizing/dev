#include <stdlib.h>
#include <stdio.h>

#include "../../thread.h"
#include "mutex.h"

extern xsyncposixmutex * xsyncposixmutex_new(void)
{
    xsyncposixmutex * sync = (xsyncposixmutex *) calloc(sizeof(xsyncposixmutex), 1);

    xassertion(sync == xnil, "");

    sync->rem = xsyncposixmutex_rem;

    sync->lock = xsyncposixmutex_lock;
    sync->unlock = xsyncposixmutex_unlock;
    sync->wait = xsyncposixmutex_wait;
    sync->wakeup = xsyncposixmutex_wakeup;

    sync->mutex = calloc(sizeof(pthread_mutex_t), 1);

    xvalueof(sync->mutex) = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    int ret = pthread_mutex_init(sync->mutex, xnil);

    xassertion(ret != xsuccess, "");

    return sync;
}

extern xsyncposixmutex * xsyncposixmutex_rem(xsyncposixmutex * o)
{
    xassertion(o == xnil, "");
    xassertion(o->rem != xsyncposixmutex_rem, "");

    if(o->condition)
    {
        pthread_cond_destroy(o->condition);
        free(o->condition);
    }
    if(o->mutex)
    {
        pthread_mutex_destroy(o->mutex);
        free(o->mutex);
    }
    free(o);

    return xnil;
}

extern xint32 xsyncposixmutex_lock(xsyncposixmutex * o)
{
    xassertion(o == xnil || o->mutex == xnil, "");

    int ret = pthread_mutex_lock(o->mutex);

    xassertion(ret != xsuccess, "");

    return ret == xsuccess ? xsuccess : xfail;
}

extern xint32 xsyncposixmutex_unlock(xsyncposixmutex * o)
{
    xassertion(o == xnil || o->mutex == xnil, "");

    int ret = pthread_mutex_unlock(o->mutex);

    xassertion(ret != xsuccess, "");

    return ret == xsuccess ? xsuccess : xfail;
}

extern xint32 xsyncposixmutex_wait(xsyncposixmutex * o, xint64 second, xint64 nanosecond)
{
    xassertion(o == xnil || o->mutex == xnil || o->condition == xnil, "");
    xassertion(second < 0 || nanosecond < 0, "");

    if(o->condition)
    {
        int ret = xsuccess;
        if(second > 0 || nanosecond > 0)
        {
            struct timespec spec;
            if((ret = clock_gettime(CLOCK_REALTIME, &spec)) == xsuccess)
            {
                spec.tv_sec  = spec.tv_sec + second;
                spec.tv_nsec = spec.tv_nsec + nanosecond;
                ret = pthread_cond_timedwait(o->condition, o->mutex, &spec);
                xassertion(ret != xsuccess, "");
            }
            else
            {
                xassertion(ret != xsuccess, "");
            }
        }
        else
        {
            ret = pthread_cond_wait(o->condition, o->mutex);
            xassertion(ret != xsuccess, "");
        }
        return ret == xsuccess ? xsuccess : xfail;
    }
    return xsuccess;
}

extern xint32 xsyncposixmutex_wakeup(xsyncposixmutex * o, xint32 all)
{
    xassertion(o == xnil || o->mutex == xnil || o->condition == xnil, "");

    if(o->condition)
    {
        int ret = xsuccess;
        if(all)
        {
            ret = pthread_cond_broadcast(o->condition);
            xassertion(ret != xsuccess, "");
        }
        else
        {
            ret = pthread_cond_signal(o->condition);
            xassertion(ret != xsuccess, "");
        }
    }
    return xsuccess;
}

extern xsyncposixmutex * xsyncposixcond_init(xsyncposixmutex * o)
{
    xassertion(o == xnil, "");

    if(o->condition == xnil)
    {
        o->condition = (pthread_cond_t *) calloc(sizeof(pthread_cond_t), 1);
        xvalueof(o->condition) = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

        int ret = pthread_cond_init(o->condition, xnil);

        xassertion(ret != xsuccess, "");
    }
    return o;
}

extern xsyncposixmutex * xsyncposixcond_term(xsyncposixmutex * o)
{
    xassertion(o == xnil, "");

    if(o->condition)
    {
        pthread_cond_destroy(o->condition);
        free(o->condition);
        o->condition = xnil;
    }
    return o;
}