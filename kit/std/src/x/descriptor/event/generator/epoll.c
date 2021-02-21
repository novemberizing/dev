#include <errno.h>

#include "epoll.h"
#include "subscription/list.h"

#include "../subscription.h"
#include "../../../descriptor.h"

static inline xint32 xdescriptoreventgenerator_epoll_register(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
{
    xassertion(subscrption == xnil || subscrption->descriptor == xnil, "");

    if(epollfd >= 0)
    {
        xdescriptor * descriptor = subscrption->descriptor;

        if(descriptor->handle.f >= 0)
        {
            if(descriptor->status & xdescriptorstatus_exception)
            {
                return xfail;
            }
            if(descriptor->status & xdescriptorstatus_close)
            {
                return xfail;
            }
            // 아래의 로직은 고민스럽다.
            if((descriptor->status & xdescriptorstatus_register) == xdescriptorstatus_void || force)
            {
                struct epoll_event event;

                event.data.ptr = subscrption;
                event.events = (EPOLLERR | EPOLLPRI | EPOLLHUP | EPOLLRDHUP | EPOLLONESHOT | EPOLLET);

                if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
                {
                    event.events |= EPOLLOUT;
                }
                if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
                {
                    event.events |= EPOLLIN;
                }

                int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);

                if(force)
                {
                    if(errno == EEXIST)
                    {
                        if(epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event) == xsuccess)
                        {
                            return xsuccess;
                        }
                    }
                }
                return ret == xsuccess ? xsuccess : xerrorret(errno);
            }
        }
        return xfail;
    }
    return xsuccess;
}

static inline xint32 xdescriptoreventgenerator_epoll_unregister(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
{
    if(epollfd >= 0)
    {
        xdescriptor * descriptor = subscrption->descriptor;
        if(descriptor->handle.f >= 0)
        {
            if((descriptor->status & xdescriptorstatus_register) || force)
            {
                int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);

                xassertion(ret != xsuccess, "");

                return ret == xsuccess ? xsuccess : xerrorret(errno);
            }
        }
    }
    return xsuccess;
}

static inline xint32 xdescriptoreventgenerator_epoll_update(int epollfd, xdescriptoreventsubscription * subscrption, xint32 force)
{
    if(epollfd >= 0)
    {
        xdescriptor * descriptor = subscrption->descriptor;
        if(descriptor->handle.f >= 0)
        {
            if(descriptor->status & xdescriptorstatus_exception)
            {
                return xfail;
            }
            if(descriptor->status & xdescriptorstatus_close)
            {
                return xfail;
            }
            struct epoll_event event;
            event.data.ptr = subscrption;
            event.events = (EPOLLHUP | EPOLLERR | EPOLLRDHUP | EPOLLPRI | EPOLLET | EPOLLONESHOT);

            if(descriptor->status & xdescriptorstatus_register)
            {
                int ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);
                if(ret != xsuccess)
                {
                    if(force)
                    {
                        if(errno == ENOENT)
                        {
                            if(epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event) == xsuccess)
                            {
                                return xsuccess;
                            }
                        }
                    }
                    return ret == xsuccess ? xsuccess : xerrorret(errno);
                }
                return xsuccess;
            }
            else
            {
                int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                if(ret != xsuccess)
                {
                    if(force)
                    {
                        if(errno == EEXIST)
                        {
                            if(epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event) == xsuccess)
                            {
                                return xsuccess;
                            }
                        }
                    }
                    return ret == xsuccess ? xsuccess : xerrorret(errno);
                }
                return xsuccess;
            }
        }
        return xfail;
    }
    return xsuccess;
}

static inline xint32 xdescriptoreventgenerator_epoll_open(xdescriptoreventgenerator_epoll * generator)
{
    if(generator->f < 0)
    {
        generator->f = epoll_create(generator->max);

        if(generator->f >= 0)
        {
            xsynclock(generator->alive->sync);
            xdescriptoreventsubscription * subscription = generator->alive->head;
            while(subscription)
            {
                // 
            }
            xsyncunlock(generator->alive->sync);
        }
        else
        {
            xassertion(generator->f < 0, "");
            return xfail;
        }
    }
    return xsuccess;
}

extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) calloc(sizeof(xdescriptoreventgenerator_epoll), 1);

    generator->alive       = xdescriptoreventgeneratorsubscriptionlist_new();
    generator->queue       = xdescriptoreventgeneratorsubscriptionlist_new();

    generator->engine      = engine;
    generator->f           = xinvalid;
    generator->max         = 1024;
    generator->millisecond = 1;
    generator->events      = (struct epoll_event *) malloc(sizeof(struct epoll_event) * generator->max);

    return (xdescriptoreventgenerator *) generator;
}

extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xassertion(generator == xnil || generator->alive->size > 0 || generator->queue->size > 0, "");

    if(generator->f >= 0)
    {
        if(close(generator->f) != xsuccess)
        {
            xassertion(errno, "");
        }
        generator->f = xinvalid;
    }

    generator->events = xobjectrem(generator->events);

    generator->alive  = xdescriptoreventgeneratorsubscriptionlist_rem(generator->alive);
    generator->queue  = xdescriptoreventgeneratorsubscriptionlist_rem(generator->queue);

    return xnil;
}

extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptor * descriptor = subscription->descriptor;

    if(descriptor->handle.f >= 0)
    {
        if((descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
        {
            if((descriptor->status & xdescriptorstatus_close) == xdescriptorstatus_void)
            {
                if(descriptor->status & xdescriptorstatus_open)
                {
                    int ret = xdescriptoreventgenerator_epoll_register(generator->f, subscription, xfalse);
                    if(ret == xsuccess)
                    {
                        xdescriptorevent_dispatch_register(descriptor, xnil, xtrue);
                        xdescriptoreventgeneratorsubscriptionlist_push(generator->alive, subscription);
                    }
                    else
                    {
                        xdescriptorevent_dispatch_exception(descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_generator_register_fail]), xerrorval(ret));
                    }
                    return;
                }
            }
        }
    }
    xdescriptoreventgeneratorsubscriptionlist_push(generator->queue, subscription);
}

extern void xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xdescriptor * descriptor = subscription->descriptor;

    if(descriptor->handle.f >= 0)
    {
        if(descriptor->status & xdescriptorstatus_register)
        {
            xdescriptoreventgenerator_epoll_unregister(generator->f, descriptor, xtrue);
        }
    }
    xdescriptoreventgeneratorsubscriptionlist_del(subscription);
}

extern void xdescriptoreventgenerator_update(xdescriptoreventsubscription * subscription)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) subscription->generatornode.generator;

    xdescriptor * descriptor = subscription->descriptor;

    if(descriptor->handle.f >= 0)
    {
        if(descriptor->status & xdescriptorstatus_exception)
        {
            return;
        }
        if(descriptor->status & xdescriptorstatus_close)
        {
            return;
        }
        int ret = xdescriptoreventgenerator_epoll_update(generator->f, subscription);
        if(ret != xsuccess)
        {
            xdescriptorevent_dispatch_exception(descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_generator_update_fail]), xerrorval(ret));
        }
    }
}

extern void xdescriptoreventgenerator_once(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    if(xdescriptoreventgenerator_epoll_open(generator) == xsuccess)
    {
        xdescriptoreventgenerator_queue_once(o);

        int nfds = epoll_wait(generator->f, generator->events, generator->max, generator->millisecond);

        if(nfds >= 0)
        {
            for(int i = 0; i < nfds; i++)
            {
                xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) generator->events[i].data.ptr;

                if(generator->events[i].events & (EPOLLERR | EPOLLPRI | EPOLLRDHUP | EPOLLHUP))
                {
                    xdescriptorevent_dispatch_exception(subscription->descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_generator_dispatch_exception]), generator->events[i].events);
                    continue;
                }
                if(generator->events[i].events & EPOLLOUT)
                {
                    xdescriptorevent_dispatch_out(subscription->descriptor);
                }
                if(generator->events[i].events & EPOLLIN)
                {
                    xdescriptorevent_dispatch_in(subscription->descriptor);
                }
            }
        }
        else
        {
            if(errno != EINTR)
            {
                int ret = close(generator->f);
                xassertion(ret != xsuccess, "");
                generator->f = xinvalid;
            }
        }
    }
}

extern void xdescriptoreventgenerator_queue_once(xdescriptoreventgenerator * o)
{
    xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

    xsynclock(generator->queue->sync);
    xuint64 total = generator->queue->size;
    for(xuint64 i = 0; i < total; i++)
    {
        xdescriptoreventsubscription * subscription = xdescriptoreventgeneratorsubscriptionlist_pop(generator->queue);
        if(subscription)
        {
            xsyncunlock(generator->queue->sync);

            xdescriptor * descriptor = subscription->descriptor;
            if(descriptor->handle.f >= 0 || (descriptor->status & xdescriptorstatus_exception) || (descriptor->status & xdescriptorstatus_close))
            {
                xassertion(descriptor->status & xdescriptorstatus_register, "");
                xdescriptorevent_process(xdescriptoreventmask_close, xnil, 0);
                xsynclock(generator->queue->sync);
                continue;
            }
            xdescriptorevent_process(xdescriptoreventmask_open, xnil, 0);
            xsynclock(generator->queue->sync);
            continue;
        }
        break;
    }
    xsyncunlock(generator->queue->sync);
}
