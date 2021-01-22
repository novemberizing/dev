#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

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

extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 unisecond)
{
    if(o)
    {
        if(o->f > 0)
        {
            fd_set readfds;
            fd_set writefds;
            fd_set exceptionfds;
            struct timeval timeval = { unisecond / 1000000 , unisecond % 1000000 };

            FD_ZERO(&readfds);
            FD_ZERO(&writefds);
            FD_ZERO(&exceptionfds);

            if(mask & xdescriptor_event_read)
            {
                FD_SET(o->f, &readfds);
            }
            if(mask & xdescriptor_event_write)
            {
                FD_SET(o->f, &writefds);
            }
            if(mask & xdescriptor_event_except)
            {
                FD_SET(o->f, &exceptionfds);
            }

            int ret = select(1, &readfds, &writefds, &exceptionfds, &timeval);

            if(ret > 0)
            {
                if(!FD_ISSET(o->f, &exceptionfds))
                {
                    mask &= (~xdescriptor_event_except);
                }
                if(!FD_ISSET(o->f, &readfds))
                {
                    mask &= (~xdescriptor_event_read);
                }
                if(!FD_ISSET(o->f, &writefds))
                {
                    mask &= (~xdescriptor_event_write);
                }
                return mask;
            }
            else if(ret == 0)
            {
                xcheck(xtrue, "check this logic");
            }
            else
            {
                xassertion(xtrue, "fail to select (%d)", errno);
            }
        }
        else
        {
            xcheck(xtrue, "socket is not alive");
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
    return xfail;
}