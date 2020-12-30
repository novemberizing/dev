#include "util.hh"

namespace x
{
    namespace graphics
    {
        namespace util
        {
            x::float32 real32(const x::string & o)
            {
                char * end = nullptr;
                float32 value = strtof(o.str(), &end);
                assertion((end - o.str() == o.size() + 1 && end[0] != 'f') && (end - o.str() != o.size()));
                return value;
            }

            x::uint32 uinteger32(const x::string & o)
            {
                char * end = nullptr;
                x::uint32 value = strtol(o.str(), &end, 10);
                assertion(end - o.str() != o.size());
                return value;
            }
        }
    }
}
