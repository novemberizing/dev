#define _GNU_SOURCE

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "descriptor.h"
#include "socket.h"
#include "client.h"

struct xsocket
{
    union
    {
        xint32 f;
        handle v;
    } handle;
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
    struct
    {
        xstream * in;
        xstream * out;
    } stream;
    xclient *             parent;
};

static xint64 xclient_socket_event_on(xsocket * descriptor, xuint32 event, const void * param, xint64 val);
static xint64 xclient_socket_process(xsocket * descriptor, xuint32 event);
static xsocket * xclient_socket_rem(xsocket * descriptor);

extern xclient * xclient_new(int domain, int type, int protocol, const void * addr, xuint32 addrlen, xuint64 size)
{
    xassertion(size < sizeof(xclient), "invalid size");

    xclient * client               = (xclient *) calloc(size, 1);

    xassertion(client == xnil, "fail to calloc (%d)", errno);

    client->descriptor             = xsocket_new(domain,
                                                 type,
                                                 protocol,
                                                 xclient_socket_event_on,
                                                 xclient_socket_process,
                                                 sizeof(xsocket));

    client->descriptor->addr       = xdup(addr, addrlen);
    client->descriptor->addrlen    = addrlen;
    client->descriptor->stream.in  = xnil;   // TODO: IMPLEMENT STREAM
    client->descriptor->stream.out = xnil;  // TODO: IMPLEMENT STREAM
    client->descriptor->parent     = client;

    return client;
}

extern xclient * xclient_rem(xclient * client)
{
    if(client)
    {
        client->descriptor = xclient_socket_rem(client->descriptor);
        client->sync       = xsync_rem(client->sync);
        free(client);
        client = xnil;
    }
    return client;
}

extern xint32 xclient_connect(xclient * client)
{
    xassertion(client == xnil, "client is null");
    if(client->descriptor->handle.f < 0)
    {
        xint64 ret = xsocket_open(client->descriptor);
        if(ret != xsuccess)
        {
            xcheck(xtrue, "fail to xsocket open");
            return xfail;
        }
    }
    if(client->descriptor->handle.f >= 0)
    {
        if((client->descriptor->status & xdescriptor_status_connect) == xdescriptor_status_void)
        {
            xint64 ret = xsocket_connect(client->descriptor, client->descriptor->addr, client->descriptor->addrlen);
            if(ret != xsuccess)
            {
                xcheck(ret != xsuccess, "fail to xsocket connect");
                return xfail;
            }
        }
        else
        {
            xcheck(xtrue, "socket is already connected");
        }
        return xsuccess;
    }
    else
    {
        xcheck(xtrue, "socket is not open");
    }
    return xfail;
}

extern xint64 xclient_read(xclient * client, void * buffer, xuint64 size)
{
    xassertion(client == xnil, "client is null");

    if(client->descriptor->stream.in)
    {
        // TODO: 8192 대신에 적절한 값을 체크하도록 하자.
        xstream_recapacity(client->descriptor->stream.in, 8196);
        xint64 n = xsocket_read(client->descriptor,
                                xstream_back(client->descriptor->stream.in),
                                xstream_remain(client->descriptor->stream.in));

        if(n >= 0)
        {
            xstream_push(client->descriptor->stream.in, xnil, n);
            if(buffer && size)
            {
                return xstream_pop(client->descriptor->stream.in, buffer, size);
            }
        }

        return n;
    }

    return xsocket_read(client->descriptor, buffer, size);
}

extern xint64 xclient_write(xclient * client, const void * data, xuint64 len)
{
    xassertion(client == xnil, "client is null");

    if(client->descriptor->stream.out)
    {
        if(xstream_size(client->descriptor->stream.out) == 0)
        {
            xint64 n = xsocket_write(client->descriptor, data, len);

            if(n >= 0)
            {
                if(n != len)
                {
                    xstream_push(client->descriptor->stream.out,
                                 xaddressof(((unsigned char *) data)[n]),
                                 len - n);
                }
            }
            return n;
        }
        else
        {
            xstream_push(client->descriptor->stream.out, data, len);
            xint64 n = xsocket_write(client->descriptor,
                                     xstream_front(client->descriptor->stream.out),
                                     xstream_size(client->descriptor->stream.out));

            if(n >= 0)
            {
                xstream_pop(client->descriptor->stream.out, xnil, n);
                return len;
            }

            return n;
        }
    }

    return xsocket_write(client->descriptor, data, len);
}

extern xint32 xclient_close(xclient * client)
{
    xassertion(client == xnil, "client is null");
    return xsocket_close(client->descriptor);
}

extern xint32 xclient_shutdown(xclient * client, xint32 how)
{
    xassertion(client == xnil, "client is null");
    return xsocket_shutdown(client->descriptor, how);
}

extern xuint32 xclient_wait(xsocket * descriptor, xuint32 event, xint64 second, xint64 nanosecond)
{
    xassertion(xtrue, "implement this");
    xassertion(descriptor == xnil, "descriptor is null");
    
    if(descriptor->handle.f >= 0)
    {
        if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
        {
            struct pollfd pollfd;
            pollfd.fd = descriptor->handle.f;
            pollfd.revents = 0;
            pollfd.events  = (POLLNVAL | POLLPRI | POLLHUP | POLLRDHUP | POLLERR);
            if(event & (xdescriptor_event_in | xdescriptor_event_connect))
            {
                pollfd.events |= POLLIN;
            }
            if(event & xdescriptor_event_out)
            {
                pollfd.events |= POLLOUT;
            }
            xtime current = xtimeget();
            xtime limit = xtimegen(current.second + second, current.nanosecond + nanosecond);
            struct timespec timeout = { 0, 1000 };  // 1 unisecond: TODO: 적절한 값을 찾자.
            xuint32 result = 0;
            while((result & event) != event && (result & xdescriptor_event_exception) == xdescriptor_event_void)
            {
                int nfds = ppoll(&pollfd, 1, &timeout, xnil);
                if(nfds >= 0)
                {
                    if(pollfd.revents & (POLLNVAL | POLLPRI | POLLHUP | POLLRDHUP | POLLERR))
                    {
                        result |= xdescriptor_event_exception;
                        break;
                    }
                    else
                    {
                        if(event & xdescriptor_event_connect && (descriptor->status & xdescriptor_status_connect) == xdescriptor_status_void)
                        {
                            int ret = connect(descriptor->handle.f, (struct sockaddr *) descriptor->addr, descriptor->addrlen);
                            if(ret == xsuccess)
                            {
                                result |= xdescriptor_event_connect;

                                descriptor->status |= xdescriptor_status_connect;
                                descriptor->status &= (~xdescriptor_status_connecting);
                                xint64 ret = xdescriptor_event_on(descriptor, xdescriptor_status_connect, xnil, 0);
                                if(ret < 0)
                                {
                                    descriptor->status |= xdescriptor_status_exception;
                                    result             |= xdescriptor_event_exception;
                                    break;
                                }
                            }
                            else
                            {

                            }
                        }
                        else
                        {
                            if(pollfd.revents & POLLOUT)
                            {
                                result |= xdescriptor_event_out;
                            }
                            if(pollfd.revents & POLLIN)
                            {
                                result |= xdescriptor_event_in;
                            }
                        }
                    }
                }
                else
                {
                    int err = errno;
                    switch(err)
                    {
                        case EFAULT: xassertion(err == EFAULT, "The array given as argument was not contained in the calling program's address space. (%d)", err); break;
                        case EINTR:  xassertion(err == EINTR, "A signal occurred before any requested event. (%d)", err); break;
                        case EINVAL: xassertion(err == EINVAL, "The nfds value exceeds the RLIMIT_NOFILE value. or The timeout value expressed in *ip is invalid (negative). (%d)", err); break;
                        case ENOMEM: xassertion(err == ENOMEM, "There was no space to allocate file descriptor tables. (%d)", err); break;
                        default:     xassertion(err, "Unknown (%d)", err); break;
                    }
                }
                if((result & event) != event && (result & xdescriptor_event_exception) == xdescriptor_event_void)
                {
                    current = xtimeget();
                    if(xtimecmp(&limit, &current) <= 0)
                    {
                        result |= xdescriptor_event_timeout;
                        break;
                    }
                    pollfd.revents = 0;
                    continue;
                }
            }
            return result;
        }
        else
        {
            xcheck(xtrue, "descriptor's status is exception");
        }
    }
    else
    {
        xcheck(descriptor->handle.f < 0, "descriptor is not open");
    }
    return xdescriptor_event_exception;
}

/**
 * 모든 이벤트를 보내지 않는다.
 */
static xsocket * xclient_socket_rem(xsocket * descriptor)
{
    xassertion(descriptor == xnil, "descriptor is null");

    int ret = xsuccess;

    if(descriptor->handle.f >= 0)
    {
        xcheck(descriptor->handle.f >= 0, "descriptor is open");

        ret = shutdown(descriptor->handle.f, SHUT_RDWR);
        xcheck(ret != xsuccess, "fail to shutdown (%d)", errno);

        ret = close(descriptor->handle.f);
        xcheck(ret != xsuccess, "fail to close (%d)", errno);

        descriptor->handle.f = xinvalid;
    }
    descriptor->status = xdescriptor_status_void;
    
    xassertion(descriptor->io || descriptor->prev || descriptor->next, "descriptor is registered in descriptor event engine");

    descriptor->sync = xsync_rem(descriptor->sync);
    descriptor->addr = xfree(descriptor->addr);

    descriptor->stream.in = xstream_rem(descriptor->stream.in);
    descriptor->stream.out = xstream_rem(descriptor->stream.out);

    free(descriptor);
    descriptor = xnil;

    return descriptor;
}

static xint64 xclient_socket_event_on(xsocket * descriptor, xuint32 event, const void * param, xint64 val)
{
    // IMPLEMENT THIS
    return xsuccess;
}

static xint64 xclient_socket_process(xsocket * descriptor, xuint32 event)
{
    // IMPLEMENT FOR DESCRIPTOR EVENT ENGINE
    return xsuccess;
}