#ifndef   __NOVEMBERIZING_X__TYPES__H__
#define   __NOVEMBERIZING_X__TYPES__H__

#include <stdbool.h>

#define xnil                (void *)(0)
#define xsuccess            0
#define xfail               -1
#define xallocated          0x80000000U

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;

union xval
{
    xuint32 u32;
    xuint64 u64;
    void *  ptr;
};

typedef union xval xval;

struct xobj;

typedef struct xobj xobj;
typedef xobj * (*destructor)(xobj *);
typedef xobj * (*constructor)(void);

struct xobj
{
    xuint32 flags;
    destructor rem;
};

#define xobjhas(o, v) (o->flags & v)

extern xobj * xobjrem(xobj * o);


#endif // __NOVEMBERIZING_X__TYPES__H__
