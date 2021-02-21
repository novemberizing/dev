#include <errno.h>

#include "./epoll.h"

#include "../../../descriptor.h"
#include "../subscription.h"
#include "../generator/subscription/list.h"

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
            int ret = xdescriptoreventgenerator_epoll_unregister(generator->f, descriptor);
            if(ret == xsuccess)
            {

            }
            else
            {
                
            }
        }
    }
}
// extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o);

// extern void xdescriptoreventgenerator_call(xdescriptoreventgenerator * o);
// extern void xdescriptoreventgenerator_queue_consume(xdescriptoreventgenerator * o);

// extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);
// extern xdescriptoreventsubscription * xdescriptoreventgenerator_update(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);
// extern xdescriptoreventsubscription * xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription);


// static inline xint32 xdescriptoreventgenerator_epoll_unregister(int epollfd, xdescriptoreventsubscription * subscription, xint32 force)
// {
//     xassertion(epollfd < 0, "");
    
//     if(subscription)
//     {
//         xdescriptor * descriptor = subscription->descriptor;

//         if(descriptor && descriptor->handle.f >= 0)
//         {
//             if((descriptor->status & xdescriptorstatus_register) || force)
//             {
//                 int ret = epoll_ctl(epollfd, EPOLL_CTL_DEL, descriptor->handle.f, xnil);

//                 if(ret != xsuccess)
//                 {
//                     xassertion(ret != xsuccess, "");
//                     return xerrorret(errno);
//                 }
//             }
//         }
//     }
//     return xsuccess;
// }

// static inline xint32 xdescriptoreventgenerator_epoll_update(int epollfd, xdescriptoreventsubscription * subscription, xint32 force)
// {
//     xassertion(epollfd < 0 || subscription == xnil, "");

//     xdescriptor * descriptor = subscription->descriptor;

//     xassertion(descriptor == xnil || descriptor->handle.f < 0, "");

//     xassertion(descriptor->status & xdescriptorstatus_register, "");
//     xassertion(descriptor->status & xdescriptorstatus_exception, "");
//     xassertion(descriptor->status & xdescriptorstatus_close, "");

//     struct epoll_event event;
//     event.data.ptr = subscription;
//     event.events = (EPOLLERR | EPOLLPRI | EPOLLHUP | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);

//     if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
//     {
//         event.events |= EPOLLIN;
//     }

//     if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
//     {
//         event.events |= EPOLLOUT;
//     }

//     int ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);

//     if(ret != xsuccess)
//     {
//         if(errno == ENOENT && force)
//         {
//             ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);

//             return ret != xsuccess ? xerrorret(errno) : xsuccess;
//         }
//         return xerrorret(errno);
//     }

//     return ret;
// }

// static inline xint32 xdescriptoreventgenerator_epoll_register(int epollfd, xdescriptoreventsubscription * subscription, xuint32 force)
// {
//     xassertion(epollfd < 0 || subscription == xnil, "");

//     xdescriptor * descriptor = subscription->descriptor;

//     xassertion(descriptor == xnil || descriptor->handle.f < 0, "");

//     xassertion(descriptor->status & xdescriptorstatus_register, "");
//     xassertion(descriptor->status & xdescriptorstatus_exception, "");
//     xassertion(descriptor->status & xdescriptorstatus_close, "");

//     struct epoll_event event;
//     event.data.ptr = subscription;
//     event.events = (EPOLLERR | EPOLLPRI | EPOLLHUP | EPOLLRDHUP | EPOLLET | EPOLLONESHOT);

//     if((descriptor->status & xdescriptorstatus_in) == xdescriptorstatus_void)
//     {
//         event.events |= EPOLLIN;
//     }

//     if((descriptor->status & xdescriptorstatus_out) == xdescriptorstatus_void)
//     {
//         event.events |= EPOLLOUT;
//     }

//     int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, descriptor->handle.f, &event);

//     if(ret != xsuccess)
//     {
//         if(errno == EEXIST && force)
//         {
//             ret = epoll_ctl(epollfd, EPOLL_CTL_MOD, descriptor->handle.f, &event);

//             return ret != xsuccess ? xerrorret(errno) : xsuccess;
//         }
//         return xerrorret(errno);
//     }

//     return ret;
// }

// static inline xint32 xdescriptoreventgenerator_epoll_open(xdescriptoreventgenerator_epoll * generator)
// {
//     xassertion(generator == xnil, "");

//     if(generator->f < 0)
//     {
//         generator->f = epoll_create(generator->max);

//         if(generator->f >= 0)
//         {
//             xsynclock(generator->alive->sync);
//             xdescriptoreventsubscription * subscription = generator->alive->head;

//             while(subscription)
//             {
//                 int ret = xdescriptoreventgenerator_epoll_register(generator->f, subscription, xfalse);
//                 if(ret < 0)
//                 {
//                     // 외부에서 LOCK/UNLOCK 을 보장해주어야 한다.
//                     // TODO: THREAD SAFETY 가 PREFECT 하게 보장되는지 확인하자.
//                     // ALIVE 컨테이너에서의 삭제는 항상 이벤트 루트의 메인
//                     // 스레드에서 수행되도록 하자.
//                     xdescriptoreventsubscription * next = xdescriptoreventgeneratorsubscriptions_del(generator->alive, subscription);
//                     xsyncunlock(generator->alive->sync);

//                     // 아래의 함수에서 예외 큐에 삽입하도록 되어 있다.
//                     xdescriptorevent_dispatch_exception(subscription->descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_generator_register_fail]), xerrorval(ret));

//                     xsynclock(generator->alive->sync);
//                     subscription = next;
//                     continue;
//                 }
//                 subscription = subscription->generatornode.next;
//             }
//             xsyncunlock(generator->alive->sync);
//         }
//     }

//     return generator->f > 0;
// }

// extern xdescriptoreventgenerator * xdescriptoreventgenerator_new(xeventengine * engine)
// {
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) calloc(sizeof(xdescriptoreventgenerator), 1);

//     generator->alive       = xdescriptoreventgeneratorsubscriptions_new();
//     generator->queue       = xdescriptoreventgeneratorsubscriptions_new();
//     generator->engine      = engine;

//     generator->f           = xinvalid;
//     // 아래의 값은 많은 실험을 통하여 적절한 값을 찾아야 한다.
//     generator->max         = 1024;
//     generator->millisecond = 1;
//     generator->events      = (struct epoll_event *) malloc(sizeof(struct epoll_event) * generator->max);

//     return generator;
// }

// extern xdescriptoreventgenerator * xdescriptoreventgenerator_rem(xdescriptoreventgenerator * o)
// {
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     if(generator)
//     {
//         xassertion(generator->alive->size > 0 || generator->queue->size > 0, "");

//         generator->alive = xdescriptoreventgeneratorsubscriptions_rem(generator->alive);
//         generator->queue = xdescriptoreventgeneratorsubscriptions_rem(generator->queue);

//         if(generator->f >= 0)
//         {
//             int ret = close(generator->f);
//             if(ret != xsuccess)
//             {
//                 xassertion(ret != xsuccess, "");
//             }
//             generator->f = xinvalid;
//         }

//         generator->events = xobjectrem(generator->events);

//         free(generator);
//     }

//     return xnil;
// }

// extern void xdescriptoreventgenerator_register(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
// {
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     xassertion(generator == xnil || subscription == xnil, "");

//     xassertion(subscription->generatornode.subscriptions ||
//                subscription->generatornode.next ||
//                subscription->generatornode.prev, "");

//     xdescriptor * descriptor = subscription->descriptor;

//     if(descriptor->handle.f >= 0)
//     {
//         if((descriptor->status & xdescriptorstatus_open) && (descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
//         {
//             if(xdescriptoreventgenerator_epoll_register(generator->f, subscription, xfalse) == xsuccess)
//             {
//                 xdescriptoreventgeneratorsubscriptions_push(generator->alive, subscription);
//                 return;
//             }
//         }
//     }

//     xdescriptoreventgeneratorsubscriptions_push(generator->queue, subscription);
// }

// extern xdescriptoreventsubscription * xdescriptoreventgenerator_unregister(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
// {
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     xassertion(generator == xnil || subscription == xnil, "");

//     if(generator->f >= 0)
//     {
//         // 리턴 값이 의미가 있을까? 
//         xdescriptoreventgenerator_epoll_unregister(generator->f, subscription, xfalse);
//     }

//     if(subscription->generatornode.subscriptions)
//     {
//         xdescriptoreventgeneratorsubscriptions_del(subscription->generatornode.subscriptions, subscription);
//     }

//     return subscription;
// }

// extern xdescriptoreventsubscription * xdescriptoreventgenerator_update(xdescriptoreventgenerator * o, xdescriptoreventsubscription * subscription)
// {
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     xassertion(generator == xnil || subscription == xnil, "");

//     if(generator->f >= 0)
//     {
//         int ret = xdescriptoreventgenerator_epoll_update(generator->f, subscription, xfalse);
//         if(ret == xsuccess)
//         {

//         }
//         else
//         {
//             // 업데이트에 실패하면 존재하지 않는다고 봐야 할 듯...
//         }
//     }

//     return subscription;
// }

// extern void xdescriptoreventgenerator_call(xdescriptoreventgenerator * o)
// {
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;

//     if(xdescriptoreventgenerator_epoll_open(generator))
//     {
//         xdescriptoreventgenerator_queue_consume(o);

//         int nfds = epoll_wait(generator->f, generator->events, generator->max, generator->millisecond);
//         if(nfds >= 0)
//         {
//             for(int i = 0; i < nfds; i++)
//             {
//                 xdescriptoreventsubscription * subscription = (xdescriptoreventsubscription *) generator->events[i].data.ptr;

//                 if(generator->events[i].events & (EPOLLERR | EPOLLHUP | EPOLLRDHUP | EPOLLPRI))
//                 {
//                     xdescriptorevent_dispatch_exception(subscription->descriptor, xaddressof(descriptorexceptioncodes[xdescriptorexceptioncode_generator_dispatch_exception]), generator->events[i].events);
//                     continue;
//                 }
//                 if(generator->events[i].events & EPOLLOUT)
//                 {
//                     xdescriptorevent_dispatch_out(subscription->descriptor);
//                 }
//                 if(generator->events[i].events & EPOLLIN)
//                 {
//                     xdescriptorevent_dispatch_in(subscription->descriptor);
//                 }
//             }
//         }
//         else
//         {
//             if(errno != EINTR)
//             {
//                 xassertion(errno != EINTR, "");
//                 if(close(generator->f) != xsuccess)
//                 {
//                     xassertion(errno, "");
//                 }
//                 generator->f = xinvalid;
//             }
//         }
//     }
// }

// extern void xdescriptoreventgenerator_queue_consume(xdescriptoreventgenerator * o)
// {
//     xdescriptoreventgenerator_epoll * generator = (xdescriptoreventgenerator_epoll *) o;
    
//     xsynclock(generator->queue->sync);
//     xuint64 limit = generator->queue->size;
//     for(xuint64 i = 0; i < limit; i++)
//     {
//         xdescriptoreventsubscription * subscription = xdescriptoreventgeneratorsubscriptions_pop(generator->queue);
//         if(subscription)
//         {
//             xsyncunlock(generator->queue->sync);
//             xdescriptor * descriptor = subscription->descriptor;
//             // 디스크립터의 상태에 따라서 디스크립터를 처리한다.
//             // 내부에서 이벤트를 처리해야 하는가? 아니면 외부에서 이벤트 처리 후에 EPOLL 에 등록하는 것을 처리해야 
//             if(descriptor->status & xdescriptorstatus_exception)
//             {
//                 descriptor->process(descriptor, xdescriptoreventmask_exception, xnil);
//                 // 고민스러운 부분이다.
//             }
//             else if(descriptor->status & xdescriptorstatus_close)
//             {
//                 descriptor->process(descriptor, xdescriptoreventmask_close, xnil);
//                 // 고민스러운 부분이다.
//             }
//             else if((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void)
//             {
//                 descriptor->process(descriptor, xdescriptoreventmask_open, xnil);
//                 // 고민스러운 부분이다.
//             }
//             else
//             {
//                 // 상태를 처리할 수 없다.
//                 xassertion(xtrue, "");
//             }
//             xsynclock(generator->queue->sync);
//             continue;
//         }
//         break;
//     }
//     xsyncunlock(generator->queue->sync);
// }


