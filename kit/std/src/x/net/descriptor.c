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

extern void xdescriptordebug_event_mask(xuint32 mask)
{
    if(mask == xdescriptor_event_void)
    {
        printf("descriptor event void\n");
    }
    else
    {
        if(mask & xdescriptor_event_in)
        {
            printf("xdescriptor_event_in\n");
        }
        if(mask & xdescriptor_event_out)
        {
            printf("xdescriptor_event_out\n");
        }
        if((mask & xdescriptor_event_closeall) == xdescriptor_event_closeall)
        {
            printf("xdescriptor_event_closeout\n");
        }
        else
        {
            if(mask & xdescriptor_event_closein)
            {
                printf("xdescriptor_event_closein\n");
            }
            if(mask & xdescriptor_event_closeout)
            {
                printf("xdescriptor_event_closeout\n");
            }
        }
        if(mask & xdescriptor_event_close)
        {
            printf("xdescriptor_event_close\n");
        }
        if(mask & xdescriptor_event_exception)
        {
            printf("xdescriptor_event_exception\n");
        }
        if(mask & xdescriptor_event_open)
        {
            printf("xdescriptor_event_open\n");
        }
        if(mask & xdescriptor_event_connect)
        {
            printf("xdescriptor_event_connect\n");
        }
        if(mask & xdescriptor_event_connecting)
        {
            printf("xdescriptor_event_connecting\n");
        }
        if(mask & xdescriptor_event_invalid)
        {
            printf("xdescriptor_event_invalid\n");
        }
        if(mask & xdescriptor_event_timeout)
        {
            printf("xdescriptor_event_timeout\n");
        }
        if(mask & xdescriptor_event_bind)
        {
            printf("xdescriptor_event_bind\n");
        }
        if(mask & xdescriptor_event_listen)
        {
            printf("xdescriptor_event_listen\n");
        }
    }
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
                descriptor->handle.f  = xinvalid;
                descriptor->status   |= xdescriptor_status_close;
                descriptor->status   &= (~(xdescriptor_status_in | xdescriptor_status_out));
                xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_event_close, descriptor->data, xvalgen(0));
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
                    xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_status_in, buffer, xvalgen(n));
                    return n;
                }
                else if(n == 0)
                {
                    xcheck(xtrue, "check this");
                    descriptor->status |= xdescriptor_status_exception;
                    xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_event_exception, xnil, xvalgen(0));
                    return xfail;
                }
                else
                {
                    int err = errno;
                    if(err == EAGAIN)
                    {
                        descriptor->status &= (~xdescriptor_status_in);
                        if(descriptor->io)
                        {
                            xdescriptorioreg(descriptor->io, descriptor);
                        }
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(xtrue, "fail to read (%d)", err);
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_event_exception, xnil, xvalgen(err));
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
                    xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_event_out, xnil, xvalgen(n));
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
                        if(descriptor->io)
                        {
                            xdescriptorioreg(descriptor->io, descriptor);
                        }
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(xtrue, "fail to write (%d)", errno);
                        descriptor->status |= xdescriptor_status_exception;
                        xdescriptoreventpub(descriptor, descriptor->data, xdescriptor_status_exception, xnil, xvalgen(err));
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
