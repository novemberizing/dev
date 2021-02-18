#include "event.h"

#include "../processor.h"
#include "../processor/pool.h"

extern xeventprocessor_event * xeventprocessor_event_new(xeventprocessor_event_handler handler, xeventprocessor * processor)
{
    xeventprocessor_event * o = (xeventprocessor_event *) calloc(sizeof(xeventprocessor_event), 1);

    o->on        = handler;
    o->processor = processor;

    return o;
}

extern void xeventprocessor_event_exit(xeventprocessor_event * event)
{
    xeventprocessor * processor = event->processor;
    
    if(xthreadcheck_removable((xthread *) processor))
    {
        xeventprocessor_rem(processor);

        free(event);
    }
    else
    {
        xeventprocessorpool * pool = processor->pool;
        xeventengine * engine = pool->engine;
        xeventengine_main_push(event);
    }
}