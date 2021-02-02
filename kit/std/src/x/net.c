#include <stdlib.h>

#include "./net.h"

struct xeventengine
{

};

extern xeventengine * xeventengine_new(void)
{
    xeventengine * engine = (xeventengine *) calloc(sizeof(xeventengine), 1);
    
    return (xeventengine * ) engine;
}

extern void *         xeventengine_rem(void * pointer)
{
    if(pointer)
    {
        free(pointer);
    }
    return xnil;
}