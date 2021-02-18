#ifndef   __NOVEMBERIZING_X__CLIENT__SOCKET__H__
#define   __NOVEMBERIZING_X__CLIENT__SOCKET__H__

#include <x/socket.h>
#include <x/socket/stream.h>
#include <x/socket/subscription.h>

struct xclientsocket;

typedef struct xclientsocket xclientsocket;

typedef xclientsocket * (*xclientsocketdestructor)(xclientsocket *);

typedef xint64 (*xclientsocketprocessor)(xclientsocket *, xuint32, void *);
typedef xint64 (*xclientsocketstatuschecker)(xclientsocket *, xuint32, void *, xint64);
typedef xint32 (*xclientsocketsubscriber)(xclientsocket *, xuint32);

struct xclientsocket
{
    /** INHERITED EVENT TARGET */
    xclientsocketdestructor    rem;
    xsocketsubscription *      subscription;
    xsync *                    sync;
    xuint32                    mask;
    xuint32                    status;
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle          handle;
    xclientsocketprocessor     process;
    xclientsocketstatuschecker check;
    xclientsocketsubscriber    on;
    /** INHERITED SOCKET */
    xint32                     domain;
    xint32                     type;
    xint32                     protocol;
    /** CLIENT SOCKT MEMBER */
    void *                     addr;
    xuint32                    addrlen;
    xsocketstream              stream;
};

extern xclientsocket * xclientsocket_new(int domain, int type, int protocol, const void * addr, xuint32 addrlen, xuint32 mask);

#endif // __NOVEMBERIZING_X__CLIENT__SOCKET__H__
