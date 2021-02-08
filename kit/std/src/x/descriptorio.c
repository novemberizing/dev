#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "io.h"
#include "descriptor.h"

extern xuint32 xdescriptorio_status(xdescriptorio * o)
{
    return o ? o->status : xdescriptorio_status_void;
}

extern void xdescriptorio_clear(xdescriptorio * o)
{
    xassertion(o == xnil, "descriptorio is null");
    
    xdescriptor * descriptor = o->queue.head;
    while(descriptor)
    {
        xdescriptor * prev = descriptor->prev;
        xdescriptor * next = descriptor->next;
        if(prev)
        {
            prev->next = next;
        }
        else
        {
            o->queue.head = next;
        }
        if(next)
        {
            next->prev = prev;
        }
        else
        {
            o->queue.tail = prev;
        }
        o->queue.total = o->queue.total - 1;
        descriptor->prev = xnil;
        descriptor->next = xnil;
        descriptor->io = xnil;
        descriptor = next;
    }
    descriptor = o->children.head;
    while(descriptor)
    {
        xdescriptor * prev = descriptor->prev;
        xdescriptor * next = descriptor->next;
        if(prev)
        {
            prev->next = next;
        }
        else
        {
            o->children.head = next;
        }
        if(next)
        {
            next->prev = prev;
        }
        else
        {
            o->children.tail = prev;
        }
        o->children.total = o->children.total - 1;
        descriptor->prev = xnil;
        descriptor->next = xnil;
        descriptor->io = xnil;
        descriptor = next;
    }
    xassertion(o->children.head || o->children.tail || o->children.total, "criticial fail to clear");
    xassertion(o->queue.head || o->queue.tail || o->queue.total, "criticial fail to clear");
}
