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