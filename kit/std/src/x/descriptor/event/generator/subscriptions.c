#include "subscriptions.h"

#include "../subscription.h"

/**
 * @fn          extern xdescriptoreventgeneratorsubscriptions * xdescriptoreventgeneratorsubscriptions_new(void)
 * @brief       디스크립터 이벤트 제네레이터의 서브스크립션 리스트를 생성합니다.
 * @details     스레드를 위한 동기화 객체는 스레드를 사용할 때 사용해야 합니다.
 * 
 * @return      | xdescriptoreventgeneratorsubscriptions * | 디스크립터 이벤트 제네레이터 서브스크립션 리스트 |
 * 
 * @see         xdescriptoreventgeneratorsubscriptions,
 *              calloc
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 */
extern xdescriptoreventgeneratorsubscriptions * xdescriptoreventgeneratorsubscriptions_new(void)
{
    xdescriptoreventgeneratorsubscriptions * subscriptions = calloc(sizeof(xdescriptoreventgeneratorsubscriptions), 1);

    return subscriptions;
}

/**
 * @fn          extern xdescriptoreventgeneratorsubscriptions * xdescriptoreventgeneratorsubscriptions_rem(xdescriptoreventgeneratorsubscriptions * subscriptions)
 * @brief       디스크립터 이벤트 제네레이터 서브스크립션 리스트를 메모리 상에서 해제합니다.
 * @details     이 함수는 모든 서브스크립션을 삭제하고 호출해야 합니다.
 * 
 * @param       subscriptions | xdescriptoreventgeneratorsubscriptions * | in | 디스크립터 이벤트 제네레이터 서브스크립션 리스트 |
 * @return      | xdescriptoreventgeneratorsubscriptions * | 디스크립터 이벤트 제네레이터 서브스크립션 리스트로 항상 널을 리턴합니다. |
 * 
 * @see         xdescriptoreventgeneratorsubscriptions,
 *              xsyncrem,
 *              free
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 */
extern xdescriptoreventgeneratorsubscriptions * xdescriptoreventgeneratorsubscriptions_rem(xdescriptoreventgeneratorsubscriptions * subscriptions)
{
    if(subscriptions)
    {
        xassertion(subscriptions->size > 0, "");

        subscriptions->sync = xsyncrem(subscriptions->sync);

        free(subscriptions);
    }

    return subscriptions;
}

/**
 * @fn          extern void xdescriptoreventgeneratorsubscriptions_push(xdescriptoreventgeneratorsubscriptions * subscriptions, xdescriptoreventsubscription * subscription)
 * @brief       디스크립터 이벤트 제네레이터 서브스크립션 리스트에 서브스크립션을 등록합니다.
 * @details     파라미터가 널이거나 서브스크립션 객체에 제네레이터 노드 상태가 초기 상태가 아니면
 *              즉, subscription->generatornode.subscriptions,
 *              subscription->generatornode.prev, subscription->generatornode.next
 *              에 데이터가 존재하면 예외를 발생시킵니다.
 * 
 * @param       subscriptions | xdescriptoreventgeneratorsubscriptions * | in | 디스크립터 이벤트 제네레이터 서브스크립션 리스트 객체 |
 * @param       subscription  | xdescriptoreventsubscription *           | in | 디스크립터 이벤트 서브스크립션 |
 * 
 * @see         xdescriptoreventgeneratorsubscriptions,
 *              xdescriptoreventsubscription,
 *              xsynclock,
 *              xsyncunlock
 * 
 * @version     0.0.1
 * @date        2021. 02. 19.
 * 
 */
extern void xdescriptoreventgeneratorsubscriptions_push(xdescriptoreventgeneratorsubscriptions * subscriptions, xdescriptoreventsubscription * subscription)
{
    xassertion(subscriptions == xnil || subscription == xnil, "");

    xassertion(subscription->generatornode.subscriptions ||
               subscription->generatornode.prev ||
               subscription->generatornode.next, "");

    xsynclock(subscriptions->sync);

    subscription->generatornode.subscriptions = subscriptions;

    subscription->generatornode.prev = subscriptions->tail;
    if(subscription->generatornode.prev)
    {
        subscription->generatornode.prev->generatornode.next = subscription;
    }
    else
    {
        subscriptions->head = subscription;
    }
    subscriptions->size = subscriptions->size + 1;

    xsyncunlock(subscriptions->sync);
}

/**
 * @fn          extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptions_del(xdescriptoreventgeneratorsubscriptions * subscriptions, xdescriptoreventsubscription * subscription)
 * @brief       디스크립터 이벤트 서브스크립션을 제거합니다.
 * @details     서브스크립션에 저장된 리스트와 파라미터가 같지 않으면 예외를 발생시킵니다.
 *              내부적으로 서브스크립션에 LOCK/UNLOCK 을 통해서 스레드 세이프를 보장합니다.
 *              멀티 스레드 환경에서 LOCK/UNLOCK 을 수행하도록 하려면 서브스크립션 리스트에
 *              SYNC 멤버에 동적으로 객체를 할당해야 합니다.
 *              리스트에서 삭제하는 것이지 메모리 상에서는 지워지지 않습니디.
 * 
 * @param       subscriptions | xdescriptoreventgeneratorsubscriptions * | in | 디스크립터 이벤트 제네레이터 서브스크립션 리스트 |
 * @param       subscription  | xdescriptoreventsubscription *           | in | 디스크립터 이벤트 서브스크립션 |
 * 
 * @return      | xdescriptoreventsubscription * | 서브스크립션 |
 * 
 * @exception   | `subscriptions == xnil` |
 *              | `subscription == xnil` |
 *              | `subscriptions != subscription->generatornode.subscriptions` |
 * 
 * @see         xdescriptoreventsubscription
 *              xdescriptoreventgeneratorsubscriptions
 *              xsynclock,
 *              xsyncunlock
 *              
 */
extern xdescriptoreventsubscription * xdescriptoreventgeneratorsubscriptions_del(xdescriptoreventgeneratorsubscriptions * subscriptions, xdescriptoreventsubscription * subscription)
{
    xassertion(subscriptions == xnil || subscription == xnil, "");

    xassertion(subscriptions != subscription->generatornode.subscriptions, "");

    xsynclock(subscriptions->sync);

    xdescriptoreventsubscription * prev = subscription->generatornode.prev;
    xdescriptoreventsubscription * next = subscription->generatornode.next;

    if(prev)
    {
        prev->generatornode.next = next;
    }
    else
    {
        subscriptions->head = next;
    }

    if(next)
    {
        next->generatornode.prev = prev;
    }
    else
    {
        subscriptions->tail = prev;
    }
    subscriptions->size = subscriptions->size - 1;

    subscription->generatornode.prev          = xnil;
    subscription->generatornode.next          = xnil;
    subscription->generatornode.subscriptions = xnil;

    xsyncunlock(subscriptions->sync);

    return subscription;
}