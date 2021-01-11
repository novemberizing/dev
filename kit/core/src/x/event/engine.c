/**
 * @file    x/event/engine.c
 * @brief
 * @details
 * 
 * @version 0.0.1
 * @since   2021. 01. 11.
 */

#include "../event.h"

/**
 * @fn      void xengine_event_dispatch(xengine * o, xevent * event)
 * @brief   이벤트를 배치합니다.
 * @details
 * 
 * @param   | o     | in | xengine * | 엔진 객체 |
 * @param   | event | in | xevent *  | 이벤트 객체 |
 * 
 */
void xengine_event_dispatch(xengine * o, xevent * event)
{
    xassertion(o == xnil || event  == xnil, "null pointer");

    xeventqueue * queue = &(o->events);

    xsynclock(queue->sync);
    xqueuepush(queue, event);
    xsyncwakeup(queue->sync, xfalse);
    xsyncunlock(queue->sync);
}

/**
 * @fn      xevent * xengine_event_emit(xengine * o)
 * @brief   이벤트 큐에서 이벤트를 방출합니다.
 * @details
 * 
 * @param   | o | in | xengine * | 이벤트 엔진 |
 * 
 * @return  | xevent * | 이벤트 객체 |
 * 
 *              이벤트가 존재하지 않으면 널을 배출합니다.
 * 
 */
xevent * xengine_event_emit(xengine * o)
{
    xassertion(o == xnil, "null pointer");

    xeventqueue * queue = &(o->events);

    return xqueuepop(queue);
}

/**
 * @fn      void xengine_event_process(xengine * o)
 * @brief   엔진의 메인 루프에서 실행되는 이벤트 프로세스 함수입니다.
 * @details
 * 
 * @param   | o | in | xengine * | 이벤트 엔진 |
 */
void xengine_event_process(xengine * o)
{
    xassertion(o == xnil, "null pointer");

    xeventqueue * queue = &(o->events);
    xuint64 size = xqueuesize(queue);
    
    xsynclock(queue->sync);
    for(xuint64 i = 0; i < size; i++) {
        xevent * event = xqueuepop(queue);
        if(event) {
            xsyncunlock(queue->sync);
            /**
             * IMPLEMENT THIS
             */
            xsynclock(queue->sync);
            continue;
        }
        break;
    }
    xsyncunlock(queue->sync);
}

int xenginerun(xengine * o)
{
    xassertion(o == xnil, "null pointer");
    xassertion(o->status != xengine_status_void, "engine is already running");

    o->status |= xengine_status_on;

    while((o->status & xengine_status_cancel) == xfalse)
    {
        for(xgenerator * generator = xlisthead(&o->generators); generator != xnil; generator = xlistnext(generator))
        {
            xgeneratorrun(generator, o);
        }
        xengine_event_process(o);
    }

    o->status &= (~xengine_status_on);

    return xsuccess;
}

int main(int argc, char ** argv)
{
    xengine engine = xengineinit();

    xengine_plug_generator(xgenerator_io_new());
    xengine_plug_generator(xgenerator_time_new());
    xengine_plug_generator(xgenetator_signal_new());

    return xenginerun(&engine);
}