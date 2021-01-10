#ifndef   __HOMEWORLD2__TEXTURE__HH__
#define   __HOMEWORLD2__TEXTURE__HH__

#include <x/string.hh>
#include <x/bytes.hh>
#include <x/math.hh>

namespace Homeworld2
{
    class Texture
    {
    public:     static x::uint32 size(x::uint32 width, x::uint32 height, x::uint32 mip, x::uint32 format)
                {
                    if(format == 0x44585435U) // DXD5
                    {
                        return x::math::max<x::uint32>(1U, width >> (mip + 1U)) * x::math::max(1U, height >> (mip + 1U)) * 16U;
                    }
                    else
                    {
                        exceptional();
                    }
                }
    protected:  x::string __name;
    protected:  x::uint32 __format;
    protected:  x::uint32 __width;
    protected:  x::uint32 __height;
    protected:  x::bytes __data;
    public:     inline const x::string & name() const { return __name; }
    public:     inline const x::bytes & data() const { return __data; }
    public:     inline x::uint32 format() const { return __format; }
    public:     inline x::uint32 width() const { return __width; }
    public:     inline x::uint32 height() const { return __height; }
    public:     inline void name(x::string && v){ __name = x::move(v); }
    public:     inline void name(const x::string & v){ __name = v; }
    public:     inline void format(x::uint32 v){ __format = v; }
    public:     inline void width(x::uint32 v){ __width = v; }
    public:     inline void height(x::uint32 v){ __height = v; }
    public:     inline void data(x::bytes && v){ __data = x::move(v); }
    public:     Texture & operator=(const Texture & o);
    public:     Texture & operator=(Texture && o) noexcept;
    public:     Texture();
    public:     Texture(const Texture & o);
    public:     Texture(Texture && o) noexcept;
    public:     virtual ~Texture();
    public:     friend x::output::stream & operator<<(x::output::stream & os, const Texture & o)
                {
                    os << "{";
                    os << "\"name\": " << o.__name << ",";
                    os << "\"format\": " << o.__format << ",";
                    os << "\"width\": " << o.__width << ",";
                    os << "\"height\": " << o.__height;
                    os << "}";
                    return os;
                }
    };
}

#endif // __HOMEWORLD2__TEXTURE__HH__
