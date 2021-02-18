#include "posix.h"

static void * xthreadposix_routine(void * o);

extern xthreadposix * xthreadposix_rem(xthreadposix * o)
{
    if(o->handle)
    {
        int ret = pthread_join(xvalueof(o->handle), xnil);

        xassertion(ret != xsuccess, "");

        o->handle = xobjectrem(o->handle);
    }
    free(o);
    return xnil;
}

extern void xthreadposix_cancel(xthreadposix * o, xthreadposixfunc cancel)
{
    xassertion(o->cancel, "");
    if(o->handle)
    {
        o->cancel = cancel;
    }
}

extern void xthreadposix_run(xthreadposix * o)
{
    xassertion(o->handle, "");

    o->handle = calloc(sizeof(pthread_t), 1);

    int ret = pthread_create(o->handle, xnil, xthreadposix_routine, o);

    xassertion(ret != xsuccess, "");

    if(ret != xsuccess)
    {
        o->handle = xobjectrem(o->handle);
    }
}

static void * xthreadposix_routine(void * o)
{
    xthreadposix * thread = (xthreadposix *) o;

    thread->status |= xthreadstatus_on;

    thread->func(thread);

    thread->status &= (~xthreadstatus_on);

    if(thread->cancel)
    {
        thread->cancel(thread);
    }

    return xnil;
}
