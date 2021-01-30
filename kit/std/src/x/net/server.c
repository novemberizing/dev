#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../net.h"

extern xint64 xserversocketeventon(xserver * o, void * parent, xuint32 mask, const void * data, xval val)
{

}

extern int xdefaultserverbacklog(void)
{
    return SOMAXCONN;
}

extern xeventobj * xdefaultsessionfactory(xeventobj * o)
{
    if(o)
    {
        xeventobj * session = (xeventobj *) xsessionnew();
        session->parent = o;
        session->prev = o->children.tail;
        if(session->prev)
        {
            session->prev->next = session;
        }
        else
        {
            o->children.head = session;
        }
        o->children.tail = session;
        o->children.total = o->children.total + 1;

        return session;
    }
    else
    {
        xassertion(o == xnil, "object is null");
    }
    return xnil;
}

extern void xdefaultsessionreleaser(xeventobj * o, xeventobj * child)
{
    if(child)
    {
        if(child->parent)
        {
            xeventobj * prev = child->prev;
            xeventobj * next = child->next;
            if(prev)
            {
                prev->next = next;
            }
            else
            {
                child->parent->children.head = next;
            }
            if(next)
            {
                next->prev = prev;
            }
            else
            {
                child->parent->children.tail = prev;
            }
            child->parent->children.total = child->parent->children.total - 1;
            child->prev = xnil;
            child->next = xnil;
            child->parent = xnil;
        }
        xobjrem(child);
    }
    else
    {
        xassertion(child == xnil, "child is null");
    }
}

extern xserver * xservernew(int domain, int type, int protocol, void * addr, xuint64 addrlen)
{
    xserver * server = (xserver *) calloc(sizeof(xserver), 1);

    server->flags           = (xobj_mask_allocated);
    server->destruct        = xserverrem;

    server->socket.handle.f = xinvalid;
    server->socket.on       = xserversocketeventon;

    server->socket.domain   = domain;
    server->socket.type     = type;
    server->socket.protocol = protocol;

    server->addr            = xdup(addr, addrlen);
    server->addrlen         = addrlen;

    server->create          = xdefaultsessionfactory;
    server->release         = xdefaultsessionreleaser;

    server->backlog         = SOMAXCONN;

    return server;
}

extern void * xserverrem(void * p)
{
    xserver * o = (xserver *) p;
    if(o)
    {
        xsynclock(o->sync);

        xassertion(o->parent, "server's parent already linked");
        xassertion(o->children.total > 0, "server's children exist");

        if(xserveralive(o))
        {
            xserverclose(o);
        }

        o->addr     = xfree(o->addr);
        o->addrlen  = 0;

        xsyncunlock(o->sync);

        o->sync     = xobjrem(o->sync);

        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}

extern xint32 xserverclose(xserver * server)
{
    if(server)
    {
        int ret = xdescriptorclose((xdescriptor *) xaddressof(server->socket));
        if(ret == xsuccess)
        {
            if(server->parent)
            {
                server->parent->release(server->parent, (xeventobj *) server);
            }
            return xsuccess;
        }
        else
        {
            xcheck(xtrue, "fail to xdescriptorclose");
            return xfail;
        }
    }
    else
    {
        xcheck(xtrue, "server is null");
    }

    return xsuccess;
}

extern xint32 xserverbind(xserver * server, void * addr, xuint64 addrlen)
{
    if(server)
    {
        if(addr && addrlen)
        {
            server->addr    = xcopy(server->addr, addr, addrlen, server->addrlen != addrlen);
            server->addrlen = addrlen;
        }
        int ret = xsocketbind((xsocket *) xaddressof(server->socket), server->addr, server->addrlen);
        if(ret == xsuccess)
        {
            return xsuccess;
        }
        xcheck(xtrue, "fail to xsocketbind");
        xserverclose(server);
        return xfail;
    }
    else
    {
        xcheck(xtrue, "server is null");
    }
    return xfail;
}

extern xint32 xserverlisten(xserver * server, void * addr, xuint64 addrlen)
{
    if(server)
    {
        int ret = xserverbind(server, addr, addrlen);
        if(ret == xsuccess)
        {
            ret = listen(server->socket.handle.f, server->backlog);
            if(ret == xsuccess)
            {
                server->socket.status |= xdescriptor_status_listen;
                xservereventpub(xaddressof(server->socket), server, xdescriptor_event_listen, xnil, xvalgen(0));
                return xsuccess;
            }
            xcheck(xtrue, "fail to listen (%d)", errno);
            xserverclose(server);
            return xfail;
        }
        xcheck(xtrue, "fail to xserverbind");
        xserverclose(server);
        return xfail;
    }
    else
    {
        xcheck(xtrue, "server is null");
    }
    return xfail;
}