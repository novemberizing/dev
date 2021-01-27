#ifndef   __NOVEMBERIZING_X__NET__H__
#define   __NOVEMBERIZING_X__NET__H__

#include <x/std.h>

struct xdescriptor;
struct xsocket;
struct xsession;
struct xclient;
struct xserver;
struct xdescriptorlist;
struct xpoll;

typedef struct xdescriptorlist xdescriptorlist;
typedef struct xdescriptor xdescriptor;
typedef struct xsocket xsocket;
typedef struct xclient xclient;
typedef struct xserver xserver;
typedef struct xsession xsession;
typedef struct xpoll xpoll;

struct xdescriptor
{
    union
    {
        int    f;       /**!< file descriptor */
        void * h;       /**!< handle descriptor */
    } value;
    xdescriptor * prev; /**!< ... */
    xdescriptor * next; /**!< ... */
    xdescriptorlist * parent;
    xuint32 interest;
    xuint32 masked;
    xsync * sync;
};

/**
 * 
 */
struct xdescriptorlist
{
    xuint32 flags;
    xdestructor destruct;

    xdescriptor * head;
    xdescriptor * tail;
    xuint64 descriptors;

    xsync * sync;
};

#define xdescriptorinit()               (xdescriptor) { { .f = xinvalid }, xnil, xnil, xnil, xdescriptor_event_void, xdescriptor_event_void, xnil }

#define xdescriptor_event_void          0x00000000U
#define xdescriptor_event_read          0x00000001U
#define xdescriptor_event_write         0x00000002U
#define xdescriptor_event_error         0x00000004U
#define xdescriptor_event_pri           0x00000008U
#define xdescriptor_event_readhup       0x00000010U
#define xdescriptor_event_hup           0x00000020U
#define xdescriptor_event_invalid       0x00000040U
#define xdescriptor_event_readband      0x00000080U
#define xdescriptor_event_writeband     0x00000100U
#define xdescriptor_event_timeout       0x00000200U
#define xdescriptor_event_except        0x00000400U

extern xint32 xdescriptoralive(const xdescriptor * o);

extern xint32 xdescriptor_nonblock_on(xdescriptor * o);
extern xint32 xdescriptor_nonblock_off(xdescriptor * o);

extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 nanosecond);

extern xint32 xdescriptorclose(xdescriptor * o);

#define xobj_type_socket                0x00000100U
#define xobj_type_io_facility           0x00000200U

#define xsocket_masks                   0x00FF0000U
#define xsocket_mask_nonblock           0x00010000U

#define xsocket_event_void              xdescriptor_event_void
#define xsocket_event_read              xdescriptor_event_read
#define xsocket_event_write             xdescriptor_event_write
#define xsocket_event_error             xdescriptor_event_error
#define xsocket_event_pri               xdescriptor_event_pri
#define xsocket_event_readhup           xdescriptor_event_readhup
#define xsocket_event_hup               xdescriptor_event_hup
#define xsocket_event_invalid           xdescriptor_event_invalid
#define xsocket_event_readband          xdescriptor_event_readband
#define xsocket_event_writeband         xdescriptor_event_writeband
#define xsocket_event_timeout           xdescriptor_event_timeout
#define xsocket_event_except            xdescriptor_event_except

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

extern xuint32 xsocketwait(xsocket * o, xuint32 mask, xuint64 nanosecond);

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

#define xclient_event_void          xsocket_event_void
#define xclient_event_read          xsocket_event_read
#define xclient_event_write         xsocket_event_write
#define xclient_event_error         xsocket_event_error
#define xclient_event_pri           xsocket_event_pri
#define xclient_event_readhup       xsocket_event_readhup
#define xclient_event_hup           xsocket_event_hup
#define xclient_event_invalid       xsocket_event_invalid
#define xclient_event_readband      xsocket_event_readband
#define xclient_event_writeband     xsocket_event_writeband
#define xclient_event_except        xsocket_event_except
#define xclient_event_timeout       xsocket_event_timeout

#define xclient_event_connect       0x00000800U

// TODO: UPDATE
#define xclient_status_connecting   0x00000001U
#define xclient_status_connected    0x00000002U

#define xclientinit(domain, type, protocol)                         (xclient) { xobj_type_client, xclientrem, xdescriptorinit(), domain, type, protocol, xnil, 0 }
extern xclient * xclientnew(int domain, int type, int protocol);

#define xclientmaskadd(client, mask)    (xclient *) xsocketmaskadd((xsocket *) client, mask)

extern xuint32 xclientwait(xclient * o, xuint32 mask, xuint64 nanosecond);
extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen);
extern xint32 xclientreconnect(xclient * o);
// extern xint32 xclientclose(xclient * o);
#define xclientclose(o)                 xsocketclose(o)
#define xclient_nonblock_on(o)          xsocket_nonblock_on((xsocket *) o)
#define xclient_nonblock_off(o)         xsocket_nonblock_off((xsocket *) o)
#define xclientsend(o, data, len)       xsocketwrite((xsocket *) o, data, len)
#define xclientrecv(o, buffer, len)     xsocketread((xsocket *) o, buffer, len)
extern void * xclientrem(void * p);

#define xobj_type_session           (xobj_type_socket | 0x00000002U)

#define xsession_event_void         xsocket_event_void
#define xsession_event_read         xsocket_event_read
#define xsession_event_write        xsocket_event_write
#define xsession_event_error        xsocket_event_error
#define xsession_event_pri          xsocket_event_pri
#define xsession_event_readhup      xsocket_event_readhup
#define xsession_event_hup          xsocket_event_hup
#define xsession_event_invalid      xsocket_event_invalid
#define xsession_event_readband     xsocket_event_readband
#define xsession_event_writeband    xsocket_event_writeband
#define xsession_event_except       xsocket_event_except
#define xsession_event_timeout      xsocket_event_timeout

// TODO: UPDATE
#define xsession_status_link        0x00000001U

struct xsession
{
    xuint32 flags;
    xdestructor destruct;

    xdescriptor descriptor;

    int domain;
    int type;
    int protocol;

    xuint32 status;

    void * addr;
    xuint64 addrlen;

    xserver * parent;

    xsession * prev;
    xsession * next;

//    xsync * sync;
};

extern xsession * xsessionnew(void);
extern void * xsessionrem(void * p);

typedef xsession * (*xsessionfactory)(void);
typedef void * (*xsessionrelease)(void *);


#define xobj_type_server            (xobj_type_socket | 0x00000003U)

#define xserver_event_void          xsocket_event_void
#define xserver_event_read          xsocket_event_read
#define xserver_event_write         xsocket_event_write
#define xserver_event_error         xsocket_event_error
#define xserver_event_pri           xsocket_event_pri
#define xserver_event_readhup       xsocket_event_readhup
#define xserver_event_hup           xsocket_event_hup
#define xserver_event_invalid       xsocket_event_invalid
#define xserver_event_readband      xsocket_event_readband
#define xserver_event_writeband     xsocket_event_writeband
#define xserver_event_except        xsocket_event_except
#define xserver_event_timeout       xsocket_event_timeout

#define xserver_event_accept        xserver_event_read

struct xserver
{
    xuint32 flags;
    xdestructor destruct;

    xdescriptor descriptor;

    int domain;
    int type;
    int protocol;

    xuint32 status;

    void * addr;
    xuint64 addrlen;

    xint32 backlog;
    xsessionfactory factory;
    xsessionrelease release;

    xsession * head;
    xsession * tail;

    xuint64 alives;

//    xsync * sync;
};

#define xserverinit(domain, type, protocol)                         (xserver) { xobj_type_server, xserverrem, xdescriptorinit(), domain, type, protocol, xnil, 0, xdefaultmaxconn(), xsessionnew, xsessionrem, xnil, xnil, 0, xnil }
extern xserver * xservernew(int domain, int type, int protocol);

#define xservermaskadd(client, mask)    (xserver *) xsocketmaskadd((xserver *) client, mask)

extern xuint32 xserverwait(xserver * o, xuint32 mask, xuint64 nanosecond);
extern xint32 xserverlisten(xserver * o, void * addr, xuint64 addrlen);
extern xint32 xserverrelisten(xserver * o);

// extern xint32 xclientclose(xclient * o);

#define xserverclose(o)                 xsocketclose(o)
#define xserver_nonblock_on(o)          xsocket_nonblock_on((xsocket *) o)
#define xserver_nonblock_off(o)         xsocket_nonblock_off((xsocket *) o)

extern void * xserverrem(void * p);

extern xsession * xserveraccept(xserver * o);

#define xobj_type_poll                  (xobj_type_io_facility | 0x00000001U)

struct xpoll
{
    xuint32 flags;
    xdestructor destruct;

    xdescriptor * head;
    xdescriptor * tail;
    xuint64 descriptors;

    xsync * sync;
};

#define xpollinit()         (xpoll) { xobj_type_poll, xpollrem, xnil, xnil, 0, xnil }
extern xpoll * xpollnew(void);
extern void * xpollrem(void * p);
// extern void xpolladd(xdescriptor )

#endif // __NOVEMBERIZING_X__NET__H__
