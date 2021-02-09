/**
 * @file    x/event/processor.h
 * @brief   [internal] event processor
 * 
 * @todo    스레드 풀을 구현하자.
 * 
 */
#ifndef   __NOVEMBERIZING_X__EVENT__PROCESSOR__H__
#define   __NOVEMBERIZING_X__EVENT__PROCESSOR__H__

#include <x/event.h>

typedef void (*xeventprocessor_once)(xeventqueue *);

struct xeventprocessor
{
    
};

#endif // __NOVEMBERIZING_X__EVENT__PROCESSOR__H__
