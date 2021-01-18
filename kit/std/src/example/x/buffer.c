#include <stdlib.h>
#include <stdio.h>

#include <x/std.h>

int main(int argc, char ** argv)
{
    xbuffer local = xbufferinit(1024);
    xbuffer * o = xaddressof(local);

    o->size += snprintf(xbufferback(o), xbuffercapacity(o), "hello world %lu\n", xthreadid());
    o->size += snprintf(xbufferback(o), xbuffercapacity(o), "hello world %lu\n", xthreadid());

    printf("%s", xbufferfront(o));

    xbufferrem(&local);
    return 0;
}
