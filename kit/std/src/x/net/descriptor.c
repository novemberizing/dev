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
            xuint32 result = xdescriptor_event_void;
            struct timeval basis;
            gettimeofday(&basis, xnil); // CHECK FAIL

            while(result != mask)
            {
                // printf("-------------------\n");
                fd_set readfds;
                fd_set writefds;
                fd_set exceptionfds;
                struct timeval timeval = { 0, 1 };

                FD_ZERO(&readfds);
                FD_ZERO(&writefds);
                FD_ZERO(&exceptionfds);

                if(mask & xdescriptor_event_read)
                {
                    printf("read event set\n");
                    FD_SET(o->f, &readfds);
                }
                if(mask & xdescriptor_event_write)
                {
                    printf("write event set\n");
                    FD_SET(o->f, &writefds);
                }
                FD_SET(o->f, &exceptionfds);

                int ret = select(o->f + 1, &readfds, &writefds, &exceptionfds, &timeval);

                if(ret >= 0)
                {
                    if(FD_ISSET(o->f, &exceptionfds))
                    {
                        return xdescriptor_event_except;
                    }
                    if(FD_ISSET(o->f, &readfds))
                    {
                        printf("readfds\n");
                        result |= xdescriptor_event_read;
                    }
                    if(FD_ISSET(o->f, &writefds))
                    {
                        printf("writefds\n");
                        result |= xdescriptor_event_write;
                    }
                    // xcheck(xtrue, "implement timeout");
                    if(result != mask)
                    {
                        struct timeval current;
                        struct timeval diff;
                        gettimeofday(&current, xnil);   // TODO: ERROR HANDLING
                        timersub(&current, &basis, &diff);
                        xuint64 r = xtimeunisecond(diff.tv_sec, diff.tv_usec);
                        // printf("unisecond (%lu) : response (%lu)\n", unisecond, r);
                        if(xtimeunisecond(diff.tv_sec, diff.tv_usec) < unisecond)
                        {
                            // printf("retry\n");
                            continue;
                        }
                        return xdescriptor_event_timeout;
                    }
                    printf("----------------- 2 -\n");
                }
                else
                {
                    xassertion(xtrue, "fail to select (%d)", errno);
                    return xdescriptor_event_except;
                }
            }
            return result;
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
    return xdescriptor_event_except;
}