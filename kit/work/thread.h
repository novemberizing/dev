#ifndef   __NOVEMBERIZING_X__THREAD__H__
#define   __NOVEMBERIZING_X__THREAD__H__

#include <x/std.h>

/**
 * 동기화 객체는 항상 동적할당에 의해서 생성됩니다.
 * 그 이유는 다양한 운영체제를 커버하기 위해서 입니다.
 * 윈도우의 경우 자체 동기화 객체를 생성해야 하며,
 * 나머지 POSIX 계열의 경우 PTHREAD 의 객체를 사용합니다.
 * 
 */

struct xsync;

typedef struct xsync xsync;

struct xsync
{
    xuint32 flags;
    xdestructor free;

    xint32 (*lock)(xsync *);
    xint32 (*unlock)(xsync *);
    xint32 (*wait)(xsync *, xuint64);
    xint32 (*wakeup)(xsync *, xint32);
};

#define xsynclock(sync)             (sync ? sync->lock(sync) : xsuccess)
#define xsyncunlock(sync)           (sync ? sync->unlock(sync) : xsuccess)
#define xsyncwait(sync, nanosecond) (sync ? sync->wait(sync, nanosecond) : xsuccess)
#define xsyncwakeup(sync, all)      (sync ? sync->wakeup(sync, all) : xsuccess)

extern xsync * xsyncnew(xuint32 type);
extern void * xsyncfree(void * p);

extern xint32 xsyncon(xsync * o);
extern xint32 xsyncoff(xsync * o);
extern xint32 xsynccondon(xsync * o);
extern xint32 xsynccondoff(xsync * o);

#endif // __NOVEMBERIZING_X__THREAD__H__
