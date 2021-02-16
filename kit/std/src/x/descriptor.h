#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include <x/event.h>

#define xdescriptor_event_void          (0x00000000u)
#define xdescriptor_event_open          (0x00000001u)
#define xdescriptor_event_in            (0x00000002u)
#define xdescriptor_event_out           (0x00000004u)
#define xdescriptor_event_close         (0x00000008u)
#define xdescriptor_event_exception     (0x00000010u)

#define xdescriptor_status_void         xdescriptor_event_void
#define xdescriptor_status_open         xdescriptor_event_open
#define xdescriptor_status_in           xdescriptor_event_in
#define xdescriptor_status_out          xdescriptor_event_out
#define xdescriptor_status_close        xdescriptor_event_close
#define xdescriptor_status_exception    xdescriptor_event_exception

struct xdescriptor;
struct xdescriptorsub;
struct xdescriptorsubs;
struct xdescriptoreventgen;

typedef struct xdescriptor xdescriptor;
typedef struct xdescriptorsub xdescriptorsub;
typedef struct xdescriptorsubs xdescriptorsubs;
typedef struct xdescriptoreventgen xdescriptoreventgen;

typedef xint64 (*xdescriptor_event_handler)(xdescriptor *, xuint32, const void *, xint64);
typedef xint64 (*xdescriptor_event_processor)(xdescriptor *, xuint32);

struct xdescriptor
{
    xdescriptorsub * subscription;
    union
    {
        int f;
        void * v;
    } handle;
    xuint32 mask;
    xuint32 status;
    xsync * sync;
    xint64  (*on)(xdescriptor *, xuint32, const void *, xuint64, xint64);
    xint64  (*process)(xdescriptor *, xuint32, const void *, xuint64);
};

extern xint64 xdescriptorevent_dispatch(xdescriptor * descriptor, xuint32 event, const void * data, xuint64 size);
extern xint64 xdescriptorevent_process(xdescriptor * descriptor, xuint32 event, const void * data, xuint64 size);
extern xint64 xdescriptorevent_finish(xdescriptor * descriptor, xuint32 event, const void * data, xuint64 size, xint64 result);
extern xint32 xdescriptorexist_out(xdescriptor * descriptor);
// xdescriptorevent_dispatch
// xdescriptorevent_process
// xdescriptorevent_quit

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
