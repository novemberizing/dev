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

union xval
{
    xuint32 u32;
    xuint64 u64;
    void *  ptr;
};

typedef union xval xval;

#define xvalget(o)      o.u64
#define xvalgetptr(o)   o.ptr

#define xvalgen(v)      (xval) { .u64 = v }
#define xvalgenptr(p)   (xval) { .ptr = p }

struct xobj;

typedef struct xobj xobj;

typedef void * (*destructor)(void *);

#define xobj_mask_allocated     0x80000000U

#define xobj_mask_types         0x0000FFFFU

#define xobj_type_primitive     0x00000001U

#define xobjtype(o) (o->flags & xobj_mask_types)

struct xobj
{
    xuint32    flags;
    destructor destruct;
};

/**
 * PRIMITIVE 타입 객체 정의
 */

#define xobj_type_val       0x00000002U

extern xobj * xobjnew(xuint64 size, xuint32 type, destructor destruct);
extern void * xobjrem(void * p);

struct xobjval
{
    xuint32    flags;
    destructor destruct;
    xval       value;
};

typedef struct xobjval xobjval;

#define xobjvalinit(v)  (xobjval) { xobj_type_val, xnil, v }

extern xobjval * xobjvalnew(xval v);

/**
 * 함수 객체의 정의
 */

#define xobj_type_fun       0x00000003U

struct xfun;

typedef struct xfun xfun;

#define xfun_mask_called    0x40000000U
#define xfun_mask_success   0x20000000U
#define xfun_mask_fail      0x10000000U
#define xfun_mask_cancelled 0x08000000U

#define xfunisrunning(o)    ((o->flags & xfun_mask_called) && (o->flags & (xfun_mask_success | xfun_mask_fail)) == 0)

typedef xobj * (*xfunc)(xobj *);
typedef void (*xcb)(xfun *);

struct xfun
{
    xuint32 flags;
    destructor destruct;

    xobj * param;
    xobj * result;
    xfunc func;
    xcb cb;
};

#define xfuninit(func, param, cb)   (xfun) { xobj_type_fun, xfunrem, param, xnil, func, cb }

extern xfun * xfunnew(xfunc func, xobj * param, xcb cb);
extern void * xfunrem(void * p);

extern void xfuncall(xfun * o);
extern void xfuncancel(xfun * o);

/**
 * 동기화
 */

#define xobj_type_sync      0x00000004U

#define xsync_type_mask     0x00FF0000U

#define xsync_type_none     0x00010000U
#define xsync_type_mutex    0x00020000U

#define xsynctype(o)        (o->flags & xsync_type_mask)

struct xsync;

typedef struct xsync xsync;

struct xsync
{
    xuint32 flags;
    destructor destruct;

    int (*on)(xsync *);
    int (*off)(xsync *);
    int (*lock)(xsync *);
    int (*unlock)(xsync *);
    int (*wait)(xsync *, xuint64);
    int (*wakeup)(xsync *, int);
    int (*condon)(xsync *);
    int (*condoff)(xsync *);
};

#define xsyncon(o)                  (o ? o->on(o) : xsuccess)
#define xsyncoff(o)                 (o ? o->off(o) : xsuccess)
#define xsynclock(o)                (o ? o->lock(o) : xsuccess)
#define xsyncunlock(o)              (o ? o->unlock(o) : xsuccess)
#define xsyncwait(o, nanosecond)    (o ? o->wait(o, nanosecond) : xsuccess)
#define xsyncwakeup(o, all)         (o ? o->wakeup(o, wakeup) : xsuccess)
#define xsynccondon(o)              (o ? o->condon(o) : xsuccess)
#define xsynccondoff(o)             (o ? o->condoff(o) : xsuccess)

extern xsync * xsyncnew(xuint32 type);
extern void * xsyncrem(void * o);

/**
 * 스레드 
 */

#define xobj_type_thread        0x00000005U

struct xthread;

typedef struct xthread xthread;

typedef xobj * (*xthreadfun)(xobj *);

struct xthread
{
    xuint32 flags;
    destructor destruct;

    xobj * param;
    xobj * result;
    xthreadfun func;
};

extern xthread * xthreadnew(xthreadfun func, xobj * param);

#endif // __NOVEMBERIZING_X__STD__H__
