#ifndef   __NOVEMBERIZING_X__DESCRIPTOR_SUBSCRIPTIONS__H__
#define   __NOVEMBERIZING_X__DESCRIPTOR_SUBSCRIPTIONS__H__

#include <x/descriptor/subscription.h>

struct xdescriptorsubs;

typedef struct xdescriptorsubs xdescriptorsubs;

/**
 * 이름이 마음에 들지 않는다. 딱히 이만한 이름도 없다.
 * 
 * xdescriptorsubs
 */
struct xdescriptorsubs
{
    xdescriptorsub * head;
    xdescriptorsub * tail;
    xuint64 size;
};

#endif // __NOVEMBERIZING_X__DESCRIPTOR_SUBSCRIPTIONS__H__
