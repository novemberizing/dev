/**
 * 
 * xeventengine * engine = xeventengine_new();
 * 
 * ```
 * xeventengine * engine = xeventengine_new();
 * ...
 * return xeventengine_run(engine);
 * ```
 * 
 * 
 * 이벤트 엔진의 상태는 어떤 변수로 설정할 수 있는가 ?
 */
#ifndef   __NOVEMBERIZING_X__EVENT__ENGINE__H__
#define   __NOVEMBERIZING_X__EVENT__ENGINE__H__

#include <x/event.h>
#include <x/event/queue.h>

#include <x/descriptor.h>
#include <x/console.h>

#include <x/descriptor/event/generator.h>

#define xeventenginestatus_off      1

typedef void (*xeventenginecb)(xeventengine *, xuint32);
typedef void (*xeventenginefunc)(xeventengine *);       /**!< 이벤트 엔진의 기본 가상 함수입니다. */

/**
 * 사용자는 이벤트 엔진 객체의 내부를 알아야 할 필요가 없습니다.
 * 사용자는 인터페이스만 알고 내부 멤버는 PRIVATE 으로 사용자가 알아야 하지 않습니다.
 * 다만, 스택에 구조체를 생성할 경우는 ... 
 */
struct xeventengine
{
    xeventenginecb                                     on;
    xeventenginefunc                                   cancel;
    xeventqueue *                                      queue;
    xeventqueue *                                      main;
    xsync *                                            sync;
    struct { xeventsubscription * head;
             xeventsubscription * tail;
             xsync * sync;
             xuint64 size;                           } subscriptions;
    struct { xdescriptoreventgenerator * descriptor; } generators;
    xeventprocessorpool *                              processors;
};

extern xeventengine * xeventengine_new(void);
extern xint32 xeventengine_run(xeventengine * engine);
extern void xeventengine_cancel(xeventengine * engine, xeventenginefunc callback);

extern void xeventengine_sync(xeventengine * engine, xint32 on);

extern xuint64 xeventengine_processor_pool_size(xeventengine * engine);

extern void xeventengine_generators_on(xeventengine * engine);
extern void xeventengine_processors_on(xeventengine * engine);
extern void xeventengine_main_consume(xeventengine * engine);
extern void xeventengine_queue_consume(xeventengine * engine);
extern void xeventengine_main_clear(xeventengine * engine);
extern void xeventengine_queue_clear(xeventengine * engine);
extern void xeventengine_generators_once(xeventengine * engine);
extern void xeventengine_main_process(xeventengine * engine);
extern void xeventengine_generators_off(xeventengine * engine);

extern xint32 xengineengine_descriptor_dispatch(xdescriptor * descriptor);

extern xeventsubscription * xeventengine_descriptor_register(xeventengine * engine, xdescriptor * descriptor);
extern xeventsubscription * xeventengine_descriptor_unregister(xeventengine * engine, xdescriptor * descriptor);

extern xeventsubscription * xeventengine_console_descriptor_register(xeventengine * engine, xconsoledescriptor * descriptor);
extern xeventsubscription * xeventengine_console_descriptor_unregister(xeventengine * engine, xconsoledescriptor * descriptor);

extern void xeventengine_main_push(xeventengine * engine, xevent * event);
extern xevent * xeventengine_main_pop(xeventengine * engine);

extern void xeventengine_queue_push(xeventengine * engine, xevent * event);
extern xevent * xeventengine_queue_pop(xeventengine * engine);



#endif // __NOVEMBERIZING_X__EVENT__ENGINE__H__
