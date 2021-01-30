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

static xuint32 __xdescriptor_internal_poll_mask_convert(xuint32 mask)
{
    xuint32 result = 0;
    if(mask & xdescriptor_event_in)
    {
        result |= POLLIN;
    }
    if(mask & xdescriptor_event_out)
    {
        result |= POLLOUT;
    }
    return result;
}

extern void xdescriptornonblock_on(xdescriptor * descriptor)
{
    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {
            int flags = fcntl(descriptor->handle.f, F_GETFL);
            if(flags >= 0)
            {
                flags |= O_NONBLOCK;
                int ret = fcntl(descriptor->handle.f, F_SETFL, flags);
                if(ret == xfail)
                {
                    xcheck(xtrue, "fail to fcntl (%d)", errno);
                }
            }
            else
            {
                xcheck(xtrue, "fail to fcntl (%d)", errno);
            }
        }
    }
}

extern void xdescriptornonblock_off(xdescriptor * descriptor)
{
    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {
            int flags = fcntl(descriptor->handle.f, F_GETFL);
            if(flags >= 0)
            {
                flags &= (~O_NONBLOCK);
                int ret = fcntl(descriptor->handle.f, F_SETFL, flags);
                if(ret == xfail)
                {
                    xcheck(xtrue, "fail to fcntl (%d)", errno);
                }
            }
            else
            {
                xcheck(xtrue, "fail to fcntl (%d)", errno);
            }
        }
    }
}

/**
 * @fn      extern xint32 xdescriptoralive(xdescriptor * descriptor)
 * @brief   파일 디스크립터 객체가 오픈 상태임을 체크합니다.
 *              
 *              파일 디스크럽터의 오픈 상태는 디스크립터의 값을 참조하여 상태를 체크합니다.
 *              디스크립터 객체의 상태를 체크하는 변수 `status` 에 저장된 값을 참조하지는 않습니다.
 *              즉, `descriptor.handle.f >= 0` 인 경우에 한하여 TRUE 를 리턴합니다.
 * 
 * @param   descriptor  | in | xdescriptor * | 디스크립터 객체 |
 * 
 * @return  | xint32 | 파일 디스크립터의 오픈 상태 |
 *          
 *              파일 디스크립터가 오픈 상태이면 TRUE 를 그렇지 않으면 FALSE 를 리턴합니다.
 */
extern xint32 xdescriptoralive(xdescriptor * descriptor)
{
    return descriptor && descriptor->handle.f >= 0;
}

/**
 * @fn      extern xint32 xdescriptorclose(xdescriptor * descriptor)
 * @brief   디스크립터를 닫습니다.
 * 
 *              디스크럽터의 닫기가 성공하면, 상태를 CLOSE 상태로 설정하고,
 *              IN/OUT 상태를 제거한 상태에서 이벤트 핸들러가 존재하면,
 *              이벤트 핸들러를 호출하고, 마지막으로 모든 상태를 초기화합니다.
 *              즉, 최종적으로 디스크립터 객체의 상태는 공허한 상태가 되고,
 *              파일 디스크립터는 INVALID 로 설정됩니다.
 * 
 * @param   descriptor  | in | xdescriptor * | 디스크립터 객체 |
 * 
 * @return  | xint32 | 디스크립터 닫기 수행 결과 |
 * 
 *              디스크립터 닫기 수행 결과로 성공하면 0 (SUCCESS), 
 *              실패하면 -1 (FAIL) 을 리턴합니다.
 * 
 */
extern xint32 xdescriptorclose(xdescriptor * descriptor)
{
    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {
            int ret = close(descriptor->handle.f);
            
            if(ret == xsuccess)
            {
                descriptor->handle.f = xinvalid;
                descriptor->status |= xdescriptor_status_close;
                descriptor->status &= (~(xdescriptor_status_in | xdescriptor_status_out));
                xdescriptoreventpub(descriptor, xdescriptor_event_close, descriptor->data, xvalgen(0));
                descriptor->status = xdescriptor_status_void;
                return xsuccess;
            }
            else
            {
                xassertion(xtrue, "fail to close (%d)", errno);
                return xfail;
            }
        }
        else
        {
            xcheck(xtrue, "o.handle.f >= 0");
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
    }
    return xsuccess;
}

/**
 * @fn      extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
 * @brief   디스크립터 객체의 읽기를 수행합니다.
 * 
 *              디스크립터 객체의 읽기를 수행하고, 읽은 결과가 존재하면
 *              디스크립터의 상태를 IN 으로 설정합니다. 즉, 읽기 가능한 상태가 된 것입니다.
 *              만약에, 읽기에 실패하고 그 에러 결과가 EAGAIN 이면,
 *              디스크립터 상태에서 IN 을 제거합니다.
 *              
 *              읽은 상태가 0 이면 이미 닫힌 디스크립터가 판단하고 상태를 예외 발생으로 설정합니다.
 * 
 * @param   descriptor  | in | descriptor * | 디스크립터 객체 |
 * @param   buffer      | in | void *       | 버퍼 |
 * @param   size        | in | xuint64      | 버퍼의 크기 |
 * 
 * @return  | xint64 | 디스크립터 객체의 읽기 수행 결과 |
 * 
 *              읽기 수행에 성공하면, 그 읽은 버퍼의 크기를 리턴합니다.
 *              만약에, 디스크립터가 정상 상태이면서 읽은 버퍼가 없으면, 0 을 리턴하고,
 *              디스크립터의 상태에서 IN 이 제거됩니다.
 *              디스크립터가 존재하지 않거나 혹은 닫힌 디스크립터인 경우 그리고 읽기 수행에 실패한 경우는
 *              실패 (-1) 을 리턴합니다.
 * 
 */
extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
{
    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {
            if(buffer && size)
            {
                xint64 n = read(descriptor->handle.f, buffer, size);

                if(n > 0)
                {
                    descriptor->status |= xdescriptor_status_in;
                    xdescriptoreventpub(descriptor, xdescriptor_status_in, buffer, xvalgen(n));
                }
                else if(n == 0)
                {
                    xcheck(xtrue, "check this");
                    descriptor->status |= xdescriptor_status_exception;
                    xdescriptoreventpub(descriptor, xdescriptor_event_exception, xnil, xvalgen(0));
                    return xfail;
                }
                else
                {
                    int err = errno;
                    if(err == EAGAIN)
                    {
                        descriptor->status &= (~xdescriptor_status_in);
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(xtrue, "fail to read (%d)", err);
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptoreventpub(descriptor, xdescriptor_event_exception, xnil, xvalgen(err));
                        return xfail;
                    }
                }
            }
            else
            {
                xcheck(xtrue, "buffer is not avail");
                return xsuccess;
            }
        }
        else
        {
            xcheck(xtrue, "descriptor handle value is invalid");
        }
    }
    else
    {
        xcheck(xtrue, "descriptor is null");
    }

    return xfail;
}

/**
 * @fn      extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len)
 * @brief   디스크립터 객체의 쓰기를 수행합니다.
 * 
 *              디스크립터 객체의 쓰기를 수행하고 그 수행 결과가 존재하면,
 *              쓰여진 데이터의 바이트 수를 리턴합니다. 만약에,
 *              디스크립터 핸들러가 존재하면, 디스크립터의 이벤트 핸들러 수행 결과를 리턴합니다.
 *              디스크립터가 널이거나 닫힌 상태이면 실패를 리턴합니다.
 * 
 * @param   descriptor | in | descriptor * | 디스크립터 객체 |
 * @param   data       | in | const void * | 데이터 |
 * @param   len        | in | xuint64      | 데이터의 크기 |
 * 
 * @todo    `write` 함수의 리턴 값이 0 인 경우에 대해서 자료 조사 필요
 */
extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len)
{
    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {
            if(data && len)
            {
                xint64 n = write(descriptor->handle.f, data, len);

                if(n > 0)
                {
                    descriptor->status |= xdescriptor_status_out;
                    xdescriptoreventpub(descriptor, xdescriptor_event_out, xnil, xvalgen(n));
                    return n;
                }
                else if(n == 0)
                {
                    xcheck(xtrue, "check this");
                    return xsuccess;
                }
                else
                {
                    int err = errno;
                    if(err == EAGAIN)
                    {
                        descriptor->status &= (~xdescriptor_status_out);
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(xtrue, "fail to write (%d)", errno);
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptoreventpub(descriptor, xdescriptor_status_exception, xnil, xvalgen(err));
                        return xfail;
                    }
                }
            }
            else
            {
                xcheck(xtrue, "data is not avail");
                return xsuccess;
            }
        }
        else
        {
            xcheck(xtrue, "descriptor is not open");
        }
    }
    else
    {
        xcheck(xtrue, "descriptor is null");
    }
    return xfail;
}

extern void xdescriptormask_nonblock_on(xdescriptor * descriptor)
{
    if(descriptor)
    {
        descriptor->mask |= xdescriptor_mask_nonblock;
        xdescriptornonblock_on(descriptor);
    }
    else
    {
        xcheck(xtrue, "descriptor is null");
    }
}

extern void xdescriptormask_nonblock_off(xdescriptor * descriptor)
{
    if(descriptor)
    {
        descriptor->mask &= (~xdescriptor_mask_nonblock);
        xdescriptornonblock_off(descriptor);
    }
    else
    {
        xcheck(xtrue, "descriptor is null");
    }
}

extern xuint32 xdescriptorwait(xdescriptor * descriptor, xuint32 mask, xint64 second, xint64 nanosecond)
{
    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {

            struct pollfd   pollfd;
            struct timespec timeout = { 0, 1000 };

            xtime current   = xtimeget();
            xtime end       = xtimeset(current.second + second, current.nanosecond + nanosecond);
            xuint32 result  = 0;
            
            pollfd.fd       = descriptor->handle.f;
            pollfd.events   = __xdescriptor_internal_poll_mask_convert(mask);
            pollfd.events  |= (POLLERR | POLLHUP | POLLNVAL | POLLPRI | POLLRDHUP);
            pollfd.revents  = 0;

            mask           &= (xdescriptor_event_in | xdescriptor_event_out);

            while((result & mask) != mask)
            {
                int nfds = ppoll(&pollfd, 1, &timeout, xnil);

                if(nfds >= 0)
                {
                    if(pollfd.revents & (~(POLLIN | POLLOUT)))
                    {
                        return xdescriptor_event_exception;
                    }
                    if(pollfd.revents & POLLOUT)
                    {
                        result |= xdescriptor_event_out;
                    }
                    if(pollfd.revents & POLLIN)
                    {
                        result |= xdescriptor_event_in;
                    }
                    if((result & mask) != mask)
                    {
                        current = xtimeget();
                        if(xtimecmp(&current, &end) >= 0)
                        {
                            result |= xdescriptor_event_timeout;
                            return result;
                        }
                    }
                }
                else
                {
                    return xdescriptor_event_exception;
                }
            }
            return result;
        }
        else
        {
            xcheck(xtrue, "descriptor is not alive");
        }
    }
    else
    {
        xcheck(xtrue, "descriptor is null");
    }
    return xdescriptor_event_invalid;
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

// static inline xuint32 __xpoll_convert_mask_to_pollmask(xuint32 mask)
// {
//     xuint32 result = 0;
//     if(mask & xdescriptor_status_in)
//     {
//         result |= POLLIN;
//     }
//     if(mask & xdescriptor_status_out)
//     {
//         result |= POLLOUT;
//     }
//     if(mask & xdescriptor_status_exception)
//     {
//         result |= (POLLPRI | POLLRDHUP | POLLERR | POLLHUP | POLLNVAL);
//     }
//     else
//     {
//         if(mask & xdescriptor_status_read_hangup)
//         {
//             result |= POLLRDHUP;
//         }
//         if(mask & xdescriptor_status_pri)
//         {
//             result |= POLLPRI;
//         }
//         if(mask & xdescriptor_status_hangup)
//         {
//             result |= POLLHUP;
//         }
//         if(mask & xdescriptor_status_error)
//         {
//             result |= POLLERR;
//         }
//         if(mask & xdescriptor_status_invalid)
//         {
//             result |= POLLNVAL;
//         }
//     }
//     return result;
// }

// /**
//  * @fn      extern xint32 xdescriptorclose(xdescriptor * o)
//  * @brief   
//  * @details
//  * 
//  * 
//  */
// extern xint32 xdescriptorclose(xdescriptor * o)
// {
//     if(o)
//     {
//         if(o->handle.f >= 0)
//         {
//             int ret = close(o->handle.f);

//             if(ret == xsuccess)
//             {
//                 o->status |= xdescriptor_status_close;
//                 o->status &= (~(xdescriptor_status_open | xdescriptor_status_in | xdescriptor_status_out));

//                 xdescriptoreventpub(o, xdescriptor_event_close, o->parent, xvalgen(0));

//                 o->status = xdescriptor_event_void;

//                 o->handle.f = xinvalid;
//             }
//             else
//             {
//                 xassertion(xtrue, "fail to close (%d) - check this", errno);
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
//     return xsuccess;
// }

// extern xint32 xdescriptoralive(xdescriptor * o)
// {
//     return (o && o->handle.f >=0);
// }

// extern xint64 xdescriptorread(xdescriptor * o, void * buffer, xuint64 size)
// {
//     if(o)
//     {
//         if(o->handle.f >= 0)
//         {
//             // xcheck((o->status & xdescriptor_status_in) == xdescriptor_status_void, "not avail descriptor in");
//             if(buffer && size)
//             {
//                 xint64 n = read(o->handle.f, buffer, size);
//                 if(n > 0)
//                 {
//                     o->status |= xdescriptor_status_in;
//                     xdescriptoreventpub(o, xdescriptor_event_in, o->parent, xvalgen(n));
//                     return n;
//                 }
//                 else if(n == 0)
//                 {
//                     xcheck(xtrue, "read return zero (may be closed)");
//                     o->status |= xdescriptor_event_exception;
//                     // TODO: CHECK CLOSE ??????????
//                     xdescriptoreventpub(o, xdescriptor_event_exception, o->parent, xvalgen(0));
//                     return xfail;
//                 }
//                 else
//                 {
//                     int err = errno;
//                     if(err == EAGAIN)
//                     {
//                         o->status &= (~xdescriptor_status_in);
//                         return 0;
//                     }
//                     else
//                     {
//                         xcheck(xtrue, "fail to read (%d)", err);
//                         o->status |= xdescriptor_event_exception;
//                         xdescriptoreventpub(o, xdescriptor_event_exception, o->parent, xvalgen(err));
//                         return xfail;
//                     }
//                 }
//             }
//             else
//             {
//                 xcheck(xtrue, "buffer not exist");
//                 return xsuccess;
//             }
//         }
//         else
//         {
//             xcheck(xtrue, "not alive descriptor");
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
//     return xfail;
// }

// extern xint64 xdescriptorwrite(xdescriptor * o, const void * data, xuint64 length)
// {
//     if(o)
//     {
//         if(o->handle.f >= 0)
//         {
//             if(data && length)
//             {
//                 // xcheck((o->status & xdescriptor_status_out) == xdescriptor_status_void, "descriptor not avail write");
//                 xint64 n = write(o->handle.f, data, length);
//                 if(n > 0)
//                 {
//                     o->status |= xdescriptor_status_out;
//                     xdescriptoreventpub(o, xdescriptor_event_out, o->parent, xvalgen(n));
//                     return n;
//                 }
//                 else if(n == 0)
//                 {
//                     // PRINT ALL 
//                     xcheck(xtrue, "check this logic");
//                     return xsuccess;
//                 }
//                 else
//                 {
//                     int err = errno;
//                     if(err == EAGAIN)
//                     {
//                         o->status &= (~xdescriptor_status_out);
//                         return xsuccess;
//                     }
//                     else
//                     {
//                         xcheck(xtrue, "fail to write (%d)", err);
//                         o->status |= xdescriptor_event_exception;
//                         xdescriptoreventpub(o, xdescriptor_event_exception, o->parent, xvalgen(err));
//                         return xfail;
//                     }
//                 }
//             }
//             else
//             {
//                 xcheck(xtrue, "no available data");
//                 return xsuccess;
//             }
//         }
//         else
//         {
//             xcheck(xtrue, "not alive descriptor");
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
//     return xfail;
// }

// extern xint32 xdescriptornonblock_on(xdescriptor * o)
// {
//     if(o)
//     {
//         if(o->handle.f >= 0)
//         {
//             int flags = fcntl(o->handle.f, F_GETFL, 0);

//             xassertion(flags == xfail, "fail to fcntl (%d)", errno);

//             flags |= O_NONBLOCK;

//             int ret = fcntl(o->handle.f, F_SETFL, flags);

//             xassertion(ret == xfail, "fail to fcntl (%d)", errno);

//             return xsuccess;
//         }
//         else
//         {
//             xcheck(xtrue, "not alive descriptor");
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
//     return xfail;
// }

// extern xint32 xdescriptornonblock_off(xdescriptor * o)
// {
//     if(o)
//     {
//         if(o->handle.f >= 0)
//         {
//             int flags = fcntl(o->handle.f, F_GETFL, 0);

//             xassertion(flags == xfail, "fail to fcntl (%d)", errno);

//             flags &= (~O_NONBLOCK);

//             int ret = fcntl(o->handle.f, F_SETFL, flags);

//             xassertion(ret == xfail, "fail to fcntl (%d)", errno);

//             return xsuccess;
//         }
//         else
//         {
//             xcheck(xtrue, "not alive descriptor");
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
//     return xfail;
// }

// extern xdescriptorio * xdescriptorionew(xuint32 type, xdestructor destructor, xuint64 memorysize)
// {
//     // TODO: TYPE CHECK
//     xassertion(memorysize < sizeof(xdescriptorio) || destructor == xnil, "invalid parameter");

//     xdescriptorio * o = (xdescriptorio *) calloc(memorysize, 1);
//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     o->flags = (xobj_mask_allocated | type);
//     o->destruct = destructor;

//     return o;
// }

// extern void xdescriptorioadd(xdescriptorio * o, xdescriptor * descriptor)
// {
//     if(o && descriptor)
//     {
//         xsynclock(descriptor->sync);
//         if(descriptor->io == xnil)
//         {
//             xsynclock(o->sync);
//             descriptor->io = o;
//             descriptor->prev = o->tail;
//             o->tail = descriptor;
//             if(descriptor->prev)
//             {
//                 descriptor->prev->next = descriptor;
//             }
//             else
//             {
//                 o->head = descriptor;
//             }
//             o->total = o->total + 1;
//             xsyncunlock(o->sync);
//         }
//         else
//         {
//             xcheck(xtrue, "parent io facility is exist");
//         }
//         xsyncunlock(descriptor->sync);
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
// }

// extern void xdescriptoriodel(xdescriptorio * o, xdescriptor * descriptor)
// {
//     if(o && descriptor)
//     {
//         xsynclock(descriptor->sync);
//         xcheck(o != descriptor->io, "invalid io facility");
//         if(descriptor->io)
//         {
//             o = descriptor->io;
//             xsynclock(o->sync);
//             xdescriptor * prev = descriptor->prev;
//             xdescriptor * next = descriptor->next;
//             if(prev)
//             {
//                 prev->next = next;
//             }
//             else
//             {
//                 o->head = next;
//             }
//             if(next)
//             {
//                 next->prev = prev;
//             }
//             else
//             {
//                 o->tail = prev;
//             }
//             o->total = o->total - 1;
//             descriptor->io = xnil;
//             descriptor->prev = xnil;
//             descriptor->next = xnil;
//             xsyncunlock(o->sync);
//         }
//         else
//         {
//             xcheck(xtrue, "descriptor's io facility is not exist");
//         }
//         xsyncunlock(descriptor->sync);
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
// }

// extern void xdescriptorioclear(xdescriptorio * o)
// {
//     if(o)
//     {
//         xsynclock(o->sync);
//         while(o->head)
//         {
//             xdescriptor * descriptor = o->head;
//             o->head = o->head->next;
//             descriptor->next = xnil;
//             descriptor->io = xnil;
//             o->total = o->total - 1;
//             if(o->head)
//             {
//                 o->head->prev = xnil;
//             }
//             else
//             {
//                 o->tail = xnil;
//             }
//         }
//         xsyncunlock(o->sync);
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
// }

// extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 second, xuint64 nanosecond)
// {
//     if(o)
//     {
//         if(o->handle.f >= 0)
//         {
//             if(mask)
//             {
//                 struct pollfd data;
//                 data.fd      = o->handle.f;
//                 data.events  = __xpoll_convert_mask_to_pollmask(mask);
//                 data.revents = 0;

//                 xtime start  = xtimeget();
//                 xtime end    = xtimeset(start.second + second, start.nanosecond + nanosecond);

//                 xuint32 result = xdescriptor_event_void;

//                 while((result & mask) != mask)
//                 {
//                     data.revents = 0;
//                     struct timespec timeout = { 0, 1000 };      // 1 unisecond
//                     int nfds = ppoll(&data, 1, &timeout, xnil); // TODO: SIGNAL HANDLING
//                     if(nfds >= 0)
//                     {
//                         if(data.revents & POLLIN)
//                         {
//                             result |= xdescriptor_event_in;
//                         }
//                         if(data.revents & POLLOUT)
//                         {
//                             result |= xdescriptor_event_out;
//                         }
//                         if(data.revents & POLLPRI)
//                         {
//                             result |= (xdescriptor_event_pri | xdescriptor_event_exception);
//                         }
//                         if(data.revents & POLLRDHUP)
//                         {
//                             result |= (xdescriptor_event_read_hangup | xdescriptor_event_exception);
//                         }
//                         if(data.revents & POLLERR)
//                         {
//                             result |= (xdescriptor_event_error | xdescriptor_event_exception);
//                         }
//                         if(data.revents & POLLHUP)
//                         {
//                             result |= (xdescriptor_event_hangup | xdescriptor_event_exception);
//                         }
//                         if(data.revents & POLLNVAL)
//                         {
//                             result |= (xdescriptor_event_invalid | xdescriptor_event_exception);
//                         }
//                         if(result & xdescriptor_event_exception)
//                         {
//                             // TODO: CHECK OTHER EXCEPTION ...
//                             return result;
//                         }
//                         else
//                         {
//                             if((result & mask) != mask && (second > 0 || nanosecond > 0))
//                             {
//                                 xtime current = xtimeget();
//                                 if(xtimecmp(&current, &end) >= 0)
//                                 {
//                                     result |= xdescriptor_event_timeout;
//                                     return result;
//                                 }
//                             }
//                         }
//                     }
//                     else
//                     {
//                         xassertion(xtrue, "fail to poll (%d)", errno);
//                     }
//                 }
//                 return result;
//             }
//             else
//             {
//                 xcheck(xtrue, "no event mask");
//                 return xdescriptor_event_void;
//             }
//         }
//         else
//         {
//             xcheck(xtrue, "not alive descriptor");
//             return xdescriptor_event_exception;
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//         return xdescriptor_event_exception;
//     }
// }


// extern void xdescriptorset_nonblock_on(xdescriptor * o)
// {
//     if(o)
//     {
//         if((o->mask & xdescriptor_mask_nonblock) == xdescriptor_mask_void)
//         {
//             o->mask |= xdescriptor_mask_nonblock;
//             if(o->handle.f >= 0)
//             {
//                 xdescriptornonblock_on(o);
//             }
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
// }

// extern void xdescriptorset_nonblock_off(xdescriptor * o)
// {
//     if(o)
//     {
//         if(o->mask & xdescriptor_mask_nonblock)
//         {
//             o->mask &= (~xdescriptor_mask_nonblock);
//             if(o->handle.f >= 0)
//             {
//                 xdescriptornonblock_off(o);
//             }
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
// }

// // // extern xint32 xdescriptorclose(xdescriptor * o)
// // // {
// // //     xcheck(o == xnil, "null pointer");
// // //     if(o)
// // //     {
// // //         xcheck((o->value.f >= 0) == xfalse, "socket not opened");

// // //         if(o->value.f >= 0)
// // //         {
// // //             if(close(o->value.f) != xsuccess)
// // //             {
// // //                 xassertion(xtrue, "fail to close (%d)", errno);
// // //             }
// // //             o->value.f = xinvalid;
// // //         }
// // //         return xsuccess;
// // //     }
// // //     return xfail;
// // // }

// // // extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 nanosecond)
// // // {
// // //     if(o)
// // //     {
// // //         if(o->value.f >= 0)
// // //         {
// // //             struct pollfd fds = { xinvalid, 0, 0 };
// // //             fds.fd = o->value.f;
// // //             if(mask & xdescriptor_event_read)
// // //             {
// // //                 fds.events |= POLLIN;
// // //             }
// // //             if(mask & xdescriptor_event_write)
// // //             {
// // //                 fds.events |= POLLOUT;
// // //             }
// // //             if(mask & xdescriptor_event_error)
// // //             {
// // //                 fds.events |= POLLERR;
// // //             }
// // //             if(mask & xdescriptor_event_pri)
// // //             {
// // //                 fds.events |= POLLPRI;
// // //             }
// // //             if(mask & xdescriptor_event_readhup)
// // //             {
// // //                 fds.events |= POLLRDHUP;
// // //             }
// // //             if(mask & xdescriptor_event_hup)
// // //             {
// // //                 fds.events |= POLLHUP;
// // //             }
// // //             if(mask & xdescriptor_event_invalid)
// // //             {
// // //                 fds.events |= POLLNVAL;
// // //             }
// // //             if(mask & xdescriptor_event_readband)
// // //             {
// // //                 fds.events |= POLLRDBAND;
// // //             }
// // //             if(mask & xdescriptor_event_writeband)
// // //             {
// // //                 fds.events |= POLLWRBAND;
// // //             }
// // //             int result = xdescriptor_event_void;
// // //             struct timespec start = { 0, 0};
// // //             struct timespec current = { 0, 0 };
// // //             struct timespec diff = { 0, 0};
// // //             clock_gettime(CLOCK_REALTIME, &start);  // TODO: CHECK FAIL
// // //             struct timespec timespec = { 0, 1000 };
// // //             while((result & mask) != mask)
// // //             {
// // //                 int nfds = ppoll(&fds, 1, &timespec, xnil);
// // //                 if(nfds >= 0)
// // //                 {
// // //                     /**
// // //                      * TODO: 마스크 처리하는데 시간이 많이 걸린다.
// // //                      * 어떻게 하면 STD 라이브러리 헤더 없이 ....
// // //                      */
// // //                     if(fds.revents & POLLIN)
// // //                     {
// // //                         result |= xdescriptor_event_read;
// // //                     }
// // //                     if(fds.revents & POLLOUT)
// // //                     {
// // //                         result |= xdescriptor_event_write;
// // //                     }
// // //                     if(fds.revents & POLLPRI)
// // //                     {
// // //                         result |= xdescriptor_event_pri;
// // //                     }
// // //                     if(fds.revents & POLLERR)
// // //                     {
// // //                         result |= xdescriptor_event_error;
// // //                     }
// // //                     if(fds.revents & POLLRDHUP)
// // //                     {
// // //                         result |= xdescriptor_event_readhup;
// // //                     }
// // //                     if(fds.revents & POLLHUP)
// // //                     {
// // //                         result |= xdescriptor_event_hup;
// // //                     }
// // //                     if(fds.revents & POLLRDBAND)
// // //                     {
// // //                         result |= xdescriptor_event_readband;
// // //                     }
// // //                     if(fds.revents & POLLWRBAND)
// // //                     {
// // //                         result |= xdescriptor_event_writeband;
// // //                     }
// // //                     if(fds.revents & POLLNVAL)
// // //                     {
// // //                         result |= xdescriptor_event_invalid;
// // //                     }
// // //                     clock_gettime(CLOCK_REALTIME, &current);
// // //                     diff.tv_sec = current.tv_sec - start.tv_sec;
// // //                     diff.tv_nsec = current.tv_nsec - start.tv_nsec;
// // //                     if(diff.tv_nsec < 0)
// // //                     {
// // //                         diff.tv_sec = diff.tv_sec - 1;
// // //                         diff.tv_nsec = 1000000000 + diff.tv_nsec;
// // //                     }
// // //                     // check overflow
// // //                     if((result & mask) != mask)
// // //                     {
// // //                         if(nanosecond < xtimenanosecond(diff.tv_sec, diff.tv_nsec))
// // //                         {
// // //                             result |= xdescriptor_event_timeout;
// // //                             return result;
// // //                         }
// // //                     }
// // //                 }
// // //                 else
// // //                 {
// // //                     xassertion(xtrue, "fail to ppoll (%d)", errno);
// // //                     return xdescriptor_event_except;
// // //                 }
// // //             }
// // //             return result;
// // //         }
// // //         else
// // //         {
// // //             xcheck(xtrue, "socket is not alive");
// // //         }
// // //     }
// // //     else
// // //     {
// // //         xcheck(xtrue, "null pointer");
// // //     }
// // //     return xdescriptor_event_except;
// // // }