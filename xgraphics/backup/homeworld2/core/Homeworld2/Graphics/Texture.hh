#ifndef   __HOMEWORLD2_GRAPHICS__TEXTURE__HH__
#define   __HOMEWORLD2_GRAPHICS__TEXTURE__HH__

#include <x/string.hh>
#include <x/bytes.hh>
#include <x/math.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Texture
        {
            static x::uint32 size(x::uint32 width, x::uint32 height, x::uint32 mip, x::uint32 format)
            {
                if(format == 0x44585435U) // DXD5
                {
                    return x::max<x::uint32>(1U, width >> (mip + 1U)) * x::max<x::uint32>(1U, height >> (mip + 1U)) * 16U;
                }
                else
                {
                    exceptional();
                }
            }
        }
    }
}

#endif // __HOMEWORLD2_GRAPHICS__TEXTURE__HH__
