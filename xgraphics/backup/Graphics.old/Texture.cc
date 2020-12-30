#include "Texture.hh"

namespace Homeworld2
{
    // Texture::Texture() :
    //     __name(),
    //     __format(),
    //     __width(),
    //     __height(),
    //     __data()
    // {
    // }
    //
    // Texture::Texture(const Texture & o) :
    //     __name(o.__name),
    //     __format(o.__format),
    //     __width(o.__width),
    //     __height(o.__height),
    //     __data(o.__data)
    // {
    // }
    //
    // Texture::Texture(Texture && o) noexcept :
    //     __name(x::move(o.__name)),
    //     __format(o.__format),
    //     __width(o.__width),
    //     __height(o.__height),
    //     __data(x::move(o.__data))
    // {
    //     o.__format = 0;
    //     o.__width = 0;
    //     o.__height = 0;
    // }
    //
    // Texture::~Texture()
    // {
    //     __format = 0;
    // }
    //
    // Texture & Texture::operator=(Texture && o) noexcept
    // {
    //     if(&o != this)
    //     {
    //         __name = x::move(o.__name);
    //         __format = o.__format;
    //         __width = o.__width;
    //         __height = o.__height;
    //         __data = x::move(o.__data);
    //
    //         o.__format = 0;
    //         o.__width = 0;
    //         o.__height = 0;
    //     }
    //     return *this;
    // }
    //
    // Texture & Texture::operator=(const Texture & o)
    // {
    //     if(&o != this)
    //     {
    //         __name = o.__name;
    //         __format = o.__format;
    //         __width = o.__width;
    //         __height = o.__height;
    //         __data = o.__data;
    //     }
    //     return *this;
    // }
}
