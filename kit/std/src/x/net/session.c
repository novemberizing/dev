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

#include "../net.h"

extern xint64 xsessionsocketeventon(xsession * o, void * parent, xuint32 mask, const void * data, xval val)
{

}

extern xsession * xsessionnew(void)
{
    xsession * session = (xsession *) calloc(sizeof(xsession), 1);

    session->flags           = (xobj_mask_allocated);
    session->destruct        = xsessionrem;

    session->socket.handle.f = xinvalid;
    session->socket.on       = xsessionsocketeventon;

    return session;
}
extern void * xsessionrem(void * p)
{
    xsession * o = (xsession *) p;
    if(o)
    {
        xsynclock(o->sync);

        xassertion(o->parent, "xsession's parent already linked");
        xassertion(o->children.total > 0, "xsession's children exist");

        if(xclientalive(o))
        {
            xclientclose(o);
        }

        o->readbuf  = xobjrem(o->readbuf);
        o->writebuf = xobjrem(o->writebuf);

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


// static xint64 __xsession_internal_descriptor_event_on(xdescriptor * descriptor, xuint32 mask, void * p, xval data)
// {
//     xassertion(descriptor == xnil || p == xnil, "null pointer");
//     xsession * session = (xsession *) p;

//     xcheck(session->on == xnil && session->parent, "no event handler");

//     return session->on ? session->on((xeventobj *) p, mask, xnil, data) : xfail;
// }

// extern xsession * xsessionnew(void)
// {
//     xsession * o = (xsession *) calloc(sizeof(xsession), 1);
//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     if(o)
//     {
//         o->flags    = (xobj_mask_allocated | xobj_type_event_session);
//         o->destruct = xsessionrem;

//         o->descriptor.handle.f = xinvalid;
//         o->descriptor.parent   = o;
//         o->descriptor.on       = __xsession_internal_descriptor_event_on;
//     }

//     return o;
// }

// extern void * xsessionrem(void * p)
// {
//     xsession * o = (xsession *) p;

//     if(o)
//     {
//         xsynclock(o->sync);
//         xeventobj * parent = o->parent;
//         if(parent)
//         {
//             xsynclock(parent->sync);
//             xeventobj * prev = o->prev;
//             xeventobj * next = o->next;
//             if(prev)
//             {
//                 prev->next = next;
//             }
//             else
//             {
//                 parent->head = next;
//             }
//             if(next)
//             {
//                 next->prev = prev;
//             }
//             else
//             {
//                 parent->tail = prev;
//             }
//             parent->total = parent->total - 1;
//             xsyncunlock(parent->sync);
//             o->parent = xnil;
//             o->prev = xnil;
//             o->next = xnil;
//         }
//         if(xsocketalive(o))
//         {
//             xclientshutdown(o, xdescriptor_event_close);
//         }
//         o->readbuf = xobjrem(o->readbuf);
//         o->writebuf = xobjrem(o->writebuf);
//         // check need to clear children
//         while(o->head)
//         {
//             xeventobj * next = o->head->next;
//             xsynclock(o->head->sync);
//             if(next)
//             {
//                 next->prev = xnil;
//             }
//             else
//             {
//                 o->tail = xnil;
//             }
//             o->total = o->total - 1;
//             xsyncunlock(o->head->sync);
//             o->head = next;
//         }
//         xsyncunlock(o->sync);
//         o->sync = xobjrem(o->sync);

//         if(xobjallocated(o))
//         {
//             free(o);
//             o = xnil;
//         }
//     }

//     return o;
// }


// // extern xsession * xsessionnew(void)
// // {
// //     xsession * o = (xsession *) calloc(sizeof(xsession), 1);


// //     o->flags      = (xobj_mask_allocated | xobj_type_session);
// //     o->destruct   = xsessionrem;
// //     o->descriptor = xdescriptorinit();

// //     return o;
// // }

// // extern void * xsessionrem(void * p)
// // {
// //     xsession * o = (xsession *) p;
// //     xcheck(o == xnil, "null pointer");

// //     if(o)
// //     {
// //         xassertion(xobjtype(o) != xobj_type_session, "invalid object");

// //         if(xsocketalive(o))
// //         {
// //             xsocketclose(o);
// //         }
// //         // 로직에 문제가 없는지 확인해보자.
// //         // 살아 있는 상태에서만 등록되도록 하였기 때문에, 큰 문제가 없다.
// //         if(o->parent && o->parent->release)
// //         {
// //             o->parent->release(o);

// //             // xsynclock(o->parent->sync);
// //             // xsession * next = o->next;
// //             // xsession * prev = o->prev;
// //             // if(next)
// //             // {
// //             //     next->prev = prev;
// //             // }
// //             // else
// //             // {
// //             //     o->parent->tail = prev;
// //             // }
// //             // if(prev)
// //             // {
// //             //     prev->next = next;
// //             // }
// //             // else
// //             // {
// //             //     o->parent->head = next;
// //             // }
// //             // o->parent->alives = o->parent->alives - 1;
// //             // xsyncunlock(o->parent->sync);
// //         }

// //         o->addr = xfree(o->addr);
// //         o->addrlen = 0;
// //         o->domain = 0;

// //         o->parent = xnil;
// //         o->protocol = 0;
// //         o->status = 0;
// //         o->descriptor.sync = xobjrem(o->descriptor.sync);
// //     }
// //     return o;
// // }