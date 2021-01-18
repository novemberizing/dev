#include <stdio.h>

#include <x/std.h>

xthreadlocal * threadlocal = xnil;

static xobj * internal_thread_func(xthread * o)
{
    xthreadlocalset(threadlocal, xprimitivenew(xvalgen(xrandomgen() % 64)));

    xprimitive * data = (xprimitive *) xthreadlocalget(threadlocal);

    if(data != xnil)
    {
        printf("%u\n", data->value.u32);
    }
    else
    {
        printf("data is xnil\n");
    }
    

    // thread 에서 시그널 생성

    return xnil;
}

static void custom_object_free(void * p)
{
    printf("called \n");
    xobjrem(p);
}

int main(int argc, char ** argv)
{
    xrandomon();

    threadlocal = xthreadlocalnew(custom_object_free);
    
    int total = xrandomgen() % 64;
    for(int i = 0; i < total; i++)
    {
        xthread * o = xthreadon(xthreadnew(internal_thread_func, xnil));

        xthreadrem(o);
        printf("thread is destroy\n");
    }

    xthreadlocalrem(threadlocal);
    return 0;
}
