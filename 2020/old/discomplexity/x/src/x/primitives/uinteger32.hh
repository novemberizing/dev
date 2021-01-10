#ifndef   __X_PRIMITVES__UINTEGER32__HH__
#define   __X_PRIMITVES__UINTEGER32__HH__

#include <x/output/stream.hh>
#include <x/parameter.hh>

namespace x
{
    class uinteger32 : public x::parameter<x::uint32>
    {
    public:     uinteger32 & operator=(const uinteger32 & o)
                {
                    if(&o != this)
                    {
                        x::parameter<x::uint32>::operator=(o);
                    }
                    return *this;
                }
    public:     uinteger32 & operator=(uinteger32 && o) noexcept
                {
                    if(&o != this)
                    {
                        x::parameter<x::uint32>::operator=(x::move(o));
                    }
                    return *this;
                }
    public:     uinteger32 & operator=(x::uint32 v)
                {
                    x::parameter<x::uint32>::operator=(v);
                    return *this;
                }
    public:     uinteger32(const x::string & name) :
                    x::parameter<x::uint32>(name, x::variable::uinteger32_type, 0)
                {
                }
    public:     uinteger32(x::string && name) :
                    x::parameter<x::uint32>(name, x::variable::uinteger32_type, 0)
                {
                }
    public:     uinteger32(const x::string & name, x::uint32 value) :
                    x::parameter<x::uint32>(name, x::variable::uinteger32_type, value)
                {
                }
    public:     uinteger32(x::string && name, x::uint32 value) :
                    x::parameter<x::uint32>(name, x::variable::uinteger32_type, value)
                {
                }
    public:     uinteger32() = delete;
    public:     uinteger32(const x::uinteger32 & o) :
                    x::parameter<x::uint32>(o)
                {
                }
    public:     uinteger32(x::uinteger32 && o) noexcept :
                    x::parameter<x::uint32>(x::move(o))
                {
                }
    public:     ~uinteger32() override
                {
                }
    public:     friend x::output::stream & operator<<(x::output::stream & os, const x::uinteger32 & o)
                {
                    os << "{";
                    os << o.name() << ": ";
                    os << o.__value;
                    os << "}";
                    return os;
                }
    };
}

#endif // __X_PRIMITVES__UINTEGER32__HH__
