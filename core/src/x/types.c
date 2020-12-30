#include "types.h"
#include "log.h"

xobj * xobjrem(xobj * o)
{
    xcheck(o == xnil, xnil, "o == xnil");

    xassertion(xobjhas(o, xallocated) == false, "xobjhas(o, xallocated) == false");

    if(o->rem)
    {
        o->rem(o);
    }
    free(o);
    
    return xnil;
}