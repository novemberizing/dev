#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "std.h"

static int __xsync_none_on(xsync * o)
{
    return xsuccess;
}

static int __xsync_none_off(xsync * o)
{
    return xsuccess;
}

static int __xsync_none_lock(xsync * o)
{
    return xsuccess;
}

static int __xsync_none_unlock(xsync * o)
{
    return xsuccess;
}

static int __xsync_none_wait(xsync * o, xuint64 nanosecond)
{
    return xsuccess;
}

static int __xsync_none_wakeup(xsync * o, int all)
{
    return xsuccess;
}

static int __xsync_none_condon(xsync * o)
{
    return xsuccess;
}

static int __xsync_none_condoff(xsync * o)
{
    return xsuccess;
}

static void * __xsync_none_rem(void * p)
{
    xsync * o = (xsync *) p;
    xassertion(xobjtype(o) != xobj_type_sync || xsynctype(o) != xsync_type_none, "xobjtype(o) != xobj_type_sync || xsynctype(o) != xsync_type_none");

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

static inline xsync * __xsync_none_new(void)
{
    xsync * o = (xsync *) calloc(sizeof(xsync), 1);
    xassertion(o == xnil, "o == xnil => calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_none;
    o->destruct = __xsync_none_rem;

    o->on = __xsync_none_on;
    o->off = __xsync_none_off;
    o->lock = __xsync_none_lock;
    o->unlock = __xsync_none_unlock;
    o->wait = __xsync_none_wait;
    o->wakeup = __xsync_none_wakeup;
    o->condon = __xsync_none_condon;
    o->condoff = __xsync_none_condoff;

    return o;
}

struct __xpmutex;

typedef struct __xpmutex __xpmutex;

struct __xpmutex
{
    xuint32 flags;
    destructor destruct;

    int (*on)(xsync *);
    int (*off)(xsync *);
    int (*lock)(xsync *);
    int (*unlock)(xsync *);
    int (*wait)(xsync *, xuint64);
    int (*wakeup)(xsync *, int);
    int (*condon)(xsync *);
    int (*condoff)(xsync *);

    pthread_mutex_t * mutex;
    pthread_cond_t * cond;
};

static int __xsync_mutex_on(xsync * p)
{
    __xpmutex * o = (__xpmutex *) p;
    xassertion(o == xnil, "o == xnil");

    xcheck(o->mutex, xsuccess, "o->mutex");

    if(o->mutex == xnil)
    {
        o->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
        *(o->mutex) = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    }

    return xsuccess;
}

static int __xsync_mutex_off(xsync * p)
{
    __xpmutex * o = (__xpmutex *) p;
    xassertion(o == xnil, "o == xnil");

    if(o->mutex)
    {
        pthread_mutex_destroy(o->mutex);
        free(o->mutex);
        o->mutex = xnil;
    }

    return xsuccess;
}

static int __xsync_mutex_condon(xsync * p)
{
    __xpmutex * o = (__xpmutex *) p;
    xassertion(o == xnil, "o == xnil");

    xcheck(o->cond, xsuccess, "o->mutex");

    if(o->cond == xnil)
    {
        o->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
        *(o->cond) = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    }

    return xsuccess;
}

static int __xsync_mutex_condoff(xsync * p)
{
    __xpmutex * o = (__xpmutex *) p;
    xassertion(o == xnil, "o == xnil");

    if(o->cond)
    {
        pthread_cond_destroy(o->cond);
        free(o->cond);
        o->cond = xnil;
    }

    return xsuccess;
}

static int __xsync_mutex_lock(xsync * p)
{
    __xpmutex * o = (__xpmutex *) p;
    xassertion(o == xnil, "o == xnil");

    if(o->mutex)
    {
        int ret = pthread_mutex_lock(o->mutex);
        xassertion(ret != xsuccess, "pthread_mutex_lock() => %d", ret);
    }

    return xsuccess;
}

static int __xsync_mutex_unlock(xsync * p)
{
    __xpmutex * o = (__xpmutex *) p;
    xassertion(o == xnil, "o == xnil");

    if(o->mutex)
    {
        int ret = pthread_mutex_unlock(o->mutex);
        xassertion(ret != xsuccess, "pthread_mutex_unlock() => %d", ret);
    }

    return xsuccess;
}

static int __xsync_mutex_wait(xsync * p, xuint64 nanosecond)
{
    __xpmutex * o = (__xpmutex *) p;
    xassertion(o == xnil, "o == xnil");

    if(o->mutex && o->cond)
    {
        if(nanosecond > 0)
        {
            struct timespec timespec = { nanosecond/1000000000, nanosecond % 1000000000 };
            int ret = pthread_cond_timedwait(o->cond, o->mutex, &timespec);
            xassertion(ret != xsuccess, "pthread_cond_timedwait() => %d", ret);
        }
        else
        {
            int ret = pthread_cond_wait(o->cond, o->mutex);
            xassertion(ret != xsuccess, "pthread_cond_wait() => %d", ret);
        }
    }

    return xsuccess;
}

static int __xsync_mutex_wakeup(xsync * p, int all)
{
    __xpmutex * o = (__xpmutex *) p;
    xassertion(o == xnil, "o == xnil");

    if(o->mutex && o->cond)
    {
        if(all)
        {
            int ret = pthread_cond_broadcast(o->cond);
            xassertion(ret != xsuccess, "pthread_cond_broadcast() => %d", ret);
        }
        else
        {
            int ret = pthread_cond_signal(o->cond);
            xassertion(ret != xsuccess, "pthread_cond_signal() => %d", ret);
        }
    }

    return xsuccess;
}

static void * __xsync_mutex_rem(void * p)
{
    xsync * o = (xsync *) p;
    xassertion(xobjtype(o) != xobj_type_sync || xsynctype(o) != xsync_type_mutex, "xobjtype(o) != xobj_type_sync || xsynctype(o) != xsync_type_mutex");
    
    __xsync_mutex_condoff(o);
    __xsync_mutex_off(o);

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

xsync * __xsync_mutex_new(void)
{
    __xpmutex * o = (__xpmutex *) calloc(sizeof(__xpmutex), 1);
    xassertion(o == xnil, "o == xnil");

    o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_mutex;
    o->destruct = __xsync_mutex_rem;

    o->on = __xsync_mutex_on;
    o->off = __xsync_mutex_off;
    o->lock = __xsync_mutex_lock;
    o->unlock = __xsync_mutex_unlock;
    o->wait = __xsync_mutex_wait;
    o->wakeup = __xsync_mutex_wakeup;
    o->condon = __xsync_mutex_condon;
    o->condoff = __xsync_mutex_condoff;

    return (xsync *) o;
}

/**
 * @fn      xsync * xsyncnew(xuint32 type)
 * @brief   동기화 객체를 생성합니다.
 * @details
 * 
 * @param   | type | in | uint32 | 동기화 객체 타입 |
 * 
 * @return  | xsync * | 생성된 동기화 객체 |
 */
xsync * xsyncnew(xuint32 type)
{
    if(type == xsync_type_none)
    {
        return __xsync_none_new();
    }
    else if(type == xsync_type_mutex)
    {
        return __xsync_mutex_new();
    }
    else
    {
        xassertion(xtrue, "unknown type");
    }
}

/**
 * @fn      void * xsyncrem(void * p)
 * @brief   생성된 동기화 객체를 메모리에서 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 객체의 주소 값 |
 */
void * xsyncrem(void * p)
{
    xsync * o = (xsync *) p;
    xcheck(o == xnil, xnil, "o == xnil");

    xassertion(xobjtype(o) != xobj_type_sync, "xobjtype(o) != xobj_type_sync");

    xuint32 type = o->flags & xsync_type_mask;

    switch(type)
    {
        case xsync_type_none: o = __xsync_none_rem(p); break;
        case xsync_type_mutex: o = __xsync_mutex_rem(p); break;
        default: xassertion(xtrue, "unknown type");
    }

    return o;
}