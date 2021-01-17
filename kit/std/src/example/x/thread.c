#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <x/std.h>

xint32 __total = 0;
xthread ** __internal_threads = xnil;

xobj * example_xthreadfunc(xthread * o)
{
    xprimitive * primitive = (xprimitive *) o->param;
    xint32 result = 0;
    for(xint32 i = 0; i < primitive->value.i32; i++)
    {
        result = result + 1;
    }
    return (xobj *) xprimitivenew(xvalgen(result));
}

static xthread ** create_threads(xint32 total)
{
    __total = total > 0 ? total : 1;

    xthread ** threads = (xthread **) calloc(sizeof(xthread *), __total);

    for(xint32 i = 0; i < __total; i++)
    {
        threads[i] = xthreadon(xthreadnew(example_xthreadfunc, (xobj *) xprimitivenew(xvalgen((xrandomgen() % 64) + 1))));
    }

    return threads;
}

static void check_simple_thread(int total)
{
    __internal_threads = create_threads(total);

    for(xint32 i = 0; i < __total; i++)
    {
        xthreadrem(__internal_threads[i]);
    }
    free(__internal_threads);

    __internal_threads = xnil;
}

int main(int argc, char ** argv)
{
    xrandomon();

    check_simple_thread(xrandomgen() % 64);

    return 0;
}