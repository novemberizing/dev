#ifndef   __NOVEMBERIZING_DS_XARRAY__H__
#define   __NOVEMBERIZING_DS_XARRAY__H__

#include <novemberizing/ds/xtypes.h>

struct xarray
{
    xuint32 type;
    xuint64 size;
    void *  values;
};

typedef struct xarray xarray;

#define xcontainer_type_array   3

extern xarray * xarraynew(void);

#endif // __NOVEMBERIZING_DS_XARRAY__H__
