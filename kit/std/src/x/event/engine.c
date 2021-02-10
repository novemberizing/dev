#include "engine.h"

extern void xeventengine_register_object(xeventengine * engine, xeventobject * object)
{
    xassertion(engine == xnil || object == xnil, "");   // 파라미터가 널입니다.
    xassertion(object->enginenode.cntr, "");            // 이미 등록된 이벤트 객체입니다.

    object->enginenode.cntr = engine;

    object->enginenode.prev = engine->tail;
    if(object->enginenode.prev)
    {
        object->enginenode.prev->enginenode.next = object;
    }
    else
    {
        engine->head = object;
    }
    engine->size = engine->size + 1;

    if(xeventobject_interest_has(xeventcategory_type_descriptor))
    {
        /**
         * 디스크립터 이벤트 제네레이터는 오픈된 상태의 디스크립터면 제네레이터에
         * 등록이 되는데, 그렇지 않은 경우 오픈 상태 혹은 종료 상태를 수행해야 한다.
         * 그렇게 하고 나서 오픈되면 다시 등록하는 절차를 밟아야 한다. 이렇게 로직을
         * 짜야 오픈된 디스크립터만 관리가 가능하다. 오픈 되지 않은 디스크립터는
         * 어디서 관리되어지는가? 그 디스크립터는 엔진에서 관리되고,
         * 이벤트 큐에서 관리되어진다.
         */
        xassertion(xtrue, "implement specified event generator register");
        xeventgenerator_register_object(engine->descriptorgen, object);
    }
    if(xeventobject_interest_has(xeventcategory_type_time))
    {
        xassertion(xtrue, "implement specified event generator register");
        xeventgenerator_register_object(engine->timegen, object);
    }
    if(xeventobject_interest_has(xeventcategory_type_signal))
    {
        xassertion(xtrue, "implement specified event generator register");
        xeventgenerator_register_object(engine->signalgen, object);
    }
}

extern void xeventengine_unregister_object(xeventengine * engine, xeventobject * object)
{

}