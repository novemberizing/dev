/**
 * @file    x/log.c
 * @brief   log library implement file
 * @details
 * 
 * 
 */

#include <unistd.h>
#include <stdlib.h>

#include "std.h"

static int __logfd = xinvalid;

/**
 * @fn      int xlogfd(void)
 * @brief   로그 파일 디스크립터를 리턴합니다.
 * @details
 * 
 * @return  | int | 로그 파일 디스크립터 |
 */
int xlogfd(void)
{
    return __logfd > xinvalid ? __logfd : STDOUT_FILENO;
}

/**
 * @fn      void xexit(int status)
 * @brief   프로세스를 종료합니다.
 * @details
 * 
 * @param   | status | in | int | 프로세스 종료 상태 |
 */
void xexit(int status)
{
    exit(status);
}
