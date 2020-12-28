#ifndef   __NOVEMBERIZING_X__LIST__H__
#define   __NOVEMBERIZING_X__LIST__H__

#include <x/val.h>

struct xlistnode
{
    struct xlistnode * prev;
    struct xlistnode * next;
    xval value;
};

typedef struct xlistnode xlistnode;

struct xlist
{
    xuint32 type;
    xuint64 size;
    struct xlistnode * head;
    struct xlistnode * tail;
};

typedef struct xlist xlist;

extern xlist * xlistnew();
extern xlist * xlistinit(xlist * o);
extern xlist * xlistterm(xlist * o);
extern xlist * xlistrem(xlist * o);

#endif // __NOVEMBERIZING_X__LIST__H__
