#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "std.h"

// static int xsync_none_on(xsync * o);
// static int xsync_none_off(xsync * o);
// static int xsync_none_lock(xsync * o);
// static int xsync_none_unlock(xsync * o);
// static int xsync_none_condon(xsync * o);
// static int xsync_none_condoff(xsync * o);
// static int xsync_none_wait(xsync * o, xuint64 nanosecond);
// static int xsync_none_wakeup(xsync * o, xint32 all);
// static void * xsync_none_rem(void * p);
// static xsync * xsync_none_new(void);

/**
 * xsync * o = xsyncon(xsyncnew());
 */

/**
 *
xsync * xsyncnew(xuint32 type)
{
    switch(type)
    {
        case xsync_type_none:  return xsync_none_new();
        case xsync_type_mutex: return xsync_mutex_new();
    }
    xassertion(xtrue, "unknown type");
}

void * xsyncrem(void * p)
{
}
