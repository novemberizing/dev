/**
 * @file    x/descriptor/handle.h
 * @brief   디스크립터 핸들 객체입니다.
 * 
 * 
 * 
 * @todo    `void *` 대신에 좋은 단어가 없을까?
 */
#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__HANDLE__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__HANDLE__H__

#include <x/std.h>

struct xdescriptorhandle;

typedef struct xdescriptorhandle xdescriptorhandle;

struct xdescriptorhandle
{
    xint32 f;
    void * v;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR__HANDLE__H__
