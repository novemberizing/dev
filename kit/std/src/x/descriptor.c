#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "descriptor.h"

extern xint64 xdescriptor_read(xdescriptor * descriptor, void * buffer, xuint64 size)
{
    xassertion(descriptor == xnil, "descriptor is null");
    xassertion(descriptor->handle.f < 0, "descriptor is not open");

    if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
    {
        if(buffer && size)
        {
            xint64 n = read(descriptor->handle.f, buffer, size);
            if(n > 0)
            {
                descriptor->status |= xdescriptor_status_in;
                xint64 ret = xdescriptor_event_on(descriptor, xdescriptor_event_in, buffer, n);
                if(ret < 0)
                {
                    descriptor->status |= xdescriptor_status_exception;
                    xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                }
                return ret;
            }
            else if(n == 0)
            {
                xcheck(n == 0, "fail to read (0)");
                descriptor->status &= (~xdescriptor_status_in);
                descriptor->status |= xdescriptor_status_exception;
                xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                return xfail;
            }
            else
            {
                descriptor->status &= (~xdescriptor_status_in);
                int err = errno;
                if(err == EAGAIN)
                {
                    return xsuccess;
                }
                else
                {
                    xcheck(err != EAGAIN, "fail to read (%d)", err);
                    descriptor->status |= xdescriptor_status_exception;
                    xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, err);
                    return xfail;
                }
            }
        }
    }
    
    return xsuccess;
}

extern xint64 xdescriptor_write(xdescriptor * descriptor, const void * data, xuint64 len)
{
    xassertion(descriptor == xnil, "descriptor is null");
    xassertion(descriptor->handle.f < 0, "descriptor is not open");

    if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
    {
        if(data && len)
        {
            xint64 n = write(descriptor->handle.f, data, len);
            if(n > 0)
            {
                descriptor->status |= xdescriptor_status_out;
                xint64 ret = xdescriptor_event_on(descriptor, xdescriptor_event_out, data, n);
                if(ret < 0)
                {
                    descriptor->status |= xdescriptor_status_exception;
                    xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, 0);
                }
                return ret;
            }
            else if(n == 0)
            {
                xassertion(n == 0, "check this");
                return xsuccess;
            }
            else
            {
                descriptor->status &= (~xdescriptor_status_out);
                int err = errno;
                if(err == EAGAIN)
                {
                    return xsuccess;
                }
                else
                {
                    xcheck(err != EAGAIN, "fail to write (%d)", err);
                    descriptor->status |= xdescriptor_status_exception;
                    xdescriptor_event_on(descriptor, xdescriptor_event_exception, xnil, err);
                    return xfail;
                }
            }
        }
    }
    
    return xsuccess;
}

extern xint64 xdescriptor_close(xdescriptor * descriptor)
{
    xassertion(descriptor == xnil, "descriptor is null");

    if(descriptor->handle.f >= 0)
    {
        int ret = close(descriptor->handle.f);

        if(ret != xsuccess)
        {
            xassertion(ret != xsuccess, "fail to close (%d)", errno);
        }

        descriptor->status |= xdescriptor_status_close;
        xdescriptor_event_on(descriptor, xdescriptor_event_close, xnil, 0);
        descriptor->handle.f = xinvalid;
        descriptor->status  = xdescriptor_status_void;
    }
    else
    {
        xassertion(descriptor->handle.f < 0, "descriptor is not open");
    }
    return xsuccess;
}
