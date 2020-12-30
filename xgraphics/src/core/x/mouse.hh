#ifndef   __X__MOUSE__HH__
#define   __X__MOUSE__HH__

#include <x/core.hh>

namespace x
{
    namespace mouse
    {
        static const x::uint32 down = 1;
        static const x::uint32 up = 2;
        static const x::uint32 left = 3;
        static const x::uint32 middle = 4;
        static const x::uint32 right = 5;

        namespace scroll
        {
            static const x::uint32 up = 6;
            static const x::uint32 down = 7;
        }
    }
}

#endif // __X__MOUSE__HH__
