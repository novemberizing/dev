#include <time.h>
#include <errno.h>
#include <stdio.h>

#include "std.h"

extern xtime xtimeget(void)
{
    struct timespec timespec;

    struct xtime o = { 0, };

    if(clock_gettime(CLOCK_REALTIME, &timespec) == xsuccess)
    {
        o.second = timespec.tv_sec;
        o.nanosecond = timespec.tv_nsec;
    }
    else
    {
        xassertion(xtrue, "fail to clock_gettime (%d)", errno);
    }

    return o;
}

extern xtime xtimeset(xint64 second, xint64 nanosecond)
{
    xtime o = { second, nanosecond };

    if(o.nanosecond < 0)
    {
        o.second = o.second - (o.nanosecond / 1000000000 + 1);
        o.nanosecond = o.nanosecond - ((o.nanosecond / 1000000000 + 1) * 1000000000);
    }

    if(o.nanosecond >= 1000000000)
    {
        o.second = o.second + (o.nanosecond / 1000000000);
        o.nanosecond = o.nanosecond % 1000000000;
    }

    return o;
}

extern xint64 xtimecmp(const xtime * x, const xtime * y)
{
    xassertion(x == xnil || y == xnil, "invalid parameter");

    if(x->second != y->second)
    {
        return x->second - y->second;
    }

    return x->nanosecond - y->nanosecond;
}
