#ifndef   __X__SET__HH__
#define   __X__SET__HH__

#include <x/output/stream.hh>
#include <x/collection.hh>
#include <x/node.hh>
#include <x/single.hh>

namespace x
{
    template <typename K, typename TUPLE = single<K> >
    class set : public collection<TUPLE>
    {
    protected:  static const uint32 BLACK = 0;
    protected:  static const uint32 RED = 1;
    protected:  static const uint32 LEFT = 0;
    protected:  static const uint32 RIGHT = 1;
    protected:  class node : public x::node
                {
                protected:  uint32 __color;
                protected:  node * __parent;
                protected:  node * __left;
                protected:  node * __right;
                protected:  TUPLE __item;
                public:     node * next()
                            {
                                if(this->__right)
                                {
                                    return this->__right->minimum();
                                }
                                else if(this->__parent)
                                {
                                    node * n = this;
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
                public:     node * minimum()
                            {
                                node * n = this;
                                while(n && n->__left)
                                {
                                    n = n->__left;
                                }
                                return n;
                            }
                public:     node * maximum()
                            {
                                node * n = this;
                                while(n && n->__right)
                                {
                                    n = n->__right;
                                }
                                return n;
                            }
                public:     node * grandparent() const
                            {
                                if(this->__parent)
                                {
                                    return this->__parent->__parent;
                                }
                                return nullptr;
                            }
                public:     node * sibling() const
                            {
                                if(this->__parent)
                                {
                                    if(this->__parent->__left == this)
                                    {
                                        return this->__parent->__right;
                                    }
                                    else
                                    {
                                        return this->__parent->__left;
                                    }
                                }
                                return nullptr;
                            }
                public:     node * uncle() const
                            {
                                node * grandparent = this->grandparent();
                                if(grandparent)
                                {
                                    if(grandparent->__left == this->__parent)
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
                public:     uint32 color() const
                            {
                                return this->__color;
                            }
                public:     void color(uint32 value)
                            {
                                this->__color = value;
                            }
                public:     node * parent() const
                            {
                                return this->__parent;
                            }
                public:     void parent(node * n)
                            {
                                this->__parent = n;
                            }
                public:     node * left() const
                            {
                                return this->__left;
                            }
                public:     void left(node * n)
                            {
                                this->__left = n;
                            }
                public:     node * right() const
                            {
                                return this->__right;
                            }
                public:     void right(node * n)
                            {
                                this->__right = n;
                            }
                public:     const TUPLE & item() const
                            {
                                return this->__item;
                            }
                public:     TUPLE & item()
                            {
                                return this->__item;
                            }
                public:     void item(const TUPLE & item)
                            {
                                this->__item = item;
                            }
                public:     void item(TUPLE && item)
                            {
                                this->__item = x::move(item);
                            }
                public:     const K & key() const
                            {
                                return this->__item.first();
                            }
                public:     node & operator=(const node & o) = delete;
                public:     node & operator=(node && o) noexcept = delete;
                public:     node() = delete;
                public:     node(const node & o) = delete;
                public:     node(node && o) noexcept = delete;
                public:     node(const TUPLE & item) : __color(set<K, TUPLE>::RED), __parent(nullptr), __left(nullptr), __right(nullptr), __item(item)
                            {
                            }
                public:     node(TUPLE && item) : __color(set<K, TUPLE>::RED), __parent(nullptr), __left(nullptr), __right(nullptr), __item(x::move(item))
                            {
                            }
                public:     node(const TUPLE & item, node * parent) : __color(set<K, TUPLE>::RED), __parent(parent), __left(nullptr), __right(nullptr), __item(item)
                            {
                            }
                public:     node(TUPLE && item, node * parent) : __color(set<K, TUPLE>::RED), __parent(parent), __left(nullptr), __right(nullptr), __item(x::move(item))
                            {
                            }
                public:     ~node() override
                            {
                                this->__color = 0;
                                this->__parent = nullptr;
                                this->__left = nullptr;
                                this->__right = nullptr;
                            }
                };
    protected:  node * __root;
    protected:  uint64 __size;
    protected:  static node * minimum(node * n)
                {
                    return n ? n->minimum() : nullptr;
                }
    protected:  static uint32 color(node * n)
                {
                    return n ? n->color() : BLACK;
                }
    protected:  static void color(node * n, uint32 color)
                {
                    if(n)
                    {
                        n->color(color);
                    }
                }
    protected:  static node * left(node * n)
                {
                    return n ? n->left() : nullptr;
                }
    protected:  static void left(node * n, node * left)
                {
                    if(n)
                    {
                        n->left(left);
                    }
                }
    protected:  static node * right(node * n)
                {
                    return n ? n->right() : nullptr;
                }
    protected:  static void right(node * n, node * right)
                {
                    if(n)
                    {
                        n->right(right);
                    }
                }
    protected:  static node * parent(node * n)
                {
                    return n ? n->parent() : nullptr;
                }
    protected:  static void parent(node * n, node * parent)
                {
                    if(n)
                    {
                        n->parent(parent);
                    }
                }
    protected:  virtual void rotate(node * n, uint32 direction)
                {
                    if(direction == LEFT)
                    {
                        node * right = n->right();
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
                        node * left = n->left();
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
    protected:  void insertion(node * n)
                {
                    while(n && set<K, TUPLE>::color(n->parent()) == RED)
                    {
                        node * parent = n->parent();
                        node * grandparent = n->grandparent();
                        if(grandparent)
                        {
                            node * uncle = (grandparent->left() == n->parent() ? grandparent->right() :  grandparent->left());
                            if(set<K, TUPLE>::color(uncle) == RED)
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
    protected:  void deletion(node * parent)
                {
                    node * n = nullptr;
                    while(set<K, TUPLE>::color(n) == BLACK && parent != nullptr)
                    {
                        node * sibling = parent->right();
                        if(n != sibling)
                        {
                            if(set<K, TUPLE>::color(sibling) == RED)
                            {
                                uint32 color = parent->color();
                                parent->color(sibling->color());
                                sibling->color(color);
                                this->rotate(parent, LEFT);
                                sibling = parent->right();
                            }
                            if(set<K, TUPLE>::color(sibling->right()) == BLACK)
                            {
                                if(set<K, TUPLE>::color(sibling->left()) == BLACK)
                                {
                                    sibling->color(RED);
                                    if(set<K, TUPLE>::color(parent) == BLACK)
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
                                set<K, TUPLE>::color(sibling->left(), BLACK);
                                this->rotate(sibling, RIGHT);
                                sibling = parent->right();
                            }
                            sibling->color(parent->color());
                            parent->color(BLACK);
                            set<K, TUPLE>::color(sibling->right(), BLACK);
                            this->rotate(parent, LEFT);
                            break;
                        }
                        else
                        {
                            sibling = parent->left();
                            if(set<K, TUPLE>::color(sibling) == RED)
                            {
                                uint32 color = parent->color();
                                parent->color(sibling->color());
                                sibling->color(color);
                                this->rotate(parent, RIGHT);
                                sibling = parent->left();
                            }
                            if(set<K, TUPLE>::color(sibling->left()) == BLACK)
                            {
                                if(set<K, TUPLE>::color(sibling->right()) == BLACK)
                                {
                                    sibling->color(RED);
                                    if(set<K, TUPLE>::color(parent) == BLACK)
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
                                set<K, TUPLE>::color(sibling->right(), BLACK);
                                this->rotate(sibling, LEFT);
                                sibling = parent->left();
                            }
                            sibling->color(parent->color());
                            parent->color(BLACK);
                            set<K, TUPLE>::color(sibling->left(), BLACK);
                            this->rotate(parent, RIGHT);
                            break;
                        }
                    }
                    if(this->__root)
                    {
                        this->__root->color(BLACK);
                    }
                }
    protected:  node * find(const K & key) const
                {
                    node * current = this->__root;
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

    protected:  node * insert(const TUPLE & item)
                {
                    node * current = this->__root;
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
                            node * n = new node(item, current);
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
                            node * n = new node(item, current);
                            current->right(n);
                            this->__size = this->__size + 1;
                            insertion(n);
                            return n;
                        }
                    }
                    this->__root = new node(item);
                    this->__root->color(BLACK);
                    this->__size = this->__size + 1;
                }
    protected:  node * insert(TUPLE && item)
                {
                    node * current = this->__root;
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
                            node * n = new node(x::move(item), current);
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
                            node * n = new node(x::move(item), current);
                            current->right(n);
                            this->__size = this->__size + 1;
                            insertion(n);
                            return n;
                        }
                    }
                    this->__root = new node(x::move(item));
                    this->__root->color(BLACK);
                    this->__size = this->__size + 1;
                }
    public:     node * remove(node * n)
                {
                    if(n)
                    {
                        if(n->left() == NULL)
                        {
                            node * parent = n->parent();
                            node * right = n->right();
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
                            return nullptr;
                            node * parent = n->parent();
                            node * left = n->left();
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
                            node * minimum = n->minimum();
                            node * parent = minimum->parent();
                            uint32 color = minimum->color();
                            node * right = minimum->right();

                            if(set<K, TUPLE>::left(minimum->parent()) == minimum)
                            {
                                set<K, TUPLE>::left(minimum->parent(), right);
                            }
                            else
                            {
                                set<K, TUPLE>::right(minimum->parent(), right);
                            }

                            set<K, TUPLE>::parent(minimum->right(), parent);

                            if(n->parent())
                            {
                                if(set<K, TUPLE>::left(n->parent()) == n)
                                {
                                    set<K, TUPLE>::left(n->parent(), minimum);
                                }
                                else
                                {
                                    set<K, TUPLE>::right(n->parent(), minimum);
                                }
                            }
                            else
                            {
                                this->__root = minimum;
                            }
                            minimum->parent(n->parent());
                            minimum->left(n->left());
                            set<K, TUPLE>::parent(minimum->left(), minimum);
                            minimum->right(n->right());
                            set<K, TUPLE>::parent(minimum->right(), minimum);
                            minimum->color(n->color());
                            if(color == BLACK)
                            {
                                if(set<K, TUPLE>::color(right) == RED)
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
    public:     node * remove(const K & key)
                {
                    return remove(find(key));
                }
    public:     virtual bool del(const K & key)
                {
                    node * n = remove(key);
                    if(n)
                    {
                        this->__size = this->__size - 1;
                        delete n;
                        return true;
                    }
                    return false;
                }
    public:     virtual bool exist(const K & key)
                {
                    return find(key) != nullptr;
                }
    public:     void add(const TUPLE & item) override
                {
                    insert(item);
                }
    public:     void add(TUPLE && item) override
                {
                    insert(x::move(item));
                }
    public:     uint64 size() const override
                {
                    return this->__size;
                }
    public:     x::boolean empty() const override
                {
                    return this->__root == nullptr || this->__size == 0L;
                }
    public:     void clear() override
                {
                    clear(nullptr);
                }
    public:     void clear(std::function<void (TUPLE &&)> f) override
                {
                    node * current = minimum(this->__root);
                    while(current)
                    {
                        node * next = current->next();
                        node * parent = current->parent();
                        node * right = current->right();
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
    public:     void each(std::function<void (const TUPLE &)> f) const override
                {
                    if(f)
                    {
                        node * current = this->__root->minimum();
                        while(current)
                        {
                            f(current->item());
                            current = current->next();
                        }
                    }
                }
    public:     set<K, TUPLE> & operator=(const std::initializer_list<K> & list)
                {
                    this->clear();
                    for(typename std::initializer_list<K>::iterator it = list.begin(); it != list.end(); ++it)
                    {
                        this->add(*it);
                    }
                    return *this;
                }
    public:     set<K, TUPLE> & operator=(const set<K, TUPLE> & o)
                {
                    if(&o != this)
                    {
                        this->clear();
                        node * current = o.__root->minimum();
                        while(current)
                        {
                            this->add(current->item());
                            current = current->next();
                        }
                    }
                    return *this;
                }
    public:     set<K, TUPLE> & operator=(set<K, TUPLE> && o) noexcept
                {
                    if(&o != this)
                    {
                        this->clear();

                        this->__root = o.__root;
                        this->__size = o.__size;

                        o.__root = nullptr;
                        o.__size = 0L;
                    }
                    return *this;
                }
    public:     set(const std::initializer_list<K> & list) : __root(nullptr), __size(0L)
                {
                    for(typename std::initializer_list<K>::iterator it = list.begin(); it != list.end(); ++it)
                    {
                        this->add(*it);
                    }
                }
    public:     set() : __root(nullptr), __size(0L)
                {
                }
    public:     set(const set<K, TUPLE> & o) : __root(nullptr), __size(0L)
                {
                    o.each([this](const TUPLE & tuple){ this->add(tuple); });
                }
    public:     set(set<K, TUPLE> && o) noexcept : __root(o.__root), __size(o.__size)
                {
                    o.__root = nullptr;
                    o.__size = 0L;
                }
    public:     ~set() override
                {
                    this->clear();
                }
    public:     friend x::output::stream & operator<<(x::output::stream & os, const set<K, TUPLE> & o)
                {
                    if(o.__root != nullptr && o.__size > 0)
                    {
                        os << "[";
                        node * current = o.__root->minimum();
                        while(current)
                        {
                            os << current->key();
                            current = current->next();
                            if(current)
                            {
                                os << ",";
                            }
                        }
                        os << "]";
                    }
                    else
                    {
                        os << "null";
                    }
                    return os;
                }
    };
}

#endif // __X__SET__HH__
