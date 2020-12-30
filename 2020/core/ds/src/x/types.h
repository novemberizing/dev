#ifndef   __NOVEMBERIZING_X__TYPES__H__
#define   __NOVEMBERIZING_X__TYPES__H__

#define xnil                (void *)(0)
#define xsuccess            0
#define xfail               -1
#define xallocated          0x80000000U

#define xisallocated(v)     (v & xallocated)

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;

struct xval
{
    xuint32 u32;
    xuint64 u64;
    void *  ptr;
};

typedef struct xval xval;

typedef void (*xvalget)(xval);

#define xvalgen(v)      ((xval){ .u64 = v })
#define xvalgenptr(v)   ((xval){ .ptr = v })

/**
 * 
 * | 0 bit            | 1 - 7 bit   |
 * | ---------------- | ----------- |
 * | allocated status | object type |
 */
struct xobj
{
    xuint32 type;
    struct xobj * (*rem)(struct xobj *);
};

typedef struct xobj xobj;

extern xobj * xobjrem(xobj * o);

#define xfunc_status_call       0x00000001U
#define xfunc_status_success    0x00000002U
#define xfunc_status_fail       0x00000004U

struct xfunc
{
    xuint32 status;
    xobj *  param;
    xobj *  result;
    xobj *  (*call)(xobj *);
    void    (*back)(struct xfunc *, xobj *);
};

typedef struct xfunc xfunc;

#define xfuncisprogress(o)  ((o->status & (xfunc_status_success | xfunc_status_fail)) == 0 && o->status & xfunc_status_call)

extern xfunc * xfuncnew(xobj * param, xobj * (*call)(xobj *), void (*back)(xfunc *, xobj *));
extern xfunc * xfuncrem(xfunc * o);
extern xfunc * xfuncinit(xfunc * o, xobj * param, xobj * (*call)(xobj *), void (*back)(xfunc *, xobj *));
extern xfunc * xfuncterm(xfunc * o);
extern xobj * xfunccall(xfunc * o);

extern int __check_x_types(int total);

#endif // __NOVEMBERIZING_X__TYPES__H__
