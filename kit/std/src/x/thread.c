#include "thread.h"

#include "thread/posix.h"

extern xthread * xthreadnew(xthreadfunc func, xuint64 size)
{
    xassertion(func == xnil || size < sizeof(xthread), "");

    xthread * o = (xthread *) calloc(size, 1);

    o->func     = func;

    return o;
}

extern xthread * xthreadrem(xthread * o)
{
    return (xthread *) xthreadposix_rem(o);
}

extern xint32 xthreadcheck_removable(xthread * o)
{
    return (o->status & xthreadstatus_on) == xthreadstatus_void;
}

extern void xthreadcancel(xthread * o, xthreadfunc cancel)
{
    xthreadposix_cancel((xthreadposix *) o, (xthreadposixfunc) cancel);
}

extern void xthreadrun(xthread * o)
{
    xthreadposix_run((xthreadposix *) o);
}