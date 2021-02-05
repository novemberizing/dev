#ifndef   __NOVEMBERIZING_X__SOCKET__H__
#define   __NOVEMBERIZING_X__SOCKET__H__

#include <x/std.h>

struct xsocket;
struct xclient;
struct xserver;
struct xsession;

typedef struct xsocket xsocket;
typedef struct xclient xclient;
typedef struct xserver xserver;
typedef struct xsession xsession;

typedef xint64 (*xsocket_event_handler)(xsocket *, xuint32, const void *, xint64);
typedef xint64 (*xsocket_process_func)(xsocket *, xuint32);

extern xsocket * xsocket_new(int domain, int type, int protocol, xsocket_event_handler handler, xsocket_process_func processor, xuint64 size);
extern xint32 xsocket_open(xsocket * descriptor);
extern xint32 xsocket_bind(xsocket * descriptor, const void * addr, xuint64 addrlen);
extern xint32 xsocket_listen(xsocket * descriptor, int backlog);
extern xint32 xsocket_connect(xsocket * descriptor, const void * addr, xuint64 addrlen);
extern xint64 xsocket_read(xsocket * descriptor, void * buffer, xuint64 size);
extern xint64 xsocket_write(xsocket * descriptor, const void * data, xuint64 len);
extern xint32 xsocket_close(xsocket * descriptor);
extern xint32 xsocket_shutdown(xsocket * descriptor, xint32 how);
extern xint32 xsocket_nonblock_on(xsocket * descriptor);
extern xint32 xsocket_nonblock_off(xsocket * descriptor);
extern xuint32 xsocket_wait(xsocket * descriptor, xuint32 event, xint64 second, xint64 nanosecond);

// #define xsocket_nonblock_on(descriptor)         xdescriptor_nonblock_on((xdescriptor *) descriptor)
// #define xsocket_nonblock_off(descriptor)        xdescriptor_nonblock_off((xdescriptor *) descriptor)

#endif // __NOVEMBERIZING_X__SOCKET__H__
