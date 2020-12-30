#ifndef   __X_JSON__OBJECT__HH__
#define   __X_JSON__OBJECT__HH__

#include <x/json/value.hh>
#include <x/map.hh>
#include <x/file.hh>

namespace x
{
    namespace json
    {
        class object : public x::json::value
        {
        public:     static x::json::object * from(const x::file & f);
        protected:  x::map<x::string, x::json::value *> __children;
        public:     inline const x::map<x::string, x::json::value *> & children() const { return __children; }
        public:     const x::json::value * get(const x::string & key) const
                    {
                        try
                        {
                            return __children[key];
                        }
                        catch(const x::exception & e)
                        {
                            return nullptr;
                        }
                    }
        public:     x::json::value * get(const x::string & key)
                    {
                        try
                        {
                            return __children[key];
                        }
                        catch(const x::exception & e)
                        {
                            return nullptr;
                        }
                    }
        public:     x::output::stream & out(x::output::stream & os) const override
                    {
                        os << "{";
                        x::uint64 count = 0;
                        __children.each([&os, this, &count](const x::string & name, const x::var<x::json::value *>::type & value){
                            os << "\"" << name << "\":";
                            if(value)
                            {
                                value->out(os);
                            }
                            else
                            {
                                os << "null";
                            }
                            os << (++count == __children.size() ? "" : ",");
                        });
                        os << "}";
                        return os;
                    }
        public:     virtual void put(const x::string & key, x::json::value * value)
                    {
                        try
                        {
                            x::json::value * v = __children[key];
                            if(v)
                            {
                                delete v;
                            }
                        }
                        catch(const x::exception & e)
                        {

                        }
                        __children.put(key, value);
                    }
        public:     x::json::value * clone() const override
                    {
                        return new x::json::object(*this);
                    }
        public:     virtual void clear()
                    {
                        __children.each([](const x::string & name, x::var<x::json::value *>::type & value){
                            if(value)
                            {
                                delete value;
                                value = nullptr;
                            }
                        });
                        __children.clear();
                    }
        public:     x::json::object & operator=(const x::json::object & o)
                    {
                        if(&o != this)
                        {
                            clear();

                            x::json::value::operator=(o);

                            o.__children.each([this](const x::string & name, const x::var<x::json::value *>::type & value){
                                __children.put(name, value ? value->clone() : nullptr);
                            });
                        }
                        return *this;
                    }
        public:     x::json::object & operator=(x::json::object && o) noexcept
                    {
                        if(&o != this)
                        {
                            clear();

                            x::json::value::operator=(x::move(o));
                            __children = x::move(o.__children);
                        }
                        return *this;
                    }
        public:     object()
                    :   x::json::value(x::json::value::type::object),
                        __children()
                    {
                    }
        public:     object(const x::json::object & o)
                    :   x::json::value(o),
                        __children()
                    {
                        o.__children.each([this](const x::string & name, const x::var<x::json::value *>::type & value){
                            __children.put(name, value ? value->clone() : nullptr);
                        });
                    }
        public:     object(x::json::object && o) noexcept
                    :  x::json::value(x::move(o)),
                        __children(x::move(o.__children))
                    {
                    }
        public:     virtual ~object()
                    {
                        clear();
                    }
        };
    }
}

#endif // __X_JSON__OBJECT__HH__
