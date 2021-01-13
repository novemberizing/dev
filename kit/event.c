#include <stdio.h>
#include <stdlib.h>

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


#define xevent_type_user    0x01000000U
#define xevent_type_io      0x02000000U
#define xevent_type_time    0x03000000U
#define xevent_type_signal  0x04000000U

struct xevent
{
    xuint32 type;
    xevent * prev;
    xevent * next;
};

struct xevents
{
    xevent * head;
    xevent * tail;
    xuint64 size;
};

#define xeventengine_status_void    0x00000000U
#define xeventengine_status_on      0x00000001U
#define xeventengine_status_cancel  0x80000000U

struct xeventgenerators
{
    xeventgenerator * head;
    xeventgenerator * tail;
    xuint64 size;
};

struct xeventengine
{
    xuint32 status;
    xevents events;
    xeventgenerators generators;
    xeventprocessor processor;
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

#define xeventprocessor_run(engine) if(engine->processor) {     \
    engine->processor(engine);                                  \
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

        xcontainerlock(xaddressof(o->events));
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

    while((o->status & xeventengine_status_cancel) != xeventengine_status_cancel)
    {
        for(xeventgenerator * generator = xlistfront(xaddressof(o->generators)); generator != xnil; generator = xlistnext(generator))
        {
            xeventgenerator_run(generator, o);
        }
        xeventprocessor_run(o);
    }

    o->status &= (~xeventengine_status_on);
    return xsuccess;
}

struct xcustomgenerator;
typedef struct xcustomgenerator xcustomgenerator;

static inline void xcustomgenerator_run(xeventgenerator * p, xeventengine * engine)
{
    printf("hello world\n");
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

int main(int argc, char ** argv)
{
    xeventengine engine = { 0, };
    engine.processor = xeventprocessor_main;
    xeventengine_plug_generator(xaddressof(engine), xcustomgeneratornew());
//    xeventengine_plug_handler()
    return xeventengine_run(xaddressof(engine));
}


// struct xeventengine
// {
//     xuint32 status;
//     xeventgenerators generators;
//     xeventprocessor processor;
// };