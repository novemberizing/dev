#ifndef   __X__ARRAY__HH__
#define   __X__ARRAY__HH__

#include <x/output/stream.hh>
#include <x/collection.hh>
#include <x/memory.hh>
#include <x/page.hh>
#include <x/initializer.hh>

namespace x
{
    template <typename T>
    class array : public x::collection<T>
    {
    protected:  T * __container;
    protected:  x::uint64 __capacity;
    protected:  x::uint64 __size;
    protected:  x::uint64 __page;
    public:     array<T> sub(x::uint64 offset, x::uint64 length) const
                {
                    if(__size < offset + length)
                    {
                        exceptional();
                    }
                    return x::array<T>(const_cast<const T *>(&__container[offset]), length);
                }
    public:     virtual const T * data() const
                {
                    return this->__container;
                }
    public:     virtual void push(const T & item)
                {
                    if(this->__capacity <= this->__size + 1)
                    {
                        this->__capacity = x::page::calculate(this->__size + 1, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::set<T>(&this->__container[this->__size], item);
                    this->__size = this->__size + 1;
                }
    public:     virtual void push(T && item)
                {
                    if(this->__capacity <= this->__size + 1)
                    {
                        this->__capacity = x::page::calculate(this->__size + 1, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::set<T>(&this->__container[this->__size], x::move(item));
                    this->__size = this->__size + 1;
                }
    public:     virtual void push(const T & item, x::uint64 n)
                {
                    if(this->__capacity <= this->__size + n)
                    {
                        this->__capacity = x::page::calculate(this->__size + n, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::set<T>(&this->__container[this->__size], item, n);
                    this->__size = this->__size + n;
                }
    public:     virtual void push(const T * source, x::uint64 n)
                {
                    if(this->__capacity <= this->__size + n)
                    {
                        this->__capacity = x::page::calculate(this->__size + n, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::copy<T>(&this->__container[this->__size], source, n);
                    this->__size = this->__size + n;
                }
    public:     virtual void push(array<T> && o)
                {
                    if(this->__capacity <= this->__size + o.__size)
                    {
                        this->__capacity = x::page::calculate(this->__size + o.__size, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::move<T>(&this->__container[this->__size], o.__container, o.__size);
                    this->__size = this->__size + o.__size;
                }
    public:     virtual void push(const array<T> & o)
                {
                    if(this->__capacity <= this->__size + o.__size)
                    {
                        this->__capacity = x::page::calculate(this->__size + o.__size, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::copy<T>(&this->__container[this->__size], o.__container, o.__size);
                    this->__size = this->__size + o.__size;
                }
    public:     virtual void push(const x::initializer<T> & list)
                {
                    if(this->__capacity <= this->__size + list.size())
                    {
                        this->__capacity = x::page::calculate(this->__size + list.size(), this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::copy<T>(&this->__container[this->__size], list);
                    this->__size = this->__size + list.size();
                }
    public:     virtual void resize(x::uint64 n)
                {
                    this->resize(n, T());
                }
    public:     virtual void resize(x::uint64 n, const T & v)
                {
                    if(n < this->__size)
                    {
                        x::memory::del<T>(&this->__container[n], this->__size - n);
                        this->__size = n;
                    }
                    else if(n > this->__size)
                    {
                        if(this->__capacity <= n)
                        {
                            this->__capacity = x::page::calculate(n, this->__page);
                            this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                        }
                        x::memory::set<T>(&this->__container[this->__size], v, n - this->__size);
                        this->__size = n;
                    }
                }
    public:     void add(const T & item) override
                {
                    if(this->__capacity <= this->__size + 1)
                    {
                        this->__capacity = x::page::calculate(this->__size + 1, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::set<T>(&this->__container[this->__size], item);
                    this->__size = this->__size + 1;
                }
    public:     void add(T && item) override
                {
                    if(this->__capacity <= this->__size + 1)
                    {
                        this->__capacity = x::page::calculate(this->__size + 1, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::set<T>(&this->__container[this->__size], x::move(item));
                    this->__size = this->__size + 1;
                }
    public:     void clear() override
                {
                    x::memory::del<T>(this->__container, this->__size);
                    this->__size = 0;
                    this->__capacity = this->__page;
                    this->__container = memory::allocate<T>(this->__container, this->__capacity);
                }
    public:     void clear(x::function<void (T &&)> f) override
                {
                    if(f)
                    {
                        for(x::uint64 i = 0; i < this->__size; i++)
                        {
                            f(x::move(this->__container[i]));
                        }
                    }
                    this->clear();
                }
    public:     virtual void each(x::function<void (T &)> f)
                {
                    if(f)
                    {
                        for(x::uint64 i = 0; i < this->__size; i++)
                        {
                            f(this->__container[i]);
                        }
                    }
                }
    public:     void each(x::function<void (const T &)> f) const override
                {
                    if(f)
                    {
                        for(x::uint64 i = 0; i < this->__size; i++)
                        {
                            f(this->__container[i]);
                        }
                    }
                }
    public:     x::uint64 size() const override
                {
                    return this->__size;
                }
    public:     x::boolean empty() const override
                {
                    return this->__container == nullptr || this->__size == 0;
                }
    public:     const T & operator[](x::uint64 i) const
                {
                    if(this->__size <= i)
                    {
                        exceptional();
                    }
                    return this->__container[i];
                }
    public:     T & operator[](x::uint64 i)
                {
                    if(this->__size <= i)
                    {
                        exceptional();
                    }
                    return this->__container[i];
                }
    public:     x::array<T> & operator+=(T && item)
                {
                    this->push(x::move(item));
                    return *this;
                }
    public:     x::array<T> & operator+=(const T & item)
                {
                    this->push(item);
                    return *this;
                }
    public:     x::array<T> & operator+=(const x::array<T> & o)
                {
                    this->push(o);
                    return *this;
                }
    public:     x::array<T> & operator+=(x::array<T> && o)
                {
                    this->push(x::move(o));
                    return *this;
                }
    public:     x::array<T> & operator+=(const x::initializer<T> & list)
                {
                    this->push(list);
                    return *this;
                }
    public:     x::array<T> & operator=(const x::array<T> & o)
                {
                    if(&o != this)
                    {
                        x::memory::del<T>(this->__container, this->__size);
                        this->__container = x::memory::allocate<T>(this->__container, o.__capacity);

                        x::memory::copy<T>(this->__container, o.__container, o.__size);
                        this->__capacity = o.__capacity;
                        this->__size = o.__size;
                        this->__page = o.__page;
                    }
                    return *this;
                }
    public:     x::array<T> & operator=(x::array<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        x::memory::del<T>(this->__container, this->__size);
                        x::memory::deallocate<T>(this->__container);

                        this->__container = o.__container;
                        this->__capacity = o.__capacity;
                        this->__size = o.__size;
                        this->__page = o.__page;

                        o.__container = nullptr;
                        o.__capacity = 0L;
                        o.__size = 0L;
                        o.__page = 0L;
                    }
                    return *this;
                }
    public:     x::array<T> & operator=(const T & item)
                {
                    x::memory::del<T>(this->__container, this->__size);
                    if(this->__capacity <= 1)
                    {
                        this->__capacity = x::page::calculate(1, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::set<T>(this->__container, item);
                    this->__size = 1;
                    return *this;
                }
    public:     x::array<T> & operator=(T && item)
                {
                    x::memory::del<T>(this->__container, this->__size);
                    if(this->__capacity <= 1)
                    {
                        this->__capacity = x::page::calculate(1, this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::set<T>(this->__container, x::move(item));
                    this->__size = 1;
                    return *this;
                }
    public:     x::array<T> & operator=(const x::initializer<T> & list)
                {
                    x::memory::del<T>(this->__container, this->__size);
                    if(this->__capacity <= list.size())
                    {
                        this->__capacity = x::page::calculate(list.size(), this->__page);
                        this->__container = x::memory::allocate<T>(this->__container, this->__capacity);
                    }
                    x::memory::copy<T>(this->__container, list);
                    this->__size = list.size();
                    return *this;
                }
    public:     array(T *&& container, x::uint64 n) :
                    __container(container),
                    __capacity(n),
                    __size(n),
                    __page(x::page::size())
                {
                }
    public:     array(T *&& container, x::uint64 n,x::uint64 capacity) :
                    __container(container),
                    __capacity(capacity),
                    __size(n),
                    __page(x::page::size())
                {
                }
    public:     array(const x::initializer<T> & list) :
                    __container(x::memory::allocate<T>(x::page::calculate(list.size()))),
                    __capacity(x::page::calculate(list.size())),
                    __size(0L),
                    __page(x::page::size())
                {
                    x::memory::copy<T>(this->__container, list);
                    this->__size = list.size();
                }
    public:     array(const T * source, x::uint64 n) :
                    __container(x::memory::allocate<T>(x::page::calculate(n))),
                    __capacity(x::page::calculate(n)),
                    __size(0L),
                    __page(x::page::size())
                {
                    x::memory::copy<T>(this->__container, source, n);
                    this->__size = this->__size + n;
                }
    public:     array(const T & item, x::uint64 n) :
                    __container(x::memory::allocate<T>(x::page::calculate(n))),
                    __capacity(x::page::calculate(n)),
                    __size(0L),
                    __page(x::page::size())
                {
                    x::memory::set<T>(this->__container, item, n);
                    this->__size = this->__size + n;
                }
    protected:  array(x::uint64 page)
                :   __container(x::memory::allocate<T>(x::page::calculate(0, page))),
                    __capacity(x::page::calculate(0, page)),
                    __size(0L),
                    __page(page > 0 ? page : 1)
                {
                }
    public:     array() :
                    __container(memory::allocate<T>(x::page::size())),
                    __capacity(x::page::size()),
                    __size(0L),
                    __page(x::page::size())
                {
                }
    public:     array(const array<T> & o) :
                    __container(memory::allocate<T>(o.__capacity)),
                    __capacity(o.__capacity),
                    __size(o.__size),
                    __page(o.__page)
                {
                    x::memory::copy<T>(this->__container, o.__container, this->__size);
                }
    public:     array(array<T> && o) noexcept :
                    __container(o.__container),
                    __capacity(o.__capacity),
                    __size(o.__size),
                    __page(o.__page)
                {
                    o.__container = nullptr;
                    o.__capacity = 0L;
                    o.__size = 0L;
                }
    public:     ~array() override
                {
                    x::memory::del<T>(this->__container, this->__size);
                    this->__container = x::memory::deallocate<T>(this->__container);
                    this->__size = 0L;
                    this->__capacity = 0L;
                }
    public:     friend x::output::stream & operator<<(x::output::stream & os, const array<T> & o)
                {
                    if(o.__container)
                    {
                        os << "[";
                        for(x::uint64 i = 0; i < o.__size; i++)
                        {
                            os << o.__container[i];
                            if(i + 1 != o.__size)
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

#endif // __X__ARRAY__HH__
