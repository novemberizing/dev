#include <pthread.h>

#include "std.h"

extern unsigned long xthreadid(void)
{
    return pthread_self();
}