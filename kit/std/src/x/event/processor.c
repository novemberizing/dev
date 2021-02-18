#include "processor.h"
#include "processor/pool.h"
#include "engine.h"

static void xeventprocessor_loop(xeventprocessor * processor);
static void xeventprocessor_dispatch_exit(xeventprocessor * processor);

/**
 * @fn      extern xeventprocessor * xeventprocessor_new(xeventprocessorpool * pool)
 * @brief   이벤트 프로세서를 생성합니다.
 * @details 이벤트는 생성과 동시에 풀에 등록되며,
 *          자동으로 실행됩니다.
 * 
 * @param   pool | xeventprocessorpool * | in | 이벤트 프로세서 풀 |
 * 
 * @return  | xeventprocessor * | 이벤트 프로세서 객체 |
 * 
 * @exception   `pool == xnil`
 * 
 * @see         xeventprocessorpool,
 *              xeventprocessor,
 *              xthread,
 *              xeventprocessor_loop,
 *              xthreadrun,
 *              calloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xeventprocessor * xeventprocessor_new(xeventprocessorpool * pool)
{
    xassertion(pool == xnil, "");

    xeventprocessor * processor = (xeventprocessor *) calloc(sizeof(xeventprocessor), 1);

    processor->func             = xeventprocessor_loop;
    processor->pool             = pool;

    processor->prev             = pool->tail;
    if(processor->prev)
    {
        processor->prev->next   = processor;
    }
    else
    {
        pool->head              = processor;
    }
    pool->size                  = pool->size + 1;

    xthreadrun((xthread *) processor);

    return processor;
}

/**
 * @fn          extern xeventprocessor * xeventprocessor_rem(xeventprocessor * processor)
 * @brief       이벤트 프로세서를 메모리 상에서 제거합니다.
 * @details     이벤트 포로세서를 메모리 상에서 제거 하기 전에, 이벤트 포로세서가 속해 있는 풀에서 제거하고, 스레드를 종료합니다.
 *              이벤트 프로세서는 이미 종료되어서, 제거 가능한 상태여야 합니다.
 * 
 * @param       processor | xeventprocessor * | in | 이벤트 프로세서 객체 |
 * @return      | xeventprocessor * | 항상 널을 리턴합니다. |
 * 
 * @exception   `xthreadcheck_removable(processor) == xfalse`
 *              `processor == xnil`
 * 
 * @see         xthreadcheck_removable,
 *              xthreadrem,
 *              xeventprocessorpool,
 *              xeventprocessor,
 *              xthread
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xeventprocessor * xeventprocessor_rem(xeventprocessor * processor)
{
    xassertion(processor == xnil, "");
    xassertion(xthreadcheck_removable((xthread *) processor) == xfalse, "");

    xeventprocessorpool * pool = processor->pool;

    if(pool)
    {
        xeventprocessor * prev = processor->prev;
        xeventprocessor * next = processor->next;

        if(prev)
        {
            prev->next = next;
        }
        else
        {
            pool->head = next;
        }

        if(next)
        {
            next->prev = prev;
        }
        else
        {
            pool->tail = prev;
        }

        pool->size = pool->size - 1;
    }

    return xthreadrem((xthread *) processor);
}

/**
 * @fn          extern void xeventprocessor_cancel(xeventprocessor * processor)
 * @brief       이벤트 프로세서를 종료합니다.
 * @details     이벤트 프로세서의 종료는 이벤트 엔진의 메인 프로세서에서 동작합니다.
 *              즉, 이 함수를 호출한다고 하여도 이벤트 프로세서가 바로 종료되지 않습니다.
 *              이 함수는 호출하면 `cancel` 함수가 등록되는 것으로 끝나게 됩니다.
 * 
 * @param       processor | xeventprocessor * | in | 이벤트 프로세서 |
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 * 
 * @see         xeventprocessor,
 *              xeventprocessor_dispatch_exit
 */
extern void xeventprocessor_cancel(xeventprocessor * processor)
{
    if(processor->handle)
    {
        processor->cancel = xeventprocessor_dispatch_exit;
    }
}

static void xeventprocessor_loop(xeventprocessor * processor)
{
    xeventprocessorpool * pool = processor->pool;
    xeventengine *      engine = pool->engine;
    xeventqueue *        queue = xaddressof(engine->queue);
    
    while(processor->cancel == xnil)
    {
        xsynclock(queue->sync);
        if(queue->size == 0)
        {
            xsyncwait(queue->sync, 0, 0);
            if(processor->cancel)
            {
                xsyncunlock(queue->sync);
                break;
            }
        }
        xevent * event = xeventqueue_pop(queue);
        xsyncunlock(queue->sync);
        if(event)
        {
            event->on(event);
        }
    }
}

static void xeventprocessor_dispatch_exit(xeventprocessor * processor)
{
    // xeventprocessor_exit_event;
    // ENGINE 의 큐에 스레드 종료를 호출하도록 합니다.
}