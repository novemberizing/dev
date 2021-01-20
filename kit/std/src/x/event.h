#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xeventobj;
struct xeventgenerator;
struct xeventengine;

typedef struct xevent xevent;
typedef struct xeventobj xeventobj;
typedef struct xeventgenerator xeventgenerator;
typedef struct xeventengine xeventengine;

typedef void (*xeventsignalhandler)(xint32, xint32, xeventobj *, void *, xeventgenerator *, xeventengine *);

#define xevent_mask_categories                  0xFF000000U
#define xevent_mask_types                       0x0000FFFFU

#define xevent_category_io                      0x01000000U
#define xevent_category_signal                  0x02000000U
#define xevent_category_time                    0x03000000U

#define xevent_category_custom                  0xFF000000U

#define xeventengine_mask_status                0x00FFFFFFU

#define xeventengine_allocated                  0x80000000U

#define xeventengine_status_void                0x00000000U
#define xeventengine_status_on                  0x00000001U
#define xeventengine_status_main_cusuming_off   0x00000002U
#define xeventengine_status_cancel              0x00800000U

#define xeventcategory(event)                   (event->type & xevent_mask_categories)
#define xeventtype(event)                       (event->type & xevent_mask_types)

#define xeventenginestatus(engine)              (engine->status & xeventengine_mask_status)
#define xeventengineallocated(engine)           (engine->status & xeventengine_allocated)

struct xevent
{
    xuint32 type;
    xeventgenerator * from;
};

struct xeventgenerator
{

};

struct xeventengine
{
    xuint32 status;
    xlist generators;
    void (*internal)(xeventengine *);
    xlist queue;
    xlist processors;
    xevent * (*handler)(xevent *, xeventengine *);
    xeventsignalhandler * signals;
};

struct xeventobj
{

};

#define xeventengineinit()  (xeventengine) { 0, xlistinit(), xnil, xlistinit(), xlistinit(), xnil }

extern void xeventengineon(void);

extern xthreadlocal * xeventenginethreadlocal(void);

extern xeventengine * xeventenginenew(void);

#define xeventengine_internal_func(engine, func)  (engine->internal = func)

extern void xeventengine_signal_handler_set(xeventengine * o, xint32 no, xeventsignalhandler handler);
extern void xeventengine_signal_handler_del(xeventengine * o, xint32 no);

extern xint32 xeventenginerun(xeventengine * o);

#define xeventenginecancel(o)   (o->status |= xeventengine_status_cancel)

#endif // __NOVEMBERIZING_X__EVENT__H__
