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