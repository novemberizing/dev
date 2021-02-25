/**
 * @file        x/std.c
 * @brief       표준 라이브러리 구현 소스 파일입니다.
 * @details     
 * 
 * @version     0.0.1
 * @date        2021. 02. 22.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "std.h"
#include "thread.h"

/**
 * @fn          extern xint32 xerrorret(xint32 number)
 * @brief       양수의 에러 번호를 음수로 치환합니다.
 * @details     주어진 파라미터가 음수이거나 0 이면 변환하지 않습니다.
 * 
 * @param       number | xint32 | in | 에러 번호 |
 * 
 * @return      | xint32 | 음수로 변환된 에러 번호 |
 * 
 * @version     0.0.1
 * @date        2021. 02. 25.
 */
extern xint32 xerrorret(xint32 number)
{
    return number > 0 ? -number : number;
}
