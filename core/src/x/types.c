#include "types.h"
#include "log.h"

/**
 * @fn      void * xobjrem(void * p)
 * @brief   객체의 멤버들을 해제하는 함수입니다.
 * @details
 * 
 */
void * xobjrem(void * p)
{
    xcheck(p == xnil, xnil, "o == xnil");

    xobj * o = (xobj *) p;

    if(o->rem)
    {
        o->rem(o);
    }

    if(xobjhas(o, xobj_status_allocated))
    {
        free(o);
        return xnil;
    }

    return o;
}

/**
 * @fn      xfun * xfunnew(xfunc func, xobj * param, xfuncb cb, destructor rem)
 * @brief
 * @details
 * 
 * @param   | func  | in | xfunc      | ... |
 * @param   | param | in | xobj *     | ... |
 * @param   | cb    | in | xfuncb     | ... |
 * @param   | rem   | in | destructor | ... |
 * 
 * @return  | xfun * | ... |
 */
xfun * xfunnew(xfunc func, xobj * param, xfuncb cb, destructor rem)
{
    xassertion(func == xnil, "func == xnil");

    xfun * o = (xfun *) calloc(sizeof(xfun), 1);

    o->flags = xallocated | xobj_type_fun;
    o->rem   = rem ? rem : xfunrem;
    o->param = param;
    o->cb    = cb;
    o->func  = func;

    return o;
}

/**
 * @fn      xfun * xfunrem(xfun * o)
 * @brief   메모리 할당을 통한 객체 생성 및 초기화
 * @details
 * 
 * @param   | p | in | void * | ... |
 * 
 * @return  | void * | ... |
 */
void * xfunrem(void * p)
{
    xcheck(p == xnil, xnil, "p == xnil");

    xfun * o = (xfun *) p;

    xassertion(xobjis(o, xobj_type_fun) == false, "xobjis(xobj_type_fun)");
    xassertion(xobjhas(o, (xfun_status_called)) && xobjhas(o, (xfun_status_fail | xfun_status_success)) == false, "xobjhas(o, (xfun_status_called)) && xobjhas(o, (xfun_status_fail | xfun_status_success)) == false");
    xassertion(xobjhas(o, xallocated) == false, "xobjhas(o, xallocated) == false");

    if(xobjhas(o, xfun_status_called) == false)
    {
        // cancel
        o->flags |= xfun_status_fail;
        o->cb(o);
    }

    xobjrem(o->param);
    xobjrem(o->result);

    free(o);

    return xnil;
}

/**
 * @fn      xfun * xfuninit(xfun * o, xfunc func, xobj * param, xfuncb cb, destructor rem)
 * @brief   초기화된 객체의 경우 재할당 
 */
xfun * xfuninit(xfun * o, xfunc func, xobj * param, xfuncb cb, destructor rem)
{
    xcheck(o == xnil, xnil, "o is xnil");

    xassertion(xobjis(o, xobj_type_fun) == false, "xobjis(o, xobj_type_fun) == false");
    xassertion(xobjhas(o, (xfun_status_called)) && xobjhas(o, (xfun_status_fail | xfun_status_success)) == false, "xobjhas(o, (xfun_status_called)) && xobjhas(o, (xfun_status_fail | xfun_status_success)) == false");

    o->flags = (xobjhas(o, xallocated) ? xallocated : 0) | xobj_type_fun;
    
    xobjrem(o->param);
    o->result = xobjrem(o->result);

    o->param = param;
    o->cb = cb;
    o->func = func;
    o->rem = rem;

    free(o);

    return o;
}

/**
 * @brief       객체를 해제하지 않고 객체 내부의 멤버만 해제
 * 
 */
xfun * xfunterm(xfun * o)
{
    xassertion(xobjis(o, xobj_type_fun) == false, "xobjis(xobj_type_fun)");
    xassertion(xobjhas(o, (xfun_status_called)) && xobjhas(o, (xfun_status_fail | xfun_status_success)) == false, "xobjhas(o, (xfun_status_called)) && xobjhas(o, (xfun_status_fail | xfun_status_success)) == false");
    xassertion(xobjhas(o, xallocated) == false, "xobjhas(o, xallocated) == false");

    if(xobjhas(o, xfun_status_called) == false)
    {
        // cancel
        o->flags |= xfun_status_fail;
        o->cb(o);
    }

    o->flags = (xobjhas(o, xallocated) ? xallocated : 0) | xobj_type_fun;
    o->param = xobjrem(o->param);
    o->result = xobjrem(o->result);
    o->cb = xnil;
    o->func = xnil;
    o->rem = xnil;

    return o;
}