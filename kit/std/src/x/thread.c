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

struct __internal_thread
{
    xuint32 flags;
    xdestructor destruct;

    xobj * param;
    xthreadfunc func;
    xobj * result;

    pthread_t * id;
};

struct __internal_thread_local
{
    xuint32 flags;
    xdestructor xdestruct;

    xval local;

    pthread_key_t key;
};

static void * __internal_thread_routine(void * p)
{
    struct __internal_thread * o = (struct __internal_thread *) p;

    o->result = o->func((xthread *) o);

    return xnil;
}

static void * __xthread_internal_rem(void * p)
{
    struct __internal_thread * o = (struct __internal_thread *) p;

    if(o->id)
    {
        void * result = xnil;
        o->flags |= xthread_mask_cancel;
        int ret = pthread_join(*o->id, &result);
        xassertion(ret != xsuccess, "fail to pthread_join (%d)", ret);

        xobjrem(o->result);
        free(o->id);
    }

    xobjrem(o->param);
    free(o);
    o = xnil;
    
    return o;
}

static void * __internal_thread_local_rem(void * p);

extern xthread * xthreadnew(xthreadfunc func, xobj * param)
{
    xassertion(func == xnil, "invalid paramter");

    struct __internal_thread * o = (struct __internal_thread *) calloc(sizeof(struct __internal_thread), 1);

    o->flags = xobj_mask_allocated | xobj_type_thread;
    o->destruct = __xthread_internal_rem;
    o->func = func;
    o->param = param;

    return (xthread *) o;
}

extern void * xthreadrem(void * p)
{
    xcheck(p == xnil, "invalid parameter");

    if(p)
    {
        xassertion(xobjtype(p) != xobj_type_thread, "invalid object");

        p = __xthread_internal_rem(p);
    }

    return p;
}

extern xthread * xthreadon(xthread * p)
{
    struct __internal_thread * o = (struct __internal_thread *) p;
    xcheck(o->id, "thread is already created");

    if(o->id == xnil)
    {
        xcheck(o->result, "old result is exist");
        o->result = xobjrem(o->result);

        o->id = calloc(sizeof(pthread_t), 1);
        int ret = pthread_create(o->id, xnil, __internal_thread_routine, o);
        xassertion(ret != xsuccess, "fail to pthread_create (%d)", ret);
    }
    return (xthread *) o;
}
extern xthread * xthreadoff(xthread * p, xobj * (*cb)(xobj *))
{
    struct __internal_thread * o = (struct __internal_thread *) p;
    xcheck(o->id == xnil, "thread is already destroyed");

    if(o->id)
    {
        void * result = xnil;
        int ret = pthread_join(*o->id, &result);
        xassertion(ret != xsuccess, "fail to pthread_join (%d)", ret);
        if(cb)
        {
            o->result = cb(o->result);
        }
        o->result = xobjrem(o->result);
        free(o->id);
        o->id = xnil;
    }

    return p;
}

extern xthreadlocal * xthreadlocalnew(void (*destructor)(void *))
{
    struct __internal_thread_local * o = (struct __internal_thread_local *) calloc(sizeof(struct __internal_thread_local), 1);

    o->flags = xobj_mask_allocated | xobj_type_threadlocal;
    o->xdestruct = __internal_thread_local_rem;
    int ret = pthread_key_create(&o->key, destructor);
    xassertion(ret != xsuccess, "fail to pthread_key_create (%d)", ret);

    return (xthreadlocal *) o;
}

extern void * xthreadlocalrem(void * p)
{
    xcheck(p == xnil, "null pointer");
    if(p != xnil)
    {
        xassertion(xobjtype(p) != xobj_type_threadlocal, "invalid object");

        p = __internal_thread_local_rem(p);
    }
    return p;
}

extern void * xthreadlocalget(xthreadlocal * p)
{
    struct __internal_thread_local * o = (struct __internal_thread_local *) p;
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        return pthread_getspecific(o->key);
    }

    return xnil;
}

extern void xthreadlocalset(xthreadlocal * p, void * data)
{
    struct __internal_thread_local * o = (struct __internal_thread_local *) p;
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        // TODO: CHECK OLD DATA
        int ret = pthread_setspecific(o->key, data);
        xassertion(ret != xsuccess, "fail to pthread_setspecific (%d)", ret);
    }
}

/** INTERNAL */

static void * __internal_thread_local_rem(void * p)
{
    struct __internal_thread_local * o = (struct __internal_thread_local *) p;

    if(o->key)
    {
        pthread_key_delete(o->key);
    }
    free(o);

    return xnil;
}
