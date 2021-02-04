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

    return session;
}

extern xint32 xsession_connect(xsession * session);
extern xint64 xsession_read(xsession * session, void * buffer, xuint64 size);
extern xint64 xsession_write(xsession * session, const void * data, xuint64 len);
extern xint32 xsession_close(xsession * session);
extern xint32 xsession_shutdown(xsession * session, xint32 how);