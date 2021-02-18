#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include <x/io.h>
#include <x/sync.h>

#include <x/descriptor/handle.h>
#include <x/descriptor/subscription.h>

typedef xint64 (*xdescriptorprocessor)(xdescriptor *, xuint32, void *);
typedef xint64 (*xdescriptorsubscriber)(xdescriptor *, xuint32, void *, xint64);
typedef xint32 (*xdescriptorstatuschecker)(xdescriptor *, xuint32);

struct xdescriptor
{
    /** INHERITED EVENT TARGET */
    xdescriptordestructor     rem;
    xdescriptorsubscription * subscription;
    xsync *                   sync;
    xuint32                   mask;
    xuint32                   status;
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle         handle;
    xdescriptorprocessor      process;
    xdescriptorstatuschecker  check;
    xdescriptorsubscriber     on;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
