#ifndef   __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL__H__
#define   __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL__H__

#include <x/event.h>
#include <x/sync.h>

struct xeventprocessorpool
{
    xeventprocessor * head;
    xeventprocessor * tail;
    xuint64           size;
    xeventengine *    engine;
};

extern xeventprocessorpool * xeventprocessorpool_new(xeventengine * engine, xuint64 n);
extern xeventprocessorpool * xeventprocessorpool_rem(xeventprocessorpool * pool);

extern void xeventprocessorpool_add(xeventprocessorpool * pool, xuint64 n);
extern void xeventprocessorpool_del(xeventprocessorpool * pool, xuint64 n);

extern xint32 xeventprocessorpool_removable(xeventprocessorpool * pool);

#endif // __NOVEMBERIZING_X__EVENT__PROCESSOR_POOL__H__
