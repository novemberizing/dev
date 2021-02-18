#ifndef   __NOVEMBERIZING_X__EVENT__PROCESSOR__H__
#define   __NOVEMBERIZING_X__EVENT__PROCESSOR__H__

#include <x/event.h>

struct xeventprocessor
{
    xeventprocessor * prev;
    xeventprocessor * next;
    xeventprocessorpool * pool;
};

extern xeventprocessor * xeventprocessor_new(xeventprocessorpool * pool);

#endif // __NOVEMBERIZING_X__EVENT__PROCESSOR__H__
