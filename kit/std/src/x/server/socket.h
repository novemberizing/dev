#ifndef   __NOVEMBERIZING_X__SERVER__SOCKET__H__
#define   __NOVEMBERIZING_X__SERVER__SOCKET__H__

#include <x/io.h>
#include <x/server.h>
#include <x/sync.h>
#include <x/exception.h>

#include <x/descriptor/handle.h>

#include <x/socket/stream.h>

#include <x/server/socket/event.h>
#include <x/server/socket/event/subscription.h>

typedef xserversocket * (*xserversocketdestructor)(xserversocket *);
typedef xint64 (*xserversocketprocessor)(xserversocket *, xuint32, void *);
typedef xint64 (*xserversocketsubscriber)(xserversocket *, xuint32, void *, xint64);
typedef xint32 (*xserversocketcheck)(xserversocket *, xuint32);

struct xserversocket
{
    /** INHERITED EVENT TARGET */
    xserversocketdestructor          rem;           /**!< destructor */
    xserversocketeventsubscription * subscription;  /**!< subscription */
    xsync *                          sync;          /**!< synchronization */
    xuint32                          mask;          /**!< mask */
    xuint32                          status;        /**!< status */
    /** INHERITED DESCRIPTOR */
    xdescriptorhandle                handle;        /**!< descriptor handle */
    xserversocketprocessor           process;       /**!< descriptor process function */
    xserversocketcheck               check;         /**!< descriptor status checker  */
    xserversocketsubscriber          on;            /**!< descriptor event subscriber */
    xserversocketevent               event;         /**!< descriptor default event */
    xexception                       exception;     /**!< descriptor exception */
    /** INHERITED SOCKET */
    xint32                           domain;        /**!< domain */
    xint32                           type;          /**!< type */
    xint32                           protocol;      /**!< protocol */
    /** SERVER SOCKET MEMBER */
    void *                           addr;          /**!< address */
    xuint32                          addrlen;       /**!< address length */
    xserver *                        server;        /**!< parent server reference */
};

extern xserversocket * xserversocket_new(xserver * server, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen);
extern xserversocket * xserversocket_rem(xserversocket * descriptor);

extern xint32 xserversocketcheck_rem(xserversocket * descriptor);
// 
// extern xclientsocket * xclientsocket_new(xclient * client, xint32 domain, xint32 type, xint32 protocol, const void * addr, xuint32 addrlen);
// extern xclientsocket * xclientsocket_rem(xclientsocket * o);

#endif // __NOVEMBERIZING_X__SERVER__SOCKET__H__
