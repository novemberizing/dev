#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "socket.h"

static inline void xclientsocket_nonblock_check(xclientsocket * o)
{
    if(o->subscription && xsocketmask_has(xsocketmask_nonblock))
    {
        xsocketnonblock((xsocket *) o, xtrue);
    }
}

static inline xint64 xclientsocket_tcp_open(xclientsocket * o, void * parameter)
{
    if(xsocketcreate(o) != xsuccess)
    {
        return xfail;
    }


    // xclientsocket_nonblock_check(o);
    // if(!xsocketstatus_has(xsocketstatus_connect))
    // {
    //     xint64 ret = connect(o->handle.f, (struct sockaddr *) o->addr, o->addrlen);

    //     if(ret == xsuccess)
    //     {
    //         o->status |= xsocketstatus_connect;
    //     }
    //     else
    //     {
    //         int err = errno;
    //         if(err == EAGAIN || err == EINPROGRESS)
    //         {
    //             o->status |= xsocketstatus_connecting;
    //         }
    //         else
    //         {
    //             o->status |= xsocketstatus_exception;
    //             return xfail;
    //         }
    //     }
    // }
    // else
    // {
    //     xassertion(xsocketstatus_has(xsocketstatus_connect), "");
    // }

    // return xsuccess;
}

static inline xint64 xclientsocket_open(xclientsocket * o, void * parameter)
{
    if(!xsocketstatus_has(xsocketstatus_open))
    {
        switch(o->protocol)
        {
            case IPPROTO_TCP: return xclientsocket_tcp_open(o, parameter);
        }
        xassertion(xtrue, "");
    }
    else
    {
        xassertion(xtrue, "");
    }
    return xsuccess;
}

static inline xint64 xclientsocket_in(xclientsocket * o, void * parameter)
{
    return xfail;
    // return xsocket_in((xsocket *) o, parameter);
}

static inline xint64 xclientsocket_out(xclientsocket * o, void * parameter)
{
    return xfail;
    // return xsocket_out((xsocket *) o, parameter);
}

static inline xint64 xclientsocket_close(xclientsocket * o, void * parameter)
{
    return xfail;
    // return xsocket_close((xsocket *) o, parameter);
}

static inline xint64 xclientsocket_exception(xclientsocket * o, void * parameter)
{
    return xfail;
    // return xsocket_exception((xsocket *) o, parameter);
}

static inline xint64 xclientsocket_processor(xclientsocket * o, xuint32 event, void * parameter)
{
    xassertion(o == xnil, "");
    // SUBSCRIPTION 이 존재하면서,... ENGINE 에 PROCESSOR POOL 사이즈가 존재하면,
    




    switch(event)
    {
        case xsocketevent_open:         return xclientsocket_open(o, parameter);
        case xsocketevent_in:           return xclientsocket_in(o, parameter);
        case xsocketevent_out:          return xclientsocket_out(o, parameter);
        case xsocketevent_close:        return xclientsocket_close(o, parameter);
        case xsocketevent_exception:    return xclientsocket_exception(o, parameter);
    }
    xassertion(xtrue, "");
}

extern xclientsocket * xclientsocket_new(int domain, int type, int protocol, const void * addr, xuint32 addrlen, xuint32 mask)
{
    xclientsocket * o = calloc(sizeof(xclientsocket), 1);

    o->mask     = mask;

    o->handle.f = xinvalid;

    o->domain   = domain;
    o->type     = type;
    o->protocol = protocol;
    o->addr     = xobjectnew(addr, addrlen);
    o->addrlen  = addrlen;

    o->rem      = xnil; // TODO
    o->process  = xclientsocket_processor;

    // /** INHERITED EVENT TARGET */
    // xclientsocketdestructor    rem;
    // xsocketsubscription *      subscription;
    // xsync *                    sync;
    // xuint32                    mask;
    // xuint32                    status;
    // /** INHERITED DESCRIPTOR */
    // xdescriptorhandle          handle;
    // xclientsocketprocessor     process;
    // xclientsocketstatuschecker check;
    // xclientsocketsubscriber    on;
    // /** INHERITED SOCKET */
    // xint32                     domain;
    // xint32                     type;
    // xint32                     protocol;
    // /** CLIENT SOCKT MEMBER */
    // void *                     addr;
    // xuint32                    addrlen;
    // xsocketstream              stream;

    return o;
}