#ifndef   __X__JSON__HH__
#define   __X__JSON__HH__

#include <x/json/value.hh>
#include <x/json/string.hh>
#include <x/json/number.hh>
#include <x/json/array.hh>
#include <x/json/object.hh>

namespace x
{
    namespace json
    {
        namespace cast
        {
            inline x::json::array * array(x::json::value * value)
            {
                if(value)
                {
                    if(value->type() == x::json::value::type::array)
                    {
                        return static_cast<x::json::array *>(value);
                    }
                }

                exceptional();
            }

            inline x::json::string * string(x::json::value * value)
            {
                if(value)
                {
                    if(value->type() == x::json::value::type::string)
                    {
                        return static_cast<x::json::string *>(value);
                    }
                }

                exceptional();
            }

            inline x::json::number * number(x::json::value * value)
            {
                if(value)
                {
                    if(value->type() == x::json::value::type::number)
                    {
                        return static_cast<x::json::number *>(value);
                    }
                }

                exceptional();
            }

            inline x::json::object * object(x::json::value * value)
            {
                if(value)
                {
                    if(value->type() == x::json::value::type::object)
                    {
                        return static_cast<x::json::object *>(value);
                    }
                }

                exceptional();
            }

            inline const x::json::array * array(const x::json::value * value)
            {
                if(value)
                {
                    if(value->type() == x::json::value::type::array)
                    {
                        return static_cast<const x::json::array *>(value);
                    }
                }

                exceptional();
            }

            inline const x::json::string * string(const x::json::value * value)
            {
                if(value)
                {
                    if(value->type() == x::json::value::type::string)
                    {
                        return static_cast<const x::json::string *>(value);
                    }
                }

                exceptional();
            }

            inline const x::json::number * number(const x::json::value * value)
            {
                if(value)
                {
                    if(value->type() == x::json::value::type::number)
                    {
                        return static_cast<const x::json::number *>(value);
                    }
                }

                exceptional();
            }

            inline const x::json::object * object(const x::json::value * value)
            {
                if(value)
                {
                    if(value->type() == x::json::value::type::object)
                    {
                        return static_cast<const x::json::object *>(value);
                    }
                }

                exceptional();
            }
        }
    }
}

#endif // __X__JSON__HH__
