#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "std.h"

static xlistnode * xlistnodenew(xval v);

/**
 * @fn      xlist * xlistnew(void)
 * @brief   리스트 객체를 생성합니다.
 * @details
 * 
 * @return  | xlist * | 생성된 리스트 객체 |
 */
xlist * xlistnew(void)
{
    xlist * o = (xlist *) calloc(sizeof(xlist), 1);

    o->flags = xobj_mask_allocated | xobj_type_list;
    o->destruct = xlistrem;

    return o;
}

/**
 * @fn      void * xlistrem(void * p)
 * @brief   리스트 객체를 메모리 상에서 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 리스트 객체의 주소 |
 * 
 * @return  | void * | 메모리 상에서 해제된 객체의 주소 값 |
 */
void * xlistrem(void * p)
{
    xlist * o = (xlist *) p;
    xcheck(o == xnil, xnil, "invalid parameter");
    xassertion(xobjtype(o) != xobj_type_list || o->size > 0, "list is not clear");

    xlistclear(o, xnil);
    xlistsyncoff(o);

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }

    return o;
}

/**
 * @fn      xlist * xlistsyncon(xlist * o, xuint32 type)
 * @brief   리스트 객체의 동기화 기능을 활성화합니다.
 * @details
 * 
 * @param   | o    | in | xlist * | 리스트 객체 |
 * @param   | type | in | xuint32 | 동기화 객체 타입 |
 * 
 * @return  | xlist * | 리스트 객체 |
 */
xlist * xlistsyncon(xlist * o, xuint32 type)
{
    xcheck(o == xnil || o->sync, o, "object is null or sync object's is already created");

    o->sync = xsyncnew(type);

    return o;
}

/**
 * @fn      xlist * xlistsyncoff(xlist * o)
 * @brief   리스트 객체의 동기화 기능을 비활성화합니다.
 * @details 
 * 
 * @param   | o | in | xlist * | 리스트 객체 |
 * 
 * @return  | xlist * | 리스트 객체 |
 */
xlist * xlistsyncoff(xlist * o)
{
    xcheck(o == xnil || o->sync == xnil, o, "object is null or sync object's is not created");

    o->sync = o->sync->destruct(o->sync);

    return o;
}

/**
 * @fn      void xlistadd(xlist * o, xval v)
 * @brief   리스트 객체에 리스트 아이템을 삽입합니다. (리스트에서 가장 앞에)
 * @details
 * 
 * @param   | o | in | xlist * | 리스트 객체 |
 * @param   | v | in | xval    | 리스트 아이템의 값 |
 * 
 * 만약에 원격지 서버에 리스트가 존재하여 콜백에 의한 처리가 필요하다면
 */
void xlistadd(xlist * o, xval v)
{
    xassertion(o == xnil, "list is null");

    xlistnode * node = xlistnodenew(v);

    xsynclock(o->sync);
    node->next = o->head;
    o->head = node;
    if(node->next)
    {
        node->next->prev = node;
    }
    if(o->tail == xnil)
    {
        o->tail = node;
    }
    o->size = o->size + 1;
    xsyncunlock(o->sync);
}

/**
 * @fn      void xlistpush(xlist * o, xval v)
 * @brief   리스트 객체의 맨 뒤에 값을 삽입합니다.
 * @details
 * 
 * @param   | o | in | xlist * | 리스트 객체 |
 * @param   | v | in | xval    | 값 |
 */
void xlistpush(xlist * o, xval v)
{
    xassertion(o == xnil, "list is null");

    xlistnode * node = xlistnodenew(v);

    xsynclock(o->sync);
    node->prev = o->tail;
    o->tail = node;
    if(node->prev)
    {
        node->prev->next = node;
    }
    if(o->head == xnil)
    {
        o->head = node;
    }
    o->size = o->size + 1;
    xsyncunlock(o->sync);
}

/**
 * @fn      int xlistpop(xlist * o, xvalcb f)
 * @brief   리스트 객체의 맨 앞에 있는 아이템을 제거 합니다.
 * @details
 * 
 * @param   | o | in | xlist * | 리스트 객체 |
 * @param   | f | in | xvalcb  | 리스트 객체 제거 시에 호출되는 콜백 함수 |
 * 
 * @return  | int | 리스트 아이템의 제거 결과 (성공: 0, 실패: -1) |
 */
int xlistpop(xlist * o, xvalcb f)
{
    xassertion(o == xnil, "list is null");

    xsynclock(o->sync);
    xlistnode * node = o->head;
    if(node)
    {
        o->head = node->next;
        if(o->head)
        {
            o->head->prev = xnil;
        }
    }
    if(o->tail == node)
    {
        o->tail = xnil;
    }

    o->size = o->size - 1;
    xsyncunlock(o->sync);

    if(node)
    {
        if(f)
        {
            f(node->value);
        }
        free(node);
        return xsuccess;
    }
    return xfail;
}

/**
 * @fn      int xlistpop(xlist * o, xvalcb f)
 * @brief   리스트 객체의 맨 뒤에 있는 아이템을 제거 합니다.
 * @details
 * 
 * @param   | o | in | xlist * | 리스트 객체 |
 * @param   | f | in | xvalcb  | 리스트 객체 제거 시에 호출되는 콜백 함수 |
 * 
 * @return  | int | 리스트 아이템의 제거 결과 (성공: 0, 실패: -1) |
 */
int xlistdel(xlist * o, xvalcb f)
{
    xassertion(o == xnil, "list is null");

    xlistnode * node = o->tail;

    xsynclock(o->sync);
    if(node)
    {
        o->tail = node->prev;
        if(o->tail)
        {
            o->tail->next = xnil;
        }
    }
    if(o->head == node)
    {
        o->head = xnil;
    }

    o->size = o->size - 1;
    xsyncunlock(o->sync);

    if(node)
    {
        if(f)
        {
            f(node->value);
        }
        free(node);
        return xsuccess;
    }
    return xfail;
}

/**
 * @fn      void xlisteach(xlist * o, xvalcb f)
 * @brief   리스트 객체의 모든 아이템을 조회합니다.
 * @details
 * 
 * @param   | o | in | xlist * | 리스트 객체 |
 * @param   | f | in | xvalcb  | 리스트 아이템을 순회할 때의 콜백 함수 |
 */
void xlisteach(xlist * o, xvalcb f)
{
    xassertion(o == xnil || f == xnil, "o == xnil or callback is null");

    xlistnode * node = o->head;

    xsynclock(o->sync);
    while(node)
    {
        // unlock & lock check:
        // lock & unlock 을 한 상태에서 다른 스레드에서 노드가 삭제되면,
        // 그리고 그 다음 노드 역시 삭제되면 문제가 생길 수 있다.
        // 그렇게 때문에 전체 락을 걸 수 밖에 없다.
        f(node->value);
        node = node->next;
    }
    xsyncunlock(o->sync);
}

/**
 * @fn      xlist * xlistclear(xlist * o, xvalcb f)
 * @brief   리스트의 모든 아이템을 제거 합니다.
 * @details
 * 
 * @param   | o | in | xlist * | 리스트 객체 |
 * @param   | f | in | xvalcb  | 리스트 아이템 콜백 |
 * 
 * @return  | xlist * | 리스트 객체 |
 */
xlist * xlistclear(xlist * o, xvalcb f)
{
    xsynclock(o->sync);
    while(o->head)
    {
        if(f)
        {
            f(o->head->value);
        }
        xlistnode * node = o->head;
        o->head = o->head->next;
        o->size = o->size - 1;
        free(node);
    }
    xsyncunlock(o->sync);

    return o;
}

static xlistnode * xlistnodenew(xval v)
{
    xlistnode * o = (xlistnode *) calloc(sizeof(xlistnode), 1);

    o->value = v;
    
    return o;
}