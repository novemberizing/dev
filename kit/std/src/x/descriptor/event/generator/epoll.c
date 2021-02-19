#include <errno.h>

#include "./epoll.h"

#include "../../descriptor.h"
#include "../subscription.h"
#include "../generator/subscriptions.h"

static inline xint32 xdescriptoreventgenerator_epoll_unregister(int epollfd, xdescriptoreventsubscription * subscription, xint32 force)
{
    if(epollfd >= 0)
    {
        xdescriptor * descriptor = subscription->descriptor;
        if(descriptor->handle.f >= 0)
        {
            if((descriptor->status & xdescriptorstatus_register) || force)
            {
                int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);
                if(ret != xsuccess)
                {
                    xassertion(force == xfalse, "");
                }
                if(descriptor->status & xdescriptorstatus_register)
                {
                    descriptor->on(descriptor, xdescriptoreventmask_register, xobjectof(xfalse), 0);
                }
                return force ? xsuccess : ret;
            }
        }
    }
    return xsuccess;
}

static inline xint32 xdescriptoreventgenerator_epoll_update(int epollfd, xdescriptoreventsubscription * subscription, xint32 force)
{

}

static inline xint32 xdescriptoreventgenerator_epoll_register(int epollfd, xdescriptoreventsubscription * subscription)
{
    if(epollfd >= 0)
    {
        xdescriptor * descriptor = subscription->descriptor;

        xassertion(descriptor->handle.f < 0, "");
        xassertion((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void, "");
        xassertion(descriptor->status & xdescriptorstatus_exception, "");
        xassertion(descriptor->status & xdescriptorstatus_close, "");

        struct epoll_event event;
        event.events = (EPOLLERR | EPOLLPRI | EPOLLHUP | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);
        event.data.ptr = subscription;

        if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
        {
            event.events |= EPOLLIN;
        }

        if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
        {
            event.events |= EPOLLOUT;
        }

        int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
        if(ret != xsuccess)
        {
            /**
             * 이 함수는 최초에 등록될 때만 사용하기 때문에 예외 코드가 EEXIST 라도 
             * 예외를 발생시켜야 한다.
             * 
             */
            if(errno == EEXIST)
            {
                xdescriptoreventgenerator_epoll_unregister(epollfd, descriptor, xtrue);

                xdescriptorevent_dispatch_exception(descriptor,
                                                    xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_generator_register_fail]),
                                                    EEXIST);
                return xfail;
            }
            xdescriptorevent_dispatch_exception(descriptor,
                                                xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_generator_register_fail]),
                                                errno);
            return xfail;
        }
        descriptor->status |= xdescriptorstatus_register;
        descriptor->on(descriptor, xdescriptoreventmask_register, xobjectof(xtrue), 0);
    }
    return xsuccess;
}

extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) calloc(sizeof(xdescriptoreventgenerator), 1);

    generator->alive       = xdescriptoreventgeneratorsubscriptions_new();
    generator->queue       = xdescriptoreventgeneratorsubscriptions_new();
    generator->engine      = engine;

    generator->f           = xinvalid;
    // 아래의 값은 많은 실험을 통하여 적절한 값을 찾아야 한다.
    generator->max         = 1024;
    generator->millisecond = 1;
    generator->events      = (struct epoll_event *) malloc(sizeof(struct epoll_event) * generator->max);

    return generator;
}

extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    if(generator)
    {
        xassertion(generator->alive->size > 0 || generator->queue->size > 0, "");

        generator->alive = xdescriptoreventgeneratorsubscriptions_rem(generator->alive);
        generator->queue = xdescriptoreventgeneratorsubscriptions_rem(generator->queue);

        if(generator->f >= 0)
        {
            int ret = close(generator->f);
            if(ret != xsuccess)
            {
                xassertion(ret != xsuccess, "");
            }
            generator->f = xinvalid;
        }

        generator->events = xobjectrem(generator->events);

        free(generator);
    }

    return xnil;
}

extern xdescriptoreventsubscription * xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(generator == xnil || subscription == xnil, "");

    xassertion(subscription->generatornode.subscriptions ||
               subscription->generatornode.next ||
               subscription->generatornode.prev, "");

    xdescriptor * descriptor = subscription->descriptor;

    if(descriptor->handle.f >= 0)
    {
        if((descriptor->status & xdescriptorstatus_open) && (descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
        {
            if(xdescriptoreventgenerator_epoll_register(generator->f, subscription) == xsuccess)
            {
                xdescriptoreventgeneratorsubscriptions_push(generator->alive, subscription);
                return subscription;
            }
            xassertion(xtrue, "");
        }
    }

    xdescriptoreventgeneratorsubscriptions_push(generator->queue, subscription);
    return subscription;
}

extern xdescriptoreventsubscription * xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(generator == xnil || subscription == xnil, "");

    if(generator->f >= 0)
    {
        // 리턴 값이 의미가 있을까? 
        xdescriptoreventgenerator_epoll_unregister(generator->f, subscription, xfalse);
    }

    if(subscription->generatornode.subscriptions)
    {
        xdescriptoreventgeneratorsubscriptions_del(subscription->generatornode.subscriptions, subscription);
    }

    return subscription;
}

extern xdescriptoreventsubscription * xdescriptoreventgenerator_update(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(generator == xnil || subscription == xnil, "");

    if(generator->f >= 0)
    {
        int ret = xdescriptoreventgenerator_epoll_update(generator->f, subscription, xfalse);
        if(ret == xsuccess)
        {
        }
        else
        {
            // 업데이트에 실패하면 존재하지 않는다고 봐야 할 듯...

        }
    }

    return subscription;
}
