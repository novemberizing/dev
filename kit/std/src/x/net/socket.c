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
                xsocketeventpub(o, o->data, xdescriptor_event_open, xnil, xvalgen(0));
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
                        xsocketeventpub(socket, socket->data, xdescriptor_status_closeall, xnil, xvalgen(0));
                    }
                }
                else if(how & xdescriptor_event_closein)
                {
                    if(socket->status & xdescriptor_status_closein)
                    {
                        socket->status |= xdescriptor_status_closein;
                        xsocketeventpub(socket, socket->data, xdescriptor_event_closein, xnil, xvalgen(0));
                    }
                    if((socket->status & xdescriptor_status_closeall) == xdescriptor_status_closeall)
                    {
                        xsocketeventpub(socket, socket->data, xdescriptor_status_closeall, xnil, xvalgen(0));
                    }
                }
                else if(how & xdescriptor_event_closeout)
                {
                    if(socket->status & xdescriptor_event_closeout)
                    {
                        socket->status |= xdescriptor_status_closeout;
                        xsocketeventpub(socket, socket->data, xdescriptor_event_closein, xnil, xvalgen(0));
                    }
                    if((socket->status & xdescriptor_status_closeall) == xdescriptor_status_closeall)
                    {
                        xsocketeventpub(socket, socket->data, xdescriptor_status_closeall, xnil, xvalgen(0));
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

extern xint32 xsocketbind(xsocket * socket, void * addr, xuint64 addrlen)
{
    if(socket)
    {
        if(xsocketalive(socket) == xfalse)
        {
            int ret = xsocketopen(socket);
            if(ret != xsuccess)
            {
                xcheck(xtrue, "fail to xsocketopen");
                return xfail;
            }
        }
        if((socket->status & xdescriptor_status_bind) == xdescriptor_status_void)
        {
            int ret = bind(socket->handle.f, (struct sockaddr *) addr, addrlen);

            if(ret == xsuccess)
            {
                socket->status |= xdescriptor_status_bind;
                xsocketeventpub(socket, socket->data, xdescriptor_event_bind, xnil, xvalgen(0));
                return xsuccess;
            }
            else
            {
                xcheck(xtrue, "fail to bind (%d)", errno);
                xsocketclose(socket);
                return xfail;
            }
        }
        else
        {
            xcheck(xtrue, "socket is already bind");
            return xsuccess;
        }
    }
    else
    {
        xcheck(xtrue, "socket is null");
    }

    return xfail;
}
