#include "descriptor.h"
#include "descriptor/subscription.h"
#include "descriptor/event/generator.h"

static inline xint64 xdescriptorevent_finish_close(xdescriptor * descriptor, const void * data, xuint64 size, xint64 result)
{
    /** 
     * 이미 프로세스에서 제네레이터에서 삭제하고 모든 것을 끝냈을 것이다.
     * 다만, 디스크립터가 서버인 경우 다시 바인딩하고 리슨을 수행하고
     * 클라이언트의 경우 다시 다시 접속하고, 세션의 경우 릴리즈한다.
     * 
     * 종료 이벤트는 사용자 요청에 의해서만 발생한다.
     * 그 외의 이벤트들은 엔진에서의 종료는 예외를 통해서만 이루어진다.
     * 
     * CLOSE 이벤트가 발생했다는 것은 사용자가 close 를 호출하였기 때문이다.
     * 그렇기 때문에, 모두 종료하고 서브스크립션을 삭제한다.
     */
    return result;
}

static inline xint64 xdescriptorevent_finish_exception(xdescriptor * descriptor, const void * data, xuint64 size, xint64 result)
{
    /** 
     * 이미 프로세스에서 제네레이터에서 삭제하고 모든 것을 끝냈을 것이다.
     * 다만, 디스크립터가 서버인 경우 다시 바인딩하고 리슨을 수행하고
     * 클라이언트의 경우 다시 다시 접속하고, 세션의 경우 릴리즈한다.
     */
    return result;
}

/**
 * 
 * @details     이 함수를 호출하기 전에 result 값에 따라서 예외를 처리하기 때문에,
 *              이 곳에서의 result 변수 값은 항상 성공을 뜻하는 값입니다.
 */
static inline xint64 xdescriptorevent_finish_in(xdescriptor * descriptor, const void * data, xuint64 size, xint64 result)
{
    /**
     * 이 함수는 이미 성공적인 이벤트 수행을 마친 것이다.
     */
    if(descriptor->status & xdescriptor_status_in)
    {
        if(descriptor->subscription)
        {
            xeventengine * engine = descriptor->subscription->enginenode.engine;
            xeventengine_event_push(engine, xeventcategory_descriptor, xdescriptor_event_in, descriptor);
        }
    }
    else
    {
        // 디스크립터 이벤트 제네레이터에 등록합니다.
        if(descriptor->subscription)
        {
            if(xdescriptorevent_subscription_renewal(descriptor->subscription)!=xsuccess)
            {
                xdescriptorevent_dispatch(descriptor, xdescriptor_event_exception, xnil, 0);
                return xfail;
            }
        }
    }
    return result;
}

static inline xint64 xdescriptorevent_finish_out(xdescriptor * descriptor, const void * data, xuint64 size, xint64 result)
{
    /**
     * 이 함수는 이미 성공적인 이벤트 수행을 마친 것이다.
     */
    if(descriptor->status & xdescriptor_status_out)
    {
        if(descriptor->subscription && xdescriptorexist_out(descriptor))
        {
            xeventengine * engine = descriptor->subscription->enginenode.engine;
            xeventengine_event_push(engine, xeventcategory_descriptor, xdescriptor_event_in, descriptor);
        }
    }
    else
    {
        // 디스크립터 이벤트 제네레이터에 등록합니다.
        if(descriptor->subscription)
        {
            if(xdescriptorevent_subscription_renewal(descriptor->subscription)!=xsuccess)
            {
                xdescriptorevent_dispatch(descriptor, xdescriptor_event_exception, xnil, 0);
                return xfail;
            }
        }
    }
    return result;
}

static inline xint64 xdescriptorevent_finish_open(xdescriptor * descriptor, const void * data, xuint64 size, xint64 result)
{
    if(xdescriptorexist_out(descriptor))
    {
        xint64 ret = xdescriptorevent_dispatch(descriptor, xdescriptor_event_out, xnil, 0);
        if(ret != xsuccess)
        {
            return ret;
        }
    }
    if(xdescriptorevent_subscription_open(descriptor->subscription) != xsuccess)
    {
        if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
        {
            descriptor->status |= xdescriptor_status_exception;
            xdescriptorevent_dispatch(descriptor, xdescriptor_event_exception, xnil, 0);
        }
        return xfail;
    }
    return result;
}

extern xint64 xdescriptorevent_dispatch(xdescriptor * descriptor, xuint32 event, const void * data, xuint64 size)
{
    xint64 ret = xdescriptorevent_process(descriptor, event, data, size);
    return xdescriptorevent_finish(descriptor, event, data, size, ret);
}

extern xint64 xdescriptorevent_process(xdescriptor * descriptor, xuint32 event, const void * data, xuint64 size)
{
    xint64 ret = descriptor->process(descriptor, event, data, size);
    return descriptor->on(descriptor, event, data, size, ret);
}

extern xint64 xdescriptorevent_finish(xdescriptor * descriptor, xuint32 event, const void * data, xuint64 size, xint64 result)
{
    if(result < 0)
    {
        if((descriptor->status & xdescriptor_status_exception) == xdescriptor_status_void)
        {
            descriptor->status |= xdescriptor_status_exception;
            xdescriptorevent_dispatch(descriptor, xdescriptor_event_exception, xnil, 0);
        }
    }
    else
    {
        switch(event)
        {
            case xdescriptor_event_in:          return xdescriptorevent_finish_in(descriptor, data, size, result);
            case xdescriptor_event_out:         return xdescriptorevent_finish_out(descriptor, data, size, result);
            case xdescriptor_event_open:        return xdescriptorevent_finish_open(descriptor, data, size, result);
            case xdescriptor_event_close:       return xdescriptorevent_finish_close(descriptor, data, size, result);
            case xdescriptor_event_exception:   return xdescriptorevent_finish_exception(descriptor, data, size, result);
        }
    }
    return result;
}