#include <stdio.h>
#include <stdlib.h>

#include "../thread.h"

#include "../descriptor/status.h"

#include "socket.h"

static void xsessionsocketeventhandler_tcp(xsessionsocketevent * event);
static xint64 xsessionsocketsubscriber_tcp(xsessionsocket * descriptor, xuint32 event, void * data, xint64 result);
static xint64 xsessionsocketprocessor_tcp(xsessionsocket * descriptor, xuint32 event, void * data);
static xint32 xsessionsocketcheck_tcp(xsessionsocket * descriptor, xuint32 event);

extern xsessionsocket * xsessionsocket_new(xint32 domain, xint32 type, xint32 protocol)
{
    xsessionsocket * descriptor = (xsessionsocket * ) calloc(sizeof(xsessionsocket), 1);

    descriptor->rem = xsessionsocket_rem;
    descriptor->handle.f = xinvalid;
    descriptor->event.descriptor = descriptor;
    descriptor->event.on = xsessionsocketeventhandler_tcp;
    descriptor->process = xsessionsocketprocessor_tcp;
    descriptor->check = xsessionsocketcheck_tcp;
    descriptor->on = xsessionsocketsubscriber_tcp;
    descriptor->domain = domain;
    descriptor->type = type;
    descriptor->protocol = protocol;

    return descriptor;
}

extern xsessionsocket * xsessionsocket_rem(xsessionsocket * descriptor)
{
    if(descriptor)
    {
        xassertion(descriptor->subscription, "");
        xassertion(descriptor->status != xdescriptorstatus_void && descriptor->status != xdescriptorstatus_rem, "");
        xassertion(descriptor->handle.f >= 0, "");
        xassertion(descriptor->event.queue || descriptor->event.prev || descriptor->event.next, "");

        descriptor->sync = xsyncrem(descriptor->sync);

        descriptor->stream.in = xstreamrem(descriptor->stream.in);
        descriptor->stream.out = xstreamrem(descriptor->stream.out);

        free(descriptor);
    }
    return xnil;
}

extern xstream * xsessionsocketstreamin_get(xsessionsocket * descriptor)
{
    return descriptor->stream.in;
}

extern void xsessionsocketstreamin_set(xsessionsocket * descriptor, xstream * stream)
{
    xassertion(descriptor->stream.in, "");

    descriptor->stream.in = stream;
}

extern xstream * xsessionsocketstreamout_get(xsessionsocket * descriptor)
{
    return descriptor->stream.out;
}

extern void xsessionsocketstreamout_set(xsessionsocket * descriptor, xstream * stream)
{
    xassertion(descriptor->stream.out, "");

    descriptor->stream.out = stream;
}

static void xsessionsocketeventhandler_tcp(xsessionsocketevent * event)
{
    xassertion(xtrue, "implement this");
}

static xint64 xsessionsocketsubscriber_tcp(xsessionsocket * descriptor, xuint32 event, void * data, xint64 result)
{
    xassertion(xtrue, "implement this");

    return xfail;
}

static xint64 xsessionsocketprocessor_tcp(xsessionsocket * descriptor, xuint32 event, void * data)
{
    xassertion(xtrue, "implement this");

    return xfail;
}

static xint32 xsessionsocketcheck_tcp(xsessionsocket * descriptor, xuint32 event)
{
    xassertion(xtrue, "implement this");

    return xfail;
}
