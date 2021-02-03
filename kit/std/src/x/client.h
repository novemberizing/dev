#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/socket.h>

struct xclient;

typedef struct xclient xclient;

typedef xint64 (*xclient_event_handler)(xclient *, xuint32, const void *, xint64);

struct xclient
{
    xsocket * descriptor;
    void *    addr;
    xuint32   addrlen;
    struct
    {
        xstream * in;
        xstream * out;
    } stream;
};

extern xclient * xclient_new(int domain, int type, int protocol, xclient_event_handler handler, xuint64 size);
extern xint32 xclient_connect(xclient * client, void * addr, xuint32 addrlen);

#endif // __NOVEMBERIZING_X__CLIENT__H__
