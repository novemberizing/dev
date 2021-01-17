/**
 * @fn      x/thread.c
 * @brief   표준 스레드 라이브러리 구현
 * @details
 * 
 * @version 0.0.1
 */

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

struct __internal_thread
{

};

static void * __xsync_none_rem(void * p);
static xint32 __xsync_none_lock(xsync * o);
static xint32 __xsync_none_unlock(xsync * o);
static xint32 __xsync_none_wait(xsync * o, xuint64 nanosecond);
static xint32 __xsync_none_wakeup(xsync *o, xint32 all);

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

static void * __xsync_mutex_rem(void * p);
static xint32 __xsync_mutex_lock(xsync * o);
static xint32 __xsync_mutex_unlock(xsync * o);
static xint32 __xsync_mutex_wait(xsync * o, xuint64 nanosecond);
static xint32 __xsync_mutex_wakeup(xsync *o, xint32 all);

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

extern xthread * xthreadnew(xthreadfunc func, xobj * param)
{

}

extern void * xthreadrem(void * p);
extern xthread * xthreadon(xthread * o);
extern xthread * xthreadoff(xthread * o);

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

// /**
//  * @file    x/thread.c
//  * 
//  */

// #include <pthread.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <errno.h>
// #include <sys/time.h>

// #include "std.h"

// static inline pthread_cond_t * __xsync_pthread_condoff(pthread_cond_t * o)
// {
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         // TODO: IMPLEMENT CHECK FUNCTION
//         pthread_cond_destroy(o);
//         free(o);
//     }
//     return xnil;
// }

// static inline pthread_mutex_t * __xsync_pthread_mutexoff(pthread_mutex_t * o)
// {
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         // TODO: IMPLEMENT CHECK FUNCTION
//         pthread_mutex_destroy(o);
//         free(o);
//     }
//     return xnil;
// }

// static void * __xsync_none_free(void * p);
// static xint32 __xsync_none_lock(xsync * o);
// static xint32 __xsync_none_unlock(xsync * o);
// static xint32 __xsync_none_wait(xsync * o, xuint64 nanosecond);
// static xint32 __xsync_none_wakeup(xsync * o, xint32 all);

// static void * __xsync_mutex_free(void * p);
// static xint32 __xsync_mutex_lock(xsync * o);
// static xint32 __xsync_mutex_unlock(xsync * o);
// static xint32 __xsync_mutex_wait(xsync * o, xuint64 nanosecond);
// static xint32 __xsync_mutex_wakeup(xsync * o, xint32 all);

// static inline xsync * __xsync_none_new(void)
// {
//     xsync * o = (xsync *) calloc(sizeof(xsync), 1);
//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_none;
//     o->free  = __xsync_none_free;
//     o->lock = __xsync_none_lock;
//     o->unlock = __xsync_none_unlock;
//     o->wait = __xsync_none_wait;
//     o->wakeup = __xsync_none_wakeup;

//     return o;
// }

// static void * __xthread_pthread_free(void * p);

// struct __mutex
// {
//     xuint32 flags;
//     xdestructor free;

//     xint32 (*lock)(xsync *);
//     xint32 (*unlock)(xsync *);
//     xint32 (*wait)(xsync *, xuint64);
//     xint32 (*wakeup)(xsync *, xint32);

//     pthread_mutex_t * mutex;
//     pthread_cond_t * cond;
// };

// static inline xsync * __xsync_mutex_new(void)
// {
//     struct __mutex * o = (struct __mutex *) calloc(sizeof(struct __mutex), 1);
//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     o->flags = xobj_mask_allocated | xobj_type_sync | xsync_type_mutex;

//     o->free  = __xsync_mutex_free;
//     o->lock = __xsync_mutex_lock;
//     o->unlock = __xsync_mutex_unlock;
//     o->wait = __xsync_mutex_wait;
//     o->wakeup = __xsync_mutex_wakeup;

//     return (xsync *) o;
// }

// static inline xsync * __xsync_mutex_on(struct __mutex * o)
// {
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         xcheck(o->mutex != xnil, "already mutex created");
//         if(o->mutex == xnil)
//         {
//             o->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
//             xassertion(o->mutex == xnil, "fail to calloc (%d)", errno);
//             *(o->mutex) = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
//         }
//     }
//     return (xsync *) o;
// }

// static inline xsync * __xsync_mutex_off(struct __mutex * o)
// {
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         xcheck(o->mutex, "already mutex destroyed");
//         if(o->mutex)
//         {
//             int ret = pthread_mutex_destroy(o->mutex);
//             xassertion(ret != xsuccess, "fail to pthread_mutex_destroy (%d)", ret);

//             free(o->mutex);
//             o->mutex = xnil;

//             if(o->cond)
//             {
//                 ret = pthread_cond_destroy(o->cond);
//                 xassertion(ret != xsuccess, "fail to pthread_cond_destroy (%d)", ret);

//                 free(o->cond);
//                 o->cond = xnil;
//             }
//         }
//     }
//     return (xsync *) o;
// }

// static inline xsync * __xsync_cond_on(struct __mutex * o)
// {
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         if(o->mutex == xnil)
//         {
//             xcheck(xtrue, "mutex not created");
//             o->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
//             xassertion(o->mutex == xnil, "fail to malloc (%d)", errno);
//             *(o->mutex) = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
//         }
//         xcheck(o->cond != xnil, "already cond created");
//         if(o->cond == xnil)
//         {
//             o->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
//             xassertion(o->cond == xnil, "fail to malloc (%d)", errno);
//             *(o->cond) = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
//         }
//     }
//     return (xsync *) o;
// }

// static inline xsync * __xsync_cond_off(struct __mutex * o)
// {
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         xcheck(o->cond == xnil, "already cond destroyed");
//         if(o->cond)
//         {
//             int ret = pthread_cond_destroy(o->cond);
//             xassertion(ret != xsuccess, "fail to pthread_cond_destroy (%d)", ret);

//             free(o->cond);
//             o->cond = xnil;
//         }
//     }
//     return (xsync *) o;
// }

// /**
//  * @fn      xuint64 xthreadid(void)
//  * @brief
//  * 
//  * @return  | xuint64 | 스레드 아이디 |
//  */
// xuint64 xthreadid(void)
// {
//     return pthread_self();
// }

// /**
//  * @fn      xsync * xsyncnew(xuint32 type)
//  */
// xsync * xsyncnew(xuint32 type)
// {
//     switch(type & xsync_mask_types)
//     {
//         case xsync_type_none:   return __xsync_none_new();
//         case xsync_type_mutex:  return __xsync_mutex_new();
//     }
//     xassertion(xtrue, "unsupported type");
// }

// /**
//  * @fn      void * xsyncrem(void * p)
//  */
// void * xsyncrem(void * p)
// {
//     return xobjrem()
//     xsync * o = (xsync *) p;
//     xcheck(o == xnil, "null pointer");
//     if(o)
//     {
//         o = o->destruct(o);
//     }
//     return o;
// }

// /**
//  * @fn      xsync * xsyncon(xsync * p)
//  */
// xsync * xsyncon(xsync * p)
// {
//     xsync * o = (xsync *) p;
//     xcheck(o == xnil, "null pointer");

//     switch(o->flags & xsync_mask_types)
//     {
//         case xsync_type_none:   return xsuccess;
//         case xsync_type_mutex:  return __xsync_mutex_on((struct __mutex *) o);
//     }
//     xassertion(xtrue, "unsupported type");
// }

// /**
//  * @fn      xsync * xsyncoff(xsync * p)
//  */
// xsync * xsyncoff(xsync * p)
// {
//     xsync * o = (xsync *) p;
//     xcheck(o == xnil, "null pointer");

//     switch(o->flags & xsync_mask_types)
//     {
//         case xsync_type_none:   return xsuccess;
//         case xsync_type_mutex:  return __xsync_mutex_off((struct __mutex *) o);
//     }
//     xassertion(xtrue, "unsupported type");
// }

// /**
//  * @fn      xsync * xcondon(xsync * p)
//  */
// xsync * xcondon(xsync * p)
// {
//     xsync * o = (xsync *) p;
//     xcheck(o == xnil, "null pointer");

//     switch(o->flags & xsync_mask_types)
//     {
//         case xsync_type_none:   return xsuccess;
//         case xsync_type_mutex:  return __xsync_cond_on((struct __mutex *) o);
//     }
//     xassertion(xtrue, "unsupported type");
// }

// /**
//  * @fn      xsync * xcondoff(xsync * p)
//  */
// xsync * xcondoff(xsync * p)
// {
//     xsync * o = (xsync *) p;
//     xcheck(o == xnil, "null pointer");

//     switch(o->flags & xsync_mask_types)
//     {
//         case xsync_type_none:   return xsuccess;
//         case xsync_type_mutex:  return __xsync_cond_off((struct __mutex *) o);
//     }
//     xassertion(xtrue, "unsupported type");
// }

// struct __pthread
// {
//     xuint32 flags;
//     xdestructor destruct;

//     xval * parameter;
//     xthreadfunc func;

//     pthread_t * id;
// };

// static void * __pthread_internal_func(void * param)
// {
//     struct __pthread * o = (struct __pthread *) param;

//     return o->func((xthread *) o);
// }

// xthread * xthreadnew(xthreadfunc func, xval * param)
// {
//     xthread * o = (xthread *) calloc(sizeof(xthread), 1);
//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     o->flags = xobj_mask_allocated | xobj_type_thread;
//     o->destruct  = __xthread_pthread_free;
//     o->func = func;
//     o->param = param;

//     return o;
// }

// void * xthreadrem(void * p)
// {
//     xthread * o = (xthread *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         o = o->free(o);
//     }

//     return p;
// }

// /**
//  * @fn      xthread * xthreadon(xthread * p)
//  */
// xthread * xthreadon(xthread * p)
// {
//     struct __pthread * o = (struct __pthread *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         xcheck(o->id, "thread is already on");
//         if(o->id == xnil)
//         {
//             o->id = (pthread_t *) calloc(sizeof(pthread_t), 1);
//             int ret = pthread_create(o->id, xnil, __pthread_internal_func, o);
//             xassertion(ret != xsuccess, "fail to pthread_create (%d)", errno);
//         }
//     }

//     return (xthread *) o;
// }

// /**
//  * @fn      xthread * xthreadoff(xthread * p)
//  */
// xthread * xthreadoff(xthread * p, xvalcb cb)
// {
//     struct __pthread * o = (struct __pthread *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         xcheck(o->id == xnil, "thread is already off status");
//         if(o->id)
//         {
//             o->flags |= xthread_status_cancel;
//             void * result = xnil;
//             int ret = pthread_join(*o->id, &result);
//             xassertion(ret != xsuccess, "fail to pthread_join (%d)", errno);
//             if(cb)
//             {
//                 cb(xvalgenptr(result));
//             }
//             free(o->id);
//             o->id = xnil;
//         }
//     }

//     return (xthread *) o;
// }

// /** SYNC */

// static void * __xsync_none_free(void * p)
// {
//     xsync * o = (xsync *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         xassertion(xobjtype(o) != xobj_type_sync, "invalid object");
//         xassertion(xsynctype(o) != xsync_type_none, "invalid sync type");

//         if(o->flags & xobj_mask_allocated)
//         {
//             free(o);
//             o = xnil;
//         }
//     }
//     return o;
// }

// static xint32 __xsync_none_lock(xsync * o)
// {
//     return xsuccess;
// }

// static xint32 __xsync_none_unlock(xsync * o)
// {
//     return xsuccess;
// }

// static xint32 __xsync_none_wait(xsync * o, xuint64 nanosecond)
// {
//     return xsuccess;
// }

// static xint32 __xsync_none_wakeup(xsync * o, xint32 all)
// {
//     return xsuccess;
// }

// static void * __xsync_mutex_free(void * p)
// {
//     struct __mutex * o = (struct __mutex *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         o->mutex = __xsync_pthread_mutexoff(o->mutex);
//         o->cond = __xsync_pthread_condoff(o->cond);

//         if(o->flags & xobj_mask_allocated)
//         {
//             free(o);
//             o = xnil;
//         }
//     }

//     return o;
// }

// static xint32 __xsync_mutex_lock(xsync * p)
// {
//     struct __mutex * o = (struct __mutex *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o && o->mutex)
//     {
//         int ret = pthread_mutex_lock(o->mutex);
//         xassertion(ret != xsuccess, "fail to pthread_mutex_lock (%d)", errno);
//     }
//     return xsuccess;
// }

// static xint32 __xsync_mutex_unlock(xsync * p)
// {
//     struct __mutex * o = (struct __mutex *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o && o->mutex)
//     {
//         int ret = pthread_mutex_unlock(o->mutex);
//         xassertion(ret != xsuccess, "fail to pthread_mutex_unlock (%d)", errno);
//     }
//     return xsuccess;
// }

// static xint32 __xsync_mutex_wait(xsync * p, xuint64 nanosecond)
// {
//     struct __mutex * o = (struct __mutex *) p;
//     xcheck(o == xnil, "null pointer");
//     xassertion(o->cond && o->mutex == xnil, "mutex is not allocated");

//     if(o && o->cond && o->mutex)
//     {
//         if(nanosecond > 0)
//         {
//             struct timespec timespec = { 0, };
//             // TODO: ERROR HANDLING
//             clock_gettime(CLOCK_REALTIME, &timespec);
//             timespec.tv_sec += nanosecond / 1000000000;
//             timespec.tv_nsec += nanosecond % 1000000000;
//             int ret = pthread_cond_timedwait(o->cond, o->mutex, &timespec);
//             if(ret != ETIMEDOUT && ret != EINTR)
//             {
//                 xassertion(ret != xsuccess, "fail to pthread_cond_timedwait (%d)", ret);
//             }
//         }
//         else
//         {
//             pthread_cond_wait(o->cond, o->mutex);
//         }
//     }
//     return xsuccess;
// }

// static xint32 __xsync_mutex_wakeup(xsync * p, xint32 all)
// {
//     struct __mutex * o = (struct __mutex *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o && o->cond)
//     {
//         if(all)
//         {
//             pthread_cond_broadcast(o->cond);
//         }
//         else
//         {
//             pthread_cond_signal(o->cond);
//         }
//     }
//     return xsuccess;
// }

// static void * __xthread_pthread_free(void * p)
// {
//     struct __pthread * o = (struct __pthread *) p;
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         // TODO: IMPLEMENT THIS
//     }
    
//     return o;
// }