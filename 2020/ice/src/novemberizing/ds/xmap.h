#ifndef   __NOVEMBERIZING_DS_XMAP__H__
#define   __NOVEMBERIZING_DS_XMAP__H__

#include <novemberizing/ds/xtypes.h>

enum xmapcolor
{
    xmapnode_red = 0,
    xmapnode_black = 1
};

typedef enum xmapcolor xmapcolor;

struct xmapnode
{
    xmapcolor         color;
    struct xmapnode * parent;
    struct xmapnode * left;
    struct xmapnode * right;
    variant           value;
};

typedef struct xmapnode xmapnode;

struct xmap
{
    xuint32    type;
    xuint64    size;
    xmapnode * root;

    int (*comp)(variant, variant);
};

typedef struct xmap xmap;

#define xcontainer_type_map     2

extern xmap * xmapnew(void);
extern xmap * xmapclr(xmap * o, void (*func)(variant));
extern xmap * xmaprem(xmap * o, void (*func)(variant));
extern xmap * xmapfor(xmap * o, void (*func)(variant));

extern xmap * xmapadd(xmap * o, variant v, void (*func)(variant));
extern xmapnode * xmapget(xmap * o, variant v);
extern xmap * xmapdel(xmap * o, variant v, void (*func)(variant));

#endif // __NOVEMBERIZING_DS_XMAP__H__