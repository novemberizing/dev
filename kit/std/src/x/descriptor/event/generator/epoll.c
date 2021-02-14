#include "epoll.h"

#include "../../subscription.h"

extern xdescriptorsub * xdescriptoreventgen_register(xdescriptoreventgen * o, xdescriptor * descriptor)
{
    xassertion(o == xnil || descriptor == xnil, "");

    xdescriptoreventgen_epoll * generator = (xdescriptoreventgen_epoll *) o;

    // 오픈 상태를 체크하고 오픈 상태가 아니면 오픈을 수행한다.

    /**
     */




    xdescriptorsub * subscription = calloc(sizeof(xdescriptorsub), 1);

    subscription->generatornode.prev = generator->tail;
    if(subscription->generatornode.prev)
    {
        subscription->generatornode.prev->generatornode.next = subscription;
    }
    else
    {
        generator->head = subscription;
    }
    generator->tail = subscription;
    generator->size = generator->size + 1;

    descriptor->subscription = subscription;


    return subscription;
}