#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../event.h"

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

extern xint32 xeventenginerun(xeventengine * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xassertion(xeventenginestatus(o) != xeventengine_status_void, "engine is already running");

        o->status |= xeventengine_status_on;

        // TODO: PLUG EVENT GENERATOR

        while(o->status & xeventengine_status_cancel != xeventengine_status_cancel)
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

    return o;
}