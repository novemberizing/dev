#include "list.h"

#include "../subscription.h"
#include "../subscription/list.h"

extern xdescriptoreventgeneratorsubscriptionlist * xdescriptoreventgeneratorsubscriptionlist_new(void)
{
    return (xdescriptoreventgeneratorsubscriptionlist *) calloc(sizeof(xdescriptoreventgeneratorsubscriptionlist), 1);
}

extern xdescriptoreventgeneratorsubscriptionlist * xdescriptoreventgeneratorsubscriptionlist_rem(xdescriptoreventgeneratorsubscriptionlist * list)
{
    xassertion(list == xnil || list->size > 0, "");

    list->sync = xsyncrem(list->sync);
    free(list);
    
    return xnil;
}

extern void xdescriptoreventgeneratorsubscriptionlist_push(xdescriptoreventgeneratorsubscriptionlist * list, xdescriptoreventsubscription * subscription)
{
    xassertion(list == xnil || subscription == xnil || subscription->generatornode.generator == xnil, "");
    xassertion(subscription->generatornode.list || subscription->generatornode.prev || subscription->generatornode.next, "");

    subscription->generatornode.prev = list->tail;
    if(subscription->generatornode.prev)
    {
        subscription->generatornode.prev->generatornode.next = subscription;
    }
    else
    {
        list->head = subscription;
    }
    list->tail = subscription;
    list->size = list->size + 1;
}

extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptionlist_del(xdescriptoreventsubscription * subscription)
{
    xassertion(subscription == xnil || subscription->generatornode.generator == xnil || subscription->generatornode.list == xnil, "");

    xdescriptoreventsubscription *              prev = subscription->generatornode.prev;
    xdescriptoreventsubscription *              next = subscription->generatornode.next;
    xdescriptoreventgeneratorsubscriptionlist * list = subscription->generatornode.list;

    if(prev)
    {
        prev->generatornode.next = next;
        subscription->generatornode.prev = xnil;
    }
    else
    {
        list->head = next;
    }
    if(next)
    {
        next->generatornode.prev = prev;
        subscription->generatornode.next = xnil;
    }
    else
    {
        list->tail = prev;
    }
    list->size = list->size - 1;
    subscription->generatornode.list = xnil;

    return next;
}

extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptionlist_pop(xdescriptoreventgeneratorsubscriptionlist * list)
{
    xassertion(list == xnil, "");
    xdescriptoreventsubscription * subscription = list->head;
    if(subscription)
    {
        list->head = subscription->generatornode.next;
        if(list->head)
        {
            list->head->generatornode.prev = xnil;
            subscription->generatornode.next = xnil;
        }
        else
        {
            list->tail = xnil;
        }
        list->size = list->size - 1;
    }
    return subscription;
}