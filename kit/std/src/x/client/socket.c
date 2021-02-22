#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "socket.h"

static xint64 xclientsocketprocessor_tcp_on(xclientsocket * o, xuint32 event, void * data);
static xint64 xclientsocketprocessor_tcp_open(xclientsocket * o);
static xint64 xclientsocketprocessor_tcp_in(xclientsocket * o);
static xint64 xclientsocketprocessor_tcp_out(xclientsocket * o);
static xint64 xclientsocketprocessor_tcp_close(xclientsocket * o);
static xint64 xclientsocketprocessor_tcp_exception(xclientsocket * o);

static xint32 xclientsocketstatuscheck_tcp(xclientsocket * o, xuint32 event);
static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * data, xint64 val);

extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xassertion(client == xnil, "");

    xclientsocket * o = (xclientsocket *) calloc(sizeof(xclientsocket), 1);

    o->handle.f       = xinvalid;
    o->client         = client;
    o->domain         = domain;
    o->type           = type;
    o->protocol       = protocol;
    o->addr           = xobjectdup(addr, addrlen);
    o->addrlen        = addrlen;

    o->process        = xclientsocketprocessor_tcp_on;
    o->check          = xclientsocketstatuscheck_tcp;
    o->on             = xclientsocketsubscriber_tcp;
    o->rem            = xclientsocket_rem;

    return o;
}

extern xclientsocket * xclientsocket_rem(xclientsocket * o)
{
    xassertion(o->subscription, "");
    xassertion(o->handle.f >=0, "");
    xassertion(o->event.queue, "");

    o->sync = xsyncrem(o->sync);
    o->addr = xobjectrem(o->addr);
    o->stream.in = xstreamrem(o->stream.in);
    o->stream.out = xstreamrem(o->stream.out);

    free(o);

    return xnil;
}

static xint64 xclientsocketprocessor_tcp_on(xclientsocket * o, xuint32 event, void * data)
{
    switch(event)
    {
        case xdescriptoreventmask_open:         return xclientsocketprocessor_tcp_open(o);
        case xdescriptoreventmask_in:           return xclientsocketprocessor_tcp_in(o);
        case xdescriptoreventmask_out:          return xclientsocketprocessor_tcp_out(o);
        case xdescriptoreventmask_close:        return xclientsocketprocessor_tcp_close(o);
        case xdescriptoreventmask_exception:    return xclientsocketprocessor_tcp_close(o);
        // REMOVE LOGIC 은 살펴 보자.
        case xdescriptoreventmask_rem:          return xclientsocketprocessor_tcp_close(o);
    }
    xassertion(event, "");
}

static xint64 xclientsocketprocessor_tcp_open(xclientsocket * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        if((o->status & xdescriptorstatus_open) == xdescriptorstatus_void)
        {
            if(o->handle.f < 0)
            {
                xassertion(o->status & xdescriptorstatus_bind, "");
                xassertion(o->status & xdescriptorstatus_create, "");
                xassertion(o->status & xdescriptorstatus_connecting, "");
                xassertion(o->status & xdescriptorstatus_connect, "");

                o->handle.f = socket(o->domain, o->type, o->protocol);

                if(o->handle.f < 0)
                {
                    o->exception.func   = socket;
                    o->exception.number = errno;
                    o->status          |= xdescriptorstatus_exception;
                    return xfail;
                }
            }
            else
            {
                xassertion((o->status & xdescriptorstatus_create) == xdescriptorstatus_void, "");
                if(o->status & xdescriptorstatus_connect)
                {
                    return xsuccess;
                }
                if(o->status & xdescriptorstatus_connecting)
                {
                    xint32 value = xsuccess;
                    if(getsockopt(o->handle.f, SOL_SOCKET, SO_ERROR, &value, sizeof(xint32)) == xsuccess)
                    {
                        if(value == EAGAIN || value == EINPROGRESS)
                        {
                            return xsuccess;
                        }
                        else if(value == xsuccess)
                        {
                            o->status |= (xdescriptorstatus_connect | xdescriptorstatus_bind);
                            o->status &= (~xdescriptorstatus_connecting);
                            o->on(o, xdescriptoreventmask_connect, xnil, 0);
                            return xsuccess;
                        }
                        else
                        {
                            o->exception.func   = connect;
                            o->exception.number = value;
                            o->status          |= xdescriptorstatus_exception;
                            return xfail;
                        }
                    }
                    else
                    {
                        o->exception.func   = getsockopt;
                        o->exception.number = errno;
                        o->status          |= xdescriptorstatus_exception;
                        return xfail;
                    }
                }
            }
            xdescriptorset_nonblock((xdescriptor *) o, xtrue);
            xint32 ret = connect(o->handle.f, o->addr, o->addrlen);
            if(ret == xsuccess)
            {
                o->status |= (xdescriptorstatus_connect | xdescriptorstatus_bind);
                o->on(o, xdescriptoreventmask_connect, xnil, 0);
                return xsuccess;
            }
            else
            {
                if(errno == EAGAIN || errno == EINPROGRESS)
                {
                    o->status |= xdescriptorstatus_connecting;
                    o->on(o, xdescriptorstatus_connecting, xnil, 0);
                    return xsuccess;
                }
                else
                {
                    o->exception.func   = connect;
                    o->exception.number = errno;
                    o->status          |= xdescriptorstatus_exception;
                    return xfail;
                }
            }
        }
        return xsuccess;
    }
    return xfail;
}

static xint64 xclientsocketprocessor_tcp_in(xclientsocket * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        // TODO: 적절한 TCP 버그 크기를 구한다.
        xstreamcapacity_set(o->stream.in, xstreamcapacity_get(o->stream.in) + 8192);
        return xdescriptorread((xdescriptor *) o, xstreamback(o->stream.in), xstreamremain(o->stream.in));
    }
    return xfail;
}

static xint64 xclientsocketprocessor_tcp_out(xclientsocket * o)
{
    if(xdescriptorcheck_close((xdescriptor *) o) == xfalse)
    {
        // TODO: 적절한 TCP 버그 크기를 구한다.
        xstreamcapacity(o->stream.in, 8192);
        return xdescriptorwrite((xdescriptor *) o, xstreamfront(o->stream.in), xstreamlen(o->stream.in));
    }
    return xfail;
}

static xint64 xclientsocketprocessor_tcp_close(xclientsocket * o)
{
    if(o->exception.func)
    {
        o->on(o, xdescriptoreventmask_exception, xaddressof(o->exception), 0);
        xexceptioninit(xaddressof(o->exception));

    }
    if(o->handle.f >= 0)
    {

        // TODO: SHUTDOWN IMPLEMENT
        if(close(o->handle.f) != xsuccess)
        {
            o->exception.func   = close;
            o->exception.number = errno;
            o->on(o, xdescriptoreventmask_exception, xaddressof(o->exception), 0);
            xexceptioninit(xaddressof(o->exception));
        }
        o->status   |= xdescriptorstatus_close;
        o->handle.f  = xinvalid;
    }

    return xsuccess;
}

static xint32 xclientsocketstatuscheck_tcp(xclientsocket * o, xuint32 event)
{
    if(event == xdescriptoreventmask_out)
    {
        return xstreamlen(o->stream.out) > 0;
    }
    // 다른 이벤트 체크는 필요에 따라서 구현한다.
    xassertion(event, "");
}

static xint64 xclientsocketsubscriber_tcp(xclientsocket * o, xuint32 event, void * data, xint64 val)
{
    switch(event)
    {
        case xdescriptoreventmask_in:           return o->client->on(o->client, event, o->stream.in, val);
        case xdescriptoreventmask_out:          return o->client->on(o->client, event, o->stream.out, val);
        case xdescriptoreventmask_exception:    return o->client->on(o->client, event, xaddressof(o->exception), 0);
        case xdescriptoreventmask_close:        return o->client->on(o->client, event, xnil, 0);
        case xdescriptoreventmask_rem:          return o->client->on(o->client, event, xnil, 0);
        case xdescriptoreventmask_register:     return o->client->on(o->client, event, xnil, val);
    }
    return o->client->on(o->client, event, data, val);
}


// static inline void xclientsocket_nonblock_check(xclientsocket * o)
// {
//     if(o->subscription && xsocketmask_has(xsocketmask_nonblock))
//     {
//         xsocketnonblock((xsocket *) o, xtrue);
//     }
// }

// static inline xint64 xclientsocket_tcp_open(xclientsocket * o, void * parameter)
// {
//     if(xsocketcreate(o) != xsuccess)
//     {
//         return xfail;
//     }


//     // xclientsocket_nonblock_check(o);
//     // if(!xsocketstatus_has(xsocketstatus_connect))
//     // {
//     //     xint64 ret = connect(o->handle.f, (struct sockaddr *) o->addr, o->addrlen);

//     //     if(ret == xsuccess)
//     //     {
//     //         o->status |= xsocketstatus_connect;
//     //     }
//     //     else
//     //     {
//     //         int err = errno;
//     //         if(err == EAGAIN || err == EINPROGRESS)
//     //         {
//     //             o->status |= xsocketstatus_connecting;
//     //         }
//     //         else
//     //         {
//     //             o->status |= xsocketstatus_exception;
//     //             return xfail;
//     //         }
//     //     }
//     // }
//     // else
//     // {
//     //     xassertion(xsocketstatus_has(xsocketstatus_connect), "");
//     // }

//     // return xsuccess;
// }

// static inline xint64 xclientsocket_open(xclientsocket * o, void * parameter)
// {
//     if(!xsocketstatus_has(xsocketstatus_open))
//     {
//         switch(o->protocol)
//         {
//             case IPPROTO_TCP: return xclientsocket_tcp_open(o, parameter);
//         }
//         xassertion(xtrue, "");
//     }
//     else
//     {
//         xassertion(xtrue, "");
//     }
//     return xsuccess;
// }

// static inline xint64 xclientsocket_in(xclientsocket * o, void * parameter)
// {
//     return xfail;
//     // return xsocket_in((xsocket *) o, parameter);
// }

// static inline xint64 xclientsocket_out(xclientsocket * o, void * parameter)
// {
//     return xfail;
//     // return xsocket_out((xsocket *) o, parameter);
// }

// static inline xint64 xclientsocket_close(xclientsocket * o, void * parameter)
// {
//     return xfail;
//     // return xsocket_close((xsocket *) o, parameter);
// }

// static inline xint64 xclientsocket_exception(xclientsocket * o, void * parameter)
// {
//     return xfail;
//     // return xsocket_exception((xsocket *) o, parameter);
// }

// static inline xint64 xclientsocket_processor(xclientsocket * o, xuint32 event, void * parameter)
// {
//     xassertion(o == xnil, "");
//     // SUBSCRIPTION 이 존재하면서,... ENGINE 에 PROCESSOR POOL 사이즈가 존재하면,
    




//     switch(event)
//     {
//         case xsocketevent_open:         return xclientsocket_open(o, parameter);
//         case xsocketevent_in:           return xclientsocket_in(o, parameter);
//         case xsocketevent_out:          return xclientsocket_out(o, parameter);
//         case xsocketevent_close:        return xclientsocket_close(o, parameter);
//         case xsocketevent_exception:    return xclientsocket_exception(o, parameter);
//     }
//     xassertion(xtrue, "");
// }

// extern xclientsocket * xclientsocket_new(int domain, int type, int protocol, const void * addr, xuint32 addrlen, xuint32 mask)
// {
//     xclientsocket * o = calloc(sizeof(xclientsocket), 1);

//     o->mask     = mask;

//     o->handle.f = xinvalid;

//     o->domain   = domain;
//     o->type     = type;
//     o->protocol = protocol;
//     o->addr     = xobjectnew(addr, addrlen);
//     o->addrlen  = addrlen;

//     o->rem      = xnil; // TODO
//     o->process  = xclientsocket_processor;

//     // /** INHERITED EVENT TARGET */
//     // xclientsocketdestructor    rem;
//     // xsocketsubscription *      subscription;
//     // xsync *                    sync;
//     // xuint32                    mask;
//     // xuint32                    status;
//     // /** INHERITED DESCRIPTOR */
//     // xdescriptorhandle          handle;
//     // xclientsocketprocessor     process;
//     // xclientsocketstatuschecker check;
//     // xclientsocketsubscriber    on;
//     // /** INHERITED SOCKET */
//     // xint32                     domain;
//     // xint32                     type;
//     // xint32                     protocol;
//     // /** CLIENT SOCKT MEMBER */
//     // void *                     addr;
//     // xuint32                    addrlen;
//     // xsocketstream              stream;

//     return o;
// }