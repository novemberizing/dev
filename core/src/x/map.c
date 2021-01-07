#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "std.h"

static xmapnode * xmapnodenew(xval v, xmapnode * parent);
static void xmapnode_adjust_insertion(xmap * o, xmapnode * node);
static void xmapnode_adjust_deletion(xmap * o, xmapnode * node);

static xmapnode * xmapnode_get_minimum(xmapnode * n);
static xmapnode * xmapnode_get_next(xmapnode * n);


xmap * xmapnew(xvalcmp comp)
{
    xassertion(comp == xnil, "comp is null");

    xmap * o = (xmap *) calloc(sizeof(xmap), 1);

    xassertion(o == xnil, "fail to calloc (%d)", errno);

    o->flags = xobj_mask_allocated | xobj_type_map;
    o->comp = comp;

    return o;
}

/**
 * @fn      void * xmaprem(void * p)
 * @brief   맵 객체를 메모리 상에서 해제합니다.
 * @details
 * 
 * @param   | p | in | void * | 맵의 객체를 메모리 상에서 해제합니다. |
 * 
 * @return  | void * | 해제된 맵 객체의 주소 (맵이 동적할당에 의해서 생성되었다면 해제 후에 널을 리턴합니다.) |
 */
extern void * xmaprem(void * p)
{
    xmap * o = (xmap *) p;
    xcheck(o == xnil, xnil, "invalid parameter");
    xassertion(xobjtype(o) != xobj_type_map || o->size > 0, "list is not clear");

    xmapclear(o, xnil);
    xmapsyncoff(o);

    if(o->flags & xobj_mask_allocated)
    {
        free(o);
        o = xnil;
    }
    return o;
}

/**
 * @fn      xmap * xmapsyncon(xmap * o, xuint32 type)
 * @brief   맵의 동기화 객체를 활성화 합니다.
 * @details
 * 
 * @param   | o    | in | xmap *  | 맵의 객체 주소 |
 * @param   | type | in | xuint32 | 생성하고자 하는 동기화 객체의 타입 |
 * 
 * @return  | xmap * | 객체의 포인터 |
 */
xmap * xmapsyncon(xmap * o, xuint32 type)
{
    xcheck(o == xnil || o->sync, o, "object is null or sync is already created");
    o->sync = xsyncnew(type);
    
    return o;
}

/**
 * @fn      xmap * xmapsyncoff(xmap * o)
 * @brief   맵 객체의 동기화를 해제합니다.
 * @details
 * 
 * @param   | o | in | xmap * | 맵의 객체 |
 * 
 * @return  | xmap * | 맵 객체 |
 */
xmap * xmapsyncoff(xmap * o)
{
    xcheck(o == xnil || o->sync == xnil, o, "object is null or sync is not created");

    o->sync = o->sync->destruct(o->sync);

    return o;
}

/**
 * @fn      int xmapadd(xmap * o, xval v, xvalcb f)
 * @brief   맵에 아이템을 삽입합니다.
 * @details 
 * 
 * @param   | o | in | xmap * | 맵 객체 |
 * @param   | v | in | xval   | 아이템 |
 * @param   | f | in | xvalcb | 이전에 대입되었던 값이 존재하면 이전 값을 파라미터로 삽입합니다. |
 */
int xmapadd(xmap * o, xval v, xvalcb f)
{
    xassertion(o == xnil, "object is null");

    xsynclock(o->sync);
    xmapnode * node = o->root;
    while(node)
    {
        int diff = o->comp(node->value, v);
        if(diff < 0)
        {
            if(node->right)
            {
                node = node->right;
                continue;
            }
            node->right = xmapnodenew(v, node);
            o->size = o->size + 1;
            xmapnode_adjust_insertion(o, node->right);
            xsyncunlock(o->sync);
            return xsuccess;
        }
        else if(diff > 0)
        {
            if(node->left)
            {
                node = node->left;
                continue;
            }
            node->right = xmapnodenew(v, node);
            o->size = o->size + 1;
            xmapnode_adjust_insertion(o, node->left);
            xsyncunlock(o->sync);
            return xsuccess;
        }
        else
        {
            xval old = node->value;
            node->value = v;
            xsyncunlock(o->sync);
            if(f)
            {
                f(old);
            }
            return xsuccess;
        }
    }
    o->root = xmapnodenew(v, xnil);
    o->root->color = xmapnode_black;
    o->size = o->size + 1;
    xsyncunlock(o->sync);
    return xsuccess;
}

/**
 * @fn      int xmapdel(xmap * o, xval v, xvalcb f)
 * @brief   객체의 아이템을 삭제합니다.
 * @details
 * 
 * @param   | o | in | xmap * | 맵의 객체입니다. |
 * @param   | v | in | xval   | 지우고자 하는 값 |
 * @param   | f | in | xvalcb | 지운 값의 콜백 |
 * 
 * @return  | int | 맵의 삭제 결과 |
 */
int xmapdel(xmap * o, xval v, xvalcb f)
{
    xassertion(o == xnil, "object is null");

    xsynclock(o->sync);
    xmapnode * node = o->root;

    while(node)
    {
        int diff = o->comp(node->value, v);
        if(diff < 0)
        {
            node = node->right;
        }
        else if(diff > 0)
        {
            node = node->left;
        }
        else
        {
            xval value = node->value;
            // delete
            if(node->left && node->right)
            {
                xmapnode * successor = xmapnode_get_minimum(node->right);
                node->value = successor->value;
                node = successor;
            }
            
            /**
             * only one child node's color is red,
             * only node's color is black
             */
            if(node->left)
            {
                node->left->parent = node->parent;

                if(node->parent)
                {
                    if(node->parent->left == node)
                    {
                        node->parent->left = node->left;
                    }
                    else
                    {
                        node->parent->right = node->left;
                    }
                }
                else
                {
                    o->root = node->left;
                }
                node->left->color = xmapnode_black;
                o->size = o->size - 1;
                xsyncunlock(o->sync);
                if(f)
                {
                    f(value);
                }
                free(node);
                return xsuccess;
            }
            else if(node->right)
            {
                node->right->parent = node->parent;

                if(node->parent)
                {
                    if(node->parent->left == node)
                    {
                        node->parent->left = node->right;
                    }
                    else
                    {
                        node->parent->right = node->right;
                    }
                }
                else
                {
                    o->root = node->right;
                }
                node->right->color = xmapnode_black;
                o->size = o->size - 1;
                xsyncunlock(o->sync);
                if(f)
                {
                    f(value);
                }
                free(node);
                return xsuccess;
            }
            else
            {
                if(node->parent)
                {
                    if(node->parent->left == node)
                    {
                        node->parent->left = xnil;
                    }
                    else
                    {
                        node->parent->right = xnil;
                    }
                }
                else
                {
                    o->root = xnil;
                }
                if(node->color != xmapnode_red)
                {
                    xmapnode_adjust_deletion(o, node);
                }
                o->size = o->size - 1;
                xsyncunlock(o->sync);
                if(f)
                {
                    f(value);
                }
                free(node);
                return xsuccess;
            }
        }
    }
    xsyncunlock(o->sync);

    return xfail;
}

/**
 * @fn      xmap * xmapclear(xmap * o, xvalcb f)
 * @brief   맵 객체의 모든 아이템을 삭제합니다.
 * @details
 * 
 * @param   | o | in | xmap * | 맵 객체 |
 * @param   | f | in | xvalcb | 지운 아이템의 콜백 |
 * 
 * @return  | xmap * | 맵의 포인터 |
 */
xmap * xmapclear(xmap * o, xvalcb f)
{
    xcheck(o == xnil || o->size == 0, o, "object is null or size is zero");

    xsynclock(o->sync);
    
    xmapnode * node = xmapnode_get_minimum(o->root);

    while(node)
    {
        xmapnode * next = xmapnode_get_next(node);
        if(f)
        {
            f(node->value);
        }
        free(node);
        node = next;
    }

    xsyncunlock(o->sync);

    return o;
}

/**
 * @fn      int xmapget(xmap * o, xval v, xvalcb f)
 * @brief   맵에서 값을 찾습니다.
 * @details
 * 
 * @param   | o | in | xmap * | 맵의 객체 |
 * @param   | v | in | xval   | 찾고자 하는 값 |
 * @param   | f | in | xvalcb | 찾았을 때 호출되는 콜백 함수 |
 * 
 * @return  | int | 맵의 리턴 값 (success or fail) |
 */
int xmapget(xmap * o, xval v, xvalcb f)
{
    xassertion(o == xnil || f == xnil, "object is null or callback is not exist");

    xsynclock(o->sync);
    xmapnode * node = o->root;
    while(node)
    {
        int diff = o->comp(node->value, v);
        if(diff < 0)
        {
            node = node->right;
        }
        else if(diff > 0)
        {
            node = node->left;
        }
        else
        {
            xval value = node->value;
            xsyncunlock(o->sync);
            f(value);
            return xsuccess;
        }
    }
    xsyncunlock(o->sync);
    return xfail;
}