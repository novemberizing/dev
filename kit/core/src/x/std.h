/**
 * @file    x/std.h
 * @brief   standard library include file.
 * @details - log
 *          - data structure
 *          - thread & synchronization
 * 
 */
#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

#define xinvalid        -1
#define xtrue           1
#define xfalse          0
#define xsuccess        0
#define xfail           -1
#define xnil            (void *)(0)

typedef __INT8_TYPE__   xint8;
typedef __INT16_TYPE__  xint16;
typedef __INT32_TYPE__  xint32;
typedef __INT64_TYPE__  xint64;
typedef __UINT8_TYPE__  xuint8;
typedef __UINT16_TYPE__ xuint16;
typedef __UINT32_TYPE__ xuint32;
typedef __UINT64_TYPE__ xuint64;

union xval;
struct xobj;

typedef struct xobj xobj;
typedef union xval xval;

typedef void * (*xdestructor)(void *);
typedef void * (*xfunction)(void *);
typedef void (*xcallback)(int, void *);

#define     xobj_mask_allocated     0x80000000U
#define     xobj_mask_types         0x0000FFFFU

union xval
{
    xuint32 u32;
    xuint64 u64;
    void *  ptr;
};

struct xobj
{
    xuint32 flags;
    xdestructor destruct;
};

extern xobj * xobjnew(xuint64 size, xuint32 type, xdestructor destruct);
extern void * xobjrem(void * p);

/** LOG ************************************************/

extern int xlogfd(void);
extern void xexit(int status);
extern unsigned long xthreadid(void);

#define xassertion(condition, err, format, ...)  do {   \
    if(condition) {                                     \
        dprintf(xlogfd(), "[assertion] "                \
                          "%s:%d %s:%lu => "            \
                          format "\n",                  \
                          __FILE__, __LINE__,           \
                          __func__, xthreadid(),        \
                          ##__VA_ARGS__);               \
        xexit(err);                                     \
    }                                                   \
} while(0)

/** THREAD *********************************************/
#define xobj_type_sync              0x00000001U

struct xsync;

typedef struct xsync xsync;

#define xsync_mask_types            0x00FF0000U

#define xsync_type_none             0x00010000U
#define xsync_type_mutex            0x00020000U

#define xsynctype(o)                (o->flags & xsync_mask_types)

#define xsynclock(o)                (o ? o->lock(o) : xsuccess)
#define xsyncunlock(o)              (o ? o->unlock(o) : xsuccess)
#define xsyncwait(o, nanosecond)    (o ? o->wait(o, nanosecond) : xsuccess)
#define xsyncwakeup(o, all)         (o ? o->wakeup(o, all) : xsuccess)

struct xsync
{
    xuint32 flags;
    xdestructor destruct;

    int (*lock)(xsync *);
    int (*unlock)(xsync *);
    int (*wait)(xsync *, xuint64);
    int (*wakeup)(xsync *, xuint32);
};

extern xsync * xsyncnew(xuint32 type);
extern void * xsyncrem(void * p);

extern xsync * xsyncon(xsync * o);
extern xsync * xsyncoff(xsync * o);
extern xsync * xsynccondon(xsync * o);
extern xsync * xsynccondoff(xsync * o);

#define xobj_type_thread        0x00000002U

struct xthread;

typedef struct xthread xthread;

struct xthread
{
    xuint64 flags;
    xdestructor destruct;

    xfunction func;
    xval * param;
    xval * result;
    xcallback callback;
};

#endif // __NOVEMBERIZING_X__STD__H__
