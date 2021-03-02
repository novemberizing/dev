#ifndef   __NOVEMBERIZING_X__EXCEPTION__H__
#define   __NOVEMBERIZING_X__EXCEPTION__H__

#include <x/std.h>

#define xexceptiontype_void                     0
#define xexceptiontype_system                   1
#define xexceptiontype_descriptor               2

struct xexception;

typedef struct xexception xexception;

struct xexception
{
    void *       func;
    xint32       number;
    xuint32      type;
    const char * message;
};

#define xexception_void     ((xexception) { xnil, 0, 0, xnil })

extern void xexceptionset(xexception * exception, void * func, xint32 number, xuint32 type, const char * message);

extern const char * xexceptionmessage_get(void * func, xuint32 type, xint32 number);

#endif // __NOVEMBERIZING_X__EXCEPTION__H__
