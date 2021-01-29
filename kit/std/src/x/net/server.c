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

extern xserver * xservernew(int domain, int type, int protocol, xeventobjon handler)
{
    xserver * o = (xserver *) calloc(sizeof(xserver), o);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags               = (xobj_mask_allocated | xobj_type_event_server);
    o->destruct            = xserverrem;
    o->on                  = handler;

    o->descriptor.handle.f = xinvalid;
    o->descriptor.parent   = o;
    o->descriptor.on       = __xclient_internal_descriptor_event_on;

    o->domain              = domain;
    o->type                = type;
    o->protocol            = protocol;

    return o;
}

extern void * xserverrem(void * p)
{
    xserver * o = (xserver *) p;

    if(o)
    {
        xassertion(xobjtype(o) != xobj_type_event_server, "invalid object");

        xsynclock(o->sync);
        xeventobj * parent = o->parent;
        if(parent)
        {
            xsynclock(parent->sync);
            xeventobj * prev = o->prev;
            xeventobj * next = o->next;
            if(prev)
            {
                prev->next = next;
            }
            else
            {
                parent->head = next;
            }
            if(next)
            {
                next->prev = prev;
            }
            else
            {
                parent->tail = prev;
            }
            parent->total = parent->total - 1;
            xsyncunlock(parent->sync);
            o->prev = xnil;
            o->next = xnil;
            o->parent = xnil;
        }
        if(xsocketalive(o))
        {
            xclientshutdown(o, xdescriptor_event_close);
        }
        o->addr = xfree(o->addr);
        o->addrlen = 0;
        // check need to clear children
        while(o->head)
        {
            xeventobj * next = o->head->next;
            // xsynclock(o->head->sync); 락이 필요 없는 이유는 ... 빠지지 않으니까 ?
            if(next)
            {
                next->prev = xnil;
            }
            else
            {
                o->tail = xnil;
            }
            o->total = o->total - 1;
            // xsyncunlock(o->head->sync);
            o->head = next;
        }
        xsyncunlock(o->sync);
        o->sync = xobjrem(o->sync);
        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}


// #include "../net.h"

// static socklen_t __xinternal_addrlen_get(int protocol)
// {
//     switch(protocol)
//     {
//         case AF_INET: return sizeof(struct sockaddr_in);
//     }
//     xassertion(xtrue, "not supported protocol");
// }

// extern xserver * xservernew(int domain, int type, int protocol)
// {
//     xserver * o = (xserver *) calloc(sizeof(xserver), 1);

//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     o->flags = (xobj_type_server | xobj_mask_allocated);
//     o->destruct = xserverrem;

//     o->descriptor = xdescriptorinit();

//     o->domain = domain;
//     o->type = type;
//     o->protocol = protocol;

//     o->backlog = SOMAXCONN;
//     o->factory = xsessionnew;
//     o->release = xsessionrem;

//     return o;
// }

// extern xuint32 xserverwait(xserver * o, xuint32 mask, xuint64 nanosecond)
// {
//     // TODO: IMPLEMENT THIS
// }
// extern xint32 xserverlisten(xserver * o, void * addr, xuint64 addrlen)
// {
//     xcheck(o == xnil, "");
//     if(o)
//     {
//         xcheck(xsocketalive(o), "socket is alive");
//         if(xsocketalive(o) == xfalse)
//         {
//             o->addr = xcopy(o->addr, addr, addrlen, o->addrlen < addrlen);
//             o->addrlen = addrlen;

//             int ret = xsocketopen((xsocket *) o);
//             if(ret == xsuccess)
//             {
//                 ret = bind(o->descriptor.value.f, (struct sockaddr *) o->addr, o->addrlen);
//                 if(ret == xsuccess)
//                 {
//                     ret = listen(o->descriptor.value.f, o->backlog);
//                     if(ret == xsuccess)
//                     {
//                         if(o->flags & xsocket_mask_nonblock)
//                         {
//                             ret = xdescriptor_nonblock_on(xaddressof(o->descriptor));
//                             xassertion(ret != xsuccess, "fail to nonblocking");
//                         }
//                         return xsuccess;
//                     }
//                     else
//                     {
//                         xsocketclose(o);
//                         xassertion(xtrue, "fail to socket listen (%d)", errno);
//                     }
//                 }
//                 else
//                 {
//                     xsocketclose(o);
//                     xassertion(xtrue, "fail to socket bind (%d)", errno);
//                 }
//             }
//             else
//             {
//                 xassertion(xtrue, "fail to socket open");
//             }
//         }
//     }
//     return xfail;
// }
// extern xint32 xserverrelisten(xserver * o)
// {
//     xcheck(o == xnil, "");
//     if(o)
//     {
//         xcheck(xsocketalive(o), "socket is alive");
//         if(xsocketalive(o) == xfalse)
//         {
//             int ret = xsocketopen((xsocket *) o);
//             if(ret == xsuccess)
//             {
//                 ret = bind(o->descriptor.value.f, (struct sockaddr *) o->addr, o->addrlen);
//                 if(ret == xsuccess)
//                 {
//                     ret = listen(o->descriptor.value.f, o->backlog);
//                     if(ret == xsuccess)
//                     {
//                         if(o->flags & xsocket_mask_nonblock)
//                         {
//                             ret = xdescriptor_nonblock_on(xaddressof(o->descriptor));
//                             xassertion(ret != xsuccess, "fail to nonblocking");
//                         }
//                         return xsuccess;
//                     }
//                     else
//                     {
//                         xsocketclose(o);
//                         xassertion(xtrue, "fail to socket listen (%d)", errno);
//                     }
//                 }
//                 else
//                 {
//                     xsocketclose(o);
//                     xassertion(xtrue, "fail to socket bind (%d)", errno);
//                 }
//             }
//             else
//             {
//                 xassertion(xtrue, "fail to socket open");
//             }
//         }
//     }
//     return xfail;
// }
// extern void * xserverrem(void * p)
// {
//     xserver * o = (xserver *) p;
//     xcheck(o == xnil, "null pointer");
//     if(o)
//     {
//         xsocketclose(o);

//         o->protocol = 0;
//         o->type = 0;
//         o->domain = 0;

//         o->addr = xfree(o->addr);
//         o->addrlen = 0;

//         if(xobjallocated(o))
//         {
//             free(o);
//             o = xnil;
//         }
//     }
//     return o;
// }

// extern xsession * xserveraccept(xserver * o)
// {
//     xcheck(o == xnil, "null pointer");
//     if(o)
//     {
//         xcheck(xsocketalive(o) == xfalse, "socket is not alive");
//         if(xsocketalive(o))
//         {
//             socklen_t addrlen = __xinternal_addrlen_get(o->protocol);
//             struct sockaddr * addr = (struct sockaddr *) calloc(addrlen, 1) ;
//             int fd = accept(o->descriptor.value.f, addr, &addrlen);
//             if(fd >= 0)
//             {
//                 xsession * session = o->factory();

//                 session->addr = addr;
//                 session->addrlen = addrlen;
//                 session->protocol = o->protocol;
//                 session->domain = o->domain;
//                 session->descriptor.value.f = fd;
//                 session->parent = o;
//                 session->status = xsession_status_link;
//                 session->type = o->type;

//                 xsynclock(o->descriptor.sync);
//                 session->prev = o->tail;
//                 if(session->prev)
//                 {
//                     session->prev->next = session;
//                 }
//                 else
//                 {
//                     o->head = session;
//                 }
//                 o->tail = session;
//                 o->alives = o->alives + 1;
//                 xsyncunlock(o->descriptor.sync);
//                 // TODO: EVENT HANDLING ... 
//                 return session;
//             }
//             else
//             {
//                 xcheck(xtrue, "fail to accept (%d)", errno);
//                 free(addr);
//             }
//         }
//     }
//     return xnil;
// }

// extern xsession * xserver_default_session_factory(void)
// {
//     xsession * o = xsessionnew();

//     return o;
// }