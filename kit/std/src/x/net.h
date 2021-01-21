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
typedef struct xclient xclient;

union xdescriptor
{
    int    f;       /**!< file descriptor */
    void * h;       /**!< handle descriptor */
};

#define xdescriptorinit()               (xdescriptor) { .f = 0 }

extern xint32 xdescriptoralive(const xdescriptor * o);

extern xint32 xdescriptorclose(xdescriptor * o);

#define xobj_type_socket                0x00000100U

struct xsocket
{
    xuint32 flags;
    xdestructor destruct;

    xdescriptor descriptor;

    int domain;
    int type;
    int protocoal;
};

// int domain, int type, int protocol

#define xsocketinit(domain, type, protocol)     (xsocket) { xobj_type_socket, xsocketrem, xdescriptorinit(), domain, type, protocol }
#define xsocketalive(socket)                    (socket ? xdescriptoralive(xaddressof(socket->descriptor)) : xfalse)

extern xsocket * xsocketnew(int domain, int type, int protocol);
extern void * xsocketrem(void * p);
extern xint32 xsocketopen(xsocket * o);
extern xint64 xsocketwrite(xsocket * o, const xbyte * data, xuint64 len);
extern xint64 xsocketread(xsocket * o, void * buffer, xuint64 len);
#define xsocketclose(socket)                    (socket ? xdescriptorclose(xaddressof(socket->descriptor)) : xfail)

#define xobj_type_client            (xobj_type_socket | 0x00000001U)

struct xclient
{
    xuint32 flags;
    xdestructor destruct;

    xdescriptor descriptor;

    int domain;
    int type;
    int protocoal;

    void * addr;
    xuint64 addrlen;
};

#define xclientinit(domain, type, protocol)                         (xclient) { xobj_type_client, xclientrem, xdescriptorinit(), domain, type, protocol, xnil, 0 }
extern xclient * xclientnew(int domain, int type, int protocol);

extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen);
extern xint32 xclientreconnect(xclient * o);
extern xint32 xclientclose(xclient * o);
#define xclientsend(o, data, len)    xsocketwrite((xsocket *) o, data, len);
#define xclientrecv(o, buffer, len)  xsocketread((xsocket *) o, buffer, len);
extern void * xclientrem(void * p);

struct xsession
{
    xsocket socket;
};

struct xserver
{
    xsocket socket;
};



#endif // __NOVEMBERIZING_X__NET__H__
