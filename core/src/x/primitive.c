#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "std.h"

/**
 * @fn      xprimitive * xprimitivenew(xval v)
 * @brief   프리미티비 객체를 메모리에 생성하고 v 로 초기화합니다.
 * @details
 * 
 * @param   | v | in | xval | 값 |
 * 
 * @return  | xprimitive * | 생성된 객체의 메모리 주소 값 |
 */
xprimitive * xprimitivenew(xval v)
{
    xprimitive * o = (xprimitive *) calloc(sizeof(xprimitive), 1);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_primitive;
    o->destruct = xprimitiverem;
    o->value = v;

    return o;
}

/**
 * @fn      void * xprimitiverem(void * p)
 * @brief   프리미티브 객체를 메모리 상에서 해제합니다.
 * @details 객체가 메모리 상에 할당되었다면 객체의 멤버들을 메모리에서 해제 한 후에 자신 역시 메모리에서 해제하고 널을 리턴합니다.
 * 
 * @param   | p | in | void * | 해제하고자 하는 메모리의 주소 값 |
 * @return  | void * | 객체의 멤버를 해제한 객체의 주소 값 (자신이 메모리에서 해제되었다면 NULL 을 리턴합니다.) |
 */
void * xprimitiverem(void * p)
{
    xprimitive * o = (xprimitive *) p;
    xcheck(o == xnil, xnil, "invalid parameter");
    xassertion(xobjtype(o) != xobj_type_primitive, "object type is not primitive");

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}