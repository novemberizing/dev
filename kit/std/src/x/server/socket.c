#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"

#include "socket.h"

static void xserversocketeventhandler_tcp(xserversocketevent * server);

extern xserversocket * xserversocket_new(xserver * server, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen)
{
    xserversocket * descriptor = calloc(sizeof(xserversocket), 1);

    descriptor->server           = server;
    descriptor->domain           = domain;
    descriptor->type             = type;
    descriptor->protocol         = protocol;
    descriptor->addr             = xobjectdup(addr, addrlen);
    descriptor->addrlen          = addrlen;

    descriptor->rem              = xserversocket_rem;
    descriptor->handle.f         = xinvalid;

    descriptor->event.descriptor = descriptor;
    descriptor->event.on         = xserversocketeventhandler_tcp;

    // descriptor->factory          = xsessionfactory_tcp;
    // descriptor->rem              = xsessionreleaser_tcp;

    return descriptor;
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

static void xserversocketeventhandler_tcp(xserversocketevent * server)
{
    xassertion(xtrue, "implement this");
}
