#ifndef   __X__STRING__HH__
#define   __X__STRING__HH__

#include <x/array.hh>
#include <x/input.stream.hh>
#include <x/output.stream.hh>

namespace x
{
    class string : protected x::array<x::character>
    {
    public:     static x::string from(const x::byte * data, x::uint32 offset, x::uint32 length)
                {
                    return x::string((x::character *) &data[offset], length);
                }
    public:     virtual const character * str() const
                {
                    return __container;
                }
    public:     virtual void erase(x::uint64 offset, x::uint64 length)
                {
                    assertion(__size < offset + length);

                    if(offset + length == __size)
                    {
                        __size = offset;
                    }
                    else
                    {
                        x::memory::move<x::character>(&__container[offset], &__container[offset + length], __size - (offset + length));
                        __size = __size - length;
                    }
                }
    public:     inline x::uint64 find(x::function<x::boolean (x::character)> f, x::uint64 offset, x::int32 direction) const
                {
                    if(direction >= 0)
                    {
                        for(x::uint64 i = offset; i < __size; i++)
                        {
                            if(f(__container[i]))
                            {
                                return i;
                            }
                        }
                    }
                    else if(direction < 0)
                    {
                        for(x::uint64 i = offset; i < __size; i--)
                        {
                            if(f(__container[i]))
                            {
                                return i;
                            }
                        }
                    }
                    return -1LU;
                }
    public:     inline x::uint64 find(x::character c, x::uint64 offset, x::int32 direction) const
                {
                    if(direction >= 0)
                    {
                        for(x::uint64 i = offset; i < __size; i++)
                        {
                            if(__container[i] == c)
                            {
                                return i;
                            }
                        }
                    }
                    else if(direction < 0)
                    {
                        for(x::uint64 i = offset; i < __size; i--)
                        {
                            if(__container[i] == c)
                            {
                                return i;
                            }
                        }
                    }
                    return -1LU;
                }
    public:     inline x::uint64 find(x::character c) const
                {
                    for(x::uint64 i = 0; i < __size; i++)
                    {
                        if(__container[i] == c)
                        {
                            return i;
                        }
                    }
                    return -1LU;
                }
    public:     inline x::string sub(x::uint64 offset, x::uint64 length) const
                {
                    assertion(__size < offset + length);

                    return x::string(&__container[offset], length);
                }
    public:     inline x::array<x::string> split(x::function<x::string (const x::character *, x::uint64 &, x::uint64)> f) const
                {
                    x::array<x::string> result;
                    for(x::uint64 i = 0; i < __size; )
                    {
                        x::uint64 index = 0;
                        x::string s = f(&__container[i], index, __size - i);
                        i = i + index;
                        result.push(x::move(s));
                    }
                    return result;
                }
    public:     inline x::array<x::string> split(x::character c, x::uint64 until) const
                {
                    until = (__size < until ? __size : until);
                    x::array<x::string> result;
                    x::uint64 start = 0;
                    for(x::uint64 i = 0; i < until; i++)
                    {
                        if(__container[i] == c)
                        {
                            result.push(sub(start, i - start));
                            start = i + 1;
                        }
                        else
                        {
                            if(i + 1 == until)
                            {
                                result.push(sub(start, until - start));
                            }
                        }
                    }
                    return result;
                }
    public:     inline x::array<x::string> split(x::character c) const
                {
                    return split(c, __size);
                }
    public:     void resize(x::uint64 n, const x::character & item) override
                {
                    x::array<x::character>::resize(n, item);
                    __container[__size] = 0;
                }
    public:     void resize(x::uint64 n) override
                {
                    x::array<x::character>::resize(n);
                    __container[__size] = 0;
                }
    protected:  void push(const x::character * source, x::uint64 n) override
                {
                    x::array<x::character>::push(source, n);
                    __container[__size] = 0;
                }
    protected:  void push(const x::character & item, x::uint64 n) override
                {
                    x::array<x::character>::push(item, n);
                    __container[__size] = 0;
                }
    protected:  void push(const x::character & item) override
                {
                    x::array<x::character>::push(item);
                    __container[__size] = 0;
                }
    protected:  void push(x::character && item) override
                {
                    x::array<x::character>::push(x::move(item));
                    __container[__size] = 0;
                }
    protected:  void push(const x::array<x::character> & o) override
                {
                    x::array<x::character>::push(o);
                    __container[__size] = 0;
                }
    protected:  void push(const x::initializer<x::character> & list) override
                {
                    x::array<x::character>::push(list);
                    __container[__size] = 0;
                }
    protected:  virtual void push(const x::string & o)
                {
                    x::array<x::character>::push(o);
                    __container[__size] = 0;
                }
    public:     void append(const x::character * source, x::uint64 n) override
                {
                    x::array<x::character>::append(source, n);
                    __container[__size] = 0;
                }
    public:     void append(const x::character & item, x::uint64 n) override
                {
                    x::array<x::character>::append(item, n);
                    __container[__size] = 0;
                }
    public:     void append(const x::character & item) override
                {
                    x::array<x::character>::append(item);
                    __container[__size] = 0;
                }
    public:     void append(x::character && item) override
                {
                    x::array<x::character>::append(x::move(item));
                    __container[__size] = 0;
                }
    public:     void append(const x::array<x::character> & o) override
                {
                    x::array<x::character>::append(o);
                    __container[__size] = 0;
                }
    public:     void append(const x::initializer<x::character> & list) override
                {
                    x::array<x::character>::append(list);
                    __container[__size] = 0;
                }
    public:     virtual void append(const x::string & o)
                {
                    x::array<x::character>::append(o);
                    __container[__size] = 0;
                }
    public:     virtual void append(const x::character * s)
                {
                    x::array<x::character>::append(s, s ? __core_strlen(s) : 0);
                    __container[__size] = 0;
                }
    public:     void assign(const x::character * source, x::uint64 n) override
                {
                    x::array<x::character>::assign(source, n);
                    __container[__size] = 0;
                }
    public:     void assign(const x::character & item, x::uint64 n) override
                {
                    x::array<x::character>::assign(item, n);
                    __container[__size] = 0;
                }
    public:     void assign(const x::character & item) override
                {
                    x::array<x::character>::assign(item);
                    __container[__size] = 0;
                }
    public:     void assign(x::character && item) override
                {
                    x::array<x::character>::assign(x::move(item));
                    __container[__size] = 0;
                }
    public:     void assign(const x::array<x::character> & o) override
                {
                    x::array<x::character>::assign(o);
                    __container[__size] = 0;
                }
    public:     void assign(x::array<x::character> && o) noexcept override
                {
                    x::array<x::character>::assign(x::move(o));
                    __container[__size] = 0;
                }
    public:     void assign(const x::initializer<x::character> & list) override
                {
                    x::array<x::character>::assign(list);
                    __container[__size] = 0;
                }
    public:     virtual void assign(const x::string & o)
                {
                    x::array<x::character>::assign(o);
                    __container[__size] = 0;
                }
    public:     virtual void assign(x::string && o) noexcept
                {
                    x::array<x::character>::assign(x::move(o));
                    __container[__size] = 0;
                }
    public:     virtual void assign(const x::character * s)
                {
                    x::array<x::character>::assign(s, s != nullptr ? __core_strlen(s) : 0);
                    __container[__size] = 0;
                }
    public:     x::uint64 size() const override
                {
                    return x::array<x::character>::size();
                }
    public:     x::boolean empty() const override
                {
                    return x::array<x::character>::empty();
                }
    public:     void clear() override
                {
                    x::array<x::character>::clear();
                    __container[__size] = 0;
                }
    public:     void clear(x::function<void (x::character &&)> f) override
                {
                    x::array<x::character>::clear(f);
                    __container[__size] = 0;
                }
    protected:  void each(x::function<void (const x::character &)> f) const override
                {
                    x::array<x::character>::each(f);
                }
    protected:  void each(x::function<void (x::character &)> f) override
                {
                    x::array<x::character>::each(f);
                }
    public:     x::character & operator[](x::uint64 i)
                {
                    return x::array<x::character>::operator[](i);
                }
    public:     const x::character & operator[](x::uint64 i) const
                {
                    return x::array<x::character>::operator[](i);
                }
    public:     x::string & operator+=(const x::character * s)
                {
                    append(s);
                    return *this;
                }
    public:     x::string & operator+=(const x::character & item)
                {
                    append(item);
                    return *this;
                }
    public:     x::string & operator+=(const x::array<x::character> & o)
                {
                    append(o);
                    return *this;
                }
    public:     x::string & operator+=(const x::initializer<x::character> & list)
                {
                    append(list);
                    return *this;
                }
    public:     x::string & operator+=(const x::string & o)
                {
                    append(o);
                    return *this;
                }
    public:     x::string & operator=(const x::character * s)
                {
                    assign(s);
                    return *this;
                }
    public:     x::string & operator=(const x::character & item)
                {
                    assign(item);
                    return *this;
                }
    public:     x::string & operator=(x::character && item)
                {
                    assign(x::move(item));
                    return *this;
                }
    public:     x::string & operator=(const x::initializer<x::character> & list)
                {
                    assign(list);
                    return *this;
                }
    public:     x::string & operator=(const array<x::character> & o)
                {
                    assign(o);
                    return *this;
                }
    public:     x::string & operator=(array<x::character> && o) noexcept
                {
                    assign(x::move(o));
                    return *this;
                }
    public:     x::string & operator=(const x::string & o)
                {
                    assign(o);
                    return *this;
                }
    public:     x::string & operator=(x::string && o) noexcept
                {
                    assign(x::move(o));
                    return *this;
                }
    protected:  string(x::character * container, x::uint64 n, x::uint64 capacity, x::uint64 page)
                :   x::array<x::character>(container, n, capacity, page)
                {
                }
    protected:  string(x::character * container, x::uint64 n, x::uint64 capacity)
                :   x::array<x::character>(container, n, capacity)
                {
                }
    public:     string(const x::array<x::character> & o)
                :   x::array<x::character>(o)
                {
                    __container[__size] = 0;
                }
    public:     string(x::array<x::character> && o) noexcept
                :   x::array<x::character>(x::move(o))
                {
                    __container[__size] = 0;
                }
    public:     string(const x::character * source)
                :   x::array<x::character>(source, source ? __core_strlen(source) : 0)
                {
                    __container[__size] = 0;
                }
    public:     string(const x::character * source, x::uint64 n)
                :   x::array<x::character>(source, n)
                {
                    __container[__size] = 0;
                }
    public:     string(const x::character & item, x::uint64 n)
                :   x::array<x::character>(item, n)
                {
                    __container[__size] = 0;
                }
    public:     string(const x::initializer<x::character> & list)
                :   x::array<x::character>(list)
                {
                    __container[__size] = 0;
                }
    protected:  string(x::uint64 page)
                :   x::array<x::character>(page)
                {
                    __container[__size] = 0;
                }
    public:     string()
                :   x::array<x::character>()
                {
                    __container[__size] = 0;
                }
    public:     string(const x::string & o)
                :   x::array<x::character>(o)
                {
                    __container[__size] = 0;
                }
    public:     string(x::string && o) noexcept
                :   x::array<x::character>(x::move(o))
                {
                    __container[__size] = 0;
                }
    public:     ~string() override
                {
                }
    public:     friend x::string operator+(const x::string &     left, const x::string &     right)
                    {
                        x::string out = left;
                        out += right;
                        return out;
                    }
    public:     friend x::string operator+(const x::string &     left, const x::character *   right)
                {
                    x::string out = left;
                    out += right;
                    return out;
                }
    public:     friend x::string operator+(const x::string &     left, x::character           right)
                {
                    x::string out = left;
                    out += right;
                    return out;
                }
    public:     friend x::string operator+(const x::character *   left, const x::string &     right)
                {
                    x::string out = left;
                    out += right;
                    return out;
                }
    public:     friend x::string operator+(x::character           left, const x::string &     right)
                {
                    x::string out = left;
                    out += right;
                    return out;
                }
    public:     friend x::boolean operator==(const x::string &    left, const x::string &     right)
                {
                    return left.__size == right.__size && __core_strcmp(left.__container, right.__container) == 0;
                }
    public:     friend x::boolean operator==(const x::string &    left, const x::character *  right)
                {
                    x::uint64 len = (right ? __core_strlen(right) : 0);
                    return left.__size == len && __core_strcmp(left.__container, right) == 0;
                }
    public:     friend x::boolean operator==(const x::string &    left, x::character          right)
                {
                    return left.__size == 1 && left.__container[0] == right;
                }
    public:     friend x::boolean operator==(const x::character * left, const x::string &     right)
                {
                    x::uint64 len = (left ? __core_strlen(left) : 0);
                    return right.__size == len && __core_strcmp(right.__container, left) == 0;
                }
    public:     friend x::boolean operator==(x::character          left, const x::string &    right)
                {
                    return right.__size == 1 && right.__container[0] == right;
                }
    public:     friend x::boolean operator!=(const x::string &     left, const x::string &    right)
                {
                    return left.__size != right.__size || __core_strcmp(left.__container, right.__container) != 0;
                }
    public:     friend x::boolean operator!=(const x::string &     left, const x::character * right)
                {
                    x::uint64 len = (right ? __core_strlen(right) : 0);
                    return left.__size != len || __core_strcmp(left.__container, right) != 0;
                }
    public:     friend x::boolean operator!=(const x::string &     left, x::character         right)
                {
                    return left.__size != 1 || left.__container[0] != right;
                }
    public:     friend x::boolean operator!=(const x::character *  left, const x::string &    right)
                {
                    x::uint64 len = (left ? __core_strlen(left) : 0);
                    return right.__size != len || __core_strcmp(right.__container, left) != 0;
                }
    public:     friend x::boolean operator!=(x::character          left, const x::string &    right)
                {
                    return right.__size != 1 && right.__container[0] != right;
                }
    public:     friend x::boolean operator< (const x::string &     left, const x::string &    right)
                {
                    return __core_strcmp(left.__container, right.__container) < 0;
                }
    public:     friend x::boolean operator< (const x::string &     left, const x::character * right)
                {
                    return __core_strcmp(left.__container, right) < 0;
                }
    public:     friend x::boolean operator< (const x::character *  left, const x::string &    right)
                {
                    return __core_strcmp(left, right.__container) <= 0;
                }
    public:     friend x::boolean operator<=(const x::string &     left, const x::string &    right)
                {
                    return __core_strcmp(left.__container, right.__container) < 0;
                }
    public:     friend x::boolean operator<=(const x::string &     left, const x::character * right)
                {
                    return __core_strcmp(left.__container, right) <= 0;
                }
    public:     friend x::boolean operator<=(const x::character *  left, const x::string &    right)
                {
                    return __core_strcmp(left, right.__container) <= 0;
                }
    public:     friend x::boolean operator> (const x::string &     left, const x::string &    right)
                {
                    return __core_strcmp(left.__container, right.__container) > 0;
                }
    public:     friend x::boolean operator> (const x::string &     left, const x::character * right)
                {
                    return __core_strcmp(left.__container, right) > 0;
                }
    public:     friend x::boolean operator> (const x::character *  left, const x::string &    right)
                {
                    return __core_strcmp(left, right.__container) >= 0;
                }
    public:     friend x::boolean  operator>=(const x::string &    left, const x::string &    right)
                {
                    return __core_strcmp(left.__container, right.__container) > 0;
                }
    public:     friend x::boolean  operator>=(const x::string &    left, const x::character * right)
                {
                    return __core_strcmp(left.__container, right) >= 0;
                }
    public:     friend x::boolean  operator>=(const x::character * left, const x::string &    right)
                {
                    return __core_strcmp(left, right.__container) >= 0;
                }
    public:     friend x::output::stream & operator<<(x::output::stream & os, const string & o)
                {
                    return os << (const char *)(o.__container ? o.__container : "");
                }
    public:     friend x::input::stream & operator>>(x::input::stream & is, string & o)
                {
                    exceptional();
                    return is;
                }
    };
}

#endif // __X__STRING__HH__
