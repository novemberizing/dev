#ifndef   __NOVEMBERIZING_X__TYPES__H__
#define   __NOVEMBERIZING_X__TYPES__H__

#include <stdbool.h>

#define xnil                (void *)(0)
#define xsuccess            0
#define xfail               -1

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

typedef void * (*destructor)(void *);
typedef xobj * (*constructor)(void);

typedef xobj * (*xfunc)(xobj *);

struct xobj
{
    xuint32 flags;
    destructor rem;
};

#define xobj_status_allocated   0x80000000U

#define xobj_type_mask          0x0000FFFFU

#define xobjhas(o, v) (o->flags & v)
#define xobjis(o, v)  ((o->flags & xobj_type_mask) == v)

extern void * xobjrem(void * o);

struct xfun;

typedef struct xfun xfun;

typedef void (*xfuncb)(xfun *);

#define xfun_status_called      0x40000000U
#define xfun_status_success     0x20000000U
#define xfun_status_fail        0x10000000U

#define xobj_type_fun           0x00000001U

#define xfun_is_inprogress(o)   ((o->flags & xfun_status_called) && (o->flags & (xfun_status_success | xfun_status_fail)) == 0)

struct xfun
{
    xuint32    flags;
    destructor rem;

    xobj *     param;
    xobj *     result;
    xfunc      func;
    xfuncb     cb;
};

extern xfun * xfunnew(xfunc func, xobj * param, xfuncb cb, destructor rem);
extern void * xfunrem(void * o);
extern xfun * xfuninit(xfun * o, xfunc func, xobj * param, xfuncb cb, destructor rem);
extern xfun * xfunterm(xfun * o);

#endif // __NOVEMBERIZING_X__TYPES__H__
