#ifndef   __NOVEMBERIZING_X__SOCKET__H__
#define   __NOVEMBERIZING_X__SOCKET__H__

#include <x/io.h>

#include <x/descriptor.h>

typedef xint64 (*xsocketprocessor)(xsocket *, xuint32, void *);
typedef xint64 (*xsocketsubscriber)(xsocket *, xuint32, void *, xint64);
typedef xint32 (*xsocketstatuschecker)(xsocket *, xuint32);

struct xsocket
{
    /** INHERITED EVENT TARGET */
    xsocketdestructor     rem;
    xsocketsubscription * subscription;
    xsync *               sync;
    xuint32               mask;
    xuint32               status;
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle     handle;
    xsocketprocessor      process;
    xsocketstatuschecker  check;
    xsocketsubscriber     on;
    /** SOCKET MEMBER */
    xint32                domain;
    xint32                type;
    xint32                protocol;
};

#endif // __NOVEMBERIZING_X__SOCKET__H__
