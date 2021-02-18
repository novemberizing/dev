#include "object.h"

// REMOVE THIS

/**
 * @fn      extern xeventobject * xeventobjectnew(xuint64 size)
 * @brief   메모리 공간에 이벤트 타겟 객체를 생성합니다.
 * @details 메모리 공간에 할당할 객체의 크기는 xeventobject 의 크기보다 커야 합니다.
 * 
 * @param   size    | xuint64 | 메모리 공간에 할당할 객체의 크기 |
 * @return  | xeventobject * | 이벤트 타겟 객체 |
 */
extern xeventobject * xeventobjectnew(xuint64 size)
{
    xassertion(size < sizeof(xeventobject), "");

    xeventobject * o = (xeventobject *) calloc(size, 1);

    // TODO: REMOVE BELOW CODE: CALLOC'S SAME RESULT
    o->subscription  = xnil;
    o->sync          = xnil;
    o->mask          = xeventobjectmask_void;
    o->status        = xeventobjectstatus_void;

    return o;
}

/**
 * @fn      extern xeventobject * xeventobjectrem(xeventobject * o)
 * @brief   이벤트 타겟 객체를 메모리 상에서 해제합니다.
 * @details subscription 과 sync 객체를 해제한 후에 객체 자신 역시 메모리 상에서 해제합니다.
 * 
 * @param   o   | xeventobject * | 이벤트 타겟 객체 |
 * 
 * @return  | xeventobject * | 이벤트 타겟 객체 |
 * 
 *              언제나 널을 리턴합니다.
 * 
 * @todo    xsubscriptionrem
 * @todo    xsyncrem
 * @todo    xobjectrem
 * @todo    객체 해제 시에 해제되면 안되는 것을 확인하도록 합니다.
 *          멀티스레드 구조에서 어딘가에서 사용중인 상태이면
 *          사용이 완료된 후에 삭제되어야 하는 경우가 생길 수 있습니다.
 *          그렇기 때문에
 */
extern xeventobject * xeventobjectrem(xeventobject * o)
{
    if(o)
    {
        o->subscription = xsubscriptionrem(o->subscription);
        o->sync = xsyncrem(o->sync);
        o = xobjectrem(o);
    }
    return o;
}