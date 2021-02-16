#ifndef   __NOVEMBERIZING_X__SERVER__H__
#define   __NOVEMBERIZING_X__SERVER__H__

#include <x/std.h>

struct xserver
{
    xdescriptor * descriptor;
    
    xint32 domain;
    xint32 type;
    xint32 protocol;
    void * addr;
    xuint32 addrlen;
    // session
};

typedef struct xserver xserver;

#endif // __NOVEMBERIZING_X__SERVER__H__
