#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

/**
 * EVENT GENERATOR
 * EVENT PROCESSOR
 * EVENT HANDLER
 * EVENT OBJECT
 * 
 * EVENT
 * 
 * EVENT ENGINE
 */

struct xeventengine;

typedef struct xeventengine xeventengine;

struct xeventobj;

typedef struct xeventobj xeventobj;

struct xevent;

typedef struct xevent xevent;

struct xevent
{
    xuint16 cagegory;
    xuint16 type;
    xeventobj * target;
    xeventengine * engine;
};

/**
 * 
 * xeventengine_on(engine);
 * xeventengine_off(engine);
 * 
 * xeventengine_run(engine);
 * 
 * socket
 * time
 * signal
 * i/o
 * 
 * 
 * 
 * 
 */


struct xeventengine
{
    xlist generators;
};

#define xeventengine_init() (xeventengine) { 0, }

extern int xeventengine_run(xeventengine * o);




#endif // __NOVEMBERIZING_X__EVENT__H__
