#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>

#include "io.h"

#include "descriptor.h"
#include "descriptorio.h"

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
    xuint32 status;

    int fd;
    struct epoll_event * events;
    int maxevents;
    int timeout;
};

typedef struct xdescriptorio_epoll xdescriptorio_epoll;

extern void xdescriptorio_call(xdescriptorio * o)
{
    xassertion(o == xnil, "xdescriptorio is null");

    xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

    xdescriptorip_create(io);
    xdescriptorio_queue_once(io);

    if(io->fd >= 0)
    {
        int nfds = epoll_wait(io->fd, io->events, io->maxevents, io->timeout);
        if(nfds >= 0)
        {

        }
        else
        {
            switch(err)
            {
                case EBADF: xassertion(err == EBADF, "fail to epoll_wait (%d => %s)", err, xerrorstr(epoll_wait, err)); break;
            }
    //                EBADF  epfd is not a valid file descriptor.

    //    EFAULT The memory area pointed to by events is not accessible with write permissions.

    //    EINTR  The call was interrupted by a signal handler before either (1) any of the requested events occurred or (2) the timeout expired; see signal(7).

    //    EINVAL epfd is not an epoll file descriptor, or maxevents is less than or equal to zero.

        }
    }
}


// static inline xint32 xdescriptorio_epoll_reg(int epollfd, xdescriptor * descriptor)
// {
//     xassertion(descriptor == xnil, "descriptor is null");
//     xassertion(epollfd < 0, "epoll file descriptor is not open");
//     xassertion(descriptor->handle.f < 0, "descriptor is not open");
//     xassertion(descriptor->status & xdescriptor_status_exception, "exception descriptor");

//     struct epoll_event event;
//     event.data.ptr = descriptor;
//     event.events = (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);

//     if((descriptor->status & xdescriptor_status_in) == xdescriptor_status_void)
//     {
//         event.events |= EPOLLIN;
//     }
//     if((descriptor->status & xdescriptor_status_out) == xdescriptor_status_void)
//     {
//         event.events |= EPOLLOUT;
//     }

//     if(descriptor->status & xdescriptor_status_register)
//     {
//         int ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
//         if(ret == xsuccess)
//         {
//             return xsuccess;
//         }
//         else
//         {
//             int err = errno;
//             if(err == ENOENT)
//             {
//                 ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
//                 if(ret == xsuccess)
//                 {
//                     return xsuccess;
//                 }
//                 xcheck(ret != xsuccess, "fail to epoll_ctl - add (%d)", errno);
//             }
//             else
//             {
//                 xcheck(ret != xsuccess, "fail to epoll_ctl - mod (%d)", err);
//             }
//         }
//     }
//     else
//     {
//         int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
//         if(ret == xsuccess)
//         {
//             descriptor->status |= xdescriptor_status_register;
//             if(xdescriptor_event_on(descriptor, xdescriptor_event_register, xnil, 0) != xsuccess)
//             {
//                 if(epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil) != xsuccess)
//                 {
//                     xcheck(xtrue, "fail to epoll_ctl - del (%d)", errno);
//                 }
//                 descriptor->status &= (~xdescriptor_status_register);
//                 descriptor->status |= xdescriptor_status_exception;
//                 xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);)
//                 return xfail;
//             }
//             return xsuccess;
//         }
//         else
//         {
//             int err = errno;
//             if(err == EEXIST)
//             {
//                 ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
//                 if(ret == xsuccess)
//                 {
//                     descriptor->status |= xdescriptor_status_register;
//                     if(xdescriptor_event_on(descriptor, xdescriptor_event_register, xnil, 0) != xsuccess)
//                     {
//                         if(epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil) != xsuccess)
//                         {
//                             xcheck(xtrue, "fail to epoll_ctl - del (%d)", errno);
//                         }
//                         descriptor->status &= (~xdescriptor_status_register);
//                         descriptor->status |= xdescriptor_status_exception;
//                         xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);)
//                         return xfail;
//                     }
//                     return xsuccess;
//                 }
//                 xcheck(ret != xsuccess, "fail to epoll_ctl - mod (%d)", errno);
//             }
//             else
//             {
//                 xcheck(ret != xsuccess, "fail to epoll_ctl - add (%d)", err);
//             }
//         }
//     }
//     return xfail;
// }

// static inline xint32 xdescriptorio_epoll_unreg(int epollfd, xdescriptor * descriptor)
// {
//     xassertion(descriptor == xnil, "descriptor is null");

//     if(epollfd >= 0 && descriptor->handle.f >= 0)
//     {
//         if(descriptor->status & xdescriptor_status_register)
//         {
//             int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);
//             xcheck(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
//             descriptor->status &= (~xdescriptor_status_register);
//         }
//     }

//     return xsuccess;
// }

// /**
//  * 
//  * 워커 모델로 구현하는 것은 아니다.
//  */
// static inline xint64 xdescriptorio_dispatch(xdescriptor * descriptor, xuint32 event)
// {
//     xassertion(descriptor == xnil, "descriptor is null");

//     if(event & xdescriptor_event_exception)
//     {
//     }
//     else if(event & xdescriptor_event_close)
//     {
//     }
//     else
//     {
//         if(event & xdescriptor_event_out)
//         {
//         }
//         if(event & xdescriptor_event_in)
//         {
//         }
//     }
// }

// // static inline xint64 xdescriptorio_dispatch(xdescriptor * descriptor, xuint32 event)
// // {
// //     xassertion(descriptor == xnil, "descriptor is null");
// //     if(event & xdescriptor_event_exception)
// //     {
// //         xassertion(event & xdescriptor_event_exception, "implement descriptor exception dispatch");
// //         return xsuccess;
// //     }
// //     else
// //     {
// //         return xdescriptor_do(descriptor, event);
// //     }
// // }

// // static inline xint32 xdescriptorio_epoll_reg(int epollfd, xdescriptor * descriptor)
// // {
// //     if(descriptor)
// //     {
// //         if(epollfd >= 0)
// //         {
// //             if(descriptor->handle.f >= 0)
// //             {
// //                 if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
// //                 {
// //                     struct epoll_event event;
// //                     event.data.ptr = descriptor;
// //                     event.events = (EPOLLERR | EPOLLPRI | EPOLLHUP | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);
// //                     int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
// //                     if(ret != xsuccess)
// //                     {
// //                         int err = errno;
// //                         if(err == EEXIST)
// //                         {
// //                             ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
// //                             if(ret != xsuccess)
// //                             {
// //                                 xcheck(err != EEXIST, "fail to epoll_ctl (%d)", err);
// //                                 ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);
// //                                 xcheck(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
// //                                 return xfail;
// //                             }
// //                         }
// //                         else
// //                         {
// //                             xcheck(err != EEXIST, "fail to epoll_ctl (%d)", err);
// //                             return xfail;
// //                         }
// //                     }
// //                     return xsuccess;
// //                 }
// //                 else
// //                 {
// //                     xassertion(descriptor->status & xdescriptor_status_exception, "exception descriptor");
// //                     return xfail;
// //                 }
// //             }
// //             else
// //             {
// //                 xassertion(descriptor->handle.f < 0, "descriptor is not alive");
// //                 return xfail;
// //             }
// //         }
// //         else
// //         {
// //             xcheck(xtrue, "epollfd is not open");
// //             return xsuccess;
// //         }
// //     }
// //     else
// //     {
// //         xassertion(descriptor == xnil, "descriptor is null");
// //         return xfail;
// //     }
// // }

// // static inline void xdescriptorio_epoll_unreg(int epollfd, xdescriptor * descriptor)
// // {
// //     if(epollfd >= 0 && descriptor && descriptor->handle.f >= 0)
// //     {
// //         int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);
// //         xcheck(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
// //     }
// // }

// // static inline void xdescriptorio_epoll_queue_loop(xdescriptorio_epoll * io)
// // {
// //     xassertion(io == xnil, "io is null");

// //     xdescriptor * descriptor = io->queue.head;
// //     xuint32 total = io->queue.total;

// //     for(xuint32 i = 0; i < total && descriptor; i++)
// //     {
// //         xdescriptor * next = xdescriptorio_queue_del(descriptor);

// //         if(descriptor->status & xdescriptor_status_exception)
// //         {
// //             // registered ... ?
// //             xdescriptorio_dispatch(descriptor, xdescriptor_event_exception);
// //             descriptor = next;
// //             continue;
// //         }

// //         xassertion(descriptor->status != xdescriptor_status_void, "invalid descriptor status (critical)");

// //         xint32 ret = xdescriptorio_dispatch(descriptor, xdescriptor_event_open);
// //         if(ret == xsuccess)
// //         {
// //             ret = xdescriptorio_epoll_reg(io->fd, descriptor);
// //             if(ret == xsuccess)
// //             {
// //                 xdescriptorio_children_push(descriptor);
// //                 descriptor = next;
// //                 continue;
// //             }
// //         }

// //         xassertion((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void, "invalid descriptor status (critical)");
// //         xdescriptorio_do(descriptor, xdescriptor_event_exception);
// //         descriptor = next;
// //     }
// // }


// // // static inline xint32 xdescriptorio_epoll_reg(int epollfd, xdescriptor * descriptor)
// // // {
// // //     xassertion(descriptor == xnil, "descriptor is null");

// // //     if(epollfd >= 0)
// // //     {
// // //         if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
// // //         {
// // //             if(descriptor->handle.f >= 0)
// // //             {
// // //                 struct epoll_event event;
// // //                 event.data.ptr = descriptor;
// // //                 event.events = (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);
// // //                 if((descriptor->status & xdescriptor_status_in) == xdescriptor_status_void)
// // //                 {
// // //                     printf("register in\n");
// // //                     event.events |= EPOLLIN;
// // //                 }
// // //                 if((descriptor->status & xdescriptor_status_out) == xdescriptor_status_void)
// // //                 {
// // //                     printf("register out\n");
// // //                     event.events |= EPOLLOUT;
// // //                 }
// // //                 if((descriptor->status & xdescriptor_status_connect) == xdescriptor_status_void)
// // //                 {
// // //                     if(descriptor->status & xdescriptor_status_connecting)
// // //                     {
// // //                         event.events |= EPOLLOUT;
// // //                     }
// // //                 }

// // //                 int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
// // //                 if(ret != xsuccess)
// // //                 {
// // //                     int err = errno;
// // //                     if(err == EEXIST)
// // //                     {
// // //                         ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
// // //                         if(ret != xsuccess)
// // //                         {
// // //                             xcheck(ret != xsuccess, "fail to epoll_ctl - mod (%d)", errno);
// // //                             ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);
// // //                             xcheck(ret != xsuccess, "fail to epoll_ctl - del (%d)", errno);
// // //                             return xfail;
// // //                         }
// // //                         printf("server is listen 1\n");
// // //                         return xsuccess;
// // //                     }
// // //                     xcheck(err != EEXIST, "fail to epoll_ctl - add (%d)", err);
// // //                     return xfail;
// // //                 }
// // //                 printf("server is listen 2\n");
// // //                 return xsuccess;
// // //             }
// // //         }
// // //     }
// // //     return xfail;
// // // }

// // // static inline void xdescriptorio_epoll_unreg(int epollfd, xdescriptor * descriptor)
// // // {
// // //     if(epollfd >= 0)
// // //     {
// // //         if(descriptor && descriptor->handle.f >= 0)
// // //         {
// // //             int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);
// // //             xcheck(ret != xsuccess, "fail to epoll_ctl - del (%d)", errno);
// // //         }
// // //     }
// // // }

// // // static inline void xdescriptorio_epoll_children_open(xdescriptorio_epoll * io)
// // // {
// // //     xassertion(io == xnil, "xdescriptorio epoll is null");

// // //     xuint32 total = io->queue.total;
// // //     xdescriptor * descriptor = io->queue.head;
// // //     for(xuint32 i = 0; i < total && descriptor != xnil; i++)
// // //     {
// // //         int ret = xdescriptor_open(descriptor);
// // //         if(ret == xsuccess)
// // //         {
// // //             xdescriptor * prev = descriptor->prev;
// // //             xdescriptor * next = descriptor->next;
// // //             if(prev)
// // //             {
// // //                 prev->next = next;
// // //             }
// // //             else
// // //             {
// // //                 io->queue.head = next;
// // //             }
// // //             if(next)
// // //             {
// // //                 next->prev = prev;
// // //             }
// // //             else
// // //             {
// // //                 io->queue.tail = prev;
// // //             }
// // //             io->queue.total = io->queue.total - 1;

// // //             if(io->fd >= 0)
// // //             {
// // //                 ret = xdescriptorio_epoll_reg(io->fd, descriptor);
// // //                 if(ret != xsuccess)
// // //                 {
// // //                     descriptor->status |= xdescriptor_status_exception;
// // //                     xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
// // //                     descriptor->next = xnil;
// // //                     descriptor->prev = io->exceptions.tail;
// // //                     if(descriptor->prev)
// // //                     {
// // //                         descriptor->prev->next = descriptor;
// // //                     }
// // //                     else
// // //                     {
// // //                         io->exceptions.head = descriptor;
// // //                     }
// // //                     io->exceptions.tail = descriptor;
// // //                     io->exceptions.total = io->exceptions.total + 1;

// // //                     descriptor = next;
// // //                     continue;
// // //                 }
// // //             }
            
// // //             descriptor->next = xnil;
// // //             descriptor->prev = io->children.tail;
// // //             if(descriptor->prev)
// // //             {
// // //                 descriptor->prev->next = descriptor;
// // //             }
// // //             else
// // //             {
// // //                 io->children.head = descriptor;
// // //             }
// // //             io->children.tail = descriptor;
// // //             io->children.total = io->children.total + 1;

// // //             descriptor = next;
// // //         }
// // //         else
// // //         {
// // //             descriptor = descriptor->next;
// // //         }
// // //     }
// // // }

// // // static inline xint32 xdescriptorio_epoll_open(xdescriptorio_epoll * io)
// // // {
// // //     xassertion(io == xnil, "io is null");

// // //     if(io->fd < 0)
// // //     {
// // //         io->fd = epoll_create(io->maxevents);

// // //         if(io->fd >= 0)
// // //         {
// // //             xdescriptor * descriptor = io->children.head;

// // //             while(descriptor)
// // //             {
// // //                 xassertion(descriptor->handle.f < 0 || (descriptor->status & xdescriptor_status_exception), "descriptor's not alive or exceptions");

// // //                 int ret = xdescriptorio_epoll_reg(io->fd, descriptor);

// // //                 if(ret != xsuccess)
// // //                 {
// // //                     xdescriptor * prev = descriptor->prev;
// // //                     xdescriptor * next = descriptor->next;

// // //                     if(prev)
// // //                     {
// // //                         prev->next = next;
// // //                     }
// // //                     else
// // //                     {
// // //                         io->children.head = next;
// // //                     }

// // //                     if(next)
// // //                     {
// // //                         next->prev = prev;
// // //                     }
// // //                     else
// // //                     {
// // //                         io->children.tail = prev;
// // //                     }
// // //                     io->children.total = io->children.total - 1;
                    
// // //                     descriptor->next = xnil;
// // //                     descriptor->prev = io->exceptions.tail;
// // //                     if(descriptor->prev)
// // //                     {
// // //                         descriptor->prev->next = descriptor;
// // //                     }
// // //                     else
// // //                     {
// // //                         io->exceptions.head = descriptor;
// // //                     }
// // //                     io->exceptions.tail = descriptor;
// // //                     io->exceptions.total = io->exceptions.total + 1;

// // //                     descriptor = next;
// // //                     continue;
// // //                 }

// // //                 descriptor = descriptor->next;
// // //             }
// // //         }
// // //         else
// // //         {
// // //             xcheck(io->fd < 0, "fail to epoll_create (%d)", errno);
// // //         }
// // //     }
// // // }

// // // static inline void xdescriptorio_exception_on(xdescriptorio_epoll * io, xdescriptor * descriptor, const void * data, xint64 val)
// // // {
// // //     xassertion(io == xnil || descriptor == xnil, "io is null or descriptor is null");
// // //     if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
// // //     {
// // //         descriptor->status |= xdescriptor_status_exception;
// // //         xdescriptor_event_on(descriptor, xdescriptor_event_exception, data, val);
        
// // //         // 혹시나 xdescriptor_event_on 에 exception 발생 시에 구현될지 몰라서, 위가 아닌 
// // //         // 아래에 구현한다.

// // //         xdescriptor * prev = descriptor->prev;
// // //         xdescriptor * next = descriptor->next;

// // //         if(prev)
// // //         {
// // //             prev->next = next;
// // //         }
// // //         else
// // //         {
// // //             io->children.head = next;
// // //         }

// // //         if(next)
// // //         {
// // //             next->prev = prev;
// // //         }
// // //         else
// // //         {
// // //             io->children.tail = prev;
// // //         }

// // //         io->children.total = io->children.total - 1;

// // //         descriptor->next = xnil;
// // //         descriptor->prev = io->exceptions.tail;
// // //         if(descriptor->prev)
// // //         {
// // //             descriptor->prev->next = descriptor;
// // //         }
// // //         else
// // //         {
// // //             io->exceptions.head = descriptor;
// // //         }
// // //         io->exceptions.tail = descriptor;
// // //         io->exceptions.total = io->exceptions.total + 1;

// // //         if(io->fd >= 0)
// // //         {
// // //             if(descriptor->handle.f >= 0)
// // //             {
// // //                 xdescriptorio_epoll_unreg(io->fd, descriptor);
// // //             }
// // //         }
// // //     }
// // // }

// // // extern xdescriptorio * xdescriptorio_new(void)
// // // {
// // //     xdescriptorio_epoll * io = (xdescriptorio_epoll *) calloc(sizeof(xdescriptorio_epoll), 1);

// // //     xassertion(io == xnil, "fail to calloc (%d)", errno);

// // //     io->fd        = xinvalid;
// // //     io->maxevents = 1024;   // check this constant
// // //     io->events    = malloc(sizeof(struct epoll_event) * io->maxevents);
// // //     xassertion(io->events == xnil, "fail to malloc (%d)", errno);
// // //     io->timeout   = 1;      // check this timeout

// // //     return (xdescriptorio *) io;
// // // }

// // // extern void xdescriptorio_term(xdescriptorio * o)
// // // {
// // //     xdescriptorio_clear(o);

// // //     xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

// // //     if(io->fd >= 0)
// // //     {
// // //         int ret = close(io->fd);
// // //         xcheck(ret != xsuccess, "fail to close (%d)", errno);
// // //     }
// // // }

// // // extern xdescriptorio * xdescriptorio_rem(xdescriptorio * o)
// // // {
// // //     xdescriptorio_term(o);

// // //     xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

// // //     if(io)
// // //     {
// // //         if(io->fd >= 0)
// // //         {
// // //             close(io->fd);
// // //         }

// // //         io->events = xfree(io->events);

// // //         free(io);
// // //         io = xnil;
// // //     }

// // //     return (xdescriptorio *) io;
// // // }

// // // extern xint32 xdescriptorio_reg(xdescriptorio * o, xdescriptor * descriptor)
// // // {
// // //     xassertion(o == xnil || descriptor == xnil, "descriptorio is null or descriptor is null");
// // //     if(descriptor->io == xnil)
// // //     {
// // //         xassertion(descriptor->prev || descriptor->next, "descriptor is invalid (not clear)");

// // //         if(descriptor->handle.f >= 0)
// // //         {
// // //             if(descriptor->status & xdescriptor_status_exception)
// // //             {
// // //                 descriptor->io = o;

// // //                 descriptor->prev = o->exceptions.tail;
// // //                 if(descriptor->prev)
// // //                 {
// // //                     descriptor->prev->next = descriptor;
// // //                 }
// // //                 else
// // //                 {
// // //                     o->exceptions.head = descriptor;
// // //                 }
// // //                 o->exceptions.tail = descriptor;
// // //                 o->exceptions.total = o->exceptions.total + 1;
// // //             }
// // //             else
// // //             {
// // //                 xassertion((descriptor->status & xdescriptor_status_open) == xdescriptor_status_void, "descriptor is invalid status");

// // //                 xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;
// // //                 if(io->fd >= 0)
// // //                 {
// // //                     int ret = xdescriptorio_epoll_reg(io->fd, descriptor);
// // //                     if(ret != xsuccess)
// // //                     {
// // //                         xcheck(ret != xsuccess, "fail to xdescriptorio epoll reg");
// // //                         return xfail;
// // //                     }
// // //                 }

// // //                 descriptor->io = o;

// // //                 descriptor->prev = o->children.tail;
// // //                 if(descriptor->prev)
// // //                 {
// // //                     descriptor->prev->next = descriptor;
// // //                 }
// // //                 else
// // //                 {
// // //                     o->children.head = descriptor;
// // //                 }
// // //                 o->children.tail = descriptor;
// // //                 o->children.total = o->children.total + 1;
// // //             }
// // //             return xsuccess;
// // //         }
// // //         else
// // //         {
// // //             xassertion(descriptor->status != xdescriptor_status_void, "descriptor status not void");

// // //             descriptor->io = o;

// // //             descriptor->prev = o->queue.tail;
// // //             if(descriptor->prev)
// // //             {
// // //                 descriptor->prev->next = descriptor;
// // //             }
// // //             else
// // //             {
// // //                 o->queue.head = descriptor;
// // //             }
// // //             o->queue.tail = descriptor;
// // //             o->queue.total = o->queue.total + 1;

// // //             return xsuccess;
// // //         }
// // //     }
// // //     else if(descriptor->io == o)
// // //     {
// // //         return xsuccess;
// // //     }
// // //     else
// // //     {
// // //         xassertion(descriptor->io != o, "descriptor is already registered");
// // //         return xfail;
// // //     }
// // // }

// // // extern xint32 xdescriptorio_unreg(xdescriptorio * o, xdescriptor * descriptor)
// // // {
// // //     xassertion(o == xnil || descriptor == xnil, "fail to xdescriptor");

// // //     if(descriptor->io == o)
// // //     {
// // //         if(descriptor->handle.f >= 0)
// // //         {
// // //             if(descriptor->status & xdescriptor_status_exception)
// // //             {
// // //                 xdescriptor * prev = descriptor->prev;
// // //                 xdescriptor * next = descriptor->next;

// // //                 if(prev)
// // //                 {
// // //                     prev->next = next;
// // //                 }
// // //                 else
// // //                 {
// // //                     o->exceptions.head = next;
// // //                 }

// // //                 if(next)
// // //                 {
// // //                     next->prev = prev;
// // //                 }
// // //                 else
// // //                 {
// // //                     o->exceptions.tail = prev;
// // //                 }
// // //                 o->exceptions.total = o->exceptions.total - 1;

// // //                 descriptor->prev = xnil;
// // //                 descriptor->next = xnil;
// // //                 descriptor->io = xnil;
// // //             }
// // //             else
// // //             {
// // //                 xdescriptor * prev = descriptor->prev;
// // //                 xdescriptor * next = descriptor->next;

// // //                 if(prev)
// // //                 {
// // //                     prev->next = next;
// // //                 }
// // //                 else
// // //                 {
// // //                     o->children.head = next;
// // //                 }

// // //                 if(next)
// // //                 {
// // //                     next->prev = prev;
// // //                 }
// // //                 else
// // //                 {
// // //                     o->children.tail = prev;
// // //                 }
// // //                 o->children.total = o->children.total - 1;

// // //                 descriptor->prev = xnil;
// // //                 descriptor->next = xnil;
// // //                 descriptor->io = xnil;

// // //                 xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

// // //                 if(io->fd >= 0)
// // //                 {
// // //                     xdescriptorio_epoll_unreg(io->fd, descriptor);
// // //                 }
// // //             }
// // //         }
// // //         else
// // //         {
// // //             xassertion(descriptor->status != xdescriptor_status_void, "descriptor is not clear");

// // //             xdescriptor * prev = descriptor->prev;
// // //             xdescriptor * next = descriptor->next;
// // //             if(prev)
// // //             {
// // //                 prev->next = next;
// // //             }
// // //             else
// // //             {
// // //                 o->queue.head = next;
// // //             }
// // //             if(next)
// // //             {
// // //                 next->prev = prev;
// // //             }
// // //             else
// // //             {
// // //                 o->queue.tail = prev;
// // //             }
// // //             o->queue.total = o->queue.total - 1;

// // //             descriptor->prev = xnil;
// // //             descriptor->next = xnil;
// // //             descriptor->io = xnil;
// // //         }
// // //         return xsuccess;
// // //     }
// // //     else if(descriptor->io == xnil)
// // //     {
// // //         return xsuccess;
// // //     }
// // //     else
// // //     {
// // //         xassertion(descriptor->io != o, "descriptor io and io is not same");
// // //         return xfail;
// // //     }

// // // }

// // // extern void xdescriptorio_call(xdescriptorio * o)
// // // {
// // //     xdescriptorio_epoll * io = (xdescriptorio_epoll *) o;

// // //     xassertion(io == xnil, "descriptor event generator is null");

// // //     xdescriptorio_epoll_open(io);
// // //     xdescriptorio_epoll_children_open(io);

// // //     if(io->fd >= 0)
// // //     {
// // //         int nfds = epoll_wait(io->fd, io->events, io->maxevents, io->timeout);
// // //         if(nfds >= 0)
// // //         {
// // //             for(xint32 i = 0; i < nfds; i++)
// // //             {
// // //                 xdescriptor * descriptor = (xdescriptor *) io->events[i].data.ptr;
// // //                 printf("%p\n", descriptor);
// // //                 if(io->events[i].events & (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP))
// // //                 {
// // //                     printf("poll hup\n");
// // //                     xdescriptorio_exception_on(io, descriptor, xnil, 0);
// // //                     continue;
// // //                 }
// // //                 if(io->events[i].events & EPOLLOUT)
// // //                 {
// // //                     printf("out\n");
// // //                     descriptor->status |= xdescriptor_status_out;
// // //                     xint64 ret = xdescriptor_event_on(descriptor, xdescriptor_event_out, xnil, 0);
// // //                     if(ret < 0)
// // //                     {
// // //                         xdescriptorio_exception_on(io, descriptor, xnil, 0);
// // //                         continue;
// // //                     }
// // //                 }
// // //                 if(io->events[i].events & EPOLLIN)
// // //                 {
// // //                     printf("in\n");
// // //                     descriptor->status |= xdescriptor_status_in;
// // //                     xint64 ret = xdescriptor_event_on(descriptor, xdescriptor_event_in, xnil, 0);
// // //                     if(ret < 0)
// // //                     {
// // //                         xdescriptorio_exception_on(io, descriptor, xnil, 0);
// // //                         continue;
// // //                     }
// // //                 }
// // //             }
// // //         }
// // //         else
// // //         {
// // //             int err = errno;
// // //             if(err != EINTR)
// // //             {
// // //                 switch(err)
// // //                 {
// // //                     case EBADF: xcheck(err == EBADF, "epfd is not a valid file descriptor. (%d)", err); break;
// // //                     case EFAULT: xcheck(err = EFAULT, "The memory area pointed to by events is not accessible with write permissions. (%d)", err); break;
// // //                     case EINVAL: xcheck(err == EINVAL, "epfd is not an epoll file descriptor, or maxevents is less than or equal to zero. (%d)", err); break;
// // //                     default:     xcheck(err, "Undocumented exception (%d)", err); break;
// // //                 }
// // //                 close(io->fd);
// // //                 io->fd = xinvalid;
// // //             }
// // //         }
// // //     }
// // // }