#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "../net.h"

static xint32 __xsocket_internal_shutdown_method_convert(xuint32 how)
{
    if((how & xdescriptor_event_closeall) == xdescriptor_event_closeall)
    {
        return SHUT_RDWR;
    }
    else if(how & xdescriptor_event_closein)
    {
        return SHUT_RD;
    }
    else if(how & xdescriptor_event_closeout)
    {
        return SHUT_WR;
    }
    else
    {
        xassertion(xtrue, "invalid shutdown method");
        return 0;
    }
}

/**
 * @fn      extern xint32 xsocketopen(xsocket * o)
 * @brief   소켓을 오픈합니다.
 * 
 *              소켓 객체에 설정된 도메인, 타입, 프로토콜 정보를 통하여
 *              소켓을 오픈합니다. 소켓 오픈에 성공하고 이벤트 핸들러가 존재할 경우
 *              이벤트를 발생시킵니다.
 * 
 * @param   o | in | socket * | 소켓 객체 |
 * 
 * @return  | xint32 | 소켓 오픈 수행 상태 |
 * 
 *              소켓 오픈에 성공할 경우 성공 (0), 실패할 경우 실패 (-1) 을 리턴합니다.
 */
extern xint32 xsocketopen(xsocket * o)
{
    if(o)
    {
        if(xsocketalive(o) == xfalse)
        {
            o->handle.f = socket(o->domain, o->type, o->protocol);
            if(o->handle.f >= 0)
            {
                o->status |= xdescriptor_status_open;
                xsocketeventpub(o, xdescriptor_event_open, xnil, xvalgen(0));
                if(o->mask & xdescriptor_mask_nonblock)
                {
                    xsocketnonblock_on(o);
                }
                return xsuccess;
            }
            else
            {
                xcheck(xtrue, "fail to socket (%d)", errno);
                return xfail;
            }
        }
        else
        {
            xcheck(xtrue, "socket is already open");
            return xsuccess;
        }
    }
    else
    {
        xcheck(xtrue, "socket is null");
        return xfail;
    }
}

/**
 * @fn      extern xint32 xsocketshutdown(xsocket * socket, xint32 how)
 * @brief   소켓의 IN/OUT 상태를 종료합니다.
 * 
 *              소켓의 접속 상태를 파라미터에 따라서 IN, OUT 혹은 IN/OUT 모두를 종료합니다.
 *              이 함수와 별개로 `xsocketclose(socket)` 을 호출하여야
 *              모든 자원이 해제됩니다.
 * 
 * @param   socket | in | xsocket * | 소켓 객체 |
 * @param   how    | in | xuint32   | 소켓 종료 방법 |
 * 
 *              소켓 종료의 방법은 READ 만 닫을 경우
 *              `xsocketshutdown(socket, xdescriptor_event_closein)` 을
 *              호출하고, WRITE 만 닫을 경우
 *              `xsocketshutdown(socket, xdescriptor_event_closeout)` 을
 *              호출하고, 모두 닫을 경우
 *              `xsocketshutdown(socket, xdescriptor_event_closeall)` 을 호출합니다.
 *              또한, IN 혹은 OUT 만 닫았다고 하더라도,
 *              개별적인 CLOSE 이벤트를 발생시키고,
 *              IN/OUT 이 모두 닫혀 있는 이벤트를 발생시킵니다.
 * 
 * @return  | xint32 | 소켓 IN/OUT 종료 수행 상태 |
 * 
 *              함수 호출에 성공하면 성공(0)을 실패하면 실패(-1)을 리턴합니다.
 */
extern xint32 xsocketshutdown(xsocket * socket, xuint32 how)
{
    if(socket)
    {
        if(xsocketalive(socket))
        {
            int ret = shutdown(socket->handle.f, __xsocket_internal_shutdown_method_convert(how));
            if(ret == xsuccess)
            {
                if((how & xdescriptor_event_closeall) == xdescriptor_event_closeall)
                {
                    if((socket->status & xdescriptor_status_closeall) != xdescriptor_status_closeall)
                    {
                        socket->status |= xdescriptor_status_closeall;
                        xsocketeventpub(socket, xdescriptor_status_closeall, xnil, xvalgen(0));
                    }
                }
                else if(how & xdescriptor_event_closein)
                {
                    if(socket->status & xdescriptor_status_closein)
                    {
                        socket->status |= xdescriptor_status_closein;
                        xsocketeventpub(socket, xdescriptor_event_closein, xnil, xvalgen(0));
                    }
                    if((socket->status & xdescriptor_status_closeall) == xdescriptor_status_closeall)
                    {
                        xsocketeventpub(socket, xdescriptor_status_closeall, xnil, xvalgen(0));
                    }
                }
                else if(how & xdescriptor_event_closeout)
                {
                    if(socket->status & xdescriptor_event_closeout)
                    {
                        socket->status |= xdescriptor_status_closeout;
                        xsocketeventpub(socket, xdescriptor_event_closein, xnil, xvalgen(0));
                    }
                    if((socket->status & xdescriptor_status_closeall) == xdescriptor_status_closeall)
                    {
                        xsocketeventpub(socket, xdescriptor_status_closeall, xnil, xvalgen(0));
                    }
                }
            }
            else
            {
                xcheck(xtrue, "fail to shutdown (%d)", errno);
                return xfail;
            }
        }
        else
        {
            xcheck(xtrue, "socket is not alive");
        }
    }
    else
    {
        xcheck(xtrue, "socket is null");
    }

    return xsuccess;
}


// static inline int __xsocket_internal_convert_shutdown_method(xuint32 how)
// {
//     if((how & xdescriptor_event_close) == xdescriptor_event_close)
//     {
//         return SHUT_RDWR;
//     }
//     else if(how & xdescriptor_event_close_read)
//     {
//         return SHUT_RD;
//     }
//     else if(how & xdescriptor_event_close_write)
//     {
//         return SHUT_WR;
//     }
//     else
//     {
//         xassertion(xtrue, "invalid parameter");
//         return 0;
//     }
// }

// static xint64 __xsocket_internal_descriptor_event_on(xdescriptor * descriptor, xuint32 mask, void * p, xval data)
// {
//     xassertion(descriptor == xnil || p == xnil, "null pointer");
//     xsocket * socket = (xsocket *) p;

//     xcheck(socket->on == xnil && socket->parent, "no event handler");

//     return socket->on ? socket->on((xeventobj *) p, mask, xnil, data) : xfail;
// }

// extern xsocket * xsocketnew(int domain, int type, int protocol, xeventobjon handler)
// {
//     xsocket * o = (xsocket *) calloc(sizeof(xsocket), 1);
//     xassertion(o == xnil, "fail to calloc (%d)", errno);

//     o->flags               = (xobj_mask_allocated | xobj_type_event_socket);
//     o->destruct            = xsocketrem;
//     o->on                  = handler;
    
//     o->descriptor.handle.f = xinvalid;
//     o->descriptor.parent   = o;
//     o->descriptor.on       = __xsocket_internal_descriptor_event_on;

//     o->domain              = domain;
//     o->type                = type;
//     o->protocol            = protocol;

//     return o;
// }

// extern void * xsocketrem(void * p)
// {
//     xsocket * o = (xsocket *) p;

//     if(o)
//     {
//         xassertion(xobjtype(o) != xobj_type_event_socket, "invalid object");

//         xsynclock(o->sync);

//         // atomic get and set ...
//         xeventobj * parent = o->parent;
//         if(parent)
//         {
//             xeventobj * prev = o->prev;
//             xeventobj * next = o->next;
//             if(prev)
//             {
//                 prev->next = next;
//             }
//             else
//             {
//                 parent->head = next;
//             }
//             if(next)
//             {
//                 next->prev = prev;
//             }
//             else
//             {
//                 parent->tail = prev;
//             }
//             parent->total = parent->total - 1;
//             o->parent = xnil;
//             o->prev = xnil;
//             o->next = xnil;
//         }
//         while(o->head)
//         {
//             xeventobj * next = o->head->next;
//             xsynclock(o->head->sync);
//             if(next)
//             {
//                 next->prev = xnil;
//             }
//             else
//             {
//                 o->tail = xnil;
//             }
//             o->total = o->total - 1;
//             xsyncunlock(o->head->sync);
//             o->head = next;
//         }
//         if(xsocketalive(o))
//         {
//             xsocketshutdown(o, xdescriptor_event_close);
//         }
//         xsyncunlock(o->sync);
//         o->sync = xobjrem(o->sync);
//         if(xobjallocated(o))
//         {
//             free(o);
//             o = xnil;
//         }
//     }
//     return o;
// }

// extern xint32 xsocketshutdown(xsocket * o, xuint32 how)
// {
//     if(o)
//     {
//         if(o->descriptor.handle.f >= 0)
//         {
//             int ret = shutdown(o->descriptor.handle.f, __xsocket_internal_convert_shutdown_method(how));
//             if(ret == xsuccess)
//             {
//                 if((how & xdescriptor_event_close) != xdescriptor_event_close)
//                 {
//                     if(how & xdescriptor_event_close_read)
//                     {
//                         if((o->descriptor.status & xdescriptor_status_close_read) == xdescriptor_status_void)
//                         {
//                             o->descriptor.status |= xdescriptor_status_close_read;
//                             o->descriptor.status &= (~xdescriptor_status_in);
//                             xdescriptoreventpub(xaddressof(o->descriptor), xdescriptor_event_close_read, o, xvalgen(0));
//                         }
//                     }
//                     if(how & xdescriptor_event_close_write)
//                     {
//                         if((o->descriptor.status & xdescriptor_status_close_write) == xdescriptor_status_void)
//                         {
//                             o->descriptor.status |= xdescriptor_status_close_write;
//                             o->descriptor.status &= (~xdescriptor_status_out);
//                             xdescriptoreventpub(xaddressof(o->descriptor), xdescriptor_event_close_write, o, xvalgen(0));
//                         }
//                     }
//                 }
//                 if((o->descriptor.status & xdescriptor_status_close) == xdescriptor_status_close)
//                 {
//                     xsocketclose(o);
//                 }
//                 return xsuccess;
//             }
//             else
//             {
//                 int err = errno;
//                 if(err == ENOTCONN)
//                 {
//                     xsocketclose(o);
//                 }
//                 else
//                 {
//                     xcheck(xtrue, "fail to shutdown (%d)", err);
//                 }
//                 return xfail;
//             }
//         }
//         else
//         {
//             xcheck(xtrue, "not alive socket");
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
//     return xsuccess;
// }

// extern xint32 xsocketopen(xsocket * o)
// {
//     if(o)
//     {
//         if(xsocketalive(o) == xfalse)
//         {
//             o->descriptor.handle.f = socket(o->domain, o->type, o->protocol);
//             if(o->descriptor.handle.f >= 0)
//             {
//                 o->descriptor.status |= xdescriptor_status_open;
//                 if(o->descriptor.mask & xdescriptor_mask_nonblock)
//                 {
//                     xdescriptornonblock_on(xaddressof(o->descriptor));
//                 }
//                 xdescriptoreventpub(xaddressof(o->descriptor), xdescriptor_event_open, o, xvalgen(0));
//                 return xsuccess;
//             }
//             else
//             {
//                 xcheck(xtrue, "fail to socket (%d)", errno);
//                 return xfail;
//             }
//         }
//         else
//         {
//             xcheck(xtrue, "already open");
//             return xsuccess;
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
//     return xfail;
// }

// extern xint32 xsocketbind(xsocket * o, void * addr, xuint64 addrlen)
// {
//     if(o)
//     {
//         if(addr && addrlen)
//         {
//             if(xsocketalive(o) == xfalse)
//             {
//                 xint32 ret = xsocketopen(o);
//                 if(ret != xsuccess)
//                 {
//                     xcheck(xtrue, "fail to xsocketopen");
//                     return xfail;
//                 }
//             }
//             if((o->descriptor.status & xsocket_status_bind) == xdescriptor_status_void)
//             {
//                 int ret = bind(o->descriptor.handle.f, (struct sockaddr *) addr, addrlen);
//                 if(ret == xsuccess)
//                 {
//                     o->descriptor.status |= xsocket_status_bind;
//                     xdescriptoreventpub(xaddressof(o->descriptor), xsocket_event_bind, o, xvalgen(0));
//                     return xsuccess;
//                 }
//                 else
//                 {
//                     xcheck(xtrue, "fail to bind (%d)", errno);
//                     // EADDRINUSE
//                     // NOT SOCKET CLOSE ... CHECK THIS ...
//                 }
//             }
//             else
//             {
//                 xcheck(xtrue, "already bind socket");
//                 return xsuccess;
//             }
//         }
//         else
//         {
//             xassertion(xtrue, "invalid parameter (address)");
//         }
//     }
//     else
//     {
//         xcheck(xtrue, "null pointer");
//     }
//     return xfail;
// }

// // static xint32 __xsocket_internal_shutdown_method_convert(xint32 how)
// // {
// //     xint32 result = 0;
// //     if((how & xdescriptor_event_close) == xdescriptor_event_close)
// //     {
// //         result = SHUT_RDWR;
// //     }
// //     else if(how & xdescriptor_event_close_read)
// //     {
// //         result = SHUT_RD;
// //     }
// //     else if(how & xdescriptor_event_close_write)
// //     {
// //         result = SHUT_WR;
// //     }
// //     else
// //     {
// //         xassertion(xtrue, "invalid parameter");
// //     }
// //     return result;
// // }

// // extern xsocket * xsocketnew(int domain, int type, int protocol)
// // {
// //     xsocket * o = (xsocket *) calloc(sizeof(xsocket), 1);
// //     xassertion(o == xnil, "fail to calloc (%d)", errno);

// //     o->flags    = (xobj_mask_allocated | xobj_type_socket);
// //     o->destruct = xsocketrem;

// //     o->value.f  = xinvalid;

// //     o->domain   = domain;
// //     o->type     = type;
// //     o->protocol = protocol;

// //     return o;
// // }

// // extern void * xsocketrem(void * p)
// // {
// //     xsocket * o = (xsocket *) p;
// //     xcheck(o == xnil, "null pointer");
// //     if(o)
// //     {
// //         xassertion(xobjtype(o) != xobj_type_socket, "invalid object");

// //         xsynclock(o->sync);
// //         if(o->parent)
// //         {
// //             xsynclock(o->parent->sync);
// //             xdescriptor * prev = o->prev;
// //             xdescriptor * next = o->next;
// //             if(prev)
// //             {
// //                 prev->next = next;
// //             }
// //             else
// //             {
// //                 o->parent->head = next;
// //             }
// //             if(next)
// //             {
// //                 next->prev = prev;
// //             }
// //             else
// //             {
// //                 o->parent->tail = prev;
// //             }
// //             o->parent->total = o->parent->total - 1;
// //             xsyncunlock(o->parent->sync);
// //             o->parent = xnil;
// //         }
// //         o->sync = xobjrem(o->sync);
// //         if(xsocketalive(o))
// //         {
// //             xsocketshutdown(o, xdescriptor_event_close);
// //         }
// //         xsyncunlock(o->sync);
// //         if(xobjallocated(o))
// //         {
// //             free(o);
// //             o = xnil;
// //         }
// //     }
// //     return o;
// // }

// // extern xint32 xsocketshutdown(xsocket * o, int how)
// // {
// //     if(o)
// //     {
// //         if(xsocketalive(o))
// //         {
// //             int ret = shutdown(o->value.f, __xsocket_internal_shutdown_method_convert(how));

// //             if(ret == xsuccess)
// //             {
// //                 int mask = xdescriptor_event_void;
// //                 if(how & xdescriptor_event_close_read)
// //                 {
// //                     o->status |= xdescriptor_status_close_read;
// //                     o->status &= (~xdescriptor_status_read);
// //                     mask |= xdescriptor_event_close_read;
// //                 }
// //                 if(how & xdescriptor_event_close_write)
// //                 {
// //                     o->status |= xdescriptor_status_close_write;
// //                     o->status &= (~xdescriptor_status_write);
// //                     mask |= xdescriptor_event_close_write;
// //                 }
// //                 if(mask == xdescriptor_event_close)
// //                 {
// //                     xdescriptorpub(o, xdescriptor_event_close);
// //                 }
// //                 else
// //                 {
// //                     xdescriptorpub(o, mask);
// //                     if((o->status & xdescriptor_status_close) == xdescriptor_status_close)
// //                     {
// //                         o->value.f = xinvalid;
// //                         xdescriptorpub(o, xdescriptor_event_close);
// //                         o->status = xdescriptor_status_void;
// //                     }
// //                 }
// //                 return xsuccess;
// //             }
// //             else
// //             {
// //                 xcheck(ret != xsuccess, "fail to shutdown (%d)", errno);
// //                 return xfail;
// //             }
// //         }
// //         else
// //         {
// //             xcheck(xtrue, "already shutdown");
// //         }
// //     }
// //     else
// //     {
// //         xcheck(xtrue, "null pointer");
// //     }
// //     return xsuccess;
// // }

// // extern xint32 xsocketopen(xsocket * o)
// // {
// //     if(o)
// //     {
// //         if(xsocketalive(o) == xfalse)
// //         {
// //             int ret = socket(o->domain, o->type, o->protocol);
// //             if(ret < 0)
// //             {
// //                 return xfail;
// //             }
// //             else
// //             {
// //                 o->status |= xdescriptor_status_open;
// //                 xsocketpub(o, xdescriptor_event_open);
// //                 return xsuccess;
// //             }
// //         }
// //         else
// //         {
// //             xcheck(xtrue, "already open");
// //             return xsuccess;
// //         }
// //     }
// //     else
// //     {
// //         xcheck(xtrue, "null pointer");
// //     }
// //     return xfail;
// // }

// // extern xint32 xsoketbind(xsocket * o, void * addr, xuint64 addrlen)
// // {
// //     if(o)
// //     {
// //         if(xsocketalive(o))
// //         {
// //             if((o->status & xdescriptor_status_bind) == xdescriptor_status_void)
// //             {
// //                 if(addr && addrlen)
// //                 {
// //                     int ret = bind(o->value.f, addr, addrlen);
// //                     if(ret == xsuccess)
// //                     {
// //                         o->status |= xdescriptor_status_bind;

// //                         xsocketpub(o, xdescriptor_event_bind);

// //                         return xsuccess;
// //                     }
// //                     else
// //                     {
// //                         xcheck(xtrue, "fail to bind (%d)", errno);
// //                         return xfail;
// //                     }
// //                 }
// //                 else
// //                 {
// //                     xassertion(xtrue, "invalid parameter");
// //                 }
// //             }
// //             else
// //             {
// //                 xcheck(xtrue, "socket is already bind");
// //                 return xsuccess;
// //             }
// //         }
// //         else
// //         {
// //             xcheck(xtrue, "socket is not alive");
// //         }
// //     }
// //     else
// //     {
// //         xcheck(xtrue, "null pointer");
// //     }
// //     return xfail;
// // }



// // // extern xint32 xsocketopen(xsocket * o)
// // // {
// // //     xcheck(o == xnil, "null pointer");
// // //     if(o)
// // //     {
// // //         xcheck(xsocketalive(o), "socket is alive");
// // //         if(xsocketalive(o) == xfalse)
// // //         {
// // //             o->descriptor.value.f = socket(o->domain, o->type, o->protocoal);
            
// // //             xassertion(o->descriptor.value.f < 0, "fail to socket (%d)", errno);
// // //         }
// // //         return xsuccess;
// // //     }
// // //     return xfail;
// // // }

// // // extern xsocket * xsocketnew(int domain, int type, int protocol)
// // // {
// // //     xsocket * o = (xsocket *) calloc(sizeof(xsocket), 1);

// // //     o->flags = xobj_type_socket | xobj_mask_allocated;
// // //     o->destruct = xsocketrem;
    
// // //     o->descriptor = xdescriptorinit();

// // //     o->domain = domain;
// // //     o->type = type;
// // //     o->protocoal = protocol;

// // //     return o;
// // // }

// // // extern void * xsocketrem(void * p)
// // // {
// // //     xsocket * o = (xsocket *) p;
// // //     xcheck(o == xnil, "null pointer");

// // //     if(o)
// // //     {
// // //         xassertion(xobjtype(o) != xobj_type_socket, "invalid object");

// // //         xsocketclose(o);

// // //         if(xobjallocated(o))
// // //         {
// // //             free(o);
// // //             o = xnil;
// // //         }
// // //     }

// // //     return o;
// // // }

// // // extern xint64 xsocketwrite(xsocket * o, const xbyte * data, xuint64 len)
// // // {
// // //     xcheck(o == xnil, "null pointer");
// // //     if(o)
// // //     {
// // //         xcheck(xsocketalive(o) == xfalse, "socket is closed");
// // //         if(xsocketalive(o))
// // //         {
// // //             xcheck(len == 0, "invalid parameter");
// // //             if(len > 0)
// // //             {
// // //                 xint64 n = write(o->descriptor.value.f, data, len);
// // //                 if(n > 0)
// // //                 {
// // //                     return n;
// // //                 }
// // //                 else if(n == 0)
// // //                 {
// // //                     xcheck(xtrue, "check this logic");
// // //                 }
// // //                 else
// // //                 {
// // //                     int ret = errno;
// // //                     if(ret == EAGAIN)
// // //                     {
// // //                         return xsuccess;
// // //                     }
// // //                     xcheck(xtrue, "fail to write (%d)", errno);
// // //                     xsocketclose(o);
// // //                     return xfail;
// // //                 }
// // //             }
// // //             return xsuccess;
// // //         }
// // //     }
// // //     return xfail;
// // // }

// // // extern xint64 xsocketread(xsocket * o, void * buffer, xuint64 len)
// // // {
// // //     xcheck(o == xnil, "null pointer");
// // //     if(o)
// // //     {
// // //         xcheck(xsocketalive(o) == xfalse, "socket is closed");
// // //         if(xsocketalive(o))
// // //         {
// // //             xcheck(len == 0, "invalid parameter");
// // //             if(len > 0)
// // //             {
// // //                 xint64 n = read(o->descriptor.value.f, buffer, len);
// // //                 if(n > 0)
// // //                 {
// // //                     return n;
// // //                 }
// // //                 else if(n == 0)
// // //                 {
// // //                     // socket read zero is close
// // //                     return xfail;
// // //                 }
// // //                 else
// // //                 {
// // //                     int ret = errno;
// // //                     if(ret == EAGAIN)
// // //                     {
// // //                         return xsuccess;
// // //                     }
// // //                     xcheck(xtrue, "fail to write (%d)", errno);
// // //                     xsocketclose(o);
// // //                     return xfail;
// // //                 }
// // //             }
// // //             return xsuccess;
// // //         }
// // //     }
// // //     return xfail;
// // // }

// // // extern xsocket * xsocketmaskadd(xsocket * o, xuint32 mask)
// // // {
// // //     xcheck(o == xnil, "null pointer");
// // //     if(o)
// // //     {
// // //         xassertion(mask & (~xsocket_masks), "invalid socket mask");

// // //         o->flags |= mask;
// // //         if(xsocketalive(o))
// // //         {
// // //             switch(mask)
// // //             {
// // //                 case xsocket_mask_nonblock: xassertion(xsocket_nonblock_on(o)!=xsuccess, "fail to nonblocking"); break;
// // //             }
// // //         }
// // //     }
// // //     return o;
// // // }

// // // extern xint32 xsocket_nonblock_on(xsocket * o)
// // // {
// // //     if(o)
// // //     {
// // //         o->flags |= xsocket_mask_nonblock;
// // //         return xdescriptor_nonblock_on(xaddressof(o->descriptor));
// // //     }
// // //     return xfail;
// // // }

// // // extern xint32 xsocket_nonblock_off(xsocket * o)
// // // {
// // //     if(o)
// // //     {
// // //         o->flags &= (~xsocket_mask_nonblock);
// // //         return xdescriptor_nonblock_off(xaddressof(o->descriptor));
// // //     }
// // //     return xfail;
// // // }

// // // extern xuint32 xsocketwait(xsocket * o, xuint32 mask, xuint64 unisecond)
// // // {
// // //     if(o)
// // //     {
// // //         return xdescriptorwait(xaddressof(o->descriptor), mask, unisecond);
// // //     }
// // //     return xfail;
// // // }