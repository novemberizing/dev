#ifndef   __NOVEMBERIZING_X__THREAD__POSIX__H__
#define   __NOVEMBERIZING_X__THREAD__POSIX__H__

#include <pthread.h>

#include <x/thread.h>

struct xthreadposix;

typedef struct xthreadposix xthreadposix;

typedef void (*xthreadposixfunc)(xthreadposix *);

/** TODO: 사용자가 재정의할 수 있도록 해야 한다. */
struct xthreadposix
{
    pthread_t *      handle;
    xthreadposixfunc func;
    xuint32          status;
    xthreadposixfunc cancel;
};

extern xthreadposix * xthreadposix_rem(xthreadposix * o);

extern void xthreadposix_cancel(xthreadposix * o, xthreadposixfunc cancel);
extern void xthreadposix_run(xthreadposix * o);

#endif // __NOVEMBERIZING_X__THREAD__POSIX__H__
