#ifndef   __NOVEMBERIZING_X__SERVER__H__
#define   __NOVEMBERIZING_X__SERVER__H__

#include <x/socket.h>

struct xserver;

typedef struct xserver xserver;

struct xserver
{
    xsocket * descriptor;
};

#endif // __NOVEMBERIZING_X__SERVER__H__
