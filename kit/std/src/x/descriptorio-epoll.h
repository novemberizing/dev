#ifndef   __NOVEMBERIZING_X__DESCRIPTORIO__EPOLL__H__
#define   __NOVEMBERIZING_X__DESCRIPTORIO__EPOLL__H__

#include <sys/epoll.h>

#include "std.h"

struct xdescriptor;
struct xdescriptorio;
struct xdescriptorio_epoll;

typedef struct xdescriptor xdescriptor;
typedef struct xdescriptorio xdescriptorio;
typedef struct xdescriptorio_epoll xdescriptorio_epoll;

struct xdescriptorio_epoll
{
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;
    } children;
    struct
    {
        xdescriptor * head;
        xdescriptor * tail;
        xuint32       total;
    } queue;

    int fd;

    struct epoll_event * events;
    int nfds;
    int timeout;
};

extern xdescriptorio * xdescriptorio_epoll_new(void);
extern xdescriptorio * xdescriptorio_epoll_rem(xdescriptorio * address);
extern void xdescriptorio_epoll_call(xdescriptorio * address);

#endif // __NOVEMBERIZING_X__DESCRIPTORIO__EPOLL__H__
