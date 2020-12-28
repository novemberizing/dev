#ifndef   __NOVEMBERIZING_X__EVENT_IO_GENERATOR__H__
#define   __NOVEMBERIZING_X__EVENT_IO_GENERATOR__H__

#include <x/type.h>

struct xevent_io_generator
{
    xuint32 type;
    struct xgenerator * (*rem)(xgenerator *);
};

typedef struct xevent_io_generator xevent_io_generator;

extern xevent_io_generator * xevent_io_generator_new();

#endif // __NOVEMBERIZING_X__EVENT_IO_GENERATOR__H__
