#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "../net.h"

extern xclient * xclientnew(int domain, int type, int protocol)
{
    xclient * o = (xclient *) calloc(sizeof(xclient), 1);

    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = (xobj_type_client | xobj_mask_allocated);
    o->destruct = xclientrem;

    o->domain = domain;
    o->type = type;
    o->protocoal = protocol;

    return o;
}

extern void * xclientrem(void * p)
{
    xclient * o = (xclient *) p;
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xsocketclose(o);

        o->protocoal = 0;
        o->type = 0;
        o->domain = 0;

        o->addr = xfree(o->addr);
        o->addrlen = 0;

        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}

extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen)
{
    xcheck(o == xnil, "");
    if(o)
    {
        xcheck(xsocketalive(o), "alive socket");
        if(xsocketalive(o) == xfalse)
        {
            int ret = xsocketopen((xsocket *) o);
            if(ret == xsuccess)
            {
                o->addr = xcopy(o->addr, addr, addrlen, o->addrlen < addrlen);
                o->addrlen = addrlen;

                ret = connect(o->descriptor.f, (struct sockaddr *) o->addr, o->addrlen);
                
                if(ret != xsuccess)
                {
                    xsocketclose(o);
                    return xfail;
                }
                return xsuccess;
            }
            else
            {
                xassertion(xtrue, "fail to xsocketopen");
            }
        }
    }

    return xfail;
}

extern xint32 xclientreconnect(xclient * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xcheck(xsocketalive(o), "alive socket");

        if(xsocketalive(o) == xfalse)
        {
            xassertion(o->addr == xnil || o->addrlen == 0, "address is not exist");
            int ret = xsocketopen((xsocket *) o);
            if(ret == xsuccess)
            {
                ret = connect(o->descriptor.f, (struct sockaddr *) o->addr, o->addrlen);
                
                if(ret != xsuccess)
                {
                    xsocketclose(o);
                    return xfail;
                }
                return xsuccess;
            }
            else
            {
                xassertion(xtrue, "fail to xsocketopen");
            }
        }
    }

    return xfail;
}

extern xint32 xclientclose(xclient * o)
{
    return xsocketclose(o);
}