#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
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
                                 xaddressof(data[n]),
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
