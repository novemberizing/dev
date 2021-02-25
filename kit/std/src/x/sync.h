/**
 * @file        x/sync.h
 * @brief       동기화 객체의 타입, 메서드, 구조체를 정의한 헤더 파일입니다.
 * @details
 * 
 * @version     0.0.1
 * @date        2021. 02. 25.
 */
#ifndef   __NOVEMBERIZING_X__SYNC__H__
#define   __NOVEMBERIZING_X__SYNC__H__

#include <x/std.h>

#define xsynctype_mutex         (0)                 /**!< 뮤텍스 동기화 객체 타입 */
#define xsynctype_spinlock      (1)                 /**!< 스핀락 동기화 객체 타입  */

#define xsynctype_default       xsynctype_mutex     /**!< 기본 동기화 객체 타입: 뮤텍스 동기화 객체 타입 */

struct xsync;                                       /**!< 동기화 구조체 */

typedef struct xsync xsync;                         /**!< 동기화 객체 타입 */

typedef xsync * (*xsyncdestructor)(xsync *);        /**!< 동기화 객체의 소멸자로 동기화 객체의 타입을 의미합니다. */

/**
 * @struct      xsync
 * @brief       동기화 객체의 인터페이스 입니다.
 * 
 */
struct xsync
{
    xsyncdestructor rem;                            /**!< 소멸자입니다. 소멸자를 통해서 타입을 유추할 수 있습니다. */
    xint32  (*lock)(xsync *);                       /**!< 스레드 락을 수행합니다. */
    xint32  (*unlock)(xsync *);                     /**!< 스레드 언락을 수행합니다. */
    xint32  (*wait)(xsync *, xint64, xint64);       /**!< 수행을 주어진 시간에 맞추서 잠시 멈춥니다. */
    xint32  (*wakeup)(xsync *, xint32);             /**!< 멈춘 스레드가 존재하면 전체 혹은 하나를 깨우는 신호를 보냅니다. */
};

/**
 * @def         xsynclock(o)
 * @brief       동기화 객체의 락을 수행합니다.
 *              만약에 동기화 객체가 널이면 성공을 리턴합니다.
 * 
 * @param       o | xsync * | in | 동기화 객체 |
 * 
 * @return      | xint32 | 동기화 객체 락의 수행 성공 여부 |
 * 
 *                  0(SUCCESS): 성공
 *                  -1(FAIL): 실패
 */
#define xsynclock(o)                        (o ? o->lock(o) : xsuccess)

/**
 * @def         xsyncunlock(o)
 * @brief       동기화 객체의 언락을 수행합니다.
 *              만약에 동기화 객체가 널이면 성공을 리턴합니다.
 * 
 * @param       o | xsync * | in | 동기화 객체 |
 * 
 * @return      | xint32 | 동기화 객체 락의 수행 성공 여부 |
 * 
 *                  0(SUCCESS): 성공
 *                  -1(FAIL): 실패
 */
#define xsyncunlock(o)                      (o ? o->unlock(o) : xsuccess)

/**
 * @fn          xsyncwait(o, second, nanosecond)
 * @brief       동기화 객체를 통하여 스레드의 수행을 잠시 멈춥니다.
 * @details     
 * 
 *                  시그널을 수신할 때까지 무한히 멈추고자 한다면 second, nanosecond 에
 *                  0 을 삽입해야 합니다.
 * 
 * @param       o | xsync * | in | 동기화 객체 |
 * @param       second | xint64 | in | 멈추고자하는 초 단위 시간 |
 * @param       nanosecond | xint64 | in | 멈추고자하는 나노 세컨드 단위 시간 |
 * 
 * @return      | xint32 | 동기화 객체를 톻아여 스레드의 수행을 멈추는 루틴의 수행 성공 여부 |
 * 
 * 
 * 
 */
#define xsyncwait(o, second, nanosecond)    (o ? o->wait(o, second, nanosecond) : xsuccess)

/**
 * @fn          xsyncwakeup(o, all)
 * @brief       멈춘 동기화 객체에 시그널을 전송하여 동작을 재개하도록 합니다.
 * @details 
 * 
 * @param       o | xsync * | in | 동기화 객체 |
 * @param       all | xint32 | in | FALSE 이면 하나의 멈춘 스레드에만 시그널을 전송하고, 그렇지 않으면 전체 멈춘 스레드에 시그널을 전송합니다. |
 * 
 * @return      | xint32 | 시그널 전송 성공 여부 |
 * 
 * 
 *                  0(SUCCESS): 전송 성공
 *                  -1(FAIL): 전송 실패
 * 
 */
#define xsyncwakeup(o, all)                 (o ? o->wakeup(o, all) : xsuccess)

extern xsync * xsyncnew(xuint32 type);
extern xsync * xsyncrem(xsync * o);
extern xsync * xsynccondinit(xsync * o);
extern xsync * xsynccondterm(xsync * o);

#endif // __NOVEMBERIZING_X__SYNC__H__
