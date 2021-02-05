#ifndef   __NOVEMBERIZING_X__SERVER__H__
#define   __NOVEMBERIZING_X__SERVER__H__

#include <x/socket.h>

typedef xsession * (*xserver_session_factory)(xserver *);
typedef void (*xserver_session_releaser)(xserver *, xsession *);

struct xserver
{
    xsocket * descriptor;
    xsync * sync;

    struct
    {
        xsession * head;
        xsession * tail;
        xuint32    total;
    } sessions;

    xserver_session_factory create;
    xserver_session_releaser release;
};

extern xserver * xserver_new(int domain, int type, int protocol, const void * addr, xuint32 addrlen, xuint64 size);
extern xserver * xserver_rem(xserver * server);

extern xint32 xserver_listen(xserver * server);
extern xint32 xserver_close(xserver * server);
extern xsession * xserver_accept(xserver * server);

#define xserver_nonblock_on(server)     (server ? xsocket_nonblock_on(server->descriptor) : xfail)
#define xserver_nonblock_off(server)    (server ? xsocket_nonblock_off(server->descriptor) : xfail)

#endif // __NOVEMBERIZING_X__SERVER__H__
