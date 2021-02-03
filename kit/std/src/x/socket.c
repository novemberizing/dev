#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "socket.h"
#include "descriptor.h"

struct xsocket
{
    union
    {
        int    f;
        void * v;
    } handle;

    xuint32            status;

    xdescriptor *      prev;
    xdescriptor *      next;
    xdescriptorio *    io;

    xsocket_opener          open;
    xsocket_event_processor process;
    xsocket_event_handler   on;

    int domain;
    int type;
    int protocol;
};

extern xsocket * xsocket_new(xint32 f, int domain, int type, int protocol, xsocket_event_handler handler, xsocket_event_processor processor, xsocket_opener opener)
{
    xsocket * o = (xsocket *) calloc(sizeof(xsocket), 1);

    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->handle.f = xinvalid;
    o->open     = opener;
    o->process  = processor;
    o->on       = handler;

    o->domain   = domain;
    o->type     = type;
    o->protocol = protocol;

    return o;
}

extern xsocket * xsocket_rem(xsocket * o)
{
    if(o)
    {
        xassertion(o->handle.f >= 0, "socket must close");
        xassertion(o->prev || o->next || o->io, "socket must unregister");

        free(o);
        o = xnil;
    }

    return o;
}

extern xint32 xsocket_open(xsocket * o)
{
    if(o)
    {
        if(o->handle.f < 0)
        {
            o->handle.f = socket(o->domain, o->type, o->protocol);

            if(o->handle.f >= 0)
            {
                o->status |= xsocket_event_create;

                if(o->on)
                {
                    if(o->on(o, xsocket_event_create, xnil, 0) != xsuccess)
                    {
                        int ret = close(o->handle.f);

                        xcheck(ret != xsuccess, "fail to close (%d)", errno);

                        o->handle.f = xinvalid;
                        o->status |= xsocket_status_close;
                        o->on(o, xsocket_event_close, xnil, 0);
                        o->status = xsocket_status_void;

                        return xfail;
                    }
                }

                return xsuccess;
            }
            else
            {
                xcheck(o->handle.f < 0, "fail to socket (%d)", errno);
                return xfail;
            }
        }
        else
        {
            xcheck(o->handle.f >= 0, "fail to open");
            return xsuccess;
        }
    }
    else
    {
        xcheck(o == xnil, "socket is null");
    }
    return xfail;
}

extern xint32 xsocket_close(xsocket * o)
{
    if(o)
    {
        if(o->handle.f >= 0)
        {
            int ret = close(o->handle.f);
            xcheck(ret != xsuccess, "fail to close (%d)", errno);

            o->handle.f = xinvalid;
            if(o->on)
            {
                o->status |= xsocket_status_close;
                o->on(o, xsocket_event_close, xnil, 0);
            }
            o->status = xsocket_status_void;
        }
        else
        {
            xcheck(o->handle.f < 0, "socket is not open");
        }
        return xsuccess;
    }
    else
    {
        xcheck(o == xnil, "socket is null");
    }

    return xfail;
}

extern xint64 xsocket_read(xsocket * o, void * buffer, xuint64 size)
{
    if(o)
    {
        if(o->handle.f >= 0)
        {
            if(buffer && size)
            {
                xint64 n = read(o->handle.f, buffer, size);
                if(n > 0)
                {

                }
                else if(n == 0)
                {

                }
                else
                {
                    
                }
            }
            else
            {
                xcheck(buffer == xnil || size == 0, "buffer is not exist");
                return xsuccess;
            }
        }
        else
        {
            xcheck(o->handle.f < 0, "socket is not open");
        }
    }
    else
    {
        xcheck(o == xnil, "socket is null");
    }
    return xfail;
}

extern xint64 xsocket_write(xsocket * o, const void * data, xuint64 len)
{
    xint64 n = 0;
    return n;
}
