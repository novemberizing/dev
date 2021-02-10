#ifndef   __NOVEMBERIZING_X__EVENT__OBJECT__H__
#define   __NOVEMBERIZING_X__EVENT__OBJECT__H__

#include <x/event.h>

struct xeventobject
{
    /** INHERITED EVENT MEMBER */
    xeventqueue_node       eventnode;
    xeventhandler          on;
    /** BASE EVENT MEMBER */
    xeventengine_node      enginenode;
    xeventgenerator_node * generatorhead;
    xeventlist             events;
    xsync *                sync;
    xuint32                masks;
    xuint32                status;
};



#endif // __NOVEMBERIZING_X__EVENT__OBJECT__H__
