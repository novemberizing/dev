#include "log.h"

#include "types.h"

/**
 * @fn      xobj * xobjnew(xuint64 size)
 * @brief   동적할당을 통하여 기본적인 객체를 생성합니다.
 * @details 
 * 
 * @param   | size | in | xuint64 | 객체의 메모리 크기 |
 * @param   | type | in | xuint32 | 객체의 타입 |
 * 
 *          객체 타입의 비트 마스크인 0xFFFF0000 
 * 
 * @param   | rem | in | destructor | 객체 소멸자 |
 * @return  | xobj * | 객체 |
 */
xobj * xobjnew(xuint64 size, xuint32 type, destructor rem)
{
    xassertion(type & 0xFFFF0000U, "type & 0xFFFF0000U");

    xobj * o = (xobj *) calloc(size, 1);
    xassertion(o == xnil, "o == xnil");

    o->flags = xobj_status_allocated | type;
    o->rem   = rem;

    return o;
}

/**
 * @fn      void * xobjrem(void * p)
 * @brief   객체의 자원을 해제하는 함수입니다.
 * @details 객체가 동적할당에 의해서 생성된 것이라면 free() 함수를 호출하여 자원을 해제합니다.
 * 
 * @param   | p | in | void * | 메모리 상에서 삭제하려는 객체의 포인터 |
 * 
 * @return  | void * | 
 */
void * xobjrem(void * p)
{
    xcheck(p == xnil, xnil, "p == xnil");

    xobj * o = (xobj *) p;

    if(o->rem)
    {
        o->rem(o);
        o->rem = xnil;
    }
    
    if(o->flags & xobj_status_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

/**
 * @fn      xfun * xfunnew(xfunc func, xobj * param, xcb cb, destructor rem)
 * @brief   동적할당에 의해 새로운 함수 객체를 생성합니다.
 * @details func 파라미터가 null 이면 프로그램이 비정상적으로 종료됩니다.
 * 
 * @param   | o     | in | xfun *     | 초기화 시키려는 객체로 NULL 이면 새로운 객체를 생성한다. |
 * @param   | func  | in | xfunc      | 함수 포인터 |
 * @param   | param | in | xobj *     | 함수 실행 시의 파라미터, 파라미터가 존재하지 않는 경우면 null 을 대입하면 됩니다. |
 * @param   | cb    | in | xcb        | 콜백 함수 포인터로 필요할 경우면 콜백함수의 주소값을 대입하고 그렇지 않으면 null 을 대입합니다. |
 * @param   | rem   | in | destructor | xfun 객체 멤버들의 해제 시에 메모리 상에서 자원 해제가 필요한 경우 구현하여 파리미터에 대입을 하면 됩니다. 그렇지 않을 경우 null 을 대입합니다. |
 * 
 * @return  | xfun * | 동적할당에 의해서 생성된 객체를 리턴합니다. |
 */
xfun * xfunnew(xfun * o, xfunc func, xobj * param, xcb cb)
{
    xassertion(func == xnil, "func == xnil");

    if(o == xnil)
    {
        o = (xfun *) calloc(sizeof(xfun), 1);
        xassertion(o == xnil, "o == xnil => calloc (error: %d)", errno);

        o->flags = xobj_status_allocated;
    }
    else
    {
        xassertion(xfunisrunning(o), "xfunisrunning(o)");
        xfuncancel(o);

        o->flags = (o->flags & xobj_status_allocated);
        o->param = xobjrem(o->param);
        o->result = xobjrem(o->result);
        o->cb = xnil;
    }

    o->flags |= xobj_type_fun;
    o->rem = xfunrem;

    o->param = param;
    o->func = func;
    o->cb = cb;

    return o;
}

/**
 * @fn      void * xfunrem(void * p)
 * @brief   함수의 객체 초기화합니다. 만약에 함수의 객체가 동적할당에 의해서 생성되었으면 메모리에서 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 해제하려는 객체의 주소 |
 * 
 * @return  | void * | 해제한 객체의 주소 |
 * 
 *          동적할당에 의해서 해제된 경우 널을 리턴합니다.
 */
void * xfunrem(void * p)
{
    xcheck(p == xnil, xnil, "p == xnil");

    xfun * o = (xfun *) p;
    xassertion(xobjtype(o) != xobj_type_fun, "xobjtype(o) != xobj_type_fun");
    xassertion(xfunisrunning(o), "xfunisrunning(o)");
    
    xfuncancel(o);

    o->param = xobjrem(o->param);
    o->result = xobjrem(o->result);

    if(o->flags & xobj_status_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

/**
 * @fn      void xfuncancel(xfun * o)
 * @brief   실행중이지 않은 함수의 경우 호출을 취소합니다.
 * @details 
 * 
 * @param   | o | in | xfun * | 함수 객체 |
 * 
 * 
 */
void xfuncancel(xfun * o)
{
    if((o->flags & xfun_status_called) == xfalse)
    {
        if((o->flags & xfun_status_cancelled) == xfalse)
        {
            o->flags |= xfun_status_cancelled;
            if(o->cb)
            {
                o->cb(o);
            }
        }
    }
}

/**
 * @fn      void xfuncall(xfun * o)
 * @brief   함수 객체를 실행합니다.
 * @details 객체가 널이거나 혹은 내부 함수 멤버가 널이면 비정상적으로 종료됩니다.
 *          현재 함수가 호출된 상태이면 다시 호출하지 않습니다.
 * 
 * @param   | o | in | xfun * | 함수 객체 |
 */
void xfuncall(xfun * o)
{
    xassertion(o == xnil || o->func == xnil, "o == xnil || o->func == xnil");

    xcheckvoid(o->flags == xfun_status_called, "o->flags == xfun_status_called");
    
    o->flags |= xfun_status_called;
    o->result = o->func(o->param);
    o->flags |= xfun_status_success;
}
