#include "log.h"
#include "obj.h"

xobj * xobjrem(xobj * o)
{
    debug(o == xnil, xnil, "o == xnil");

    if(o->destruct)
    {
        o->destruct(o);
    }
    free(o);
    
    return xnil;
}