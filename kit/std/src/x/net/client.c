#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include "../net.h"

extern xclient * xclientnew(int domain, int type, int protocol)
{
    xclient * o = (xclient *) calloc(sizeof(xclient), 1);

    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = (xobj_type_client | xobj_mask_allocated);
    o->destruct = xclientrem;

    o->domain = domain;
    o->type = type;
    o->protocoal = protocol;

    return o;
}

extern void * xclientrem(void * p)
{
    xclient * o = (xclient *) p;
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xsocketclose(o);

        o->protocoal = 0;
        o->type = 0;
        o->domain = 0;

        o->addr = xfree(o->addr);
        o->addrlen = 0;

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
    xcheck(o == xnil, "");
    if(o)
    {
        xcheck(xsocketalive(o), "alive socket");
        if(xsocketalive(o) == xfalse)
        {
            int ret = xsocketopen((xsocket *) o);
            if(ret == xsuccess)
            {
                o->addr = xcopy(o->addr, addr, addrlen, o->addrlen < addrlen);
                o->addrlen = addrlen;

                if(o->flags & xsocket_mask_nonblock)
                {
                    ret = xdescriptor_nonblock_on(xaddressof(o->descriptor));
                    xassertion(ret != xsuccess, "fail to nonblocking");
                }

                ret = connect(o->descriptor.f, (struct sockaddr *) o->addr, o->addrlen);
                
                if(ret != xsuccess)
                {
                    int err = errno;
                    if(o->flags & xsocket_mask_nonblock)
                    {
                        if(err == EINPROGRESS)
                        {
                            o->status |= xclient_status_connecting;
                            return xsuccess;
                        }
                    }
                    xcheck(xtrue, "fail to connect (%d)", err);
                    xsocketclose(o);
                    return xfail;
                }
                o->status |= xclient_status_connected;
                return xsuccess;
            }
            else
            {
                xassertion(xtrue, "fail to xsocketopen");
            }
        }
    }

    return xfail;
}

extern xint32 xclientreconnect(xclient * o)
{
    xcheck(o == xnil, "null pointer");

    if(o)
    {
        xcheck(xsocketalive(o), "alive socket");

        if(xsocketalive(o) == xfalse)
        {
            xassertion(o->addr == xnil || o->addrlen == 0, "address is not exist");
            int ret = xsocketopen((xsocket *) o);
            if(ret == xsuccess)
            {
                if(o->flags & xsocket_mask_nonblock)
                {
                    ret = xdescriptor_nonblock_on(xaddressof(o->descriptor));
                    xassertion(ret != xsuccess, "fail to nonblocking");
                }
                ret = connect(o->descriptor.f, (struct sockaddr *) o->addr, o->addrlen);
                
                if(ret != xsuccess)
                {
                    xsocketclose(o);
                    return xfail;
                }
                return xsuccess;
            }
            else
            {
                xassertion(xtrue, "fail to xsocketopen");
            }
        }
    }

    return xfail;
}

extern xuint32 xclientwait(xclient * o, xuint32 mask, xuint64 unisecond)
{
    xcheck(o == xnil, "null pointer");
    if(o)
    {
        xcheck(xsocketalive(o) == xfalse, "client is not alive");
        if(xsocketalive(o))
        {
            if(mask == xclient_event_connect)
            {
                struct timeval basis;
                gettimeofday(&basis, xnil); // CHECK FAIL

                while(xtrue)
                {
                    fd_set readfds;
                    fd_set writefds;
                    fd_set exceptfds;

                    FD_ZERO(&readfds);
                    FD_ZERO(&writefds);
                    FD_ZERO(&exceptfds);

                    FD_SET(o->descriptor.f, &readfds);
                    FD_SET(o->descriptor.f, &writefds);
                    FD_SET(o->descriptor.f, &exceptfds);

                    struct timeval timeval = { 0, 1 };
                    printf("count\n");

                    int ret = select(1, &readfds, &writefds, &exceptfds, &timeval);

                    if(ret >= 0)
                    {
                        if(FD_ISSET(o->descriptor.f, &exceptfds))
                        {
                            int err = 0;
                            socklen_t len = sizeof(int);
                            // check fail to getsockopt
                            getsockopt(o->descriptor.f, SOL_SOCKET, SO_ERROR, &err, &len);
                            printf("getsockopt => %d\n", err);
                            // check this logic
                            if(err == EINPROGRESS)
                            {
                                struct timeval current;
                                struct timeval diff;
                                gettimeofday(&current, xnil);   // TODO: ERROR HANDLING
                                timersub(&current, &basis, &diff);
                                if(xtimeunisecond(diff.tv_sec, diff.tv_usec) < unisecond)
                                {
                                    continue;
                                }
                                return xclient_event_timeout;
                            }
                            else if(err == EALREADY || err == EISCONN)
                            {
                                return xclient_event_connect;
                            }
                            else
                            {
                                xcheck(xtrue, "fail to connect (%d)", err);
                                return xclient_event_except;
                            }
                            return xclient_event_except;
                        }
                        /**
                         * https://www.gnu.org/software/libc/manual/html_node/Connecting.html
                         * 
                         * EINPROGRESS
                         * 
                         * The socket socket is nonblocking and the connection could
                         * not be established immediately. You can determine when the
                         * connection is completely established with select;
                         * see Waiting for I/O. Another connect call on the same socket,
                         * before the connection is completely established, will
                         * fail with EALREADY.
                         */
                        ret = connect(o->descriptor.f, (struct sockaddr *) o->addr, o->addrlen);
                        if(ret != xsuccess)
                        {
                            int err = errno;
                            if(err == EINPROGRESS)
                            {
                                struct timeval current;
                                struct timeval diff;
                                gettimeofday(&current, xnil);   // TODO: ERROR HANDLING
                                timersub(&current, &basis, &diff);
                                if(xtimeunisecond(diff.tv_sec, diff.tv_usec) < unisecond)
                                {
                                    continue;
                                }
                                return xclient_event_timeout;
                            }
                            else if(err == EALREADY || err == EISCONN)
                            {
                                return xclient_event_connect;
                            }
                            else
                            {
                                xcheck(xtrue, "fail to connect (%d)", err);
                                return xclient_event_except;
                            }
                        }
                    }
                    else
                    {
                        xassertion(xtrue, "fail to select (%d)", errno);
                        return xclient_event_except;
                    }
                }
                return xclient_event_connect;
            }
            else if(mask == xclient_event_write)
            {
                return xdescriptorwait(xaddressof(o->descriptor), mask, unisecond);
            }
            else if(mask == xclient_event_read)
            {
                return xdescriptorwait(xaddressof(o->descriptor), mask, unisecond);
            }
            else
            {
                xassertion(xtrue, "unsupported event");
                return xclient_event_except;
            }
        }
    }
    return xclient_event_except;
}