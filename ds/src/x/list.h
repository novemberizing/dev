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

#define xcontainer_type_list        1

extern xlist * xlistnew();
extern xlist * xlistrem(xlist * o, xvalget f);

extern void xlistclr(xlist * o, xvalget f);

extern int xlistpush(xlist * o, xval v);
extern int xlistpop(xlist * o, xvalget f);

#endif // __NOVEMBERIZING_X__LIST__H__
