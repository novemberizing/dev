#ifndef   __NOVEMBERZING_X__MAP__H__
#define   __NOVEMBERZING_X__MAP__H__

#include <x/val.h>
#include <x/sync.h>

struct xmapnode
{
    xuint32 color;
    struct xmapnode * parent;
    struct xmapnode * left;
    struct xmapnode * right;
    xval value;
};

typedef struct xmapnode xmapnode;

struct xmap
{
    xsync * sync;
    xuint32 type;
    xuint64 size;
    xmapnode * root;
    xvalcmp comp;
};

typedef struct xmap xmap;

#define xcontainer_type_map     2

#define xmapnode_red            1
#define xmapnode_black          0

extern xmap * xmapnew(xvalcmp comp);
extern xmapnode * xmapget(xmap * o, xval v);
extern int xmapadd(xmap * o, xval v, xvalget f);
extern int xmapdel(xmap * o, xval v, xvalget f);
extern void xmapclr(xmap * o, xvalget f);
extern xmap * xmaprem(xmap * o, xvalget f);


#endif // __NOVEMBERZING_X__MAP__H__
