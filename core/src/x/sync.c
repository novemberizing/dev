#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "std.h"

static xsync * xsync_none_new(void);
static void * xsync_none_rem(void * p);
static xsync * xsync_none_on(xsync * o);
static xsync * xsync_none_off(xsync * o);
static xsync * xsync_none_condon(xsync * o);
static xsync * xsync_none_condoff(xsync * o);

static int xsync_none_lock(xsync * o);
static int xsync_none_unlock(xsync * o);
static int xsync_none_wait(xsync * o, xuint64 nanosecond);
static int xsync_none_wakeup(xsync * o, xuint32 all);

static xsync * xsync_mutex_new(void);
static void * xsync_mutex_rem(void * p);
static xsync * xsync_mutex_on(xsync * o);
static xsync * xsync_mutex_off(xsync * o);
static xsync * xsync_mutex_condon(xsync * o);
static xsync * xsync_mutex_condoff(xsync * o);

static int xsync_mutex_lock(xsync * o);
static int xsync_mutex_unlock(xsync * o);
static int xsync_mutex_wait(xsync * o, xuint64 nanosecond);
static int xsync_mutex_wakeup(xsync * o, xuint32 all);

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

/**
 * @fn      xsync * xsyncon(xsync * o)
 * @brief   동기화 객체를 활성화시킨다.
 * @details
 * 
 * @param   | o | in | xsync * | 동기화 객체 |
 * 
 * @return  | xsync * | 동기화 객체 |
 */
xsync * xsyncon(xsync * o)
{
    xassertion(o == xnil, "invalid parameter (o == xnil");
    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_on(o);
        case xsync_type_mutex: return xsync_mutex_on(o);
    }
    return o;
}

/**
 * @fn      xsync * xsyncoff(xsync * o)
 * @brief   활성화된 동기화 객체를 비활성화 시킨다.
 * @details
 * 
 * @param   | o | in | xsync * | 동기화 객체 |
 * 
 * @return  | xsync * | 동기화 객체 |
 */
xsync * xsyncoff(xsync * o)
{
    xassertion(o == xnil, "invalid parameter (o == xnil");
    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_off(o);
        case xsync_type_mutex: return xsync_mutex_off(o);
    }
    return o;
}

/**
 * @fn      xsync * xsynccondon(xsync * o)
 * @brief   동기화 객체의 컨디션을 활성화 시킨다.
 * @details
 * 
 * @param   | o | in | xsync * | 동기화 객체 |
 * 
 * @return  | xsync * | 동기화 객체 |
 */
xsync * xsynccondon(xsync * o)
{
    xassertion(o == xnil, "invalid parameter (o == xnil");
    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_condon(o);
        case xsync_type_mutex: return xsync_mutex_condon(o);
    }
    return o;
}

/**
 * @fn      xsync * xsynccondoff(xsync * o)
 * @brief   동기화 객체의 컨디션을 비활성화 시킨다.
 * @details
 * 
 * @param   | o | in | xsync * | 동기화 객체 |
 * 
 * @return  | xsync * | 동기화 객체 |
 */
xsync * xsynccondoff(xsync * o)
{
    xassertion(o == xnil, "invalid parameter (o == xnil");
    switch(o->flags & xsync_mask_types)
    {
        case xsync_type_none: return xsync_none_condoff(o);
        case xsync_type_mutex: return xsync_mutex_condoff(o);
    }
    return o;
}



static xsync * xsync_none_new(void)
{
    xsync * o = (xsync *) malloc(sizeof(xsync));

    o->flags = xobj_type_sync | xsync_type_none;
    return o;
}
static void * xsync_none_rem(void * p);
static xsync * xsync_none_on(xsync * o);
static xsync * xsync_none_off(xsync * o);
static xsync * xsync_none_condon(xsync * o);
static xsync * xsync_none_condoff(xsync * o);

static int xsync_none_lock(xsync * o);
static int xsync_none_unlock(xsync * o);
static int xsync_none_wait(xsync * o, xuint64 nanosecond);
static int xsync_none_wakeup(xsync * o, xuint32 all);
