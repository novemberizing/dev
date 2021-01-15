/**
 * @file    x/log.c
 * @brief   표준 로그 라이브러리 소스
 * @details
 * 
 * @version 0.0.1
 * 
 * 로그 라이브러리는 업그레이드 할 필요가 있습니다.
 * 
 * 컨셉:
 * 
 * - 로그 레벨
 * - 스레드별 로그
 * - 아답터 개념 도입
 */

#include <unistd.h>

#include "std.h"

static int __fd =  xinvalid;

/**
 * @fn      int xlogfd(void)
 * @brief   로그 파일 디스크립터를 리턴합니다.
 * @details
 * 
 * @return  | int | 로그 파일 디스크립터 |
 */
int xlogfd(void)
{
    return __fd > xinvalid ? __fd : STDOUT_FILENO;
}
