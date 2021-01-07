#ifndef   __NOVEMBERIZING_X__STD__H__
#define   __NOVEMBERIZING_X__STD__H__

/**
 * 프로그램에서 공통적으로 사용되어지는 매크로의 정의
 */
#define xnil        (void *)(0)
#define xinvalid    -1
#define xsuccess    0
#define xfail       -1
#define xtrue       1
#define xfalse      0

/**
 * 일반적으로 사용되는 함수 정의
 */

extern void xabort(void);

extern unsigned long xthreadself(void);

/**
 * 로그 관련된 함수와 매크로의 정의
 */

extern int xlogfd(void);

/**
 * @def     xassertion(condition, format, ...)
 * @brief   소프트웨어의 비정상적인 동작을 감지하기 위한 매크로 함수입니다.
 * @details 비정상 상태이면 프로그램을 종료합니다.
 * 
 * @param   | condition | in | -            | 비정상 상태 조건 |
 * @param   | format    | in | const char * | 비정상 상태의 로그의 포맷 |
 * @param   | ...       | in | -            | 비정상 상태의 로그 포맷의 파라미터 |
 */
#define xassertion(condition, format, ...) do {                                       \
    if(condition) {                                                                   \
        dprintf(xlogfd(), "[assertion] %s:%d %s:%lu => " format "\n", __FILE__,       \
                                                                      __LINE__,       \
                                                                      __func__,       \
                                                                      xthreadself(),  \
                                                                      ##__VA_ARGS__); \
        xabort();                                                                     \
    }                                                                                 \
} while(0)

/**
 * @def     #define xcheck(condition, ret, format, ...)
 * @brief   로직의 상태는 정상이지만 디버깅 메시지를 출력하는 매크로 함수입니다.
 * @details 조건에 따라서 특별한 값을 리턴합니다.
 *          만약에 void 를 리턴해야 하는 경우 xcheckvoid 매크로를 호출해야 합니다.
 * 
 * @param   | condition | in | -            | 상태 조건 |
 * @param   | ret       | in | -            | 조건이 참일 경우 리턴하는 값 |
 * @param   | format    | in | const char * | 조건의 참일 경우 출력하는 문자열 포맷 |
 * @param   | ...       | in | -            | 포맷 문자열의 파라미터 |
 */
#define xcheck(condition, ret, format, ...) do {                                      \
    if(condition) {                                                                   \
        dprintf(xlogfd(), "[check] %s:%d %s:%lu => " format "\n", __FILE__,           \
                                                                  __LINE__,           \
                                                                  __func__,           \
                                                                  xthreadself(),      \
                                                                  ##__VA_ARGS__);     \
        return ret;                                                                   \
    }                                                                                 \
} while(0)

/**
 * @def     #define xcheckvoid(condition, ret, format, ...)
 * @brief   로직의 상태는 정상이지만 디버깅 메시지를 출력하는 매크로 함수입니다. (리턴 타입이 void 일 경우)
 * @details 조건이 참일 경우 메시지를 출력하고 함수를 종료합니다.
 *          함수 종료 시에 리턴 값이 필요할 경우 xcheck 매크로를 호출해야 합니다.
 * 
 * @param   | condition | in | -            | 상태 조건 |
 * @param   | format    | in | const char * | 조건의 참일 경우 출력하는 문자열 포맷 |
 * @param   | ...       | in | -            | 포맷 문자열의 파라미터 |
 */
#define xcheckvoid(condition, format, ...) do {                                       \
    if(condition) {                                                                   \
        dprintf(xlogfd(), "[check] %s:%d %s:%lu => " format "\n", __FILE__,           \
                                                                  __LINE__,           \
                                                                  __func__,           \
                                                                  xthreadself(),      \
                                                                  ##__VA_ARGS__);     \
        return;                                                                   \
    }                                                                                 \
} while(0)

/**
 * 기본 프리미티브 타입의 정의
 */

typedef __INT8_TYPE__       xint8;
typedef __INT16_TYPE__      xint16;
typedef __INT32_TYPE__      xint32;
typedef __INT64_TYPE__      xint64;
typedef __UINT8_TYPE__      xuint8;
typedef __UINT16_TYPE__     xuint16;
typedef __UINT32_TYPE__     xuint32;
typedef __UINT64_TYPE__     xuint64;

/**
 * VALIDIC TYPE
 */

union xval;

typedef union xval xval;

union xval
{
    xuint32 u32;
    xuint64 u64;
    void *  ptr;
};

typedef void (*xvalcb)(xval);

#define xvalget(o)      o.u64
#define xvalgetptr(o)   o.ptr

#define xvalgen(v)      (xval) { .u64 = v }
#define xvalgenptr(v)   (xval) { .ptr = v }

/**
 * OBJECT
 * 
 */

#define xobj_mask_allocated     0x80000000U
#define xobj_mask_types         0x0000FFFFU

#define xobjtype(o) (o->flags & xobj_mask_types)

struct xobj;

typedef struct xobj xobj;

typedef void * (*xdestructor)(void *);

struct xobj
{
    xuint32     flags;
    xdestructor destruct;
};

extern xobj * xobjnew(xuint64 size, xuint32 type, xdestructor destruct);
extern void * xobjrem(void * p);

/**
 * PRIMITIVE
 * 
 */

#define xobj_type_primitive     0x00000001U

struct xprimitive;

typedef struct xprimitive xprimitive;

struct xprimitive
{
    xuint32     flags;
    xdestructor destruct;

    xval        value;
};

#define xprimitiveinit(v)   (xprimitive) { xobj_type_primitive, xprimitiverem, v }

extern xprimitive * xprimitivenew(xval v);
extern void * xprimitiverem(void * p);

/**
 * FUNCTION
 * 
 * 함수는 여러번 호출될 수 있나?
 * 
 */

#define xobj_type_function     0x00000002U

struct xfunction;

typedef struct xfunction xfunction;

typedef void (*xfunc)(xfunction *);
typedef void (*xcallback)(xfunction *);

struct xfunction
{
    xuint32     flags;
    xdestructor destruct;

    xobj * param;
    xobj * result;
    xfunc func;
    xcallback cb;
};

#define xfunction_mask_called       0x40000000U
#define xfunction_mask_success      0x20000000U
#define xfunction_mask_fail         0x10000000U
#define xfunction_mask_cancelled    0x08000000U

#define xfunction_is_cancel(o)      (o->flags & (xfunction_mask_cancelled) != xfalse)
#define xfunction_is_running(o)     ((o->flags & xfunction_mask_called) && (o->flags & (xfunction_mask_success | xfunction_mask_fail)) == xfalse)
#define xfunction_is_done(o)        (o->flags & (xfunction_mask_success | xfunction_mask_fail))

#define xfunctioninit(func, param, cb)  (xfunction) { xobj_type_function, xfunctionrem, param, xnil, func, cb}

extern xfunction * xfunctionnew(xfunc func, xobj * param, xcallback cb);
extern void * xfunctionrem(void *);

extern void xfunctioncall(xfunction * o);
extern void xfunctioncancel(xfunction * o);

/**
 * THREAD
 * 
 */

#define xobj_type_thread     0x00000002U

struct xthread;

typedef struct xthread xthread;

struct xthread
{
    xuint32     flags;
    xdestructor destruct;

    xobj * param;
    xobj * result;
    xfunc func;
    xcallback cb;
};

#define xthread_mask_called         0x40000000U
#define xthread_mask_success        0x20000000U
#define xthread_mask_fail           0x10000000U
#define xthread_mask_cancelled      0x08000000U

#define xthread_is_cancel(o)        (o->flags & (xthread_mask_cancelled) != xfalse)
#define xthread_is_running(o)       ((o->flags & xthread_mask_called) && (o->flags & (xthread_mask_success | xthread_mask_fail)) == xfalse)
#define xthread_is_done(o)          (o->flags & (xthread_mask_success | xthread_mask_fail))

extern xthread * xthreadnew(xfunc func, xobj * param, xcallback cb);
extern void * xthreadrem(void *);

extern xthread * xthreadon(xthread *);
extern xthread * xthreadoff(xthread *);

/**
 * SYNC
 */

#define xobj_type_sync      0x00000003U

struct xsync;

typedef struct xsync xsync;

struct xsync
{
    xuint32     flags;
    xdestructor destruct;

    int (*lock)(xsync *);
    int (*unlock)(xsync *);
    int (*wait)(xsync *, xuint64);
    int (*wakeup)(xsync *, xint32);
};

#define xsync_mask_types    0x00FF0000U

#define xsync_type_none     0x00010000U
#define xsync_type_mutex    0x00020000U

#define xsynctype(o)        (o->flags & xsync_mask_types)

#define xsynclock(o)        (o ? o->lock(o) : xsuccess)
#define xsyncunlock(o)      (o ? o->unlock(o) : xsuccess)
#define xsyncwait(o, v)     (o ? o->wait(o, v) : xsuccess)
#define xsyncwakeup(o, v)   (o ? o->wakeup(o, v) : xsuccess)

extern xsync * xsyncon(xsync * o);
extern xsync * xsyncoff(xsync * o);
extern xsync * xsynccondon(xsync * o);
extern xsync * xsynccondoff(xsync * o);

extern xsync * xsyncnew(xuint32 type);
extern void * xsyncrem(void * p);

/**
 * STANDARD TEMPLATE LIBRARY
 */

#define xobj_type_list      0x00000004U

struct xlistnode;

typedef struct xlistnode xlistnode;

struct xlistnode
{
    xlistnode * prev;
    xlistnode * next;
    xval        value;
};

struct xlist;

typedef struct xlist xlist;

struct xlist
{
    xuint32 flags;
    xdestructor destruct;

    xuint64 size;

    xlistnode * head;
    xlistnode * tail;
};

#define xlistinit()     (xlist) { xobj_type_list, xlistrem, 0, xnil, xnil }

#define xlistsize(o)    (o->size)
#define xlistempty(o)   (o->size == 0)

extern xlist * xlistnew(void);
extern void * xlistrem(void * p);
extern void xlistadd(xval v);
extern void xlistpush(xval v);
extern void xlistpop(xvalcb f);
extern void xlistdel(xvalcb f);

#endif // __NOVEMBERIZING_X__STD__H__
