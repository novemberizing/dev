#include <stdio.h>
#include <stdlib.h>

#include "sync.h"
#include "sync/posix/mutex.h"

#include "thread.h"

/**
 * @fn          extern xsync * xsyncnew(xuint32 type)
 * @brief       타입과 알맞는 동기화 객체를 생성합니다.
 * @details     현재는 POSIX 뮤텍스 동기화 객체만을 생성하며,
 *              다른 타입이 파라미터로 주어지면 예외를 발생시킵니다.
 * 
 * @param       type    | xuint32 | in | 생성하고자 하는 동기화 객체 타입 |
 * 
 * @return      | xsync * | 동기화 객체 |
 * 
 * @see         xsync
 *              xsyncposixmutex_new
 *              xsynctype_mutex
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xsync * xsyncnew(xuint32 type)
{
    switch(type)
    {
        case xsynctype_mutex:   return (xsync *) xsyncposixmutex_new();
    }

    xassertion(xtrue, "");
}

/**
 * @fn          extern xsync * xsyncrem(xsync * o)
 * @brief       동기화 객체를 메모리 상에서 해제합니다.
 * @details     등록된 소멸자를 호출합니다.
 * 
 * @param       o   | xsync * | in | 동기화 객체 |
 * 
 * @return      | xsync * | 항상 널을 리턴합니다. |
 * 
 * @see         xsync
 *              xsyncdestructor
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xsync * xsyncrem(xsync * o)
{
    return o->rem(o);
}

/**
 * @fn          extern xsync * xsynccondinit(xsync * o)
 * @brief       동기화 객체의 컨디션을 활성화 시킵니다.
 * @details     동기화 객체의 타임은 소멸자를 통해서 체크합니다.
 * 
 * @param       o | xsync * | 동기화 객체 |
 * 
 * @return      | xsync | 파라미터로 주어진 동기화 객체를 리턴합니다. |
 * 
 * @see         xsync
 *              xsyncdestructor
 *              xsyncposixcond_init
 *              xsyncposixmutex
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xsync * xsynccondinit(xsync * o)
{
    if(o->rem == (xsyncdestructor) xsyncposixmutex_rem)
    {
        return (xsync *) xsyncposixcond_init((xsyncposixmutex *) o);
    }
    xassertion(xtrue, "");
}

/**
 * @fn          extern xsync * xsynccondterm(xsync * o)
 * @brief       동기화 객체의 컨디션을 비활성화 시킵니다.
 * @details     동기화 객체의 타입에 따라서 내부에서 사용하는 함수를 호출합니다.
 *              동기화 객체의 타입은 소멸자의 주소를 통해서 체크합니다.
 * 
 * @param       o | xsync * | in | 동기화 객체 |
 * 
 * @return      | xsync * | 동기화 객체 |
 * 
 * @see         xsync
 *              xsyncdestructor
 *              xsyncposixmutex_rem
 *              xsyncposixcond_term
 *              xsyncposixmutex
 * 
 * @version     0.0.1
 * @date        2021. 02. 24.
 */
extern xsync * xsynccondterm(xsync * o)
{
    if(o->rem == (xsyncdestructor) xsyncposixmutex_rem)
    {
        return (xsync *) xsyncposixcond_term((xsyncposixmutex *) o);
    }
    xassertion(xtrue, "");
}
