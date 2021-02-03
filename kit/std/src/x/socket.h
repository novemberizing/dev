#ifndef   __NOVEMBERIZING_X__SOCKET__H__
#define   __NOVEMBERIZING_X__SOCKET__H__

#include <x/std.h>

struct xsocket;

typedef struct xsocket xsocket;

typedef xint32 (*xsocket_opener)(xsocket *);
typedef xint64 (*xsocket_event_processor)(xsocket *, xuint32);
typedef xint64 (*xsocket_event_handler)(xsocket *, xuint32, const void *, xint64);

extern xsocket * xsocket_new(xint32 f, int domain, int type, int protocol, xsocket_event_handler handler, xsocket_event_processor processor, xsocket_opener opener);
extern xsocket * xsocket_rem(xsocket * o);

extern xint32 xsocket_open(xsocket * o);
extern xint32 xsocket_close(xsocket * o);
extern xint64 xsocket_read(xsocket * o, void * buffer, xuint64 size);
extern xint64 xsocket_write(xsocket * o, const void * data, xuint64 len);

#endif // __NOVEMBERIZING_X__SOCKET__H__
