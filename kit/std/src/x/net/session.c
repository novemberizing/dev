#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <poll.h>

#include "../net.h"

extern xint64 xsessionsocketeventon(xsession * o, void * parent, xuint32 mask, const void * data, xval val)
{

}

extern xsession * xsessionnew(void)
{
    xsession * session = (xsession *) calloc(sizeof(xsession), 1);

    session->flags           = (xobj_mask_allocated);
    session->destruct        = xsessionrem;

    session->socket.handle.f = xinvalid;
    session->socket.on       = xsessionsocketeventon;

    return session;
}

extern void * xsessionrem(void * p)
{
    xsession * o = (xsession *) p;
    if(o)
    {
        xsynclock(o->sync);

        xassertion(o->parent, "xsession's parent already linked");
        xassertion(o->children.total > 0, "xsession's children exist");

        if(xsessionalive(o))
        {
            xsessionclose(o);
        }

        o->readbuf  = xobjrem(o->readbuf);
        o->writebuf = xobjrem(o->writebuf);

        xsyncunlock(o->sync);

        o->sync     = xobjrem(o->sync);

        if(xobjallocated(o))
        {
            free(o);
            o = xnil;
        }
    }
    return o;
}

extern xint32 xsessionclose(xsession * session)
{
    if(session)
    {
        int ret = xdescriptorclose((xdescriptor *) xaddressof(session->socket));
        if(ret == xsuccess)
        {
            if(session->parent)
            {
                session->parent->release(session->parent, (xeventobj *) session);
            }
            return xsuccess;
        }
        else
        {
            xcheck(xtrue, "fail to xdescriptorclose");
            return xfail;
        }
    }
    else
    {
        xcheck(xtrue, "session is null");
    }
    return xsuccess;
}
