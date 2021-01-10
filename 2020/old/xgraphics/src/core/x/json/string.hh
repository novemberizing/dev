#ifndef   __X_JSON__STRING__HH__
#define   __X_JSON__STRING__HH__

#include <x/json/value.hh>
#include <x/string.hh>

namespace x
{
    namespace json
    {
        class string : public x::json::value
        {
        protected:  x::string __value;
        public:     const x::string & value() const { return __value; }
        public:     x::output::stream & out(x::output::stream & os) const override
                    {
                        os << "\"" << __value << "\"";
                        return os;
                    }
        public:     x::json::value * clone() const override { return new x::json::string(*this); }
        public:     x::json::string & operator=(const x::json::string & o)
                    {
                        if(&o != this)
                        {
                            x::json::value::operator=(o);

                            __value = o.__value;
                        }
                        return *this;
                    }
        public:     x::json::string & operator=(x::json::string && o) noexcept
                    {
                        if(&o != this)
                        {
                            x::json::value::operator=(x::move(o));

                            __value = x::move(o.__value);
                        }
                        return *this;
                    }
        public:     string(const x::string & s)
                    :   x::json::value(x::json::value::type::string),
                        __value(s)
                    {
                    }
        public:     string(x::string && s)
                    :   x::json::value(x::json::value::type::string),
                        __value(x::move(s))
                    {
                    }
        public:     string()
                    :   x::json::value(x::json::value::type::string),
                        __value()
                    {
                    }
        public:     string(const x::json::string & o)
                    :   x::json::value(o),
                        __value(o.__value)
                    {
                    }
        public:     string(x::json::string && o) noexcept
                    :   x::json::value(x::move(o)),
                        __value(x::move(o.__value))
                    {
                    }
        public:     ~string() override
                    {
                    }
        public:     friend x::output::stream & operator<<(x::output::stream & os, const x::json::string & o)
                    {
                        return o.out(os);
                    }
        };
    }
}

#endif // __X_JSON__STRING__HH__
