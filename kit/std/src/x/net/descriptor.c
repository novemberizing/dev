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

#include "../net.h"



// /**
//  * @fn  
//  * @brief   
//  */
// extern xdescriptor * xdescriptornew(xuint32 type, xdestructor destructor, xuint64 size)
// {
//     xassertion(size <= sizeof(xdescriptor), "invalid size");
//     xdescriptor * o = (xdescriptor *) calloc(size, 1);
//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     // TODO: CHECK TYPE VALIDATION
//     o->flags = (xobj_mask_allocated | xobj_type_net | type);
//     o->destruct = destructor;

//     o->value.f = xinvalid;

//     return o;
// }

// extern void * xdescriptorrem(void * p)
// {
//     xdescriptor * o = (xdescriptor *) p;
//     xcheck(o == xnil, "null pointer");
//     if(o)
//     {
//         xsynclock(o->sync);
//         if(o->parent)
//         {
//             xsynclock(o->parent->sync);
//             xdescriptor * prev = o->prev;
//             xdescriptor * next = o->next;
//             if(prev)
//             {
//                 prev->next = next;
//             }
//             else
//             {
//                 o->parent->head = next;
//             }
//             if(next)
//             {
//                 next->prev = prev;
//             }
//             else
//             {
//                 o->parent->tail = prev;
//             }
//             o->parent->total = o->parent->total - 1;
//             xsyncunlock(o->parent->sync);
//             o->parent = xnil;
//         }
//         o->sync = xobjrem(o->sync);
//         if(xdescriptoralive(o))
//         {
//             xdescriptorclose(o);
//         }
//         xsyncunlock(o->sync);
//         if(xobjallocated(o))
//         {
//             free(o);
//             o = xnil;
//         }
//     }
//     return o;
// }

// extern xint32 xdescriptorclose(xdescriptor * o)
// {
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         if(xdescriptoralive(o))
//         {
//             int ret = close(o->value.f);
//             xassertion(ret != xsuccess, "fail to close (%d)", errno);

//             xcheck(xtrue, "implement callback notify");

//             o->value.f = xinvalid;
//             o->status  = xdescriptor_status_close;

//             xdescriptorpub(o, xdescriptor_event_close);

//             o->status  = xdescriptor_status_void;

//             return xsuccess;
//         }
//         else
//         {
//             xcheck(xtrue, "already close");
//         }
//     }

//     return xsuccess;
// }

// extern xint32 xdescriptoralive(xdescriptor * o)
// {
//     xcheck(o == xnil, "null pointer");

//     return (o && o->value.f >= 0);
// }

// extern xint64 xdescriptorread(xdescriptor * o, xbyte * buffer, xuint64 size)
// {
//     xassertion(buffer == xnil || size == 0, "invalid parameter");

//     if(o)
//     {
//         if(xdescriptoralive(o))
//         {
//             xint64 n = read(o->value.f, buffer, size);
//             if(n > 0)
//             {
//                 return n;
//             }
//             else if(n == 0)
//             {
//                 xcheck(xtrue, "check this logic");
//             }
//             else
//             {
//                 int err = errno;
//                 if(err == EAGAIN)
//                 {
//                     return 0;
//                 }
//                 xcheck(xtrue, "fail to read (%d)", err);
//             }
//         }
//         else
//         {
//             xcheck(xtrue, "not alive");
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }

//     return xfail;
// }

// extern xint64 xdescriptorwrite(xdescriptor * o, const xbyte * data, xuint64 len)
// {
//     if(o)
//     {
//         if(xdescriptoralive(o))
//         {
//             if(data && len > 0)
//             {
//                 xint64 n = write(o->value.f, data, len);
//                 if(n > 0)
//                 {
//                     return n;
//                 }
//                 else if(n == 0)
//                 {
//                     xcheck(xtrue, "check this logic");
//                     return 0;
//                 }
//                 else
//                 {
//                     int err = errno;
//                     if(err == EAGAIN)
//                     {
//                         return 0;
//                     }
//                     xcheck(xtrue, "fail to read (%d)", err);
//                 }
//             }
//             else
//             {
//                 return 0;
//             }
//         }
//         else
//         {
//             xcheck(xtrue, "not alive");
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }

//     return xfail;
// }


// // extern xint32 xdescriptoralive(const xdescriptor * o)
// // {
// //     return o ? o->value.f >= 0 : xfalse;
// // }

// // extern xint32 xdescriptor_nonblock_on(xdescriptor * o)
// // {
// //     if(o)
// //     {
// //         if(o->value.f >= 0)
// //         {
// //             int flags = fcntl(o->value.f, F_GETFL, 0);
// //             xassertion(flags == xfail, "fail to fcntrl (%d)", errno);
// //             flags |= O_NONBLOCK;
// //             int ret = fcntl(o->value.f, F_SETFL, flags);
// //             xassertion(ret == xfail, "fail to fcntl (%d)", errno);
// //             return ret;
// //         }
// //     }
// //     return xfail;
// // }

// // extern xint32 xdescriptor_nonblock_off(xdescriptor * o)
// // {
// //     if(o)
// //     {
// //         if(o->value.f >= 0)
// //         {
// //             int flags = fcntl(o->value.f, F_GETFL, 0);
// //             xassertion(flags == xfail, "fail to fcntrl (%d)", errno);
// //             flags &= (~O_NONBLOCK);
// //             int ret = fcntl(o->value.f, F_SETFL, flags);
// //             xassertion(ret == xfail, "fail to fcntl (%d)", errno);
// //             return ret;
// //         }
// //     }
// //     return xfail;
// // }


// // extern xint32 xdescriptorclose(xdescriptor * o)
// // {
// //     xcheck(o == xnil, "null pointer");
// //     if(o)
// //     {
// //         xcheck((o->value.f >= 0) == xfalse, "socket not opened");

// //         if(o->value.f >= 0)
// //         {
// //             if(close(o->value.f) != xsuccess)
// //             {
// //                 xassertion(xtrue, "fail to close (%d)", errno);
// //             }
// //             o->value.f = xinvalid;
// //         }
// //         return xsuccess;
// //     }
// //     return xfail;
// // }

// // extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 nanosecond)
// // {
// //     if(o)
// //     {
// //         if(o->value.f >= 0)
// //         {
// //             struct pollfd fds = { xinvalid, 0, 0 };
// //             fds.fd = o->value.f;
// //             if(mask & xdescriptor_event_read)
// //             {
// //                 fds.events |= POLLIN;
// //             }
// //             if(mask & xdescriptor_event_write)
// //             {
// //                 fds.events |= POLLOUT;
// //             }
// //             if(mask & xdescriptor_event_error)
// //             {
// //                 fds.events |= POLLERR;
// //             }
// //             if(mask & xdescriptor_event_pri)
// //             {
// //                 fds.events |= POLLPRI;
// //             }
// //             if(mask & xdescriptor_event_readhup)
// //             {
// //                 fds.events |= POLLRDHUP;
// //             }
// //             if(mask & xdescriptor_event_hup)
// //             {
// //                 fds.events |= POLLHUP;
// //             }
// //             if(mask & xdescriptor_event_invalid)
// //             {
// //                 fds.events |= POLLNVAL;
// //             }
// //             if(mask & xdescriptor_event_readband)
// //             {
// //                 fds.events |= POLLRDBAND;
// //             }
// //             if(mask & xdescriptor_event_writeband)
// //             {
// //                 fds.events |= POLLWRBAND;
// //             }
// //             int result = xdescriptor_event_void;
// //             struct timespec start = { 0, 0};
// //             struct timespec current = { 0, 0 };
// //             struct timespec diff = { 0, 0};
// //             clock_gettime(CLOCK_REALTIME, &start);  // TODO: CHECK FAIL
// //             struct timespec timespec = { 0, 1000 };
// //             while((result & mask) != mask)
// //             {
// //                 int nfds = ppoll(&fds, 1, &timespec, xnil);
// //                 if(nfds >= 0)
// //                 {
// //                     /**
// //                      * TODO: 마스크 처리하는데 시간이 많이 걸린다.
// //                      * 어떻게 하면 STD 라이브러리 헤더 없이 ....
// //                      */
// //                     if(fds.revents & POLLIN)
// //                     {
// //                         result |= xdescriptor_event_read;
// //                     }
// //                     if(fds.revents & POLLOUT)
// //                     {
// //                         result |= xdescriptor_event_write;
// //                     }
// //                     if(fds.revents & POLLPRI)
// //                     {
// //                         result |= xdescriptor_event_pri;
// //                     }
// //                     if(fds.revents & POLLERR)
// //                     {
// //                         result |= xdescriptor_event_error;
// //                     }
// //                     if(fds.revents & POLLRDHUP)
// //                     {
// //                         result |= xdescriptor_event_readhup;
// //                     }
// //                     if(fds.revents & POLLHUP)
// //                     {
// //                         result |= xdescriptor_event_hup;
// //                     }
// //                     if(fds.revents & POLLRDBAND)
// //                     {
// //                         result |= xdescriptor_event_readband;
// //                     }
// //                     if(fds.revents & POLLWRBAND)
// //                     {
// //                         result |= xdescriptor_event_writeband;
// //                     }
// //                     if(fds.revents & POLLNVAL)
// //                     {
// //                         result |= xdescriptor_event_invalid;
// //                     }
// //                     clock_gettime(CLOCK_REALTIME, &current);
// //                     diff.tv_sec = current.tv_sec - start.tv_sec;
// //                     diff.tv_nsec = current.tv_nsec - start.tv_nsec;
// //                     if(diff.tv_nsec < 0)
// //                     {
// //                         diff.tv_sec = diff.tv_sec - 1;
// //                         diff.tv_nsec = 1000000000 + diff.tv_nsec;
// //                     }
// //                     // check overflow
// //                     if((result & mask) != mask)
// //                     {
// //                         if(nanosecond < xtimenanosecond(diff.tv_sec, diff.tv_nsec))
// //                         {
// //                             result |= xdescriptor_event_timeout;
// //                             return result;
// //                         }
// //                     }
// //                 }
// //                 else
// //                 {
// //                     xassertion(xtrue, "fail to ppoll (%d)", errno);
// //                     return xdescriptor_event_except;
// //                 }
// //             }
// //             return result;
// //         }
// //         else
// //         {
// //             xcheck(xtrue, "socket is not alive");
// //         }
// //     }
// //     else
// //     {
// //         xcheck(xtrue, "null pointer");
// //     }
// //     return xdescriptor_event_except;
// // }