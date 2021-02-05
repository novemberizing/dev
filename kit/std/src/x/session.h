#ifndef   __NOVEMBERIZING_X__SESSION__H__
#define   __NOVEMBERIZING_X__SESSION__H__

#include <x/socket.h>

struct xsession
{
    xsocket *  descriptor;
    xsync *    sync;

    xsession * prev;
    xsession * next;
    xserver *  parent;
};

extern xsession * xsession_new(int domain, int type, int protocol, xuint64 size);

extern xint64 xsession_read(xsession * session, void * buffer, xuint64 size);
extern xint64 xsession_write(xsession * session, const void * data, xuint64 len);
extern xint32 xsession_close(xsession * session);
extern xint32 xsession_shutdown(xsession * session, xint32 how);

extern xsession * xserver_default_session_factory(xserver * server);
extern void xserver_default_session_releaser(xserver * server, xsession * session);

#define xsession_nonblock_on(session)   (session ? xsocket_nonblock_on(session->descriptor) : xfail)
#define xsession_nonblock_off(session)  (session ? xsocket_nonblock_off(session->descriptor) : xfail)

#endif // __NOVEMBERIZING_X__SESSION__H__
