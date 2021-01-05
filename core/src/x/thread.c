#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "std.h"

struct __xpthread;

typedef struct __xpthread __xpthread;

struct __xpthread
{
    xuint32 flags;
    destructor destruct;

    xobj * param;
    xobj * result;
    xfunc func;
    xcb cb;

    pthread_t * id;
};

static void * __xpthread_routine(void * p)
{
    __xpthread * o = (__xpthread *) p;

    xassertion(o == xnil || (o->flags & xthread_mask_called), "o == xnil || (o->flags & xthread_mask_called)");
    xcheck(o->flags & xthread_mask_cancelled, xnil,"o->flags & xthread_mask_cancelled");

    o->flags |= xthread_mask_called;
    o->result = o->func(o->param);
    o->flags |= xthread_mask_success;
    
    if(o->cb)
    {
        o->cb(o);
    }

    return o->result;
}

/**
 * @fn      xthread * xthreadnew(xfunc func, xobj * param, xcb cb)
 * @brief   스레드 객체를 생성합니다.
 * @details
 * 
 * @param   | func  | in | xfunc | 스레드 실행 함수입니다. |
 * @param   | param | in | xval  | 스레드 실행을 위한 파라미너터입니다. |
 * @param   | cb    | in | xcb   | 스레드 종료 시에 호출되는 콜백입니다. |
 */
xthread * xthreadnew(xfunc func, xobj * param, xcb cb)
{
    __xpthread * o = (__xpthread *) calloc(sizeof(__xpthread), 1);
    xassertion(o == xnil, "o == xnil");

    o->flags = xobj_mask_allocated | xobj_type_thread;
    o->destruct = xthreadrem;
    xassertion(o->destruct == xnil, "implement this");

    o->func = func;
    o->param = param;
    o->result = xnil;
    o->id = xnil;

    return o;
}

/**
 * @fn      void * xthreadrem(void * p)
 * @brief   메모리 상에 할당된 스레드 객체를 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 스레드 객체의 주소 |
 * 
 * @return  | void * | 메모리 상에서 제거된 스레드 객체의 주소 (객체가 메모리 상에서 할당되었다면 xnil 을 리턴합니다.) |
 */
void * xthreadrem(void * p)
{
    __xpthread * o = (__xpthread *) p;
    xcheck(o == xnil, xnil, "o == xnil");

    xthreadoff(o);

    o->param = xobjrem(o->param);
    o->result = xobjrem(o->result);

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

/**
 * @fn      int xthreadon(xthread * p)
 * @brief   스레드를 시작합니다.
 * @details 
 * 
 * @param   | p | in | xthread * | 스레드 객체의 주소값 |
 * @return  | int | 스레드 수행 루틴 |
 */
int xthreadon(xthread * p)
{
    xassertion(p == xnil, "o == xnil");

    __xpthread * o = (__xpthread *) p;

    if(o->id == xnil)
    {
        o->id = (pthread_t *) malloc(sizeof(pthread_t));

        xassertion(o->id == xnil, "o->id == xnil => malloc (%d)", errno);

        int ret = pthread_create(o->id, xnil, __xpthread_routine, o);

        xassertion(ret != xsuccess, "ret != xsuccess => pthread_create (%d)", errno);

        return xsuccess;
    }

    return xfail;
}

int xthreadoff(xthread * p)
{
    xassertion(p == xnil, "o == xnil");

    __xpthread * o = (__xpthread *) p;

    if(o->id != xnil)
    {
        o->flags |= xthread_mask_cancelling;
        
    }

    return xfail;
}