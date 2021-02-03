#ifndef   __NOVEMBERIZING_X__SESSION__H__
#define   __NOVEMBERIZING_X__SESSION__H__

#include <x/socket.h>

struct xsession;

typedef struct xsession xsession;

struct xsession
{
    xsocket * descriptor;
};

#endif // __NOVEMBERIZING_X__SESSION__H__
