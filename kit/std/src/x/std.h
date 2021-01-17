/**
 * @file    x/std.h
 * @brief   표준 라이브러리 헤더
 * @details
 * 
 * @version 0.0.1
 * 
 */

#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

/** COMMON */

union xval;
struct xobj;
struct xprimitive;

#define xsuccess            (0)
#define xfail               (-1)
#define xinvalid            (-1)
#define xtrue               (1)
#define xfalse              (0)
#define xnil                ((void *) 0)

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;
typedef unsigned char       xbyte;
typedef union xval          xval;
typedef struct xobj         xobj;
typedef struct xprimitive   xprimitive;

union xval
{
    xint32  i32;
    xuint32 u32;
    xuint64 u64;
    void *  ptr;
};

typedef void *              (*xdestructor)(void *);
typedef void                (*xvalcb)(xval);

#define xvalgen(v)          (xval) { .u64 = v }
#define xvalgenptr(v)       (xval) { .ptr = v }

#define xobj_mask_void      0x00000000U
#define xobj_mask_allocated 0x80000000U
#define xobj_mask_types     0x0000FFFFU

#define xobjtype(o)         (((xobj *) o)->flags & xobj_mask_types)
#define xobjallocated(o)    (((xobj *) o)->flags & xobj_mask_allocated)

struct xobj
{
    xuint32     flags;
    xdestructor destruct;
};

#define xobj_type_primitive 0x00000001U

struct xprimitive
{
    xuint32     flags;
    xdestructor destruct;
    xval        value;
};

extern xprimitive * xprimitivenew(xval v);
extern void * xprimitiverem(void * p);

#define xprimitiveinit(v)   ((xprimitive) { xobj_type_primitive, xprimitiverem, v })

/** SYSTEM */

extern void xrandomon(void);
extern xint64 xrandomgen(void);

extern void xinterrupt(void);       // signal
extern xuint64 xthreadid(void);     // thread

// /** LOG */

extern xint32 xlogfd(void);

#define xassertion(condition, format, ...) do {     \
    if(condition) {                                 \
        dprintf(xlogfd(), "[assertion] %s:%d "      \
                          "%s:%lu => "              \
                          format "\n",              \
                          __FILE__, __LINE__,       \
                          __func__, xthreadid(),    \
                          ##__VA_ARGS__);           \
        xinterrupt();                               \
    }                                               \
} while(0)

#define xcheck(condition, format, ...) do {         \
    if(condition) {                                 \
        dprintf(xlogfd(), "[check] %s:%d "          \
                          "%s:%lu => "              \
                          format "\n",              \
                          __FILE__, __LINE__,       \
                          __func__, xthreadid(),    \
                          ##__VA_ARGS__);           \
    }                                               \
} while(0)

/** THREAD */

#define xobj_type_sync              0x00000002U

#define xsync_mask_types            0x00FF0000U

#define xsync_type_none             0x00010000U
#define xsync_type_mutex            0x00020000U

#define xsynctype(o)                (((xsync *) o)->flags & xsync_mask_types)

struct xsync;

typedef struct xsync xsync;

struct xsync
{
    xuint32 flags;
    xdestructor destruct;

    xint32 (*lock)(xsync *);
    xint32 (*unlock)(xsync *);
    xint32 (*wait)(xsync *, xuint64);
    xint32 (*wakeup)(xsync *, xint32);
};

extern xsync * xsyncnew(xuint32 type);
extern void * xsyncrem(void * p);

extern xsync * xsynccondon(xsync * o);
extern xsync * xsynccondoff(xsync * o);

#define xsynclock(sync)                 (sync ? sync->lock(sync) : xsuccess)
#define xsyncunlock(sync)               (sync ? sync->unlock(sync) : xsuccess)
#define xsyncwait(sync, nanosecond)     (sync ? sync->wait(sync, nanosecond) : xsuccess)
#define xsyncwakeup(sync, all)          (sync ? sync->wakeup(sync, all) : xsuccess)

// /** THREAD */

// #define xsynctype(o)                (o->flags & xsync_mask_types)

// #define xsynclock(sync)             (sync ? sync->lock(sync) : xsuccess)
// #define xsyncunlock(sync)           (sync ? sync->unlock(sync) : xsuccess)
// #define xsyncwait(sync, nanosecond) (sync ? sync->wait(sync, nanosecond) : xsuccess)
// #define xsyncwakeup(sync, all)      (sync ? sync->wakeup(sync, all) : xsuccess)

// extern xuint64 xthreadid(void);

// extern xsync * xsyncnew(xuint32 type);
// extern void * xsyncrem(void * p);

// extern xsync * xsyncon(xsync * p);
// extern xsync * xsyncoff(xsync * p);
// extern xsync * xcondon(xsync * p);
// extern xsync * xcondoff(xsync * p);

// #define xobj_type_thread            0x00000003U

// #define xthread_mask_status         0x00FF0000U

// #define xthread_status_cancel       0x00800000U

// struct xthread;

// typedef struct xthread xthread;

// typedef void * (*xthreadfunc)(xthread *);

// struct xthread
// {
//     xuint32 flags;
//     xdestructor destruct;

//     xval * param;

//     xthreadfunc func;
// };

// extern xthread * xthreadnew(xthreadfunc func, xval * param);
// extern void * xthreadrem(void * p);

// extern xthread * xthreadon(xthread * p);
// extern xthread * xthreadoff(xthread * p, xvalcb cb);

#endif // __NOVEMBERIZING_X__STD__H__
