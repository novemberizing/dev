#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_EVENT__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_EVENT__H__

#include <x/descriptor.h>

extern xint64 xdescriptorevent_dispatch(xdescriptor * descriptor, xuint32 event, void * parameter);
extern xint64 xdescriptorevent_process(xdescriptor * descriptor, xuint32 event, void * parameter);
extern xint64 xdescriptorevent_finish(xdescriptor * descriptor, xuint32 event, void * parameter, xint64 result);

#endif // __NOVEMBERIZING_X__DESCRIPTOR_EVENT__H__
