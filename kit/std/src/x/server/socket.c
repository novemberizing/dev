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

extern xserversocket * xserversocket_rem(xserversocket * descriptor);
extern void xserversocketfactory_set(xserversocket * server, xsessionfactory factory);
extern void xserversocketreleaser_set(xserversocket * server, xsessionreleaser releaser);