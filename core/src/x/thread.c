#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "std.h"

struct xpthread;

typedef struct xpthread xpthread;

struct xpthread
{
    xuint32     flags;
    xdestructor destruct;

    xobj * param;
    xobj * result;
    xfunc func;
    xcallback cb;

    pthread_t * id;
};

static void * xpthreadroutiune(void * p);

/**
 * @fn      xthread * xthreadnew(xfunc func, xobj * param, xcallback cb)
 * @brief   쓰레드 객체를 생성합니다.
 * @details 
 * 
 * @param   | func  | in | xfunc     | 함수 |
 * @param   | param | in | xobj *    | 스레드 수행 시의 파라미터 |
 * @param   | cb    | in | xcallback | 스레드 종료 시에 수행되는 콜백함수 |
 * 
 * @return  | xthread * | 생성된 스레드 객체 |
 */
xthread * xthreadnew(xfunc func, xobj * param, xcallback cb)
{
    xpthread * o = (xpthread *) calloc(sizeof(xpthread), 1);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_thread;
    o->destruct = xthreadrem;

    o->func = func;
    o->param = param;
    o->cb = cb;

    return o;
}

/**
 * @fn      void * xthreadrem(void * p)
 * @brief   스레드 객체를 메모리 상에서 해제합니다.
 * @details 스레드가 동작 중이면 스레드를 종료합니다.
 *          스레드의 함수를 정의할 때, 스레드 상태가 취소 상태이면
 *          수행중인 상태를 종료할 로직을 사용자는 구현해야 합니다.
 * 
 * @param   | p | in | void * | 제거하려는 스레드 객체의 주소 값 |
 * 
 * @return  | void * | 메모리 상에서 제거된 스레드 객체의 주소 값 |
 *          스레드가 동적할당에 의해서 생성되었다면 널을 리턴합니다.
 *          
 */
void * xthreadrem(void * p)
{
    xpthread * o = (xpthread *) p;
    xcheck(o == xnil, xnil, "invalid parameter (p == xnil)");

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
 * @fn      xthread * xthreadon(xthread * p)
 * @brief   스레드를 실행합니다.
 * @details 
 * 
 * @param   | p | in | xthread * | 스레드 객체 |
 * 
 * @return  | xthread * | 스레드 객체 |
 */
xthread * xthreadon(xthread * p)
{
    xpthread * o = (xpthread *) p;
    xcheck(o == xnil, xnil, "invalid parameter (p == xnil");

    if(o->id == xnil)
    {
        o->id = (pthread_t *) malloc(sizeof(pthread_t));
        xassertion(o->id == xnil, "fail to malloc (%d)", errno);

        int ret = pthread_create(o->id, xnil, xpthreadroutiune, o);
        xassertion(ret != xsuccess, "fail to pthread_create (%d)", ret);
    }

    return o;
}

/**
 * @fn      xthread * xthreadoff(xthread * p)
 * @brief   스레드를 종료합니다.
 * @details
 * 
 * @param   | p | in | xthread * | 스레드 객체 |
 * 
 * @return  | xthread * | 스레드 객체 |
 */
xthread * xthreadoff(xthread * p)
{
    xpthread * o = (xpthread *) p;
    xcheck(o == xnil, xnil, "invalid parameter (p == xnil");

    if(o->id)
    {
        o->flags |= xthread_mask_cancelled;
        void * result = xnil;
        int ret = pthread_join(*o->id, &result);
        xassertion(ret != xsuccess, "fail to pthread_join (%d)", errno);
        free(o->id);
        o->id = xnil;
    }

    return o;
}

/**
 * @fn      static void * xpthreadroutiune(void * p)
 * @brief   POSIX 스레드 루틴
 * @details
 * 
 * @param   | p | in | void * | 파라미터 |
 * @return  | void * | 스레드 결과 값 |
 */
static void * xpthreadroutiune(void * p)
{
    xpthread * o = (xpthread *) p;

    o->flags |= xthread_mask_called;
    o->func(o);
    o->flags |= xthread_mask_success;

    return o->result;
}