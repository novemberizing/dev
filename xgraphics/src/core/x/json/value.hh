#ifndef   __X_JSON__VALUE__HH__
#define   __X_JSON__VALUE__HH__

#include <x/output.stream.hh>
#include <x/string.hh>
#include <x/reality/vector.hh>

namespace x
{
    namespace json
    {
        class value
        {
        public:     class type
                    {
                    public:     static const x::uint32 none = 0;
                    public:     static const x::uint32 string = 1;
                    public:     static const x::uint32 number = 2;
                    public:     static const x::uint32 array = 3;
                    public:     static const x::uint32 object = 4;
                    };
        public:     class as
                    {
                    public:     static const x::string & string(x::json::value * value);
                    public:     static const x::string & string(const x::json::value * value);
                    public:     static x::real number(x::json::value * value, x::real d);
                    public:     static x::real number(const x::json::value * value, x::real d);
                    public:     static x::real number(x::json::value * value);
                    public:     static x::real number(const x::json::value * value);
                    public:     static const x::array<x::json::value *> & array(x::json::value * value);
                    public:     static const x::array<x::json::value *> & array(const x::json::value * value);
                    public:     static x::reality::vector vector(x::json::value * value);
                    public:     static x::reality::vector vector(const x::json::value * value);
                    };
        public:     static x::json::value * from(const x::string & s);
        protected:  x::uint32 __type;
        public:     inline x::uint32 type() const { return __type; }
        public:     virtual x::json::value * clone() const = 0;
        public:     virtual x::output::stream & out(x::output::stream & os) const
                    {
                        return os;
                    }
        public:     x::json::value & operator=(const x::json::value & o)
                    {
                        if(&o != this)
                        {
                            __type = o.__type;
                        }
                        return *this;
                    }
        public:     x::json::value & operator=(x::json::value && o) noexcept
                    {
                        if(&o != this)
                        {
                            __type = o.__type;

                            o.__type = x::json::value::type::none;
                        }
                        return *this;
                    }
        protected:  value(x::uint32 type)
                    :   __type(type)
                    {
                    }
        public:     value()
                    :   __type(x::json::value::type::none)
                    {
                    }
        public:     value(const x::json::value & o)
                    :   __type(o.__type)
                    {
                    }
        public:     value(x::json::value && o) noexcept
                    :   __type(o.__type)
                    {
                        o.__type = x::json::value::type::none;
                    }
        public:     virtual ~value()
                    {
                        __type = x::json::value::type::none;
                    }
        public:     friend x::output::stream & operator<<(x::output::stream & os, const x::json::value & o)
                    {
                        return o.out(os);
                    }
        };
    }
}

#endif // __X_JSON__VALUE__HH__
