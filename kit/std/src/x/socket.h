#ifndef   __NOVEMBERIZING_X__SOCKET__H__
#define   __NOVEMBERIZING_X__SOCKET__H__

#include <x/descriptor.h>

struct xsocket
{
    /** INHERITED EVENT OBJECT */
    xdescriptorsub * subscription;
    xsync *          sync;
    xuint32          mask;
    xuint32          status;
    /** INHERITED DESCRIPTOR */
    union
    {
        int    f;
        void * v;
    } handle;
    xint64 (*on)(xdescriptor *, xuint32, void *, xint64);
    xint64 (*process)(xdescriptor *, xuint32, void *);
    xint32 (*need)(xdescriptor *, xuint32);
    /** SOCKET MEMBER */
    xint32 domain;
    xint32 type;
    xint32 protocol;
};

typedef struct xsocket xsocket;

extern xsocket * xsocketnew(xuint64 size);
extern xsocket * xsocketrem(xsocket * o);

#endif // __NOVEMBERIZING_X__SOCKET__H__
