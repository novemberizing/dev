#ifndef   __NOVEMBERIZING_X__OBJECT__H__
#define   __NOVEMBERIZING_X__OBJECT__H__

#include <x/val.h>

struct xobj
{
    xuint32 type;
    void (*construct)(void);
    void (*destruct)(struct xobj *);
};

typedef struct xobj xobj;

extern xobj * xobjrem(xobj * o);

#endif // __NOVEMBERIZING_X__OBJECT__H__
