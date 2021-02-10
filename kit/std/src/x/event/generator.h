#ifndef   __NOVEMBERIZING_X__EVENT__GENERATOR__H__
#define   __NOVEMBERIZING_X__EVENT__GENERATOR__H__

#include <x/event.h>

struct xeventgenerator
{
    xeventgenerator_node * head;
    xeventgenerator_node * tail;
    xuint64 size;
};



#endif // __NOVEMBERIZING_X__EVENT__GENERATOR__H__
