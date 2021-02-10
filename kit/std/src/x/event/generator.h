#ifndef   __NOVEMBERIZING_X__EVENT__GENERATOR__H__
#define   __NOVEMBERIZING_X__EVENT__GENERATOR__H__

#include <x/event.h>

struct xeventgenerator
{
};



extern xint32 xeventgenerator_register_object(xeventgenerator * generator, xeventobject * object);
extern xint32 xeventgenerator_unregister_object(xeventgenerator * generator, xeventobject * object);

#endif // __NOVEMBERIZING_X__EVENT__GENERATOR__H__
