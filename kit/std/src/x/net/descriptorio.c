#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <poll.h>
#include <sys/epoll.h>

#include "../net.h"

struct __xdescriptorio_epoll;

typedef struct __xdescriptorio_epoll __xdescriptorio_epoll;

struct __xdescriptorio_epoll
{
    xsync *             sync;

    xdescriptor *       head;
    xdescriptor *       tail;
    xuint64             total;

    int                  fd;

    int                  nfds;
    struct epoll_event * events;
};

extern xdescriptorio * xdescriptorionew(void)
{
    __xdescriptorio_epoll * io = (__xdescriptorio_epoll *) calloc(sizeof(__xdescriptorio_epoll), 1);

    io->fd     = xinvalid;

    /**
     * 기본적으로 4096 정도를 기다리도록 하자.
     * 만약에 이 값을 늘리면 어떻게 될 것인가...?
     */
    io->nfds   = 4096;
    io->events = (struct epoll_event *) malloc(sizeof(struct epoll_event) * 4096);
    
    return (xdescriptorio *) io;
}

extern void * xdescriptoriorem(void * p)
{
    __xdescriptorio_epoll * io = (__xdescriptorio_epoll *) p;

    if(io)
    {
        if(io->fd >= 0)
        {
            close(io->fd);
            io->fd = xinvalid;
        }
        while(io->head)
        {
            xdescriptor * node = io->head;
            io->head = node->next;
            if(node->next)
            {
                node->next->prev = xnil;
            }
            else
            {
                io->tail = xnil;
            }
            io->total = io->total - 1;
            io->head = node->next;
            node->io = xnil;
            node->prev = xnil;
            node->next = xnil;
        }

        io->events = xfree(io->events);
        io->nfds = 0;

        free(io);
        io = xnil;
    }
    return io;
}

extern void xdescriptoriocall(xdescriptorio * o)
{
    __xdescriptorio_epoll * io = (__xdescriptorio_epoll *) o;
    if(io)
    {
        if(io->fd < 0)
        {
            io->fd = epoll_create(4096);    // 4096 is just hint
            printf("todo: reinitialize all descriptor\n");
            xdescriptor * descriptor = o->head;
            if(descriptor->handle.f >= 0)
            {
                xdescriptorioreg(o, descriptor);
            }
        }
        if(io->fd >= 0)
        {
            int nfds = epoll_wait(io->fd, io->events, io->nfds, 1);
            if(nfds >= 0)
            {
                for(int i = 0; i < nfds; i++)
                {
                    xdescriptor * descriptor = io->events[i].data.ptr;
                    if(io->events[i].events & (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP))
                    {
                        descriptor->status |= xdescriptor_status_exception;
                        int ret = epoll_ctl(io->fd, (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLIN | EPOLLOUT),descriptor->handle.f, xnil);
                        xcheck(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
                        
                        xdescriptor * prev = descriptor->prev;
                        xdescriptor * next = descriptor->next;

                        if(prev)
                        {
                            prev->next = next;
                        }
                        else
                        {
                            io->head = next;
                        }
                        if(next)
                        {
                            next->prev = prev;
                        }
                        else
                        {
                            io->tail = prev;
                        }

                        io->total = io->total - 1;

                        xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_event_exception, xnil, xvalgen(0));
                    }
                    else
                    {
                        xuint32 mask = xdescriptor_mask_void;

                        if(io->events[i].events & EPOLLOUT)
                        {
                            mask |= xdescriptor_status_out;
                            xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_status_out, xnil, xvalgen(0));
                        }

                        if(io->events[i].events & EPOLLIN)
                        {
                            printf("in event on\n");
                            mask |= xdescriptor_status_in;
                            xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_status_in, xnil, xvalgen(0));
                        }
                    }
                }
            }
            else
            {
                xcheck(xtrue, "fail to epoll wait (%d)", errno);
            }
        }
        else
        {
            xcheck(xtrue, "fail to epoll_create (%d)", errno);
        }
    }
    else
    {
        xcheck(xtrue, "io is null");
    }
}

extern void xdescriptorioadd(xdescriptorio * io, xdescriptor * descriptor)
{
    if(io)
    {
        if(descriptor)
        {
            if(descriptor->io == xnil && descriptor->prev == xnil || descriptor->next == xnil)
            {
                descriptor->io = io;
                io->total = io->total + 1;
            }
            else
            {
                if(descriptor->io == io)
                {
                    xcheck(xtrue, "descriptor is already linked");
                }
                else
                {
                    xassertion(xtrue, "descriptor is already linked in the other descriptorio");
                }
            }
        }
        else
        {
            xcheck(xtrue, "descriptor is null");
        }
    }
    else
    {
        xcheck(xtrue, "descriptorio is null");
    }
}

extern void xdescriptoriodel(xdescriptorio * o, xdescriptor * descriptor)
{
    if(o)
    {
        if(descriptor)
        {
            xdescriptor * prev = descriptor->prev;
            xdescriptor * next = descriptor->next;

            if(prev)
            {
                prev->next = next;
            }
            else
            {
                o->head = next;
            }

            if(next)
            {
                next->prev = prev;
            }
            else
            {
                o->tail = prev;
            }

            o->total = o->total - 1;
        }
        else
        {
            xcheck(xtrue, "descriptor is null");
        }
    }
    else
    {
        xcheck(xtrue, "descriptorio is null");
    }
}

extern void xdescriptorioreg(xdescriptorio * o, xdescriptor * descriptor)
{
    if(descriptor && o)
    {
        if(descriptor->io == xnil)
        {
            descriptor->io = o;

            descriptor->prev = o->tail;
            if(descriptor->prev)
            {
                descriptor->prev->next = descriptor;
            }
            else
            {
                o->head = descriptor;
            }
            o->tail = descriptor;
            o->total = o->total + 1;
        }
        xcheck(descriptor->io != o, "descriptor's io is not same");
        if(descriptor->handle.f < 0)
        {
            xdescriptoropen(descriptor);
        }
        if(descriptor->handle.f >= 0)
        {
            __xdescriptorio_epoll * io = (__xdescriptorio_epoll *) o;
            if(io->fd >= 0)
            {
                struct epoll_event event;
                event.data.ptr = descriptor;
                event.events = (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);

                if((descriptor->status & xdescriptor_event_in) == xdescriptor_event_void)
                {
                    event.events |= EPOLLIN;
                }

                if((descriptor->status & xdescriptor_event_out) == xdescriptor_event_void)
                {
                    event.events |= EPOLLOUT;
                }

                int ret = epoll_ctl(io->fd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                if(ret != xsuccess)
                {
                    int err = errno;
                    if(err == EEXIST)
                    {
                        ret = epoll_ctl(io->fd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
                        if(ret != xsuccess)
                        {
                            err = errno;
                            xcheck(xtrue, "fail to reg (epoll_ctl ...) (%d)", err);
                        }
                    }
                    else
                    {
                        xcheck(xtrue, "fail to reg (epoll_ctl ...) (%d)", err);
                    }
                }
            }
        }
        else
        {
            xcheck(xtrue, "descriptor handle is not alive (will be retried)");
        }
    }
    else
    {
        xcheck(xtrue, "descriptor or io is null");
    }
}

extern void xdescriptoriounreg(xdescriptorio * o, xdescriptor * descriptor)
{
    __xdescriptorio_epoll * io = (__xdescriptorio_epoll *) o;
    if(io && descriptor)
    {
        if(io->fd >= 0)
        {
            int ret = epoll_ctl(io->fd, (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLIN | EPOLLOUT),descriptor->handle.f, xnil);

            xcheck(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
        }
        
        xdescriptor * prev = descriptor->prev;
        xdescriptor * next = descriptor->next;

        if(prev)
        {
            prev->next = next;
        }
        else
        {
            io->head = next;
        }
        if(next)
        {
            next->prev = prev;
        }
        else
        {
            io->tail = next;
        }

        io->total = io->total - 1;
    }
    else
    {
        xcheck(io != xnil, "null pointer");
    }
}