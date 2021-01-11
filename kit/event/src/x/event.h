/**
 * @file    x/event.h
 * @brief   이벤트 라이브러리 헤더파일
 * @details
 * 
 * @version 0.0.1
 * @since   2021. 01. 11.
 * 
 */
#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xeventobj;
struct xengine;
struct xgenerator;

typedef struct xevent xevent;
typedef struct xeventobj xeventobj;
typedef struct xengine xengine;
typedef struct xgenerator xgenerator;

struct xevent
{
    xuint32 type;
    xeventobj * target;
};

struct xeventobj
{
};

struct xengine
{
};

extern int xenginerun(xengine * o);

struct xgenerator
{
    xgenerator * next;
};


#endif // __NOVEMBERIZING_X__EVENT__H__
