#include <stdio.h>

#include <x/std.h>

static xuint64 __nanosecondgen(xuint64 second, xint64 value)
{
    second = (value / 1000000000) % second;

    value = (value % 1000000000);
    value = (value == 0 ? 1 : value);

    return second * 1000000000 + value;
}

static void check_sync_impl(xint64 total)
{
    for(xint64 i = 0; i < total; i++)
    {
        xsync * o = xsynccondon(xsyncnew(xsync_type_mutex));

        xsynclock(o);
        xsyncwait(o, __nanosecondgen(2, xrandomgen()));
        xsyncunlock(o);

        xsyncrem(o);
    }
}

int main(int argc, char ** argv)
{
    xrandomon();

    check_sync_impl(xrandomgen() % 64);
    return 0;
}
