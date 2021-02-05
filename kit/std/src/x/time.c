#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "std.h"

extern xtime xtimeget(void)
{
    xtime result;

    struct timespec timespec;
    int ret = clock_gettime(CLOCK_REALTIME, &timespec);

    xassertion(ret != xsuccess, "fail to clock_gettime (%d)", errno);

    result.second     = timespec.tv_sec;
    result.nanosecond = timespec.tv_nsec;

    return result;
}

extern xtime xtimegen(xint64 second, xint64 nanosecond)
{
    xtime result = { second, nanosecond };

    if(result.nanosecond < 0)
    {
        xint64 value = labs(result.nanosecond);
        result.second = result.second - (value / 1000000000);
        if(value % 1000000000)
        {
            result.second = result.second - 1;
        }
        result.nanosecond = 1000000000 - (value % 1000000000);
    }
    else
    {
        if(result.nanosecond / 1000000000)
        {
            result.second = result.second - result.nanosecond / 1000000000;
            result.nanosecond = (result.nanosecond % 1000000000);
        }
    }

    return result;
}

extern xint64 xtimecmp(const xtime * x, const xtime * y)
{
    xassertion(x == xnil || y == xnil, "x is null or y is null");

    if(x->second == y->second)
    {
        return x->nanosecond - y->nanosecond;
    }

    return x->second - y->second;
}
