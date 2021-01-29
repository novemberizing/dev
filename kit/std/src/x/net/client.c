#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <poll.h>

#include "../net.h"

static xint64 __xclient_internal_descriptor_event_on(xdescriptor * descriptor, xuint32 mask, void * p, xval data)
{
    xassertion(descriptor == xnil || p == xnil, "null pointer");
    xclient * client = (xclient *) p;

    xcheck(client->on == xnil && client->parent, "no event handler");

    return client->on ? client->on((xeventobj *) p, mask, xnil, data) : xfail;
}

static inline xuint32 __xpoll_convert_mask_to_pollmask(xuint32 mask)
{
    xuint32 result = 0;
    if(mask & (xdescriptor_status_in | xclient_event_connected))
    {
        result |= POLLIN;
    }
    if(mask & xdescriptor_status_out)
    {
        result |= POLLOUT;
    }
    if(mask & xdescriptor_status_exception)
    {
        result |= (POLLPRI | POLLRDHUP | POLLERR | POLLHUP | POLLNVAL);
    }
    else
    {
        if(mask & xdescriptor_status_read_hangup)
        {
            result |= POLLRDHUP;
        }
        if(mask & xdescriptor_status_pri)
        {
            result |= POLLPRI;
        }
        if(mask & xdescriptor_status_hangup)
        {
            result |= POLLHUP;
        }
        if(mask & xdescriptor_status_error)
        {
            result |= POLLERR;
        }
        if(mask & xdescriptor_status_invalid)
        {
            result |= POLLNVAL;
        }
    }
    return result;
}

extern xclient * xclientnew(int domain, int type, int protocol, xeventobjon handler)
{
    xclient * o = (xclient *) calloc(sizeof(xclient), 1);
    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags               = (xobj_mask_allocated | xobj_type_event_client);
    o->destruct            = xsocketrem;
    o->on                  = handler;
    
    o->descriptor.handle.f = xinvalid;
    o->descriptor.parent   = o;
    o->descriptor.on       = __xclient_internal_descriptor_event_on;

    o->domain              = domain;
    o->type                = type;
    o->protocol            = protocol;

    return o;
}

extern void * xclientrem(void * p)
{
    xclient * o = (xclient *) p;

    if(o)
    {
        xassertion(xobjtype(o) != xobj_type_event_client, "invalid object");

        xsynclock(o->sync);
        xeventobj * parent = o->parent;
        if(parent)
        {
            xsynclock(parent->sync);
            xeventobj * prev = o->prev;
            xeventobj * next = o->next;
            if(prev)
            {
                prev->next = next;
            }
            else
            {
                parent->head = next;
            }
            if(next)
            {
                next->prev = prev;
            }
            else
            {
                parent->tail = prev;
            }
            parent->total = parent->total - 1;
            xsyncunlock(parent->sync);
            o->prev = xnil;
            o->next = xnil;
            o->parent = xnil;
        }
        if(xsocketalive(o))
        {
            xclientshutdown(o, xdescriptor_event_close);
        }
        o->readbuf = xobjrem(o->readbuf);
        o->writebuf = xobjrem(o->writebuf);
        o->addr = xfree(o->addr);
        o->addrlen = 0;
        // check need to clear children
        xsyncunlock(o->sync);
        o->sync = xobjrem(o->sync);
        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}

extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen)
{
    if(o)
    {
        xassertion(addr == xnil || addrlen == 0, "invalid parameter");

        if(xclientalive(o) == xfalse)
        {
            xint32 ret = xclientopen(o);
            if(ret != xsuccess)
            {
                xcheck(xtrue, "fail to xclientopen");
                return xfail;
            }
        }
        if((o->descriptor.status & xclient_status_connected) == xdescriptor_status_void)
        {
            o->addr = xdup(addr, addrlen);
            o->addrlen = addrlen;

            int ret = connect(o->descriptor.handle.f, (struct sockaddr * ) addr, addrlen);
            if(ret == xsuccess)
            {
                o->descriptor.status |= xclient_status_connected;
                o->descriptor.status &= (~xclient_status_connecting);
                xdescriptoreventpub(xaddressof(o->descriptor), xclient_event_connected, o, xvalgen(0));
                return xsuccess;
            }
            else
            {
                int err = errno;
                if(err == EINPROGRESS)
                {
                    o->descriptor.status |= xclient_status_connecting;
                    xdescriptoreventpub(xaddressof(o->descriptor), xclient_status_connecting, o, xvalgen(0));
                    return xsuccess;
                }
                xclientclose(o);
                // DEBUG CODE : REMOVE XASSERTION
                if(err == ECONNREFUSED)
                {
                    return xfail;
                }
                xassertion(xtrue, "fail to connect (%d) check this", err);
                // ECONNREFUSED
                return xfail;
            }
        }
        else
        {
            return xsuccess;
        }
    }
    else
    {
        xcheck(o == xnil, "null pointer");
    }
    return xfail;
}

extern xint32 xclientreconnect(xclient * o)
{
    if(o)
    {
        xassertion(o->addr == xnil || o->addrlen == 0, "invalid parameter");

        if(xclientalive(o) == xfalse)
        {
            xint32 ret = xclientopen(o);
            if(ret != xsuccess)
            {
                xcheck(xtrue, "fail to xclientopen");
                return xfail;
            }
        }
        if((o->descriptor.status & xclient_status_connected) == xdescriptor_status_void)
        {
            int ret = connect(o->descriptor.handle.f, (struct sockaddr * ) o->addr, o->addrlen);
            if(ret == xsuccess)
            {
                o->descriptor.status |= xclient_status_connected;
                o->descriptor.status &= (~xclient_status_connecting);
                xdescriptoreventpub(xaddressof(o->descriptor), xclient_event_connected, o, xvalgen(0));
                return xsuccess;
            }
            else
            {
                int err = errno;
                if(err == EINPROGRESS)
                {
                    o->descriptor.status |= xclient_status_connecting;
                    xdescriptoreventpub(xaddressof(o->descriptor), xclient_status_connecting, o, xvalgen(0));
                    return xsuccess;
                }
                xclientclose(o);
                // DEBUG CODE : REMOVE XASSERTION
                if(err == ECONNREFUSED)
                {
                    return xfail;
                }
                xassertion(xtrue, "fail to connect (%d) check this", err);
                // ECONNREFUSED
                return xfail;
            }
        }
        else
        {
            return xsuccess;
        }
    }
    else
    {
        xcheck(o == xnil, "null pointer");
    }

    return xfail;
}

extern xuint32 xclientwait(xclient * o, xuint32 mask, xuint64 second, xuint64 nanosecond)
{
    if(o)
    {
        if(xclientalive(o))
        {
            if(mask)
            {
                xuint32 result = xdescriptor_event_void;

                struct pollfd data;
                data.fd      = o->descriptor.handle.f;
                data.events  = __xpoll_convert_mask_to_pollmask(mask);
                data.revents = 0;

                xtime start  = xtimeget();
                xtime end    = xtimeset(start.second + second, start.nanosecond + nanosecond);

                while((result & mask) != mask)
                {
                    data.revents = 0;
                    struct timespec timeout = { 0, 1000 };      // 1 unisecond
                    int nfds = ppoll(&data, 1, &timeout, xnil); // TODO: SIGNAL HANDLING
                    if(nfds >= 0)
                    {
                        if(mask & xclient_event_connected)
                        {
                            if((o->descriptor.status & xclient_status_connected) == xdescriptor_status_void)
                            {
                                int ret = connect(o->descriptor.handle.f, o->addr, o->addrlen);
                                if(ret == xsuccess)
                                {
                                    o->descriptor.status |= xclient_status_connected;
                                    o->descriptor.status &= (~xclient_status_connecting);
                                    xdescriptoreventpub(xaddressof(o->descriptor), xclient_event_connected, o, xvalgen(0));
                                    result |= xclient_event_connected;
                                }
                                else
                                {
                                    int err = errno;
                                    if(err == EALREADY)
                                    {
                                        o->descriptor.status |= xclient_status_connected;
                                        o->descriptor.status &= (~xclient_status_connecting);
                                        xdescriptoreventpub(xaddressof(o->descriptor), xclient_event_connected, o, xvalgen(0));
                                        result |= xclient_event_connected;
                                    }
                                    else
                                    {
                                        if(err == ECONNREFUSED)
                                        {
                                            return xdescriptor_event_exception;
                                        }
                                        xassertion(xtrue, "fail to connect (%d)", err);
                                    }
                                }
                            }

                            if(data.revents & POLLIN)
                            {
                                data.revents &= (~POLLIN);
                            }
                        }

                        if(data.revents & POLLIN)
                        {
                            result |= xdescriptor_event_in;
                        }
                        if(data.revents & POLLOUT)
                        {
                            result |= xdescriptor_event_out;
                        }
                        if(data.revents & POLLPRI)
                        {
                            result |= (xdescriptor_event_pri | xdescriptor_event_exception);
                        }
                        if(data.revents & POLLRDHUP)
                        {
                            result |= (xdescriptor_event_read_hangup | xdescriptor_event_exception);
                        }
                        if(data.revents & POLLERR)
                        {
                            result |= (xdescriptor_event_error | xdescriptor_event_exception);
                        }
                        if(data.revents & POLLHUP)
                        {
                            result |= (xdescriptor_event_hangup | xdescriptor_event_exception);
                        }
                        if(data.revents & POLLNVAL)
                        {
                            result |= (xdescriptor_event_invalid | xdescriptor_event_exception);
                        }
                        if(result & xdescriptor_event_exception)
                        {
                            // TODO: CHECK OTHER EXCEPTION ...
                            return result;
                        }
                        else
                        {
                            if((result & mask) != mask && (second > 0 || nanosecond > 0))
                            {
                                xtime current = xtimeget();
                                if(xtimecmp(&current, &end) >= 0)
                                {
                                    result |= xdescriptor_event_timeout;
                                    return result;
                                }
                            }
                        }
                    }
                    else
                    {
                        xassertion(xtrue, "fail to poll (%d)", errno);
                    }
                }
            }
            else
            {
                xcheck(xtrue, "no event mask");
                return xdescriptor_event_void;
            }
        }
        else
        {
            xcheck(xtrue, "not alive descriptor");
            return xdescriptor_event_exception;
        }
    }
    else
    {
        xcheck(xtrue, "null pointer");
        return xdescriptor_event_exception;
    }
}

// extern xclient * xclientnew(int domain, int type, int protocol)
// {
//     xclient * o = (xclient *) calloc(sizeof(xclient), 1);

//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     o->flags = (xobj_type_client | xobj_mask_allocated);
//     o->destruct = xclientrem;

//     o->descriptor = xdescriptorinit();

//     o->domain = domain;
//     o->type = type;
//     o->protocoal = protocol;

//     return o;
// }

// extern void * xclientrem(void * p)
// {
//     xclient * o = (xclient *) p;
//     xcheck(o == xnil, "null pointer");
//     if(o)
//     {
//         xsocketclose(o);

//         o->protocoal = 0;
//         o->type = 0;
//         o->domain = 0;

//         o->addr = xfree(o->addr);
//         o->addrlen = 0;

//         if(xobjallocated(o))
//         {
//             free(o);
//             o = xnil;
//         }
//     }
//     return o;
// }

// extern xint32 xclientconnect(xclient * o, void * addr, xuint64 addrlen)
// {
//     xcheck(o == xnil, "null pointer");
//     if(o)
//     {
//         xcheck(xsocketalive(o), "alive socket");
//         if(xsocketalive(o) == xfalse)
//         {
//             int ret = xsocketopen((xsocket *) o);
//             if(ret == xsuccess)
//             {
//                 o->addr = xcopy(o->addr, addr, addrlen, o->addrlen < addrlen);
//                 o->addrlen = addrlen;

//                 if(o->flags & xsocket_mask_nonblock)
//                 {
//                     ret = xdescriptor_nonblock_on(xaddressof(o->descriptor));
//                     xassertion(ret != xsuccess, "fail to nonblocking");
//                 }

//                 ret = connect(o->descriptor.value.f, (struct sockaddr *) o->addr, o->addrlen);
                
//                 if(ret != xsuccess)
//                 {
//                     int err = errno;
//                     if(o->flags & xsocket_mask_nonblock)
//                     {
//                         if(err == EINPROGRESS)
//                         {
//                             o->status |= xclient_status_connecting;
//                             return xsuccess;
//                         }
//                     }
//                     xcheck(xtrue, "fail to connect (%d)", err);
//                     xsocketclose(o);
//                     return xfail;
//                 }
//                 o->status |= xclient_status_connected;
//                 return xsuccess;
//             }
//             else
//             {
//                 xassertion(xtrue, "fail to xsocketopen");
//             }
//         }
//     }

//     return xfail;
// }

// extern xint32 xclientreconnect(xclient * o)
// {
//     xcheck(o == xnil, "null pointer");

//     if(o)
//     {
//         xcheck(xsocketalive(o), "alive socket");

//         if(xsocketalive(o) == xfalse)
//         {
//             xassertion(o->addr == xnil || o->addrlen == 0, "address is not exist");
//             int ret = xsocketopen((xsocket *) o);
//             if(ret == xsuccess)
//             {
//                 if(o->flags & xsocket_mask_nonblock)
//                 {
//                     ret = xdescriptor_nonblock_on(xaddressof(o->descriptor));
//                     xassertion(ret != xsuccess, "fail to nonblocking");
//                 }
//                 ret = connect(o->descriptor.value.f, (struct sockaddr *) o->addr, o->addrlen);
                
//                 if(ret != xsuccess)
//                 {
//                     xsocketclose(o);
//                     return xfail;
//                 }
//                 return xsuccess;
//             }
//             else
//             {
//                 xassertion(xtrue, "fail to xsocketopen");
//             }
//         }
//     }

//     return xfail;
// }

// extern xuint32 xclientwait(xclient * o, xuint32 mask, xuint64 nanosecond)
// {
//     xcheck(o == xnil, "null pointer");
//     if(o)
//     {
//         xcheck(xsocketalive(o) == xfalse, "client is not alive");
//         if(xsocketalive(o))
//         {
//             int result = xclient_event_void;
//             if(mask & xclient_event_connect)
//             {
//                 struct pollfd fds = { xinvalid, (POLLIN | POLLOUT), 0 };
//                 fds.fd = o->descriptor.value.f;
//                 if(mask & xdescriptor_event_error)
//                 {
//                     fds.events |= POLLERR;
//                 }
//                 if(mask & xdescriptor_event_pri)
//                 {
//                     fds.events |= POLLPRI;
//                 }
//                 if(mask & xdescriptor_event_readhup)
//                 {
//                     fds.events |= POLLRDHUP;
//                 }
//                 if(mask & xdescriptor_event_hup)
//                 {
//                     fds.events |= POLLHUP;
//                 }
//                 if(mask & xdescriptor_event_invalid)
//                 {
//                     fds.events |= POLLNVAL;
//                 }
//                 if(mask & xdescriptor_event_readband)
//                 {
//                     fds.events |= POLLRDBAND;
//                 }
//                 if(mask & xdescriptor_event_writeband)
//                 {
//                     fds.events |= POLLWRBAND;
//                 }
//                 int result = xdescriptor_event_void;
//                 struct timespec start = { 0, 0};
//                 struct timespec current = { 0, 0 };
//                 struct timespec diff = { 0, 0};
//                 clock_gettime(CLOCK_REALTIME, &start);  // TODO: CHECK FAIL
//                 struct timespec timespec = { 0, 1000 };
//                 while((result & mask) != mask)
//                 {
//                     int nfds = ppoll(&fds, 1, &timespec, xnil);
//                     if(nfds >= 0)
//                     {
//                         if(fds.revents & POLLIN)
//                         {
//                             result |= xdescriptor_event_read;
//                         }
//                         if(fds.revents & POLLOUT)
//                         {
//                             result |= xdescriptor_event_write;
//                         }
//                         if(fds.revents & POLLPRI)
//                         {
//                             result |= xdescriptor_event_pri;
//                         }
//                         if(fds.revents & POLLERR)
//                         {
//                             result |= xdescriptor_event_error;
//                         }
//                         if(fds.revents & POLLRDHUP)
//                         {
//                             result |= xdescriptor_event_readhup;
//                         }
//                         if(fds.revents & POLLHUP)
//                         {
//                             result |= xdescriptor_event_hup;
//                         }
//                         if(fds.revents & POLLRDBAND)
//                         {
//                             result |= xdescriptor_event_readband;
//                         }
//                         if(fds.revents & POLLWRBAND)
//                         {
//                             result |= xdescriptor_event_writeband;
//                         }
//                         if(fds.revents & POLLNVAL)
//                         {
//                             result |= xdescriptor_event_invalid;
//                         }
//                         int ret = connect(o->descriptor.value.f, (struct sockaddr *) o->addr, o->addrlen);
//                         if(ret == xsuccess)
//                         {
//                             result |= xclient_event_connect;
//                         }
//                         else if(ret < 0)
//                         {
//                             int err = errno;
//                             if(err == EALREADY || err == EISCONN)
//                             {
//                                 result |= xclient_event_connect;
//                             }
//                             else
//                             {
//                                 return xclient_event_except;
//                             }
//                         }
//                         clock_gettime(CLOCK_REALTIME, &current);
//                         diff.tv_sec = current.tv_sec - start.tv_sec;
//                         diff.tv_nsec = current.tv_nsec - start.tv_nsec;
//                         if(diff.tv_nsec < 0)
//                         {
//                             diff.tv_sec = diff.tv_sec - 1;
//                             diff.tv_nsec = 1000000000 + diff.tv_nsec;
//                         }
//                         if((result & mask) != mask)
//                         {
//                             if(nanosecond < xtimenanosecond(diff.tv_sec, diff.tv_nsec))
//                             {
//                                 result |= xdescriptor_event_timeout;
//                                 return result;
//                             }
//                         }
//                     }
//                     else
//                     {
//                         xassertion(xtrue, "fail to ppoll (%d)", errno);
//                         return xdescriptor_event_except;
//                     }
//                 }
//                 return result;
//             }
//             else
//             {
//                 return xdescriptorwait(xaddressof(o->descriptor), mask, nanosecond);
//             }
//         }
//     }
//     return xclient_event_except;
// }