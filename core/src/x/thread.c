#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "std.h"

struct __pxthread;

typedef struct __pxthread __pxthread;

struct __pxthread
{
    xuint32 flags;
    destructor destruct;

    xobj * param;
    xobj * result;
    xfunc func;
    xcb cb;

    pthread_t * id;
};

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
    __pxthread * o = (__pxthread *) calloc(sizeof(__pxthread), 1);
    xassertion(o == xnil, "o == xnil");

    o->flags = xobj_mask_allocated | xobj_type_thread;
    o->destruct = xnil;
    xassertion(o->destruct == xnil, "implement this");

    o->func = func;
    o->param = param;
    o->result = xnil;
    o->id = xnil;

    return o;
}

// xthread * xthreadrem(xthread * o)
// {

//     return o;
// }