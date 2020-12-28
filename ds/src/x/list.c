#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "log.h"
#include "list.h"

static inline void __xlistvalget(xval v){}

static inline xlistnode * __xlistnodenew(xval v)
{
    xlistnode * o = (xlistnode *) calloc(sizeof(xlistnode), 1);

    assertion(o == NULL, "o is null caused by calloc (%d)", errno);

    o->value = v;

    return o;
}

xlist * xlistnew()
{
    xlist * o = (xlist *) calloc(sizeof(xlist), 1);

    assertion(o == NULL, "o is null caused by fail to calloc (%d)", errno);

    o->type = xcontainer_type_list;

    return o;
}

xlist * xlistrem(xlist * o, xvalget f)
{
    if(o)
    {
        xlistclr(o, f);
        free(o);
    }
    return NULL;
}

int xlistpush(xlist * o, xval v)
{
    assertion(o == NULL, "o is null");

    xlistnode * node = __xlistnodenew(v);

    assertion(node == NULL, "node is null");

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

    return true;
}

int xlistpop(xlist * o, xvalget f)
{
    if(o && o->size > 0)
    {
        f = (f ? f : __xlistvalget);

        xlistnode * node = o->head;
        xval v = o->head->value;
        
        o->head = o->head->next;
        if(o->head)
        {
            o->head->prev = NULL;
        }
        else
        {
            o->tail = NULL;
        }
        free(node);

        o->size = o->size - 1;

        return true;
    }
    return false;
}

void xlistclr(xlist * o, xvalget f)
{
    assertion(o == NULL, "o is null");
    xlistnode * node;
    f = (f ? f : __xlistvalget);

    while(o->head)
    {
        node = o->head;
        f(o->head->value);

        o->head = o->head->next;
        if(o->head)
        {
            o->head->prev = NULL;
        }
        else
        {
            o->tail = NULL;
        }
        free(node);
        o->size = o->size - 1;
    }

    assertion(o->size != 0 || o->head != NULL || o->tail != NULL, "invalidate");
}
