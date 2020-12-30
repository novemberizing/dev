#ifndef   __X__UINTEGER32__HH__
#define   __X__UINTEGER32__HH__

#include <x/core.hh>
#include <x/string.hh>
#include <x/bytes.hh>
#include <x/variable.hh>

namespace x
{
    class uinteger32 : public x::variable<x::uint32>
    {
    public:     static x::uint32 invert(x::uint32 v)
                {
                    return  ((v & 0xFF000000U) >> 24U) |
                            ((v & 0x00FF0000U) >>  8U) |
                            ((v & 0x0000FF00U) <<  8U) |
                            ((v & 0x000000FFU) << 24U);
                }
    public:     static x::uint32 from(const x::string & o)
                {
                    char * end = nullptr;
                    x::uint32 value = __core_strtol(o.str(), &end, 10);
                    assertion(end - o.str() != o.size());
                    return value;
                }
    public:     static x::uint32 from(const x::bytes & o)
                {
                    assertion(o.size() != 4);
                    x::uint32 value = *((const x::uint32 *) o.data());
                    return value;
                }
    public:     static x::uint32 from(const x::byte * data, x::uint32 offset)
                {
                    x::uint32 value = *((const x::uint32 *) &data[offset]);
                    return value;
                }
    };
}

#endif // __X__UINTEGER32__HH__
