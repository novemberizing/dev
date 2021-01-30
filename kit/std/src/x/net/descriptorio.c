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
    
    return (__xdescriptorio_epoll *) io;
}

extern void xdescriptoriocall(xdescriptorio * o)
{
    __xdescriptorio_epoll * io = (__xdescriptorio_epoll *) o;
    if(io)
    {
        if(io->fd < 0)
        {
            io->fd = epoll_create(4096);    // 4096 is just hint
        }
        if(io->fd >= 0)
        {
            int nfds = epoll_wait(io->fd, io->events, io->nfds, 1);
            if(nfds >= 0)
            {
                for(int i = 0; i < nfds; i++)
                {
                    if(io->events[i].events & (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP))
                    {
                        xdescriptor * descriptor = io->events[i].data.ptr;
                    }
                    else
                    {
                        // TODO: IMPLEMENT THIS
                        if(io->events[i].events & EPOLLOUT)
                        {
                            
                        }
                        if(io->events[i].events & EPOLLIN)
                        {

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
