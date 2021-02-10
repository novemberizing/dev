#include <errno.h>

#include "epoll.h"

/**
 * @fn      extern xeventgenerator_node * xdescriptorevent_generator_register_object(xdescriptorevent_generator * o, xdescriptor * descriptor)
 * @brief   [INTERNAL] 디스크립터 이벤트 제네레이터에 디스크립터를 등록합니다.
 * @details 디스크립터 이벤트 제네레이터에는 오픈 상태의 디스크립트가 등록됩니다.
 *          만약에, 등록되어 있지 않다면, 이벤트 엔진에 이벤트로 등록되고,
 *          오픈이 필요하면 오픈을 수행하고, 예외 상태이면 종료를 수행하게 됩니다.
 * 
 * @param   o           | xdescriptorevent_generator * | in | 디스크립터 이벤트 제네레이터 |
 * @param   descriptor  | xdescriptor *                | in | 디스크립터 |
 * 
 * @return  | xeventgenerator_node * | 디스크립터 이벤트 제네레이터와 이벤트 객체에서 관리하는 이벤트 객체 노드를 리턴합니다. |
 * 
 *              만약에 디스크립터가 오픈한 상태가 아니면 널을 리턴합니다.
 *              리턴하기 전에 이벤트 엔진에 상태에 따른 처리를 위한 이벤트를 등록하게 됩니다.
 */
extern xeventgenerator_node * xdescriptorevent_generator_register_object(xdescriptorevent_generator * o, xdescriptor * descriptor)
{
    xassertion(o == xnil, "generator is null");

    if(descriptor)
    {
        if(descriptor->handle.f >= 0)
        {
            if((descriptor->status & xdescriptorstatus_exception) == xdescriptorstatus_void)
            {
                if(descriptor->status & xdescriptorstatus_open)
                {
                    xdescriptorevent_generator_epoll * generator = (xdescriptorevent_generator_epoll *) o;
                    if(generator->f >= 0)
                    {
                        xint32 ret = xdescriptorevent_generator_epoll_register_descriptor(generator->f, descriptor);
                        if(ret == xsuccess)
                        {
                            return xeventgenerator_register_object(o, (xeventobject *) descriptor);
                        }
                        descriptor->status |= xdescriptorstatus_exception;
                    }
                    else
                    {
                        return xeventgenerator_register_object(o, (xeventobject *) descriptor);
                    }
                }
            }
        }
        xeventengine_dispatch_event(descriptor->enginenode.cntr, descriptor);
    }
    else
    {
        xcheck(descriptor == xnil, "descriptor is null");
    }

    return xnil;
}

/**
 * @fn      extern void xdescriptorevent_generator_unregister_object(xeventgenerator_node * node)
 * @brief   [INTERNAL] 디스크립터 이벤트 제네레이터 노드를 삭제합니다.
 * @details 노드를 삭제함과 동시에 EPOLL 에 등록된 이벤트 역시 삭제합니다.
 * 
 * @param   node    | xeventgenerator_node * | 이벤트 제네레이터 노드 |
 * 
 * @todo    매우 위험한 코드다. 푸하하하하!
 *          만약에, 이벤트 제네레이터가 EPOLL 이 아니면 어떻게 될까... 푸하하하하하하하하하!
 *          파라미터를 통해서 체크하도록 할까?
 *          고민스러운 코드지만, 로직을 문제 없이 짠다면, 외부에서
 *          사용하더라도 문제가 없을 것이다.
 *          그렇게 하기 위해서 외부로 노출한 함수와 구조체를 잘 선별해야 한다.
 */
extern void xdescriptorevent_generator_unregister_object(xeventgenerator_node * node)
{
    if(node)
    {
        xdescriptor * descriptor = (xdescriptor *) node->generatornode.cntr;
        xdescriptorevent_generator_epoll * generator = (xdescriptorevent_generator_epoll *) node->objectnode.cntr;

        if(generator->f >= 0)
        {
            xdescriptorevent_generator_epoll_unregister_descriptor(generator->f, descriptor);
        }

        xeventgenerator_unregister_object(node);
    }
}

extern void xdescriptorevent_generator_once(xeventgenerator * o)
{
    xassertion(o == xnil, "generator is null");

    xdescriptorevent_generator_epoll * generator = (xdescriptorevent_generator_epoll *) o;

    if(xdescriptorevent_generator_epoll_create(generator) == xsuccess)
    {
        int nfds = epoll_wait(generator->f, generator->events, generator->maxevents, generator->timeout);
        if(nfds >= 0)
        {
            for(int i = 0; i < nfds; i++)
            {
                xdescriptor * descriptor = (xdescriptor *) generator->events[i].data.ptr;
                if(generator->events[i].events & (EPOLLERR | EPOLLHUP | EPOLLPRI | EPOLLRDHUP))
                {
                    descriptor->status |= xdescriptorstatus_exception;
                    xdescriptorevent_generator_epoll_unregister_descriptor(generator->f, descriptor);
                    xeventengine_dispatch_event(descriptor->enginenode.cntr, descriptor);
                    continue;
                }
            }
        }
        else
        {

        }
    }
}

/**
 * @fn      extern xint32 xdescriptorevent_generator_epoll_register_descriptor(int f, xdescriptor * descriptor)
 * @brief   [INTERNAL] EPOLL 에 등록합니다.
 * @details 상태를 플래그로 관리합니다. 즉, REGISTER 상태이면 MOD 를
 *          UNREGISTER 상태이면, ADD 를 수행합니다.
 *          그래도 상태가 잘못된 상태여서 ADD 시에 실패하면 MOD 를
 *          MOD 시에 실패하면 ADD 를 한번 더 수행하도록 하였습니다.
 * 
 *          이 함수를 수행하기 전에 디스크립터의 값이 0보다 크거나 같아야 합니다.
 * 
 * @param   f           | int           | in | EPOLL 파일 디스크립터 |
 * @param   descriptor  | xdescriptor * | in | 디스크립터 객체 |
 * 
 * @return  | xint32 | 등록된 결과 |
 * 
 *               0: (SUCCESS)
 *              -1: (FAIL)
 */
extern xint32 xdescriptorevent_generator_epoll_register_descriptor(int f, xdescriptor * descriptor)
{
    if(descriptor)
    {
        if(f >= 0)
        {
            xassertion(descriptor->status & xdescriptorstatus_exception, "exception descriptor");
            xassertion(descriptor->handle.f >= 0, "descriptor is not open");
            xassertion((descriptor->status & xdescriptorstatus_open) == xdescriptorstatus_void, "descriptor is not open");

            struct epoll_event event;

            event.data.ptr = descriptor;
            event.events = (EPOLLERR | EPOLLHUP | EPOLLRDHUP | EPOLLPRI | EPOLLET | EPOLLONESHOT);

            if(descriptor->status & xdescriptorstatus_register)
            {
                int ret = epoll_ctl(f, EPOLL_CTL_MOD, descriptor->handle.f, &event);
                if(ret != xsuccess)
                {
                    int err = errno;
                    if(err == ENOENT)
                    {
                        ret = epoll_ctl(f, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                        if(ret != xsuccess)
                        {
                            xcheck(ret != xsuccess, "fail to epoll_ctl (%d => %s)", errno, xerrorstr(epoll_ctl, errno));
                            return xfail;
                        }
                        descriptor->status |= xdescriptorstatus_register;
                        return xsuccess;
                    }
                    return xfail;
                }
                descriptor->status |= xdescriptorstatus_register;
            }
            else
            {
                int ret = epoll_ctl(f, EPOLL_CTL_ADD, descriptor->handle.f, &event);
                if(ret != xsuccess)
                {
                    int err = errno;
                    if(err == EEXIST)
                    {
                        ret = epoll_ctl(f, EPOLL_CTL_MOD, descriptor->handle.f, &event);
                        if(ret != xsuccess)
                        {
                            xcheck(ret != xsuccess, "fail to epoll_ctl (%d => %s)", errno, xerrorstr(epoll_ctl, errno));
                            return xfail;
                        }
                        descriptor->status |= xdescriptorstatus_register;
                        return xsuccess;
                    }
                    return xfail;
                }
                descriptor->status |= xdescriptorstatus_register;
            }
        }
        else
        {
            descriptor->status &= (~xdescriptorstatus_register);
        }
    }

    return xsuccess;
}

/**
 * @fn      extern xint32 xdescriptorevent_generator_epoll_unregister_descriptor(int f, xdescriptor * descriptor)
 * @brief   [INTERNAL] EPOLL 에서 삭제합니다.
 * @details 이 함수는 언제나 성공을 리턴합니다.
 *          그리고 플래그 값이 REGISTER 상태일 경우만 삭제합니다.
 * 
 * @param   f           | int           | in | EPOLL 파일 디스크립터 |
 * @param   descriptor  | xdescriptor * | in | 디스크립터 객체 |
 * 
 * @return  | xint32 | 등록해제 수행 결과 |
 * 
 *              언제나 성공을 리턴합니다.
 */
extern xint32 xdescriptorevent_generator_epoll_unregister_descriptor(int f, xdescriptor * descriptor)
{
    if(descriptor)
    {
        if(f >= 0)
        {
            if(descriptor->handle.f >= 0)
            {
                if(descriptor->status & xdescriptorstatus_register)
                {
                    int ret = epoll_ctl(f, EPOLL_CTL_DEL, descriptor->handle.f, xnil);
                    if(ret != xsuccess)
                    {
                        xcheck(xtrue, "fail to epoll_ctl (%d => %s)", errno, xerrorstr(epoll_ctl, errno));
                    }
                    descriptor->status &= (~xdescriptorstatus_register);
                }
            }
        }
    }

    return xsuccess;
}