/**
 * @file    x/buffer.c
 * @brief   버퍼 구현 소스입니다.
 * @details
 * 
 * 
 * @version 0.0.1
 */

#include <stdio.h>
#include <stdlib.h>

#include "std.h"

extern xbuffer * xbuffernew(xuint64 capacity)
{
    xbuffer * o = (xbuffer *) calloc(sizeof(xbuffer), 1);

    o->flags = xobj_mask_allocated | xobj_type_buffer;
    o->destruct = xbufferrem;

    o->data = (capacity > 0 ? malloc(capacity) : xnil);
    o->capacity = capacity;
    o->position = 0;
    o->size = 0;

    return o;
}

/**
 * @fn      extern void * xbufferrem(void  * p)
 * @brief   버퍼 객체를 메모리에서 해제합니다. 
 */
extern void * xbufferrem(void  * p)
{
    xbuffer * o = (xbuffer *) p;
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck(xobjtype(o) != xobj_type_buffer, "invalid object");

        if(o->data)
        {
            free(o->data);
            o->data = xnil;
        }
        o->capacity = 0;
        o->size = 0;
        o->position = 0;

        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}