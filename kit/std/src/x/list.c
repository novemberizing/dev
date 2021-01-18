/**
 * @file    x/list.c
 * @brief   리스트 구현 소스입니다.
 * @details
 * 
 * @version 0.0.1
 */

#include <stdlib.h>
#include <stdio.h>

#include "std.h"

static xlistnode * __xlistnode_new(xval v)
{
    xlistnode * o = (xlistnode *) calloc(sizeof(xlistnode), 1);

    o->value = v;

    return o;
}

extern xlist * xlistnew(void)
{
    xlist * o = (xlist *) calloc(sizeof(xlist), 1);

    o->flags = xobj_mask_allocated | xobj_type_list;
    o->destruct = xlistrem;

    return o;
}

extern void * xlistrem(void * p)
{
    xlist * o = (xlist *) p;
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xassertion(xobjtype(o) != xobj_type_list, "invalid object");

        xcheck(o->size > 0, "check item is memory allocated item. need to call xlistclear(o, destructor)");

        xlistclear(o, xnil);
        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }

    return o;
}

extern void xlistclear(xlist * o, xvalcb cb)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        while(o->head)
        {
            xlistnode * node = o->head;
            if(cb)
            {
                cb(node->value);
            }
            free(node);
            o->head = node->next;
            o->size = o->size - 1;
        }
        xassertion(o->size > 0, "invalid implement");
        o->head = xnil;
        o->tail = xnil;
    }
}

extern void xlistpush(xlist * o, xval v)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xlistnode * node = __xlistnode_new(v);
        node->prev = o->tail;
        o->tail = node;
        if(node->prev)
        {
            node->prev->next = node;
        }
        else
        {
            o->head = node;
        }
        o->size = o->size + 1;
    }
}

extern void xlistpop(xlist * o, xvalcb cb)
{
    xcheck(o == xnil, "null pointer");
    if(o && o->size > 0)
    {
        xlistnode * node = o->head;
        o->head = node->next;
        if(o->head)
        {
            o->head->prev = xnil;
        }
        else
        {
            o->tail = xnil;
        }
        o->size = o->size - 1;
        if(cb)
        {
            cb(node->value);
        }
        free(node);
    }
}