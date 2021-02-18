#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/descriptor.h>

struct xclient;
struct xclientsocket;

typedef struct xclient xclient;
typedef struct xclientsocket xclientsocket;

struct xclient
{
    xclientsocket * descriptor;
};

struct xclientsocket
{
    /** INHERITED EVENT OBJECT */
    xdescriptorsub * subscription;
    xsync *          sync;
    xuint32          mask;
    xuint32          status;
    /** INHERITED DESCRIPTOR */
    union
    {
        int    f;
        void * v;
    } handle;

    xint64  (*on)(xdescriptor *, xuint32, void *, xint64);
    xint64  (*process)(xdescriptor *, xuint32, void *);
    xint32  (*need)(xdescriptor *, xuint32);
    /** INHERITED SOCKET */
    xint32           domain;
    xint32           type;
    xint32           protocol;
    /** CLIENT SPECIFIED MEMBER */
    void *           addr;
    xuint32          addrlen;
    struct
    {
        xstream * in;
        xstream * out;
    } stream;
};

extern xclient * xclientnew(xuint64 size);
extern xclient * xclientrem(xclient * client);

#endif // __NOVEMBERIZING_X__CLIENT__H__
