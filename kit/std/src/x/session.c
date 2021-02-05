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

    struct
    {
        xstream * in;
        xstream * out;
    } stream;

    xsession *            parent;
};

static xint64 xsession_socket_event_on(xsocket * descriptor, xuint32 event, const void * param, xint64 val);
static xint64 xsession_socket_process(xsocket * descriptor, xuint32 event);

extern xsession * xsession_new(int domain, int type, int protocol, xuint64 size)
{
    xassertion(size < sizeof(xsession), "invalid size parameter");

    xsession * session = (xsession *) calloc(size, 1);

    session->descriptor = xsocket_new(domain,
                                      type,
                                      protocol,
                                      xsession_socket_event_on,
                                      xsession_socket_process,
                                      sizeof(xsocket));

    xassertion(session->descriptor == xnil, "session->descriptor == xnil");

    session->descriptor->domain   = domain;
    session->descriptor->type     = type;
    session->descriptor->protocol = protocol;
    session->descriptor->parent   = session;

    return session;
}

extern xint64 xsession_read(xsession * session, void * buffer, xuint64 size)
{
    xassertion(session == xnil, "client is null");

    if(session->descriptor->stream.in)
    {
        // TODO: 8192 대신에 적절한 값을 체크하도록 하자.
        xstream_recapacity(session->descriptor->stream.in, 8196);
        xint64 n = xsocket_read(session->descriptor,
                                xstream_back(session->descriptor->stream.in),
                                xstream_remain(session->descriptor->stream.in));

        if(n >= 0)
        {
            xstream_push(session->descriptor->stream.in, xnil, n);
            if(buffer && size)
            {
                return xstream_pop(session->descriptor->stream.in, buffer, size);
            }
        }

        return n;
    }

    return xsocket_read(session->descriptor, buffer, size);
}

extern xint64 xsession_write(xsession * session, const void * data, xuint64 len)
{
    xassertion(session == xnil, "session is null");

    if(session->descriptor->stream.out)
    {
        if(xstream_size(session->descriptor->stream.out) == 0)
        {
            xint64 n = xsocket_write(session->descriptor, data, len);

            if(n >= 0)
            {
                if(n != len)
                {
                    xstream_push(session->descriptor->stream.out,
                                 xaddressof(((unsigned char *) data)[n]),
                                 len - n);
                }
            }
            return n;
        }
        else
        {
            xstream_push(session->descriptor->stream.out, data, len);
            xint64 n = xsocket_write(session->descriptor,
                                     xstream_front(session->descriptor->stream.out),
                                     xstream_size(session->descriptor->stream.out));

            if(n >= 0)
            {
                xstream_pop(session->descriptor->stream.out, xnil, n);
                return len;
            }

            return n;
        }
    }

    return xsocket_write(session->descriptor, data, len);
}

extern xint32 xsession_close(xsession * session)
{
    xassertion(session == xnil, "client is null");
    return xsocket_close(session->descriptor);
}

extern xint32 xsession_shutdown(xsession * session, xint32 how)
{
    xassertion(session == xnil, "session is null");
    return xsocket_shutdown(session->descriptor, how);
}

extern xsession * xserver_default_session_factory(xserver * server)
{
    xsession * session = xsession_new(server->descriptor->domain,
                                      server->descriptor->type,
                                      server->descriptor->protocol,
                                      sizeof(xsession));

    session->descriptor->stream.in = xstream_new(0);
    session->descriptor->stream.out = xstream_new(0);

    return session;
}

extern void xserver_default_session_releaser(xserver * server, xsession * session)
{
    xcheck(xtrue, "implement this");
    // TODO: IMPLEMENT THIS
}

static xint64 xsession_socket_event_on(xsocket * descriptor, xuint32 event, const void * param, xint64 val)
{
    xcheck(xtrue, "implement this");

    return xsuccess;
}

static xint64 xsession_socket_process(xsocket * descriptor, xuint32 event)
{
    xcheck(xtrue, "implement this");

    return xsuccess;
}