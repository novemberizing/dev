#include "array.hh"

namespace x
{
    namespace json
    {
        x::json::array * array::from(const x::file & f)
        {
            x::json::value * value = x::json::value::from(x::file::text(f));
            if(value)
            {
                if(value->type() != x::json::value::type::array)
                {
                    delete value;
                    value = nullptr;
                    exceptional();
                }
            }
            return static_cast<x::json::array *>(value);
        }
    }
}
