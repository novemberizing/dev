#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "std.h"
#include "descriptor.h"

extern xdescriptor * xdescriptor_new(xint32 f, xdescriptor_event_handler handler, xdescriptor_event_processor processor, xdescriptor_opener opener)
{
    xdescriptor * descriptor = (xdescriptor *) calloc(sizeof(xdescriptor), 1);

    if(descriptor)
    {
        descriptor->handle.f = f;
        descriptor->process  = processor;
        descriptor->on       = handler;
        descriptor->open     = opener;
    }
    else
    {
        xassertion(descriptor == xnil, "fail to calloc (%d)", errno);
    }

    return descriptor;
}

/**
 * 이 함수는 모든 것을 제거한 후에 호출되어져야 한다.
 * 스레드 세이프티를 보장하려면 내부에서 락과 언락을 수행하면 
 * 다른 로직에서 문제가 발생할 수 있다.
 */
extern xdescriptor * xdescriptor_rem(xdescriptor * descriptor)
{
    if(descriptor)
    {
        xassertion(descriptor->handle.f >= 0, "descriptior must close");
        xassertion(descriptor->prev || descriptor->next || descriptor->io, "descriptior must unregister");

        free(descriptor);
        descriptor = xnil;
    }
    else
    {
        xcheck(descriptor == xnil, "descriptor is null");
    }

    return descriptor;
}

extern xint32 xdescriptor_close(xdescriptor * descriptor)
{
    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {
            int ret = close(descriptor->handle.f);
            if(ret != xsuccess)
            {
                xassertion(ret != xsuccess, "fail to close (%d)", errno);
            }

            descriptor->handle.f  = xinvalid;
            descriptor->status   |= xdescriptor_status_close;
            xdescriptoreventpub(descriptor, xdescriptor_event_close, xnil, 0);
            descriptor->status    = xdescriptor_status_void;
        }
        return xsuccess;
    }
    else
    {
        xassertion(descriptor == xnil, "descriptor is null");
    }
    return xfail;
}

extern xint64 xdescriptor_read(xdescriptor * descriptor, void * buffer, xuint64 size)
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
                    xdescriptoreventpub(descriptor, xdescriptor_event_in, buffer, n);
                    return n;
                }
                else if(n == 0)
                {
                    return xfail;
                }
                else
                {
                    int err = errno;
                    if(err == EAGAIN)
                    {
                        // 다시 등록하는 것은 다른 곳에서 하자.
                        descriptor->status &= (~xdescriptor_status_in);
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(xtrue, "fail to read (%d)", err);
                        return xfail;
                    }
                }
            }
            else
            {
                xcheck(buffer == xnil || size == 0, "buffer is null or buffer's size is zero");
                return xsuccess;
            }
        }
        else
        {
            xcheck(descriptor->handle.f < 0, "descriptor is not alive");
        }
    }
    else
    {
        xcheck(descriptor == xnil, "descriptor is null");
    }

    return xfail;
}

extern xint64 xdescriptor_write(xdescriptor * descriptor, const void * data, xuint64 len)
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
                    xdescriptoreventpub(descriptor, xdescriptor_event_out, data, n);
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
                        // 다시 등록하는 것은 다른 곳에서 하자.
                        descriptor->status &= (~xdescriptor_status_out);
                        return xsuccess;
                    }
                    else
                    {
                        xcheck(xtrue, "fail to write (%d)", err);
                        return xfail;
                    }
                }
            }
            else
            {
                return xsuccess;
            }
        }
        else
        {
            xcheck(descriptor->handle.f < 0, "descriptor is not alive");
        }
    }
    else
    {
        xcheck(descriptor == xnil, "descriptor is null");
    }

    return xfail;
}