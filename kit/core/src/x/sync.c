/**
 * @file    x/sync.c
 * @brief   표준 동기화 객체와 관련된 구현 소스 파일입니다.
 * @details
 * 
 */

#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "std.h"

static inline int xsync_none_lock(xsync * o){ return xsuccess; }
static inline int xsync_none_unlock(xsync * o){ return xsuccess; }
static inline int xsync_none_wait(xsync * o, xuint64 nanosecond){ return xsuccess; }
static inline int xsync_none_wakeup(xsync * o, xuint32 all){ return xsuccess; }

static inline void * xsync_none_rem(void * p)
{
    xsync * o = (xsync *) p;
    xassertion(o == xnil || xsynctype(o) != xsync_type_none, xfail, "invalid parameter");

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

static inline xsync * xsync_none_new(void)
{
    xsync * o = (xsync *) calloc(sizeof(xsync), 1);

    o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_none;
    o->destruct = xsync_none_rem;

    o->lock = xsync_none_lock;
    o->unlock = xsync_none_unlock;
    o->wait = xsync_none_wait;
    o->wakeup = xsync_none_wakeup;

    return o;
}



static inline xsync * xsync_none_on(xsync * o){ return o; }
static inline xsync * xsync_none_off(xsync * o){ return o; }
static inline xsync * xsync_none_condon(xsync * o){ return o; }
static inline xsync * xsync_none_condoff(xsync * o){ return o; }

static int xsync_mutex_lock(xsync * p);
static int xsync_mutex_unlock(xsync * p);
static int xsync_mutex_wait(xsync * p, xuint64 nanosecond);
static int xsync_mutex_wakeup(xsync * p, xuint32 all);
static xsync * xsync_mutex_new(void);
static void * xsync_mutex_rem(void * p);
static xsync * xsync_mutex_on(xsync * p);
static xsync * xsync_mutex_off(xsync * p);
static xsync * xsync_mutex_condon(xsync * p);
static xsync * xsync_mutex_condoff(xsync * p);

xsync * xsyncnew(xuint32 type)
{
    switch(type)
    {
        case xsync_type_none: return xsync_none_new();
        case xsync_type_mutex: return xsync_mutex_new();
    }
    xassertion(xtrue, xfail, "unsupported sync type");
}

void * xsyncrem(void * p)
{
    xsync * o = (xsync *) p;
    xassertion(o == xnil, xfail, "invalid parameter");

    return o->destruct(o);
}

xsync * xsyncon(xsync * o)
{
    xassertion(o == xnil, xfail, "invalid parameter");
    switch(xsynctype(o))
    {
        case xsync_type_none: return xsync_none_on(o);
        case xsync_type_mutex: return xsync_mutex_on(o);
    }
    xassertion(xtrue, xfail, "unsupported sync type");
}

xsync * xsyncoff(xsync * o)
{
    xassertion(o == xnil, xfail, "invalid parameter");
    switch(xsynctype(o))
    {
        case xsync_type_none: return xsync_none_off(o);
        case xsync_type_mutex: return xsync_mutex_off(o);
    }
    xassertion(xtrue, xfail, "unsupported sync type");
}

xsync * xsynccondon(xsync * o)
{
    xassertion(o == xnil, xfail, "invalid parameter");
    switch(xsynctype(o))
    {
        case xsync_type_none: return xsync_none_condon(o);
        case xsync_type_mutex: return xsync_mutex_condon(o);
    }
    xassertion(xtrue, xfail, "unsupported sync type");
}

xsync * xsynccondoff(xsync * o)
{
    xassertion(o == xnil, xfail, "invalid parameter");
    switch(xsynctype(o))
    {
        case xsync_type_none: return xsync_none_condoff(o);
        case xsync_type_mutex: return xsync_mutex_condoff(o);
    }
    xassertion(xtrue, xfail, "unsupported sync type");
}

struct xpmutex;

typedef struct xpmutex xpmutex;

struct xpmutex
{
    xuint32 flags;
    xdestructor destruct;

    int (*lock)(xsync *);
    int (*unlock)(xsync *);
    int (*wait)(xsync *, xuint64);
    int (*wakeup)(xsync *, xuint32);

    pthread_mutex_t * mutex;
    pthread_cond_t * cond;
};

static int xsync_mutex_lock(xsync * p)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || o->mutex == xnil, xfail, "invalid parameter");

    int ret = pthread_mutex_lock(o->mutex);

    xassertion(ret != xsuccess, xfail, "fail to pthread_mutex_lock (%d)", ret);

    return xsuccess;
}

static int xsync_mutex_unlock(xsync * p)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || o->mutex == xnil, xfail, "invalid parameter");

    int ret = pthread_mutex_unlock(o->mutex);

    xassertion(ret != xsuccess, xfail, "fail to pthread_mutex_unlock (%d)", ret);

    return xsuccess;
}

static int xsync_mutex_wait(xsync * p, xuint64 nanosecond)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || o->mutex == xnil || o->cond == xnil, xfail, "invalid parameter");

    if(nanosecond > 0)
    {
        struct timespec timespec = { nanosecond / 1000000000, nanosecond % 1000000000 };
        int ret = pthread_cond_timedwait(o->cond, o->mutex, &timespec);
        xassertion(ret != xsuccess && ret != ETIMEDOUT && ret != EINTR, xfail, "fail to pthread_cond_timedwait (%d)", ret);
    }
    else
    {
        int ret = pthread_cond_wait(o->cond, o->mutex);
        xassertion(ret != xsuccess && ret != ETIMEDOUT && ret != EINTR, xfail, "fail to pthread_cond_wait (%d)", ret);
    }

    return xsuccess;
}

static int xsync_mutex_wakeup(xsync * p, xuint32 all)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || o->cond == xnil, xfail, "invalid parameter");

    if(all)
    {
        int ret = pthread_cond_broadcast(o->cond);
        xassertion(ret != xsuccess, xfail, "fail to pthread_cond_broadcast (%d)", ret);
    }
    else
    {
        int ret = pthread_cond_signal(o->cond);
        xassertion(ret != xsuccess, xfail, "fail to pthread_cond_signal (%d)", ret);
    }

    return xsuccess;
}

static xsync * xsync_mutex_new(void)
{
    xsync * o = (xsync *) calloc(sizeof(xpmutex), 1);

    o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_mutex;
    o->destruct = xsync_mutex_rem;

    o->lock = xsync_mutex_lock;
    o->unlock = xsync_mutex_unlock;
    o->wait = xsync_mutex_wait;
    o->wakeup = xsync_mutex_wakeup;

    return o;
}

static void * xsync_mutex_rem(void * p)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || xsynctype(o) != xsync_type_mutex, xfail, "invalid parameter");

    xsync_mutex_condoff((xsync *) o);
    xsync_mutex_off((xsync *) o);

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

static xsync * xsync_mutex_on(xsync * p)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || xsynctype(o) != xsync_type_mutex, xfail, "invalid parameter");

    if(o->mutex == xnil)
    {
        o->mutex = malloc(sizeof(pthread_mutex_t));
        *o->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    }

    return (xsync *) o;
}

static xsync * xsync_mutex_off(xsync * p)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || xsynctype(o) != xsync_type_mutex, xfail, "invalid parameter");

    if(o->mutex)
    {
        int ret = pthread_mutex_destroy(o->mutex);
        xassertion(ret != xsuccess, xfail, "fail to pthread_mutex_destroy (%d)", ret);
        free(o->mutex);
        o->mutex = xnil;
    }

    return (xsync *) o;
}

static xsync * xsync_mutex_condon(xsync * p)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || xsynctype(o) != xsync_type_mutex, xfail, "invalid parameter");

    if(o->cond == xnil)
    {
        o->cond = malloc(sizeof(pthread_cond_t));
        *o->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    }

    return (xsync *) o;
}

static xsync * xsync_mutex_condoff(xsync * p)
{
    xpmutex * o = (xpmutex *) p;
    xassertion(o == xnil || xsynctype(o) != xsync_type_mutex, xfail, "invalid parameter");

    if(o->cond)
    {
        int ret = pthread_cond_destroy(o->cond);
        xassertion(ret != xsuccess, xfail, "fail to pthread_cond_destroy (%d)", ret);
        free(o->cond);
        o->cond = xnil;
    }

    return (xsync *) o;
}