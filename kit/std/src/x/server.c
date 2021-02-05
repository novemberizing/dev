#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "descriptor.h"
#include "socket.h"
#include "server.h"
#include "session.h"

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

    int                   domain;
    int                   type;
    int                   protocol;

    struct sockaddr *     addr;
    socklen_t             addrlen;
    int                   backlog;

    xserver *             parent;
};

static xint64 xserver_socket_event_on(xsocket * descriptor, xuint32 event, const void * param, xint64 val);
static xint64 xserver_socket_process(xsocket * descriptor, xuint32 event);

static xsocket * xserver_socket_rem(xsocket * descriptor);

extern xserver * xserver_new(int domain, int type, int protocol, const void * addr, xuint32 addrlen, xuint64 size)
{
    xassertion(size < sizeof(xserver), "invalid size parameter");

    xserver * server             = (xserver *) calloc(size, 1);

    xassertion(server == xnil, "fail to calloc (%d)", errno);

    server->descriptor           = xsocket_new(domain,
                                               type,
                                               protocol,
                                               xserver_socket_event_on,
                                               xserver_socket_process,
                                               sizeof(xsocket));

    server->descriptor->addr     = xdup(addr, addrlen);
    server->descriptor->addrlen  = addrlen;
    server->descriptor->backlog  = SOMAXCONN;
    server->descriptor->parent   = server;

    return server;
}

extern xserver * xserver_rem(xserver * server)
{
    xassertion(server == xnil, "server is null");

    server->descriptor = xserver_socket_rem(server->descriptor);
    server->sync = xsync_rem(server->sync);

    xassertion(server->sessions.head || server->sessions.tail || server->sessions.total, "server's sessions not cleared");

    free(server);

    return xnil;
}

extern xint32 xserver_listen(xserver * server)
{
    xassertion(server == xnil, "server is null");

    if(server->descriptor->handle.f < 0)
    {
        xint64 ret = xsocket_open(server->descriptor);
        if(ret < 0)
        {
            xcheck(ret < 0, "fail to xsocket open");
            return xfail;
        }
    }

    if(server->descriptor->handle.f >= 0)
    {
        if((server->descriptor->status & xdescriptor_status_bind) == xdescriptor_status_void)
        {
            xint64 ret = xsocket_bind(server->descriptor, server->descriptor->addr, server->descriptor->addrlen);
            if(ret < 0)
            {
                xcheck(ret < 0, "fail to xsocket bind");
                return xfail;
            }
        }

        if((server->descriptor->status & xdescriptor_status_listen) == xdescriptor_status_void)
        {
            xint64 ret = xsocket_listen(server->descriptor, server->descriptor->backlog);
            if(ret < 0)
            {
                xcheck(ret < 0, "fail to xsocket listen");
                return xfail;
            }
        }
        else
        {
            xcheck(xtrue, "server is already listen");
        }
        return xsuccess;
    }
    else
    {
        xcheck(xtrue, "server is not open");
    }

    return xfail;
}

extern xint32 xserver_close(xserver * server)
{
    xassertion(server == xnil, "server is null");
    return xsocket_close(server->descriptor);
}

extern xsession * xserver_accept(xserver * server)
{
    xassertion(server == xnil, "server is null");

    if((server->descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
    {
        if(server->descriptor->status & xdescriptor_status_listen)
        {
            if(server->descriptor->handle.f >= 0)
            {
                struct sockaddr addr;
                socklen_t addrlen = sizeof(struct sockaddr);
                int fd = accept(server->descriptor->handle.f, &addr, &addrlen);
                if(fd >= 0)
                {
                    xsession * session = server->create(server);

                    if(session)
                    {
                        session->descriptor->handle.f = fd;

                        session->prev = server->sessions.tail;
                        if(session->prev)
                        {
                            session->prev->next = session;
                        }
                        else
                        {
                            server->sessions.head = session;
                        }
                        server->sessions.total = server->sessions.total + 1;
                    }

                    return session;
                }
                else
                {
                    int err = errno;
                    if(err == EBADF || err == EINVAL || err == ENOTSOCK)
                    {
                        server->descriptor->status |= xdescriptor_status_exception;
                        xdescriptor_event_on(server->descriptor, xdescriptor_event_exception, xnil, 0);
                    }
                    else if(err == EAGAIN || err == ECONNABORTED || err == EINTR || err == EMFILE || err == ENFILE || err == ENOBUFS || err == ENOMEM || err == EPROTO || err == EPERM)
                    {
                        xassertion(xtrue, "fail to accept (%d) - server is ok", err);
                    }
                    else if(err == EFAULT || err == EOPNOTSUPP)
                    {
                        xassertion(xtrue, "fail to accept (%d) - server is unknown - check this", err);
                    }
                }
            }
            else
            {
                xcheck(xtrue, "descriptor is not open");
            }
        }
        else
        {
            xcheck(xtrue, "server status is not listen");
        }
    }
    else
    {
        xcheck(xtrue, "server status is exception");
    }

    return xnil;
}

static xint64 xserver_socket_event_on(xsocket * descriptor, xuint32 event, const void * param, xint64 val)
{
    xcheck(xtrue, "implement this");

    return xsuccess;
}

static xint64 xserver_socket_process(xsocket * descriptor, xuint32 event)
{
    xcheck(xtrue, "implement this");

    return xsuccess;
}

static xsocket * xserver_socket_rem(xsocket * descriptor)
{
    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {
            int ret = close(descriptor->handle.f);
            xcheck(ret != xsuccess, "fail to close (%d)", errno);
        }

        xassertion(descriptor->next || descriptor->prev || descriptor->io, "descriptorio not cleared");
        descriptor->sync = xsync_rem(descriptor->sync);
        descriptor->addr = xfree(descriptor->addr);

        free(descriptor);
        descriptor = xnil;
    }
    return descriptor;
}