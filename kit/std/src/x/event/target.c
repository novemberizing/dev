#include "target.h"

extern xint32 xeventtargetmask_has(xeventtarget * o, xuint32 mask)
{
    return o->mask & mask;
}

extern xint32 xeventtargetstatus_has(xeventtarget * o, xuint32 status)
{
    return o->status & status;
}