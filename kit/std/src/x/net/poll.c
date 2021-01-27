#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "../net.h"

extern xpoll * xpollnew(void)
{
    xpoll * o = (xpoll *) calloc(sizeof(xpoll), 1);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = (xobj_mask_allocated | xobj_type_poll);
    o->destruct = xpollrem;

    return o;
}

extern void * xpollrem(void * p)
{
    xpoll * o = (xpoll *) p;
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xassertion(xobjtype(o) != xobj_type_poll, "invalid object");
        xsynclock(o->sync);

        while(o->head)
        {
            xdescriptor * node = o->head;
            if(node->next)
            {
                node->next->prev = xnil;
            }
            else
            {
                o->tail = xnil;
            }
            node->prev = xnil;
            node->next = xnil;
            node->parent = xnil;
            o->head = node->next;
            o->descriptors = o->descriptors - 1;
        }
        xsyncunlock(o->sync);
        // CHECKOUT ASSERTION LINKED LIST

        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }

    return o;
}