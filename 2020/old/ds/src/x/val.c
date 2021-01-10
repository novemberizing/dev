#include "val.h"

xval xvalgen(xuint64 v)
{
    xval o = { .u64 = v };

    return o;
}

xval xvalgenptr(void * p)
{
    xval o = { .ptr = p };
    return o;
}
