/**
 * @file    x/buffer.c
 * @brief   버퍼 파일
 */
#include <stdio.h>
#include <stdlib.h>

#include "std.h"

/**
 * @def     xbufferfront(buffer)
 * @brief   버퍼 객체의 내부 데이터 주소 값 (사용한 후의 버퍼의 주소)
 * @details
 * 
 * @param   | buffer | in | xbuffer * | 버퍼 객체 |
 */


/**
 * @fn      xbuffer * xbuffernew(xuint64 capacity)
 * @brief   기본 버퍼 객체를 생성합니다.
 * @details
 * 
 * @param   capacity | capacity | in | xuint64 | 버퍼의 크기 |
 * 
 * @return  | xbuffer * | 버퍼 객체 |
 */
xbuffer * xbuffernew(xuint64 capacity)
{
    xassertion(capacity == 0, "invalid parameter exception");

    xbuffer * o = (xbuffer *) calloc(sizeof(xbuffer), 1);
    xassertion(o == xnil, "null pointer exception");

    o->flags = xobj_mask_allocated | xobj_type_buffer;
    o->capacity = capacity;
    o->data = malloc(capacity);

    return o;
}

/**
 * @fn      void * xbufferrem(void * p)
 * @brief   버퍼 객체를 메모리에서 해제 합니다.
 * @details
 * 
 * @param   p   | in | void * | 버퍼 객체의 메모리 주소 |
 * @return  | void * | 해제된 버퍼 객체의 메모리 주소 |
 *          
 *              버퍼 객체가 동적할당에 의해서 생성되었으면 널을 리턴합니다.
 */
void * xbufferrem(void * p)
{
    xbuffer * o = (xbuffer *) p;
    xassertion(o == xnil, "invalid parameter exception");

    if(o->data)
    {
        free(o->data);
        o->data = xnil;
    }
    o->position = 0;
    o->size = 0;
    o->capacity = 0;

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}