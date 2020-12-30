#include "xtypes.h"

variant vargen(xuint64 v)
{
    variant value = { v };
    return value;
}

int varcmp(variant x, variant y)
{
    return x.u64 - y.u64;
}
