#ifndef   __NOVEMBERIZING_X__LIST__H__
#define   __NOVEMBERIZING_X__LIST__H__

#include <x/types.h>

struct xlistnode
{
    struct xlistnode * prev;
    struct xlistnode * next;
    xval               value;
};

typedef struct xlistnode xlistnode;

struct xlist
{
    xuint32 type;
    xuint64 size;
    xvalget xvalrem;
};

typedef struct xlist xlist;

extern xlist * xlistnew(void);
extern xlist * xlistinit(xlist * o);
extern xlist * xlistterm(xlist * o);
extern xlist * xlistrem(xlist * o);

extern void xlistclr(xlist * o, xvalget func);

#endif // __NOVEMBERIZING_X__LIST__H__
