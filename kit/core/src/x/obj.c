/**
 * @file    x/obj.c
 * @brief   표준 라이브러리에서 객체와 관련된 구현 소스 파일입니다.
 * @details
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "std.h"

/**
 * @fn      xobj * xobjnew(xuint64 size, xuint32 type, destructor destruct)
 * @brief   객체를 생성합니다.
 * @details
 * 
 * @param   | size     | in | xuint64 | 객체의 메모리 사이즈 |
 * @param   | type     | in | xuint32 | 객체의 타입 |
 * @param   | destruct | in | destructor | 객체의 메모리 해제 함수|
 * 
 * @return  | xobj * | 객체의 메모리 주소 값 |
 */
xobj * xobjnew(xuint64 size, xuint32 type, xdestructor destruct)
{
    xassertion(size == 0 || (type & xobj_mask_types) == xfalse, xfail, "invalid paramter { size: %lu, type: %u }", size, type);
    xobj * o = (xobj *) calloc(size, 1);

    o->flags = xobj_mask_allocated | type;
    o->destruct = destruct;

    return o;
}

/**
 * @fn      void * xobjrem(void * p)
 * @brief   객체의 메모리 해제 함수를 호출하고 객체가 동적할당에 의해서 생성되었으면 객체 자신을 해제하고 널을 리턴합니다.
 * @details
 * 
 * @param   | p | in | void * | 객체의 주소 값 |
 * 
 * @return  | void * | 해제된 객체의 주소 값 |
 * 
 *              객체가 동적할당에 의해서 메모리에 생성되어 있으면
 *              객체 자신을 메모리 상에서 해제하고 널을 리턴합니다.
 */
void * xobjrem(void * p)
{
    xobj * o = (xobj *) p;
    xassertion(o == xnil, xfail, "object is null");

    if(o->destruct)
    {
        o = (xobj *) o->destruct(o);
    }

    if(o && (o->flags & xobj_mask_allocated))
    {
        free(o);
        o = xnil;
    }
    
    return o;
}
