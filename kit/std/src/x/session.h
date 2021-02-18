#ifndef   __NOVEMBERIZING_X__SESSION__H__
#define   __NOVEMBERIZING_X__SESSION__H__

struct xsession;
struct xsessionsocket;

typedef struct xsession xsession;
typedef struct xsessionsocket xsessionsocket;

struct xsession
{
    xsessionsocket * descriptor;
};

struct xsessionsocket
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
    /** SESSION SOCKET SPECIFIED MEMBER */
    struct
    {
        xstream * in;
        xstream * out;
    } stream;
};

#endif // __NOVEMBERIZING_X__SESSION__H__
