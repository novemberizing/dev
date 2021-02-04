#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/socket.h>

struct xclient
{
    xsocket * descriptor;
    xsync * sync;
};

extern xclient * xclient_new(int domain, int type, int protocol, const void * addr, xuint32 addrlen, xuint64 size);

extern xint32 xclient_connect(xclient * client);
extern xint64 xclient_read(xclient * client, void * buffer, xuint64 size);
extern xint64 xclient_write(xclient * client, const void * data, xuint64 len);
extern xint32 xclient_close(xclient * client);
extern xint32 xclient_shutdown(xclient * client, xint32 how);

#endif // __NOVEMBERIZING_X__CLIENT__H__
