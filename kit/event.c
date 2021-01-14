#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "event.h"

struct xevent;
struct xevents;
struct xeventengine;
struct xeventgenerator;
struct xeventgenerators;

typedef struct xevent xevent;
typedef struct xevents xevents;
typedef struct xeventengine xeventengine;
typedef struct xeventgenerator xeventgenerator;
typedef struct xeventgenerators xeventgenerators;

typedef void (*xeventprocessor)(xeventengine *);
typedef xevent * (*xeventhandler)(xevent *, xeventengine *);

#define xsignalmax      SIGRTMAX
#define xsingalno(no)   (no)

struct xsignalhandler {

};

// xsignals

/**
 * 
 */

#define xevent_mask_categories  0xFF000000U
#define xevent_mask_types       0x0000FFFFU

#define xevent_category_custom  0x01000000U
#define xevent_category_io      0x02000000U
#define xevent_category_time    0x03000000U
#define xevent_category_signal  0x04000000U

struct xevent
{
    xuint32 type;
    xevent * prev;
    xevent * next;
    xeventgenerator * source;
    xeventengine * engine;
};

struct xevents
{
    xevent * head;
    xevent * tail;
    xuint64 size;
};

extern xevent * xeventnew(xuint32 type, xeventgenerator * generator, xeventengine * engine)
{
    xevent * o = (xevent *) calloc(sizeof(xevent), 1);

    o->type = type;
    o->source = generator;
    o->engine = engine;

    return o;
}

#define xeventengine_status_void    0x00000000U
#define xeventengine_status_on      0x00000001U
#define xeventengine_status_cancel  0x80000000U

struct xeventgenerators
{
    xeventgenerator * head;
    xeventgenerator * tail;
    xuint64 size;
};

// typedef void (*xsignalhandler)(xeventhandler)

struct xeventengine
{
    xuint32 status;
    xevents events;
    xeventgenerators generators;
    xeventprocessor processor;
    xeventhandler customeventproc;
    xeventhandler * signalhandlers;
};

typedef void (*xgenerator_run_func)(xeventgenerator *, xeventengine *);

struct xeventgenerator
{
    xeventgenerator * prev;
    xeventgenerator * next;
    xgenerator_run_func run;
};

static inline void xeventgenerator_run(xeventgenerator * o, xeventengine * engine)
{
    o->run(o, engine);
}

extern void xeventengine_plug_generator(xeventengine * o, xeventgenerator * generator)
{
    xlistpushback(xaddressof(o->generators), xeventgenerator, generator);
}

extern void xeventengine_plug_handler(xeventengine * o, xeventhandler func) {
    o->customeventproc = func;
}

#define xeventprocessor_run(engine) if(engine->processor) {     \
    engine->processor(engine);                                  \
}

static inline xevent * xeventengine_handle_custom(xevent * o, xeventengine * engine)
{
    if(engine->customeventproc)
    {
        return engine->customeventproc(o, engine);
    }
    return xnil;
}

static inline xevent * xeventengine_handle_signal(xevent * o, xeventengine * engine)
{
    return xnil;
}

static inline xevent * xeventengine_handle_io(xevent * o, xeventengine * engine)
{
    return xnil;
}

static inline xevent * xeventengine_handle_time(xevent * o, xeventengine * engine)
{
    return xnil;   
}

static inline void xeventprocessor_main(xeventengine * o) {
    xuint64 size = xqueuesize(xaddressof(o->events));
    xcontainerlock(xaddressof(o->events));
    for(xuint64 i = 0; i < size && xqueueempty(xaddressof(o->events)) == xfalse; i++)
    {
        xevent * item = o->events.head;
        if(item)
        {
            o->events.head = item->next;
            if(o->events.head)
            {
                o->events.head->prev = xnil;
            }
            else
            {
                o->events.tail = xnil;
            }
            o->events.size = o->events.size - 1;
        }
        xcontainerunlock(xaddressof(o->events));
        xevent * retry = xnil;
        switch(item->type & xevent_mask_categories)
        {
            case xevent_category_custom:    retry = xeventengine_handle_custom(item, o);    break;
            case xevent_category_io:        retry = xeventengine_handle_io(item, o);        break;
            case xevent_category_signal:    retry = xeventengine_handle_signal(item, o);    break;
            case xevent_category_time:      retry = xeventengine_handle_time(item, o);      break;
            default:                        xassertion(xtrue, "unsupported event category");    break;
        }
        if(retry == xnil)
        {
            free(item);
        }
        xcontainerlock(xaddressof(o->events));
        if(retry)
        {
            xqueuepush(xaddressof(o->events), xevent, retry);
        }
    }
    xcontainerunlock(xaddressof(o->events));

    // o->
    printf("hello engine\n");
}

extern int xeventengine_run(xeventengine * o)
{
    xassertion(o == xnil, "null pointer exception");
    xassertion(o->status != xeventengine_status_void, "");
    o->status |= xeventengine_status_on;

    o->signalhandlers = calloc(sizeof(xeventhandler), xsignalmax);

    while((o->status & xeventengine_status_cancel) != xeventengine_status_cancel)
    {
        for(xeventgenerator * generator = xlistfront(xaddressof(o->generators)); generator != xnil; generator = xlistnext(generator))
        {
            xeventgenerator_run(generator, o);
        }
        xeventprocessor_run(o);
    }

    if(o->signalhandlers)
    {
        free(o->signalhandlers);
    }

    o->status &= (~xeventengine_status_on);
    return xsuccess;
}

struct xcustomgenerator;
typedef struct xcustomgenerator xcustomgenerator;

#define custom_event_type_helloworld    1

#define xcustomeventtype(type)  (xevent_category_custom | type)

static inline void xcustomgenerator_run(xeventgenerator * p, xeventengine * engine)
{
    xqueuepush(xaddressof(engine->events), xevent, xeventnew(xcustomeventtype(custom_event_type_helloworld), p, engine));
}

struct xcustomgenerator
{
    xeventgenerator * prev;
    xeventgenerator * next;
    xgenerator_run_func run;
};

extern xeventgenerator * xcustomgeneratornew()
{
    xcustomgenerator * o = (xcustomgenerator *) calloc(sizeof(xcustomgenerator), 1);

    o->run = xcustomgenerator_run;

    return (xeventgenerator *) o;
}

static inline xevent * customeventhandle(xevent * o, xeventengine * engine)
{
    switch((o->type & xevent_mask_types))
    {
        case custom_event_type_helloworld: printf("hello world"); free(o); break;
    }
    return xnil;
}

static inline void internal_signal_handler(int no, siginfo_t * info, void * data)
{

}

extern void xeventengine_plug_singal_handler(xeventengine * o, int signal, xeventhandler handler) {
    if(0 < signal && signal < xsignalmax)
    {
        o->signalhandlers[signal] = handler;
        struct sigaction action = { 0, };
        action.sa_sigaction = internal_signal_handler;
        action.sa_flags = SA_SIGINFO;
        sigaction(signal, &action, NULL);
    }
}

#include <signal.h>

#define xevent_signal_type_interrupt    SIGINT

static xevent * custom_interrupt_signal_handler(xevent * o, xeventengine * engine)
{
    printf("engine: %p\n", o->engine);
    printf("source: %p\n", o->source);
    printf("type: %d\n", o->type);
//    printf(o->)
    return xnil;
}

int main(int argc, char ** argv)
{
    xeventengine engine = { 0, };

    /**
     * set thread local data
     */

    engine.processor = xeventprocessor_main;
    /**
     * 이벤트 제네레이터를 생성할 때, 핸들러도 넣을 수 있도록 하자.
     * xeventengine_plug(xaddressof(engine), xcustomgenerarornew(), xcustomhandlernew())
     */

    xeventengine_plug_singal_handler(xaddressof(engine), xevent_signal_type_interrupt, custom_interrupt_signal_handler);
    // xeventengine_add_signalevent_handler();


    xeventengine_plug_generator(xaddressof(engine), xcustomgeneratornew());
    xeventengine_plug_handler(xaddressof(engine), customeventhandle);
//    xeventengine_plug_handler()
    return xeventengine_run(xaddressof(engine));
}


// struct xeventengine
// {
//     xuint32 status;
//     xeventgenerators generators;
//     xeventprocessor processor;
// };