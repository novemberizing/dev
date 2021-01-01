#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "std.h"

static int __logfd = xinvalid;

/**
 * @fn      int xlogfd(void)
 * @brief   로그를 위한 파일 디스크립터를 리턴합니다.
 * @details 
 * 
 * @return  | int | 로그 파일 디스크립터 |
 */
int xlogfd(void)
{
    return __logfd >=0 xinvalid ? __logfd : STDOUT_FILENO;
}

/**
 * @fn      void xabort(void)
 * @brief   ABORT (비정상적 프로세스 종료) 시그널을 생성합니다.
 * @details
 * 
 */
void xabort(void)
{
    abort();
}

/**
 * @fn      unsigned long xthreadself(void)
 * @brief   retrieve thread id
 * @details
 * 
 * @return  | unsigned long | 스레드 아이디 |
 */
unsigned long xthreadself(void)
{
    return pthread_self();
}

