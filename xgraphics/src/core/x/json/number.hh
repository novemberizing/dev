#ifndef   __X_JSON__NUMBER__HH__
#define   __X_JSON__NUMBER__HH__

#include <x/json/value.hh>

namespace x
{
    namespace json
    {
        class number : public x::json::value
        {
        public:     static x::json::number * from(const x::string & s);
        protected:  x::float64 __value;
        public:     inline x::float64 value() const { return __value; }
        public:     x::output::stream & out(x::output::stream & os) const override
                    {
                        os << __value;
                        return os;
                    }
        public:     x::json::value * clone() const override { return new x::json::number(*this); }
        public:     x::json::number & operator=(const x::json::number & o)
                    {
                        if(&o != this)
                        {
                            x::json::value::operator=(o);

                            __value = o.__value;
                        }
                        return *this;
                    }
        public:     x::json::number & operator=(x::json::number && o) noexcept
                    {
                        if(&o != this)
                        {
                            x::json::value::operator=(x::move(o));

                            __value = o.__value;

                            o.__value = 0;
                        }
                        return *this;
                    }
        public:     number(x::float64 v)
                    :   x::json::value(x::json::value::type::number),
                        __value(v)
                    {
                    }
        public:     number()
                    :   x::json::value(x::json::value::type::number),
                        __value(0)
                    {
                    }
        public:     number(const x::json::number & o)
                    :   x::json::value(o),
                        __value(o.__value)
                    {
                    }
        public:     number(x::json::number && o) noexcept
                    :   x::json::value(x::move(o)),
                        __value(o.__value)
                    {
                        o.__value = 0;
                    }
        public:     ~number() override
                    {
                    }
        public:     friend x::output::stream & operator<<(x::output::stream & os, const x::json::number & o)
                    {
                        return o.out(os);
                    }
        };
    }
}

#endif // __X_JSON__NUMBER__HH__
