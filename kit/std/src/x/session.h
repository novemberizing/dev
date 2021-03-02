#ifndef   __NOVEMBERIZING_X__SESSION__H__
#define   __NOVEMBERIZING_X__SESSION__H__

#include <x/std.h>

struct xsession;
struct xsessionsocket;

typedef struct xsession xsession;
typedef struct xsessionsocket xsessionsocket;

typedef xint64 (*xsessionsubscriber)(xsession *, xuint64, void *, xint64);

struct xsession
{
    xsessionsocket * descriptor;
    xsessionsubscriber on;
};

#endif // __NOVEMBERIZING_X__SESSION__H__
