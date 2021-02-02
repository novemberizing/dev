#ifndef   __NOVEMBERIZING_X__NET__H__
#define   __NOVEMBERIZING_X__NET__H__

#include <x/std.h>

// EVENT //////////////////////////////////////////////////////

struct xeventobj;

typedef struct xeventobj xeventobj;

typedef xeventobj * (*xeventobjfactory)(xeventobj *);
typedef void (*xeventobjreleaser)(xeventobj *, xeventobj *);

struct xeventobj
{
    xuint32     flags;
    xdestructor destruct;

    xsync *     sync;

    xeventobj * prev;
    xeventobj * next;
    xeventobj * parent;

    struct
    {
        xeventobj * head;
        xeventobj * tail;
        xuint64     total;
    } children;

    xeventobjfactory create;
    xeventobjreleaser release;
};

// DESCRIPTOR /////////////////////////////////////////////////

#define xdescriptor_mask_void           (0x00000000U)
#define xdescriptor_mask_nonblock       (0x00000001U)

#define xdescriptor_event_void          (0x00000000U)
#define xdescriptor_event_in            (0x00000001U)
#define xdescriptor_event_out           (0x00000002U)
#define xdescriptor_event_closein       (0x00000004U)
#define xdescriptor_event_closeout      (0x00000008U)
#define xdescriptor_event_closeall      (xdescriptor_event_closein | xdescriptor_event_closeout)
#define xdescriptor_event_close         (0x00000010U)
#define xdescriptor_event_exception     (0x00000020U)
#define xdescriptor_event_open          (0x00000040U)
#define xdescriptor_event_connect       (0x00000080U)
#define xdescriptor_event_connecting    (0x00000100U)
#define xdescriptor_event_invalid       (0x00000200U)
#define xdescriptor_event_timeout       (0x00000400U)
#define xdescriptor_event_bind          (0x00000800U)
#define xdescriptor_event_listen        (0x00001000U)

#define xdescriptor_status_void         xdescriptor_event_void
#define xdescriptor_status_in           xdescriptor_event_in
#define xdescriptor_status_out          xdescriptor_event_out
#define xdescriptor_status_closein      xdescriptor_event_closein
#define xdescriptor_status_closeout     xdescriptor_event_closeout
#define xdescriptor_status_closeall     xdescriptor_event_closeall
#define xdescriptor_status_close        xdescriptor_event_close
#define xdescriptor_status_exception    xdescriptor_event_exception
#define xdescriptor_status_open         xdescriptor_event_open
#define xdescriptor_status_connect      xdescriptor_event_connect
#define xdescriptor_status_connecting   xdescriptor_event_connecting
#define xdescriptor_status_invalid      xdescriptor_event_invalid
#define xdescriptor_status_timeout      xdescriptor_event_timeout
#define xdescriptor_status_bind         xdescriptor_event_bind
#define xdescriptor_status_listen       xdescriptor_event_listen

extern void xdescriptordebug_event_mask(xuint32 mask);

struct xdescriptor;
struct xdescriptorio;

typedef struct xdescriptor xdescriptor;
typedef struct xdescriptorio xdescriptorio;

typedef xint64 (*xdescriptoreventon)(xdescriptor *, void *, xuint32, const void *, xval);

struct xdescriptor
{
    union
    {
        int    f;
        void * p;
    } handle;

    xuint32 mask;
    xuint32 status;

    xsync * sync;

    xdescriptor * prev;
    xdescriptor * next;
    xdescriptorio * io;

    void * data;

    xdescriptoreventon on;

    xint32 (*open)(xdescriptor *);
};

#define xdescriptorinit(data, handler) (xdescriptor) {  \
    { .f = xinvalid },                                  \
    xdescriptor_mask_void,                              \
    xdescriptor_status_void,                            \
    xnil,                                               \
    xnil,                                               \
    xnil,                                               \
    xnil,                                               \
    data,                                               \
    handler,                                            \
    xnil }

extern xint32  xdescriptoralive(xdescriptor * descriptor);
extern xint32  xdescriptorclose(xdescriptor * descriptor);
extern xint64  xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size);
extern xint64  xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len);
extern void    xdescriptornonblock_on(xdescriptor * descriptor);
extern void    xdescriptornonblock_off(xdescriptor * descriptor);
extern void    xdescriptormask_nonblock_on(xdescriptor * descriptor);
extern void    xdescriptormask_nonblock_off(xdescriptor * descriptor);
extern xuint32 xdescriptorwait(xdescriptor * descriptor, xuint32 mask, xint64 second, xint64 nanosecond);

#define xdescriptoreventpub(descriptor, parent, mask, data, val)    \
((descriptor && descriptor->on)                                     \
    ? descriptor->on(descriptor, parent, mask, data, val)           \
    : xfail)

#define xdescriptoropen(descriptor)     descriptor->open(descriptor)

struct xdescriptorio
{
    xsync * sync;

    xdescriptor * head;
    xdescriptor * tail;
    xuint64       total;

    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint64       total;
    } queue;
};

extern xdescriptorio * xdescriptorionew(void);
extern void * xdescriptoriorem(void * p);
extern void xdescriptoriocall(xdescriptorio * o);

extern void xdescriptorioreg(xdescriptorio * o, xdescriptor * descriptor);
extern void xdescriptoriounreg(xdescriptorio * o, xdescriptor * descriptor);
// SOCKET /////////////////////////////////////////////////////

struct xsocket;

typedef struct xsocket xsocket;

typedef xint64 (*xsocketeventon)(xsocket *, void *, xuint32, const void *, xval);

struct xsocket
{
    union
    {
        int    f;
        void * p;
    } handle;

    xuint32 mask;
    xuint32 status;

    xsync * sync;

    xdescriptor * prev;
    xdescriptor * next;
    xdescriptorio * io;

    void * data;

    xsocketeventon on;
    xint32 (*open)(xdescriptor *);

    int domain;
    int type;
    int protocol;
};

#define xsocketinit(domain, type, protocol, handler) (xsocket) {    \
    { .f = xinvalid },                                              \
    xdescriptor_mask_void,                                          \
    xdescriptor_status_void,                                        \
    xnil,                                                           \
    xnil,                                                           \
    xnil,                                                           \
    xnil,                                                           \
    xnil,                                                           \
    handler,                                                        \
    xnil,                                                           \
    domain,                                                         \
    type,                                                           \
    protocol }

#define xsocketalive(socket)                                xdescriptoralive((xdescriptor *) socket)
#define xsocketclose(socket)                                xdescriptorclose((xdescriptor *) socket)
#define xsocketread(socket, buffer, size)                   xdescriptorread((xdescriptor *) socket, buffer, size)
#define xsocketwrite(socket, data, len)                     xdescriptorwrite((xdescriptor *) socket, data, len)
#define xsocketmask_nonblock_on(socket)                     xdescriptormask_nonblock_on((xdescriptor *) socket)
#define xsocketmask_nonblock_off(socket)                    xdescriptormask_nonblock_off((xdescriptor *) socket)
#define xsocketnonblock_on(socket)                          xdescriptornonblock_on((xdescriptor *) socket)
#define xsocketnonblock_off(socket)                         xdescriptornonblock_off((xdescriptor *) socket)
#define xsocketwait(descriptor, mask, second, nanosecond)   xdescriptorwait((xdescriptor *) socket, mask, second, nanosecond)

#define xsocketeventpub(socket, parent, mask, data, val)    xdescriptoreventpub(((xdescriptor *) socket), parent, mask, data, val)

extern xint32 xsocketopen(xsocket * socket);
extern xint32 xsocketshutdown(xsocket * socket, xuint32 how);
extern xint32 xsocketbind(xsocket * socket, void * addr, xuint64 addrlen);

// NETWORK ////////////////////////////////////////////////////

struct xclient;
struct xsession;
struct xserver;

typedef struct xclient xclient;
typedef struct xsession xsession;
typedef struct xserver xserver;

typedef xint64 (*xclienteventon)(xsocket *, void *, xuint32, const void *, xval);

struct xclient
{
    xuint32     flags;
    xdestructor destruct;

    xsync *     sync;

    xeventobj * prev;
    xeventobj * next;
    xeventobj * parent;

    struct
    {
        xeventobj * head;
        xeventobj * tail;
        xuint64     total;
    } children;

    xeventobjfactory create;
    xeventobjreleaser release;

    struct
    {
        union
        {
            int    f;
            void * p;
        } handle;

        xuint32 mask;
        xuint32 status;

        xsync * sync;

        xdescriptor * prev;
        xdescriptor * next;
        xdescriptorio * io;

        void * data;

        xclienteventon on;

        xint32 (*open)(xdescriptor *);

        int domain;
        int type;
        int protocol;
    } socket;

    void *    addr;
    xuint64   addrlen;

    xbuffer * readbuf;
    xbuffer * writebuf;
};

#define xclientinit(domain, type, protocol) (xclient) {         \
    0,                                                          \
    xclientrem,                                                 \
    xnil,                                                       \
    xnil,                                                       \
    xnil,                                                       \
    xnil,                                                       \
    { xnil, xnil, 0 },                                          \
    xnil,                                                       \
    xnil,                                                       \
    {                                                           \
        { .f = xinvalid },                                      \
        xdescriptor_mask_void,                                  \
        xdescriptor_status_void,                                \
        xnil,                                                   \
        xnil,                                                   \
        xnil,                                                   \
        xnil,                                                   \
        xnil,                                                   \
        xclientsocketeventon,                                   \
        xclientopen,                                            \
        domain,                                                 \
        type,                                                   \
        protocol                                                \
    },                                                          \
    xnil,                                                       \
    0,                                                          \
    xnil,                                                       \
    xnil }

extern xint64    xclientsocketeventon(xsocket * socket, void * parent, xuint32 mask, const void * data, xval val);
extern xclient * xclientnew(int domain, int type, int protocol);
extern void *    xclientrem(void * p);
extern xint32    xclientconnect(xclient * client, void * addr, xuint64 addrlen);
extern xuint32   xclientwait(xclient * client, xuint32 mask, xint64 second, xint64 nanosecond);
extern xint32    xclientclose(xclient * client);
extern xint32    xclientopen(xdescriptor * descriptor);

#define xclientalive(client)                                (client ? xdescriptoralive((xdescriptor *) xaddressof(client->socket)) : xfalse)
#define xclientread(client, buffer, size)                   xdescriptorread((xdescriptor *) xaddressof(client->socket), buffer, size)
#define xclientwrite(client, data, len)                     xdescriptorwrite((xdescriptor *) xaddressof(client->socket), data, len)
#define xclientmask_nonblock_on(client)                     (client ? xdescriptormask_nonblock_on((xdescriptor *) xaddressof(client->socket)) : xfail)
#define xclientmask_nonblock_off(client)                    (client ? xdescriptormask_nonblock_off((xdescriptor *) xaddressof(client->socket)) : xfail)

#define xclientnonblock_on(client)                          xdescriptornonblock_on((xdescriptor *) (client ? xaddressof(client->socket) : xnil))
#define xclientnonblock_off(client)                         xdescriptornonblock_off((xdescriptor *) (client ? xaddressof(client->socket) : xnil))

#define xclienteventpub(socket, parent, mask, data, val)    xdescriptoreventpub(((xdescriptor *) socket), parent, mask, data, val)

#define xclientshutdown(client, how)                        (client ? xsocketshutdown((xsocket *) xaddressof(client->socket), how) : xfail)

typedef xint64 (*xsessioneventon)(xsession *, void *, xuint32, const void *, xval);
typedef xeventobj * (*xsessioneventobjfactory)(xsession *);
typedef void (*xsessioneventobjreleaser)(xsession *, xeventobj *);

struct xsession
{
    xuint32     flags;
    xdestructor destruct;

    xsync *     sync;

    xeventobj * prev;
    xeventobj * next;
    xeventobj * parent;

    struct
    {
        xeventobj * head;
        xeventobj * tail;
        xuint64     total;
    } children;

    xeventobjfactory create;
    xeventobjreleaser release;

    struct
    {
        union
        {
            int    f;
            void * p;
        } handle;

        xuint32 mask;
        xuint32 status;

        xsync * sync;

        xdescriptor * prev;
        xdescriptor * next;
        xdescriptorio * io;

        void * data;

        xsessioneventon on;
        xint32 (*open)(xdescriptor *);

        int domain;
        int type;
        int protocol;
    } socket;

    xbuffer * readbuf;
    xbuffer * writebuf;
};

extern xint64     xsessionsocketeventon(xsession * o, void * parent, xuint32 mask, const void * data, xval val);

extern xsession * xsessionnew(void);
extern void *     xsessionrem(void * p);
extern xint32     xsessionclose(xsession * session);

#define xsessionalive(session)                              (session ? xdescriptoralive((xdescriptor *) xaddressof(session->socket)) : xfalse)
#define xsessionread(session, buffer, size)                 xdescriptorread((xdescriptor *) xaddressof(session->socket), buffer, size)
#define xsessionwrite(session, data, len)                   xdescriptorwrite((xdescriptor *) xaddressof(session->socket), data, len)
#define xsessionmask_nonblock_on(session)                   (session ? xdescriptormask_nonblock_on((xdescriptor *) xaddressof(session->socket)) : xfail)
#define xsessionmask_nonblock_off(session)                  (session ? xdescriptormask_nonblock_off((xdescriptor *) xaddressof(session->socket)) : xfail)

#define xsessionnonblock_on(session)                        xdescriptornonblock_on((xdescriptor *) (session ? xaddressof(session->socket) : xnil))
#define xsessionnonblock_off(session)                       xdescriptornonblock_off((xdescriptor *) (session ? xaddressof(session->socket) : xnil))

#define xsessioneventpub(socket, parent, mask, data, val)   xdescriptoreventpub(((xdescriptor *) socket), parent, mask, data, val)

#define xsessionopen(session)                               (session ? xsocketopen((xsocket *) xaddressof(session->socket)) : xfail)
#define xsessionshutdown(session, how)                      (session ? xsocketshutdown((xsocket *) xaddressof(session->socket), how) : xfail)

#define xsessionwait(session, mask, second, nanosecond) xdescriptorwait((xdescriptor *) xaddressof(session->socket), mask, second, nanosecond)

typedef xint64 (*xservereventon)(xdescriptor *, void *, xuint32, const void *, xval);

struct xserver
{
    xuint32     flags;
    xdestructor destruct;

    xsync *     sync;

    xeventobj * prev;
    xeventobj * next;
    xeventobj * parent;

    struct
    {
        xeventobj * head;
        xeventobj * tail;
        xuint64     total;
    } children;

    xeventobjfactory create;
    xeventobjreleaser release;

    struct
    {
        union
        {
            int    f;
            void * p;
        } handle;

        xuint32 mask;
        xuint32 status;

        xsync * sync;

        xdescriptor * prev;
        xdescriptor * next;
        xdescriptorio * io;

        void * data;

        xservereventon on;
        xint32 (*open)(xdescriptor *);

        int domain;
        int type;
        int protocol;
    } socket;

    void *    addr;
    xuint64   addrlen;

    int       backlog;
};

#define xserverinit(domain, type, protocol) (xserver) {     \
    0,                                                      \
    xserverrem,                                             \
    xnil,                                                   \
    xnil,                                                   \
    xnil,                                                   \
    xnil,                                                   \
    { xnil, xnil, 0 },                                      \
    xnil,                                                   \
    xnil,                                                   \
    {                                                       \
        { .f = xinvalid },                                  \
        0,                                                  \
        0,                                                  \
        xnil,                                               \
        xnil,                                               \
        xnil,                                               \
        xnil,                                               \
        xnil,                                               \
        xserversocketeventon,                               \
        xserveropen,                                        \
        domain,                                             \
        type,                                               \
        protocol                                            \
    },                                                      \
    xnil,                                                   \
    0,                                                      \
    xdefaultserverbacklog() }

extern xeventobj * xdefaultsessionfactory(xeventobj * child);
extern void xdefaultsessionreleaser(xeventobj * o, xeventobj * child);
extern int xdefaultserverbacklog(void);

extern xint64    xserversocketeventon(xdescriptor * o, void * parent, xuint32 mask, const void * data, xval val);

extern xserver * xservernew(int domain, int type, int protocol, void * addr, xuint64 addrlen);
extern void *    xserverrem(void * p);
extern xint32    xserverclose(xserver * server);
extern xint32    xserverbind(xserver * server, void * addr, xuint64 addrlen);
extern xint32    xserverlisten(xserver * server, void * addr, xuint64 addrlen);
extern xint32    xserveropen(xdescriptor * descriptor);
extern xsession * xserveraccept(xserver * server);

#define xserveralive(server)                                (server ? xdescriptoralive((xdescriptor *) xaddressof(server->socket)) : xfalse)

#define xservermask_nonblock_on(server)                     (server ? xdescriptormask_nonblock_on((xdescriptor *) xaddressof(server->socket)) : xfail)
#define xservermask_nonblock_off(server)                    (server ? xdescriptormask_nonblock_off((xdescriptor *) xaddressof(server->socket)) : xfail)

#define xservernonblock_on(server)                          xdescriptornonblock_on((xdescriptor *) (server ? xaddressof(server->socket) : xnil))
#define xservernonblock_off(server)                         xdescriptornonblock_off((xdescriptor *) (session ? xaddressof(server->socket) : xnil))

#define xservereventpub(socket, parent, mask, data, val)    xdescriptoreventpub(((xdescriptor *) socket), parent, mask, data, val)

#define xservershutdown(server, how)                        (server ? xsocketshutdown((xsocket *) xaddressof(server->socket), how) : xfail)

#define xserverwait(server, mask, second, nanosecond)       xdescriptorwait((xdescriptor *) xaddressof(server->socket), mask, second, nanosecond)

/* NETWORK EVENT IO ***************************************************/

#endif // __NOVEMBERIZING_X__NET__H__
