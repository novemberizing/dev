#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/socket.h>

struct xclient
{
    xsocket * descriptor;
    xsync *   sync;
};

extern xclient * xclient_new(int domain, int type, int protocol, const void * addr, xuint32 addrlen, xuint64 size);
extern xclient * xclient_rem(xclient * client);

extern xint32 xclient_connect(xclient * client);
extern xint64 xclient_read(xclient * client, void * buffer, xuint64 size);
extern xint64 xclient_write(xclient * client, const void * data, xuint64 len);
extern xint32 xclient_close(xclient * client);
extern xint32 xclient_shutdown(xclient * client, xint32 how);
extern xuint32 xclient_wait(xclient * client, xuint32 event, xint64 second, xint64 nanosecond);
extern void xclient_mask_add(xclient * client, xuint32 mask);
extern void xclient_mask_del(xclient * client, xuint32 mask);
extern xuint32 xclient_status(xclient * client);

#define xclient_nonblock_on(client)     (client ? xsocket_nonblock_on(client->descriptor) : xfail)
#define xclient_nonblock_off(client)    (client ? xsocket_nonblock_off(client->descriptor) : xfail)

#endif // __NOVEMBERIZING_X__CLIENT__H__
