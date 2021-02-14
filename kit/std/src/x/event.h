#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xeventqueue;
struct xeventengine;
struct xeventgenerator;
struct xeventprocessor;
struct xeventobject;
struct xeventsubscription;

struct xsubscription;
struct xsubscriptions;

typedef struct xevent xevent;
typedef struct xeventqueue xeventqueue;
typedef struct xeventengine xeventengine;
typedef struct xeventgenerator xeventgenerator;
typedef struct xeventprocessor xeventprocessor;
typedef struct xeventobject xeventobject;
typedef struct xeventsubscription xeventsubscription;

typedef struct xsubscription xsubscription;
typedef struct xsubscriptions xsubscriptions;

typedef void (*xeventhandler)(xevent *);
// EVENT HANDLER

struct xevent
{
    xevent *      prev;
    xevent *      next;
    xeventqueue * cntr;
    xeventhandler on;
};

struct xeventqueue
{
    xevent * head;
    xevent * tail;
    xuint64  size;
    xsync *  sync;
};

struct xeventobject
{
};

#endif // __NOVEMBERIZING_X__EVENT__H__
