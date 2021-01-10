#ifndef   __X__ARRAY__HH__
#define   __X__ARRAY__HH__

#include <x/collection.hh>

namespace x
{
    template <typename T>
    class array : public x::collection<T>
    {
    protected:  T * __container;
    protected:  x::uint64 __size;
    protected:  x::uint64 __capacity;
    protected:  x::uint64 __page;
    public:     inline array<T> sub(x::uint64 offset, x::uint64 length) const
                {
                    assertion(__size < offset + length);
                    return x::array<T>(&__container[offset], length);
                }
    public:     virtual const T * data() const
                {
                    return __container;
                }
    public:     virtual void resize(x::uint64 n, const T & item)
                {
                    if(n < __size)
                    {
                        x::memory::destruct<T>(&__container[n], __size - n);
                        __size = n;
                    }
                    else if(n > __size)
                    {
                        if(__capacity <= n)
                        {
                            __capacity = x::paging::calculate(n, __page);
                            __container = x::memory::allocate<T>(__container, __capacity);
                        }
                        x::memory::construct<T>(&__container[__size], item, n - __size);
                        __size = n;
                    }
                }
    public:     virtual void resize(x::uint64 n)
                {
                    resize(n, T());
                }
    public:     virtual void push(const T * source, x::uint64 n)
                {
                    append(source, n);
                }
    public:     virtual void push(const T & item, x::uint64 n)
                {
                    append(item, n);
                }
    public:     virtual void push(const T & item)
                {
                    append(item);
                }
    public:     virtual void push(T && item)
                {
                    append(x::move(item));
                }
    public:     virtual void push(const x::array<T> & o)
                {
                    append(o);
                }
    public:     virtual void push(const x::initializer<T> & list)
                {
                    append(list);
                }
    public:     virtual void append(const T * source, x::uint64 n)
                {
                    if(__capacity <= __size + n)
                    {
                        __capacity = x::paging::calculate(__size + n, __page);
                        __container = x::memory::allocate<T>(__container, __capacity);
                    }
                    x::memory::copy<T>(&__container[__size], source, n);
                    __size = __size + n;
                }
    public:     virtual void append(const T & item, x::uint64 n)
                {
                    if(__capacity <= __size + n)
                    {
                        __capacity = x::paging::calculate(__size + n, __page);
                        __container = x::memory::allocate<T>(__container, __capacity);
                    }
                    x::memory::construct<T>(&__container[__size], item, n);
                    __size = __size + n;
                }
    public:     virtual void append(const T & item)
                {
                    if(__capacity <= __size + 1)
                    {
                        __capacity = x::paging::calculate(__size + 1, __page);
                        __container = x::memory::allocate<T>(__container, __capacity);
                    }
                    x::memory::construct<T>(&__container[__size], item);
                    __size = __size + 1;
                }
    public:     virtual void append(T && item)
                {
                    if(__capacity <= __size + 1)
                    {
                        __capacity = x::paging::calculate(__size + 1, __page);
                        __container = x::memory::allocate<T>(__container, __capacity);
                    }
                    x::memory::construct<T>(&__container[__size], x::move(item));
                    __size = __size + 1;
                }
    public:     virtual void append(const x::array<T> & o)
                {
                    if(&o != this)
                    {
                        __capacity = x::paging::calculate(__size + o.__size, __page);
                        __container = x::memory::allocate<T>(__container, __capacity);
                        x::memory::copy<T>(&__container[__size], o.__container, o.__size);
                        __size = __size + o.__size;
                    }
                    else
                    {
                        x::array<T> temp = o;
                        append(temp);
                    }
                }
    public:     virtual void append(const x::initializer<T> & list)
                {
                    __capacity = x::paging::calculate(__size + list.size(), __page);
                    __container = x::memory::allocate<T>(__container, __capacity);
                    x::memory::copy<T>(&__container[__size], list);
                    __size = __size + list.size();
                }
    public:     virtual void assign(const T * source, x::uint64 n)
                {
                    __container = x::memory::destruct<T>(__container, __size);

                    __capacity = x::paging::calculate(n, __page);
                    __container = x::memory::allocate<T>(__container, __capacity);
                    x::memory::copy<T>(__container, source, n);
                    __size = n;
                }
    public:     virtual void assign(const T & item, x::uint64 n)
                {
                    __container = x::memory::destruct<T>(__container, __size);

                    __capacity = x::paging::calculate(n, __page);
                    __container = x::memory::allocate<T>(__container, __capacity);
                    x::memory::construct<T>(__container, item, n);
                    __size = n;
                }
    public:     virtual void assign(const T & item)
                {
                    __container = x::memory::destruct<T>(__container, __size);

                    __capacity = x::paging::calculate(1, __page);
                    __container = x::memory::allocate<T>(__container, __capacity);
                    x::memory::construct<T>(__container, item);
                    __size = 1;
                }
    public:     virtual void assign(T && item)
                {
                    __container = x::memory::destruct<T>(__container, __size);

                    __capacity = x::paging::calculate(1, __page);
                    __container = x::memory::allocate<T>(__container, __capacity);
                    x::memory::construct<T>(__container, item);
                    __size = 1;
                }
    public:     virtual void assign(const x::array<T> & o)
                {
                    if(&o != this)
                    {
                        __container = x::memory::destruct<T>(__container, __size);

                        __container = x::memory::allocate<T>(__container, o.__capacity);

                        __container = x::memory::copy<T>(__container, o.__container, o.__size);
                        __size = o.__size;
                        __capacity = o.__capacity;
                        __page = o.__page;
                    }
                }
    public:     virtual void assign(x::array<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        __container = x::memory::destruct<T>(__container, __size);

                        __container = x::memory::deallocate<T>(__container);

                        __container = o.__container;
                        __size = o.__size;
                        __capacity = o.__capacity;
                        __page = o.__page;

                        o.__container = nullptr;
                        o.__size = 0;
                        o.__capacity = 0;
                        o.__page = x::paging::size;
                    }
                }
    public:     virtual void assign(const x::initializer<T> & list)
                {
                    __container = x::memory::destruct<T>(__container, __size);

                    __container = x::memory::allocate<T>(__container, x::paging::calculate(list.size(), __page));
                    __container = x::memory::copy<T>(__container, list);
                    __size = list.size();
                    __capacity = x::paging::calculate(list.size(), __page);
                }

    public:     x::uint64 size() const override
                {
                    return __size;
                }
    public:     x::boolean empty() const override
                {
                    return __size == 0;
                }
    public:     void clear() override
                {
                    __container = x::memory::destruct<T>(__container, __size);
                    __container = x::memory::allocate<T>(__container, __page);
                    __capacity = __page;
                    __size = 0;
                }
    public:     void clear(x::function<void (T&&)> f) override
                {
                    if(f)
                    {
                        for(x::uint64 i = 0; i < __size; i++)
                        {
                            f(x::move(__container[i]));
                        }
                    }
                    clear();
                }
    public:     virtual x::boolean until(x::function<x::boolean (const T &)> f)
                {
                    if(f)
                    {
                        for(x::uint64 i = 0; i < __size; i++)
                        {
                            if(f(__container[i]))
                            {
                                return true;
                            }
                        }
                    }
                    return false;
                }
    public:     virtual x::boolean until(x::function<x::boolean (T &)> f)
                {
                    if(f)
                    {
                        for(x::uint64 i = 0; i < __size; i++)
                        {
                            if(f(__container[i]))
                            {
                                return true;
                            }
                        }
                    }
                    return false;
                }
    public:     void each(x::function<void (const T &)> f) const override
                {
                    if(f)
                    {
                        for(x::uint64 i = 0; i < __size; i++)
                        {
                            f(__container[i]);
                        }
                    }
                }
    public:     void each(x::function<void (T &)> f) override
                {
                    if(f)
                    {
                        for(x::uint64 i = 0; i < __size; i++)
                        {
                            f(__container[i]);
                        }
                    }
                }
    public:     T & operator[](x::uint64 i)
                {
                    assertion(__size <= i);

                    return __container[i];
                }
    public:     const T & operator[](x::uint64 i) const
                {
                    assertion(__size <= i);

                    return __container[i];
                }
    public:     array<T> & operator+=(const T & item)
                {
                    append(item);
                    return *this;
                }
    public:     array<T> & operator+=(const x::array<T> & o)
                {
                    append(o);
                    return *this;
                }
    public:     array<T> & operator+=(const x::initializer<T> & list)
                {
                    append(list);
                    return *this;
                }
    public:     array<T> & operator=(const T & item)
                {
                    assign(item);
                    return *this;
                }
    public:     array<T> & operator=(T && item)
                {
                    assign(x::move(item));
                    return *this;
                }
    public:     array<T> & operator=(const x::initializer<T> & list)
                {
                    assign(list);
                    return *this;
                }
    public:     array<T> & operator=(const array<T> & o)
                {
                    assign(o);
                    return *this;
                }
    public:     array<T> & operator=(array<T> && o) noexcept
                {
                    assign(o);
                    return *this;
                }
    protected:  array(T * container, x::uint64 n, x::uint64 capacity, x::uint64 page)
                :   x::collection<T>(),
                    __container(container),
                    __size(n),
                    __capacity(capacity),
                    __page(x::paging::get(page))
                {
                }
    protected:  array(T * container, x::uint64 n, x::uint64 capacity)
                :   x::collection<T>(),
                    __container(container),
                    __size(n),
                    __capacity(capacity),
                    __page(x::paging::size)
                {
                }
    public:     array(const T * source, x::uint64 n)
                :   x::collection<T>(),
                    __container(x::memory::allocate<T>(x::paging::calculate(n, x::paging::size))),
                    __size(n),
                    __capacity(x::paging::calculate(n, x::paging::size)),
                    __page(x::paging::size)
                {
                    x::memory::copy<T>(__container, source, n);
                }
    public:     array(const T & item, x::uint64 n)
                :   x::collection<T>(),
                    __container(x::memory::allocate<T>(x::paging::calculate(n, x::paging::size))),
                    __size(n),
                    __capacity(x::paging::calculate(n, x::paging::size)),
                    __page(x::paging::size)
                {
                    x::memory::construct<T>(__container, item, n);
                }
    public:     array(const x::initializer<T> & list)
                :   x::collection<T>(),
                    __container(x::memory::allocate<T>(x::paging::calculate(list.size(), x::paging::size))),
                    __size(list.size()),
                    __capacity(x::paging::calculate(list.size(), x::paging::size)),
                    __page(x::paging::size)
                {
                    x::memory::copy<T>(__container, list);
                }
    protected:  array(x::uint64 page)
                :   x::collection<T>(),
                    __container(x::memory::allocate<T>(x::paging::get(page))),
                    __size(0L),
                    __capacity(x::paging::get(page)),
                    __page(x::paging::get(page))
                {
                }
    public:     array()
                :   x::collection<T>(),
                    __container(x::memory::allocate<T>(x::paging::size)),
                    __size(0L),
                    __capacity(x::paging::size),
                    __page(x::paging::size)
                {
                }
    public:     array(const x::array<T> & o)
                :   x::collection<T>(),
                    __container(x::memory::allocate<T>(o.__capacity)),
                    __size(o.__size),
                    __capacity(o.__capacity),
                    __page(o.__page)
                {
                    x::memory::copy<T>(__container, o.__container, __size);
                }
    public:     array(array<T> && o) noexcept
                :   x::collection<T>(),
                    __container(o.__container),
                    __size(o.__size),
                    __capacity(o.__capacity),
                    __page(o.__page)
                {
                    o.__container = nullptr;
                    o.__size = 0;
                    o.__capacity = 0;
                    o.__page = x::paging::size;
                }
    public:     ~array() override
                {
                    __container = x::memory::destruct<T>(__container, __size);
                    __container = x::memory::deallocate<T>(__container);
                    __size = 0;
                    __capacity = 0;
                    __page = x::paging::size;
                }
    };
}

#endif // __X__ARRAY__HH__
