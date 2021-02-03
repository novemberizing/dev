#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "descriptor.h"
#include "descriptorio-epoll.h"

static inline xint32 xdescriptorio_epoll_reg(xdescriptorio_epoll * io, xdescriptor * descriptor)
{
    if(io && descriptor)
    {
        if(io->fd >= 0)
        {
            if(descriptor->handle.f >= 0)
            {
                struct epoll_event event;

                event.data.ptr = descriptor;
                event.events   = (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);

                if((descriptor->status & xdescriptor_status_in) == xdescriptor_status_void)
                {
                    event.events |= EPOLLIN;
                }

                if((descriptor->status & xdescriptor_status_out) == xdescriptor_status_void)
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
                            xassertion(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
                            return xfail;
                        }
                    }
                    else
                    {
                        xassertion(ret != xsuccess && ret != EEXIST, "fail to epoll_ctl (%d)", err);
                        return xfail;
                    }
                }

                return xsuccess;
            }
            else
            {
                xassertion(descriptor->handle.f < 0, "descriptor is not alive");
            }
        }
        else
        {
            xassertion(io->fd < 0, "io is not open");
        }
    }
    else
    {
        xassertion(io == xnil || descriptor == xnil, "io is null or descriptor is null");

        return xfail;
    }
}

static inline void xdescriptorio_epoll_unreg(xdescriptorio_epoll * io, xdescriptor * descriptor)
{
    if(io && descriptor)
    {
        if(io->fd >= 0)
        {
            if(descriptor->handle.f >= 0)
            {
                int ret = epoll_ctl(io->fd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);

                if(ret != xsuccess)
                {
                    xassertion(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
                }
            }
        }
    }
}

static inline void xdescriptorio_epoll_descriptor_open(xdescriptorio_epoll * io)
{
    xassertion(io == xnil || io->fd < 0, "descriptorio is null or not open");
    xuint32 total = io->queue.total;
    xdescriptor * descriptor = io->queue.head;
    for(xuint32 i = 0; i < total && descriptor; i++)
    {
        xassertion(descriptor->open == xnil, "descriptor passive open");
        if(descriptor->open(descriptor) == xsuccess)
        {
            if(xdescriptorio_epoll_reg(io, descriptor) == xsuccess)
            {
                xdescriptor * prev = descriptor->prev;
                xdescriptor * next = descriptor->next;
                if(prev)
                {
                    prev->next = next;
                }
                else
                {
                    io->queue.head = next;
                }
                if(next)
                {
                    next->prev = prev;
                }
                else
                {
                    io->queue.tail = prev;
                }
                io->queue.total = io->queue.total - 1;

                descriptor->prev = io->children.tail;
                descriptor->next = xnil;
                if(descriptor->prev)
                {
                    descriptor->prev->next = descriptor;
                }
                else
                {
                    io->children.head = descriptor;
                }
                io->children.tail = descriptor;
                io->children.total = io->children.total + 1;
                continue;
            }
            else
            {
                xdescriptor_close(descriptor);
            }
        }
        descriptor = descriptor->next;
    }
}

static inline xint32 xdescriptorio_epoll_open(xdescriptorio_epoll * io)
{
    if(io)
    {
        if(io->fd < 0)
        {
            io->fd = epoll_create(io->nfds);
            if(io->fd >= 0)
            {
                xdescriptor * descriptor = io->children.head;
                while(descriptor)
                {
                    if(descriptor->handle.f >= 0)
                    {
                        struct epoll_event event;
                        event.data.ptr = descriptor;
                        event.events   = (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);
                        if((descriptor->status & xdescriptor_status_in) == xdescriptor_status_void)
                        {
                            event.events |= EPOLLIN;
                        }
                        if((descriptor->status & xdescriptor_status_out) == xdescriptor_status_void)
                        {
                            event.events |= EPOLLOUT;
                        }
                        int ret = epoll_ctl(io->fd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                        if(ret == xsuccess)
                        {
                            descriptor = descriptor->next;
                        }
                        else
                        {
                            xassertion(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
                        }
                    }
                    else
                    {
                        xassertion(descriptor->handle.f < 0, "descriptor's handle is invalid");
                    }
                }
                return xsuccess;
            }
            return xfail;
        }
        return xsuccess;
    }
    else
    {
        xcheck(io == xnil, "io is null");
    }
    return xfail;
}

static inline void xdescriptorio_epoll_descriptor_close(xdescriptorio_epoll * io, xdescriptor * descriptor)
{
    xdescriptorio_epoll_unreg(io, descriptor);

    xdescriptor * prev = descriptor->prev;
    xdescriptor * next = descriptor->next;

    if(prev)
    {
        prev->next = next;
    }
    else
    {
        io->children.head = next;
    }

    if(next)
    {
        next->prev = prev;
    }
    else
    {
        io->children.tail = prev;
    }

    descriptor->prev = xnil;
    descriptor->next = xnil;
    descriptor->io   = xnil;

    io->children.total = io->children.total - 1;

    if(descriptor->open)
    {
        descriptor->io   = (xdescriptorio *) io;
        descriptor->prev = io->queue.tail;

        if(descriptor->prev)
        {
            descriptor->prev->next = descriptor;
        }
        else
        {
            io->queue.head = descriptor;
        }

        io->queue.tail   = descriptor;
        io->queue.total  = io->queue.total + 1;
    }

    xdescriptor_close(descriptor);
}

static inline void xdescriptorio_epoll_on(xdescriptorio_epoll * io, xdescriptor * descriptor, xuint32 mask)
{
    xassertion(io == xnil || descriptor == xnil, "io is null or descriptor is null");
    // 만약에 프로세서가 여러개 존재하면 READ, WRITE & CLOSE 를 다른 곳에서 수행하자.
    if(mask & xdescriptor_event_exception)
    {
        xdescriptorio_epoll_descriptor_close(io, descriptor);
    }
    else
    {
        if(mask & xdescriptor_event_out)
        {
            // 어떻게 구현해야할까?
        }

        if(mask & xdescriptor_event_in)
        {
            // 어떻게 구현해야할까? 궁극적으로는 DESCRIPTOR'S
        }
    }
}

extern xdescriptorio * xdescriptorio_epoll_new(void)
{
    xdescriptorio_epoll * io = (xdescriptorio_epoll *) calloc(sizeof(xdescriptorio_epoll), 1);

    /**
     * EPOLL 최신 커널 소스를 분석해서,
     * 1024 혹은 괜찮은 값을 찾자.
     */
    io->fd      = xinvalid;
    io->nfds    = 1024;
    io->events  = (struct epoll_event *) malloc(sizeof(struct epoll_event) * io->nfds);
    io->timeout = 1;

    xassertion(io->events == xnil, "fail to malloc (%d)", errno);

    return (xdescriptorio *) io;
}

extern xdescriptorio * xdescriptorio_epoll_rem(xdescriptorio * address)
{
    xdescriptorio_epoll * io = (xdescriptorio_epoll *) address;
    if(io)
    {
        xassertion(io->children.head || io->children.tail || io->children.total, "io's children is exist");
        xassertion(io->queue.head || io->queue.tail || io->queue.total, "io's queue is exist");

        /**
         * 여기에서 닫기를 수행하는 이유는
         * 이것은 다른 객체에서 관리되지 않는 객체이며, 다시 오픈하거나 하는 로직이 없기 때문이다.
         */
        if(io->fd >= 0)
        {
            int ret = close(io->fd);
            xassertion(ret != xsuccess, "fail to close (%d)", errno);
        }

        io->events = xfree(io->events);
    }
    else
    {
        xcheck(io == xnil, "io is null");
    }

    return (xdescriptorio *) io;
}

extern void xdescriptorio_epoll_call(xdescriptorio * address)
{
    xdescriptorio_epoll * io = (xdescriptorio_epoll *) address;
    if(io)
    {
        if(xdescriptorio_epoll_open(io) == xsuccess)
        {
            xdescriptorio_epoll_descriptor_open(io);
            int nfds = epoll_wait(io->fd, io->events, io->nfds, io->timeout);
            if(nfds >= 0)
            {
                for(int i = 0; i < nfds; i++)
                {
                    xdescriptor * descriptor = (xdescriptor *) io->events[i].data.ptr;
                    xassertion(descriptor == xnil, "descriptor is null");

                    if(io->events[i].events & (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP))
                    {
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptorio_epoll_on(io, descriptor, xdescriptor_event_exception);
                    }
                    else
                    {
                        if(io->events[i].events & EPOLLOUT)
                        {
                            descriptor->status |= xdescriptor_status_out;
                            xdescriptorio_epoll_on(io, descriptor, xdescriptor_event_out);
                        }
                        if(io->events[i].events & EPOLLIN)
                        {
                            descriptor->status |= xdescriptor_status_in;
                            xdescriptorio_epoll_on(io, descriptor, xdescriptor_event_in);
                        }
                    }
                }
            }
            else
            {
                int err = errno;
                if(err != EINTR)
                {
                    xassertion(nfds < 0, "fail to epoll_wait (%d)", err);
                    close(io->fd);
                    io->fd = xinvalid;
                }
            }
        }
    }
    else
    {
        xcheck(io == xnil, "io is null");
    }
}
