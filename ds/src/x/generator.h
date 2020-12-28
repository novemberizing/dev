#ifndef   __NOVEMBERIZING_X__GENERATOR__H__
#define   __NOVEMBERIZING_X__GENERATOR__H__

#include <x/type.h>

struct xgenerator
{
    xuint32 type;
    struct xgenerator * (*rem)(xgenerator *);
};

typedef struct xgenerator xgenerator;

typedef xgenerator * (*removal)(xgenerator *);

#endif // __NOVEMBERIZING_X__GENERATOR__H__
