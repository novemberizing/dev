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

static inline xuint32 __xpoll_convert_mask_to_pollmask(xuint32 mask)
{
    xuint32 result = 0;
    if(mask & xdescriptor_status_in)
    {
        result |= POLLIN;
    }
    if(mask & xdescriptor_status_out)
    {
        result |= POLLOUT;
    }
    if(mask & xdescriptor_status_exception)
    {
        result |= (POLLPRI | POLLRDHUP | POLLERR | POLLHUP | POLLNVAL);
    }
    else
    {
        if(mask & xdescriptor_status_read_hangup)
        {
            result |= POLLRDHUP;
        }
        if(mask & xdescriptor_status_pri)
        {
            result |= POLLPRI;
        }
        if(mask & xdescriptor_status_hangup)
        {
            result |= POLLHUP;
        }
        if(mask & xdescriptor_status_error)
        {
            result |= POLLERR;
        }
        if(mask & xdescriptor_status_invalid)
        {
            result |= POLLNVAL;
        }
    }
    return result;
}

/**
 * @fn      extern xint32 xdescriptorclose(xdescriptor * o)
 * @brief   
 * @details
 * 
 * 
 */
extern xint32 xdescriptorclose(xdescriptor * o)
{
    if(o)
    {
        if(o->handle.f >= 0)
        {
            int ret = close(o->handle.f);

            if(ret == xsuccess)
            {
                o->status |= xdescriptor_status_close;
                o->status &= (~(xdescriptor_status_open | xdescriptor_status_in | xdescriptor_status_out));

                xdescriptoreventpub(o, xdescriptor_event_close, o->parent, xvalgen(0));

                o->status = xdescriptor_event_void;

                o->handle.f = xinvalid;
            }
            else
            {
                xassertion(xtrue, "fail to close (%d) - check this", errno);
            }
        }
        else
        {
            xcheck(xtrue, "not alive");
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
    return xsuccess;
}

extern xint32 xdescriptoralive(xdescriptor * o)
{
    return (o && o->handle.f >=0);
}

extern xint64 xdescriptorread(xdescriptor * o, void * buffer, xuint64 size)
{
    if(o)
    {
        if(o->handle.f >= 0)
        {
            // xcheck((o->status & xdescriptor_status_in) == xdescriptor_status_void, "not avail descriptor in");
            if(buffer && size)
            {
                xint64 n = read(o->handle.f, buffer, size);
                if(n > 0)
                {
                    o->status |= xdescriptor_status_in;
                    xdescriptoreventpub(o, xdescriptor_event_in, o->parent, xvalgen(n));
                    return n;
                }
                else if(n == 0)
                {
                    xcheck(xtrue, "read return zero (may be closed)");
                    o->status |= xdescriptor_event_exception;
                    // TODO: CHECK CLOSE ??????????
                    xdescriptoreventpub(o, xdescriptor_event_exception, o->parent, xvalgen(0));
                    return xfail;
                }
                else
                {
                    int err = errno;
                    if(err == EAGAIN)
                    {
                        o->status &= (~xdescriptor_status_in);
                        return 0;
                    }
                    else
                    {
                        xcheck(xtrue, "fail to read (%d)", err);
                        o->status |= xdescriptor_event_exception;
                        xdescriptoreventpub(o, xdescriptor_event_exception, o->parent, xvalgen(err));
                        return xfail;
                    }
                }
            }
            else
            {
                xcheck(xtrue, "buffer not exist");
                return xsuccess;
            }
        }
        else
        {
            xcheck(xtrue, "not alive descriptor");
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
    return xfail;
}

extern xint64 xdescriptorwrite(xdescriptor * o, const void * data, xuint64 length)
{
    if(o)
    {
        if(o->handle.f >= 0)
        {
            if(data && length)
            {
                // xcheck((o->status & xdescriptor_status_out) == xdescriptor_status_void, "descriptor not avail write");
                xint64 n = write(o->handle.f, data, length);
                if(n > 0)
                {
                    o->status |= xdescriptor_status_out;
                    xdescriptoreventpub(o, xdescriptor_event_out, o->parent, xvalgen(n));
                    return n;
                }
                else if(n == 0)
                {
                    // PRINT ALL 
                    xcheck(xtrue, "check this logic");
                    return xsuccess;
                }
                else
                {
                    int err = errno;
                    if(err == EAGAIN)
                    {
                        o->status &= (~xdescriptor_status_out);
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(xtrue, "fail to write (%d)", err);
                        o->status |= xdescriptor_event_exception;
                        xdescriptoreventpub(o, xdescriptor_event_exception, o->parent, xvalgen(err));
                        return xfail;
                    }
                }
            }
            else
            {
                xcheck(xtrue, "no available data");
                return xsuccess;
            }
        }
        else
        {
            xcheck(xtrue, "not alive descriptor");
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
    return xfail;
}

extern xint32 xdescriptornonblock_on(xdescriptor * o)
{
    if(o)
    {
        if(o->handle.f >= 0)
        {
            int flags = fcntl(o->handle.f, F_GETFL, 0);

            xassertion(flags == xfail, "fail to fcntl (%d)", errno);

            flags |= O_NONBLOCK;

            int ret = fcntl(o->handle.f, F_SETFL, flags);

            xassertion(ret == xfail, "fail to fcntl (%d)", errno);

            return xsuccess;
        }
        else
        {
            xcheck(xtrue, "not alive descriptor");
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
    return xfail;
}

extern xint32 xdescriptornonblock_off(xdescriptor * o)
{
    if(o)
    {
        if(o->handle.f >= 0)
        {
            int flags = fcntl(o->handle.f, F_GETFL, 0);

            xassertion(flags == xfail, "fail to fcntl (%d)", errno);

            flags &= (~O_NONBLOCK);

            int ret = fcntl(o->handle.f, F_SETFL, flags);

            xassertion(ret == xfail, "fail to fcntl (%d)", errno);

            return xsuccess;
        }
        else
        {
            xcheck(xtrue, "not alive descriptor");
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
    return xfail;
}

extern xdescriptorio * xdescriptorionew(xuint32 type, xdestructor destructor, xuint64 memorysize)
{
    // TODO: TYPE CHECK
    xassertion(memorysize < sizeof(xdescriptorio) || destructor == xnil, "invalid parameter");

    xdescriptorio * o = (xdescriptorio *) calloc(memorysize, 1);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = (xobj_mask_allocated | type);
    o->destruct = destructor;

    return o;
}

extern void xdescriptorioadd(xdescriptorio * o, xdescriptor * descriptor)
{
    if(o && descriptor)
    {
        xsynclock(descriptor->sync);
        if(descriptor->io == xnil)
        {
            xsynclock(o->sync);
            descriptor->io = o;
            descriptor->prev = o->tail;
            o->tail = descriptor;
            if(descriptor->prev)
            {
                descriptor->prev->next = descriptor;
            }
            else
            {
                o->head = descriptor;
            }
            o->total = o->total + 1;
            xsyncunlock(o->sync);
        }
        else
        {
            xcheck(xtrue, "parent io facility is exist");
        }
        xsyncunlock(descriptor->sync);
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
}

extern void xdescriptoriodel(xdescriptorio * o, xdescriptor * descriptor)
{
    if(o && descriptor)
    {
        xsynclock(descriptor->sync);
        xcheck(o != descriptor->io, "invalid io facility");
        if(descriptor->io)
        {
            o = descriptor->io;
            xsynclock(o->sync);
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
            descriptor->io = xnil;
            descriptor->prev = xnil;
            descriptor->next = xnil;
            xsyncunlock(o->sync);
        }
        else
        {
            xcheck(xtrue, "descriptor's io facility is not exist");
        }
        xsyncunlock(descriptor->sync);
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
}

extern void xdescriptorioclear(xdescriptorio * o)
{
    if(o)
    {
        xsynclock(o->sync);
        while(o->head)
        {
            xdescriptor * descriptor = o->head;
            o->head = o->head->next;
            descriptor->next = xnil;
            descriptor->io = xnil;
            o->total = o->total - 1;
            if(o->head)
            {
                o->head->prev = xnil;
            }
            else
            {
                o->tail = xnil;
            }
        }
        xsyncunlock(o->sync);
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
}

extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 second, xuint64 nanosecond)
{
    if(o)
    {
        if(o->handle.f >= 0)
        {
            if(mask)
            {
                struct pollfd data;
                data.fd      = o->handle.f;
                data.events  = __xpoll_convert_mask_to_pollmask(mask);
                data.revents = 0;

                xtime start  = xtimeget();
                xtime end    = xtimeset(start.second + second, start.nanosecond + nanosecond);

                xuint32 result = xdescriptor_event_void;

                while((result & mask) != mask)
                {
                    data.revents = 0;
                    struct timespec timeout = { 0, 1000 };      // 1 unisecond
                    int nfds = ppoll(&data, 1, &timeout, xnil); // TODO: SIGNAL HANDLING
                    if(nfds >= 0)
                    {
                        if(data.revents & POLLIN)
                        {
                            result |= xdescriptor_event_in;
                        }
                        if(data.revents & POLLOUT)
                        {
                            result |= xdescriptor_event_out;
                        }
                        if(data.revents & POLLPRI)
                        {
                            result |= (xdescriptor_event_pri | xdescriptor_event_exception);
                        }
                        if(data.revents & POLLRDHUP)
                        {
                            result |= (xdescriptor_event_read_hangup | xdescriptor_event_exception);
                        }
                        if(data.revents & POLLERR)
                        {
                            result |= (xdescriptor_event_error | xdescriptor_event_exception);
                        }
                        if(data.revents & POLLHUP)
                        {
                            result |= (xdescriptor_event_hangup | xdescriptor_event_exception);
                        }
                        if(data.revents & POLLNVAL)
                        {
                            result |= (xdescriptor_event_invalid | xdescriptor_event_exception);
                        }
                        if(result & xdescriptor_event_exception)
                        {
                            // TODO: CHECK OTHER EXCEPTION ...
                            return result;
                        }
                        else
                        {
                            if((result & mask) != mask && (second > 0 || nanosecond > 0))
                            {
                                xtime current = xtimeget();
                                if(xtimecmp(&current, &end) >= 0)
                                {
                                    result |= xdescriptor_event_timeout;
                                    return result;
                                }
                            }
                        }
                    }
                    else
                    {
                        xassertion(xtrue, "fail to poll (%d)", errno);
                    }
                }
                return result;
            }
            else
            {
                xcheck(xtrue, "no event mask");
                return xdescriptor_event_void;
            }
        }
        else
        {
            xcheck(xtrue, "not alive descriptor");
            return xdescriptor_event_exception;
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
        return xdescriptor_event_exception;
    }
}


extern void xdescriptorset_nonblock_on(xdescriptor * o)
{
    if(o)
    {
        if((o->mask & xdescriptor_mask_nonblock) == xdescriptor_mask_void)
        {
            o->mask |= xdescriptor_mask_nonblock;
            if(o->handle.f >= 0)
            {
                xdescriptornonblock_on(o);
            }
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
}

extern void xdescriptorset_nonblock_off(xdescriptor * o)
{
    if(o)
    {
        if(o->mask & xdescriptor_mask_nonblock)
        {
            o->mask &= (~xdescriptor_mask_nonblock);
            if(o->handle.f >= 0)
            {
                xdescriptornonblock_off(o);
            }
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
}

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