#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <poll.h>

#include "../net.h"

extern xclient * xclientnew(int domain, int type, int protocol)
{
    xclient * o = (xclient *) calloc(sizeof(xclient), 1);

    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = (xobj_type_client | xobj_mask_allocated);
    o->destruct = xclientrem;

    o->descriptor = xdescriptorinit();

    o->domain = domain;
    o->type = type;
    o->protocoal = protocol;

    return o;
}

extern void * xclientrem(void * p)
{
    xclient * o = (xclient *) p;
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xsocketclose(o);

        o->protocoal = 0;
        o->type = 0;
        o->domain = 0;

        o->addr = xfree(o->addr);
        o->addrlen = 0;

        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}

extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck(xsocketalive(o), "alive socket");
        if(xsocketalive(o) == xfalse)
        {
            int ret = xsocketopen((xsocket *) o);
            if(ret == xsuccess)
            {
                o->addr = xcopy(o->addr, addr, addrlen, o->addrlen < addrlen);
                o->addrlen = addrlen;

                if(o->flags & xsocket_mask_nonblock)
                {
                    ret = xdescriptor_nonblock_on(xaddressof(o->descriptor));
                    xassertion(ret != xsuccess, "fail to nonblocking");
                }

                ret = connect(o->descriptor.value.f, (struct sockaddr *) o->addr, o->addrlen);
                
                if(ret != xsuccess)
                {
                    int err = errno;
                    if(o->flags & xsocket_mask_nonblock)
                    {
                        if(err == EINPROGRESS)
                        {
                            o->status |= xclient_status_connecting;
                            return xsuccess;
                        }
                    }
                    xcheck(xtrue, "fail to connect (%d)", err);
                    xsocketclose(o);
                    return xfail;
                }
                o->status |= xclient_status_connected;
                return xsuccess;
            }
            else
            {
                xassertion(xtrue, "fail to xsocketopen");
            }
        }
    }

    return xfail;
}

extern xint32 xclientreconnect(xclient * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xcheck(xsocketalive(o), "alive socket");

        if(xsocketalive(o) == xfalse)
        {
            xassertion(o->addr == xnil || o->addrlen == 0, "address is not exist");
            int ret = xsocketopen((xsocket *) o);
            if(ret == xsuccess)
            {
                if(o->flags & xsocket_mask_nonblock)
                {
                    ret = xdescriptor_nonblock_on(xaddressof(o->descriptor));
                    xassertion(ret != xsuccess, "fail to nonblocking");
                }
                ret = connect(o->descriptor.value.f, (struct sockaddr *) o->addr, o->addrlen);
                
                if(ret != xsuccess)
                {
                    xsocketclose(o);
                    return xfail;
                }
                return xsuccess;
            }
            else
            {
                xassertion(xtrue, "fail to xsocketopen");
            }
        }
    }

    return xfail;
}

extern xuint32 xclientwait(xclient * o, xuint32 mask, xuint64 nanosecond)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck(xsocketalive(o) == xfalse, "client is not alive");
        if(xsocketalive(o))
        {
            int result = xclient_event_void;
            if(mask & xclient_event_connect)
            {
                struct pollfd fds = { xinvalid, (POLLIN | POLLOUT), 0 };
                fds.fd = o->descriptor.value.f;
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
                        int ret = connect(o->descriptor.value.f, (struct sockaddr *) o->addr, o->addrlen);
                        if(ret == xsuccess)
                        {
                            result |= xclient_event_connect;
                        }
                        else if(ret < 0)
                        {
                            int err = errno;
                            if(err == EALREADY || err == EISCONN)
                            {
                                result |= xclient_event_connect;
                            }
                            else
                            {
                                return xclient_event_except;
                            }
                        }
                        clock_gettime(CLOCK_REALTIME, &current);
                        diff.tv_sec = current.tv_sec - start.tv_sec;
                        diff.tv_nsec = current.tv_nsec - start.tv_nsec;
                        if(diff.tv_nsec < 0)
                        {
                            diff.tv_sec = diff.tv_sec - 1;
                            diff.tv_nsec = 1000000000 + diff.tv_nsec;
                        }
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
                return xdescriptorwait(xaddressof(o->descriptor), mask, nanosecond);
            }
        }
    }
    return xclient_event_except;
}