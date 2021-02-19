#include "posix.h"

static void * xthreadposix_routine(void * o);

/**
 * @fn          extern xthreadposix * xthreadposix_rem(xthreadposix * o)
 * @brief       POSIX 스레드 종료 함수입니다.
 * @details     POSIX 스레드를 사용하는 경우 호출되는 함수입니다.
 *              핸들이 존재하면서 cancel 콜백이 존재하면,
 *              이미 종료된 상태에서 cancel 이 호출된 것입니다.
 *              그리고 이와 같은 경우 스레드가 종료된 후에 cancel 이 호출되게 됩니다.
 * 
 * @param       o | xthreadposix * | POSIX 스레드 객체 |
 * @return      | xthreadposix * | 언제나 널을 리턴합니다. |
 * 
 * @exception   | `(ret = pthread_join(xvalueof(o->handle), xnil)) != xsuccess` | 스레드 조인의 결과가 성공이 아니면 예외가 발생합니다. |
 * 
 * @see         xthreadposix,
 *              pthread_join,
 *              xobjectrem,
 *              free
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xthreadposix * xthreadposix_rem(xthreadposix * o)
{
    if(o->handle)
    {
        int ret = pthread_join(xvalueof(o->handle), xnil);

        xassertion(ret != xsuccess, "");

        o->handle = xobjectrem(o->handle);

        if(o->cancel)
        {
            o->cancel(o);
            o->cancel = xnil;
        }
    }
    free(o);
    return xnil;
}

/**
 * @fn          extern void xthreadposix_cancel(xthreadposix * o, xthreadposixfunc cancel)
 * @brief       스레드를 취소합니다.
 * @details     비동기적으로 동작하며, 종료는 스레드 루틴 내부에서 호출되기 때문에,
 *              절대로 pthread_join 혹은 xthreadposix_rem 을 콜백에 담지 않도록 합니다.
 * 
 * @param       o        | xthreadposix *   | 스레드 객체                |
 * @param       callback | xthreadposixfunc | 스레드 종료 시에 호출되는 콜백 |
 * 
 * @exception   | `o->cancel` | 이미 콜백이 등록되어 있으면 예외를 발생 시킵니다. |
 * 
 * @see         xthreadposix,
 *              xthreadposixfunc
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern void xthreadposix_cancel(xthreadposix * o, xthreadposixfunc callback)
{
    xassertion(o->cancel, "");
    if(o->handle)
    {
        o->cancel = callback;
    }
}

/**
 * @fn          extern void xthreadposix_run(xthreadposix * o)
 * @brief       스레드를 실행합니다.
 * @details     스레드의 생성 여부는 handle 값이 메모리 상에서 생성되었느냐
 *              아니냐에 따라서 체크할 수 있습니다.
 * 
 * @param       o | xthreadposix * | POSIX 스레드 객체 |
 * 
 * @see         xthreadposix,
 *              pthread_t,
 *              calloc,
 *              sizeof,
 *              xthreadstatus_on,
 *              pthread_create,
 *              xthreadposix_routine,
 *              xobjectrem
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 * 
 * @exception   | `o->handle` | 스레드 핸들이 존재하면 예외를 발생시킵니다. |
 *              | `(ret = pthread_create(o->handle, xnil, xthreadposix_routine, o)) != xsuccess` | pthread_create 함수의 수행 결과가 성공이 아니면 예외를 발생시킵니다. |
 */
extern void xthreadposix_run(xthreadposix * o)
{
    xassertion(o->handle, "");

    o->handle = calloc(sizeof(pthread_t), 1);
    o->status |= xthreadstatus_on;

    int ret = pthread_create(o->handle, xnil, xthreadposix_routine, o);

    xassertion(ret != xsuccess, "");

    if(ret != xsuccess)
    {
        o->status &= (~xthreadstatus_on);
        o->handle = xobjectrem(o->handle);
    }
}

/**
 * @fn          static void * xthreadposix_routine(void * o)
 * @brief       POSIX 스레드의 루틴입니다.
 * @details     OS 가 POSIX 를 지원할 경우 스레드는 아래의 루틴을 실행시킵니다.
 *              xthread 멤버의 func 을 수행하고, 그 함수가 종료되면
 *              스레드 상태를 종료로 설정하고, 취소 콜백이 등록되어 있으면
 *              취소 콜백을 수행하게 됩니다.
 * 
 * @param       o | void * | 파라미터 - xthreadposix 로 변경이 가능해야 합니다. |
 * @return      | void * | 스레드 함수의 리턴 값으로 언제나 널을 리턴합니다. |
 * 
 * @see         xthreadposix,
 *              xthreadstatus_on
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
static void * xthreadposix_routine(void * o)
{
    xthreadposix * thread = (xthreadposix *) o;

    thread->func(thread);

    thread->status &= (~xthreadstatus_on);

    if(thread->cancel)
    {
        thread->cancel(thread);
        thread->cancel = xnil;
    }

    return xnil;
}
