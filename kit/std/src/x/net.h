#ifndef   __NOVEMBERIZING_X__NET__H__
#define   __NOVEMBERIZING_X__NET__H__

#include <x/std.h>

// EVENT //////////////////////////////////////////////////////

struct xeventobj;

typedef struct xeventobj xeventobj;

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

struct xdescriptor;
struct xdescriptorio;

typedef struct xdescriptor xdescriptor;
typedef struct xdescriptorio xdescriptorio;

typedef xint64 (*xdescriptoreventon)(xdescriptor *, xuint32, const void *, xval);

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
    handler }

extern xint32 xdescriptoralive(xdescriptor * descriptor);
extern xint32 xdescriptorclose(xdescriptor * descriptor);
extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size);
extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len);
extern void xdescriptornonblock_on(xdescriptor * descriptor);
extern void xdescriptornonblock_off(xdescriptor * descriptor);
extern void xdescriptormask_nonblock_on(xdescriptor * descriptor);
extern void xdescriptormask_nonblock_off(xdescriptor * descriptor);
extern xuint32 xdescriptorwait(xdescriptor * descriptor, xuint32 mask, xint64 second, xint64 nanosecond);

#define xdescriptoreventpub(descriptor, mask, data, val)    \
((descriptor && descriptor->on)                             \
    ? descriptor->on(descriptor, mask, data, val)           \
    : xfail)

struct xdescriptorio
{
    xsync * sync;

    xdescriptor * head;
    xdescriptor * tail;
    xuint64       total;
};

extern void xdescriptorioadd(xdescriptorio * o, xdescriptor * descriptor);
extern void xdescriptoriodel(xdescriptorio * o, xdescriptor * descriptor);

// SOCKET /////////////////////////////////////////////////////

struct xsocket;

typedef struct xsocket xsocket;

typedef xint64 (*xsocketeventon)(xsocket *, xuint32, const void *, xval);

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

#define xsocketeventpub(socket, mask, data, val)    \
((socket && socket->on)                             \
    ? socket->on(socket, mask, data, val)           \
    : xfail)

extern xint32 xsocketopen(xsocket * socket);
extern xint32 xsocketshutdown(xsocket * socket, xuint32 how);

// NETWORK ////////////////////////////////////////////////////

struct xclient;
struct xsession;
struct xserver;

typedef struct xclient xclient;
typedef struct xsession xsession;
typedef struct xserver xserver;

typedef xint64 (*xclienteventon)(xclient *, xuint32, const void *, xval);

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

        int domain;
        int type;
        int protocol;
    } socket;

    void *    addr;
    xuint64   addrlen;

    xbuffer * readbuf;
    xbuffer * writebuf;
};

extern xint64 xclientsocketeventon(xclient * o, xuint32 mask, const void * data, xval val);

#define xclientinit(domain, type, protocol) (xclient) {         \
    0,                                                          \
    xclientrem,                                                 \
    xnil,                                                       \
    xnil,                                                       \
    xnil,                                                       \
    xnil,                                                       \
    { xnil, xnil, 0 },                                          \
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
        domain,                                                 \
        type,                                                   \
        protocol                                                \
    },                                                          \
    xnil,                                                       \
    0,                                                          \
    xnil,                                                       \
    xnil }

extern xclient * xclientnew(int domain, int type, int protocol);
extern void * xclientrem(void * p);
extern xint32 xclientconnect(xclient * client, void * addr, xuint64 addrlen);

#define xclientalive(client)                            (client ? xdescriptoralive((xdescriptor *) xaddressof(client->socket)) : xfalse)
#define xclientclose(client)                            (client ? xdescriptorclose((xdescriptor *) xaddressof(client->socket)) : xfail)
#define xclientread(client, buffer, size)               xdescriptorread((xdescriptor *) xaddressof(client->socket), buffer, size)
#define xclientwrite(client, data, len)                 xdescriptorwrite((xdescriptor *) xaddressof(client->socket), data, len)
#define xclientmask_nonblock_on(client)                 (client ? xdescriptormask_nonblock_on((xdescriptor *) xaddressof(client->socket)) : xfail)
#define xclientmask_nonblock_off(client)                (client ? xdescriptormask_nonblock_off((xdescriptor *) xaddressof(client->socket)) : xfail)

#define xclientnonblock_on(client)                      xdescriptornonblock_on((xdescriptor *) (client ? xaddressof(client->socket) : xnil))
#define xclientnonblock_off(client)                     xdescriptornonblock_off((xdescriptor *) (client ? xaddressof(client->socket) : xnil))

#define xclienteventpub(client, mask, data, val)    \
((client && client->socket.on)                      \
    ? client->socket.on(client, mask, data, val)    \
    : xfail)

#define xclientopen(client)                             (client ? xsocketopen((xsocket *) xaddressof(client->socket)) : xfail)
#define xclientshutdown(client, how)                    (client ? xsocketshutdown((xsocket *) xaddressof(client->socket), how) : xfail)

extern xuint32 xclientwait(xclient * client, xuint32 mask, xint64 second, xint64 nanosecond);

typedef xint64 (*xsessioneventon)(xsession *, xuint32, const void *, xval);

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

        int domain;
        int type;
        int protocol;
    } socket;

    xbuffer * readbuf;
    xbuffer * writebuf;
};

extern xint64 xsessionsocketeventon(xsession * o, xuint32 mask, const void * data, xval val);

extern xsession * xsessionnew(void);
extern void * xsessionrem(void * p);

#define xsessionalive(session)                          (session ? xdescriptoralive((xdescriptor *) xaddressof(session->socket)) : xfalse)
#define xsessionclose(session)                          (session ? xdescriptorclose((xdescriptor *) xaddressof(session->socket)) : xfail)
#define xsessionread(session, buffer, size)             xdescriptorread((xdescriptor *) xaddressof(session->socket), buffer, size)
#define xsessionwrite(session, data, len)               xdescriptorwrite((xdescriptor *) xaddressof(session->socket), data, len)
#define xsessionmask_nonblock_on(session)               (session ? xdescriptormask_nonblock_on((xdescriptor *) xaddressof(session->socket)) : xfail)
#define xsessionmask_nonblock_off(session)              (session ? xdescriptormask_nonblock_off((xdescriptor *) xaddressof(session->socket)) : xfail)

#define xsessionnonblock_on(session)                    xdescriptornonblock_on((xdescriptor *) (session ? xaddressof(session->socket) : xnil))
#define xsessionnonblock_off(session)                   xdescriptornonblock_off((xdescriptor *) (session ? xaddressof(session->socket) : xnil))

#define xsessioneventpub(session, mask, data, val)  \
((session && session->socket.on)                    \
    ? session->socket.on(session, mask, data, val)  \
    : xfail)

#define xsessionopen(session)                           (session ? xsocketopen((xsocket *) xaddressof(session->socket)) : xfail)
#define xsessionshutdown(session, how)                  (session ? xsocketshutdown((xsocket *) xaddressof(session->socket), how) : xfail)

#define xsessionwait(session, mask, second, nanosecond) xdescriptorwait((xdescriptor *) xaddressof(session->socket), mask, second, nanosecond)

typedef xint64 (*xservereventon)(xserver *, xuint32, const void *, xval);

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

        int domain;
        int type;
        int protocol;
    } socket;

    void *    addr;
    xuint64   addrlen;
};

#define xserverinit(domain, type, protocol) (xserver) {     \
    0,                                                      \
    xserverrem,                                             \
    xnil,                                                   \
    xnil,                                                   \
    xnil,                                                   \
    xnil,                                                   \
    { xnil, xnil, 0 },                                      \
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
        domain,                                             \
        type,                                               \
        protocol                                            \
    },                                                      \
    xnil,                                                   \
    0 }

extern xint64 xserversocketeventon(xserver * o, xuint32 mask, const void * data, xval val);

extern xserver * xservernew(int domain, int type, int protocol, void * addr, xuint64 addrlen);
extern void * xserverrem(void * p);

#define xserveralive(server)                            (server ? xdescriptoralive((xdescriptor *) xaddressof(server->socket)) : xfalse)
#define xserverclose(server)                            (server ? xdescriptorclose((xdescriptor *) xaddressof(server->socket)) : xfail)

#define xservermask_nonblock_on(server)                 (server ? xdescriptormask_nonblock_on((xdescriptor *) xaddressof(server->socket)) : xfail)
#define xservermask_nonblock_off(server)                (server ? xdescriptormask_nonblock_off((xdescriptor *) xaddressof(server->socket)) : xfail)

#define xservernonblock_on(server)                      xdescriptornonblock_on((xdescriptor *) (server ? xaddressof(server->socket) : xnil))
#define xservernonblock_off(server)                     xdescriptornonblock_off((xdescriptor *) (session ? xaddressof(server->socket) : xnil))

#define xservereventpub(server, mask, data, val)    \
((server && server->socket.on)                      \
    ? server->socket.on(server, mask, data, val)    \
    : xfail)

#define xserveropen(server)                             (server ? xsocketopen((xsocket *) xaddressof(server->socket)) : xfail)
#define xservershutdown(server, how)                    (server ? xsocketshutdown((xsocket *) xaddressof(server->socket), how) : xfail)

#define xserverwait(server, mask, second, nanosecond)   xdescriptorwait((xdescriptor *) xaddressof(server->socket), mask, second, nanosecond)


// /* EVENT ***************************************************/

// #define xobj_type_category_mask     (0x0000F000U)       // MOVE TO STD

// #define xobj_type_category_event    (0x00001000U)       // EVENT OBJECT CATEGORY

// struct xevent;
// struct xeventobj;

// typedef struct xevent xevent;
// typedef struct xeventobj xeventobj;

// typedef xint64 (*xeventobjon)(xeventobj *, xuint32, void *, xval);

// struct xeventobj
// {
//     xuint32     flags;
//     xdestructor destruct;

//     xeventobj * parent;
//     xeventobj * prev;
//     xeventobj * next;

//     xsync *     sync;

//     xeventobjon on;

//     xeventobj * head;
//     xeventobj * tail;
//     xuint64     total;
// };

// // PARAMETER 를 등록할 필요가 있을까?
// struct xevent
// {
//     xuint32     type;
//     xeventobj * target;
// };

// /* DESCRIPTOR **********************************************/

// #define xdescriptor_mask_void               (0x00000000U)
// #define xdescriptor_mask_nonblock           (0x00000001U)

// #define xdescriptor_event_void              (0x00000000U)
// #define xdescriptor_event_in                (0x00000001U)
// #define xdescriptor_event_out               (0x00000002U)
// #define xdescriptor_event_read_hangup       (0x00000004U)
// #define xdescriptor_event_pri               (0x00000008U)
// #define xdescriptor_event_hangup            (0x00000010U)
// #define xdescriptor_event_error             (0x00000020U)
// #define xdescriptor_event_invalid           (0x00000040U)
// #define xdescriptor_event_timeout           (0x00000080U)
// #define xdescriptor_event_exception         (0x00000100U)

// #define xdescriptor_event_open              (0x00000200U)
// #define xdescriptor_event_close_read        (0x00000400U)
// #define xdescriptor_event_close_write       (0x00000800U)
// #define xdescriptor_event_close             (xdescriptor_event_close_read | xdescriptor_event_close_write)

// #define xsocket_event_bind                  (0x00001000U)

// #define xclient_event_connected             (0x00002000U)
// #define xclient_event_connecting            (0x00004000U)

// #define xdescriptor_status_void             xdescriptor_event_void
// #define xdescriptor_status_in               xdescriptor_event_in
// #define xdescriptor_status_out              xdescriptor_event_out
// #define xdescriptor_status_read_hangup      xdescriptor_event_read_hangup
// #define xdescriptor_status_pri              xdescriptor_event_pri
// #define xdescriptor_status_hangup           xdescriptor_event_hangup
// #define xdescriptor_status_error            xdescriptor_event_error
// #define xdescriptor_status_invalid          xdescriptor_event_invalid
// #define xdescriptor_status_timeout          xdescriptor_event_timeout
// #define xdescriptor_status_exception        xdescriptor_event_exception

// #define xdescriptor_status_open             xdescriptor_event_open
// #define xdescriptor_status_close_read       xdescriptor_event_close_read
// #define xdescriptor_status_close_write      xdescriptor_event_close_write
// #define xdescriptor_status_close            xdescriptor_event_close

// #define xsocket_status_bind                 xsocket_event_bind

// #define xclient_status_connected            xclient_event_connected
// #define xclient_status_connecting           xclient_event_connecting

// union xdescriptorhandle;
// struct xdescriptor;
// struct xdescriptorio;

// typedef struct xdescriptor xdescriptor;
// typedef struct xdescriptorio xdescriptorio;
// typedef union xdescriptorhandle xdescriptorhandle;

// typedef xint64 (*xdescriptoreventon)(xdescriptor *, xuint32, void *, xval);

// union xdescriptorhandle
// {
//     int    f;
//     void * v;
// };

// struct xdescriptor
// {
//     xdescriptorhandle  handle;
    
//     xdescriptor *      prev;
//     xdescriptor *      next;
//     xdescriptorio *    io;

//     xsync *            sync;

//     xuint32            status;
//     xuint32            mask;

//     xdescriptoreventon on;

//     void *             parent;
// };

// #define xdescriptorinit() (xdescriptor) {                              \
//     { .f = xinvalid },                                                 \
//     xnil,                                                              \
//     xnil,                                                              \
//     xnil,                                                              \
//     xnil,                                                              \
//     xdescriptor_event_void,                                            \
//     0,                                                                 \
//     xnil,                                                              \
//     xnil }

// #define xdescriptoreventpub(descriptor, mask, parent, additional)      \
//     ((descriptor && descriptor->on) ? descriptor->on(descriptor,       \
//                                                      mask,             \
//                                                      parent,           \
//                                                      additional)       \
//                                     : xfail)

// extern xint32 xdescriptornonblock_on(xdescriptor * o);
// extern xint32 xdescriptornonblock_off(xdescriptor * o);

// extern xint32 xdescriptorclose(xdescriptor * o);
// extern xint32 xdescriptoralive(xdescriptor * o);
// extern xint64 xdescriptorread(xdescriptor * o, void * buffer, xuint64 size);
// extern xint64 xdescriptorwrite(xdescriptor * o, const void * data, xuint64 length);

// extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 second, xuint64 nanosecond);

// extern void xdescriptorset_nonblock_on(xdescriptor * o);
// extern void xdescriptorset_nonblock_off(xdescriptor * o);

// /**
//  * interface
//  */
// struct xdescriptorio
// {
//     xuint32       flags;
//     xdestructor   destruct;

//     xdescriptor * head;
//     xdescriptor * tail;
//     xuint64       total;

//     xsync *       sync;
// };

// #define xdescriptorioinit(type, destructor) (xdescriptorio) {   \
//     type,                                                       \
//     destructor,                                                 \
//     xnil,                                                       \
//     xnil,                                                       \
//     0,                                                          \
//     xnil }

// extern xdescriptorio * xdescriptorionew(xuint32 type, xdestructor destructor, xuint64 memorysize);

// extern void xdescriptorioadd(xdescriptorio * o, xdescriptor * descriptor);
// extern void xdescriptoriodel(xdescriptorio * o, xdescriptor * descriptor);
// extern void xdescriptorioclear(xdescriptorio * o);


// /* NETWORK *************************************************/

// // SERVER 

// #define xobj_type_event_socket          (xobj_type_category_event | 0x0001U)
// #define xobj_type_event_server          (xobj_type_category_event | 0x0002U)
// #define xobj_type_event_client          (xobj_type_category_event | 0x0003U)
// #define xobj_type_event_session         (xobj_type_category_event | 0x0004U)

// struct xsocket;
// struct xserver;
// struct xclient;
// struct xsession;

// typedef struct xsocket xsocket;
// typedef struct xserver xserver;
// typedef struct xclient xclient;
// typedef struct xsession xsession;

// struct xsocket
// {
//     xuint32     flags;
//     xdestructor destruct;

//     xeventobj * parent;
//     xeventobj * prev;
//     xeventobj * next;

//     xsync *     sync;

//     xeventobjon on;

//     xeventobj * head;
//     xeventobj * tail;
//     xuint64     total;

//     xdescriptor descriptor;

//     int         domain;
//     int         type;
//     int         protocol;
// };

// #define xsocketinit(domain, type, protocol, handler) (xsocket) { \
//     xobj_type_event_socket,                                      \
//     xsocketrem,                                                  \
//     xnil,                                                        \
//     xnil,                                                        \
//     xnil,                                                        \
//     xnil,                                                        \
//     handler,                                                     \
//     xnil,                                                        \
//     xnil,                                                        \
//     0,                                                           \
//     xdescriptorinit(),                                           \
//     domain,                                                      \
//     type,                                                        \
//     protocol }

// extern xsocket * xsocketnew(int domain, int type, int protocol, xeventobjon handler);
// extern void * xsocketrem(void * p);
// extern xint32 xsocketshutdown(xsocket * o, xuint32 how);
// extern xint32 xsocketopen(xsocket * o);
// extern xint32 xsocketbind(xsocket * o, void * addr, xuint64 addrlen);

// #define xsocketeventpub()

// #define xsocketnonblock_on(socket)                      (socket ? xdescriptornonblock_on(xaddressof(socket->descriptor)) : xfail)
// #define xsocketnonblock_off(socket)                     (socket ? xdescriptornonblock_off(xaddressof(socket->descriptor)) : xfail)
// #define xsocketclose(socket)                            (socket ? xdescriptorclose(xaddressof(socket->descriptor)) : xfail)
// #define xsocketalive(socket)                            (socket ? xdescriptoralive(xaddressof(socket->descriptor)) : xfalse)
// #define xsocketread(socket, buffer, size)               (socket ? xdescriptorread(xaddressof(socket->descriptor), buffer, size) : xfail)
// #define xsocketwrite(socket, data, length)              (socket ? xdescriptorwrite(xaddressof(socket->descriptor), data, length) : xfail)
// #define xsocketwait(socket, mask, second, nanosecond)   (socket ? xdescriptorwait(xaddressof(socket->descriptor), mask, second, nanosecond) : xfail)
// #define xsocketset_nonblock_on(socket)                  (socket ? xdescriptorset_nonblock_on(xaddressof(socket->descriptor)) : xfail)
// #define xsocketset_nonblock_off(socket)                 (socket ? xdescriptorset_nonblock_off(xaddressof(socket->descriptor)) : xfail)

// struct xclient
// {
//     xuint32     flags;
//     xdestructor destruct;

//     xeventobj * parent;
//     xeventobj * prev;
//     xeventobj * next;

//     xsync *     sync;

//     xeventobjon on;

//     xeventobj * head;
//     xeventobj * tail;
//     xuint64     total;

//     xdescriptor descriptor;

//     int         domain;
//     int         type;
//     int         protocol;

//     void *      addr;
//     xuint64     addrlen;

//     xbuffer *   readbuf;
//     xbuffer *   writebuf;
// };

// #define xclientinit(domain, type, protocol, handler) (xclient) { \
//     xobj_type_event_client,                                      \
//     xclientrem,                                                  \
//     xnil,                                                        \
//     xnil,                                                        \
//     xnil,                                                        \
//     xnil,                                                        \
//     handler,                                                     \
//     xnil,                                                        \
//     xnil,                                                        \
//     0,                                                           \
//     xdescriptorinit(),                                           \
//     domain,                                                      \
//     type,                                                        \
//     protocol,                                                    \
//     xnil,                                                        \
//     0,                                                           \
//     xnil,                                                        \
//     xnil }

// extern xclient * xclientnew(int domain, int type, int protocol, xeventobjon handler);
// extern void * xclientrem(void * p);
// extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen);
// extern xint32 xclientreconnect(xclient * o);
// extern xuint32 xclientwait(xclient * o, xuint32 mask, xuint64 second, xuint64 nanosecond);

// #define xclientshutdown(client, how)                    (client ? xsocketshutdown((xsocket *) client, how) : xsuccess)
// #define xclientopen(client)                             (client ? xsocketopen((xsocket *) client) : xfail)
// #define xclientbind(client, addr, addrlen)              (client ? xsocketbind((xsocket *) client, addr, addrlen) : xfail)

// #define xclienteventpub()

// #define xclientnonblock_on(client)                      (client ? xdescriptornonblock_on(xaddressof(client->descriptor)) : xfail)
// #define xclientnonblock_off(client)                     (client ? xdescriptornonblock_off(xaddressof(client->descriptor)) : xfail)
// #define xclientclose(client)                            (client ? xdescriptorclose(xaddressof(client->descriptor)) : xfail)
// #define xclientalive(client)                            (client ? xdescriptoralive(xaddressof(client->descriptor)) : xfalse)
// #define xclientread(client, buffer, size)               (client ? xdescriptorread(xaddressof(client->descriptor), buffer, size) : xfail)
// #define xclientwrite(client, data, length)              (client ? xdescriptorwrite(xaddressof(client->descriptor), data, length) : xfail)
// // #define xclientwait(client, mask, second, nanosecond)   (client ? xdescriptorwait(xaddressof(client->descriptor), mask, second, nanosecond) : xfail)
// #define xclientset_nonblock_on(client)                  (client ? xdescriptorset_nonblock_on(xaddressof(client->descriptor)) : xfail)
// #define xclientset_nonblock_off(client)                 (client ? xdescriptorset_nonblock_off(xaddressof(client->descriptor)) : xfail)

// struct xsession
// {
//     xuint32     flags;
//     xdestructor destruct;

//     xeventobj * parent;
//     xeventobj * prev;
//     xeventobj * next;

//     xsync *     sync;

//     xeventobjon on;

//     xeventobj * head;
//     xeventobj * tail;
//     xuint64     total;

//     xdescriptor descriptor;

//     int         domain;
//     int         type;
//     int         protocol;

//     xbuffer *   readbuf;
//     xbuffer *   writebuf;
// };

// #define xsessioninit() (xsession) {     \
//     xobj_type_event_session,            \
//     xsessionrem,                        \
//     xnil,                               \
//     xnil,                               \
//     xnil,                               \
//     xnil,                               \
//     xnil,                               \
//     xnil,                               \
//     xnil,                               \
//     0,                                  \
//     xdescriptorinit(),                  \
//     0,                                  \
//     0,                                  \
//     0,                                  \
//     xnil,                               \
//     xnil }

// extern xsession * xsessionnew(void);
// extern void * xsessionrem(void * p);

// #define xsessionshutdown(session, how)                  (session ? xsocketshutdown((xsocket *) session, how) : xsuccess)
// #define xsessionopen(session)                           (session ? xsocketopen((xsocket *) session) : xfail)
// #define xsessionbind(session, addr, addrlen)            (session ? xsocketbind((xsocket *) session, addr, addrlen) : xfail)

// #define xsessioneventpub()

// #define xsessionnonblock_on(session)                    (session ? xdescriptornonblock_on(xaddressof(session->descriptor)) : xfail)
// #define xsessionnonblock_off(session)                   (session ? xdescriptornonblock_off(xaddressof(session->descriptor)) : xfail)
// #define xsessionclose(session)                          (session ? xdescriptorclose(xaddressof(session->descriptor)) : xfail)
// #define xsessionalive(session)                          (session ? xdescriptoralive(xaddressof(session->descriptor)) : xfalse)
// #define xsessionread(session, buffer, size)             (session ? xdescriptorread(xaddressof(session->descriptor), buffer, size) : xfail)
// #define xsessionwrite(session, data, length)            (session ? xdescriptorwrite(xaddressof(session->descriptor), data, length) : xfail)
// #define xsessionwait(session, mask, second, nanosecond) (session ? xdescriptorwait(xaddressof(session->descriptor), mask, second, nanosecond) : xfail)
// #define xsessionset_nonblock_on(session)                (session ? xdescriptorset_nonblock_on(xaddressof(session->descriptor)) : xfail)
// #define xsessionset_nonblock_off(session)               (session ? xdescriptorset_nonblock_off(xaddressof(session->descriptor)) : xfail)

// struct xserver
// {
//     xuint32     flags;
//     xdestructor destruct;

//     xeventobj * parent;
//     xeventobj * prev;
//     xeventobj * next;

//     xsync *     sync;

//     xeventobjon on;

//     xeventobj * head;
//     xeventobj * tail;
//     xuint64     total;

//     xdescriptor descriptor;

//     int         domain;
//     int         type;
//     int         protocol;

//     void *      addr;
//     xuint64     addrlen;
// };

// #define xserverinit(domain, type, protocol, handler) (xserver) {    \
//     xobj_type_event_server,                                         \
//     xserverrem,                                                     \
//     xnil,                                                           \
//     xnil,                                                           \
//     xnil,                                                           \
//     xnil,                                                           \
//     handler,                                                        \
//     xnil,                                                           \
//     xnil,                                                           \
//     0,                                                              \
//     xdescriptorinit(),                                              \
//     domain,                                                         \
//     type,                                                           \
//     protocol,                                                       \
//     xnil,                                                           \
//     0 }

// extern xserver * xservernew(int domain, int type, int protocol, xeventobjon handler);
// extern void * xserverrem(void * p);






// // /** EVENT **********************************************/
// // struct xevent;
// // struct xeventobj;
// // struct xeventengine;

// // typedef struct xevent xevent;
// // typedef struct xeventobj xeventobj;
// // typedef struct xeventengine xeventengine;

// // /**
// //  * @struct  xevent
// //  * @brief   
// //  */
// // struct xevent
// // {
// //     xuint32     type;
// //     xeventobj * target;
// //     void *      param;
// // };

// // struct xeventobj
// // {
// //     xuint32        flags;
// //     xdestructor    destruct;

// //     xeventobj *    prev;
// //     xeventobj *    next;
// //     xeventengine * engine;

// //     xsync *        sync;
// // };

// // /** DESCRIPTOR *****************************************/
// // /** SOCKET *********************************************/
// // struct xdescriptor;
// // struct xdescriptorparent;

// // struct xsocket;

// // typedef struct xdescriptor xdescriptor;
// // typedef struct xdescriptorparent xdescriptorparent;

// // typedef struct xsocket xsocket;

// // #define xobj_type_event                     0x00002000U
// // #define xobj_type_net                       0x00001000U

// // #define xobj_type_socket                    (xobj_type_net | 1)

// // #define xobj_type_client                    (xobj_type_event | 2)

// // #define xdescriptor_event_void              0x00000000U
// // #define xdescriptor_event_open              0x00000001U
// // #define xdescriptor_event_close_read        0x00000002U
// // #define xdescriptor_event_close_write       0x00000004U
// // #define xdescriptor_event_close             (xdescriptor_event_close_read | xdescriptor_event_close_write)
// // #define xdescriptor_event_read              0x00000008U
// // #define xdescriptor_event_write             0x00000010U
// // #define xdescriptor_event_bind              0x00000020U

// // #define xdescriptor_status_void             xdescriptor_event_void
// // #define xdescriptor_status_open             xdescriptor_event_open
// // #define xdescriptor_status_close_read       xdescriptor_event_close_read
// // #define xdescriptor_status_close_write      xdescriptor_event_close_write
// // #define xdescriptor_status_close            xdescriptor_event_close
// // #define xdescriptor_status_read             xdescriptor_event_read
// // #define xdescriptor_status_write            xdescriptor_event_write
// // #define xdescriptor_status_bind             xdescriptor_event_bind

// // struct xdescriptor
// // {
// //     xuint32 flags;
// //     xdestructor destruct;

// //     union
// //     {
// //         int    f;
// //         void * h;
// //     } value;

// //     xdescriptor * prev;
// //     xdescriptor * next;
// //     xdescriptorparent * parent;

// //     xsync ** sync;

// //     void (*on)(xdescriptor *, xuint32);

// //     xuint32 status;
// // };

// // #define xdescriptorinit(type, destructor)     \
// // (xdescriptor) { xobj_type_net | type,         \
// //                 destructor,                   \
// //                 { .f: xinvalid },             \
// //                 xnil,                         \
// //                 xnil,                         \
// //                 xnil,                         \
// //                 xnil,                         \
// //                 xnil,                         \
// //                 0 }


// // #define xdescriptorpub(descriptor, mask) do { \
// //     if(descriptor->on) {                      \
// //         descriptor->on(descriptor, mask);     \
// //     }                                         \
// // } while(0)

// // extern xdescriptor * xdescriptornew(xuint32 type, xdestructor destructor, xuint64 size);
// // extern void * xdescriptorrem(void * p);

// // extern xint32 xdescriptorclose(xdescriptor * o);
// // extern xint32 xdescriptoralive(xdescriptor * o);

// // extern xint64 xdescriptorread(xdescriptor * o, xbyte * buffer, xuint64 size);
// // extern xint64 xdescriptorwrite(xdescriptor * o, const xbyte * data, xuint64 len);

// // // #define xobj_type_descriptor_parent         0x00000001U

// // struct xdescriptorparent
// // {
// //     xuint32       flags;
// //     xdestructor   destruct;

// //     xdescriptor * head;
// //     xdescriptor * tail;
// //     xuint64       total;

// //     xsync *       sync;
// // };

// // /** SOCKET **************************************************************/

// // struct xsocket
// // {
// //     xuint32 flags;
// //     xdestructor destruct;

// //     xeventobj * prev;
// //     xeventobj * next;
// //     xeventengine * parent;

// //     xdescriptor descriptor;
// // };

// // // struct xsocket
// // // {
// // //     xuint32 flags;
// // //     xdestructor destruct;

// // //     union
// // //     {
// // //         int    f;
// // //         void * h;
// // //     } value;

// // //     xdescriptor * prev;
// // //     xdescriptor * next;
// // //     xdescriptorparent * parent;

// // //     xsync * sync;

// // //     void (*on)(xdescriptor *, xuint32);

// // //     xuint32 status;

// // //     int domain;
// // //     int type;
// // //     int protocol;
// // // };

// // // #define xsocketinit(destructor, domain, type, protocol) \
// // // (xdescriptor) { xobj_type_socket,                       \
// // //                 destructor,                             \
// // //                 { .f: xinvalid },                       \
// // //                 xnil,                                   \
// // //                 xnil,                                   \
// // //                 xnil,                                   \
// // //                 xnil,                                   \
// // //                 xnil,                                   \
// // //                 0,                                      \
// // //                 domain,                                 \
// // //                 type,                                   \
// // //                 protocol }

// // // extern xsocket * xsocketnew(int domain, int type, int protocol);
// // // extern void * xsocketrem(void * p);

// // // #define xsocketpub(socket, mask)            xdescriptorpub(socket, mask)
// // // #define xsocketclose(socket)                xdescriptorclose((xdescriptor *) socket)
// // // #define xsocketalive(socket)                xdescriptoralive((xdescriptor *) socket)
// // // #define xsocketread(socket, buffer, size)   xdescriptorread((xdescriptor *) socket, buffer, size)
// // // #define xsocketwrite(socket, data, len)     xdescriptorwrite((xdescriptor *) socket, data, len)
// // // extern xint32 xsocketshutdown(xsocket * o, int how);

// // // extern xint32 xsocketopen(xsocket * o);
// // // extern xint32 xsoketbind(xsocket * o, void * addr, xuint64 addrlen);

// // // struct xclient
// // // {
// // //     xuint32 flags;
// // //     xdestructor destruct;

// // //     xsocket sock;


// // // };

// // // struct xdescriptor;
// // // struct xsocket;
// // // struct xsession;
// // // struct xclient;
// // // struct xserver;
// // // struct xdescriptorlist;
// // // struct xpoll;

// // // typedef struct xdescriptorlist xdescriptorlist;
// // // typedef struct xdescriptor xdescriptor;
// // // typedef struct xsocket xsocket;
// // // typedef struct xclient xclient;
// // // typedef struct xserver xserver;
// // // typedef struct xsession xsession;
// // // typedef struct xpoll xpoll;

// // // struct xdescriptor
// // // {
// // //     union
// // //     {
// // //         int    f;       /**!< file descriptor */
// // //         void * h;       /**!< handle descriptor */
// // //     } value;
// // //     xdescriptor * prev; /**!< ... */
// // //     xdescriptor * next; /**!< ... */
// // //     xdescriptorlist * parent;
// // //     xuint32 interest;
// // //     xuint32 masked;
// // //     xsync * sync;
// // // };

// // // /**
// // //  * 
// // //  */
// // // struct xdescriptorlist
// // // {
// // //     xuint32 flags;
// // //     xdestructor destruct;

// // //     xdescriptor * head;
// // //     xdescriptor * tail;
// // //     xuint64 descriptors;

// // //     xsync * sync;
// // // };

// // // #define xdescriptorinit()               (xdescriptor) { { .f = xinvalid }, xnil, xnil, xnil, xdescriptor_event_void, xdescriptor_event_void, xnil }

// // // #define xdescriptor_event_void          0x00000000U
// // // #define xdescriptor_event_read          0x00000001U
// // // #define xdescriptor_event_write         0x00000002U
// // // #define xdescriptor_event_error         0x00000004U
// // // #define xdescriptor_event_pri           0x00000008U
// // // #define xdescriptor_event_readhup       0x00000010U
// // // #define xdescriptor_event_hup           0x00000020U
// // // #define xdescriptor_event_invalid       0x00000040U
// // // #define xdescriptor_event_readband      0x00000080U
// // // #define xdescriptor_event_writeband     0x00000100U
// // // #define xdescriptor_event_timeout       0x00000200U
// // // #define xdescriptor_event_except        0x00000400U

// // // extern xint32 xdescriptoralive(const xdescriptor * o);

// // // extern xint32 xdescriptor_nonblock_on(xdescriptor * o);
// // // extern xint32 xdescriptor_nonblock_off(xdescriptor * o);

// // // extern xuint32 xdescriptorwait(xdescriptor * o, xuint32 mask, xuint64 nanosecond);

// // // extern xint32 xdescriptorclose(xdescriptor * o);

// // // #define xobj_type_socket                0x00000100U
// // // #define xobj_type_io_facility           0x00000200U

// // // #define xsocket_masks                   0x00FF0000U
// // // #define xsocket_mask_nonblock           0x00010000U

// // // #define xsocket_event_void              xdescriptor_event_void
// // // #define xsocket_event_read              xdescriptor_event_read
// // // #define xsocket_event_write             xdescriptor_event_write
// // // #define xsocket_event_error             xdescriptor_event_error
// // // #define xsocket_event_pri               xdescriptor_event_pri
// // // #define xsocket_event_readhup           xdescriptor_event_readhup
// // // #define xsocket_event_hup               xdescriptor_event_hup
// // // #define xsocket_event_invalid           xdescriptor_event_invalid
// // // #define xsocket_event_readband          xdescriptor_event_readband
// // // #define xsocket_event_writeband         xdescriptor_event_writeband
// // // #define xsocket_event_timeout           xdescriptor_event_timeout
// // // #define xsocket_event_except            xdescriptor_event_except

// // // struct xsocket
// // // {
// // //     xuint32 flags;
// // //     xdestructor destruct;

// // //     xdescriptor descriptor;

// // //     int domain;
// // //     int type;
// // //     int protocoal;

// // //     xuint32 status;
// // // };

// // // // int domain, int type, int protocol

// // // #define xsocketinit(domain, type, protocol)     (xsocket) { xobj_type_socket, xsocketrem, xdescriptorinit(), domain, type, protocol }
// // // #define xsocketalive(socket)                    (socket ? xdescriptoralive(xaddressof(socket->descriptor)) : xfalse)
// // // #define xsocketmask(socket)                     (socket->flags & xsocket_masks)

// // // // #define xsocket_nonblock_on(socket)             (socket ? xdescriptor_nonblock_on(xaddressof(socket->descriptor)) : xfail)

// // // extern xint32 xsocket_nonblock_on(xsocket * o);
// // // extern xint32 xsocket_nonblock_off(xsocket * o);

// // // // extern xint32 xsocket_nonblock_on()
// // // extern xsocket * xsocketnew(int domain, int type, int protocol);

// // // extern xuint32 xsocketwait(xsocket * o, xuint32 mask, xuint64 nanosecond);

// // // extern xsocket * xsocketmaskadd(xsocket * o, xuint32 mask);

// // // extern void * xsocketrem(void * p);
// // // extern xint32 xsocketopen(xsocket * o);
// // // extern xint64 xsocketwrite(xsocket * o, const xbyte * data, xuint64 len);
// // // extern xint64 xsocketread(xsocket * o, void * buffer, xuint64 len);
// // // #define xsocketclose(socket)                    (socket ? xdescriptorclose(xaddressof(socket->descriptor)) : xfail)

// // // #define xobj_type_client            (xobj_type_socket | 0x00000001U)

// // // struct xclient
// // // {
// // //     xuint32 flags;
// // //     xdestructor destruct;

// // //     xdescriptor descriptor;

// // //     int domain;
// // //     int type;
// // //     int protocoal;

// // //     xuint32 status;

// // //     void * addr;
// // //     xuint64 addrlen;
// // // };

// // // #define xclient_event_void          xsocket_event_void
// // // #define xclient_event_read          xsocket_event_read
// // // #define xclient_event_write         xsocket_event_write
// // // #define xclient_event_error         xsocket_event_error
// // // #define xclient_event_pri           xsocket_event_pri
// // // #define xclient_event_readhup       xsocket_event_readhup
// // // #define xclient_event_hup           xsocket_event_hup
// // // #define xclient_event_invalid       xsocket_event_invalid
// // // #define xclient_event_readband      xsocket_event_readband
// // // #define xclient_event_writeband     xsocket_event_writeband
// // // #define xclient_event_except        xsocket_event_except
// // // #define xclient_event_timeout       xsocket_event_timeout

// // // #define xclient_event_connect       0x00000800U

// // // // TODO: UPDATE
// // // #define xclient_status_connecting   0x00000001U
// // // #define xclient_status_connected    0x00000002U

// // // #define xclientinit(domain, type, protocol)                         (xclient) { xobj_type_client, xclientrem, xdescriptorinit(), domain, type, protocol, xnil, 0 }
// // // extern xclient * xclientnew(int domain, int type, int protocol);

// // // #define xclientmaskadd(client, mask)    (xclient *) xsocketmaskadd((xsocket *) client, mask)

// // // extern xuint32 xclientwait(xclient * o, xuint32 mask, xuint64 nanosecond);
// // // extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen);
// // // extern xint32 xclientreconnect(xclient * o);
// // // // extern xint32 xclientclose(xclient * o);
// // // #define xclientclose(o)                 xsocketclose(o)
// // // #define xclient_nonblock_on(o)          xsocket_nonblock_on((xsocket *) o)
// // // #define xclient_nonblock_off(o)         xsocket_nonblock_off((xsocket *) o)
// // // #define xclientsend(o, data, len)       xsocketwrite((xsocket *) o, data, len)
// // // #define xclientrecv(o, buffer, len)     xsocketread((xsocket *) o, buffer, len)
// // // extern void * xclientrem(void * p);

// // // #define xobj_type_session           (xobj_type_socket | 0x00000002U)

// // // #define xsession_event_void         xsocket_event_void
// // // #define xsession_event_read         xsocket_event_read
// // // #define xsession_event_write        xsocket_event_write
// // // #define xsession_event_error        xsocket_event_error
// // // #define xsession_event_pri          xsocket_event_pri
// // // #define xsession_event_readhup      xsocket_event_readhup
// // // #define xsession_event_hup          xsocket_event_hup
// // // #define xsession_event_invalid      xsocket_event_invalid
// // // #define xsession_event_readband     xsocket_event_readband
// // // #define xsession_event_writeband    xsocket_event_writeband
// // // #define xsession_event_except       xsocket_event_except
// // // #define xsession_event_timeout      xsocket_event_timeout

// // // // TODO: UPDATE
// // // #define xsession_status_link        0x00000001U

// // // struct xsession
// // // {
// // //     xuint32 flags;
// // //     xdestructor destruct;

// // //     xdescriptor descriptor;

// // //     int domain;
// // //     int type;
// // //     int protocol;

// // //     xuint32 status;

// // //     void * addr;
// // //     xuint64 addrlen;

// // //     xserver * parent;

// // //     xsession * prev;
// // //     xsession * next;

// // // //    xsync * sync;
// // // };

// // // extern xsession * xsessionnew(void);
// // // extern void * xsessionrem(void * p);

// // // typedef xsession * (*xsessionfactory)(void);
// // // typedef void * (*xsessionrelease)(void *);


// // // #define xobj_type_server            (xobj_type_socket | 0x00000003U)

// // // #define xserver_event_void          xsocket_event_void
// // // #define xserver_event_read          xsocket_event_read
// // // #define xserver_event_write         xsocket_event_write
// // // #define xserver_event_error         xsocket_event_error
// // // #define xserver_event_pri           xsocket_event_pri
// // // #define xserver_event_readhup       xsocket_event_readhup
// // // #define xserver_event_hup           xsocket_event_hup
// // // #define xserver_event_invalid       xsocket_event_invalid
// // // #define xserver_event_readband      xsocket_event_readband
// // // #define xserver_event_writeband     xsocket_event_writeband
// // // #define xserver_event_except        xsocket_event_except
// // // #define xserver_event_timeout       xsocket_event_timeout

// // // #define xserver_event_accept        xserver_event_read

// // // struct xserver
// // // {
// // //     xuint32 flags;
// // //     xdestructor destruct;

// // //     xdescriptor descriptor;

// // //     int domain;
// // //     int type;
// // //     int protocol;

// // //     xuint32 status;

// // //     void * addr;
// // //     xuint64 addrlen;

// // //     xint32 backlog;
// // //     xsessionfactory factory;
// // //     xsessionrelease release;

// // //     xsession * head;
// // //     xsession * tail;

// // //     xuint64 alives;

// // // //    xsync * sync;
// // // };

// // // #define xserverinit(domain, type, protocol)                         (xserver) { xobj_type_server, xserverrem, xdescriptorinit(), domain, type, protocol, xnil, 0, xdefaultmaxconn(), xsessionnew, xsessionrem, xnil, xnil, 0, xnil }
// // // extern xserver * xservernew(int domain, int type, int protocol);

// // // #define xservermaskadd(client, mask)    (xserver *) xsocketmaskadd((xserver *) client, mask)

// // // extern xuint32 xserverwait(xserver * o, xuint32 mask, xuint64 nanosecond);
// // // extern xint32 xserverlisten(xserver * o, void * addr, xuint64 addrlen);
// // // extern xint32 xserverrelisten(xserver * o);

// // // // extern xint32 xclientclose(xclient * o);

// // // #define xserverclose(o)                 xsocketclose(o)
// // // #define xserver_nonblock_on(o)          xsocket_nonblock_on((xsocket *) o)
// // // #define xserver_nonblock_off(o)         xsocket_nonblock_off((xsocket *) o)

// // // extern void * xserverrem(void * p);

// // // extern xsession * xserveraccept(xserver * o);

// // // #define xobj_type_poll                  (xobj_type_io_facility | 0x00000001U)

// // // struct xpoll
// // // {
// // //     xuint32 flags;
// // //     xdestructor destruct;

// // //     xdescriptor * head;
// // //     xdescriptor * tail;
// // //     xuint64 descriptors;

// // //     xsync * sync;
// // // };

// // // #define xpollinit()         (xpoll) { xobj_type_poll, xpollrem, xnil, xnil, 0, xnil }
// // // extern xpoll * xpollnew(void);
// // // extern void * xpollrem(void * p);
// // // // extern void xpolladd(xdescriptor )

#endif // __NOVEMBERIZING_X__NET__H__

