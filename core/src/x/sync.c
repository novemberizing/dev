#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "std.h"

static xsync * xsync_none_new(void);
static void * xsync_none_rem(void * p);

static xsync * xsync_mutex_new(void);
static void * xsync_mutex_rem(void * p);

/**
 * @fn      xsync * xsyncnew(xuint32 type)
 * @brief   동기화 객체를 생성합니다.
 * @details
 * 
 * @param   | type | in | xuint32 | 동기화 객체의 타입 |
 * 
 * @return  | xsync * | 생성된 동기화 객체 |
 */
xsync * xsyncnew(xuint32 type)
{
    switch(type)
    {
        case xsync_type_none:   return xsync_none_new();
        case xsync_type_mutex:  return xsync_none_mutex();
    }
    xassertion(xtrue, "unsupported type");
}

/**
 * @fn      void * xsyncrem(void * p)
 * @brief   동기화 객체를 메모리 상에서 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 동기화 객체의 메모리 주소값 |
 * 
 * @return  | void * | 해제한 메모리의 주소 값 |
 */
void * xsyncrem(void * p)
{
    xsync * o = (xsync *) p;
    xcheck(o == xnil, xnil, "invalid parameter (p == xnil)");
    xassertion(xobjtype(o) != xobj_type_sync, "object is not sync");

    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_rem(p);
        case xsync_type_mutex: return xsync_mutex_rem(p);
    }
    xassertion(xtrue, "unsupported type");
}

extern xsync * xsyncon(xsync * o);
extern xsync * xsyncoff(xsync * o);
extern xsync * xsynccondon(xsync * o);
extern xsync * xsynccondoff(xsync * o);



// static int xsync_none_on(xsync * o);
// static int xsync_none_off(xsync * o);
// static int xsync_none_lock(xsync * o);
// static int xsync_none_unlock(xsync * o);
// static int xsync_none_condon(xsync * o);
// static int xsync_none_condoff(xsync * o);
// static int xsync_none_wait(xsync * o, xuint64 nanosecond);
// static int xsync_none_wakeup(xsync * o, xint32 all);
// static void * xsync_none_rem(void * p);
// static xsync * xsync_none_new(void);

/**
 * xsync * o = xsyncon(xsyncnew());
 */

/**
 *
xsync * xsyncnew(xuint32 type)
{
    switch(type)
    {
        case xsync_type_none:  return xsync_none_new();
        case xsync_type_mutex: return xsync_mutex_new();
    }
    xassertion(xtrue, "unknown type");
}

void * xsyncrem(void * p)
{
}
