#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <poll.h>

#include "../net.h"

extern xint32 xdescriptoralive(const xdescriptor * o)
{
    return o ? o->value.f >= 0 : xfalse;
}

extern xint32 xdescriptor_nonblock_on(xdescriptor * o)
{
    if(o)
    {
        if(o->value.f >= 0)
        {
            int flags = fcntl(o->value.f, F_GETFL, 0);
            xassertion(flags == xfail, "fail to fcntrl (%d)", errno);
            flags |= O_NONBLOCK;
            int ret = fcntl(o->value.f, F_SETFL, flags);
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
        if(o->value.f >= 0)
        {
            int flags = fcntl(o->value.f, F_GETFL, 0);
            xassertion(flags == xfail, "fail to fcntrl (%d)", errno);
            flags &= (~O_NONBLOCK);
            int ret = fcntl(o->value.f, F_SETFL, flags);
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
        xcheck((o->value.f >= 0) == xfalse, "socket not opened");

        if(o->value.f >= 0)
        {
            if(close(o->value.f) != xsuccess)
            {
                xassertion(xtrue, "fail to close (%d)", errno);
            }
            o->value.f = xinvalid;
        }
        return xsuccess;
    }
    return xfail;
}

extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 nanosecond)
{
    if(o)
    {
        if(o->value.f >= 0)
        {
            struct pollfd fds = { xinvalid, 0, 0 };
            fds.fd = o->value.f;
            if(mask & xdescriptor_event_read)
            {
                fds.events |= POLLIN;
            }
            if(mask & xdescriptor_event_write)
            {
                fds.events |= POLLOUT;
            }
            if(mask & xdescriptor_event_error)
            {
                fds.events |= POLLERR;
            }
            if(mask & xdescriptor_event_pri)
            {
                fds.events |= POLLPRI;
            }
            if(mask & xdescriptor_event_readhup)
            {
                fds.events |= POLLRDHUP;
            }
            if(mask & xdescriptor_event_hup)
            {
                fds.events |= POLLHUP;
            }
            if(mask & xdescriptor_event_invalid)
            {
                fds.events |= POLLNVAL;
            }
            if(mask & xdescriptor_event_readband)
            {
                fds.events |= POLLRDBAND;
            }
            if(mask & xdescriptor_event_writeband)
            {
                fds.events |= POLLWRBAND;
            }
            int result = xdescriptor_event_void;
            struct timespec start = { 0, 0};
            struct timespec current = { 0, 0 };
            struct timespec diff = { 0, 0};
            clock_gettime(CLOCK_REALTIME, &start);  // TODO: CHECK FAIL
            struct timespec timespec = { 0, 1000 };
            while((result & mask) != mask)
            {
                int nfds = ppoll(&fds, 1, &timespec, xnil);
                if(nfds >= 0)
                {
                    /**
                     * TODO: 마스크 처리하는데 시간이 많이 걸린다.
                     * 어떻게 하면 STD 라이브러리 헤더 없이 ....
                     */
                    if(fds.revents & POLLIN)
                    {
                        result |= xdescriptor_event_read;
                    }
                    if(fds.revents & POLLOUT)
                    {
                        result |= xdescriptor_event_write;
                    }
                    if(fds.revents & POLLPRI)
                    {
                        result |= xdescriptor_event_pri;
                    }
                    if(fds.revents & POLLERR)
                    {
                        result |= xdescriptor_event_error;
                    }
                    if(fds.revents & POLLRDHUP)
                    {
                        result |= xdescriptor_event_readhup;
                    }
                    if(fds.revents & POLLHUP)
                    {
                        result |= xdescriptor_event_hup;
                    }
                    if(fds.revents & POLLRDBAND)
                    {
                        result |= xdescriptor_event_readband;
                    }
                    if(fds.revents & POLLWRBAND)
                    {
                        result |= xdescriptor_event_writeband;
                    }
                    if(fds.revents & POLLNVAL)
                    {
                        result |= xdescriptor_event_invalid;
                    }
                    clock_gettime(CLOCK_REALTIME, &current);
                    diff.tv_sec = current.tv_sec - start.tv_sec;
                    diff.tv_nsec = current.tv_nsec - start.tv_nsec;
                    if(diff.tv_nsec < 0)
                    {
                        diff.tv_sec = diff.tv_sec - 1;
                        diff.tv_nsec = 1000000000 + diff.tv_nsec;
                    }
                    // check overflow
                    if((result & mask) != mask)
                    {
                        if(nanosecond < xtimenanosecond(diff.tv_sec, diff.tv_nsec))
                        {
                            result |= xdescriptor_event_timeout;
                            return result;
                        }
                    }
                }
                else
                {
                    xassertion(xtrue, "fail to ppoll (%d)", errno);
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