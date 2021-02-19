#include "thread.h"

#include "thread/posix.h"

/**
 * @fn      extern xthread * xthreadnew(xthreadfunc func, xuint64 size)
 * @brief   스레드를 생성합니다.
 * @details 사용자는 자신의 스레드 객체를 생성할 수 있습니다.
 *          xthread 객체와 같이 정의한 후에 자신 만의 데이터를 추가하고 스레드 호출 시에
 *          이를 활용할 수 있으며, 스레드 종료 시에도 자신 만의 스레드 멤버를 처리할 수 있습니다.
 * 
 * @param   func | xthreadfunc | 스레드 함수 |
 * @param   size | xuint64     | 객체의 메모리 크기 |
 * 
 * @return  | xthread * | 스레드 객체 |
 * 
 * @exception   | `func == xnil`           | 스레드 함수는 널이면 안됩니다. |
 *              | `size < sizeof(xthread)` | 스레드 객체의 메모리 중에서 xthread 부분은 내부적으로 사용하는 부분이기 때문에, 전체 스레드 크기는 `sizeof(xthread)` 보다 작으면 안됩니다. |
 * 
 * @see         xthread,
 *              xthreadfunc,
 *              calloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 * 
 * @todo        example
 * 
 * 
 */
extern xthread * xthreadnew(xthreadfunc func, xuint64 size)
{
    xassertion(func == xnil || size < sizeof(xthread), "");

    xthread * o = (xthread *) calloc(size, 1);

    o->func     = func;

    return o;
}

/**
 * @fn          extern xthread * xthreadrem(xthread * o)
 * @brief       스레드 객체를 종료하고 메모리에서 해제합니다.
 * @details     OS 에 따라서 적절한 스레드 함수를 호출합니다.
 * 
 * @param       o | xthread * | 해제하고자 하는 스레드 객체 |
 * 
 * @return      | xthread * | 해제된 스레드 객체로 언제나 널을 리턴합니다. |
 * 
 * @see         xthread,
 *              xthreadposix_rem
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xthread * xthreadrem(xthread * o)
{
    return (xthread *) xthreadposix_rem(o);
}

/**
 * @fn          extern xint32 xthreadremovable(xthread * o)
 * @brief       스레드 함수가 종료 가능한지 체크하는 함수입니다.
 * @details     스레드 함수는 내부적으로 사용하는 함수와 기본적으로 사용되어지는 함수로
 *              나뉘어져 있으며, 내부적으로 사용하는 함수는 스레드 멤버 변수에 사용자 삽입
 *              하게 되어 있습니다. 사용자가 xthreadrun 을 호출할 때,
 *              status 값에 xthreadstatus_on 비트가 활성화되고,
 *              사용자에게 은닉된 스레드 루틴에서 `thread->status &= (~xthreadstatus_on)`
 *              종료 시에 호출하여 다른 스레드에서 스레드의 종료 가능 여부를 체크할 수 있습니다.
 *              조심스럽게 처리해야 할 상황은 실제 종료 가능하다고 하여서 스레드가 종료되지 않았다는
 *              것입니다. 즉, 리턴이 호출되기 전에 종료 가능하다고 판단될 수 있습니다.
 *              그렇기 때문에 실제 종료는 POSIX 의 경우 pthread_join 을 통해야 합니다.
 *              
 * @param       o | xthread * | 스레드 객체 |
 * @return      | xint32 | 스레드 종료 여부 |
 * 
 *                  0(TRUE): 종료 가능
 *                  1(FALSE): 종료 불가능
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 * 
 * @see         xthreadstatus_on,
 *              xthreadstatus_void,
 *              xthread
 */
extern xint32 xthreadremovable(xthread * o)
{
    return (o->status & xthreadstatus_on) == xthreadstatus_void;
}

/**
 * @fn          extern void xthreadcancel(xthread * o, xthreadfunc callback)
 * @brief       스레드를 종료하도록 종료 시에 호출되는 콜백을 등록합니다.
 * @details     스레드 종료는 비동기적으로 호출됩니다.
 *              종료 콜백이 존재해야만 종료를 수행하게 됩니다.
 *              만약에, 종료 후 그리고 스레드가 메모리 상에서 존재할 경우는
 *              xthreadrem 호출 시에 콜백이 호출되게 됩니다.
 * 
 * @param       o        | xthread *   | 스레드 객체 |
 * @param       callback | xthreadfunc | 스레드 종료 시에 호출되는 콜백 |
 * 
 * @see         xthread,
 *              xthreadfunc,
 *              xthreadposix,
 *              xthreadposixfunc,
 *              xthreadposix_cancel
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 *              
 */
extern void xthreadcancel(xthread * o, xthreadfunc callback)
{
    xthreadposix_cancel((xthreadposix *) o, (xthreadposixfunc) callback);
}

/**
 * @fn          extern void xthreadrun(xthread * o)
 * @brief       스레드를 실행합니다.
 * @details     OS 에 따라서 적절한 스레드 실행 함수를 호출합니다.
 * 
 * @param       o | xthread * | 스레드 객체 |
 * 
 * @see         xthread,
 *              xthreadposix,
 *              xthreadposix_run
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern void xthreadrun(xthread * o)
{
    xthreadposix_run((xthreadposix *) o);
}