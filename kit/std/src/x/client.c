#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "client.h"

// typedef xint32 (*xsocket_opener)(xsocket *);
// typedef xint64 (*xsocket_event_processor)(xsocket *, xuint32);
// typedef xint64 (*xsocket_event_handler)(xsocket *, xuint32, const void *, xint64);

static xint64 xclient_socket_event_handler(xsocket * o, xuint32 event, const void * data, xint64 val);
static xint64 xclient_socket_event_processor(xsocket * o, xuint32 event);
static xint32 xclient_socket_opener(xsocket * o);

extern xclient * xclient_new(int domain, int type, int protocol, xclient_event_handler handler, xuint64 size)
{
    xclient * client = (xclient *) calloc(size, 1);
    xassertion(client == xnil, "fail to calloc (%d)", errno);

    // extern xsocket * xsocket_new(xint32 f,
    //                              int domain,
    //                              int type,
    //                              int protocol,
    //                              xsocket_event_handler handler,
    //                              xsocket_event_processor processor,
    //                              xsocket_opener opener);

    client->descriptor = xsocket_new(xinvalid,
                                     domain,
                                     type,
                                     protocol,
                                     xclient_socket_event_handler,
                                     xclient_socket_event_processor,
                                     xclient_socket_opener);

    // xsocket_data_set(x)

    // client->descriptor->internal.stream.in  = xstream_new();
    // client->descriptor->internal.stream.out = xstream_new();



    return client;
}

extern xint32 xclient_connect(xclient * client, void * addr, xuint32 addrlen)
{
    if(client)
    {
        if(xsocket_alive(client->descriptor) == xfalse)
        {
            if(addr && addrlen)
            {
                if(client->addr)
                {
                    free(client->addr);
                }

                client->addr = xdup(addr, addrlen);
                client->addrlen = addrlen;
            }
        }
        else
        {
            // TODO: 20210204 NEED TO ...
            if(addr && addrlen)
            {
                if(client->addr == xnil || client->addrlen == 0)
                {
                    xassertion(xtrue, "need to reconnect");
                    return xfail;
                }
            }
            xcheck(xtrue, "already connected");
            return xsuccess;
        }
    }
    return xfail;
}

static xint64 xclient_socket_event_handler(xsocket * o, xuint32 event, const void * data, xint64 val)
{
    return xfail;
}

static xint64 xclient_socket_event_processor(xsocket * o, xuint32 event)
{
    return xfail;
}

static xint32 xclient_socket_opener(xsocket * o)
{
    if(o)
    {
        if(xsocket_alive(o) == xfalse)
        {

        }
        else
        {

        }
    }
    else
    {
        xassertion(o == xnil, "socket is null");
    }
    return xfail;
}
