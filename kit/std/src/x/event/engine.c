#include <stdio.h>
#include <stdlib.h>

#include "../event.h"

static inline xevent * __xevent_internal_process(xevent * event, xeventengine * o)
{

    return xnil;
}

extern xint32 xeventenginerun(xeventengine * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xassertion(o->status != xeventengine_status_void, "engine is already running");

        o->status |= xeventengine_status_on;

        while(o->status & xeventengine_status_cancel != xeventengine_status_cancel)
        {
            for(xlistnode * node = xlistfront(xaddressof(o->generators)); node != xnil; node = xlistnodenext(node))
            {
                xeventgenerator * generator = (xeventgenerator *) node->value.ptr;
            }
            /**
             * TODO: 스레드 풀을 만듭니다.
             * TODO: 아래 로직을 함수로 만듭니다.
             */
            if(xtrue)
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

            if(o->internal)
            {
                o->internal(o);
            }
        }

        o->status &= (~xeventengine_status_on);
    }
    return xsuccess;
}