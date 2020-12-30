#ifndef   __X_JSON__ARRAY__HH__
#define   __X_JSON__ARRAY__HH__

#include <x/json/value.hh>
#include <x/array.hh>
#include <x/file.hh>

namespace x
{
    namespace json
    {
        class array : public x::json::value
        {
        public:     static x::json::array * from(const x::file & f);
        protected:  x::array<x::json::value *> __values;
        public:     inline x::uint64 size() const { return __values.size(); }
        public:     inline const x::json::value * at(x::uint64 i) const
                    {
                        if(i < __values.size())
                        {
                            return __values[i];
                        }
                        return nullptr;
                    }
        public:     inline x::json::value * at(x::uint64 i)
                    {
                        if(i < __values.size())
                        {
                            return __values[i];
                        }
                        return nullptr;
                    }
        public:     inline const x::array<x::json::value *> & values() const { return __values; }
        public:     virtual void each(x::function<void (const x::var<x::json::value *>::type &)> f) const
                    {
                        __values.each(f);
                    }
        public:     x::output::stream & out(x::output::stream & os) const override
                    {
                        os << "[";
                        for(x::uint64 i = 0; i < __values.size(); i++)
                        {
                            if(__values[i])
                            {
                                os << *__values[i];
                            }
                            else
                            {
                                os << "null";
                            }
                            os << (i + 1 == __values.size() ? "" : ",");
                        }
                        os << "]";
                        return os;
                    }
        public:     x::json::value * clone() const override
                    {
                        return new x::json::array(*this);
                    }
        public:     virtual void push(x::json::value * v)
                    {
                        __values.append(v);
                    }
        protected:  virtual void clear()
                    {
                        __values.each([](x::var<x::json::value *>::type & value){
                            if(value)
                            {
                                delete value;
                                value = nullptr;
                            }
                        });
                        __values.clear();
                    }
        public:     x::json::array & operator=(const x::json::array & o)
                    {
                        if(&o != this)
                        {
                            clear();

                            x::json::value::operator=(o);

                            o.__values.each([this](const x::var<x::json::value *>::type & value){
                                __values.append(value ? value->clone() : nullptr);
                            });
                        }
                        return *this;
                    }
        public:     x::json::array & operator=(x::json::array && o) noexcept
                    {
                        if(&o != this)
                        {
                            x::json::value::operator=(x::move(o));
                            __values = x::move(o.__values);
                        }
                        return *this;
                    }
        public:     array()
                    :   x::json::value(x::json::value::type::array),
                        __values()
                    {
                    }
        public:     array(const x::json::array & o)
                    :      x::json::value(o),
                       __values()
                    {
                        o.__values.each([this](const x::var<x::json::value *>::type & value){
                            __values.append(value ? value->clone() : nullptr);
                        });
                    }
        public:     array(x::json::array && o) noexcept
                    :      x::json::value(x::move(o)),
                        __values(x::move(o.__values))
                    {

                    }
        public:     ~array() override
                    {
                        clear();
                    }
        };
    }
}

#endif // __X_JSON__ARRAY__HH__
