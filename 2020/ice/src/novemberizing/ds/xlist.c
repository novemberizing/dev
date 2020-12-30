#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "xlist.h"

static xlistnode * __xlistnode_new(variant v)
{
    xlistnode * node = (xlistnode *) calloc(sizeof(xlistnode), 1);
    if(node == NULL)
    {
        fprintf(stdout, "fail to %s(%lu) caused by calloc (%d)\n", __func__, v.u64, errno);
        return NULL;
    }

    node->value = v;
    return node;
}

xlist * xlistnew(void)
{
    xlist * o = (xlist *) calloc(sizeof(xlist), 1);
    if(o == NULL)
    {
        fprintf(stdout, "fail to %s() caused by calloc (%d)\n", __func__, errno);
        return NULL;
    }

    o->type = xcontainer_type_list;

    return o;
}

xlist * xlistpush(xlist * o, variant v)
{
    if(o == NULL)
    {
        fprintf(stdout, "fail to %s(%p, %ld) caused by o is null\n", __func__, o, v.u64);
        return NULL;
    }

    xlistnode * node = __xlistnode_new(v);

    node->prev = o->tail;
    if(o->tail)
    {
        o->tail->next = node;
    }
    o->tail = node;
    if(o->head == NULL)
    {
        o->head = node;
    }
    o->size = o->size + 1;

    return o;
}

int xlistpop(xlist * o, void (*func)(variant))
{
    if(o)
    {
        if(o->head)
        {
            xlistnode * node = o->head;
            if(func)
            {
                func(o->head->value);
            }

            o->head = o->head->next;
            if(o->head)
            {
                o->head->prev = NULL;
            }
            else
            {
                o->tail = NULL;
            }
            o->size = o->size - 1;
            free(node);
        }
    }
    return fail;
}

xlist * xlistrem(xlist * o, void (*func)(variant))
{
    if(o)
    {
        xlistclr(o, func);
        free(o);
    }
    return NULL;
}

xlist * xlistclr(xlist * o, void (*func)(variant))
{
    if(o)
    {
        if(func)
        {
            while(o->head)
            {
                xlistnode * node = o->head;
                func(node->value);
                o->head = node->next;
                free(node);
                o->size = o->size - 1;
                if(o->head == NULL)
                {
                    o->tail = NULL;
                }
            }
        }
        else
        {
            while(o->head)
            {
                xlistnode * node = o->head;
                func(node->value);
                o->head = node->next;
                o->size = o->size - 1;
                if(o->head == NULL)
                {
                    o->tail = NULL;
                }
            }
        }
    }
    return o;
}