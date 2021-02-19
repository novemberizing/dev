#include <errno.h>

#include "descriptor.h"

extern void xdescriptorevent_dispatch_close(xdescriptor * descriptor)
{
    // subscription 이 존재하면 main event queue 에 삽입한다.
    if(descriptor->subscription)
    {
        if(descriptor->handle.f >= 0)
        {
            // 디스크립터 제네레이터에 등록이 되어 있다면, GENERATOR 에서 삭제한다.

        }
        // 이 상황은 항상 클로우즈 상황으로 이 상황이 발생하면 두번 호출된 케이스이다.
        xassertion(xtrue, "");
        return xsuccess;
    }
    else
    {
        return xdescriptorclose(descriptor);
    }
}

extern void xdescriptorevent_dispatch_exception(xdescriptor * descriptor, void * data, xint64 result)
{
    // subscription 이 존재하면 main event queue 에 삽입한다.
}

static xint64 xdescriptorevent_on_close(xdescriptor * descriptor, void * data, xuint64 result)
{
    if((descriptor->status & xdescriptorstatus_close) == xdescriptorstatus_void)
    {
        descriptor->status |= xdescriptorstatus_close;
        return descriptor->on(descriptor, xdescriptoreventmask_close, xnil, result);
    }
    return result;
}

static xint64 xdescriptorevent_on_exception(xdescriptor * descriptor, void * data, xuint64 result)
{
    if((descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
    {
        if(descriptor->subscription)
        {
            xassertion(xtrue, "implement this");
        }
        descriptor->status |= xdescriptorstatus_exception;
        return descriptor->on(descriptor, xdescriptoreventmask_exception, xnil, result);
    }
    return result;
}

extern xint64 xdescriptorclose(xdescriptor * descriptor)
{
    // 이 함수는 SUBSCRIPTION 에 GENERATOR 노드가 등록되어 있다면,
    // 즉, 등록된 상태라면 동작하지 않아야 한다. 즉, 상태를 UNREGISTER 상태여야만 한다.
    xassertion(descriptor == xnil, "");

    if(descriptor->handle.f >= 0)
    {
        xassertion(descriptor->status & xdescriptorstatus_register, "");

        int ret = close(descriptor->handle.f);

        descriptor->handle.f = xinvalid;

        if(ret == xsuccess)
        {
            return xdescriptorevent_on_close(descriptor, xnil, 0);
        }
        else
        {
            return xdescriptorevent_on_close(descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_close_fail]), errno);
        }
    }
    return xsuccess;
}

extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size)
{
    xassertion(descriptor == xnil, "");

    if(descriptor->handle.f >= 0)
    {
        if(!xdescriptorstatus_has(xdescriptorstatus_exception))
        {
            if(buffer && size)
            {
                xint64 n = read(descriptor->handle.f, buffer, size);
                if(n > 0)
                {
                    descriptor->status |= xdescriptorstatus_in;
                    return  descriptor->on(descriptor, xdescriptoreventmask_in, buffer, n);
                }
                else if(n == 0)
                {
                    // 다른 이벤트가 등록되어 있을 수 있기 때문에, DISPATCH 를 수행해야 한다.
                    descriptor->status &= (~xdescriptorstatus_in);
                    xdescriptorevent_dispatch_exception(descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_read_return_zero]), 0);
                }
                else
                {
                    descriptor->status &= (~xdescriptorstatus_in);
                    if(errno == EAGAIN)
                    {
                        return descriptor->on(descriptor, xdescriptoreventmask_in, xnil, 0);
                    }
                    xdescriptorevent_dispatch_exception(descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_read_fail]), errno);
                }
                return xfail;
            }
            return xsuccess;
        }
    }
    return xfail;
}

extern xint64 xdescriptorwrite(xdescriptor * descriptor, void * data, xuint64 len)
{
    xassertion(descriptor == xnil, "");

    if(descriptor->handle.f >= 0)
    {
        if(!xdescriptorstatus_has(xdescriptorstatus_exception))
        {
            if(data && len)
            {
                xint64 n = write(descriptor->handle.f, data, len);
                if(n > 0)
                {
                    descriptor->status |= xdescriptorstatus_out;
                    return descriptor->on(descriptor, xdescriptoreventmask_out, data, n);
                }
                else if(n == 0)
                {
                    xassertion(xtrue, "check this");
                    /**
                     * 이 상황에 대해서 매뉴얼 페이지를 보고 어떤 상황인지 확인해보자.
                     */
                    return descriptor->on(descriptor, xdescriptoreventmask_out, xnil, 0);
                }
                else
                {
                    descriptor->status &= (~xdescriptorstatus_out);
                    if(errno == EAGAIN)
                    {
                        return descriptor->on(descriptor, xdescriptoreventmask_out, xnil, 0);
                    }
                    xdescriptorevent_dispatch_exception(descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_write_fail]), errno);
                }
                return xfail;
            }
            return xsuccess;
        }
    }
    return xfail;
}