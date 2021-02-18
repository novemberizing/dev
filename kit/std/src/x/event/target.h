#ifndef   __NOVEMBERIZING_X__EVENT__TARGET__H__
#define   __NOVEMBERIZING_X__EVENT__TARGET__H__

#include <x/event.h>
#include <x/sync.h>

struct xeventtarget
{
    xeventtargetdestructor rem;
    xeventsubscription *   subscription;
    xsync *                sync;
    xuint32                mask;
    xuint32                status;
};

#endif // __NOVEMBERIZING_X__EVENT__TARGET__H__
