#include <sys/epoll.h>

#include "../event.h"

struct xgenerator_io;
struct xeventobj_io;

typedef struct xgenerator_io xgenerator_io;
typedef struct xeventobj_io xeventobj_io;

struct xgenerator_io
{
    xgenerator * prev;
    xgenerator * next;

    void (*run)(xgenerator *, xengine *);

    int epollfd;
};

static void xevent_io_write(xevent * event)
{
    xeventobj_io * o = (xeventobj_io *) event->obj;

    const int max = 1024;

    for(int i = 0; i < max; i++)
    {
        // xqueuefront(o->buffer[out])
        // xbuffer * buffer = xqueuepop(o->outs);
        // int n = write(o->fd, )
    }
}

static void xgenerator_io_run(xgenerator * p, xengine * engine)
{
    xgenerator_io * o = (xgenerator_io *) p;
    struct epoll_event events[1024];
    int timeout = 1;
    int nfds = epoll_wait(o->epollfd, events, 1024, timeout);
    if(nfds >= 0)
    {
        for(int i = 0; i < nfds; i++)
        {
            xevent * event = xeventnew(xevent_type_io, events[i].data.ptr, engine, o);
            if(events[i].events & EPOLLIN)
            {
                event->type |= xevent_io_type_in;
            }
            if(events[i].events & EPOLLOUT)
            {
                event->type |= xevent_io_type_out;
                xevent_io_write(event);
            }
            if(events[i].events & EPOLLPRI)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLRDNORM)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLRDBAND)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLWRNORM)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLWRBAND)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLMSG)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLERR)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLHUP)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLRDHUP)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLEXCLUSIVE)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLWAKEUP)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLONESHOT)
            {
                // CHECK THIS
            }
            if(events[i].events & EPOLLET)
            {
                // CHECK THIS
            }
        }
    }
    else
    {
        // TODO: ERROR HANDLING
    }
}

xgenerator * xgenerator_io_new(void)
{
    xgenerator_io * o = (xgenerator_io *) calloc(sizeof(xgenerator_io), 1);

    o->epollfd = xinvalid;
    o->run = xgenerator_io_run;

    return (xgenerator *) o;
}

struct xgenerator_time
{
    xgenerator * prev;
    xgenerator * next;
};

struct xgenerator_signal
{
    xgenerator * prev;
    xgenerator * next;
};
