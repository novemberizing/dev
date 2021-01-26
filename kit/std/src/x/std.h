/**
 * @file    x/std.h
 * @brief   표준 라이브러리 헤더
 * @details 어플리케이션을 구현하기 위한 최소한의 라이브러리만 구현하는 소스입니다.
 *          
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

extern void * xdup(const void * data, xuint64 len);
extern void * xfree(void * o);
extern void * xcopy(void * destination, const void * source, xuint64 sourcelen, xint32 reallocate);

extern xuint64 xtimeunisecond(xuint64 second, xuint64 unisecond);
extern xuint64 xtimenanosecond(xuint64 second, xuint64 nanosecond);

union xval
{
    xint32  i32;
    xuint32 u32;
    xuint64 u64;
    void *  ptr;
};

#define xaddressof(o)       (&o)

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

extern void * xobjrem(void * p);

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

#define xobj_type_thread                0x00000003U

#define xthread_mask_cancel             0x00800000U

struct xthread;

typedef struct xthread xthread;

typedef xobj * (*xthreadfunc)(xthread *);

struct xthread
{
    xuint32 flags;
    xdestructor destruct;

    xobj * param;
    xthreadfunc func;
    xobj * result;
};

extern xthread * xthreadnew(xthreadfunc func, xobj * param);
extern void * xthreadrem(void * p);
extern xthread * xthreadon(xthread * o);
extern xthread * xthreadoff(xthread * o, xobj * (*cb)(xobj *));

/** THREAD LOCAL */

#define xobj_type_threadlocal       0x00000004U

struct xthreadlocal;

typedef struct xthreadlocal xthreadlocal;

struct xthreadlocal
{
    xuint32 flags;
    xdestructor xdestruct;
};

extern xthreadlocal * xthreadlocalnew(void (*destructor)(void *));
extern void * xthreadlocalrem(void * p);
extern void * xthreadlocalget(xthreadlocal * o);
extern void xthreadlocalset(xthreadlocal * o, void * data);

/** BUFFER */

/**
 * 버퍼는 업그레이드를 고민하자.
 * 일단 간단하게 짜자.
 * 모든 것을 커스터마이징 하는 것은 좋지 않다.
 */

#define xobj_type_buffer            0x00000005U

struct xbuffer;

typedef struct xbuffer xbuffer;

struct xbuffer
{
    xuint32 flags;
    xdestructor destruct;

    xbyte * data;

    xuint64 capacity;
    xuint64 size;
    xuint64 position;
};

/**
 * TODO: 버퍼가 존재하지 않으면 0 이 아닌 MAX_UINT64 를 출력하자. 역시 0 이다.
 * 
 * XINVALID 가 정상적으로 동작할까?
 */

#define xbufferfront(buffer)        ((buffer && buffer->data) ? buffer->data + buffer->position : xnil)
#define xbufferback(buffer)         ((buffer && buffer->data) ? buffer->data + buffer->size : xnil)
#define xbuffersize(buffer)         (buffer ? buffer->size : 0)
#define xbuffercapacity(buffer)     (buffer ? buffer->capacity : 0)
#define xbufferposition(buffer)     (buffer ? buffer->position : 0)

#define xbufferinit(capacity)       (xbuffer) { xobj_type_buffer, xbufferrem, malloc(capacity), capacity, 0, 0 }

extern xbuffer * xbuffernew(xuint64 capacity);
extern void * xbufferrem(void  * p);

/**
 * 딱히 마음에 드는 함수 이름이 없어서
 * RECAPACITY 같은 경우 나중에 구현한다.
 */

/** DATA STRUCTURE */

// #define xobj_type_buffer            0x00000005U
#define xobj_type_list              0x00000006U

struct xlist;
struct xlistnode;

typedef struct xlist xlist;
typedef struct xlistnode xlistnode;

struct xlistnode
{
    xlistnode * prev;
    xlistnode * next;
    xval        value;
};

struct xlist
{
    xuint64     flags;
    xdestructor destruct;

    xlistnode * head;
    xlistnode * tail;
    xuint64     size;
    xsync *     sync;
};

#define xlistinit()         (xlist) { xobj_type_list, xlistrem, xnil, xnil, 0 }
#define xlistfront(list)    (list ? list->head : xnil)

#define xlistsize(list)     (list ? list->size : 0)

#define xlistnodenext(node) (node ? node->next : xnil)

extern xlist * xlistnew(void);
extern void * xlistrem(void * p);

extern void xlistclear(xlist * o, xvalcb cb);
extern void xlistpush(xlist * o, xval v);
extern void xlistpop(xlist * o, xvalcb cb);




#endif // __NOVEMBERIZING_X__STD__H__
