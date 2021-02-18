/**
 * @file    x/sync.h
 * @brief   동기화 객체를 정의한 헤더파일입니다.
 * @details 동기화 객체는 인터페이스로 내부 구현은 OS 에 따라서 다양하게 구현해야 합니다.
 * 
 */
#ifndef   __NOVEMBERIZING_X__SYNC__H__
#define   __NOVEMBERIZING_X__SYNC__H__

#include <x/std.h>

struct xsync;

typedef struct xsync xsync;

/**
 * @struct  xsync
 * @brief   동기화 구조체
 * @details
 * 
 */
struct xsync
{
    xint32  (*lock)(xsync *);
    xint32  (*unlock)(xsync *);
    xint32  (*wait)(xsync *, xint64, xint64);
    xint32  (*wakeup)(xsync *, xint32);
    xsync * (*rem)(xsync *);
};

#define xsynclock(o)                        (o ? o->lock(o) : xsuccess)
#define xsyncunlock(o)                      (o ? o->unlock(o) : xsuccess)
#define xsyncwait(o, second, nanosecond)    (o ? o->wait(o, seoncd, nanosecond) : xsuccess)
#define xsyncwakeup(o, all)                 (o ? o->wakeup(o, all) : xsuccess)
#define xsyncrem(o)                         (o ? o->rem(o) : xsuccess)

#endif // __NOVEMBERIZING_X__SYNC__H__
