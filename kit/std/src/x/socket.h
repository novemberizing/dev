#ifndef   __NOVEMBERIZING_X__SOCKET__H__
#define   __NOVEMBERIZING_X__SOCKET__H__

#include <x/std.h>

struct xsocket;
struct xserver;
struct xsession;

/**
 * 소켓 데이터란 이름 말고 좋은 이름이 없을까?
 */

typedef struct xsocket xsocket;
typedef struct xsession xsession;
typedef struct xserver xserver;

typedef xint32 (*xsocket_opener)(xsocket *);
typedef xint64 (*xsocket_event_processor)(xsocket *, xuint32);
typedef xint64 (*xsocket_event_handler)(xsocket *, xuint32, const void *, xint64);

extern xsocket * xsocket_new(xint32 f,
                             int domain,
                             int type,
                             int protocol,
                             xsocket_event_handler handler,
                             xsocket_event_processor processor,
                             xsocket_opener opener);

extern xsocket * xsocket_rem(xsocket * o);

extern xint32 xsocket_open(xsocket * o);
extern xint32 xsocket_close(xsocket * o);
extern xint64 xsocket_read(xsocket * o, void * buffer, xuint64 size);
extern xint64 xsocket_write(xsocket * o, const void * data, xuint64 len);

#define xsocketeventpub(o, event, data, val)    \
    (o->on ? o->on(o, event, data, val)         \
           : xsuccess)

#endif // __NOVEMBERIZING_X__SOCKET__H__
