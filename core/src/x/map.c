#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "std.h"

xmap * xmapnew(xvalcmp comp)
{
    xmap * o = (xmap *) calloc(sizeof(xmap), 1);

    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_map;
    o->comp = comp;

    return o;
}

/**
 * @fn      void * xmaprem(void * p)
 * @brief   맵 객체를 메모리 상에서 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 맵의 객체를 메모리 상에서 해제합니다. |
 * 
 * @return  | void * | 해제된 맵 객체의 주소 (맵이 동적할당에 의해서 생성되었다면 해제 후에 널을 리턴합니다.) |
 */
extern void * xmaprem(void * p)
{
    xmap * o = (xmap *) p;
    xcheck(o == xnil, xnil, "invalid parameter");
    xassertion(xobjtype(o) != xobj_type_map || o->size > 0, "list is not clear");

    xmapclear(o, xnil);
    xmapsyncoff(o);

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }
    return o;
}

/**
 * @fn      xmap * xmapsyncon(xmap * o, xuint32 type)
 * @brief   맵의 동기화 객체를 활성화 합니다.
 * @details
 * 
 * @param   | o    | in | xmap *  | 맵의 객체 주소 |
 * @param   | type | in | xuint32 | 생성하고자 하는 동기화 객체의 타입 |
 * 
 * @return  | xmap * | 객체의 포인터 |
 */
xmap * xmapsyncon(xmap * o, xuint32 type)
{
    xcheck(o == xnil || o->sync, o, "object is null or sync is already created");
    o->sync = xsyncnew(type);
    
    return o;
}

/**
 */
xmap * xmapsyncoff(xmap * o)
{
    o->sync 
    return o;
}

extern int xmapadd(xmap * o, xval v, xvalcb f);
extern int xmapdel(xmap * o, xval v, xvalcb f);
extern xmap * xmapclear(xmap * o, xvalcb f);