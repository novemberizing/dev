#ifndef   __NOVEMBERIZING_X__EVENT__OBJECT__H__
#define   __NOVEMBERIZING_X__EVENT__OBJECT__H__

#include <x/event.h>



extern xeventgenerator_node * xeventobject_register_generator_node(xeventobject * object, xeventgenerator_node * node);
extern xeventgenerator_node * xeventobject_unregister_generator_node(xeventgenerator_node * node);

#endif // __NOVEMBERIZING_X__EVENT__OBJECT__H__
