#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "xarray.h"

xarray * xarraynew(void)
{
    xarray * o = (xarray *) calloc(sizeof(xarray), 1);

    if(o == NULL)
    {
        fprintf(stdout, "fail to %s() caused by calloc (%d)\n", __func__, errno);
        return NULL;
    }

    o->type = xcontainer_type_array;

    return o;
}

