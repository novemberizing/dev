#ifndef   __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__
#define   __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__

#include <x/event.h>

struct xeventsubscription
{
    xeventtarget *                        target;
    struct { xeventsubscription * prev;
             xeventsubscription * next;
             xeventengine * engine;     } enginenode;

};

#endif // __NOVEMBERIZING_X__EVENT__SUBSCRIPTION__H__


// #ifndef   __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__
// #define   __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__

// struct xdescriptorsubscription;

// typedef struct xdescriptorsubscription xdescriptorsubscription;

// struct xdescriptorsubscription
// {

// };

// #endif // __NOVEMBERIZING_X__DESCRIPTOR__SUBSCRIPTION__H__
