#include "std.h"

struct __pxthread;

typedef struct __pxthread __pxthread;

struct __pxthread
{
    xuint32 flags;
    destructor destruct;

    xval param;
    xthreadfun func;
};

/**
 * @fn      xthread * xthreadnew(xthreadfun func, xval param)
 * @brief   스레드 객체를 생성합니다.
 * @details
 * 
 * @param   | func  | in | xthreadfun | 스레드 실행 함수입니다. |
 * @param   | param | in | xval       | 스레드 실행을 위한 파라미너터입니다. |
 */
xthread * xthreadnew(xthreadfun func, xobj * param)
{
    __pxthread * o = (__pxthread *) calloc(sizeof(__pxthread), 1);
    xassertion(o == xnil, "o == xnil");

    o->flags = xobj_mask_allocated | xobj_type_thread;
    o->destruct = xnil;
    xassertion(o->destruct == xnil, "implement this");

    o->func = func;
    o->param = param;
    o->result = xnil;

    return o;
}