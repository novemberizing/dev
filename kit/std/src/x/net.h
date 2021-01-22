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

extern xint32 xdescriptor_nonblock_on(xdescriptor * o);
extern xint32 xdescriptor_nonblock_off(xdescriptor * o);

extern xint32 xdescriptorclose(xdescriptor * o);

#define xobj_type_socket                0x00000100U

#define xsocket_masks                   0x00FF0000U
#define xsocket_mask_nonblock           0x00010000U

struct xsocket
{
    xuint32 flags;
    xdestructor destruct;

    xdescriptor descriptor;

    int domain;
    int type;
    int protocoal;

    xuint32 status;
};

// int domain, int type, int protocol

#define xsocketinit(domain, type, protocol)     (xsocket) { xobj_type_socket, xsocketrem, xdescriptorinit(), domain, type, protocol }
#define xsocketalive(socket)                    (socket ? xdescriptoralive(xaddressof(socket->descriptor)) : xfalse)
#define xsocketmask(socket)                     (socket->flags & xsocket_masks)

// #define xsocket_nonblock_on(socket)             (socket ? xdescriptor_nonblock_on(xaddressof(socket->descriptor)) : xfail)

extern xint32 xsocket_nonblock_on(xsocket * o);
extern xint32 xsocket_nonblock_off(xsocket * o);

// extern xint32 xsocket_nonblock_on()
extern xsocket * xsocketnew(int domain, int type, int protocol);


extern xsocket * xsocketmaskadd(xsocket * o, xuint32 mask);

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

    xuint32 status;

    void * addr;
    xuint64 addrlen;
};

// TODO: UPDATE
#define xclient_status_connecting    0x00000001U
#define xclient_status_connected     0x00000002U

#define xclientinit(domain, type, protocol)                         (xclient) { xobj_type_client, xclientrem, xdescriptorinit(), domain, type, protocol, xnil, 0 }
extern xclient * xclientnew(int domain, int type, int protocol);

#define xclientmaskadd(client, mask)    (xclient *) xsocketmaskadd((xsocket *) client, mask)

extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen);
extern xint32 xclientreconnect(xclient * o);
extern xint32 xclientclose(xclient * o);
#define xclient_nonblock_on(o)          xsocket_nonblock_on((xsocket *) o)
#define xclient_nonblock_off(o)         xsocket_nonblock_off((xsocket *) o)
#define xclientsend(o, data, len)       xsocketwrite((xsocket *) o, data, len)
#define xclientrecv(o, buffer, len)     xsocketread((xsocket *) o, buffer, len)
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
