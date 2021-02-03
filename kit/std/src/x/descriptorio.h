#ifndef   __NOVEMBERIZING_X__DESCRIPTORIO__H__
#define   __NOVEMBERIZING_X__DESCRIPTORIO__H__

#include <x/std.h>

struct xdescriptor;
struct xdescriptorio;

typedef struct xdescriptor xdescriptor;
typedef struct xdescriptorio xdescriptorio;

struct xdescriptorio
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
};

extern xdescriptorio * xdescriptorio_new(void);
extern xdescriptorio * xdescriptorio_rem(xdescriptorio * address);
extern void xdescriptorio_call(xdescriptorio * address);

#endif // __NOVEMBERIZING_X__DESCRIPTORIO__H__
