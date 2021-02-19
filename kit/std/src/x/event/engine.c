#include "engine.h"

/**
 * @fn          extern void xeventengine_processor_wakeup(xeventengine * engine, xint32 all)
 * @brief       이벤트 프로세서를 깨웁니다.
 * @details     이벤트 프로세서가 처리할 이벤트가 존재하지 않아서,
 *              대기 상태에 있으면 프로세스를 깨웁니다.
 *              이벤트 프로세서는 이벤트 큐의 CONDITIONAL 객체를 참조하고 있기 때문에
 *              이벤트 동기화 객체에 시그널을 보내게 됩니다.
 * 
 * @param       engine | xeventengine * | 이벤트 엔진 |
 * @param       all    | xint32         | 모든 객체에 보내기 위한 파라미터 |
 * 
 *                  1(TRUE): 전체 프로세서에 시그널 전송
 *                  0(FALSE): 단일 프로세서에 시그널 전송
 * 
 * @see         xeventengine,
 *              xsynclock,
 *              xsyncwakeup,
 *              xsyncunlock
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 * @exception   | `engine == xnil` | 이벤트 엔진이 널이면 예외를 발생시킵니다. |
 * 
 * @todo        이벤트 프로세서를 깨우는 것은 맞지만, ... 뭔가 이름이 마음에 들지 않는다.
 *              실제 하는 역할은 이벤트 큐의 WAKEUP 을 수행하는 것이다.
 */
extern void xeventengine_processor_wakeup(xeventengine * engine, xint32 all)
{
    xassertion(engine == xnil, "");

    xsynclock(engine->queue.sync);
    xsyncwakeup(engine->queue.sync, all);
    xsyncunlock(engine->queue.sync);
}