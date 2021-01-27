#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "../net.h"

extern xint32 xsocketopen(xsocket * o)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck(xsocketalive(o), "socket is alive");
        if(xsocketalive(o) == xfalse)
        {
            o->descriptor.value.f = socket(o->domain, o->type, o->protocoal);
            
            xassertion(o->descriptor.value.f < 0, "fail to socket (%d)", errno);
        }
        return xsuccess;
    }
    return xfail;
}

extern xsocket * xsocketnew(int domain, int type, int protocol)
{
    xsocket * o = (xsocket *) calloc(sizeof(xsocket), 1);

    o->flags = xobj_type_socket | xobj_mask_allocated;
    o->destruct = xsocketrem;
    
    o->descriptor = xdescriptorinit();

    o->domain = domain;
    o->type = type;
    o->protocoal = protocol;

    return o;
}

extern void * xsocketrem(void * p)
{
    xsocket * o = (xsocket *) p;
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xassertion(xobjtype(o) != xobj_type_socket, "invalid object");

        xsocketclose(o);

        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }

    return o;
}

extern xint64 xsocketwrite(xsocket * o, const xbyte * data, xuint64 len)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck(xsocketalive(o) == xfalse, "socket is closed");
        if(xsocketalive(o))
        {
            xcheck(len == 0, "invalid parameter");
            if(len > 0)
            {
                xint64 n = write(o->descriptor.value.f, data, len);
                if(n > 0)
                {
                    return n;
                }
                else if(n == 0)
                {
                    xcheck(xtrue, "check this logic");
                }
                else
                {
                    int ret = errno;
                    if(ret == EAGAIN)
                    {
                        return xsuccess;
                    }
                    xcheck(xtrue, "fail to write (%d)", errno);
                    xsocketclose(o);
                    return xfail;
                }
            }
            return xsuccess;
        }
    }
    return xfail;
}

extern xint64 xsocketread(xsocket * o, void * buffer, xuint64 len)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck(xsocketalive(o) == xfalse, "socket is closed");
        if(xsocketalive(o))
        {
            xcheck(len == 0, "invalid parameter");
            if(len > 0)
            {
                xint64 n = read(o->descriptor.value.f, buffer, len);
                if(n > 0)
                {
                    return n;
                }
                else if(n == 0)
                {
                    // socket read zero is close
                    return xfail;
                }
                else
                {
                    int ret = errno;
                    if(ret == EAGAIN)
                    {
                        return xsuccess;
                    }
                    xcheck(xtrue, "fail to write (%d)", errno);
                    xsocketclose(o);
                    return xfail;
                }
            }
            return xsuccess;
        }
    }
    return xfail;
}

extern xsocket * xsocketmaskadd(xsocket * o, xuint32 mask)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xassertion(mask & (~xsocket_masks), "invalid socket mask");

        o->flags |= mask;
        if(xsocketalive(o))
        {
            switch(mask)
            {
                case xsocket_mask_nonblock: xassertion(xsocket_nonblock_on(o)!=xsuccess, "fail to nonblocking"); break;
            }
        }
    }
    return o;
}

extern xint32 xsocket_nonblock_on(xsocket * o)
{
    if(o)
    {
        o->flags |= xsocket_mask_nonblock;
        return xdescriptor_nonblock_on(xaddressof(o->descriptor));
    }
    return xfail;
}

extern xint32 xsocket_nonblock_off(xsocket * o)
{
    if(o)
    {
        o->flags &= (~xsocket_mask_nonblock);
        return xdescriptor_nonblock_off(xaddressof(o->descriptor));
    }
    return xfail;
}

extern xuint32 xsocketwait(xsocket * o, xuint32 mask, xuint64 unisecond)
{
    if(o)
    {
        return xdescriptorwait(xaddressof(o->descriptor), mask, unisecond);
    }
    return xfail;
}