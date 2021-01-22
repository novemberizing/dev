#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "../net.h"

extern xint32 xdescriptoralive(const xdescriptor * o)
{
    return o ? o->f > 0 : xfalse;
}

extern xint32 xdescriptor_nonblock_on(xdescriptor * o)
{
    if(o)
    {
        if(o->f > 0)
        {
            int flags = fcntl(o->f, F_GETFL, 0);
            xassertion(flags == xfail, "fail to fcntrl (%d)", errno);
            flags |= O_NONBLOCK;
            int ret = fcntl(o->f, F_SETFL, flags);
            xassertion(ret == xfail, "fail to fcntl (%d)", errno);
            return ret;
        }
    }
    return xfail;
}

extern xint32 xdescriptor_nonblock_off(xdescriptor * o)
{
    if(o)
    {
        if(o->f > 0)
        {
            int flags = fcntl(o->f, F_GETFL, 0);
            xassertion(flags == xfail, "fail to fcntrl (%d)", errno);
            flags &= (~O_NONBLOCK);
            int ret = fcntl(o->f, F_SETFL, flags);
            xassertion(ret == xfail, "fail to fcntl (%d)", errno);
            return ret;
        }
    }
    return xfail;
}


extern xint32 xdescriptorclose(xdescriptor * o)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck((o->f > 0) == xfalse, "socket not opened");

        if(o->f > 0)
        {
            if(close(o->f) != xsuccess)
            {
                xassertion(xtrue, "fail to close (%d)", errno);
            }
            o->f = 0;
        }
        return xsuccess;
    }
    return xfail;
}