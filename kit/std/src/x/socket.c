#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "descriptor.h"
#include "socket.h"

struct xsocket
{
    union
    {
        xint32 f;
        handle v;
    } handle;
    xuint32               mask;
    xuint32               status;
    xdescriptor *         prev;
    xdescriptor *         next;
    xdescriptorio *       io;
    xsync *               sync;
    xsocket_process_func  process;
    xsocket_event_handler on;

    int domain;
    int type;
    int protocol;
};

extern xsocket * xsocket_new(int domain, int type, int protocol, xsocket_event_handler handler, xsocket_process_func processor, xuint64 size)
{
    xassertion(size < sizeof(xsocket), "invalid size");

    xsocket * descriptor = (xsocket *) calloc(size, 1);

    descriptor->handle.f = xinvalid;

    descriptor->domain   = domain;
    descriptor->type     = type;
    descriptor->protocol = protocol;

    descriptor->on       = handler;
    descriptor->process  = processor;

    return descriptor;
}

extern xint32 xsocket_open(xsocket * descriptor)
{
    xassertion(descriptor == xnil, "descriptor is null");

    if(descriptor->handle.f < 0)
    {
        descriptor->handle.f = socket(descriptor->domain, descriptor->type, descriptor->protocol);

        if(descriptor->handle.f >= 0)
        {
            if(descriptor->mask & xdescriptor_mask_nonblock)
            {
                xint32 ret = xdescriptor_nonblock_on((xdescriptor *) descriptor);
                xassertion(ret != xsuccess, "fail to xdescriptor nonblock");
            }
            descriptor->status |= xdescriptor_status_create;
            xint64 ret = xdescriptor_event_on(descriptor, xdescriptor_event_create, xnil, 0);
            if(ret < 0)
            {
                descriptor->status |= xdescriptor_status_exception;
                xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                return xfail;
            }
            return xsuccess;
        }
        else
        {
            xcheck(descriptor->handle.f < 0, "fail to socket (%d)", errno);
            return xfail;
        }
    }
    else
    {
        xcheck(descriptor->handle.f >= 0, "descriptor is already open");
        return xsuccess;
    }
}

extern xint32 xsocket_bind(xsocket * descriptor, const void * addr, xuint64 addrlen)
{
    xassertion(descriptor == xnil, "descriptor is null");

    if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
    {
        if(descriptor->handle.f >= 0)
        {
            if((descriptor->status & xdescriptor_status_bind) == xdescriptor_status_void)
            {
                xint64 ret = bind(descriptor->handle.f, (const struct sockaddr *) addr, addrlen);
                if(ret == xsuccess)
                {
                    ret = xdescriptor_event_on(descriptor, xdescriptor_event_bind, xnil, 0);
                    if(ret < 0)
                    {
                        xcheck(ret != xsuccess, "fail to bind event handling");
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                        return xfail;
                    }
                    return xsuccess;
                }
                else
                {
                    xcheck(ret != xsuccess, "fail to bind (%d)", errno);
                    descriptor->status |= xdescriptor_status_exception;
                    xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                    return xfail;
                }
            }
            else
            {
                xcheck(xtrue, "descriptor is already bind");
                return xsuccess;
            }
        }
        else
        {
            xcheck(descriptor->handle.f < 0, "descriptor is not open");
        }
    }
    else
    {
        xcheck(xtrue, "descriptor status is exception");
    }
    return xfail;
}

extern xint32 xsocket_listen(xsocket * descriptor, int backlog)
{
    xassertion(descriptor == xnil, "descriptor is null");

    if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
    {
        if(descriptor->handle.f >= 0)
        {
            if((descriptor->status & xdescriptor_status_listen) == xdescriptor_status_void)
            {
                if(descriptor->status & xdescriptor_status_bind)
                {
                    xint64 ret = listen(descriptor->handle.f, backlog);
                    if(ret == xsuccess)
                    {
                        descriptor->status |= xdescriptor_status_listen;
                        ret = xdescriptor_event_on(descriptor, xdescriptor_event_listen, xnil, 0);
                        if(ret < 0)
                        {
                            xcheck(ret != xsuccess, "fail to listen event handling");
                            descriptor->status |= xdescriptor_status_exception;
                            xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                            return xfail;
                        }
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(ret != xsuccess, "fail to listen (%d)", errno);
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                    }
                }
                else
                {
                    xcheck(xtrue, "descriptor status is not bind");
                }
            }
            else
            {
                xcheck(xtrue, "descriptor status is already listen");
            }
        }
        else
        {
            xcheck(xtrue, "descriptor is not open");
        }
    }
    else
    {
        xcheck(xtrue, "descriptor status is exception");
    }
    return xfail;
}

extern xint32 xsocket_connect(xsocket * descriptor, const void * addr, xuint64 addrlen)
{
    xassertion(descriptor == xnil, "descriptor is null");

    if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
    {
        if(descriptor->handle.f >= 0)
        {
            if((descriptor->status & xdescriptor_status_connect) == xdescriptor_status_void)
            {
                xint64 ret = connect(descriptor->handle.f, (const struct sockaddr *) addr, addrlen);
                if(ret == xsuccess)
                {
                    descriptor->status |= xdescriptor_status_connect;
                    ret = xdescriptor_event_on(descriptor, xdescriptor_event_connect, xnil, 0);
                    if(ret != xsuccess)
                    {
                        xcheck(ret != xsuccess, "fail to connect event handing");
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptor_event_on(descriptor, xdescriptor_status_exception, xnil, 0);
                        return xfail;
                    }
                    return xsuccess;
                }
                else
                {
                    int err = errno;
                    if(err == EINPROGRESS || err == EAGAIN)
                    {
                        descriptor->status |= xdescriptor_status_connecting;
                        ret = xdescriptor_event_on(descriptor, xdescriptor_status_connecting, xnil, 0);
                        if(ret != xsuccess)
                        {
                            xcheck(ret != xsuccess, "fail to connecting event handing");
                            descriptor->status |= xdescriptor_status_exception;
                            xdescriptor_event_on(descriptor, xdescriptor_status_exception, xnil, 0);
                            return xfail;
                        }
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(ret != xsuccess, "fail to connect (%d)", err);
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptor_event_on(descriptor, xdescriptor_status_exception, xnil, 0);
                        return xfail;
                    }
                }
            }
            else
            {
                xcheck(xtrue, "descriptor is already connect");
                return xsuccess;
            }
        }
        else
        {
            xcheck(descriptor->handle.f < 0, "descriptor is not open");
        }
    }
    else
    {
        xcheck(xtrue, "descriptor status is exception");
    }

    return xfail;
}

extern xint32 xsocket_shutdown(xsocket * descriptor, xint32 how)
{
    xassertion(descriptor == xnil, "descriptor is null");

    if(descriptor->handle.f >= 0)
    {
        if((how & xdescriptor_event_shutdown_all) == xdescriptor_event_shutdown_all)
        {
            if((descriptor->status & xdescriptor_status_shutdown_all) != xdescriptor_status_shutdown_all)
            {
                xint64 ret = shutdown(descriptor->handle.f, SHUT_RDWR);
                xcheck(ret != xsuccess, "fail to shutdown (%d)", errno);
                descriptor->status |= xdescriptor_status_shutdown_all;
                xdescriptor_event_on(descriptor, xdescriptor_event_shutdown_all, xnil, 0);
            }
            else
            {
                xcheck(xtrue, "already all shutdown");
            }
        }
        else if(how & xdescriptor_event_shutdown_in)
        {
            if((descriptor->status & xdescriptor_status_shutdown_in) == xdescriptor_status_void)
            {
                xint64 ret = shutdown(descriptor->handle.f, SHUT_RD);
                xcheck(ret != xsuccess, "fail to shutdown (%d)", errno);
                descriptor->status |= xdescriptor_status_shutdown_in;
                xdescriptor_event_on(descriptor, xdescriptor_event_shutdown_in, xnil, 0);
            }
            else
            {
                xcheck(xtrue, "already shutdown in");
            }
        }
        else if(how & xdescriptor_event_shutdown_out)
        {
            if((descriptor->status & xdescriptor_status_shutdown_out) == xdescriptor_status_void)
            {
                xint64 ret = shutdown(descriptor->handle.f, SHUT_WR);
                xcheck(ret != xsuccess, "fail to shutdown (%d)", errno);
                descriptor->status |= xdescriptor_status_shutdown_out;
                xdescriptor_event_on(descriptor, xdescriptor_event_shutdown_out, xnil, 0);
            }
            else
            {
                xcheck(xtrue, "already shutdown out");
            }
        }
        else
        {
            xcheck(xtrue, "unknown flags");
        }
    }
    return xsuccess;
}

extern xint64 xsocket_read(xsocket * descriptor, void * buffer, xuint64 size)
{
    return xdescriptor_read((xdescriptor *) descriptor, buffer, size);
}

extern xint64 xsocket_write(xsocket * descriptor, const void * data, xuint64 len)
{
    return xdescriptor_write((xdescriptor *) descriptor, data, len);
}

extern xint32 xsocket_close(xsocket * descriptor)
{
    return xdescriptor_close((xdescriptor *) descriptor);
}

extern xint32 xsocket_nonblock_on(xsocket * descriptor)
{
    return xdescriptor_nonblock_on((xdescriptor *) descriptor);
}

extern xint32 xsocket_nonblock_off(xsocket * descriptor)
{
    return xdescriptor_nonblock_off((xdescriptor *) descriptor);
}

extern xuint32 xsocket_wait(xsocket * descriptor, xuint32 event, xint64 second, xint64 nanosecond)
{
    return xdescriptor_wait((xdescriptor *) descriptor, event, second, nanosecond);
}

extern void      xsocket_mask_add(xsocket * descriptor, xuint32 mask)
{
    xdescriptor_mask_add((xdescriptor *) descriptor, mask);
}

extern void      xsocket_mask_del(xsocket * descriptor, xuint32 mask)
{
    xdescriptor_mask_del((xdescriptor *) descriptor, mask);
}
