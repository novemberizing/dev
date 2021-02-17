#ifndef   __NOVEMBERIZING_X__CLIENT__H__
#define   __NOVEMBERIZING_X__CLIENT__H__

#include <x/descriptor.h>

struct xclient;

typedef struct xclient xclient;

struct xclient
{
    xdescriptor * descriptor;
};

extern xclient * xclientnew(xuint64 size);
extern xclient * xclientrem(xclient * client);

#endif // __NOVEMBERIZING_X__CLIENT__H__
