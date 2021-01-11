/**
 * @file    x/event.h
 * @brief
 * @details
 * 
 * @version 0.0.1
 * @since   2021. 01. 11.
 */
#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xengine;
struct xeventqueue;
struct xgenerator;
struct xgenerators;
struct xeventobj;

typedef struct xevent xevent;
typedef struct xengine xengine;
typedef struct xeventqueue xeventqueue;
typedef struct xeventobj xeventobj;

typedef struct xgenerator xgenerator;
typedef struct xgenerators xgenerators;

struct xevent
{
    xuint32 type;
    xevent * prev;
    xevent * next;

    xeventobj * obj;
};

#define xevent_type_io      0x01000000U
#define xevent_type_time    0x02000000U
#define xevent_type_signal  0x03000000U

#define xevent_io_type_out  0x00000001U
#define xevent_io_type_in   0x00000002U
#define xevent_io_type_err  0x00000003U

extern xevent * xeventnew(xuint32 type, xeventobj * obj, xengine * engine, xgenerator * from);

struct xeventqueue
{
    xuint64 size;
    xevent * head;
    xevent * tail;

    xsync * sync;
};

#define xeventqueueinit()   (xeventqueue) { 0, xnil, xnil, xnil }

struct xgenerator
{
    xgenerator * prev;
    xgenerator * next;

    void (*run)(xgenerator *, xengine *);
};

extern xgenerator * xgenerator_io_new(void);
extern xgenerator * xgenerator_time_new(void);
extern xgenerator * xgenerator_signal_new(void);

#define xgeneratorrun(generator, engine)    generator->run(generator, engine)


struct xgenerators
{
    xuint64 size;
    xgenerator * head;
    xgenerator * tail;
};

#define xgeneratorsinit()   (xgenerators) { 0, xnil, xnil }

#define xengine_status_void     0x00000000U
#define xengine_status_on       0x00000001U

#define xengine_status_cancel   0x80000000U

struct xengine
{
    xuint32 status;
    xeventqueue events;
    xgenerators generators;
};

#define xengineinit()   (xengine) { xengine_status_void, xeventqueueinit() , xgeneratorsinit() }

// event dispatch
// event emit

extern void xengine_event_dispatch(xengine * o, xevent * event);
extern xevent * xengine_event_emit(xengine * o);
extern void xengine_event_process(xengine * o);

extern int xenginerun(xengine * o);

#endif // __NOVEMBERIZING_X__EVENT__H__
