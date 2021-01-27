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

extern xsession * xsessionnew(void)
{
    xsession * o = (xsession *) calloc(sizeof(xsession), 1);

    o->flags      = (xobj_mask_allocated | xobj_type_session);
    o->destruct   = xsessionrem;
    o->descriptor = xdescriptorinit();

    return o;
}

extern void * xsessionrem(void * p)
{
    xsession * o = (xsession *) p;
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xassertion(xobjtype(o) != xobj_type_session, "invalid object");

        if(xsocketalive(o))
        {
            xsocketclose(o);
        }
        // 로직에 문제가 없는지 확인해보자.
        // 살아 있는 상태에서만 등록되도록 하였기 때문에, 큰 문제가 없다.
        if(o->parent && o->parent->release)
        {
            o->parent->release(o);

            // xsynclock(o->parent->sync);
            // xsession * next = o->next;
            // xsession * prev = o->prev;
            // if(next)
            // {
            //     next->prev = prev;
            // }
            // else
            // {
            //     o->parent->tail = prev;
            // }
            // if(prev)
            // {
            //     prev->next = next;
            // }
            // else
            // {
            //     o->parent->head = next;
            // }
            // o->parent->alives = o->parent->alives - 1;
            // xsyncunlock(o->parent->sync);
        }

        o->addr = xfree(o->addr);
        o->addrlen = 0;
        o->domain = 0;

        o->parent = xnil;
        o->protocol = 0;
        o->status = 0;
        o->descriptor.sync = xobjrem(o->descriptor.sync);
    }
    return o;
}