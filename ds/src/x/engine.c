#include <stdlib.h>
#include <errno.h>

#include "engine.h"
#include "log.h"

static inline void __xengine_generator_list_rem(xval v)
{
    informationLog("implement this");
}

xengine * xenginenew()
{
    xengine * o = (xengine *) calloc(sizeof(xengine), 1);

    assertion(o == xnil, "fail to calloc (%d)", errno);

    o->generators = xlistnew();

    return o;
}

xengine * xenginerem(xengine * o)
{
    assertion(o == xnil, "o is null");

    xlistrem(o->generators, __xengine_generator_list_rem);
    free(o);

    return xnil;
}

xengine * xengineon(xengine * o)
{
    assertion(o == NULL, "o is null");
    assertion(o->status != 0, "engine is already running");

    while((o->status & xengine_status_cancelling) != xengine_status_cancelling)
    {

    }
    return xnil;
}

xengine * xengineplug(xengine * o, xuint32 type, void * module)
{
    assertion(o == xnil, "o is null");
    assertion(module == xnil, "module is null");

    if(type == xengine_module_type_generator)
    {
        xlistpush(o->generators, xvalgenptr(module));
    }
    else
    {
        assertion(true, "unsupported plugin type (%u)", type);
    }

    return o;
}