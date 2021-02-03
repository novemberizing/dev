#include "descriptorio.h"
#include "descriptorio-epoll.h"

extern xdescriptorio * xdescriptorio_epoll_new(void)
{
    return xdescriptorio_epoll_new();
}

extern xdescriptorio * xdescriptorio_epoll_rem(xdescriptorio * address)
{
    return xdescriptorio_epoll_rem(address);
}

extern void xdescriptorio_call(xdescriptorio * address)
{
    xdescriptorio_epoll_call(address);
}