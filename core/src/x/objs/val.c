#include <stdlib.h>

#include "../std.h"

/**
 * @fn      xobjval * xobjvalnew(xval v)
 * @brief   xval 객체를 동적할당으로 생성합니다.
 * @details
 * 
 * @param   | v | in | xval | 값 |
 * 
 * @return  | xobjval * | xval 객체 |
 */
xobjval * xobjvalnew(xval v)
{
    xobjval * o = (xobjval *) calloc(sizeof(xobjval), 1);

    o->flags = xobj_mask_allocated | xobj_type_val;
    o->destruct = xnil;
    o->value = v;

    return o;
}

