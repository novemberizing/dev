/**
 * @file    x/event/engine.h
 * @brief   [external]
 * 
 */
#ifndef   __NOVEMBERIZING_X__EVENT__ENGINE__H__
#define   __NOVEMBERIZING_X__EVENT__ENGINE__H__

#include <x/event.h>

struct xeventengine
{
    xeventobject * head;
    xeventobject * tail;
    xuint64 size;
    xsync * sync;

    xeventgenerator * timegen;
    xeventgenerator * descriptorgen;
    xeventgenerator * signalgen;
};

extern xeventengine * xeventengine_new(void);
extern xeventengine * xeventengine_rem(xeventengine * engine);
extern xint32 xeventengine_run(xeventengine * engine);

extern void xeventengine_register_object(xeventengine * engine, xeventobject * object);
extern void xeventengine_unregister_object(xeventengine * engine, xeventobject * object);

extern void xeventengine_dispatch_event(xeventengine * engine, xevent * event);
extern void xeventengine_remove_event(xeventengine * engine, xevent * event);

#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
