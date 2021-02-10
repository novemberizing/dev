/**
 * @file    x/event.h
 * @brief   [internal]
 */
#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xeventlist;
struct xeventqueue;
struct xeventqueue_node;
struct xeventengine;
struct xeventengine_node;
struct xeventobject;
struct xeventgenerator;
struct xeventgenerator_node;

typedef struct xevent xevent;
typedef struct xeventlist xeventlist;
typedef struct xeventqueue xeventqueue;
typedef struct xeventqueue_node xeventqueue_node;
typedef struct xeventengine xeventengine;
typedef struct xeventengine_node xeventengine_node;
typedef struct xeventobject xeventobject;
typedef struct xeventgenerator xeventgenerator;
typedef struct xeventgenerator_node xeventgenerator_node;

typedef void (*xeventhandler)(xevent *);

struct xeventqueue_node
{
    xevent *      prev;
    xevent *      next;
    xeventqueue * cntr;
};

struct xevent
{
    xeventqueue_node eventnode;
    xeventhandler    on;
};

struct xeventlist
{
    xevent * head;
    xevent * tail;
    xuint64  size;
};

struct xeventengine_node
{
    xeventobject * prev;
    xeventobject * next;
    xeventengine * cntr;
};

struct xeventgenerator_node
{
    xeventobject *         prev;
    xeventobject *         next;
    xeventgenerator *      cntr;

    xeventgenerator_node * tail;
};

#define xeventon(event) do { event->on(event); } while(0)

#endif // __NOVEMBERIZING_X__EVENT__H__
