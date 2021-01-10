#include <stdlib.h>
#include <errno.h>

#include "log.h"
#include "func.h"

xfunc * xfuncnew(xobj * parameter, xobj * (*call)(xobj *), void (*back)(xfunc *, xobj *))
{
    xfunc * o = (xfunc *) calloc(sizeof(xfunc), 1);
    assertion(o == xnil, "o == xnil");

    o->parameter = parameter;
    o->call = call;
    o->back = back;
    
    return o;
}

xfunc * xfuncrem(xfunc * o)
{
    debug(o == xnil, xnil, "o == xnil");

    if(o->back)
    {
        if(o->status != xfunc_status_none)
        {
            o->status = xfunc_status_fail;
        }
        o->back(o, o->result);
    }

    xobjrem(o->parameter);
    xobjrem(o->result);

    free(o);

    return xnil;
}

xobj * xfunccall(xfunc * o)
{
    o->result = o->call(o->parameter);
    o->status = xfunc_status_success;
    
    return o->result;
}