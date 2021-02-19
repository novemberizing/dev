#include "std.h"

/**
 * @fn          extern xobject xobjectnew(const xobject data, xuint64 size)
 * @brief       주어진 객체와 같은 데이터를 가진 객체를 생성합니다.
 * @details     주어진 크기의 객체를 생성 후에 메모리 카피를 수행합니다.
 * 
 * @param       data | const xobject | 원본 |
 * @param       size | xuint64       | 객체의 크기 |
 * 
 * @return      | xobject | 카피한 객체 |
 * 
 * @see         xobject,
 *              malloc,
 *              memcpy
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 * 
 * @exception   | `data == xnil` | 데이터가 널일 경우 예외가 발생합니다. |
 *              | `size == 0`    | 크기가 0 일 경우 예외가 발생합니다.  |
 */
extern xobject xobjectnew(const xobject data, xuint64 size)
{
    xassertion(data == xnil || size == 0, "");

    void * o = malloc(size);

    return memcpy(o, data, size);
}

/**
 * @fn          extern void * xobjectrem(void * o)
 * @brief       객체를 제거합니다.
 * @details     객체가 널이 아니면 동작하도록 되어 있습니다.
 *              free 함수 역시 NULL 을 허용하지만,
 *              간헐적으로 혹은 오래된 API 의 경우 예외를 발생시킬 수 있습니다.
 * 
 * @param       o | xobject | 객체 |
 * @return      | xobject | 항상 널을 리턴합니다. |
 * 
 * @see         free,
 *              xobject
 * 
 * @version     0.0.1
 * @date        2021. 02. 18.
 */
extern xobject xobjectrem(xobject o)
{
    if(o)
    {
        free(o);
    }
    
    return xnil;
}