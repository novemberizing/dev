#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include <x/event.h>

#define xdescriptor_event_open      (0x00000001u)
#define xdescriptor_event_in        (0x00000002u)
#define xdescriptor_event_out       (0x00000004u)
#define xdescriptor_event_close     (0x00000008u)
#define xdescriptor_event_exception (0x00000010u)

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
    xsubscription * subscription;
    xint32  handle;
    xuint32 mask;
    xuint32 status;
    xsync * sync;
    void    (*on)(xdescriptor *, xuint32, const void *, xint64);
    xint32  (*process)(xdescriptor *, xuint32);
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
