#ifndef   __X__REAL32__HH__
#define   __X__REAL32__HH__

#include <x/core.hh>
#include <x/string.hh>
#include <x/variable.hh>

namespace x
{
    class real32 : public x::variable<x::float32>
    {
    public:     static x::float32 from(const x::string & o)
                {
                    char * end = nullptr;
                    float32 value = __core_strtof(o.str(), &end);
                    assertion((end - o.str() == o.size() + 1 && end[0] != 'f') && (end - o.str() != o.size()));
                    return value;
                }
    };
}

#endif // __X__REAL32__HH__
