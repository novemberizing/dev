/**
 * @file    x/event.h
 * @brief   [internal]
 */
#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

#define xeventcategory_type_mask            (0x0000000Fu)
#define xeventcategory_type_descriptor      (0x00000001u)
#define xeventcategory_type_time            (0x00000002u)
#define xeventcategory_type_signal          (0x00000004u)
#define xeventcategory_type_custom          (0x00000008u)

#define xeventobject_status_void            (0x00000000u)
#define xeventobject_status_exception       (0x00000001u)

struct xevent;
struct xeventlist;
struct xeventqueue;
struct xeventqueue_node;
struct xeventengine;
struct xeventengine_node;
struct xeventobject;
struct xeventgenerator;
struct xeventgenerator_node;
struct xeventgeneratorlist;

typedef struct xevent xevent;
typedef struct xeventlist xeventlist;
typedef struct xeventqueue xeventqueue;
typedef struct xeventqueue_node xeventqueue_node;
typedef struct xeventengine xeventengine;
typedef struct xeventengine_node xeventengine_node;
typedef struct xeventobject xeventobject;
typedef struct xeventgenerator xeventgenerator;
typedef struct xeventgenerator_node xeventgenerator_node;
typedef struct xeventgeneratorlist xeventgeneratorlist;

typedef void (*xeventhandler)(xevent *);

struct xeventqueue_node
{
    xevent *      prev;
    xevent *      next;
    xeventqueue * cntr;
};

struct xeventgenerator
{
    xeventgenerator_node * head;
    xeventgenerator_node * tail;
    xuint64 size;
    xsync * sync;
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
    struct
    {
        xeventgenerator_node * prev;
        xeventgenerator_node * next;
        xeventgenerator *      cntr;
    } objectnode;
    struct
    {
        xeventgenerator_node * prev;
        xeventgenerator_node * next;
        xeventobject *         cntr;
    } generatornode;
};

struct xeventgeneratorlist
{
    xeventgenerator_node * head;
    xeventgenerator_node * tail;
    xuint64                size;
};


struct xeventobject
{
    /** INHERITED EVENT MEMBER */
    xeventqueue_node       eventnode;
    xeventhandler          on;
    /** BASE EVENT MEMBER */
    xeventengine_node      enginenode;
    xeventgeneratorlist    generators;
    xeventlist             events;
    xsync *                sync;
    xuint32                masks;
    xuint32                status;
};

#define xeventon(event) do { event->on(event); } while(0)

extern xeventgenerator_node * xeventgenerator_register_object(xeventgenerator * generator, xeventobject * object);
extern void xeventgenerator_unregister_object(xeventgenerator_node * node);

extern void xeventqueue_push()

#endif // __NOVEMBERIZING_X__EVENT__H__
