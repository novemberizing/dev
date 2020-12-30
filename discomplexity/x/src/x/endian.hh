#ifndef   __X__ENDIAN__HH__
#define   __X__ENDIAN__HH__

#include <x/type.hh>

namespace x
{
    class endian
    {
    public:     static x::uint32 convert(x::uint32 v)
                {
                    return  ((v & 0xFF000000U) >> 24U) |
                            ((v & 0x00FF0000U) >>  8U) |
                            ((v & 0x0000FF00U) <<  8U) |
                            ((v & 0x000000FFU) << 24U);
                }
    };
}

#endif // __X__ENDIAN__HH__
