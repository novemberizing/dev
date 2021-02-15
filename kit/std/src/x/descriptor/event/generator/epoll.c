#include <errno.h>

#include "epoll.h"

#include "../../subscription.h"

static inline xint32 xdescriptoreventgen_epoll_del(int f, xdescriptor * descriptor)
{
    xassertion(descriptor == xnil || descriptor->handle.f < 0 || f < 0, "");

    int ret = epoll_ctl(f, EPOLL_CTL_DEL, descriptor->handle.f, xnil);

    if(ret != xsuccess)
    {
        xassertion(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
    }

    return ret;
}

static inline xint32 xdescriptoreventgen_epoll_add(int f, xdescriptor * descriptor)
{
    xassertion(descriptor == xnil || descriptor->handle.f < 0 || f < 0, "");

    struct epoll_event event;
    event.data.ptr = descriptor;
    event.events = (EPOLLPRI | EPOLLERR | EPOLLHUP | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);
    if((descriptor->status & xdescriptor_status_in) == xdescriptor_status_void)
    {
        event.events |= EPOLLIN;
    }
    if((descriptor->status & xdescriptor_status_out) == xdescriptor_status_void)
    {
        event.events |= EPOLLOUT;
    }

    int ret = epoll_ctl(f, EPOLL_CTL_ADD, descriptor->handle.f, &event);

    if(ret != xsuccess)
    {
        xassertion(ret != xsuccess, "fail to epoll_ctl (%d)", errno);
    }

    return ret;
}

static inline void xdescriptoreventgen_epoll_descriptor_exception_on(xdescriptoreventgen_epoll * generator, xdescriptor * descriptor)
{
    xdescriptorsub * subscription = descriptor->subscription;

    xdescriptoreventgen_epoll_del(generator->f, descriptor);

    subscription->descriptor->status |= xdescriptor_status_exception;
    /** REMOVE SUBSCRIPTION IN THE ALIVE SUBSCRIPTIONS */
    xdescriptorsub * prev = subscription->generatornode.prev;
    xdescriptorsub * next = subscription->generatornode.next;
    if(prev)
    {
        prev->generatornode.next = next;
    }
    else
    {
        generator->subscriptions.alive.head = next;
    }
    if(next)
    {
        next->generatornode.prev = prev;
    }
    else
    {
        generator->subscriptions.alive.tail = prev;
    }
    generator->subscriptions.alive.size = generator->subscriptions.alive.size - 1;

    subscription->generatornode.cntr = xnil;
    subscription->generatornode.next = xnil;
    subscription->generatornode.prev = xnil;
    /** ADD SUBSCRIPTION IN THE SUBSCRIPTION QUEUE */
    subscription->generatornode.cntr = xaddressof(generator->subscriptions.queue);
    subscription->generatornode.prev = generator->subscriptions.queue.tail;
    if(subscription->generatornode.prev)
    {
        subscription->generatornode.prev->generatornode.next = subscription;
    }
    else
    {
        generator->subscriptions.queue.head = subscription;
    }
    generator->subscriptions.queue.size = generator->subscriptions.queue.size + 1;
}

static inline xint32 xdescriptoreventgen_epoll_ready(xdescriptoreventgen_epoll * generator)
{
    xassertion(generator == xnil, "");

    if(generator->f < 0)
    {
        generator->f = epoll_create(generator->max);
        if(generator->f >= 0)
        {
            xdescriptorsub * subscription = generator->subscriptions.alive.head;
            while(subscription)
            {
                if(xdescriptoreventgen_epoll_add(generator->f, subscription->descriptor)==xsuccess)
                {
                    subscription = subscription->generatornode.next;
                    continue;
                }
                xdescriptoreventgen_epoll_descriptor_exception_on(generator, subscription->descriptor);
            }
        }
        else
        {
            xassertion(generator->f < 0, "fail to epoll_create (%d)", errno);
            return xfail;
        }
    }
    return xsuccess;
}

static inline void xdescriptoreventgen_epoll_queue_consume(xdescriptoreventgen_epoll * generator)
{
    xassertion(generator == xnil, "");
    xassertion(xtrue, "implement this");
    xuint64 total = generator->subscriptions.queue.size;
    for(xuint64 i = 0; i < total; i++)
    {
        xdescriptorsub * subscription = generator->subscriptions.queue.head;
        if(subscription)
        {
            xassertion(xtrue, "implement this");
            continue;
        }
        break;
    }
}

/**
 * @fn      extern xdescriptorsub * xdescriptoreventgen_register(xdescriptoreventgen * o, xdescriptor * descriptor)
 * @brief   디스크립터를 디스크립터 이벤트 제네레이터에 등록하고 서브스크립션을 리턴합니다.
 * @details 
 * 
 * @param   o           | xdescriptoreventgen * | 디스크립터 이벤트 제네레이터 |
 * @param   descriptor  | xdescriptor *         | 디스크립터 |
 * 
 * @return  | xdescriptorsub * | 디스크립터 이벤트 서브스크립션 |
 * 
 * @todo    스레드 세이프티 보장
 */
extern xdescriptorsub * xdescriptoreventgen_register(xdescriptoreventgen * o, xdescriptor * descriptor)
{
    xassertion(o == xnil || descriptor == xnil, "");
    xassertion(descriptor->subscription, "");

    xdescriptoreventgen_epoll * generator = (xdescriptoreventgen_epoll *) o;

    if(descriptor->status & xdescriptor_status_exception)
    {
        xdescriptorsub * subscription = calloc(sizeof(xdescriptorsub), 1);

        descriptor->subscription = subscription;
        subscription->generatornode.generator = o;
        subscription->generatornode.cntr = xaddressof(generator->subscriptions.queue);
        subscription->descriptor = descriptor;

        subscription->generatornode.prev = generator->subscriptions.queue.tail;
        if(subscription->generatornode.prev)
        {
            subscription->generatornode.prev->generatornode.next = subscription;
        }
        else
        {
            generator->subscriptions.queue.head = subscription;
        }
        generator->subscriptions.queue.size = generator->subscriptions.queue.size + 1;
        
        return subscription;
    }
    else if((descriptor->status & xdescriptor_status_open) == xdescriptor_status_void)
    {
        xdescriptorsub * subscription = calloc(sizeof(xdescriptorsub), 1);
        
        descriptor->subscription = subscription;
        subscription->generatornode.generator = o;
        subscription->generatornode.cntr = xaddressof(generator->subscriptions.queue);
        subscription->descriptor = descriptor;

        subscription->generatornode.prev = generator->subscriptions.queue.tail;
        if(subscription->generatornode.prev)
        {
            subscription->generatornode.prev->generatornode.next = subscription;
        }
        else
        {
            generator->subscriptions.queue.head = subscription;
        }
        generator->subscriptions.queue.size = generator->subscriptions.queue.size + 1;
        
        return subscription;
    }
    else
    {
        if(generator->f >= 0)
        {
            int ret = xdescriptoreventgen_epoll_add(generator->f, descriptor);
            if(ret == xsuccess)
            {
                xdescriptorsub * subscription = calloc(sizeof(xdescriptorsub), 1);
                
                descriptor->subscription = subscription;
                subscription->generatornode.generator = o;
                subscription->generatornode.cntr = xaddressof(generator->subscriptions.alive);
                subscription->descriptor = descriptor;

                subscription->generatornode.prev = generator->subscriptions.alive.tail;
                if(subscription->generatornode.prev)
                {
                    subscription->generatornode.prev->generatornode.next = subscription;
                }
                else
                {
                    generator->subscriptions.alive.head = subscription;
                }
                generator->subscriptions.alive.size = generator->subscriptions.alive.size + 1;

                return subscription;
            }
            else
            {
                return xnil;
            }
        }
        else
        {
            xdescriptorsub * subscription = calloc(sizeof(xdescriptorsub), 1);

            descriptor->subscription = subscription;
            subscription->generatornode.generator = o;
            subscription->generatornode.cntr = xaddressof(generator->subscriptions.alive);
            subscription->descriptor = descriptor;

            subscription->generatornode.prev = generator->subscriptions.alive.tail;
            if(subscription->generatornode.prev)
            {
                subscription->generatornode.prev->generatornode.next = subscription;
            }
            else
            {
                generator->subscriptions.alive.head = subscription;
            }
            generator->subscriptions.alive.size = generator->subscriptions.alive.size + 1;

            return subscription;
        }
    }
}

/**
 * @fn      extern xsubscription * xdescriptoreventgen_unregister(xdescriptoreventgen * o, xsubscription * sub)
 * @brief   등록된 디스크립터를 디스크립터 이벤트 제네레이터에서 삭제하고 서브스크립션을 리턴합니다.
 * @details
 * 
 * @param   o   | xdescriptoreventgen * | in | 디스크립터 이벤트 제네레이터 |
 * @param   sub | xsubscription *       | in | 서브스크립션 |
 * 
 * @todo    스레드 세이프티 보장
 */
extern xsubscription * xdescriptoreventgen_unregister(xdescriptoreventgen * o, xsubscription * sub)
{
    xassertion(o == xnil || sub == xnil, "");

    xdescriptoreventgen_epoll * generator = (xdescriptoreventgen_epoll *) o;
    xdescriptorsub * subscription = (xdescriptorsub *) sub;
    xdescriptor * descriptor = subscription->descriptor;

    if(generator->f >= 0 && descriptor->handle.f >= 0)
    {
        xdescriptoreventgen_epoll_del(generator->f, descriptor);
    }

    xdescriptorsubs * subscriptions = subscription->generatornode.cntr;

    xdescriptorsub * prev = subscription->generatornode.prev;
    xdescriptorsub * next = subscription->generatornode.next;

    if(prev)
    {
        prev->generatornode.next = next;
    }
    else
    {
        subscriptions->head = next;
    }
    if(next)
    {
        next->generatornode.prev = prev;
    }
    else
    {
        subscriptions->tail = prev;
    }
    subscriptions->size = subscriptions->size - 1;

    subscription->generatornode.prev = xnil;
    subscription->generatornode.next = xnil;
    subscription->generatornode.generator = xnil;
    subscription->generatornode.cntr = xnil;

    return subscription;
}

extern void xdescriptoreventgen_once(xdescriptoreventgen * o)
{
    xassertion(o == xnil, "");

    xdescriptoreventgen_epoll * generator = (xdescriptoreventgen_epoll *) o;

    if(xdescriptoreventgen_epoll_ready(generator) == xsuccess)
    {
        xdescriptoreventgen_epoll_queue_consume(generator);

        int nfds = epoll_wait(generator->f, generator->events, generator->max, generator->timeout);
        if(nfds >= 0)
        {
            for(int i = 0; i < nfds; i++)
            {
                xdescriptor * descriptor = (xdescriptor *) generator->events[i].data.ptr;

                if(generator->events[i].events & (EPOLLPRI | EPOLLERR | EPOLLHUP | EPOLLRDHUP))
                {
                    xdescriptoreventgen_epoll_descriptor_exception_on(generator, descriptor);
                    continue;
                }
                if(generator->events[i].events & EPOLLOUT)
                {
                    descriptor->status |= xdescriptor_event_out;
                    xassertion(xtrue, "implement this");
                }
                if(generator->events[i].events & EPOLLIN)
                {
                    descriptor->status |= xdescriptor_event_in;
                    xassertion(xtrue, "implement this");
                }
            }
        }
        else
        {
            int err = errno;
            if(err != EINTR)
            {
                xassertion(err != EINTR, "fail to epoll_wait (%d)", err);
                if(close(generator->f) != xsuccess)
                {
                    xassertion(xtrue, "fail to close (%d)", errno);
                }
                generator->f = xinvalid;
            }
        }
    }
}
