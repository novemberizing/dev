#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>

#include "io.h"
#include "std.h"
#include "descriptor.h"

struct xdescriptorio_epoll
{
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;
    } children;
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;
    } queue;

    int fd;
    struct epoll_event * events;
    int maxevents;
    int timeout;
};

typedef struct xdescriptorio_epoll xdescriptorio_epoll;

extern xdescriptorio * xdescriptorio_new(void)
{
    xdescriptorio_epoll * io = (xdescriptorio_epoll *) calloc(sizeof(xdescriptorio_epoll), 1);

    xassertion(io == xnil, "fail to calloc (%d)", errno);

    io->fd        = xinvalid;
    io->maxevents = 1024;   // check this constant
    io->events    = malloc(sizeof(struct epoll_event) * io->maxevents);
    xassertion(io->events == xnil, "fail to malloc (%d)", errno);
    io->timeout   = 1;      // check this timeout

    return (xdescriptorio *) io;
}

extern xdescriptorio * xdescriptorio_rem(xdescriptorio * o)
{
    xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

    if(io)
    {
        if(io->fd >= 0)
        {
            close(io->fd);
        }

        io->events = xfree(io->events);

        free(io);
        io = xnil;
    }

    return (xdescriptorio *) io;
}

extern xint32 xdescriptorio_reg(xdescriptorio * o, xdescriptor * descriptor)
{
    xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

    xassertion(io == xnil, "descriptor event generator is null");

    if(descriptor)
    {
        if(descriptor->io == xnil)
        {
            descriptor->io = o;
            if(descriptor->handle.f < 0)
            {
                descriptor->prev = o->queue.tail;
                if(descriptor->prev)
                {
                    descriptor->prev->next = descriptor;
                }
                else
                {
                    o->queue.head = descriptor;
                }
                o->queue.tail = descriptor;
                o->queue.total = o->queue.total + 1;
            }
            else
            {
                xassertion(descriptor->status & xdescriptor_status_exception, "critical - maybe bug");

                descriptor->prev = o->children.tail;
                if(descriptor->prev)
                {
                    descriptor->prev->next = descriptor;
                }
                else
                {
                    o->children.head = descriptor;
                }
                o->children.tail = descriptor;
                o->children.total = o->children.total + 1;

                if(io->fd >= 0)
                {
                    struct epoll_event event;
                    event.data.ptr = descriptor;
                    event.events = (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);
                    if((descriptor->status & xdescriptor_status_in) == xdescriptor_status_void)
                    {
                        event.events |= EPOLLIN;
                    }
                    if((descriptor->status & xdescriptor_status_out) == xdescriptor_status_void)
                    {
                        event.events |= EPOLLOUT;
                    }
                    if((descriptor->status & xdescriptor_status_connect) == xdescriptor_status_void)
                    {
                        if(descriptor->status & xdescriptor_status_connecting)
                        {
                            event.events |= EPOLLOUT;
                        }
                        else
                        {
                            xassertion(xtrue, "critical - maybe bug");
                        }
                    }
                    int ret = epoll_ctl(io->fd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                    if(ret != xsuccess)
                    {
                        int err = errno;
                        xcheck(xtrue, "it's may be bug (%d)", err);
                        if(err == EEXIST)
                        {
                            ret = epoll_ctl(io->fd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
                            if(ret != xsuccess)
                            {
                                xcheck(xtrue, "fail to epoll_ctl (%d)", errno);
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
                                    o->children.tail = next;
                                }
                                descriptor->prev = xnil;
                                descriptor->next = xnil;
                                descriptor->io   = xnil;
                                o->children.total = o->children.total - 1;
                                descriptor->status |= xdescriptor_status_exception;
                                xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                                return xfail;
                            }
                            else
                            {
                                return xsuccess;
                            }
                        }
                        else
                        {
                            switch(err)
                            {
                                case EBADF:     xcheck(err == EBADF, "epfd or fd is not a valid file descriptor. (%d)", err); break;
                                case EINVAL:    xcheck(err == EINVAL, "epfd is not an epoll file descriptor, or fd is the same as epfd, or the requested operation op is not supported by this interface. (%d)", err); break;
                                case ELOOP:     xcheck(err == ELOOP, "fd refers to an epoll instance and this EPOLL_CTL_ADD operation would result in a circular loop of epoll instances monitoring one another. (%d)", err); break;
                                case ENOENT:    xcheck(err == ENOENT, "op was EPOLL_CTL_MOD or EPOLL_CTL_DEL, and fd is not registered with this epoll instance. (%d)", err); break;
                                case ENOMEM:    xcheck(err == ENOMEM, "There was insufficient memory to handle the requested op control operation. (%d)", err); break;
                                case ENOSPC:    xcheck(err == ENOSPC, "The limit imposed by /proc/sys/fs/epoll/max_user_watches was encountered while trying to register (EPOLL_CTL_ADD) a new file descriptor on an epoll instance. (%d)", err); break;
                                case EPERM:     xcheck(err == EPERM, "The target file fd does not support epoll. This error can occur if fd refers to, for example, a regular file or a directory. (%d)", err); break;
                                default:        xcheck(err, "Undocumented error (%d)", err); break;
                            }
                        }
                    }
                    else
                    {
                        return xsuccess;
                    }
                }
            }
        }
        else if(descriptor->io == io)
        {
            xcheck(descriptor->io == io, "already registered");
            return xsuccess;
        }
        else
        {
            xassertion(descriptor->io != io, "already registered and descriptor's generators are not same");
        }
    }
    else
    {
        xcheck(descriptor == xnil, "descriptor is null");
    }
    return xfail;
}

extern xint32 xdescriptorio_unreg(xdescriptorio * o, xdescriptor * descriptor)
{
    xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

    xassertion(io == xnil, "descriptor event generator is null");

    if(descriptor)
    {
        if(descriptor->io == o)
        {
            xdescriptor * prev = descriptor->prev;
            xdescriptor * next = descriptor->next;

            if(prev)
            {
                prev->next = next;
            }
            else
            {
                if(descriptor->handle.f >= 0)
                {
                    o->children.head = next;
                }
                else
                {
                    o->queue.head = next;
                }
            }

            if(next)
            {
                next->prev = prev;
            }
            else
            {
                if(descriptor->handle.f >= 0)
                {
                    o->children.tail = prev;
                }
                else
                {
                    o->queue.tail = prev;
                }
            }

            if(descriptor->handle.f >= 0)
            {
                o->children.total = o->children.total - 1;
                if(io->fd >= 0)
                {
                    int ret = epoll_ctl(io->fd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);
                    xcheck(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
                }
            }
            else
            {
                o->queue.total = o->queue.total - 1;
            }

            return xsuccess;
        }
        else if(descriptor->io == xnil)
        {
            return xsuccess;
        }
        else
        {
            return xfail;
        }
    }
    return xsuccess;
}

extern void xdescriptorio_call(xdescriptorio * o)
{
    xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

    xassertion(io == xnil, "descriptor event generator is null");

    if(io->fd < 0)
    {
        io->fd = epoll_create(io->maxevents);
        if(io->fd >= 0)
        {
            xdescriptor * descriptor = io->children.head;
            while(descriptor)
            {
                struct epoll_event event;
                event.data.ptr = descriptor;
                event.events = (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);
                int ret = epoll_ctl(io->fd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                if(ret != xsuccess)
                {
                    int err = errno;
                    if(err == EEXIST)
                    {
                        ret = epoll_ctl(io->fd, EPOLL_CTL_MOD, descriptor->handle.f, &event);

                        if(ret != xsuccess)
                        {
                            xcheck(xtrue, "fail to epoll_ctl (%d)", err);

                            descriptor->status |= xdescriptor_status_exception;
                            xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                        }
                        else
                        {
                            descriptor = descriptor->next;
                        }
                    }
                    else
                    {
                        xcheck(xtrue, "fail to epoll_ctl (%d)", err);

                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                    }
                }
                else
                {
                    descriptor = descriptor->next;
                }
            }
        }
        else
        {
            xcheck(xtrue, "fail to epoll_create (%d)", errno);
        }
    }
}