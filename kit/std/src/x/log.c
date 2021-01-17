/**
 * @file    x/log.c
 * @brief   표준 로그 라이브러리 소스
 * @details
 * 
 * @version 0.0.1
 */

#include <unistd.h>

#include "std.h"

static xint32 __fd = xinvalid;

/**
 * @fn      extern xint32 xlogfd(void)
 * @brief   로그 파일 디스크럽터를 리턴합니다.
 * @details
 * 
 * @return  | xint32 | 로그 파일 디스크립터 |
 */
extern xint32 xlogfd(void)
{
    return __fd > xinvalid ? __fd : STDOUT_FILENO;
}
