#include <pthread.h>

#include "std.h"

unsigned long xthreadid(void)
{
    return pthread_self();
}