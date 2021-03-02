#ifndef   __NOVEMBERIZING_X__SESSION__H__
#define   __NOVEMBERIZING_X__SESSION__H__

#include <x/io.h>

#include <x/socket.h>
#include <x/session/list.h>

#define xsessioneventtype_in        xsocketeventtype_in
#define xsessioneventtype_out       xsocketeventtype_out

struct xsession;
struct xsessionsocket;

typedef struct xsession xsession;
typedef struct xsessionsocket xsessionsocket;

typedef xint64 (*xsessionsubscriber)(xsession *, xuint64, void *, xint64);

typedef xsession * (*xsessionfactory)(xint32, xint32, xint32);
typedef void (*xsessionreleaser)(xsession *);

struct xsession
{
    xsessionsocket * descriptor;

    xserver * server;

    xsession * prev;
    xsession * next;
    xsessionlist * cntr;
};

#endif // __NOVEMBERIZING_X__SESSION__H__
