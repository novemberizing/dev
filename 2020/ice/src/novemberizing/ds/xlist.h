#ifndef   __NOVEMBERIZING_DS_XLIST__H__
#define   __NOVEMBERIZING_DS_XLIST__H__

#include <novemberizing/ds/xtypes.h>

struct xlistnode
{
    struct xlistnode * prev;
    struct xlistnode * next;
    variant            value;
};

typedef struct xlistnode xlistnode;

struct xlist
{
    xuint32     type;
    xuint64     size;
    xlistnode * head;
    xlistnode * tail;
};

typedef struct xlist xlist;

#define xcontainer_type_list        1

extern xlist * xlistnew(void);
extern xlist * xlistclr(xlist * o, void (*func)(variant));
extern xlist * xlistrem(xlist * o, void (*func)(variant));

extern xlist * xlistpush(xlist * o, variant v);
extern int xlistpop(xlist * o, void (*func)(variant));

#endif // __NOVEMBERIZING_DS_XLIST__H__
