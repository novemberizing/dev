/**
 * @file        x/descriptor.h
 * @brief       [internal] 디스크립터 객체, 가상 함수를 정의한 파일입니다.
 * 
 * 정리가 필요하다.
 * 
 * 실 사용자는 타입의 존재하는 것만 알고 객체의 멤버는 확인할 수 없다.
 * 
 * 그렇기 때문에 이 파일은 내부에서만 사용되어 진다.
 */
#ifndef   __NOVEMBERIZING_X__DESCRIPTOR__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR__H__

#include <x/io.h>

#include <x/exception.h>

#include <x/descriptor/handle.h>
#include <x/descriptor/event.h>

struct xdescriptoreventsubscription;

typedef struct xdescriptoreventsubscription xdescriptoreventsubscription;

typedef xint64 (*xdescriptorprocessor)(xdescriptor *, xuint32, void *);             /**!< 디스크립터 이벤트 프로세서 */
typedef xint64 (*xdescriptorsubscriber)(xdescriptor *, xuint32, void *, xint64);    /**!< 디스크립터 이벤트 서브스크리라이버 */
typedef xint32 (*xdescriptorcheck)(xdescriptor *, xuint32);                   /**!< 디스크립터 이벤트 체크 함수 타입 */

/**
 * @struct      xdescriptor
 * @brief       이벤트 디스크립터 객체
 * @details
 * 
 * @todo        사용자는 인터페이스 말고는 몰라야 한다.
 */
struct xdescriptor
{
    /** INHERITED EVENT TARGET */
    xdescriptordestructor          rem;            /**!< destructor */
    xdescriptoreventsubscription * subscription;   /**!< subscription */
    xsync *                        sync;           /**!< synchronization */
    xuint32                        mask;           /**!< mask */
    xuint32                        status;         /**!< status */
    /** DESCRIPTOR EVENT HANDLE */
    xdescriptorhandle              handle;         /**!< descriptor handle */
    xdescriptorprocessor           process;        /**!< descriptor process function */
    xdescriptorcheck               check;          /**!< descriptor status checker  */
    xdescriptorsubscriber          on;             /**!< descriptor event subscriber */
    xdescriptorevent               event;          /**!< descriptor default event */
    xexception                     exception;      /**!< descriptor exception */
};

extern xint64 xdescriptorclose(xdescriptor * descriptor);
extern xint64 xdescriptorread(xdescriptor * descriptor, void * buffer, xuint64 size);
extern xint64 xdescriptorwrite(xdescriptor * descriptor, const void * data, xuint64 len);

extern xint32 xdescriptorcheck_rem(xdescriptor * descriptor);
extern xint32 xdescriptorcheck_close(xdescriptor * descriptor);
extern xint32 xdescriptorcheck_open(xdescriptor * descriptor);

extern xint32 xdescriptornonblock_set(xdescriptor * descriptor, xint32 on);

extern xint64 xdescriptorevent_dispatch_on(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_open(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_in(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_out(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_close(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_rem(xdescriptor * descriptor);
extern xint64 xdescriptorevent_dispatch_exception(xdescriptor * descriptor);

extern xint64 xdescriptorevent_processor_on(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_open(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_in(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_out(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_close(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_register(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_unregister(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_rem(xdescriptor * descriptor);
extern xint64 xdescriptorevent_processor_exception(xdescriptor * descriptor);

#endif // __NOVEMBERIZING_X__DESCRIPTOR__H__
