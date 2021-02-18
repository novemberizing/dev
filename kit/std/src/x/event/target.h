/**
 * @file    x/event/target.h
 * @brief   이벤트 타겟 객체를 정의한 헤더 파일입니다.
 * @details
 * 
 */
#ifndef   __NOVEMBERIZING_X__EVENT__TARGET__H__
#define   __NOVEMBERIZING_X__EVENT__TARGET__H__

#include <x/sync.h>
#include <x/event/subscription.h>

struct xeventtarget;

typedef struct xeventtarget xeventtarget;

extern xint32 xeventtargetmask_has(xeventtarget * o, xuint32 mask);
extern xint32 xeventtargetstatus_has(xeventtarget * o, xuint32 status);

/**
 * @struct  xeventtarget
 * @brief   [internal] 이벤트 타겟 객체
 */
struct xeventtarget
{
    xeventsubscription * subscription;
    xsync *              sync;
    xuint32              mask;
    xuint32              status;
};

#define xeventtargetmask_add(o, mask)   (o->mask |= mask)
#define xeventtargetmask_del(o, mask)   (o->mask &= (~mask))

#define xeventtargetstatus_add(o, status)   (o->status |= status)
#define xeventtargetstatus_del(o, status)   (o->status &= (~status))

#endif // __NOVEMBERIZING_X__EVENT__TARGET__H__
