#ifndef   __X__VARIABLE__HH__
#define   __X__VARIABLE__HH__

#include <x/core.hh>

namespace x
{
    template <typename T>
    class variable
    {
    protected:  T __value;
    public:     virtual const T & value() const { return __value; }
    public:     virtual void value(const T & v){ __value = v; }
    public:     virtual void value(T && v){ __value = x::move(v); }
    public:     x::variable<T> & operator=(const x::variable<T> & o)
                {
                    if(&o != this)
                    {
                        __value = o.__value;
                    }
                    return *this;
                }
    public:     x::variable<T> & operator=(x::variable<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        __value = x::move(o.__value);
                    }
                    return *this;
                }
    public:     variable(const T & v)
                :   __value(v)
                {
                }
    public:     variable()
                :   __value()
                {
                }
    public:     variable(const x::variable<T> & o)
                :   __value(o.__value)
                {
                }
    public:     variable(x::variable<T> && o) noexcept
                :   __value(x::move(o.__value))
                {
                }
    public:     virtual ~variable()
                {
                }
    };
}

#endif // __X__VARIABLE__HH__
