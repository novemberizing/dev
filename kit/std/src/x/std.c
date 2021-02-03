#include <stdlib.h>

#include "std.h"

extern void * xfree(void * address)
{
    if(address)
    {
        free(address);
    }

    return xnil;
}

extern void * xdup(const void * source, xuint64 len)
{
    if(source && len)
    {
        void * o = malloc(len);

        memcpy(o, source, len);

        return o;
    }
    return xnil;
}