#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/std.h>

struct xclient;

typedef struct xclient xclient;

struct xclient
{
    xdescriptor * descriptor;
    xint32 domain;
    xint32 type;
    xint32 protocol;

    void * addr;
    xuint32 addrlen;
};

#endif // __NOVEMBERIZING_X__CLIENT__H__
