#ifndef   __NOVEMBERIZING_X__NET__H__
#define   __NOVEMBERIZING_X__NET__H__

#include <x/std.h>

union xdescriptor;
struct xsocket;
struct xsession;
struct xclient;
struct xserver;

typedef union xdescriptor xdescriptor;
typedef struct xsocket xsocket;

union xdescriptor
{
    int    f;       /**!< file descriptor */
    void * h;       /**!< handle descriptor */
};

#define xdescriptorinit()               (xdescriptor) { .f = 0 }

extern xint32 xdescriptoralive(const xdescriptor * o);

extern xint32 xdescriptorclose(xdescriptor * o);

struct xsocket
{
    xdescriptor descriptor;

    int domain;
    int type;
    int protocoal;
};

// int domain, int type, int protocol

#define xsocketinit(domain, type, protocol)     (xsocket) { xdescriptorinit(), domain, type, protocol }
#define xsocketalive(socket)                    (socket ? xdescriptoralive(xaddressof(socket->descriptor)) : xfalse)

extern xint32 xsocketopen(xsocket * o);
#define xsocketclose(socket)                    (socket ? xdescriptorclose(xaddressof(socket->descriptor)) : xfail)


struct xclient
{
    xsocket socket;
};

struct xsession
{
    xsocket socket;
};

struct xserver
{
    xsocket socket;
};



#endif // __NOVEMBERIZING_X__NET__H__
