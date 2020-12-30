#include "log.h"
#include "list.h"

xlist * xlistinit(xlist * o)
{
    xassertion(o == xnil, "o == xnil");

    xlistclr(o, o->xvalrem);

    return o;
}