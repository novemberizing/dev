#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "../net.h"

extern xint32 xdescriptoralive(const xdescriptor * o)
{
    return o ? o->f > 0 : xfalse;
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