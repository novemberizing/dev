#ifndef   __NOVEMBERIZING_X__FUNC__H__
#define   __NOVEMBERIZING_X__FUNC__H__

#include <x/obj.h>

struct xfunc
{
    int status;
    xobj * parameter;
    xobj * result;
    xobj * (*call)(xobj *);
    void * (*back)(struct xfunc *, xobj *);
};

typedef struct xfunc xfunc;

#define xfunc_status_none       0
#define xfunc_status_success    1
#define xfunc_status_fail       -1

extern xfunc * xfuncnew(xobj * parameter, xobj * (*call)(xobj *), void (*back)(xfunc *, xobj *));
extern xfunc * xfuncrem(xfunc * o);

extern xobj * xfunccall(xfunc * o);

#endif // __NOVEMBERIZING_X__FUNC__H__
