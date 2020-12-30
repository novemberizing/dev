#ifndef   __X__SET__HH__
#define   __X__SET__HH__

#include <x/single.hh>
#include <x/collection.hh>
#include <x/node.hh>

namespace x
{
    template <typename K, typename TUPLE = x::single<K> >
    class set : public x::collection<TUPLE>
    {
    protected:  static const x::uint32 BLACK = 0;
    protected:  static const x::uint32 RED = 1;
    protected:  static const x::uint32 LEFT = 0;
    protected:  static const x::uint32 RIGHT = 1;
    protected:  class node : public x::node
                {
                protected:  x::uint32 __color;
                protected:  typename x::set<K, TUPLE>::node * __parent;
                protected:  typename x::set<K, TUPLE>::node * __left;
                protected:  typename x::set<K, TUPLE>::node * __right;
                protected:  TUPLE __item;
                public:     inline typename x::set<K, TUPLE>::node * minimum()
                            {
                                typename x::set<K, TUPLE>::node * n = this;
                                while(n && n->__left)
                                {
                                    n = n->__left;
                                }
                                return n;
                            }
                public:     inline const typename x::set<K, TUPLE>::node * minimum() const
                            {
                                const typename x::set<K, TUPLE>::node * n = this;
                                while(n && n->__left)
                                {
                                    n = n->__left;
                                }
                                return n;
                            }
                public:     inline typename x::set<K, TUPLE>::node * maximum() const
                            {
                                typename x::set<K, TUPLE>::node * n = this;
                                while(n && n->__right)
                                {
                                    n = n->__right;
                                }
                                return n;
                            }
                public:     inline typename x::set<K, TUPLE>::node * next()
                            {
                                if(__right)
                                {
                                    return __right->minimum();
                                }
                                else if(__parent)
                                {
                                    typename x::set<K, TUPLE>::node * n = this;
                                    while(n && n->__parent && n->__parent->__right == n)
                                    {
                                        n = n->__parent;
                                    }
                                    return n ? n->__parent : nullptr;
                                }
                                else
                                {
                                    return nullptr;
                                }
                            }
                public:     inline const typename x::set<K, TUPLE>::node * next() const
                            {
                                if(__right)
                                {
                                    return __right->minimum();
                                }
                                else if(__parent)
                                {
                                    const typename x::set<K, TUPLE>::node * n = this;
                                    while(n && n->__parent && n->__parent->__right == n)
                                    {
                                        n = n->__parent;
                                    }
                                    return n ? n->__parent : nullptr;
                                }
                                else
                                {
                                    return nullptr;
                                }
                            }
                public:     inline typename x::set<K, TUPLE>::node * grandparent() const
                            {
                                if(__parent)
                                {
                                    return __parent->__parent;
                                }
                                return nullptr;
                            }
                public:     inline typename x::set<K, TUPLE>::node * sibling() const
                            {
                                if(__parent)
                                {
                                    if(__parent->__left == this)
                                    {
                                        return __parent->right;
                                    }
                                    else
                                    {
                                        return __parent->__left;
                                    }
                                }
                                return nullptr;
                            }
                public:     inline typename x::set<K, TUPLE>::node * uncle() const
                            {
                                typename x::set<K, TUPLE>::node * grandparent = __parent ? __parent->__parent : nullptr;
                                if(grandparent)
                                {
                                    if(grandparent->__left == __parent)
                                    {
                                        return grandparent->__right;
                                    }
                                    else
                                    {
                                        return grandparent->__left;
                                    }
                                }
                                return nullptr;
                            }
                public:     inline void color(x::uint32 v)
                            {
                                __color = v;
                            }
                public:     inline x::uint32 color() const
                            {
                                return __color;
                            }
                public:     inline void parent(typename x::set<K, TUPLE>::node * n)
                            {
                                __parent = n;
                            }
                public:     inline typename x::set<K, TUPLE>::node * parent() const
                            {
                                return __parent;
                            }
                public:     inline void left(typename x::set<K, TUPLE>::node * n)
                            {
                                __left = n;
                            }
                public:     inline typename x::set<K, TUPLE>::node * left() const
                            {
                                return __left;
                            }
                public:     inline void right(typename x::set<K, TUPLE>::node * n)
                            {
                                __right = n;
                            }
                public:     inline typename x::set<K, TUPLE>::node * right() const
                            {
                                return __right;
                            }
                public:     inline const TUPLE & item() const
                            {
                                return __item;
                            }
                public:     inline TUPLE & item()
                            {
                                return __item;
                            }
                public:     inline void item(const TUPLE & item)
                            {
                                __item = item;
                            }
                public:     inline void item(TUPLE && item)
                            {
                                __item = x::move(item);
                            }
                public:     inline const K & key() const
                            {
                                return __item.first();
                            }
                public:     typename x::set<K, TUPLE>::node & operator=(const typename x::set<K, TUPLE>::node & o) = delete;
                public:     typename x::set<K, TUPLE>::node & operator=(typename x::set<K, TUPLE>::node && o) noexcept = delete;
                public:     node(const TUPLE & item)
                            :   x::node(),
                                __color(x::set<K, TUPLE>::RED),
                                __parent(nullptr),
                                __left(nullptr),
                                __right(nullptr),
                                __item(item)
                            {
                            }
                public:     node(TUPLE && item)
                            :   x::node(),
                                __color(x::set<K, TUPLE>::RED),
                                __parent(nullptr),
                                __left(nullptr),
                                __right(nullptr),
                                __item(x::move(item))
                            {
                            }
                public:     node(const TUPLE & item, typename x::set<K, TUPLE>::node * parent)
                            :   x::node(),
                                __color(x::set<K, TUPLE>::RED),
                                __parent(parent),
                                __left(nullptr),
                                __right(nullptr),
                                __item(item)
                            {
                            }
                public:     node(TUPLE && item, typename x::set<K, TUPLE>::node * parent)
                            :   x::node(),
                                __color(x::set<K, TUPLE>::RED),
                                __parent(parent),
                                __left(nullptr),
                                __right(nullptr),
                                __item(x::move(item))
                            {
                            }
                public:     node() = delete;
                public:     node(const typename x::set<K, TUPLE>::node & o) = delete;
                public:     node(typename x::set<K, TUPLE>::node && o) noexcept = delete;
                public:     ~node() override
                            {
                                __color = x::set<K, TUPLE>::BLACK;
                                __parent = nullptr;
                                __left = nullptr;
                                __right = nullptr;
                            }
                };
    protected:  typename x::set<K, TUPLE>::node * __root;
    protected:  x::uint64 __size;
    protected:  static typename x::set<K, TUPLE>::node * minimum(typename x::set<K, TUPLE>::node * n)
                {
                    return n ? n->minimum() : nullptr;
                }
    protected:  static x::uint32 color(typename x::set<K, TUPLE>::node * n)
                {
                    return n ? n->color() : x::set<K, TUPLE>::BLACK;
                }
    protected:  static void color(typename x::set<K, TUPLE>::node * n, x::uint32 color)
                {
                    if(n)
                    {
                        n->color(color);
                    }
                }
    protected:  static typename x::set<K, TUPLE>::node * left(typename x::set<K, TUPLE>::node * n)
                {
                    return n ? n->left() : nullptr;
                }
    protected:  static void left(typename x::set<K, TUPLE>::node * n, typename x::set<K, TUPLE>::node * left)
                {
                    if(n)
                    {
                        n->left(left);
                    }
                }
    protected:  static typename x::set<K, TUPLE>::node * right(typename x::set<K, TUPLE>::node * n)
                {
                    return n ? n->right() : nullptr;
                }
    protected:  static void right(typename x::set<K, TUPLE>::node * n, typename x::set<K, TUPLE>::node * right)
                {
                    if(n)
                    {
                        n->right(right);
                    }
                }
    protected:  static typename x::set<K, TUPLE>::node * parent(typename x::set<K, TUPLE>::node * n)
                {
                    return n ? n->parent() : nullptr;
                }
    protected:  static void parent(typename x::set<K, TUPLE>::node * n, typename x::set<K, TUPLE>::node * parent)
                {
                    if(n)
                    {
                        n->parent(parent);
                    }
                }
    protected:  inline void rotate(typename x::set<K, TUPLE>::node * n, x::uint32 direction)
                {
                    if(direction == LEFT)
                    {
                        typename x::set<K, TUPLE>::node * right = n->right();
                        if(n->parent() != nullptr)
                        {
                            if(n->parent()->left() == n)
                            {
                                n->parent()->left(right);
                            }
                            else
                            {
                                n->parent()->right(right);
                            }
                        }
                        else
                        {
                            this->__root = n->right();
                        }
                        right->parent(n->parent());
                        n->right(right->left());
                        if(right->left())
                        {
                            right->left()->parent(n);
                        }
                        n->parent(right);
                        right->left(n);
                    }
                    else if(direction == RIGHT)
                    {
                        typename x::set<K, TUPLE>::node * left = n->left();
                        if(n->parent() != nullptr)
                        {
                            if(n->parent()->left() == n)
                            {
                                n->parent()->left(left);
                            }
                            else
                            {
                                n->parent()->right(left);
                            }
                        }
                        else
                        {
                            this->__root = n->left();
                        }
                        left->parent(n->parent());
                        n->left(left->right());
                        if(left->right())
                        {
                            left->right()->parent(n);
                        }
                        left->right(n);
                        n->parent(left);
                    }
                    else
                    {
                        exceptional();
                    }
                }
    protected:  inline void insertion(typename x::set<K, TUPLE>::node * n)
                {
                    while(n && set<K, TUPLE>::color(n->parent()) == RED)
                    {
                        typename x::set<K, TUPLE>::node * parent = n->parent();
                        typename x::set<K, TUPLE>::node * grandparent = n->grandparent();
                        if(grandparent)
                        {
                            typename x::set<K, TUPLE>::node * uncle = (grandparent->left() == n->parent() ? grandparent->right() :  grandparent->left());
                            if(x::set<K, TUPLE>::color(uncle) == RED)
                            {
                                grandparent->color(RED);
                                uncle->color(BLACK);
                                parent->color(BLACK);
                                n = grandparent;
                                continue;
                            }
                            // uncle's color is black or null
                            if(n == parent->left())
                            {
                                if(grandparent->right() == parent)
                                {
                                    this->rotate(parent, RIGHT);
                                    n = parent;
                                    parent = n->parent();
                                    grandparent = parent->parent();
                                }

                            }
                            else
                            {
                                if(grandparent->left() == parent)
                                {
                                    this->rotate(parent, LEFT);
                                    n = parent;
                                    parent = n->parent();
                                    grandparent = parent->parent();
                                }
                            }
                            if(n == parent->left())
                            {
                                if(grandparent->left() == parent)
                                {
                                    grandparent->color(RED);
                                    parent->color(BLACK);
                                    this->rotate(grandparent, RIGHT);
                                    n = grandparent;
                                    continue;
                                }
                            }
                            else
                            {
                                if(grandparent->right() == parent)
                                {
                                    grandparent->color(RED);
                                    parent->color(BLACK);
                                    this->rotate(grandparent, LEFT);
                                    n = grandparent;
                                    continue;
                                }
                            }
                        }
                        break;
                    }
                    this->__root->color(BLACK);
                }
    protected:  inline void deletion(typename x::set<K, TUPLE>::node * parent)
                {
                    typename x::set<K, TUPLE>::node * n = nullptr;
                    while(x::set<K, TUPLE>::color(n) == BLACK && parent != nullptr)
                    {
                        typename x::set<K, TUPLE>::node * sibling = parent->right();
                        if(n != sibling)
                        {
                            if(x::set<K, TUPLE>::color(sibling) == RED)
                            {
                                x::uint32 color = parent->color();
                                parent->color(sibling->color());
                                sibling->color(color);
                                this->rotate(parent, LEFT);
                                sibling = parent->right();
                            }
                            if(x::set<K, TUPLE>::color(sibling->right()) == BLACK)
                            {
                                if(x::set<K, TUPLE>::color(sibling->left()) == BLACK)
                                {
                                    sibling->color(RED);
                                    if(x::set<K, TUPLE>::color(parent) == BLACK)
                                    {
                                        n = parent;
                                        parent = n->parent();
                                        continue;
                                    }
                                    else
                                    {
                                        parent->color(BLACK);
                                        break;
                                    }
                                }
                                sibling->color(RED);
                                x::set<K, TUPLE>::color(sibling->left(), BLACK);
                                this->rotate(sibling, RIGHT);
                                sibling = parent->right();
                            }
                            sibling->color(parent->color());
                            parent->color(BLACK);
                            x::set<K, TUPLE>::color(sibling->right(), BLACK);
                            this->rotate(parent, LEFT);
                            break;
                        }
                        else
                        {
                            sibling = parent->left();
                            if(x::set<K, TUPLE>::color(sibling) == RED)
                            {
                                x::uint32 color = parent->color();
                                parent->color(sibling->color());
                                sibling->color(color);
                                this->rotate(parent, RIGHT);
                                sibling = parent->left();
                            }
                            if(x::set<K, TUPLE>::color(sibling->left()) == BLACK)
                            {
                                if(x::set<K, TUPLE>::color(sibling->right()) == BLACK)
                                {
                                    sibling->color(RED);
                                    if(x::set<K, TUPLE>::color(parent) == BLACK)
                                    {
                                        n = parent;
                                        parent = n->parent();
                                        continue;
                                    }
                                    else
                                    {
                                        parent->color(BLACK);
                                        break;
                                    }
                                }
                                sibling->color(RED);
                                x::set<K, TUPLE>::color(sibling->right(), BLACK);
                                this->rotate(sibling, LEFT);
                                sibling = parent->left();
                            }
                            sibling->color(parent->color());
                            parent->color(BLACK);
                            x::set<K, TUPLE>::color(sibling->left(), BLACK);
                            this->rotate(parent, RIGHT);
                            break;
                        }
                    }
                    if(this->__root)
                    {
                        this->__root->color(BLACK);
                    }
                }
    protected:  inline typename x::set<K, TUPLE>::node * find(const K & key) const
                {
                    typename x::set<K, TUPLE>::node * current = this->__root;
                    while(current)
                    {
                        if(current->key() == key)
                        {
                            return current;
                        }
                        else if(key < current->key())
                        {
                            current = current->left();
                        }
                        else
                        {
                            current = current->right();
                        }
                    }
                    return nullptr;
                }
    protected:  inline typename x::set<K, TUPLE>::node * insert(const TUPLE & item)
                {
                    typename x::set<K, TUPLE>::node * current = this->__root;
                    while(current)
                    {
                        if(current->key() == item.first())
                        {
                            current->item(item);
                            return current;
                        }
                        else if(item.first() < current->key())
                        {
                            if(current->left())
                            {
                                current = current->left();
                                continue;
                            }
                            typename x::set<K, TUPLE>::node * n = new typename x::set<K, TUPLE>::node(item, current);
                            current->left(n);
                            this->__size = this->__size + 1;
                            insertion(n);
                            return n;
                        }
                        else
                        {
                            if(current->right())
                            {
                                current = current->right();
                                continue;
                            }
                            typename x::set<K, TUPLE>::node * n = new typename x::set<K, TUPLE>::node(item, current);
                            current->right(n);
                            this->__size = this->__size + 1;
                            insertion(n);
                            return n;
                        }
                    }
                    this->__root = new typename x::set<K, TUPLE>::node(item);
                    this->__root->color(BLACK);
                    this->__size = this->__size + 1;
                }
    protected:  inline typename x::set<K, TUPLE>::node * insert(TUPLE && item)
                {
                    typename x::set<K, TUPLE>::node * current = this->__root;
                    while(current)
                    {
                        if(current->key() == item.first())
                        {
                            current->item(x::move(item));
                            return current;
                        }
                        else if(item.first() < current->key())
                        {
                            if(current->left())
                            {
                                current = current->left();
                                continue;
                            }
                            typename x::set<K, TUPLE>::node * n = new typename x::set<K, TUPLE>::node(x::move(item), current);
                            current->left(n);
                            this->__size = this->__size + 1;
                            insertion(n);
                            return n;
                        }
                        else
                        {
                            if(current->right())
                            {
                                current = current->right();
                                continue;
                            }
                            typename x::set<K, TUPLE>::node * n = new typename x::set<K, TUPLE>::node(x::move(item), current);
                            current->right(n);
                            this->__size = this->__size + 1;
                            insertion(n);
                            return n;
                        }
                    }
                    this->__root = new typename x::set<K, TUPLE>::node(x::move(item));
                    this->__root->color(BLACK);
                    this->__size = this->__size + 1;
                }
    protected:  inline typename x::set<K, TUPLE>::node * remove(typename x::set<K, TUPLE>::node * n)
                {
                    if(n)
                    {
                        if(n->left() == NULL)
                        {
                            typename x::set<K, TUPLE>::node * parent = n->parent();
                            typename x::set<K, TUPLE>::node * right = n->right();
                            if(parent)
                            {
                                if(parent->left() == n)
                                {
                                    parent->left(right);
                                }
                                else
                                {
                                    parent->right(right);
                                }
                            }
                            else
                            {
                                this->__root = right;
                            }
                            if(right)
                            {
                                right->parent(parent);
                            }
                            if(n->color() == BLACK)
                            {
                                if(color(right) == BLACK)
                                {
                                    deletion(parent);
                                }
                                else
                                {
                                    right->color(BLACK);
                                }
                            }
                        }
                        else if(n->right() == NULL)
                        {
                            typename x::set<K, TUPLE>::node * parent = n->parent();
                            typename x::set<K, TUPLE>::node * left = n->left();
                            if(parent)
                            {
                                if(parent->left() == n)
                                {
                                    parent->left(left);
                                }
                                else
                                {
                                    parent->right(left);
                                }
                            }
                            else
                            {
                                this->__root = left;
                            }
                            if(left)
                            {
                                left->parent(parent);
                            }
                            if(n->color() == BLACK)
                            {
                                if(color(left) == BLACK)
                                {
                                    deletion(parent);
                                }
                                else
                                {
                                    left->color(BLACK);
                                }
                            }
                        }
                        else
                        {
                            typename x::set<K, TUPLE>::node * minimum = n->minimum();
                            typename x::set<K, TUPLE>::node * parent = minimum->parent();
                            x::uint32 color = minimum->color();
                            typename x::set<K, TUPLE>::node * right = minimum->right();

                            if(x::set<K, TUPLE>::left(minimum->parent()) == minimum)
                            {
                                x::set<K, TUPLE>::left(minimum->parent(), right);
                            }
                            else
                            {
                                x::set<K, TUPLE>::right(minimum->parent(), right);
                            }

                            x::set<K, TUPLE>::parent(minimum->right(), parent);

                            if(n->parent())
                            {
                                if(x::set<K, TUPLE>::left(n->parent()) == n)
                                {
                                    x::set<K, TUPLE>::left(n->parent(), minimum);
                                }
                                else
                                {
                                    x::set<K, TUPLE>::right(n->parent(), minimum);
                                }
                            }
                            else
                            {
                                this->__root = minimum;
                            }
                            minimum->parent(n->parent());
                            minimum->left(n->left());
                            x::set<K, TUPLE>::parent(minimum->left(), minimum);
                            minimum->right(n->right());
                            x::set<K, TUPLE>::parent(minimum->right(), minimum);
                            minimum->color(n->color());
                            if(color == BLACK)
                            {
                                if(x::set<K, TUPLE>::color(right) == RED)
                                {
                                    right->color(BLACK);
                                }
                                else
                                {
                                    deletion(parent == n ? minimum : parent);
                                }
                            }
                        }
                    }
                    return n;
                }
    protected:  inline typename x::set<K, TUPLE>::node * remove(const K & key)
                {
                    return remove(find(key));
                }
    public:     virtual x::boolean del(const K & key)
                {
                    typename x::set<K, TUPLE>::node * n = remove(key);
                    if(n)
                    {
                        __size = __size - 1;
                        delete n;
                        return true;
                    }
                    return false;
                }
    public:     virtual x::boolean exist(const K & key)
                {
                    return find(key) != nullptr;
                }
    public:     virtual void add(const TUPLE & item)
                {
                    insert(item);
                }
    public:     virtual void add(TUPLE && item)
                {
                    insert(x::move(item));
                }
    public:     virtual void each(x::function<void (const K &)> f) const
                {
                    if(f)
                    {
                        node * current = __root->minimum();
                        while(current)
                        {
                            f(current->key());
                            current = current->next();
                        }
                    }
                }
    public:     void each(x::function<void (const TUPLE &)> f) const override
                {
                    if(f)
                    {
                        node * current = __root->minimum();
                        while(current)
                        {
                            f(current->item());
                            current = current->next();
                        }
                    }
                }
    protected:  void each(x::function<void (TUPLE &)> f) override
                {
                    if(f)
                    {
                        node * current = __root->minimum();
                        while(current)
                        {
                            f(current->item());
                            current = current->next();
                        }
                    }
                }
    public:     void clear(x::function<void (TUPLE &&)> f) override
                {
                    typename x::set<K, TUPLE>::node * current = minimum(this->__root);
                    while(current)
                    {
                        typename x::set<K, TUPLE>::node * next = current->next();
                        typename x::set<K, TUPLE>::node * parent = current->parent();
                        typename x::set<K, TUPLE>::node * right = current->right();
                        if(parent)
                        {
                            parent->left(right);
                            if(right)
                            {
                                right->parent(parent);
                            }
                        }
                        else
                        {
                            this->__root = right;
                            if(right)
                            {
                                right->parent(nullptr);
                            }
                        }
                        if(f)
                        {
                            f(x::move(current->item()));
                        }
                        delete current;
                        this->__size = this->__size - 1;
                        current = next;
                    }
                }
    public:     void clear() override
                {
                    clear(nullptr);
                }
    public:     x::uint64 size() const override
                {
                    return __size;
                }
    public:     x::boolean empty() const override
                {
                    return __size == 0;
                }
    public:     x::set<K, TUPLE> & operator=(const x::initializer<K> & list)
                {
                    clear();
                    for(typename x::initializer<K>::iterator it = list.begin(); it != list.end(); ++it)
                    {
                        add(*it);
                    }
                    return *this;
                }
    public:     x::set<K, TUPLE> & operator=(const x::set<K, TUPLE> & o)
                {
                    if(&o != this)
                    {
                        clear();
                        typename x::set<K, TUPLE>::node * current = o.__root->minimum();
                        while(current)
                        {
                            add(current->item());
                            current = current->next();
                        }
                    }
                    return *this;
                }
    public:     x::set<K, TUPLE> & operator=(x::set<K, TUPLE> && o) noexcept
                {
                    if(&o != this)
                    {
                        clear();

                        __root = o.__root;
                        __size = o.__size;

                        o.__root = nullptr;
                        o.__size = 0;
                    }
                    return *this;
                }
    public:     set()
                :   x::collection<TUPLE>(),
                    __root(nullptr),
                    __size(0)
                {
                }
    public:     set(const x::set<K, TUPLE> & o)
                :   x::collection<TUPLE>(),
                    __root(nullptr),
                    __size(0)
                {
                    typename x::set<K, TUPLE>::node * current = o.__root->minimum();
                    while(current)
                    {
                        add(current->item());
                        current = current->next();
                    }
                }
    public:     set(x::set<K, TUPLE> && o) noexcept
                :   x::collection<TUPLE>(),
                    __root(o.__root),
                    __size(o.__size)
                {
                    o.__root = nullptr;
                    o.__size = 0;
                }
    public:     ~set() override
                {
                    clear();
                }
    };
}

#endif // __X__SET__HH__
