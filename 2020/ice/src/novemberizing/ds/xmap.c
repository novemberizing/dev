#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

#include "xmap.h"

static inline xmapnode * __xmap_minimum_node_get(xmapnode * node)
{
    while(node && node->left)
    {
        node = node->left;
    }
    return node;
}

static inline xmapnode * __xmap_next_minumum_node_get(xmapnode * node)
{
    if(node)
    {
        if(node->right)
        {
            return __xmap_minimum_node_get(node->right);
        }
        else
        {
            xmapnode * parent = node->parent;
            while(parent && parent->right == node)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
    }
    return node;
}

// remove this

static inline void print(variant v)
{
    printf("%ld ", v.u64);
}

static inline xmap * __xmap_validate(xmap * o)
{
    xmapnode * node = o->root;
    if(node->color == xmapnode_red)
    {
        fprintf(stdout, "[%s] xmap is invalid (root node is not black)\n", "critical");
        abort();
        return NULL;
    }
    if(node->parent)
    {
        fprintf(stdout, "[%s] root is not root\n", "critical");
        abort();
        return NULL;
    }
    int blacknodecnt = 0;
    int max = 0;
    int count = 0;

    while(node)
    {
        count = count + 1;
        if(node->color == xmapnode_red)
        {
            if(node->left && node->left->color == xmapnode_red)
            {
                fprintf(stdout, "[%s] xmap is invalid (root node is not black)\n", "critical");
                abort();
                return NULL;
            }
            if(node->right && node->right->color == xmapnode_red)
            {
                fprintf(stdout, "[%s] xmap is invalid (root node is not black)\n", "critical");
                abort();
                return NULL;
            }
        }
        else
        {
            blacknodecnt = blacknodecnt + 1;
        }
        if(node->left)
        {
            node = node->left;
            continue;
        }
        if(node->right)
        {
            node = node->right;
            continue;
        }
        if(max == 0)
        {
            max == blacknodecnt;
        }
        else if(blacknodecnt != max)
        {
            fprintf(stdout, "[%s] xmap is invalid (black node count is not same)\n", "critical");
            abort();
            return NULL;
        }
        // leaf node, find not visit node
        xmapnode * parent = node->parent;
        xmapnode * right = NULL;
        while(parent)
        {
            if(parent->left == node)
            {
                if(parent->right)
                {
                    right = parent->right;
                    break;
                }
            }
            node = parent;
            parent = node->parent;
        }
        if(right)
        {
            node = right;
            continue;
        }
        break;
    }
    if(count != o->size)
    {
        xmapfor(o, print);
        fprintf(stdout, "%ld : %ld\n", count, o->size);
        fprintf(stdout, "validate is not\n");
        abort();
    }
    return o;
}

static xmapnode * __xmapnodenew(variant v, xmapnode * parent)
{
    xmapnode * o = (xmapnode *) calloc(sizeof(xmapnode), 1);
    if(o == NULL)
    {
        fprintf(stdout, "fail to %s() caused by calloc (%d)\n", __func__, errno);
        return NULL;
    }

    o->value = v;
    o->parent = parent;

    return o;
}

static inline int __xmapnode_is_black(xmapnode * node)
{
    return node == NULL || node->color == xmapnode_black;
}

static inline int __xmapnode_is_red(xmapnode * node)
{
    return node != NULL && node->color == xmapnode_red;
}

static int __xmapnode_is_left(xmapnode * parent, xmapnode * node)
{
    return parent && parent->left == node;
}

static int __xmapnode_is_right(xmapnode * parent, xmapnode * node)
{
    return parent && parent->right == node;
}

static xmapnode * __xmapnode_rotate_right(xmap * o, xmapnode * parent)
{
    // parent && node is always exist
    xmapnode * grandparent = parent->parent;
    xmapnode * node = parent->left;
    xmapnode * left = node->left;
    xmapnode * right = node->right;

    parent->left = right;
    if(right)
    {
        right->parent = parent;
    }

    if(grandparent)
    {
        if(grandparent->left == parent)
        {
            grandparent->left = node;
        }
        else
        {
            grandparent->right = node;
        }
    }
    node->parent = grandparent;
    if(node->parent == NULL)
    {
        o->root = node;
    }

    node->right = parent;
    parent->parent = node;

    return node;
}

static xmapnode * __xmapnode_rotate_left(xmap * o, xmapnode * parent)
{
    // parent && node always exist
    xmapnode * grandparent = parent->parent;
    xmapnode * node = parent->right;
    xmapnode * left = node->left;
    xmapnode * right = node->right;

    parent->right = left;
    if(left)
    {
        left->parent = parent;
    }

    if(grandparent)
    {
        if(grandparent->left == parent)
        {
            grandparent->left = node;
        }
        else
        {
            grandparent->right = node;
        }
    }
    node->parent = grandparent;
    if(node->parent == NULL)
    {
        o->root = node;
    }

    node->left = parent;
    parent->parent = node;

    return node;
    
}

static void __xmapnode_adjust_deletion(xmap * o, xmapnode * parent)
{
    xmapnode * node = NULL;
    xmapnode * sibling = NULL;
    xmapnode * grandparent = NULL;

    while(true)
    {
        /**
         * invariant
         * 
         * - node is black (or null - first insertion)
         * - node is not the root (parent is not null)
         */
        sibling = parent->right;
        if(sibling != node)
        {
            if(__xmapnode_is_red(sibling))
            {
                // node is black, sibling is red, parent is black
                // left rotate at parent
                grandparent = __xmapnode_rotate_left(o, parent);
                grandparent->color = xmapnode_black;
                parent->color = xmapnode_red;
                sibling = parent->right;
            }
            if(__xmapnode_is_black(sibling->right))
            {
                if(__xmapnode_is_black(sibling->left))
                {
                    // parent color (red or black)
                    // sibling color is black
                    // sibling's left & right color is black
                    sibling->color = xmapnode_red;
                    if(__xmapnode_is_red(parent))
                    {
                        parent->color = xmapnode_black;
                        break;
                    }
                    node = parent;
                    parent = node->parent;
                    if(parent)
                    {
                        continue;
                    }
                    break;
                }
                sibling = __xmapnode_rotate_right(o, sibling);
            }
            grandparent = __xmapnode_rotate_left(o, parent);
            grandparent->color = parent->color;
            parent->color = xmapnode_black;
            grandparent->right->color = xmapnode_black;
            break;
        }
        else
        {
            sibling = parent->left;
            if(__xmapnode_is_red(sibling))
            {
                // node is black, sibling is red, parent is black
                // left rotate at parent
                grandparent = __xmapnode_rotate_right(o, parent);
                grandparent->color = xmapnode_black;
                parent->color = xmapnode_red;
                sibling = parent->left;
            }
            if(__xmapnode_is_black(sibling->left))
            {
                if(__xmapnode_is_black(sibling->right))
                {
                    // parent color (red or black)
                    // sibling color is black
                    // sibling's left & right color is black
                    sibling->color = xmapnode_red;
                    if(__xmapnode_is_red(parent))
                    {
                        parent->color = xmapnode_black;
                        break;
                    }
                    node = parent;
                    parent = node->parent;
                    if(parent)
                    {
                        continue;
                    }
                    break;
                }
                sibling = __xmapnode_rotate_left(o, sibling);
            }
            grandparent = __xmapnode_rotate_right(o, parent);
            grandparent->color = parent->color;
            parent->color = xmapnode_black;
            grandparent->left->color = xmapnode_black;
            break;
        }
    }
}

static void __xmapnode_adjust_insertion(xmap * o, xmapnode * node)
{
    while(true)
    {
        // node is red
        xmapnode * parent = node->parent;
        if(parent == NULL)
        {
            node->color = xmapnode_black;
            break;
        }
        if(__xmapnode_is_black(parent))
        {
            break;
        }
        // parent is red, always exist parent 
        xmapnode * grandparent = parent->parent;
        xmapnode * uncle = grandparent->right;
        if(parent != uncle)
        {
            if(__xmapnode_is_red(uncle))
            {
                uncle->color       = xmapnode_black;
                parent->color      = xmapnode_black;
                grandparent->color = xmapnode_red;
                node               = grandparent;
                continue;
            }
            // uncle is black and parent is red, node is red
            if(__xmapnode_is_right(parent, node))
            {
                parent = __xmapnode_rotate_left(o, parent);
                node   = parent->left;
            }
            grandparent = __xmapnode_rotate_right(o, grandparent);
            grandparent->color = xmapnode_black;
            grandparent->right->color = xmapnode_red;
            break;
        }
        else
        {
            uncle = grandparent->left;
            if(__xmapnode_is_red(uncle))
            {
                uncle->color       = xmapnode_black;
                parent->color      = xmapnode_black;
                grandparent->color = xmapnode_red;
                node               = grandparent;
                continue;
            }
            // uncle is black and parent is red
            if(__xmapnode_is_left(parent, node))
            {
                parent = __xmapnode_rotate_right(o, parent);
                node   = parent->right;
            }

            grandparent = __xmapnode_rotate_left(o, grandparent);
            grandparent->color = xmapnode_black;
            grandparent->left->color = xmapnode_red;
            break;
        }
    }
}

xmap * xmapnew(void)
{
    xmap * o = (xmap * ) calloc(sizeof(xmap), 1);

    if(o == NULL)
    {
        fprintf(stdout, "fail to %s() caused by calloc (%d)\n", __func__, errno);
        return NULL;
    }

    o->type = xcontainer_type_map;

    return o;
}

xmap * xmapclr(xmap * o, void (*func)(variant))
{
    // fast remove & no balancing
    xmapnode * node = __xmap_minimum_node_get(o->root);

    while(node)
    {
        // left child is not exist && right child can exist
        xmapnode * parent = node->parent;
        xmapnode * right  = node->right;

        if(right)
        {
            right->parent = parent;
        }
        if(parent)
        {
            if(parent->right == node)
            {
                parent->right = right;
            }
            else
            {
                parent->left = right;
            }
        }
        if(func)
        {
            func(node->value);
        }
        free(node);
        node = right ? right : parent;
        node = __xmap_minimum_node_get(node);
        // for debug
        o->size = o->size -1;
    }
    // for debug
    if(o->size > 0)
    {
        fprintf(stdout, "clear size %ld\n", o->size);
        abort();
        return NULL;
    }
    
    o->root = NULL;
    o->size = 0;

    return o;
}

xmap * xmaprem(xmap * o, void (*func)(variant))
{
    if(o)
    {
        xmapclr(o, func);
        free(o);
    }
    return NULL;
}

xmap * xmapadd(xmap * o, variant v, void (*func)(variant))
{
    if(o == NULL)
    {
        fprintf(stdout, "fail to %s(%p, %lu) caused by o is null\n", __func__, o, v.u64);
        return NULL;
    }

    // INSERT BINARY SEARCH TREE
    xmapnode * node = o->root;
    int (*comp)(variant, variant) = o->comp ? o->comp : varcmp;

    while(node)
    {
        int compres = comp(node->value, v);

        if(compres > 0)
        {
            if(node->left == NULL)
            {
                node->left = __xmapnodenew(v, node);
                __xmapnode_adjust_insertion(o, node->left);
                o->size = o->size + 1;
                __xmap_validate(o);
                return o;
                // INSERT NEW VALUE
            }
            node = node->left;
        }
        else if(compres < 0)
        {
            if(node->right == NULL)
            {
                node->right = __xmapnodenew(v, node);
                __xmapnode_adjust_insertion(o, node->right);
                o->size = o->size + 1;
                __xmap_validate(o);
                return o;
                // INSERT NEW VALUE
            }
            node = node->right;
        }
        else
        {
            if(func)
            {
                func(node->value);
            }
            node->value = v;
            return o;
        }
    }

    o->root = __xmapnodenew(v, NULL);
    o->root->color = xmapnode_black;
    o->size = o->size + 1;
    __xmap_validate(o);

    return NULL;
}

xmap * xmapfor(xmap * o, void (*func)(variant))
{
    if(o == NULL || func == NULL)
    {
        return o;
    }
    
    xmapnode * node = __xmap_minimum_node_get(o->root);

    while(node)
    {
        func(node->value);
        node = __xmap_next_minumum_node_get(node);
    }

    return o;
}

xmapnode * xmapget(xmap * o, variant v)
{
    if(o == NULL)
    {
        fprintf(stdout, "fail to xmapget caused by o is null\n");
        return NULL;
    }

    xmapnode * node = o->root;
    int (*comp)(variant, variant) = o->comp ? o->comp : varcmp;

    while(node)
    {
        int compres = comp(node->value, v);

        if(compres > 0)
        {
            node = node->left;
        }
        else if(compres < 0)
        {
            node = node->right;
        }
        else
        {
            return node;
        }
    }
    return NULL;
}

xmap * xmapdel(xmap * o, variant v, void (*func)(variant))
{
    if(o)
    {
        xmapnode * node = xmapget(o, v);
        if(node)
        {
            // fprintf(stdout, "del %ld : %ld\n", v.u64, o->size);
            if(node->left && node->right)
            {
                xmapnode * successor = __xmap_minimum_node_get(node->right);
                xmapnode * parent = successor->parent;
                variant v = node->value;
                node->value = successor->value;

                if(successor == node->right)
                {
                    node->right = successor->right;
                    if(successor->right)
                    {
                        successor->right->parent = node;
                        successor->right->color = xmapnode_black;
                    }
                    else
                    {
                        // successor's parent always exist
                        if(successor->color == xmapnode_black)
                        {
                            __xmapnode_adjust_deletion(o, parent);
                        }
                    }
                }
                else if(successor->right)
                {
                    if(parent->left == successor)
                    {
                        parent->left = successor->right;
                    }
                    else
                    {
                        parent->right = successor->right;
                    }
                    successor->right->parent = parent;

                    // only one child, child is red, and success is always black
                    successor->right->color = xmapnode_black;
                }
                else
                {
                    // successor's children is not exist
                    if(parent->left == successor)
                    {
                        parent->left = NULL;
                    }
                    else
                    {
                        parent->right = NULL;
                    }

                    // successor's parent always exist
                    if(successor->color == xmapnode_black)
                    {
                        __xmapnode_adjust_deletion(o, parent);
                    }
                }

                if(func)
                {
                    func(v);
                }
                free(successor);
                o->size = o->size - 1;
            }
            else if(node->left)
            {
                // only one child, node is black, and child is red
                xmapnode * parent = node->parent;
                xmapnode * left = node->left;
                if(parent)
                {
                    if(parent->left == node)
                    {
                        parent->left = left;
                    }
                    else
                    {
                        parent->right = left;
                    }
                }
                else
                {
                    o->root = left;
                }
                left->parent = parent;

                left->color = xmapnode_black;

                if(func)
                {
                    func(node->value);
                }
                free(node);
                o->size = o->size - 1;
            }
            else if(node->right)
            {
                // only one child, node is black, and child is red
                xmapnode * parent = node->parent;
                xmapnode * right = node->right;
                if(parent)
                {
                    if(parent->left == node)
                    {
                        parent->left = right;
                    }
                    else
                    {
                        parent->right = right;
                    }
                }
                else
                {
                    o->root = right;
                }
                right->parent = parent;
                right->color = xmapnode_black;

                if(func)
                {
                    func(node->value);
                }
                free(node);
                o->size = o->size - 1;
            }
            else
            {
                xmapnode * parent = node->parent;
                if(parent)
                {
                    if(parent->left == node)
                    {
                        parent->left = NULL;
                    }
                    else
                    {
                        parent->right = NULL;
                    }
                }
                if(node->color == xmapnode_black)
                {
                    __xmapnode_adjust_deletion(o, parent);
                }

                if(func)
                {
                    func(node->value);
                }
                free(node);
                o->size = o->size - 1;
            }
            __xmap_validate(o);
        }
    }

    return o;
}