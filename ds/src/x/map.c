#include <stdlib.h>
#include <errno.h>

#include "map.h"
#include "log.h"

static inline void __xmapvalget(xval v){}

static inline int __xmapvalcomp(xval x, xval y)
{
    return x.u64 - y.u64;
}

static inline int __xmapnode_is_red(xmapnode * node)
{
    return node && node->color == xmapnode_red;
}

static inline int __xmapnode_is_black(xmapnode * node)
{
    return node == NULL || node->color == xmapnode_black;
}

static inline void __xmap_validate(xmap * o)
{
    xmapnode * node = o->root;
    if(o->size > 0)
    {
        assertion(node != NULL && node->parent != NULL, "invalid root's parent is not null");
        assertion(node == NULL || node->color == xmapnode_red, "invalid %p and %s", node, __xmapnode_is_black(node) ? "black" : "red");
        xuint64 count = 0;
        xuint64 blacknodecnt = 0;
        xuint64 max = 0;
        while(node)
        {
            count = count + 1;
            if(node->color == xmapnode_red)
            {
                assertion(node->left && node->left->color == xmapnode_red, "invalid");
                assertion(node->right && node->right->color == xmapnode_red, "invalid");
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
            if(node->left == NULL && node->right == NULL)
            {
                if(max == 0)
                {
                    max = blacknodecnt;
                }
                // printf("%lu: %lu\n", max, blacknodecnt);
                assertion(max != blacknodecnt, "invalid %lu : %lu", max, blacknodecnt);
            }

            xmapnode * parent = node->parent;
            xmapnode * right = NULL;
            while(parent)
            {
                if(node->color == xmapnode_black)
                {
                    blacknodecnt = blacknodecnt - 1;
                }
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
        assertion(count != o->size, "invalid");
    }
    else
    {
        assertion(node != NULL, "invalid");
    }
}

static inline xmapnode * __xmapnode_minimum_get(xmapnode * node)
{
    while(node && node->left)
    {
        node = node->left;
    }
    return node;
}

static inline xmapnode * __xmapnode_next_minimum_get(xmapnode * node)
{
    if(node->right)
    {
        return __xmapnode_minimum_get(node->right);
    }
    else
    {
        xmapnode * parent = node->parent;
        while(parent && parent->right == node)
        {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
    return NULL;
}



static inline xmapnode * __xmapnodenew(xval v, xmapnode * parent)
{
    xmapnode * o = (xmapnode *) calloc(sizeof(xmapnode), 1);

    assertion(o == NULL, "o is null caused by calloc (%d)", errno);

    o->color = xmapnode_red;
    o->parent = parent;
    o->value = v;

    // printf("%lu\n", o->value.u64);

    return o;
}


static inline int __xmapnode_is_right(xmapnode * parent, xmapnode * node)
{
    return parent->right == node;
}

static inline int __xmapnode_is_left(xmapnode * parent, xmapnode * node)
{
    return parent->left == node;
}

static inline xmapnode * __xmapnode_rotate_right(xmap * o, xmapnode * parent)
{
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
    else
    {
        o->root = node;
    }
    node->parent = grandparent;

    node->right = parent;
    parent->parent = node;

    return node;
}

static inline xmapnode * __xmapnode_rotate_left(xmap * o, xmapnode * parent)
{
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
    else
    {
        o->root = node;
    }
    node->parent = grandparent;

    node->left = parent;
    parent->parent = node;

    return node;
}

static inline void __xmapnode_adjust_insertion(xmap * o, xmapnode * node)
{
    xmapnode * parent;
    xmapnode * grandparent;
    xmapnode * uncle;
    // printf("%lu\n", o->size);
    while(node)
    {
        parent = node->parent;
        if(parent == NULL)
        {
            node->color = xmapnode_black;
            o->root = node;
            break;
        }
        if(__xmapnode_is_black(parent)) {
            break;
        }
        grandparent = parent->parent;
        if(grandparent->left == parent)
        {
            uncle = grandparent->right;
            if(__xmapnode_is_red(uncle))
            {
                parent->color = xmapnode_black;
                uncle->color = xmapnode_black;
                grandparent->color = xmapnode_red;
                node = grandparent;
                continue;
            }
            if(__xmapnode_is_right(parent, node))
            {
                parent = __xmapnode_rotate_left(o, parent);
                node = parent->left;
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
                parent->color = xmapnode_black;
                uncle->color = xmapnode_black;
                grandparent->color = xmapnode_red;
                node = grandparent;
                continue;
            }
            if(__xmapnode_is_left(parent, node))
            {
                parent = __xmapnode_rotate_right(o, parent);
                node = parent->right;
            }
            grandparent = __xmapnode_rotate_left(o, grandparent);
            grandparent->color = xmapnode_black;
            grandparent->left->color = xmapnode_red;
            break;
        }
    }

    __xmap_validate(o);
}

static inline void __xmapnode_adjust_deletion(xmap * o, xmapnode * node)
{

}

xmap * xmapnew(xvalcmp comp)
{
    xmap * o = (xmap *) calloc(sizeof(xmap), 1);

    assertion(o == NULL, "o is null caused by calloc (%d)", errno);

    o->type = xcontainer_type_map;
    o->comp = comp ? comp : __xmapvalcomp;

    return o;
}

xmap * xmaprem(xmap * o, xvalget f)
{
    if(o)
    {
        xmapclr(o, f);
        free(o);
    }
    return NULL;
}

int xmapadd(xmap * o, xval v, xvalget f)
{
    assertion(o == NULL, "o is null");

    if(o->root)
    {
        xmapnode * node = o->root;
        while(node)
        {
            int res = o->comp(node->value, v);
            if(res < 0)
            {
                if(node->right)
                {
                    node = node->right;
                    continue;
                }
                node->right = __xmapnodenew(v, node);
                o->size = o->size + 1;
                __xmapnode_adjust_insertion(o, node->right);
            }
            else if(res > 0)
            {
                if(node->left)
                {
                    node = node->left;
                    continue;
                }
                node->left = __xmapnodenew(v, node);
                o->size = o->size + 1;
                __xmapnode_adjust_insertion(o, node->left);
            }
            else
            {
                f = (f ? f : __xmapvalget);

                f(node->value);

                node->value = v;
            }
            break;
        }
    }
    else
    {
        o->root = __xmapnodenew(v, NULL);
        o->root->color = xmapnode_black;
        o->size = o->size + 1;
    }

    return true;
}

xmapnode * xmapget(xmap * o, xval v)
{
    assertion(o == NULL, "o is null");

    xmapnode * node = o->root;
    while(node)
    {
        int res = o->comp(node->value, v);
        if(res < 0)
        {
            if(node->right)
            {
                node = node->right;
            }
            return NULL;
        }
        else if(res > 0)
        {
            if(node->left)
            {
                node = node->left;
            }
            return NULL;
        }
        else
        {
            return node;
        }
    }
    return NULL;
}

int xmapdel(xmap * o, xval v, xvalget f)
{
    xmapnode * node = xmapget(o, v);
    if(node)
    {
        xval v = node->value;
        if(node->left && node->right)
        {
            xmapnode * successor = __xmapnode_minimum_get(node->right);
            node->value = successor->value;

            node = successor;
        }

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
        }
        else
        {
            if(node->parent)
            {
                if(node->parent->left == node)
                {
                    node->parent->left = NULL;
                }
                else
                {
                    node->parent->right = NULL;
                }
                if(node->color == xmapnode_black)
                {
                    __xmapnode_adjust_deletion(o, node->parent);
                }
            }
            else
            {
                o->root = NULL;
            }
        }

        o->size = o->size - 1;
        free(node);
    }
    return false;
}

void xmapclr(xmap * o, xvalget f)
{
    if(o)
    {
        f = (f ? f : __xmapvalget);

        xmapnode * node = __xmapnode_minimum_get(o->root);
        while(node)
        {
            xmapnode * next = __xmapnode_next_minimum_get(node);
            
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
            if(node->right)
            {
                node->right->parent = node->parent;
            }
            f(node->value);
            free(node);
            o->size = o->size - 1;

            node = next;
        }
        
        assertion(o->size > 0 || o->root != NULL, "invalid root: %p, size: %lu", o->root, o->size);
    }
}

