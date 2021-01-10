#include "object.hh"

namespace x
{
    namespace json
    {
        x::json::object * object::from(const x::file & f)
        {
            x::json::value * value = x::json::value::from(x::file::text(f));
            if(value)
            {
                if(value->type() != x::json::value::type::object)
                {
                    delete value;
                    value = nullptr;
                    exceptional();
                }
            }
            return static_cast<x::json::object *>(value);
        }
    }
}
