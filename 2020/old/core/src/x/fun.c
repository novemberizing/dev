#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "std.h"

/**
 * @fn      xfunction * xfunctionnew(xfunc func, xobj * param, xcallback cb)
 * @brief   함수 객체를 메모리에 생성합니다.
 * @details
 * 
 * @param   | func  | in | xfunc     | 함수 |
 * @param   | param | in | xobj *    | 파라미터 |
 * @param   | cb    | in | xcallback | 콜백 |
 * 
 * @return  | xfunction * | 생성된 메모리 객체 주소 |
 */
xfunction * xfunctionnew(xfunc func, xobj * param, xcallback cb)
{
    xfunction * o = (xfunction *) calloc(sizeof(xfunction), 1);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_function;
    o->destruct = xfunctionrem;

    o->func = func;
    o->param = param;
    o->cb = cb;

    return o;
}

/**
 * @fn      void * xfunctionrem(void * p)
 * @brief   함수 객체 멤버 중 메모리 상에서 해제되어야 하는 멤버들을 해제합니다. 객체 자신 역시 메모리에 생성되었다면 객체를 해제하고 널을 리턴합니다. 그렇지 않고 스택 상에서 생성되었다면, 스택의 주소를 리턴합니다.
 * @details
 * 
 * @param   | p | in | void * | 해제하고자 하는 객체의 메모리 주소 값 |
 * 
 * @return  | void * | 해제한 객체의 주소 값으로 객체가 동적할당으로 생성되었다면 메모리 상에서 객체를 헤제하고 널을 리턴합니다. |
 */
void * xfunctionrem(void * p)
{
    xfunction * o = (xfunction *) p;
    xcheck(o == xnil, xnil, "object is null");
    xassertion(xobjtype(o) != xobj_type_function, "object type is not function");

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
 * @fn      void xfunctioncall(xfunction * o)
 * @brief   함수 객체를 수행합니다.
 * @details 
 * 
 * @param   | o | in | xfunction * | 함수의 객체 |
 * 
 */
void xfunctioncall(xfunction * o)
{
    xassertion(o == xnil || o->flags & (xfunction_mask_called | xfunction_mask_cancelled), "object is null or function is already called or cancelled");

    o->flags |= xfunction_mask_called;
    o->func(o);
    o->flags |= xfunction_mask_success;
    if(o->cb)
    {
        o->cb(o);
    }
}

/**
 * @fn      void xfunctioncancel(xfunction * o)
 * @brief   함수의 호출을 취소합니다.
 * @details 
 * 
 * @param   | o | in | xfunction * | 함수의 객체입니다. |
 */
void xfunctioncancel(xfunction * o)
{
    xassertion(o == xnil || o->flags & (xfunction_mask_called | xfunction_mask_cancelled), "object is null or function is already called or cancelled");

    o->flags |= xfunction_mask_cancelled;
    if(o->cb)
    {
        o->cb(o);
    }
}
