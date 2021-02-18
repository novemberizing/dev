#include "std.h"

extern void * xobjectnew(const void * data, xuint64 size)
{
    xassertion(data == xnil || size == 0, "");

    void * o = malloc(size);

    return memcpy(o, data, size);
}