#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include <x/sync.h>
#include <x/descriptor/subscription.h>

struct xdescriptor;

typedef struct xdescriptor xdescriptor;

struct xdescriptor
{
    /** INHERITED EVENT TARGET */
    xdescriptorsubscription * subscription;
    xsync *                   sync;
    xuint32                   mask;
    xuint32                   status;


};

// #include <x/stream.h>
// #include <x/event.h>
// #include <x/event/object.h>

// #define xdescriptor_event_void          (0x00000000u)
// #define xdescriptor_event_open          (0x00000001u)
// #define xdescriptor_event_in            (0x00000002u)
// #define xdescriptor_event_out           (0x00000004u)
// #define xdescriptor_event_close         (0x00000008u)
// #define xdescriptor_event_exception     (0x00000010u)

// #define xdescriptor_status_void         xdescriptor_event_void
// #define xdescriptor_status_open         xdescriptor_event_open
// #define xdescriptor_status_in           xdescriptor_event_in
// #define xdescriptor_status_out          xdescriptor_event_out
// #define xdescriptor_status_close        xdescriptor_event_close
// #define xdescriptor_status_exception    xdescriptor_event_exception

// struct xdescriptor;
// struct xdescriptorsub;
// struct xdescriptorsubs;
// struct xdescriptoreventgen;

// typedef struct xdescriptor xdescriptor;
// typedef struct xdescriptorsub xdescriptorsub;
// typedef struct xdescriptorsubs xdescriptorsubs;
// typedef struct xdescriptoreventgen xdescriptoreventgen;

// typedef xint64 (*xdescriptor_event_handler)(xdescriptor *, xuint32, const void *, xint64);
// typedef xint64 (*xdescriptor_event_processor)(xdescriptor *, xuint32);

// struct xdescriptor
// {
//     xdescriptorsub * subscription;
//     xsync *          sync;
//     xuint32          mask;
//     xuint32          status;

//     union
//     {
//         int    f;
//         void * v;
//     } handle;

//     xint64 (*on)(xdescriptor *, xuint32, void *, xint64);
//     xint64 (*process)(xdescriptor *, xuint32, void *);
//     xint32 (*need)(xdescriptor *, xuint32);
// };

// #define xdescriptorlock(o)                                      xeventobject_lock(o)
// #define xdescriptorunlock(o)                                    xeventobject_unlock(o)
// #define xdescriptorwait(o, second, nanosecond)                  xeventobject_wait(o, second, nanosecond)
// #define xdescriptorwakeup(o, all)                               xeventobject_wakeup(o, all)

// #define xdescriptorstatus_has(o, status)                        xeventobject_status_has(o, status)
// #define xdescriptorstatus_add(o, status)                        xeventobject_status_add(o, status)
// #define xdescriptorstatus_del(o, status)                        xeventobject_status_del(o, status)

// #define xdescriptormask_has(o, mask)                            xeventobject_mask_has(o, mask)
// #define xdescriptormask_add(o, mask)                            xeventobject_mask_add(o, mask)
// #define xdescriptormask_del(o, mask)                            xeventobject_mask_del(o, mask)

// #define xdescriptorprocess(descriptor, event, parameter)        descriptor->process(descriptor, event, parameter)
// #define xdescriptoron(descriptor, event, parameter, result)     descriptor->on(descriptor, event, parameter, result)
// #define xdescriptorneed(descriptor, event)                      descriptor->need(descriptor, event)

// extern xint32 xdescriptoralive(xdescriptor * descriptor);

// extern xdescriptor * xdescriptornew(xuint64 size);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
