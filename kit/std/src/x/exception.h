#ifndef   __NOVEMBERIZING_X__EXCEPTION__H__
#define   __NOVEMBERIZING_X__EXCEPTION__H__

#include <x/std.h>

struct xexception;

typedef struct xexception xexception;

struct xexception
{
    void *       func;
    xint32       number;
    xuint32      type;
    const char * message;
};

extern const char * xexceptionmessage_get(void * func, xuint32 type, xint32 number);

#endif // __NOVEMBERIZING_X__EXCEPTION__H__
