#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "std.h"

extern unsigned long xthreadid(void)
{
    return pthread_self();
}

extern xsync * xsync_rem(xsync * sync)
{
    if(sync)
    {
        xassertion(xtrue, "implement this");
    }
    return xnil;
}