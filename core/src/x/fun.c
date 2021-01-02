#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "std.h"

/**
 * @fn      xfun * xfunnew(xobj * (*func)(xobj *), xobj * param, void (*cb)(xfun *))
 * @brief   동적으로 함수 객체를 생성합니다.
 * @details 수행되어져야 하는 함수가 널인 경우 동작하지 않습니다.
 * 
 * @param   | func  | in | xobj * (*func)(xobj *) | 수행 함수입니다. |
 * @param   | param | in | xobj *                 | 함수를 실행할 때의 파라미터입니다. |
 * @param   | cb    | in | void (*cb)(xfun *)     | 함수가 실행되고 난 후 수행하는 콜백 함수입니다. |
 * 
 * @return  | xfun * | 동적할당으로 생성된 함수입니다. |
 */
xfun * xfunnew(xfunc func, xobj * param, xcb cb)
{
    xassertion(func == xnil, "func == xnil");

    xfun * o = (xfun *) calloc(sizeof(xfun), 1);
    xassertion(o == xnil, "o == xnil => calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_fun;
    o->destruct = xfunrem;

    o->param = param;
    o->func = func;
    o->cb = cb;

    return o;
}

/**
 * @fn      void * xfunrem(void * p)
 * @brief   함수 객체와 관련된 메모리를 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 함수 객체의 주소 값 |
 * 
 * @return  | void * | 함수의 객체를 해제합니다. |
 */
void * xfunrem(void * p)
{
    xfun * o = (xfun *) p;

    xcheck(o == xnil, xnil, "o == xnil");

    xassertion(xobjtype(o) != xobj_type_fun, "xobjtype(o) == xobj_type_func");
    xassertion(xfunisrunning(o), "xfunisrunning");

    o->param = xobjrem(o->param);
    o->result = xobjrem(o->result);
    o->func = xnil;
    o->cb = xnil;

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

/**
 * @fn      void xfuncall(xfun * o)
 * @brief   함수 객체의 함수를 수행합니다.
 * @details 
 * 
 * @param   | o | in | xfun * | 함수 객체 |
 * 
 */
void xfuncall(xfun * o)
{
    xassertion(o == xnil || (o->flags & xfun_mask_called), "o == xnil || (o->flags & xfun_mask_called)");

    xcheckvoid(o->flags & xfun_mask_cancelled, "o->flags & xfun_mask_cancelled");

    o->flags |= xfun_mask_called;

    o->result = o->func(o->param);

    o->flags |= xfun_mask_success;

    if(o->cb)
    {
        o->cb(o);
    }
}

/**
 * @fn      void xfuncancel(xfun * o)
 * @brief   함수 객체가 실행 전이면 함수 객체 상태를 취소 상태로 변경합니다.
 * @details
 * 
 * @param   | o | in | xfun * | 함수 객체 |
 */
void xfuncancel(xfun * o)
{
    xassertion(o == xnil || (o->flags & xfun_mask_called), "o == xnil || (o->flags & xfun_mask_called)");

    if((o->flags & xfun_mask_cancelled) == xfalse)
    {
        o->flags |= xfun_mask_cancelled;
        if(o->cb)
        {
            o->cb(o);
        }
    }
}