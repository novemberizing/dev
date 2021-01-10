#include <pthread.h>


#include "std.h"

/**
 * @fn      unsigned long xthreadid(void)
 * @brief   retrieve thread id
 * @details
 * 
 * @return  | unsigned long | thread id |
 */
unsigned long xthreadid(void)
{
    return pthread_self();
}