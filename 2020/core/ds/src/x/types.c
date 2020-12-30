#include <stdlib.h>
#include <errno.h>

#include "log.h"
#include "types.h"

xobj * xobjrem(xobj * o)
{
    xcheck(o == xnil, xnil, "o == xnil");
    xcheck(xisallocated(o->type) == false, o, "xisallocated(o->type) == false");

    if(o->rem)
    {
        o->rem(o);
    }
    free(o);

    return xnil;
}

xfunc * xfuncnew(xobj * param, xobj * (*call)(xobj *), void (*back)(xfunc *, xobj *))
{
    xassertion(call == xnil, "call == xnil");

    xfunc * o = (xfunc *) calloc(sizeof(xfunc), 1);
    xassertion(o == xnil, "calloc => %d", errno);

    o->param = param;
    o->call = call;
    o->back = back;
    o->status = xallocated;

    return o;
}

xfunc * xfuncrem(xfunc * o)
{
    xcheck(o == xnil, xnil, "o == xnil");
    xcheck(xisallocated(o->status) == false, o, "xisallocated(o->status) == false");

    xassertion(xfuncisprogress(o), "xfuncisprogress(o)");

    xobjrem(o->param);
    xobjrem(o->result);
    free(o);

    return xnil;
}

xfunc * xfuncinit(xfunc * o, xobj * param, xobj * (*call)(xobj *), void (*back)(xfunc *, xobj *))
{
    xcheck(o == xnil, xnil, "o == xnil");

    xassertion(xfuncisprogress(o), "xfuncisprogress(o)");

    o->param = xobjrem(o->param);
    o->result = xobjrem(o->result);

    o->status = xisallocated(o->status) ? xallocated : 0;
    o->param = param;
    o->call = call;
    o->back = back;

    return o;
}

xfunc * xfuncterm(xfunc * o)
{
    xcheck(o == xnil, xnil, "o == xnil");

    xassertion(xfuncisprogress(o), "xfuncisprogress(o)");

    o->param = xobjrem(o->param);
    o->result = xobjrem(o->result);
    o->status = xisallocated(o->status) ? xallocated : 0;
    o->call = xnil;
    o->back = xnil;

    return o;
}

xobj * xfunccall(xfunc * o)
{
    xassertion(o == xnil, "o == xnil");
    xassertion(o->result != xnil || o->status != xallocated, "o->result != xnil || o->status != xallocated");

    o->status |= xfunc_status_call;
    o->result = o->call(o->param);
    o->status |= xfunc_status_success;

    return o->result;
}

// debug
#if 1

struct __test_param_xobj
{
    xuint32 type;
    struct xobj * (*rem)(struct xobj *);
    xuint32 x;
    xuint32 * y;
};

static inline xobj * __test_param_xobj_rem(xobj * o)
{
//    xassertion(x)
    return xnil;
}


int __check_x_types(int total)
{
    for(int i = 0; i < total; i++)
    {
        // static func
        xfunc local = { 0, };
        // xfuncinit(&local, xnil, )
        xfuncinit(&local, )

        xfuncterm(&local);
        xfunc * heap = xnil;
    }

    return true;
}

#endif // 