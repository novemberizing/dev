#ifndef   __NOVEMBERIZING_X__VAL__H__
#define   __NOVEMBERIZING_X__VAL__H__

#include <x/type.h>

union xval
{
    xuint32 u32;
    xuint64 u64;
    void *  ptr;
};

typedef union xval  xval;

#endif // __NOVEMBERIZING_X__VAL__H__
