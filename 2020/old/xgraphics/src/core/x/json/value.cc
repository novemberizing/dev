#include "value.hh"
#include "number.hh"
#include "string.hh"
#include "object.hh"
#include "array.hh"


namespace x
{
    namespace json
    {
        class context
        {
        protected:  x::string __string;
        protected:  x::uint64 __position;
        public:     x::uint64 remain() const { return __position < __string.size() ? __string.size() - __position : 0; }
        protected:  void whitespace()
                    {
                        for(; __position < __string.size(); __position++)
                        {
                            x::character c = __string[__position];
                            if(c == ' ' || c == '\n' || c == '\t' || c == '\r')
                            {
                                continue;
                            }
                            break;
                        }
                    }
        public:     x::json::number * number()
                    {
                        char * end = 0;
                        double value = __core_strtod(&__string[__position], &end);
                        __position = __position + (end - &__string[__position]);

                        whitespace();

                        return new x::json::number(value);
                    }
        public:     x::json::string * string()
                    {
                        x::string value;
                        __position = __position + 1;
                        for(; __position < __string.size(); __position++)
                        {
                            if(__string[__position] == '\\')
                            {
                                __position = __position + 1;
                                if(__position < __string.size())
                                {
                                    value += __string[__position];
                                }
                                continue;
                            }
                            if(__string[__position] == '\"')
                            {
                                __position = __position + 1;
                                break;
                            }
                            value += __string[__position];
                        }
                        whitespace();
                        return new x::json::string(value);
                    }
        public:     x::json::array * array()
                    {
                        x::json::array * result = new x::json::array();
                        __position = __position + 1;
                        for(; __position < __string.size(); __position++)
                        {
                            if(__string[__position] == ',')
                            {
                                delete result;
                                exceptional();
                            }
                            try
                            {
                                result->push(deserialize());
                            }
                            catch(const x::exception & e)
                            {
                                delete result;
                                exceptional();
                            }

                            if(__string[__position] == ',')
                            {
                                continue;
                            }
                            if(__string[__position] == ']')
                            {
                                __position = __position + 1;
                                whitespace();
                                return result;
                            }
                        }
                        delete result;
                        exceptional();
                    }
        public:     x::string title()
                    {
                        x::string value;
                        __position = __position + 1;
                        for(; __position < __string.size(); __position++)
                        {
                            if(__string[__position] == '\\')
                            {
                                __position = __position + 1;
                                if(__position < __string.size())
                                {
                                    value += __string[__position];
                                }
                                continue;
                            }
                            if(__string[__position] == '\"')
                            {
                                __position = __position + 1;
                                break;
                            }
                            value += __string[__position];
                        }
                        whitespace();
                        return value;
                    }
        public:     x::json::object * object()
                    {
                        x::json::object * result = new x::json::object();
                        __position = __position + 1;
                        for(; __position < __string.size(); __position++)
                        {
                            if(__string[__position] == ',')
                            {
                                delete result;
                                exceptional();
                            }
                            x::string key;
                            try
                            {
                                whitespace();
                                key = title();
                            }
                            catch(const x::exception & e)
                            {
                                delete result;
                                exceptional();
                            }

                            if(__string[__position] == ':')
                            {
                                __position = __position + 1;
                                if(__string.size() <= __position)
                                {
                                    delete result;
                                    exceptional();
                                }
                                whitespace();
                            }
                            try
                            {
                                result->put(key, deserialize());
                            }
                            catch(const x::exception & e)
                            {
                                delete result;
                                exceptional();
                            }

                            if(__string[__position] == ',')
                            {
                                continue;
                            }
                            if(__string[__position] == '}')
                            {
                                __position = __position + 1;
                                whitespace();
                                return result;
                            }
                        }
                        delete result;
                        exceptional();
                    }
        public:     x::json::value * null()
                    {
                        if(__position + 4 < __string.size())
                        {
                            if(__string[__position] == 'n' || __string[__position + 1] == 'u' || __string[__position + 2] == 'l' || __string[__position + 3] == 'l')
                            {
                                __position = __position + 4;
                                return nullptr;
                            }
                        }
                        exceptional();
                    }
        public:     x::json::value * deserialize()
                    {
                        whitespace();
                        if(__string[__position] == '\"')
                        {
                            return string();
                        }
                        else if(__string[__position] == '[')
                        {
                            return array();
                        }
                        else if(__string[__position] == '{')
                        {
                            return object();
                        }
                        else if((48 <= __string[__position] && __string[__position] <= 57) || __string[__position] == '-')
                        {
                            return number();
                        }
                        else if(__string[__position] == 'n')
                        {
                            return null();
                        }
                        else
                        {
                            printf("%c\n", __string[__position]);
                            exceptional();
                        }
                    }
        public:     context & operator=(const context & o)
                    {
                        if(&o != this)
                        {
                            __string = o.__string;
                            __position = o.__position;
                        }
                        return *this;
                    }
        public:     context & operator=(context && o) noexcept
                    {
                        if(&o != this)
                        {
                            __string = x::move(o.__string);
                            __position = o.__position;

                            o.__position = 0;
                        }
                        return *this;
                    }
        public:     context(x::string && s)
                    :   __string(x::move(s)),
                        __position(0)
                    {

                    }
        public:     context(const x::string & s)
                    :   __string(s),
                        __position(0)
                    {

                    }
        public:     context()
                    :   __string(),
                        __position(0)
                    {
                    }
        public:     context(const context & o)
                    :   __string(o.__string),
                        __position(o.__position)
                    {
                    }
        public:     context(context && o) noexcept
                    :   __string(x::move(o.__string)),
                        __position(o.__position)
                    {
                        o.__position = 0;
                    }
        public:     virtual ~context()
                    {
                        __position = 0;
                    }
        };

        x::json::value * value::from(const x::string & s)
        {
            x::json::context context(s);

            x::json::value * result = context.deserialize();

            if(context.remain() > 0)
            {
                delete result;
                result = nullptr;
                exceptional();
            }

            return result;
        }

        x::real value::as::number(x::json::value * value)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::number)
                {
                    x::json::number * o = static_cast<x::json::number *>(value);
                    return o->value();
                }
            }
            exceptional();
        }

        x::real value::as::number(const x::json::value * value)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::number)
                {
                    const x::json::number * o = static_cast<const x::json::number *>(value);
                    return o->value();
                }
            }
            exceptional();
        }

        x::real value::as::number(x::json::value * value, x::real d)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::number)
                {
                    x::json::number * o = static_cast<x::json::number *>(value);
                    return o->value();
                }
            }

            return d;
        }

        x::real value::as::number(const x::json::value * value, x::real d)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::number)
                {
                    const x::json::number * o = static_cast<const x::json::number *>(value);
                    return o->value();
                }
            }

            return d;
        }

        const x::string & value::as::string(x::json::value * value)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::string)
                {
                    x::json::string * o = static_cast<x::json::string *>(value);
                    return o->value();
                }
            }
            exceptional();
        }

        const x::string & value::as::string(const x::json::value * value)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::string)
                {
                    const x::json::string * o = static_cast<const x::json::string *>(value);
                    return o->value();
                }
            }
            exceptional();
        }

        const x::array<x::json::value *> & value::as::array(x::json::value * value)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::array)
                {
                    x::json::array * o = static_cast<x::json::array *>(value);
                    return o->values();
                }
            }
            exceptional();
        }
        
        const x::array<x::json::value *> & value::as::array(const x::json::value * value)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::array)
                {
                    const x::json::array * o = static_cast<const x::json::array *>(value);
                    return o->values();
                }
            }
            exceptional();
        }

        x::reality::vector value::as::vector(x::json::value * value)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::array)
                {
                    x::json::array * o = static_cast<x::json::array *>(value);

                    x::reality::vector result;

                    result[0] = x::json::value::as::number(o->at(0));
                    result[1] = x::json::value::as::number(o->at(1));
                    result[2] = x::json::value::as::number(o->at(2));
                    result[3] = x::json::value::as::number(o->at(3), 0);

                    return result;
                }
            }
            exceptional();
        }

        x::reality::vector value::as::vector(const x::json::value * value)
        {
            if(value)
            {
                if(value->type() == x::json::value::type::array)
                {
                    const x::json::array * o = static_cast<const x::json::array *>(value);

                    x::reality::vector result;

                    result[0] = x::json::value::as::number(o->at(0));
                    result[1] = x::json::value::as::number(o->at(1));
                    result[2] = x::json::value::as::number(o->at(2));
                    result[3] = x::json::value::as::number(o->at(3), 0);

                    return result;
                }
            }
            exceptional();
        }
    }
}
