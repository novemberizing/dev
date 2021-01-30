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

static xuint32 __xclient_internal_poll_mask_convert(xuint32 mask)
{
    xuint32 result = 0;
    if(mask & xdescriptor_event_in)
    {
        result |= POLLIN;
    }
    if(mask & xdescriptor_event_out)
    {
        result |= POLLOUT;
    }
    if(mask & xdescriptor_event_connect)
    {
        result |= (POLLIN | POLLOUT);
    }
    return result;
}

extern xint64 xclientsocketeventon(xsocket * o, void * parent, xuint32 mask, const void * data, xval val)
{

}

extern xclient * xclientnew(int domain, int type, int protocol)
{
    xclient * client = (xclient *) calloc(sizeof(xclient), 1);

    client->flags           = (xobj_mask_allocated);
    client->destruct        = xclientrem;

    client->socket.handle.f = xinvalid;
    client->socket.on       = xclientsocketeventon;

    client->socket.domain   = domain;
    client->socket.type     = type;
    client->socket.protocol = protocol;

    return client;
}

extern void * xclientrem(void * p)
{
    xclient * o = (xclient *) p;
    if(o)
    {
        xsynclock(o->sync);

        xassertion(o->parent, "client's parent already linked");
        xassertion(o->children.total > 0, "client's children exist");

        if(xclientalive(o))
        {
            xclientclose(o);
        }

        o->readbuf  = xobjrem(o->readbuf);
        o->writebuf = xobjrem(o->writebuf);
        o->addr     = xfree(o->addr);
        o->addrlen  = 0;

        xsyncunlock(o->sync);

        o->sync     = xobjrem(o->sync);

        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}

extern xint32 xclientconnect(xclient * client, void * addr, xuint64 addrlen)
{
    if(client)
    {
        if(xclientalive(client) == xfalse)
        {
            int ret = xclientopen(client);
            if(ret != xsuccess)
            {
                xcheck(xtrue, "fail to client open");
                return xfail;
            }
            if((client->socket.status & xdescriptor_status_connect) == xdescriptor_status_void)
            {
                if(addr && addrlen)
                {
                    client->addr    = xcopy(client->addr, addr, addrlen, client->addrlen != addrlen);
                    client->addrlen = addrlen;
                }
                if(client->addr && client->addrlen)
                {
                    int ret = connect(client->socket.handle.f, client->addr, client->addrlen);
                    if(ret == xsuccess)
                    {
                        if((client->socket.status & xdescriptor_status_connect) == xdescriptor_status_void)
                        {
                            client->socket.status |= xdescriptor_status_connect;
                            client->socket.status &= (~xdescriptor_status_connecting);
                            xclienteventpub(xaddressof(client->socket), client, xdescriptor_status_connect, xnil, xvalgen(0));
                        }
                        return xsuccess;
                    }
                    else
                    {
                        int err = errno;
                        if(err == EINPROGRESS)
                        {
                            if((client->socket.status & xdescriptor_status_connecting) == xdescriptor_status_void)
                            {
                                client->socket.status |= xdescriptor_status_connecting;
                                xclienteventpub(xaddressof(client->socket), client, xdescriptor_status_connecting, xnil, xvalgen(0));
                            }
                            return xsuccess;
                        }
                        else if(err == EALREADY || err == EISCONN)
                        {
                            if((client->socket.status & xdescriptor_status_connect) == xdescriptor_status_void)
                            {
                                client->socket.status |= xdescriptor_status_connect;
                                client->socket.status &= (~xdescriptor_status_connecting);
                                xclienteventpub(xaddressof(client->socket), client, xdescriptor_status_connect, xnil, xvalgen(0));
                            }
                            return xsuccess;
                        }
                        else
                        {
                            xcheck(xtrue, "fail to connect (%d)", err);
                            return xfail;
                        }
                    }
                }
                else
                {
                    xassertion(xtrue, "destination is not exist");
                }
            }
            else
            {
                xcheck(xtrue, "client is already connected");
                return xsuccess;
            }
        }
    }
    else
    {
        xcheck(xtrue, "client is null");
    }
    return 0;
}

extern xuint32 xclientwait(xclient * client, xuint32 mask, xint64 second, xint64 nanosecond)
{
    if(client)
    {
        if(client->socket.handle.f >= 0)
        {
            struct pollfd   pollfd;
            struct timespec timeout = { 0, 1000 };

            xtime current   = xtimeget();
            xtime end       = xtimeset(current.second + second, current.nanosecond + nanosecond);
            xuint32 result  = 0;
            
            pollfd.fd       = client->socket.handle.f;
            pollfd.events   = __xclient_internal_poll_mask_convert(mask);
            pollfd.events  |= (POLLERR | POLLHUP | POLLNVAL | POLLPRI | POLLRDHUP);
            pollfd.revents  = 0;

            mask           &= (xdescriptor_event_in | xdescriptor_event_out | xdescriptor_event_connect);

            while((result & mask) != mask)
            {
                int nfds = ppoll(&pollfd, 1, &timeout, xnil);

                if(nfds >= 0)
                {
                    if(pollfd.revents & (~(POLLIN | POLLOUT)))
                    {
                        return xdescriptor_event_exception;
                    }
                    if((mask & xdescriptor_event_connect) && ((result & xdescriptor_event_connect) == xdescriptor_event_void))
                    {
                        if((client->socket.status & xdescriptor_status_connect) == xdescriptor_status_void)
                        {
                            int ret = connect(client->socket.handle.f, client->addr, client->addrlen);
                            if(ret == xsuccess)
                            {
                                client->socket.status |= xdescriptor_status_connect;
                                client->socket.status &= (~xdescriptor_status_connecting);
                                xclienteventpub(xaddressof(client->socket), client, xdescriptor_event_connect, xnil, xvalgen(0));
                            }
                            else
                            {
                                int err = errno;
                                if(err == EALREADY || err == EISCONN)
                                {
                                    client->socket.status |= xdescriptor_status_connect;
                                    client->socket.status &= (~xdescriptor_status_connecting);
                                    xclienteventpub(xaddressof(client->socket), client, xdescriptor_event_connect, xnil, xvalgen(0));
                                }
                                else
                                {
                                    if(err != EINPROGRESS)
                                    {
                                        xcheck(xtrue, "fail to connect (%d)", err);
                                        return xdescriptor_event_exception;
                                    }
                                    else
                                    {
                                        if((result & mask) != mask)
                                        {
                                            current = xtimeget();
                                            if(xtimecmp(&current, &end) >= 0)
                                            {
                                                result |= xdescriptor_event_timeout;
                                                return result;
                                            }
                                        }
                                        pollfd.revents = 0;
                                        continue;
                                    }
                                }
                            }
                            result |= xdescriptor_status_connect;
                            if((result & mask) != mask)
                            {
                                current = xtimeget();
                                if(xtimecmp(&current, &end) >= 0)
                                {
                                    result |= xdescriptor_event_timeout;
                                    return result;
                                }
                            }
                            pollfd.events = 0;
                            if(mask & xdescriptor_event_out)
                            {
                                pollfd.events |= POLLOUT;
                            }
                            if(mask & xdescriptor_event_in)
                            {
                                pollfd.events |= POLLIN;
                            }
                            pollfd.revents = 0;
                            continue;
                        }
                        result |= xdescriptor_status_connect;
                    }
                    if(pollfd.revents & POLLOUT)
                    {
                        result |= xdescriptor_event_out;
                        pollfd.events &= (~POLLOUT);
                    }
                    if(pollfd.revents & POLLIN)
                    {
                        result |= xdescriptor_event_in;
                        pollfd.events &= (~POLLIN);
                    }
                    if((result & mask) != mask)
                    {
                        current = xtimeget();
                        if(xtimecmp(&current, &end) >= 0)
                        {
                            result |= xdescriptor_event_timeout;
                            return result;
                        }
                    }
                }
                else
                {
                    return xdescriptor_event_exception;
                }
            }
            return result;
        }
        else
        {
            xcheck(xtrue, "descriptor is not alive");
        }
    }
    else
    {
        xcheck(xtrue, "descriptor is null");
    }
    return xdescriptor_event_invalid;
}

extern xint32 xclientclose(xclient * client)
{
    if(client)
    {
        int ret = xdescriptorclose((xdescriptor *) xaddressof(client->socket));
        if(ret == xsuccess)
        {
            if(client->parent)
            {
                client->parent->release(client->parent, (xeventobj *) client);
            }
            return xsuccess;
        }
        else
        {
            xcheck(xtrue, "fail to xdescriptorclose");
            return xfail;
        }
    }
    else
    {
        xcheck(xtrue, "client is null");
    }
    return xsuccess;
}