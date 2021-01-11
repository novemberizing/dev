/**
 * @file    x/event/engine.c
 * @brief   이벤트 엔진 구현 파일입니다.
 * @details
 * 
 * @version 0.0.1
 * @since   2021. 01. 11.
 */

#include "../event.h"

int xenginerun(xengine * o)
{
    xassertion(o == xnil || o->generators == xnil, "null pointer");

    for(xgenerator * generator = xlisthead(o->generators); generator != xnil; generator = xlistnext(generator))
    {
    }

    return xsuccess;
}