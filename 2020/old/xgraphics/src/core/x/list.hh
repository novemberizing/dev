#ifndef   __X__LIST__HH__
#define   __X__LIST__HH__

#include <x/collection.hh>
#include <x/node.hh>

namespace x
{
    template <typename T>
    class list : public x::collection<T>
    {
    protected:  class node : public x::node
                {
                protected:  T __value;
                protected:  typename x::list<T>::node * __previous;
                protected:  typename x::list<T>::node * __next;
                public:     inline const typename x::list<T>::node * previous() const
                            {
                                return __previous;
                            }
                public:     inline typename x::list<T>::node * previous()
                            {
                                return __previous;
                            }
                public:     inline void previous(typename x::list<T>::node * n)
                            {
                                __previous = n;
                            }
                public:     inline const typename x::list<T>::node * next() const
                            {
                                return __next;
                            }
                public:     inline typename x::list<T>::node * next()
                            {
                                return __next;
                            }
                public:     inline void next(typename x::list<T>::node * n)
                            {
                                __next = n;
                            }
                public:     inline const T & value() const
                            {
                                return __value;
                            }
                public:     inline T & value()
                            {
                                return __value;
                            }
                public:     typename x::list<T>::node & operator=(const typename x::list<T>::node & o)
                            {
                                if(&o != this)
                                {
                                    x::node::operator=(o);
                                    __value = o.__value;
                                    __previous = o.__previous;
                                    __next = o.__next;
                                }
                                return *this;
                            }
                public:     typename x::list<T>::node & operator=(typename x::list<T>::node && o) noexcept
                            {
                                if(&o != this)
                                {
                                    x::node::operator=(x::move(o));
                                    __value = x::move(o.__value);
                                    __previous = o.__previous;
                                    __next = o.__next;

                                    o.__previous = nullptr;
                                    o.__next = nullptr;
                                }
                                return *this;
                            }
                public:     node(const T & value, typename x::list<T>::node * previous)
                            :   x::node(),
                                __value(value),
                                __previous(previous),
                                __next(nullptr)
                            {
                            }
                public:     node(T && value, typename x::list<T>::node * previous)
                            :   x::node(),
                                __value(x::move(value)),
                                __previous(previous),
                                __next(nullptr)
                            {
                            }
                public:     node(const T & value)
                            :   x::node(),
                                __value(value),
                                __previous(nullptr),
                                __next(nullptr)
                            {
                            }
                public:     node(T && value)
                            :   x::node(),
                                __value(x::move(value)),
                                __previous(nullptr),
                                __next(nullptr)
                            {
                            }
                public:     node()
                            :   x::node(),
                                __value(),
                                __previous(nullptr),
                                __next(nullptr)
                            {
                            }
                public:     node(const typename x::list<T>::node & o)
                            :   x::node(o),
                                __value(o.__value),
                                __previous(o.__previous),
                                __next(o.__next)
                            {
                            }
                public:     node(typename x::list<T>::node && o) noexcept
                            :   x::node(x::move(o)),
                                __value(x::move(o.__value)),
                                __previous(o.__previous),
                                __next(o.__next)
                            {
                                o.__previous = nullptr;
                                o.__next = nullptr;
                            }
                public:     ~node() override
                            {
                                __previous = nullptr;
                                __next = nullptr;
                            }
                };
    protected:  typename x::list<T>::node * __head;
    protected:  typename x::list<T>::node * __tail;
    protected:  x::uint64 __size;
    public:     virtual T pop()
                {
                    assertion(__head == nullptr);

                    typename x::list<T>::node * n = __head;
                    typename x::list<T>::node * next = __head->next();
                    if(next)
                    {
                        next->previous(nullptr);
                    }
                    __head = next;
                    __size = __size - 1;
                    if(__size == 0)
                    {
                        __head = nullptr;
                        __tail = nullptr;
                    }
                    T result = x::move(n->value());
                    delete n;
                    return result;
                }
    public:     virtual void push(const x::initializer<T> & list)
                {
                    for(typename x::initializer<T>::iterator it = list.begin(); it != list.end(); ++it)
                    {
                        if(__tail == nullptr)
                        {
                            __tail = __head = new typename x::list<T>::node(*it);
                        }
                        else
                        {
                            typename x::list<T>::node * n = new typename x::list<T>::node(*it, __tail);
                            __tail->next(n);
                            __tail = n;
                        }
                        __size = __size + 1;
                    }
                }
    public:     virtual void push(const T & v)
                {
                    if(__tail == nullptr)
                    {
                        __tail = __head = new typename x::list<T>::node(v);
                    }
                    else
                    {
                        typename x::list<T>::node * n = new typename x::list<T>::node(v, __tail);
                        __tail->next(n);
                        __tail = n;
                    }
                    __size = __size + 1;
                }
    public:     virtual void push(T && v)
                {
                    if(__tail == nullptr)
                    {
                        __tail = __head = new typename x::list<T>::node(x::move(v));
                    }
                    else
                    {
                        typename x::list<T>::node * n = new typename x::list<T>::node(x::move(v), __tail);
                        __tail->next(n);
                        __tail = n;
                    }
                    __size = __size + 1;
                }
    public:     void each(x::function<void (const T &)> f) const override
                {
                    if(f)
                    {
                        for(typename x::list<T>::node * i = __head; i != nullptr; i = i->next())
                        {
                            f(i->value());
                        }
                    }
                }
    public:     void each(x::function<void (T &)> f) override
                {
                    if(f)
                    {
                        for(typename x::list<T>::node * i = __head; i != nullptr; i = i->next())
                        {
                            f(i->value());
                        }
                    }
                }
    public:     x::uint64 size() const override
                {
                    return __size;
                }
    public:     x::boolean empty() const override
                {
                    return __size == 0;
                }
    public:     void clear(x::function<void (T&&)> f) override
                {
                    if(f)
                    {
                        for(typename x::list<T>::node * i = __head; i != nullptr; )
                        {
                            typename x::list<T>::node * n = i;
                            i = i->next();
                            f(x::move(n->value()));
                            delete n;
                        }
                    }
                    else
                    {
                        for(typename x::list<T>::node * i = __head; i != nullptr; )
                        {
                            typename x::list<T>::node * n = i;
                            i = i->next();
                            delete n;
                        }
                    }

                    this->__head = nullptr;
                    this->__tail = nullptr;
                    this->__size = 0;
                }
    public:     void clear() override
                {
                    for(typename x::list<T>::node * i = __head; i != nullptr; )
                    {
                        typename x::list<T>::node * n = i;
                        i = i->next();
                        delete n;
                    }
                    this->__head = nullptr;
                    this->__tail = nullptr;
                    this->__size = 0;
                }
    public:     x::list<T> & operator=(const x::initializer<T> & list)
                {
                    clear();
                    push(list);
                    return *this;
                }
    public:     x::list<T> & operator=(const x::list<T> & o)
                {
                    if(&o != this)
                    {
                        clear();

                        for(typename x::list<T>::node * i = o.__head; i != nullptr; i = i->next())
                        {
                            if(__tail == nullptr)
                            {
                                __head = __tail = new typename x::list<T>::node(i->value());
                            }
                            else
                            {
                                typename x::list<T>::node * n = new typename x::list<T>::node(i->value(), __tail);
                                __tail->next(n);
                                __tail = n;
                            }
                            __size = __size + 1;
                        }
                    }
                    return *this;
                }
    public:     x::list<T> & operator=(x::list<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        clear();

                        __head = o.__head;
                        __tail = o.__tail;
                        __size = o.__size;

                        o.__head = nullptr;
                        o.__tail = nullptr;
                        o.__size = 0;
                    }
                    return *this;
                }
    public:     list(const x::initializer<T> & list)
                :   x::collection<T>(),
                    __head(nullptr),
                    __tail(nullptr),
                    __size(0)
                {
                    for(typename x::initializer<T>::iterator it = list.begin(); it != list.end(); ++it)
                    {
                        push(*it);
                    }
                }
    public:     list()
                :   x::collection<T>(),
                    __head(nullptr),
                    __tail(nullptr),
                    __size(0)
                {
                }
    public:     list(const x::list<T> & o)
                :   x::collection<T>(),
                    __head(nullptr),
                    __tail(nullptr),
                    __size(0)
                {
                    for(typename x::list<T>::node * i = o.__head; i != nullptr; i = i->next())
                    {
                        if(__tail == nullptr)
                        {
                            __head = __tail = new typename x::list<T>::node(i->value());
                        }
                        else
                        {
                            typename x::list<T>::node * n = new typename x::list<T>::node(i->value(), __tail);
                            __tail->next(n);
                            __tail = n;
                        }
                        __size = __size + 1;
                    }
                }
    public:     list(x::list<T> && o) noexcept
                :   x::collection<T>(),
                    __head(o.__head),
                    __tail(o.__tail),
                    __size(o.__size)
                {
                    o.__head = nullptr;
                    o.__tail = nullptr;
                    o.__size = 0;
                }
    public:     ~list() override
                {
                    clear();
                }
    };
}

#endif // __X__LIST__HH__
