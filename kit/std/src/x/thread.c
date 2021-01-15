/**
 * @file    x/thread.c
 * 
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "std.h"

static inline pthread_cond_t * __xsync_pthread_condoff(pthread_cond_t * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        // TODO: IMPLEMENT CHECK FUNCTION
        pthread_cond_destroy(o);
        free(o);
    }
    return xnil;
}

static inline pthread_mutex_t * __xsync_pthread_mutexoff(pthread_mutex_t * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        // TODO: IMPLEMENT CHECK FUNCTION
        pthread_mutex_destroy(o);
        free(o);
    }
    return xnil;
}

static void * __xsync_none_free(void * p);
static xint32 __xsync_none_lock(xsync * o);
static xint32 __xsync_none_unlock(xsync * o);
static xint32 __xsync_none_wait(xsync * o, xuint64 nanosecond);
static xint32 __xsync_none_wakeup(xsync * o, xint32 all);

static void * __xsync_mutex_free(void * p);
static xint32 __xsync_mutex_lock(xsync * o);
static xint32 __xsync_mutex_unlock(xsync * o);
static xint32 __xsync_mutex_wait(xsync * o, xuint64 nanosecond);
static xint32 __xsync_mutex_wakeup(xsync * o, xint32 all);

static inline xsync * __xsync_none_new(void)
{
    xsync * o = (xsync *) calloc(sizeof(xsync), 1);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_none;
    o->free  = __xsync_none_free;
    o->lock = __xsync_none_lock;
    o->unlock = __xsync_none_unlock;
    o->wait = __xsync_none_wait;
    o->wakeup = __xsync_none_wakeup;

    return o;
}

struct __mutex
{
    xuint32 flags;
    destructor free;

    xint32 (*lock)(xsync *);
    xint32 (*unlock)(xsync *);
    xint32 (*wait)(xsync *, xuint64);
    xint32 (*wakeup)(xsync *, xint32);

    pthread_mutex_t * mutex;
    pthread_cond_t * cond;
};

static inline xsync * __xsync_mutex_new(void)
{
    struct __mutex * o = (struct __mutex *) calloc(sizeof(struct __mutex), 1);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_mutex;

    o->free  = __xsync_mutex_free;
    o->lock = __xsync_mutex_lock;
    o->unlock = __xsync_mutex_unlock;
    o->wait = __xsync_mutex_wait;
    o->wakeup = __xsync_mutex_wakeup;

    return (xsync *) o;
}

static inline xint32 __xsync_mutex_on(struct __mutex * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xcheck(o->mutex != xnil, "already mutex created");
        if(o->mutex == xnil)
        {
            o->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
            xassertion(o->mutex == xnil, "fail to calloc (%d)", errno);
            *(o->mutex) = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
        }
    }
    return xsuccess;
}

static inline xint32 __xsync_mutex_off(struct __mutex * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xcheck(o->mutex, "already mutex destroyed");
        if(o->mutex)
        {
            int ret = pthread_mutex_destroy(o->mutex);
            xassertion(ret != xsuccess, "fail to pthread_mutex_destroy (%d)", ret);

            free(o->mutex);
            o->mutex = xnil;

            if(o->cond)
            {
                ret = pthread_cond_destroy(o->cond);
                xassertion(ret != xsuccess, "fail to pthread_cond_destroy (%d)", ret);

                free(o->cond);
                o->cond = xnil;
            }
        }
    }
    return xsuccess;
}

static inline xint32 __xsync_cond_on(struct __mutex * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        if(o->mutex == xnil)
        {
            xcheck(xtrue, "mutex not created");
            o->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
            xassertion(o->mutex == xnil, "fail to malloc (%d)", errno);
            *(o->mutex) = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
        }
        xcheck(o->cond != xnil, "already cond created");
        if(o->cond == xnil)
        {
            o->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
            xassertion(o->cond == xnil, "fail to malloc (%d)", errno);
            *(o->cond) = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
        }
    }
    return xsuccess;
}

static inline xint32 __xsync_cond_off(struct __mutex * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xcheck(o->cond == xnil, "already cond destroyed");
        if(o->cond)
        {
            int ret = pthread_cond_destroy(o->cond);
            xassertion(ret != xsuccess, "fail to pthread_cond_destroy (%d)", ret);

            free(o->cond);
            o->cond = xnil;
        }
    }
    return xsuccess;
}

/**
 * @fn      xuint64 xthreadid(void)
 * @brief
 * 
 * @return  | xuint64 | 스레드 아이디 |
 */
xuint64 xthreadid(void)
{
    return pthread_self();
}

xsync * xsyncnew(xuint32 type)
{
    switch(type & xsync_mask_types)
    {
        case xsync_type_none:   return __xsync_none_new();
        case xsync_type_mutex:  return __xsync_mutex_new();
    }
    xassertion(xtrue, "unsupported type");
}

xint32 xsyncon(xsync * p)
{
    xsync * o = (xsync *) p;
    xcheck(o == xnil, "null pointer");

    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none:   return xsuccess;
        case xsync_type_mutex:  return __xsync_mutex_on((struct __mutex *) o);
    }
    xassertion(xtrue, "unsupported type");
}

xint32 xsyncoff(xsync * p)
{
    xsync * o = (xsync *) p;
    xcheck(o == xnil, "null pointer");

    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none:   return xsuccess;
        case xsync_type_mutex:  return __xsync_mutex_off((struct __mutex *) o);
    }
    xassertion(xtrue, "unsupported type");
}

xint32 xcondon(xsync * p)
{
    xsync * o = (xsync *) p;
    xcheck(o == xnil, "null pointer");

    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none:   return xsuccess;
        case xsync_type_mutex:  return __xsync_cond_on((struct __mutex *) o);
    }
    xassertion(xtrue, "unsupported type");
}

xint32 xcondoff(xsync * p)
{
    xsync * o = (xsync *) p;
    xcheck(o == xnil, "null pointer");

    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none:   return xsuccess;
        case xsync_type_mutex:  return __xsync_cond_off((struct __mutex *) o);
    }
    xassertion(xtrue, "unsupported type");
}

/** SYNC */

static void * __xsync_none_free(void * p)
{
    xsync * o = (xsync *) p;
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xassertion(xobjtype(o) != xobj_type_sync, "invalid object");
        xassertion(xsynctype(o) != xsync_type_none, "invalid sync type");

        if(o->flags & xobj_mask_allocated)
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}

static xint32 __xsync_none_lock(xsync * o)
{
    return xsuccess;
}

static xint32 __xsync_none_unlock(xsync * o)
{
    return xsuccess;
}

static xint32 __xsync_none_wait(xsync * o, xuint64 nanosecond)
{
    return xsuccess;
}

static xint32 __xsync_none_wakeup(xsync * o, xint32 all)
{
    return xsuccess;
}

static void * __xsync_mutex_free(void * p)
{
    struct __mutex * o = (struct __mutex *) p;
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        o->mutex = __xsync_pthread_mutexoff(o->mutex);
        o->cond = __xsync_pthread_condoff(o->cond);

        if(o->flags & xobj_mask_allocated)
        {
            free(o);
            o = xnil;
        }
    }

    return o;
}

static xint32 __xsync_mutex_lock(xsync * p)
{
    struct __mutex * o = (struct __mutex *) p;
    xcheck(o == xnil, "null pointer");

    if(o && o->mutex)
    {
        int ret = pthread_mutex_lock(o->mutex);
        xassertion(ret != xsuccess, "fail to pthread_mutex_lock (%d)", errno);
    }
    return xsuccess;
}

static xint32 __xsync_mutex_unlock(xsync * p)
{
    struct __mutex * o = (struct __mutex *) p;
    xcheck(o == xnil, "null pointer");

    if(o && o->mutex)
    {
        int ret = pthread_mutex_unlock(o->mutex);
        xassertion(ret != xsuccess, "fail to pthread_mutex_unlock (%d)", errno);
    }
    return xsuccess;
}

static xint32 __xsync_mutex_wait(xsync * p, xuint64 nanosecond)
{
    struct __mutex * o = (struct __mutex *) p;
    xcheck(o == xnil, "null pointer");
    xassertion(o->cond && o->mutex == xnil, "mutex is not allocated");

    if(o && o->cond && o->mutex)
    {
        if(nanosecond > 0)
        {
            struct timespec timespec = (struct timespec) { nanosecond / 1000000000, nanosecond % 1000000000 };
            int ret = pthread_cond_timedwait(o->cond, o->mutex, &timespec);
            if(ret != ETIMEDOUT && ret != EINTR)
            {
                xassertion(ret != xsuccess, "fail to pthread_cond_timedwait (%d)", ret);
            }
        }
        else
        {
            pthread_cond_wait(o->cond, o->mutex);
        }
    }
    return xsuccess;
}

static xint32 __xsync_mutex_wakeup(xsync * p, xint32 all)
{
    struct __mutex * o = (struct __mutex *) p;
    xcheck(o == xnil, "null pointer");

    if(o && o->cond)
    {
        if(all)
        {
            pthread_cond_broadcast(o->cond);
        }
        else
        {
            pthread_cond_signal(o->cond);
        }
    }
    return xsuccess;
}
