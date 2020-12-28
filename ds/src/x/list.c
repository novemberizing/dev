#include "list.h"

xlist * xlistnew()
{
    xlist * o = (xlist *) calloc(sizeof(xlist), 1);

    return o;
}

extern xlist * xlistinit(xlist * o);
extern xlist * xlistterm(xlist * o);
extern xlist * xlistrem(xlist * o);