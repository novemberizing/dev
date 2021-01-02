#include <stdlib.h>
#include <stdio.h>

#include <x/std.h>

#include "_std.h"

int check_xobjval(int total)
{
    for(int i = 0; i < total; i++)
    {
        xuint64 v = random() % 65536;
        xobjval * o = xobjvalnew(xvalgen(v));
        xassertion(v != o->value.u64, "v != o->value.u64");
        o = xobjrem(o);
        xassertion(o != xnil, "o != xnil");

        xobjval stack = xobjvalinit(xvalgen(v));
        xassertion(v != stack.value.u64, "v != o->value.u64");
        o = xobjrem(&stack);
        xassertion(o == xnil, "o == xnil");
    }
    return xtrue;
}

static xobj * __internal_plus(xobj * param)
{
    xobjval * o = (xobjval *) param;
    xobjval * result = xobjvalnew(xvalgen(o->value.u64 + 64));
    return (xobj *) result;
}

static int __reserved_cb = xfalse;
static void __internal_plus_cb(xfun * o)
{
    __reserved_cb != __reserved_cb;
}

int check_xfun(int total)
{
    for(int i = 0; i < total; i++)
    {
        int reserved = __reserved_cb = (random() % 2);
        xuint64 v = random() % 65536;
        xfun * o = xfunnew(__internal_plus, (xobj *) xobjvalnew(xvalgen(v)), __reserved_cb ? __internal_plus_cb : xnil);
        xfuncall(o);
        fprintf(stdout, "%d/%d\n", reserved, __reserved_cb);
        xassertion(reserved && __reserved_cb, "reserved && __reserved_cb");
        xassertion(v + 64 != ((xobjval *) o->result)->value.u64, "v + 64 != ((xobjval *) o->result)->value.u64");
        o = xfunrem(o);
        xassertion(o != xnil, "o != xnil");

        xfun stack = xfuninit(__internal_plus, (xobj *) xobjvalnew(xvalgen(v)), __reserved_cb ? __internal_plus_cb : xnil);
        xfuncall(&stack);
        xassertion(reserved && __reserved_cb, "reserved && __reserved_cb");
        xassertion(v + 64 != ((xobjval *) stack.result)->value.u64, "v + 64 != ((xobjval *) o->result)->value.u64");
        o = xfunrem(&stack);
        xassertion(o == xnil, "o == xnil");
    }
    return xtrue;
}