#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "std.h"

/**
 * @fn      xobj * xobjnew(xuint64 size, xuint32 type, xdestructor destruct)
 * @brief   메모리에 동적으로 객체를 생성합니다.
 * @details
 * 
 * @param   | size     | in | xuint64     | 객체의 메모리 크기 |
 * @param   | type     | in | xuint32     | 객체의 타입 |
 * @param   | destruct | in | xdestructor | 객체 메모리에서 해제할 때 불리는 함수 |
 * 
 * @return  | xobj * | 객체가 생성된 메모리의 주소값 |
 */
xobj * xobjnew(xuint64 size, xuint32 type, xdestructor destruct)
{
    xassertion(type & (~xobj_mask_types) || size == 0, "invalid parameter");

    xobj * o    = (xobj *) calloc(size, 1);
    xassertion(o == xnil, "fail to calloc caused %d", errno);

    o->flags    = xobj_mask_allocated | type;
    o->destruct = destruct;

    return o;
}

/**
 * @fn      void * xobjrem(void * p)
 * @brief   객체를 메모리 상에서 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 객체의 주소값 |
 * 
 * @return  | void * | 메모리에서 해제된 객체의 주소 값, 객체 자체가 메모리에서 할당된 경우 null 을 리턴합니다. |
 */
void * xobjrem(void * p)
{
    xobj * o = (xobj *) p;
    xcheck(o == xnil, xnil, "object is null");

    if(o->destruct)
    {
        o->destruct(o);
    }

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}







// /**
//  * @fn      xobj * xobjnew(xuint64 size, xuint32 type, destructor destruct)
//  * @brief   일반적인 객체를 생성합니다.
//  * @details
//  * 
//  * @param   | size     | in | xuint64    | 객체의 크기 |
//  * @param   | type     | in | xuint32    | 객체의 타입 |
//  * @param   | destruct | in | destructor | 객체의 소멸자 |
//  * 
//  * @return  | xobj * | 객체 |
//  */
// xobj * xobjnew(xuint64 size, xuint32 type, destructor destruct)
// {
//     xassertion(type & (~xobj_mask_types), "(type & (~xobj_mask_types)) == true");

//     xobj * o = (xobj *) calloc(size, 1);
//     xassertion(o == xnil, "calloc (%d)", errno);

//     o->flags = xobj_mask_allocated | type;
//     o->destruct = destruct;

//     return o;
// }

// /**
//  * @fn      void * xobjrem(void * p)
//  * @brief   객체의 내부 멤버를 제거합니다. 만약에 객체가 동적할당에 의해서 생성되었다면 객체를 메모리 상에서 해제합니다.
//  * @details
//  * 
//  * @param   | o | in | void * | 객체의 주소 |
//  * 
//  * @return  | void * | 객체 제거를 수행한 주소값으로 만약에 동적할당에 의해서 객체가 제거되면 널을 리턴합니다. |
//  */
// void * xobjrem(void * p)
// {
//     xcheck(p == xnil, xnil, "p == xnil");

//     xobj * o = (xobj *) p;

//     if(o->destruct)
//     {
//         o = (xobj *) o->destruct(o);
//     }

//     if(o)
//     {
//         if(o->flags & xobj_mask_allocated)
//         {
//             free(o);
//             o = xnil;
//         }
//     }

//     return o;
// }
