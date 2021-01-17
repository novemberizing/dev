#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "std.h"

struct __internal_mutex
{
    xuint32 flags;
    xdestructor destruct;

    xint32 (*lock)(xsync *);
    xint32 (*unlock)(xsync *);
    xint32 (*wait)(xsync *, xuint64);
    xint32 (*wakeup)(xsync *, xint32);

    pthread_mutex_t * mutex;
    pthread_cond_t * cond;
};

static void * __xsync_none_rem(void * p);
static xint32 __xsync_none_lock(xsync * o);
static xint32 __xsync_none_unlock(xsync * o);
static xint32 __xsync_none_wait(xsync * o, xuint64 nanosecond);
static xint32 __xsync_none_wakeup(xsync *o, xint32 all);

static void * __xsync_mutex_rem(void * p);
static xint32 __xsync_mutex_lock(xsync * o);
static xint32 __xsync_mutex_unlock(xsync * o);
static xint32 __xsync_mutex_wait(xsync * o, xuint64 nanosecond);
static xint32 __xsync_mutex_wakeup(xsync *o, xint32 all);

static inline xsync * __xsync_none_new()
{
    xsync * o = (xsync *) calloc(sizeof(xsync), 1);
    
    o->flags = xobj_mask_allocated | xsync_type_none | xobj_type_sync;
    o->destruct = __xsync_none_rem;
    o->lock = __xsync_none_lock;
    o->unlock = __xsync_none_unlock;
    o->wait = __xsync_none_wait;
    o->wakeup = __xsync_none_wakeup;

    return o;
}

static inline xsync * __xsync_mutex_new(void)
{
    struct __internal_mutex * o = (struct __internal_mutex *) calloc(sizeof(struct __internal_mutex), 1);

    o->flags = xobj_mask_allocated | xsync_type_mutex | xobj_type_sync;
    o->destruct = __xsync_mutex_rem;
    o->lock = __xsync_mutex_lock;
    o->unlock = __xsync_mutex_unlock;
    o->wait = __xsync_mutex_wait;
    o->wakeup = __xsync_mutex_wakeup;

    o->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    xassertion(o->mutex == xnil, "fail to malloc (%d)", errno);
    *o->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return (xsync *) o;
}

static inline xsync * __xsync_mutex_condon(struct __internal_mutex * o)
{
    xcheck(o->cond != xnil, "already condition is off");

    if(o->cond == xnil)
    {
        o->cond = (pthread_cond_t *) calloc(sizeof(pthread_cond_t), 1);
        xassertion(o->cond == xnil, "fail to calloc (%d)", errno);
        *o->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    }

    return (xsync *) o;
}

static inline xsync * __xsync_mutex_condoff(struct __internal_mutex * o)
{
    xcheck(o->cond == xnil, "already condition is off");

    if(o->cond)
    {
        int ret = pthread_cond_destroy(o->cond);
        xassertion(ret != xsuccess, "fail to pthread_cond_destroy (%d)", ret);
        free(o->cond);
        o->cond = xnil;
    }

    return (xsync *) o;
}

/**
 * @fn      extern xsync * xsyncnew(xuint32 type)
 * @brief
 */
extern xsync * xsyncnew(xuint32 type)
{
    switch(type)
    {
        case xsync_type_none:   return __xsync_none_new();
        case xsync_type_mutex:  return __xsync_mutex_new();
    }
    xassertion(xtrue, "unsupported type (%08x)", type);
}

/**
 * @fn      extern void * xsyncrem(void * p)
 * @brief   
 */
extern void * xsyncrem(void * p)
{
    xcheck(p == xnil, "null pointer");
    if(p)
    {
        xassertion(xobjtype(p) != xobj_type_sync, "invalid object (%d)", xobjtype(p));

        switch(xsynctype(p))
        {
            case xsync_type_none:   return __xsync_none_rem(p);
            case xsync_type_mutex:  return __xsync_mutex_rem(p);
        }

        xassertion(xtrue, "unsupported type (%d)", xsynctype(p));
    }
    return xnil;
}

extern xsync * xsynccondon(xsync * o)
{
    xcheck(o == xnil, "null pointer");

    switch(xsynctype(o))
    {
        case xsync_type_none:   return o;
        case xsync_type_mutex:  return __xsync_mutex_condon((struct __internal_mutex *) o);
    }

    xassertion(xtrue, "unsupported type (%d)", xsynctype(o));
}

extern xsync * xsynccondoff(xsync * o)
{
    xcheck(o == xnil, "null pointer");

    switch(xsynctype(o))
    {
        case xsync_type_none:   return o;
        case xsync_type_mutex:  return __xsync_mutex_condoff((struct __internal_mutex *) o);
    }
    
    xassertion(xtrue, "unsupported type (%d)", xsynctype(o));
}


/** INTERNAL */

static void * __xsync_none_rem(void * p)
{
    xassertion(xsynctype(p) != xsync_type_none, "invalid object");

    free(p);
    p == xnil;

    return p;
}

static xint32 __xsync_none_lock(xsync * o){ return xsuccess; }
static xint32 __xsync_none_unlock(xsync * o){ return xsuccess; }
static xint32 __xsync_none_wait(xsync * o, xuint64 nanosecond){ return xsuccess; }
static xint32 __xsync_none_wakeup(xsync *o, xint32 all){ return xsuccess; }

static void * __xsync_mutex_rem(void * p)
{
    xassertion(xsynctype(p) != xsync_type_mutex, "invalid object");

    struct __internal_mutex * o = (struct __internal_mutex *) p;
    
    if(o->cond)
    {
        xassertion(o->cond == xnil, "internal condition object is not allocated");
        int ret = pthread_cond_destroy(o->cond);
        xassertion(ret != xsuccess, "fail to pthread_cond_destroy (%d)", ret);
        free(o->cond);
    }

    int ret = pthread_mutex_destroy(o->mutex);
    xassertion(ret != xsuccess, "fail to pthread_mutex_destroy (%d)", ret);
    free(o->mutex);

    free(o);
    p == xnil;

    return p;
}

static xint32 __xsync_mutex_lock(xsync * o)
{
    int ret = pthread_mutex_lock(((struct __internal_mutex *) o)->mutex);
    xassertion(ret != xsuccess, "fail to pthread_mutex_lock (%d)", ret);
}

static xint32 __xsync_mutex_unlock(xsync * o)
{
    int ret = pthread_mutex_unlock(((struct __internal_mutex *) o)->mutex);
    xassertion(ret != xsuccess, "fail to pthread_mutex_lock (%d)", ret);
}

static xint32 __xsync_mutex_wait(xsync * p, xuint64 nanosecond)
{
    struct __internal_mutex * o = (struct __internal_mutex *) p;
    xcheck(o->cond == xnil, "null pointer");

    if(o->cond)
    {
        if(nanosecond > 0)
        {
            struct timespec timespec = { 0, };
            clock_gettime(CLOCK_REALTIME, &timespec);

            timespec.tv_nsec += (nanosecond % 1000000000);
            timespec.tv_sec  += ((nanosecond / 1000000000) + (timespec.tv_nsec / 1000000000));
            timespec.tv_nsec  = (timespec.tv_nsec - ((timespec.tv_nsec / 1000000000) * 1000000000));

            int ret = pthread_cond_timedwait(o->cond, o->mutex, &timespec);
            xassertion(ret != xsuccess && ret != ETIMEDOUT && ret != EINTR, "fail to pthread_cond_timedwait (%d)", ret);
        }
        else
        {
            int ret = pthread_cond_wait(o->cond, o->mutex);
            xassertion(ret != xsuccess, "fail to pthread_cond_wait (%d)", ret);
        }
    }
}

static xint32 __xsync_mutex_wakeup(xsync *p, xint32 all)
{
    struct __internal_mutex * o = (struct __internal_mutex *) p;
    xcheck(o->cond == xnil, "null pointer");
    
    if(o->cond)
    {
        if(all)
        {
            int ret = pthread_cond_broadcast(o->cond);
            xassertion(ret != xsuccess, "fail to pthread_cond_broadcast (%d)", ret);
        }
        else
        {
            int ret = pthread_cond_signal(o->cond);
            xassertion(ret != xsuccess, "fail to pthread_cond_signal (%d)", ret);
        }
    }
}