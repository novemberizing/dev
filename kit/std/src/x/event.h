#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xeventtarget;
struct xeventsubscription;
struct xeventprocessor;
struct xeventprocessorpool;
struct xeventengine;
struct xeventqueue;

typedef struct xevent xevent;
typedef struct xeventtarget xeventtarget;
typedef struct xeventsubscription xeventsubscription;
typedef struct xeventprocessor xeventprocessor;
typedef struct xeventprocessorpool xeventprocessorpool;
typedef struct xeventengine xeventengine;
typedef struct xeventqueue xeventqueue;

typedef xeventtarget * (*xeventtargetdestructor)(xeventtarget *);
typedef void (*xeventhandler)(xevent *);

struct xevent
{
    xevent *      prev;
    xevent *      next;
    xeventqueue * queue;
    xeventhandler on;
};

// 이벤트가 생성되면, 이벤트 큐에 삽입하고, 이벤트 타겟에 등록한다.

#endif // __NOVEMBERIZING_X__EVENT__H__
