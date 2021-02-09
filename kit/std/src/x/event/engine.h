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

};

extern xeventengine * xeventengine_new(void);
extern xeventengine * xeventengine_rem(xeventengine * engine);
extern xint32 xeventengine_run(xeventengine * engine);

extern void xeventengine_register_object(xeventengine * engine);
extern void xeventengine_unregister_object(xeventengine * engine);

#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
