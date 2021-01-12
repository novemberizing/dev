#include <unistd.h>

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
