#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "std.h"

static xsync * xsync_none_new(void);
static void * xsync_none_rem(void * p);
static xsync * xsync_none_on(xsync * o);
static xsync * xsync_none_off(xsync * o);
static xsync * xsync_none_condon(xsync * o);
static xsync * xsync_none_condoff(xsync * o);

static int xsync_none_lock(xsync * o);
static int xsync_none_unlock(xsync * o);
static int xsync_none_wait(xsync * o, xuint64 nanosecond);
static int xsync_none_wakeup(xsync * o, xuint32 all);

static xsync * xsync_mutex_new(void);
static void * xsync_mutex_rem(void * p);
static xsync * xsync_mutex_on(xsync * o);
static xsync * xsync_mutex_off(xsync * o);
static xsync * xsync_mutex_condon(xsync * o);
static xsync * xsync_mutex_condoff(xsync * o);

static int xsync_mutex_lock(xsync * o);
static int xsync_mutex_unlock(xsync * o);
static int xsync_mutex_wait(xsync * o, xuint64 nanosecond);
static int xsync_mutex_wakeup(xsync * o, xuint32 all);

/**
 * @fn      xsync * xsyncnew(xuint32 type)
 * @brief   동기화 객체를 생성합니다.
 * @details
 * 
 * @param   | type | in | xuint32 | 동기화 객체의 타입 |
 * 
 * @return  | xsync * | 생성된 동기화 객체 |
 */
xsync * xsyncnew(xuint32 type)
{
    switch(type)
    {
        case xsync_type_none:   return xsync_none_new();
        case xsync_type_mutex:  return xsync_mutex_new();
    }
    xassertion(xtrue, "unsupported type");
}

/**
 * @fn      void * xsyncrem(void * p)
 * @brief   동기화 객체를 메모리 상에서 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 동기화 객체의 메모리 주소값 |
 * 
 * @return  | void * | 해제한 메모리의 주소 값 |
 */
void * xsyncrem(void * p)
{
    xsync * o = (xsync *) p;
    xcheck(o == xnil, xnil, "invalid parameter (p == xnil)");
    xassertion(xobjtype(o) != xobj_type_sync, "object is not sync");

    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_rem(p);
        case xsync_type_mutex: return xsync_mutex_rem(p);
    }
    xassertion(xtrue, "unsupported type");
}

/**
 * @fn      xsync * xsyncon(xsync * o)
 * @brief   동기화 객체를 활성화시킨다.
 * @details
 * 
 * @param   | o | in | xsync * | 동기화 객체 |
 * 
 * @return  | xsync * | 동기화 객체 |
 */
xsync * xsyncon(xsync * o)
{
    xassertion(o == xnil, "invalid parameter (o == xnil");
    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_on(o);
        case xsync_type_mutex: return xsync_mutex_on(o);
    }
    return o;
}

/**
 * @fn      xsync * xsyncoff(xsync * o)
 * @brief   활성화된 동기화 객체를 비활성화 시킨다.
 * @details
 * 
 * @param   | o | in | xsync * | 동기화 객체 |
 * 
 * @return  | xsync * | 동기화 객체 |
 */
xsync * xsyncoff(xsync * o)
{
    xassertion(o == xnil, "invalid parameter (o == xnil");
    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_off(o);
        case xsync_type_mutex: return xsync_mutex_off(o);
    }
    return o;
}

/**
 * @fn      xsync * xsynccondon(xsync * o)
 * @brief   동기화 객체의 컨디션을 활성화 시킨다.
 * @details
 * 
 * @param   | o | in | xsync * | 동기화 객체 |
 * 
 * @return  | xsync * | 동기화 객체 |
 */
xsync * xsynccondon(xsync * o)
{
    xassertion(o == xnil, "invalid parameter (o == xnil");
    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_condon(o);
        case xsync_type_mutex: return xsync_mutex_condon(o);
    }
    return o;
}

/**
 * @fn      xsync * xsynccondoff(xsync * o)
 * @brief   동기화 객체의 컨디션을 비활성화 시킨다.
 * @details
 * 
 * @param   | o | in | xsync * | 동기화 객체 |
 * 
 * @return  | xsync * | 동기화 객체 |
 */
xsync * xsynccondoff(xsync * o)
{
    xassertion(o == xnil, "invalid parameter (o == xnil");
    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_condoff(o);
        case xsync_type_mutex: return xsync_mutex_condoff(o);
    }
    return o;
}



static xsync * xsync_none_new(void)
{
    xsync * o = (xsync *) malloc(sizeof(xsync));

    o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_none;
    o->destruct = xsync_none_rem;

    o->lock = xsync_none_lock;
    o->unlock = xsync_none_unlock;
    o->wait = xsync_none_wait;
    o->wakeup = xsync_none_wakeup;

    return o;
}

static void * xsync_none_rem(void * p)
{
    xsync * o = (xsync *) p;

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

static xsync * xsync_none_on(xsync * o)
{
    return o;
}

static xsync * xsync_none_off(xsync * o)
{
    return o;
}

static xsync * xsync_none_condon(xsync * o)
{
    return o;
}

static xsync * xsync_none_condoff(xsync * o)
{
    return o;
}

static int xsync_none_lock(xsync * o)
{
    return xsuccess;
}

static int xsync_none_unlock(xsync * o)
{
    return xsuccess;
}

static int xsync_none_wait(xsync * o, xuint64 nanosecond)
{
    return xsuccess;
}

static int xsync_none_wakeup(xsync * o, xuint32 all)
{
    return xsuccess;
}

struct xpmutexsync;

typedef struct xpmutexsync xpmutexsync;

struct xpmutexsync
{
    xuint32     flags;
    xdestructor destruct;

    int (*lock)(xsync *);
    int (*unlock)(xsync *);
    int (*wait)(xsync *, xuint64);
    int (*wakeup)(xsync *, xuint32);

    pthread_mutex_t * mutex;
    pthread_cond_t * cond;
};

static xsync * xsync_mutex_new(void)
{
    xpmutexsync * o = (xpmutexsync *) calloc(sizeof(xpmutexsync), 1);

    o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_mutex;
    o->destruct = xsync_mutex_rem;

    o->lock = xsync_mutex_lock;
    o->unlock = xsync_mutex_unlock;
    o->wait = xsync_mutex_wait;
    o->wakeup = xsync_mutex_wakeup;

    return (xsync *) o;
}

static void * xsync_mutex_rem(void * p)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, xnil, "invalid parameter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");

    xsyncoff((xsync *) o);
    xsynccondoff((xsync *) o);

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

static xsync * xsync_mutex_on(xsync * p)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, (xsync *) o, "invalid paramter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");

    xcheck(o->mutex, (xsync * ) o, "mutex is already created");

    o->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
    xassertion(o->mutex == xnil, "fail to malloc (%d)", errno);

    *o->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    return (xsync * ) o;
}

static xsync * xsync_mutex_off(xsync * p)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, (xsync * ) o, "invalid paramter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");

    xcheck(o->mutex == xnil, (xsync * ) o, "mutex is already destroyed");

    int ret = pthread_mutex_destroy(o->mutex);
    xassertion(ret != xsuccess, "fail to pthread_mutex_destroy (%d)", errno);

    free(o->mutex);
    o->mutex = xnil;

    return (xsync * ) o;
}

static xsync * xsync_mutex_condon(xsync * p)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, (xsync * ) o, "invalid paramter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");

    xcheck(o->cond, (xsync * ) o, "mutex condition is already created");

    o->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    xassertion(o->cond == xnil, "fail to malloc (%d)", errno);

    *o->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    return (xsync * ) o;
}

static xsync * xsync_mutex_condoff(xsync * p)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, (xsync * ) o, "invalid paramter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");

    xcheck(o->cond == xnil, (xsync * ) o, "mutex is already destroyed");

    int ret = pthread_cond_destroy(o->cond);
    xassertion(ret != xsuccess, "fail to pthread_cond_destroy (%d)", errno);

    free(o->cond);
    o->cond = xnil;

    return (xsync * ) o;
}

static int xsync_mutex_lock(xsync * p)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, xsuccess, "invalid paramter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");

    if(o->mutex)
    {
        int ret = pthread_mutex_lock(o->mutex);
        xassertion(ret != xsuccess, "fail to pthread_mutex_lock (%d)", errno);
    }

    return xsuccess;
}

static int xsync_mutex_unlock(xsync * p)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, xsuccess, "invalid paramter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");

    if(o->mutex)
    {
        int ret = pthread_mutex_unlock(o->mutex);
        xassertion(ret != xsuccess, "fail to pthread_mutex_unlock (%d)", errno);
    }

    return xsuccess;
}

static int xsync_mutex_wait(xsync * p, xuint64 nanosecond)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, xsuccess, "invalid paramter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");
    
    if(o->cond)
    {
        if(nanosecond)
        {
            struct timespec timespec = { nanosecond / 1000000000, nanosecond % 1000000000 };
            int ret = pthread_cond_timedwait(o->cond, o->mutex, &timespec);
            xassertion(ret != xsuccess, "fail to pthread_cond_timedwait (%d)", errno);
        }
        else
        {
            int ret = pthread_cond_wait(o->cond, o->mutex);
            xassertion(ret != xsuccess, "fail to pthread_cond_wait (%d)", errno);
        }
    }
    
    return xsuccess;
}

static int xsync_mutex_wakeup(xsync * p, xuint32 all)
{
    xpmutexsync * o = (xpmutexsync *) p;
    xcheck(o == xnil, xsuccess, "invalid paramter (p == xnil)");

    xassertion(xobjtype(o) != xobj_type_sync && xsynctype(o) != xsync_type_mutex, "object is not sync and mutex");
    
    if(o->cond)
    {
        if(all)
        {
            int ret = pthread_cond_broadcast(o->cond);
            xassertion(ret != xsuccess, "fail to pthread_cond_broadcast (%d)", errno);
        }
        else
        {
            int ret = pthread_cond_signal(o->cond);
            xassertion(ret != xsuccess, "fail to pthread_cond_signal (%d)", errno);
        }
    }
    
    return xsuccess;
}
