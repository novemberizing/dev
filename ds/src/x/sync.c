#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "log.h"
#include "sync.h"

static inline int __xsync_empty_on(struct xsync * o, int cond) { return xsuccess; }
static inline int __xsync_empty_off(struct xsync * o) { return xsuccess; }
static inline int __xsync_empty_lock(struct xsync * o) { return xsuccess; }
static inline int __xsync_empty_unlock(struct xsync * o) { return xsuccess; }
static inline int __xsync_empty_wait(struct xsync * o, const struct timespec * timespec) { return xsuccess; }
static inline int __xsync_empty_wakeup(struct xsync * o, int all) { return xsuccess; }

static inline xsync * __xsync_empty_new(void)
{
    xsync * o = (xsync *) calloc(sizeof(xsync), 1);

    assertion(o == xnil, "fail to __xsync_empty_new() caused by calloc (%d)", errno);

    o->type = xsync_type_empty;
    o->on = __xsync_empty_on;
    o->off = __xsync_empty_off;
    o->lock = __xsync_empty_lock;
    o->unlock = __xsync_empty_unlock;
    o->wait = __xsync_empty_wait;
    o->wakeup = __xsync_empty_wakeup;

    return o;
}

/**
 * 
 * @todo    pthread mutex attr
 */
struct __xmutex
{
    xuint32 type;
    int (*on)(struct xsync *, int cond);
    int (*off)(struct xsync *);
    int (*lock)(struct xsync *);
    int (*unlock)(struct xsync *);
    int (*wait)(struct xsync *, const struct timespec *);
    int (*wakeup)(struct xsync *, int);
    pthread_mutex_t * mutex;
    pthread_cond_t * condition;
};

typedef struct __xmutex xmutex;

static inline int __xsync_mutex_on(xsync * p, int cond)
{
    xmutex * o = (xmutex *) p;

    assertion(o == xnil || o->type != xsync_type_mutex, "o == xnil || o->type != xsync_type_mutex");

    if(o->mutex == xnil)
    {
        o->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));

        assertion(o->mutex == xnil, "malloc => %d", errno);

        *o->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    }

    if(cond)
    {
        if(o->condition == xnil)
        {
            o->condition = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));

            assertion(o->condition == xnil, "malloc => %d", errno);

            *o->condition = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
        }
    }

    return xsuccess;
}

static inline int __xsync_mutex_off(xsync * p)
{
    xmutex * o = (xmutex *) p;

    assertion(o == xnil || o->type != xsync_type_mutex, "o == xnil || o->type != xsync_type_mutex");

    if(o->mutex)
    {
        int ret = pthread_mutex_destroy(o->mutex);

        assertion(ret != xsuccess, "pthread_mutex_destroy => %d", errno);

        free(o->mutex);
        o->mutex = xnil;
    }

    if(o->condition)
    {
        int ret = pthread_cond_destroy(o->condition);

        free(o->condition);
        o->condition = xnil;
    }

    return xsuccess;
}

static inline int __xsync_mutex_lock(xsync * p)
{
    xmutex * o = (xmutex *) p;

    assertion(o == xnil || o->type != xsync_type_mutex, "o == xnil || o->type != xsync_type_mutex");

    if(o->mutex)
    {
        pthread_mutex_lock(o->mutex);
        return xsuccess;
    }

    return xfail;
}

static inline int __xsync_mutex_unlock(xsync * p)
{
    xmutex * o = (xmutex *) p;

    assertion(o == xnil || o->type != xsync_type_mutex, "o == xnil || o->type != xsync_type_mutex");

    if(o->mutex)
    {
        pthread_mutex_unlock(o->mutex);
        return xsuccess;
    }
    
    return xfail;
}

static inline int __xsync_mutex_wait(xsync * p, const struct timespec * timespec)
{
    xmutex * o = (xmutex *) p;
    int ret;

    assertion(o == xnil || o->type != xsync_type_mutex, "o == xnil || o->type != xsync_type_mutex");

    if(o->condition && o->mutex)
    {
        if(timespec)
        {
            ret = pthread_cond_timedwait(o->condition, o->mutex, timespec);
            assertion(ret != xsuccess, "pthread_cond_timedwait => %d", errno);
        }
        else
        {
            ret = pthread_cond_wait(o->condition, o->mutex);
            assertion(ret != xsuccess, "pthread_cond_wait => %d", errno);
        }
    }
    else
    {
        assertion(o->condition != xnil && o->mutex == xnil, "o->condition != xnil && o->mutex == xnil");
    }

    return xsuccess;
}

static inline int __xsync_mutex_wakeup(xsync * p, int all)
{
    xmutex * o = (xmutex *) p;
    int ret;

    assertion(o == xnil || o->type != xsync_type_mutex, "o == xnil || o->type != xsync_type_mutex");

    if(o->condition && o->mutex)
    {
        if(all)
        {
            ret = pthread_cond_broadcast(o->condition);
            assertion(ret != xsuccess, "pthread_cond_broadcast => %d", errno);
        }
        else
        {
            ret = pthread_cond_signal(o->condition);
            assertion(ret != xsuccess, "pthread_cond_signal => %d", errno);
        }
    }
    else
    {
        assertion(o->condition != xnil && o->mutex == xnil, "o->condition != xnil && o->mutex == xnil");
    }

    return xsuccess;
}

static inline xmutex * __xsync_mutex_new(void)
{
    xmutex * o = (xmutex *) calloc(sizeof(xmutex), 1);

    assertion(o == xnil, "fail to __xsync_mutex_new caused by calloc (%d)", errno);

    o->type = xsync_type_mutex;
    o->on = __xsync_mutex_on;
    o->off = __xsync_mutex_off;
    o->lock = __xsync_mutex_lock;
    o->unlock = __xsync_mutex_unlock;
    o->wait = __xsync_mutex_wait;
    o->wakeup = __xsync_mutex_wakeup;

    return o;
}

xsync * xsyncnew(xuint32 type)
{
    switch(type)
    {
        case xsync_type_empty:  return __xsync_empty_new();
        case xsync_type_mutex:  return (xsync *) __xsync_mutex_new();
    }
    return xnil;
}

xsync * xsyncrem(xsync * o)
{
    if(o)
    {
        o->off(o);
        free(o);
    }
    return xnil;
}