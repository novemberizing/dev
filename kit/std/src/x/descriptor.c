#include "descriptor.h"

/**
 * @fn      extern xint32 xdescriptoralive(xdescriptor * descriptor)
 * @brief   디스크립터의 오픈 상태 여부를 체크합니다.
 * @details 디스크립터의 상태 변수와 별개로 단순히 디스크립터의 값을 바탕으로 체크하는 함수입니다.
 * 
 * @param   descriptor  | xdescriptor * | in | 디스크립터 객체 |
 * 
 * @return  | boolean | 디스크립터의 오픈 상태 |
 * 
 *              1(TRUE):  소켓은 열린 상태입니다.
 *              0(FALSE): 소켓은 닫힌 상태입니다.
 * 
 */
extern xint32 xdescriptoralive(xdescriptor * descriptor)
{
    return descriptor->handle.f >= 0;
}




extern xdescriptor * xdescriptornew(xuint64 size)
{
    xassertion(size < sizeof(xdescriptor), "");

    xdescriptor * descriptor = (xdescriptor *) calloc(size, 1);

    descriptor->handle.f = xinvalid;

    return descriptor;
}