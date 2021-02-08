#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "descriptor.h"
#include "descriptorio.h"



extern xdescriptor * xdescriptorio_queue_head(xdescriptorio * io)
{
    xassertion(io == xnil, "io is null");

    return io->queue.head;
}

extern void xdescriptorio_queue_push(xdescriptorio * io, xdescriptor * descriptor)
{
    xassertion(io == xnil || descriptor == xnil, "io is null or descriptor is null");
    xassertion(descriptor->prev || descriptor->next, "descriptor is already registered");

    descriptor->prev = io->queue.tail;
    if(descriptor->prev)
    {
        descriptor->prev->next = descriptor;
    }
    else
    {
        xassertion(io->queue.head, "invalid queue (critical)");
        io->queue.head = descriptor;
    }
    io->queue.tail = descriptor;

    io->queue.total = io->queue.total + 1;
}

extern xdescriptor * xdescriptorio_queue_pop(xdescriptorio * io)
{
    xassertion(io == xnil, "io is null");

    xdescriptor * descriptor = io->queue.head;

    if(descriptor)
    {
        if(descriptor->next)
        {
            descriptor->next->prev = xnil;
        }
        else
        {
            io->queue.tail = xnil;
        }
        io->queue.head = descriptor->next;
        io->queue.total = io->queue.total - 1;

        xassertion(io->queue.total == xinvalid, "invalid queue status");

        descriptor->next = xnil;
        descriptor->prev = xnil;
    }
    return descriptor;
}

extern xdescriptor * xdescriptorio_queue_del(xdescriptorio * io, xdescriptor * descriptor)
{
    xassertion(io == xnil || descriptor == xnil, "io is null or descriptor is null");
    xassertion(io != descriptor->io, "descriptor's not register in this io");

    xdescriptor * prev = descriptor->prev;
    xdescriptor * next = descriptor->next;

    if(prev)
    {
        prev->next = next;
    }
    else
    {
        xassertion(io->queue.head != descriptor, "critical");
        io->queue.head = next;
    }

    if(next)
    {
        next->prev = prev;
    }
    else
    {
        xassertion(io->queue.tail != descriptor, "critical");
        io->queue.tail = prev;
    }

    io->queue.total  = io->queue.total - 1;
    xassertion(io->queue.total == xinvalid, "invalid (critical)");

    descriptor->next = xnil;
    descriptor->prev = xnil;

    return next;
}

extern void xdescriptorio_children_push(xdescriptorio * io, xdescriptor * descriptor)
{
    xassertion(io == xnil || descriptor == xnil, "io is null or descriptor is null");
    xassertion(descriptor->prev || descriptor->next, "descriptor is already registered");

    descriptor->prev = io->children.tail;
    if(descriptor->prev)
    {
        descriptor->prev->next = descriptor;
    }
    else
    {
        xassertion(io->children.head, "invalid queue (critical)");
        io->children.head = descriptor;
    }
    io->children.tail = descriptor;

    io->children.total = io->children.total + 1;
}

extern xdescriptor * xdescriptorio_children_del(xdescriptorio * io, xdescriptor * descriptor)
{
    xassertion(io == xnil || descriptor == xnil, "io is null or descriptor is null");
    xassertion(io != descriptor->io, "descriptor's not register in this io");

    xdescriptor * prev = descriptor->prev;
    xdescriptor * next = descriptor->next;

    if(prev)
    {
        prev->next = next;
    }
    else
    {
        xassertion(io->children.head != descriptor, "critical");
        io->children.head = next;
    }

    if(next)
    {
        next->prev = prev;
    }
    else
    {
        xassertion(io->children.tail != descriptor, "critical");
        io->children.tail = prev;
    }
    io->children.total = io->children.total - 1;

    descriptor->prev = xnil;
    descriptor->next = xnil;

    return next;
}

// extern xuint32 xdescriptorio_status(xdescriptorio * o)
// {
//     return o ? o->status : xdescriptorio_status_void;
// }

// extern void xdescriptorio_clear(xdescriptorio * o)
// {
//     xassertion(o == xnil, "descriptorio is null");

//     xdescriptor * descriptor = o->queue.head;
//     while(descriptor)
//     {
//         xdescriptor * prev = descriptor->prev;
//         xdescriptor * next = descriptor->next;
//         if(prev)
//         {
//             prev->next = next;
//         }
//         else
//         {
//             o->queue.head = next;
//         }
//         if(next)
//         {
//             next->prev = prev;
//         }
//         else
//         {
//             o->queue.tail = prev;
//         }
//         o->queue.total = o->queue.total - 1;
//         descriptor->prev = xnil;
//         descriptor->next = xnil;
//         descriptor->io = xnil;
//         descriptor = next;
//     }
//     descriptor = o->children.head;
//     while(descriptor)
//     {
//         xdescriptor * prev = descriptor->prev;
//         xdescriptor * next = descriptor->next;
//         if(prev)
//         {
//             prev->next = next;
//         }
//         else
//         {
//             o->children.head = next;
//         }
//         if(next)
//         {
//             next->prev = prev;
//         }
//         else
//         {
//             o->children.tail = prev;
//         }
//         o->children.total = o->children.total - 1;
//         descriptor->prev = xnil;
//         descriptor->next = xnil;
//         descriptor->io = xnil;
//         descriptor = next;
//     }
//     xassertion(o->children.head || o->children.tail || o->children.total, "criticial fail to clear");
//     xassertion(o->queue.head || o->queue.tail || o->queue.total, "criticial fail to clear");
// }
