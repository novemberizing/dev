#include <pthread.h>

#include "std.h"

/**
 * @fn      unsigned long xthreadid(void)
 * @brief   스레드 아이디를 리턴합니다.
 * @details
 * 
 * @return  | unsigned long | 스레드 아이디 |
 */
unsigned long xthreadid(void)
{
    return pthread_self();
}
