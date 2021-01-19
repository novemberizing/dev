#ifndef   __NOVEMBERIZING_X__EVENT__H__
#define   __NOVEMBERIZING_X__EVENT__H__

#include <x/std.h>

struct xevent;
struct xeventgenerator;
struct xeventengine;

typedef struct xevent xevent;
typedef struct xeventgenerator xeventgenerator;
typedef struct xeventengine xeventengine;

#define xeventengine_status_void        0x00000000U
#define xeventengine_status_on          0x00000001U

#define xeventengine_status_cancel      0x80000000U

struct xevent
{
    xuint32 type;
    xeventgenerator * from;
};

struct xeventgenerator
{

};

struct xeventengine
{
    xuint32 status;
    xlist generators;
    void (*internal)(xeventengine *);
    xlist queue;
};

extern xint32 xeventenginerun(xeventengine * o);

#define xeventenginecancel(o)   (o->status |= xeventengine_status_cancel)

#endif // __NOVEMBERIZING_X__EVENT__H__
