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

#define xsuccess        (0)
#define xfail           (-1)
#define xinvalid        (-1)
#define xtrue           (1)
#define xfalse          (0)
#define xnil            ((void *) 0)

typedef __INT8_TYPE__   xint8;
typedef __INT16_TYPE__  xint16;
typedef __INT32_TYPE__  xint32;
typedef __INT64_TYPE__  xint64;
typedef __UINT8_TYPE__  xuint8;
typedef __UINT16_TYPE__ xuint16;
typedef __UINT32_TYPE__ xuint32;
typedef __UINT64_TYPE__ xuint64;
typedef unsigned char   xbyte;

typedef void * (*destructor)(void *);

/** LOG */

extern int xlogfd(void);

/**
 * @def     xassertion(condition, format, ...)
 * @brief   조건에 따라서 ...
 * 
 * @param   codition | boolean      | ... |
 * @param   format   | const char * | ... |
 * @param   ...      | ...          | ... |
 */
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

/** OBJECT */

#define xobj_mask_allocated     0x80000000U
#define xobj_mask_types         0x0000FFFFU

#define xobjtype(o)             (o->flags & xobj_mask_types)

/** SIGNAL */

extern void xinterrupt(void);

/** THREAD */

struct xsync;

typedef struct xsync xsync;

struct xsync
{
    xuint32 flags;
    destructor free;

    xint32 (*lock)(xsync *);
    xint32 (*unlock)(xsync *);
    xint32 (*wait)(xsync *, xuint64);
    xint32 (*wakeup)(xsync *, xint32);
};

#define xobj_type_sync              0x00000002U

#define xsync_mask_types            0x00FF0000U

#define xsync_type_none             0x00010000U
#define xsync_type_mutex            0x00020000U

#define xsynctype(o)                (o->flags & xsync_mask_types)

#define xsynclock(sync)             (sync ? sync->lock(sync) : xsuccess)
#define xsyncunlock(sync)           (sync ? sync->unlock(sync) : xsuccess)
#define xsyncwait(sync, nanosecond) (sync ? sync->wait(sync, nanosecond) : xsuccess)
#define xsyncwakeup(sync, all)      (sync ? sync->wakeup(sync, all) : xsuccess)

extern xuint64 xthreadid(void);

extern xsync * xsyncnew(xuint32 type);

extern xint32 xsyncon(xsync * p);
extern xint32 xsyncoff(xsync * p);
extern xint32 xcondon(xsync * p);
extern xint32 xcondoff(xsync * p);

#endif // __NOVEMBERIZING_X__STD__H__
