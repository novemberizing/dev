#ifndef   __X__PARAMETER__HH__
#define   __X__PARAMETER__HH__

#include <x/variable.hh>

namespace x
{
    template <typename T>
    class parameter : public x::variable
    {
    protected:  T __value;
    public:     virtual const T & value() const
                {
                    return __value;
                }
    public:     virtual void value(const T & v)
                {
                    __value = v;
                }
    public:     virtual void value(T && v)
                {
                    __value = x::move(v);
                }
    protected:  parameter & operator=(const parameter & o)
                {
                    if(&o != this)
                    {
                        x::variable::operator=(o);
                        __value = o.__value;
                    }
                    return *this;
                }
    protected:  parameter<T> & operator=(parameter<T> && o) noexcept
                {
                    if(&o != this)
                    {
                        x::variable::operator=(x::move(o));
                        __value = x::move(o.__value);
                    }
                    return *this;
                }
    public:     parameter<T> & operator=(const T & v)
                {
                    __value = v;
                    return *this;
                }
    public:     parameter<T> & operator=(T && v)
                {
                    __value = x::move(v);
                    return *this;
                }
    protected:  parameter(const x::string & name, x::uint64 type) :
                    x::variable(name, type),
                    __value()
                {
                }
    protected:  parameter(x::string && name, x::uint64 type) :
                    x::variable(x::move(name), type),
                    __value()
                {
                }
    protected:  parameter(const x::string & name, x::uint64 type, const T & value) :
                    x::variable(name, type),
                    __value(value)
                {
                }
    protected:  parameter(const x::string & name, x::uint64 type, T && value) :
                    x::variable(name, type),
                    __value(x::move(value))
                {
                }
    protected:  parameter(x::string && name, x::uint64 type, const T & value) :
                    x::variable(x::move(name), type),
                    __value(value)
                {
                }
    protected:  parameter(x::string && name, x::uint64 type, T && value) :
                    x::variable(x::move(name), type),
                    __value(x::move(value))
                {
                }
    protected:  parameter() = delete;
    protected:  parameter(const parameter<T> & o) :
                    x::variable(o),
                    __value(o.__value)
                {
                }
    protected:  parameter(parameter && o) noexcept :
                    x::variable(x::move(o)),
                    __value(x::move(o.__value))
                {
                }
    public:     ~parameter()
                {
                }
    };
}

#endif // __X__PARAMETER__HH__
