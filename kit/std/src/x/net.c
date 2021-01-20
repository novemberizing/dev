#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "net.h"

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

extern xint32 xsocketopen(xsocket * o)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck(xsocketalive(o), "socket is alive");
        if(xsocketalive(o) == xfalse)
        {
            o->descriptor.f = socket(o->domain, o->type, o->protocoal);
            
            xassertion(o->descriptor.f < 0, "fail to socket (%d)", errno);


        }
        return xsuccess;
    }
    return xfail;
}