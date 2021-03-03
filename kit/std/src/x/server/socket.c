#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../thread.h"

#include "socket.h"

static void xserversocketeventhandler_tcp(xserversocketevent * server);
static xint64 xserversocketprocessor_tcp(xserversocket *, xuint32, void *);
static xint64 xserversocketsubscriber_tcp(xserversocket *, xuint32, void *, xint64);
static xint32 xserversocketcheck_tcp(xserversocket *, xuint32);

static xint64 xserversocketprocessor_tcp_open(xserversocket * descriptor, void * data);
static xint64 xserversocketprocessor_tcp_in(xserversocket * descriptor, void * data);
static xint64 xserversocketprocessor_tcp_close(xserversocket * descriptor, void * data);

extern xserversocket * xserversocket_new(xserver * server, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xserversocket * descriptor = calloc(sizeof(xserversocket), 1);

    descriptor->rem      = xserversocket_rem;
    descriptor->handle.f = xinvalid;
    descriptor->process  = xserversocketprocessor_tcp;
    descriptor->check    = xserversocketcheck_tcp;
    descriptor->on       = xserversocketsubscriber_tcp;
    descriptor->event.on = xserversocketeventhandler_tcp;
    descriptor->domain   = domain;
    descriptor->type     = type;
    descriptor->protocol = protocol;
    descriptor->addr     = xobjectdup(addr, addrlen);
    descriptor->addrlen  = addrlen;
    descriptor->server   = server;
    descriptor->backlog  = SOMAXCONN;

    return descriptor;
}

extern xint32 xserversocketcheck_open(xserversocket * descriptor)
{
    xassertion(descriptor == xnil, "");
    if(descriptor->handle.f < 0)
    {
        return xfalse;
    }
    if((descriptor->status & xserversocketstatus_open) == xserversocketstatus_void)
    {
        return xfalse;
    }

    return xtrue;
}

extern xint32 xserversocketcheck_rem(xserversocket * descriptor)
{
    xassertion(descriptor == xnil, "");

    if(descriptor->subscription)
    {
        return xfalse;
    }
    if(descriptor->handle.f >= 0)
    {
        return xfalse;
    }
    if(descriptor->event.queue || descriptor->event.next || descriptor->event.prev)
    {
        return xfalse;
    }
    return xtrue;
}

extern xserversocket * xserversocket_rem(xserversocket * descriptor)
{
    xassertion(xserversocketcheck_rem(descriptor), "");

    descriptor->sync = xsyncrem(descriptor->sync);
    descriptor->addr = xobjectrem(descriptor->addr);

    free(descriptor);
    
    return xnil;
}

extern void xserversocketbacklog_set(xserversocket * descriptor, xint32 backlog)
{
    xassertion(descriptor == xnil, "");

    descriptor->backlog = backlog;
}

static void xserversocketeventhandler_tcp(xserversocketevent * server)
{
    xassertion(xtrue, "implement this");
}

static xint64 xserversocketprocessor_tcp(xserversocket * descriptor, xuint32 event, void * data)
{
    switch(event)
    {
        case xserversocketeventtype_open:   return xserversocketprocessor_tcp_open(descriptor, data);
        case xserversocketeventtype_in:     return xserversocketprocessor_tcp_in(descriptor, data);
        case xserversocketeventtype_close:  return xserversocketprocessor_tcp_close(descriptor, data);
    }
    xassertion(xtrue, "implement this");
}

static xint64 xserversocketprocessor_tcp_open(xserversocket * descriptor, void * data)
{
    if(xserversocketcheck_open(descriptor) == xfalse)
    {
        if((descriptor->status & xsocketstatus_create) == xsocketstatus_void)
        {
            
        }


    #define xsocketstatus_create        xsocketeventtype_create
#define xsocketstatus_bind          xsocketeventtype_bind
    }
    return xfail;
}

static xint64 xserversocketprocessor_tcp_in(xserversocket * descriptor, void * data)
{
    xassertion(xtrue, "");

    return xfail;
}

static xint64 xserversocketprocessor_tcp_close(xserversocket * descriptor, void * data)
{
    xassertion(xtrue, "");

    return xfail;
}

static xint64 xserversocketsubscriber_tcp(xserversocket * descriptor, xuint32 event, void * data, xint64 result)
{
    xassertion(xtrue, "implement this");
}

static xint32 xserversocketcheck_tcp(xserversocket * descriptor, xuint32 event)
{
    xassertion(xtrue, "implement this");
}
