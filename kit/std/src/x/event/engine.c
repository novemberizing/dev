#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

#include "../event.h"

#define xsignalmax  _NSIG       /**!< only for signal (linux) */

static xthreadlocal * __threadlocal = xnil;

static inline xevent * __xevent_internal_process_io(xevent * event, xeventengine * o)
{
    return xnil;
}

static inline xevent * __xevent_internal_process_signal(xevent * event, xeventengine * o)
{
    return xnil;
}

static inline xevent * __xevent_internal_process_time(xevent * event, xeventengine * o)
{
    return xnil;
}

static inline xevent * __xevent_internal_process_custom(xevent * event, xeventengine * o)
{
    xassertion(o->handler, "custom handler not exist");
    return o->handler(event, o);
}

static inline xevent * __xevent_internal_process(xevent * event, xeventengine * o)
{
    switch(xeventcategory(event))
    {
        case xevent_category_io:     return __xevent_internal_process_io(event, o);
        case xevent_category_signal: return __xevent_internal_process_signal(event, o);
        case xevent_category_time:   return __xevent_internal_process_time(event, o);
        case xevent_category_custom: return __xevent_internal_process_custom(event, o);
    }
    xassertion(xtrue, "unsupported event category");
    return xnil;
}

static inline void __xeventengine_main_consume(xeventengine * o)
{
    xsynclock(o->queue.sync);
    xuint64 total = xlistsize(xaddressof(o->queue));
    for(xuint64 i = 0; i < total && xlistsize(xaddressof(o->queue)) > 0; i++)
    {
        xlistnode * node = o->queue.head;
        o->queue.head = node->next;
        if(o->queue.head)
        {
            o->queue.head->prev = xnil;
        }
        else
        {
            o->queue.tail = xnil;
        }
        o->queue.size = o->queue.size - 1;
        xsyncunlock(o->queue.sync);
        xevent * event = __xevent_internal_process((xevent *) node->value.ptr, o);
        if(event != node->value.ptr)
        {
            free(node->value.ptr);
        }
        if(event == xnil)
        {
            free(node);
            node = xnil;
        }
        xsynclock(o->queue.sync);
        if(event)
        {
            node->prev = o->queue.tail;
            if(node->prev)
            {
                node->prev->next = node;
            }
            else
            {
                o->queue.head = node;
            }
            o->queue.tail = node;
            o->queue.size = o->queue.size + 1;
        }
    }
    xsyncunlock(o->queue.sync);
}

static void __xeventengine_internal_signal_handler(int no, siginfo_t * info, void * data)
{
    xcheck(__threadlocal == xnil, "thread local not created");
    
    if(__threadlocal)
    {
        xeventengine * o = (xeventengine *) xthreadlocalget(__threadlocal);
        xassertion(o == xnil, "engine is registered in thread local");

        xeventsignalhandler handler = o->signals[no];
        xcheck(handler == xnil, "already removed signal(%d) handler", no);

        if(handler)
        {
            handler(xevent_category_signal, no, xnil, info->si_value.sival_ptr, xnil, o);
        }
    }
}

/**
 * TODO: 사용자가 변경하지 못하도록 하자.
 * 
 */
extern xthreadlocal * xeventenginethreadlocal(void)
{
    return __threadlocal;
}

extern void xeventengineon(void)
{
    if(__threadlocal == xnil)
    {
        xrandomon();

        __threadlocal = xthreadlocalnew(xnil);
    }
}

extern xint32 xeventenginerun(xeventengine * o)
{
    xcheck(o == xnil, "null pointer");
    
    xassertion(__threadlocal == xnil, "thread local not created");

    if(o)
    {
        xcheck(xtrue, "%p", o);

        xassertion(xeventenginestatus(o) != xeventengine_status_void, "engine is already running");
        xassertion(xthreadlocalget(__threadlocal), "already running");
        o->status |= xeventengine_status_on;

        xthreadlocalset(__threadlocal, o);

        // TODO: PLUG EVENT GENERATOR

        while((o->status & xeventengine_status_cancel) != xeventengine_status_cancel)
        {
            for(xlistnode * node = xlistfront(xaddressof(o->generators)); node != xnil; node = xlistnodenext(node))
            {
                xeventgenerator * generator = (xeventgenerator *) node->value.ptr;
            }
            if(xlistsize(xaddressof(o->processors)) == 0 || o->status & xeventengine_status_main_cusuming_off)
            {
                __xeventengine_main_consume(o);
            }
            if(o->internal)
            {
                o->internal(o);
            }
        }
        // TODO: 모든 이벤트를 종료합니다.

        // 모든 시그널 이벤트 핸들러 제거
        for(xint32 i = 0; i < xsignalmax; i++)
        {
            if(o->signals[i])
            {
                xeventengine_signal_handler_del(o, i);
            }
        }
        // 현재 등록된 스레드 로컬 엔진 제거
        xthreadlocalset(__threadlocal, xnil);
        o->status &= (~xeventengine_status_on);

        if(xeventengineallocated(o))
        {
            free(o);
        }
    }
    return xsuccess;
}

extern xeventengine * xeventenginenew(void)
{
    xeventengine * o = (xeventengine *) malloc(sizeof(xeventengine));
    xassertion(o == xnil, "fail to malloc (%d)", errno);

    o->generators = xlistinit();
    o->handler = xnil;
    o->internal = xnil;
    o->processors = xlistinit();
    o->queue = xlistinit();
    o->status = xeventengine_allocated;
    o->signals = calloc(sizeof(xeventsignalhandler), xsignalmax);

    return o;
}

extern void xeventengine_signal_handler_del(xeventengine * o, xint32 no)
{
    xcheck(o == xnil, "null pointer");

    if(o && o->signals[no])
    {
        o->signals[no] = xnil;

        struct sigaction action = { 0, };

        action.sa_handler = SIG_DFL;

        if(sigaction(no, &action, xnil) != xsuccess)
        {
            xassertion(xtrue, "fail to sigaction (%d)", errno);
        }
    }
}

extern void xeventengine_signal_handler_set(xeventengine * o, xint32 no, xeventsignalhandler handler)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xassertion(xsignalmax <= no, "not supported signal");
        xcheck(o->signals[no] != xnil, "replace signal hanadler");

        if(o->signals[no])
        {
            o->signals[no] = handler;
            if(o->signals[no] == xnil)
            {
                struct sigaction action = { 0, };

                action.sa_handler = SIG_DFL;

                if(sigaction(no, &action, xnil) != xsuccess)
                {
                    xassertion(xtrue, "fail to sigaction (%d)", errno);
                }
            }
        }
        else if(handler)
        {
            o->signals[no] = handler;

            struct sigaction action = { 0, };

            action.sa_flags = SA_NODEFER | SA_SIGINFO;
            action.sa_sigaction = __xeventengine_internal_signal_handler;

            if(sigaction(no, &action, xnil) != xsuccess)
            {
                xassertion(xtrue, "fail to sigaction (%d)", errno);
            }
        }
    }
}
