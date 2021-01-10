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

typedef void (*xvalget)(xval);
typedef int (*xvalcmp)(xval, xval);

extern xval xvalgen(xuint64 v);
extern xval xvalgenptr(void * p);



#endif // __NOVEMBERIZING_X__VAL__H__
