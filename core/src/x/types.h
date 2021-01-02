// #ifndef   __NOVEMBERIZING_X__TYPES__H__
// #define   __NOVEMBERIZING_X__TYPES__H__

// #define xnil                (void *)(0)
// #define xsuccess            0
// #define xfail               -1
// #define xtrue               1
// #define xfalse              0

// typedef __INT8_TYPE__       xint8;
// typedef __INT16_TYPE__      xint16;
// typedef __INT32_TYPE__      xint32;
// typedef __INT64_TYPE__      xint64;
// typedef __UINT8_TYPE__      xuint8;
// typedef __UINT16_TYPE__     xuint16;
// typedef __UINT32_TYPE__     xuint32;
// typedef __UINT64_TYPE__     xuint64;

// union xval
// {
//     xuint32 u32;
//     xuint64 u64;
//     void *  ptr;
// };

// typedef union xval xval;

// #define xvalgen(v)      (xval) { .u64 = v }
// #define xvalgenptr(v)   (xval) { .ptr = v }

// struct xobj;

// typedef struct xobj xobj;

// typedef void * (*destructor)(void *);
// typedef xobj * (*constructor)(void);

// struct xobj
// {
//     xuint32 flags;
//     destructor rem;
// };

// #define xobj_status_allocated   0x80000000U

// #define xobj_mask_types         0x0000FFFFU

// #define xobj_type_primitive     0x00000001U

// #define xobjtype(o) (o->flags & xobj_mask_types)

// extern xobj * xobjnew(xuint64 size, xuint32 type, destructor rem);
// extern void * xobjrem(void * p);

// // TODO: STRING
// // TODO: BUFFER

// struct xfun;

// typedef struct xfun xfun;

// #define xobj_type_fun           0x00000002U

// #define xfun_status_called      0x40000000U
// #define xfun_status_success     0x20000000U
// #define xfun_status_fail        0x10000000U
// #define xfun_status_cancelled   0x08000000U

// #define xfunisrunning(o)        ((o->flags & xfun_status_called) && (o->flags & (xfun_status_success | xfun_status_fail)) == 0)

// typedef xobj * (*xfunc)(xobj *);
// typedef void (*xcb)(xfun *);

// struct xfun
// {
//     xuint32 flags;
//     destructor rem;

//     xobj * param;
//     xobj * result;
//     xfunc  func;
//     xcb    cb;
// };

// #define xfuninit(func, param, cb)   (xfun) { xobj_type_fun, xfunrem, param, xnil, func, cb }

// extern xfun * xfunnew(xfun * o, xfunc func, xobj * param, xcb cb);
// extern void * xfunrem(void * p);

// extern void xfuncall(xfun * o);
// extern void xfuncancel(xfun * o);

// struct xsync;

// typedef struct xsync xsync;

// struct xsync
// {
//     int (*on)(xsync *);
//     int (*off)(xsync *);
//     int (*lock)(xsync *);
//     int (*unlock)(xsync *);
// };

// #define xsync_type_none     0
// #define xsync_type_mutex    1

// extern xsync * xsyncnew(xuint32 type);
// extern void * xsyncrem(void * p);

// #define xsyncon(o)  o ? o->on(o) : xsuccess
// #define xsyncoff(o)  o ? o->off(o) : xsuccess
// #define xsynclock(o)  o ? o->lock(o) : xsuccess
// #define xsyncunlock(o)  o ? o->unlock(o) : xsuccess

// //

// struct xlistnode;

// typedef struct xlistnode xlistnode;

// struct xlistnode
// {
//     xlistnode * prev;
//     xlistnode * next;
//     xval        value;
// };

// struct xlist
// {
//     xuint32 flags;
//     destructor rem;

//     xlistnode * head;
//     xlistnode * tail;
// };

// 1

// #endif // __NOVEMBERIZING_X__TYPES__H__
