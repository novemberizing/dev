#ifndef   __NOVEMBERIZING_X__ENGINE__H__
#define   __NOVEMBERIZING_X__ENGINE__H__

#include <x/list.h>

struct xengine
{
    xuint32 status;
    xlist * generators;
};

typedef struct xengine xengine;

#define xengine_status_cancelling       0x80000000U

#define xengine_module_type_generator   1

extern xengine * xenginenew();
extern xengine * xenginerem(xengine * o);
extern xengine * xengineon(xengine * o);
extern xengine * xengineplug(xengine * o, xuint32 type, void * module);

#endif // __NOVEMBERIZING_X__ENGINE__H__
