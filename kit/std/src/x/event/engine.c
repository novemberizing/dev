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