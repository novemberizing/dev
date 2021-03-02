#ifndef   __NOVEMBERIZING_X__SOCKET__H__
#define   __NOVEMBERIZING_X__SOCKET__H__

#include <x/io.h>
#include <x/sync.h>
#include <x/exception.h>

#include <x/descriptor/handle.h>

#include <x/socket/event.h>
#include <x/socket/event/type.h>
#include <x/socket/event/subscription.h>

#define xsocketeventtype_in     xdescriptoreventtype_in
#define xsocketeventtype_out    xdescriptoreventtype_out

typedef xint64 (*xsocketprocessor)(xsocket *, xuint32, void *);
typedef xint64 (*xsocketsubscriber)(xsocket *, xuint32, void *, xint64);
typedef xint32 (*xsocketstatuscheck)(xsocket *, xuint32);

struct xsocket
{
    /** INHERITED EVENT TARGET */
    xsocketdestructor          rem;             /**!< destructor */
    xsocketeventsubscription * subscription;    /**!< subscription */
    xsync *                    sync;            /**!< synchronization */
    xuint32                    mask;            /**!< mask */
    xuint32                    status;          /**!< status */
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle          handle;          /**!< descriptor handle */
    xsocketprocessor           process;         /**!< descriptor process function */
    xsocketstatuscheck         check;           /**!< descriptor status checker  */
    xsocketsubscriber          on;              /**!< descriptor event subscriber */
    xsocketevent               event;           /**!< descriptor default event */
    xexception                 exception;       /**!< descriptor exception */
    /** SOCKET MEMBER */
    xint32                     domain;          /**!< domain */
    xint32                     type;            /**!< type */
    xint32                     protocol;        /**!< protocol */
};

#endif // __NOVEMBERIZING_X__SOCKET__H__
