#ifndef   __X__STRING__HH__
#define   __X__STRING__HH__

#include <x/output/stream.hh>
#include <x/input/stream.hh>
#include <x/array.hh>

// #include <cstring>  // TODO: REMOVE THIS

namespace x
{
    class string : protected array<char>
    {
    public:     virtual const char * str() const
                {
                    return this->__container;
                }
    public:     x::string sub(x::uint64 offset, x::uint64 length) const
                {
                    if(__size < offset + length)
                    {
                        exceptional();
                    }
                    return x::string(const_cast<const char *>(&__container[offset]), length);
                }
    public:     virtual x::array<x::string> split(function<x::string (const char *, x::uint64 &, x::uint64)> f) const
                {
                    x::array<x::string> result;
                    for(x::uint64 i = 0; i < __size;)
                    {
                        x::uint64 index = 0;
                        x::string s = f(&__container[i], index, __size - i);
                        i = i + index;
                        result.push(std::move(s));
                    }
                    return result;
                }
    public:     virtual x::array<x::string> split(char c) const
                {
                    return split(c, __size);
                }
    public:     virtual x::array<x::string> split(char c, x::uint64 until) const
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
    public:     uint64 size() const override
                {
                    return array<char>::size();
                }
    protected:  void add(const char & item) override
                {
                    array<char>::add(item);
                    this->__container[this->__size] = 0;
                }
    protected:  void add(char && item) override
                {
                    array<char>::add(x::move(item));
                    this->__container[this->__size] = 0;
                }
    public:     void push(const char & item) override
                {
                    array<char>::push(item);
                    this->__container[this->__size] = 0;
                }
    public:     void push(char && item) override
                {
                    array<char>::push(x::move(item));
                    this->__container[this->__size] = 0;
                }
    public:     void push(const char & item, x::uint64 n) override
                {
                    array<char>::push(item, n);
                    this->__container[this->__size] = 0;
                }
    public:     void push(const char * source, x::uint64 n) override
                {
                    array<char>::push(source, n);
                    this->__container[this->__size] = 0;
                }
    public:     void push(array<char> && o) override
                {
                    array<char>::push(x::move(o));
                    this->__container[this->__size] = 0;
                }
    public:     void push(const array<char> & o) override
                {
                    array<char>::push(o);
                    this->__container[this->__size] = 0;
                }
    public:     void push(const x::initializer<char> & list) override
                {
                    array<char>::push(list);
                    this->__container[this->__size] = 0;
                }
    public:     string & operator+=(char c)
                {
                    this->push(c);
                    return *this;
                }
    public:     string & operator+=(const char * s)
                {
                    this->push(s, s != nullptr ? __strlen(s) : 0);
                    return *this;
                }
    public:     string & operator+=(const string & o)
                {
                    if(&o != this)
                    {
                        this->push(o.__container, o.__size);
                    }
                    else
                    {
                        string s = o;
                        this->push(s.__container, s.__size);
                    }
                    return *this;
                }
    public:     string & operator+=(string && o)
                {
                    if(&o != this)
                    {
                        this->push(o.__container, o.__size);
                    }
                    else
                    {
                        string s = o;
                        this->push(s.__container, s.__size);
                    }
                    return *this;
                }
    public:     string & operator=(char c)
                {
                    this->clear();
                    this->push(c);
                    return *this;
                }
    public:     string & operator=(const char * s)
                {
                    this->__size = 0L;
                    this->push(s, s != nullptr ? __strlen(s) : 0);
                    return *this;
                }
    public:     string & operator=(const string & o)
                {
                    if(&o != this)
                    {
                        array<char>::operator=(o);
                    }
                    return *this;
                }
    public:     string & operator=(string && o) noexcept
                {
                    if(&o != this)
                    {
                        array<char>::operator=(x::move(o));
                    }
                    return *this;
                }
    public:     string(char *&& s, uint64 n) : array<char>(x::move(s), n, n + 1)
                {
                    this->__container[this->__size] = 0;
                }
    public:     string(const char * s) : array<char>()
                {
                    this->push(s, s != nullptr ? __strlen(s) : 0);
                }
    public:     string(const char * s, uint64 len) : array<char>()
                {
                    this->push(s, len);
                }
    public:     string(char c) : array<char>()
                {
                    this->push(c);
                }
    public:     string(char c, uint64 n) : array<char>()
                {
                    this->push(c, n);
                }
    public:     string() : array<char>()
                {
                    this->__container[this->__size] = 0;
                }
    public:     string(const string & o) : array<char>(o)
                {
                    this->__container[this->__size] = 0;
                }
    public:     string(string && o) noexcept : array<char>(x::move(o))
                {
                }
    public:     ~string() override
                {
                }
    public:     friend string operator+(const string & left, const string & right)
                {
                    string out = left;
                    out += right;
                    return out;
                }
    public:     friend string operator+(const string & left, const char *   right)
                {
                    string out = left;
                    out += right;
                    return out;
                }
    public:     friend string operator+(const string & left, char           right)
                {
                    string out = left;
                    out += right;
                    return out;
                }
    public:     friend string operator+(const char *   left, const string & right)
                {
                    string out = left;
                    out += left;
                    return out;
                }
    public:     friend string operator+(char           left, const string & right)
                {
                    string out = left;
                    out += right;
                    return out;
                }
    public:     friend x::boolean operator==(const string & left, const string & right)
                {
                    return left.__size == right.__size && __strcmp(left.__container, right.__container) == 0;
                }
    public:     friend x::boolean operator==(const string & left, const char *   right)
                {
                    uint64 len = (right ? __strlen(right) : 0);
                    return left.__size == len && __strcmp(left.__container, right) == 0;
                }
    public:     friend x::boolean operator==(const string & left, char           right)
                {
                    return left.__size == 1 && left.__container[0] == right;
                }
    public:     friend x::boolean operator==(const char *   left, const string & right)
                {
                    uint64 len = (left ? __strlen(left) : 0);
                    return right.__size == len && __strcmp(right.__container, left) == 0;
                }
    public:     friend x::boolean operator==(char           left, const string & right)
                {
                    return right.__size == 1 && right.__container[0] == right;
                }
    public:     friend x::boolean operator!=(const string & left, const string & right)
                {
                    return left.__size != right.__size || __strcmp(left.__container, right.__container) != 0;
                }
    public:     friend x::boolean operator!=(const string & left, const char *   right)
                {
                    uint64 len = (right ? __strlen(right) : 0);
                    return left.__size != len || __strcmp(left.__container, right) != 0;
                }
    public:     friend x::boolean operator!=(const string & left, char           right)
                {
                    return left.__size != 1 || left.__container[0] != right;
                }
    public:     friend x::boolean operator!=(const char *   left, const string & right)
                {
                    uint64 len = (left ? __strlen(left) : 0);
                    return right.__size != len || __strcmp(right.__container, left) != 0;
                }
    public:     friend x::boolean operator!=(char           left, const string & right)
                {
                    return right.__size != 1 && right.__container[0] != right;
                }
    public:     friend x::boolean operator< (const string & left, const string & right)
                {
                    return __strcmp(left.__container, right.__container) < 0;
                }
    public:     friend x::boolean operator< (const string & left, const char *   right)
                {
                    return __strcmp(left.__container, right) < 0;
                }
    public:     friend x::boolean operator< (const char *   left, const string & right)
                {
                    return __strcmp(left, right.__container) <= 0;
                }
    public:     friend x::boolean operator<=(const string & left, const string & right)
                {
                    return __strcmp(left.__container, right.__container) < 0;
                }
    public:     friend x::boolean operator<=(const string & left, const char *   right)
                {
                    return __strcmp(left.__container, right) <= 0;
                }
    public:     friend x::boolean operator<=(const char *   left, const string & right)
                {
                    return __strcmp(left, right.__container) <= 0;
                }
    public:     friend x::boolean operator> (const string & left, const string & right)
                {
                    return __strcmp(left.__container, right.__container) > 0;
                }
    public:     friend x::boolean operator> (const string & left, const char *   right)
                {
                    return __strcmp(left.__container, right) > 0;
                }
    public:     friend x::boolean operator> (const char *   left, const string & right)
                {
                    return __strcmp(left, right.__container) >= 0;
                }
    public:     friend x::boolean  operator>=(const string & left, const string & right)
                {
                    return __strcmp(left.__container, right.__container) > 0;
                }
    public:     friend x::boolean  operator>=(const string & left, const char *   right)
                {
                    return __strcmp(left.__container, right) >= 0;
                }
    public:     friend x::boolean  operator>=(const char *   left, const string & right)
                {
                    return __strcmp(left, right.__container) >= 0;
                }
    public:     friend x::output::stream & operator<<(x::output::stream & os, const string & o)
                {
                    return os << (const char *)(o.__container ? o.__container : "");
                }
    public:     friend x::input::stream & operator>>(x::input::stream & is, string & o)
                {

                    return is;
                }
    };
}

#endif // __X__STRING__HH__
