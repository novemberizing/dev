#ifndef   __NOVEMBERIZING_X__THREAD__H__
#define   __NOVEMBERIZING_X__THREAD__H__

#include <x/std.h>

#define xthreadstatus_void      (0x00000000u)
#define xthreadstatus_on        (0x00000001u)

struct xthread;

typedef struct xthread xthread;

typedef void (*xthreadfunc)(xthread *);

extern xthread * xthreadnew(xthreadfunc func, xuint64 size);
extern xthread * xthreadrem(xthread * o);

extern xint32 xthreadcheck_removable(xthread * o);
extern void xthreadcancel(xthread * o, xthreadfunc cancel);
extern void xthreadrun(xthread * o);

/** internal definition */

struct xthread
{
    void *      handle;
    xthreadfunc func;
    xuint32     status;
    xthreadfunc cancel;
};

#endif // __NOVEMBERIZING_X__THREAD__H__
