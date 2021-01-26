/**
 * @file    x/std.c
 * @brief   표준 라이브러리 소스
 * @details
 * 
 * @version 0.0.1
 */

#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#include "std.h"

static xuint32 __random_seed = xinvalid;

/**
 * @fn      extern void xrandomon(void)
 * @brief   랜덤을 ... 
 * 
 */
extern void xrandomon(void)
{
    xcheck(__random_seed != xinvalid, "seed is already initialized");

    if(__random_seed == xinvalid)
    {
        __random_seed = time(xnil);

        srandom(__random_seed);
    }
}

/**
 * @fn      extern xint64 xrandomgen(void)
 * @brief   랜덤 값을 리턴합니다.
 * @details
 * 
 * @return  | xint64 | 랜덤 값 |
 */
extern xint64 xrandomgen(void)
{
    return random();
}

/**
 * @fn      extern void xinterrupt(void)
 * @brief   인터럽트 시그널을 생성합니다.
 * 
 * @todo    시그널 구현으로 옮길 것
 */
extern void xinterrupt(void)
{
    sigqueue(getpid(), SIGINT, (union sigval) { 0 });
}

/**
 * @fn      extern xuint64 xthreadid(void)
 * @brief   스레드 아이디를 리턴합니다.
 * 
 * @return  | xuint64 | 스레드 아이디 |
 * 
 * @todo    스레드 구현으로 옮길 것
 */
extern xuint64 xthreadid(void)
{
    return pthread_self();
}

extern void * xobjrem(void * p)
{
    xobj * o = (xobj *) p;

    if(o)
    {
        if(o->destruct)
        {
            p = o->destruct(p);
        }
    }

    return p;
}

extern xprimitive * xprimitivenew(xval v)
{
    xprimitive * o = (xprimitive *) calloc(sizeof(xprimitive), 1);

    o->flags = xobj_mask_allocated | xobj_type_primitive;
    o->destruct = xprimitiverem;
    o->value = v;

    return o;
}

extern void * xprimitiverem(void * p)
{
    xcheck(p == xnil, "null pointer");
    xassertion(xobjtype(p) != xobj_type_primitive, "invalid object");

    if(p)
    {
        if(xobjallocated(p))
        {
            free(p);
            p = xnil;
        }
    }

    return p;
}

extern void * xfree(void * o)
{
    if(o)
    {
        free(o);
    }
    return xnil;
}

extern void * xdup(const void * data, xuint64 len)
{
    if(data && len)
    {
        void * o = malloc(len);
        xassertion(o == xnil, "fail to malloc (%d)", errno);
        memcpy(o, data, len);
        return o;
    }

    xassertion(data == xnil && len > 0, "invalid parametete");

    return xnil;
}

extern void * xcopy(void * destination, const void * source, xuint64 sourcelen, xint32 reallocate)
{
    if(sourcelen > 0)
    {
        xassertion(source == xnil, "invalid parameter");

        destination = reallocate ? (destination ? realloc(destination, sourcelen) : malloc(sourcelen)) : destination;
        xassertion(destination == xnil, "fail to realloc (%d)", errno);
        memcpy(destination, source, sourcelen);
    }
    else
    {
        if(destination)
        {
            free(destination);
            destination = xnil;
        }
    }
    return destination;

    // destination = reallocate ? realloc(destination, sourcelen) : destination;

    // return destination;
}

extern xuint64 xtimeunisecond(xuint64 second, xuint64 unisecond)
{
    // CHECKING OVERFLOW
    return second * 1000000 + unisecond;
}

extern xuint64 xtimenanosecond(xuint64 second, xuint64 nanosecond)
{
    return second * 1000000000 + nanosecond;
}