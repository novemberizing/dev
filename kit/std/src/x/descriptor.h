#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include <x/io.h>
#include <x/sync.h>
#include <x/exception.h>

#include <x/descriptor/handle.h>
#include <x/descriptor/event.h>
#include <x/descriptor/event/subscription.h>



typedef xint64 (*xdescriptorprocessor)(xdescriptor *, xuint32, void *);
typedef xint64 (*xdescriptorsubscriber)(xdescriptor *, xuint32, void *, xint64);
typedef xint32 (*xdescriptorstatuscheck)(xdescriptor *, xuint32);

struct xdescriptor
{
    /** INHERITED EVENT TARGET */
    xdescriptordestructor                   rem;            /**!< destructor */
    xdescriptoreventsubscription *          subscription;   /**!< subscription */
    xsync *                                 sync;           /**!< synchronization */
    xuint32                                 mask;           /**!< mask */
    xuint32                                 status;         /**!< status */
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle                       handle;         /**!< descriptor handle */
    xdescriptorprocessor                    process;        /**!< descriptor process function */
    xdescriptorstatuscheck                  check;          /**!< descriptor status checker  */
    xdescriptorsubscriber                   on;             /**!< descriptor event subscriber */
    xdescriptorevent                        event;          /**!< descriptor default event */
    xexception                              exception;      /**!< descriptor exception */
};

extern xint64 xdescriptorclose(xdescriptor * descriptor);
extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size);
extern xint64 xdescriptorwrite(xdescriptor * descriptor, void * data, xuint64 len);

extern xint32 xdescriptorcheck_rem(xdescriptor * descriptor);
extern xint32 xdescriptorcheck_close(xdescriptor * descriptor);
extern xint32 xdescriptorcheck_open(xdescriptor * descriptor);

extern xint32 xdescriptorset_nonblock(xdescriptor * descriptor, xint32 on);

extern xint64 xdescriptorevent_dispatch_on(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_open(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_in(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_out(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_close(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_rem(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_exception(xdescriptor * descriptor, void * code, xint64 number);

extern xint64 xdescriptorevent_processor_on(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_open(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_in(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_out(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_close(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_register(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_unregister(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_rem(xdescriptor * descriptor);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
