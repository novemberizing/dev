#ifndef   __NOVEMBERIZING_X__THREAD__H__
#define   __NOVEMBERIZING_X__THREAD__H__

#include <x/std.h>

struct xthread;

typedef struct xthread xthread;

#define xthreadstatus_void      (0x00000000u)
#define xthreadstatus_on        (0x00000001u)

extern xuint64 xthreadid(void);


typedef void (*xthreadfunc)(xthread *);

extern xthread * xthreadnew(xthreadfunc func, xuint64 size);
extern xthread * xthreadrem(xthread * o);

extern xint32 xthreadremovable(xthread * o);
extern void xthreadcancel(xthread * o, xthreadfunc callback);
extern void xthreadrun(xthread * o);

/** internal definition */

struct xthread
{
    xhandle     handle;
    xthreadfunc func;
    xuint32     status;
    xthreadfunc cancel;
};

#endif // __NOVEMBERIZING_X__THREAD__H__
