#ifndef   __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL__H__
#define   __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL__H__

#include <x/event.h>
#include <x/sync.h>

struct xeventprocessorpool
{
    xeventprocessor * head;
    xeventprocessor * tail;
    xuint64           size;
    xsync *           sync;
    xeventengine *    engine;
};

extern xeventprocessorpool * xeventprocessorpool_new(xuint64 n);
extern xeventprocessorpool * xeventprocessorpool_rem(xeventprocessorpool * o);

extern void xeventprocessorpoll_add(xeventprocessorpool * o, xuint64 n);
extern void xeventprocessorpoll_del(xuint64 n);

#endif // __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL__H__
