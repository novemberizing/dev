#include "client.h"

#include "stream.h"

struct xdescriptorclient
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
    /** CLIENT SPECIFIED MEMBER */
    xint32           domain;
    xint32           type;
    xint32           protocol;
    void *           addr;
    xuint32          addrlen;
    struct
    {
        xstream * in;
        xstream * out;
    } stream;
};

typedef struct xdescriptorclient xdescriptorclient;

static xdescriptor * xdecriptorclient_new(void)
{
    xdescriptorclient * descriptor = (xdescriptorclient *) xdescriptornew(sizeof(xdescriptorclient));

    descriptor->handle.f = xinvalid;

    return descriptor;
}

extern xclient * xclientnew(xuint64 size)
{
    xassertion(size < sizeof(xclient), "");

    xclient * client = (xclient *) calloc(size, 1);

    client->descriptor = (xdescriptorclient * ) calloc(sizeof(xdescriptorclient), 1);

    return client;
}

extern xclient * xclientrem(xclient * client)
{


    return client;
}