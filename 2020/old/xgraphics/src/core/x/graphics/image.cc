#include "image.hh"

namespace x
{
    namespace graphics
    {
        image::image(x::uint32 width, x::uint32 height, x::bytes && bytes)
        :   __id(0),
            __width(width),
            __height(height),
            __bytes(x::move(bytes))
        {

        }

        image::image(x::uint32 width, x::uint32 height, const x::bytes & bytes)
        :   __id(0),
            __width(width),
            __height(height),
            __bytes(bytes)
        {

        }

        image::image()
        :   __id(0),
            __width(0),
            __height(0),
            __bytes()
        {
        }

        image::image(const x::graphics::image & o)
        :   __id(o.__id),
            __width(o.__width),
            __height(o.__height),
            __bytes(o.__bytes)
        {
        }

        image::image(x::graphics::image && o) noexcept
        :   __id(o.__id),
            __width(o.__width),
            __height(o.__height),
            __bytes(x::move(o.__bytes))
        {
            o.__id = 0;
            o.__width = 0;
            o.__height = 0;
        }

        image::~image()
        {
            __id = 0;
            __width = 0;
            __height = 0;
        }

        x::graphics::image & image::operator=(x::graphics::image && o) noexcept
        {
            if(&o != this)
            {
                __id = o.__id;
                __width = o.__width;
                __height = o.__height;
                __bytes = x::move(o.__bytes);

                o.__id = 0;
                o.__width = 0;
                o.__height = 0;
            }
            return *this;
        }

        x::graphics::image & image::operator=(const x::graphics::image & o)
        {
            if(&o != this)
            {
                __id = o.__id;
                __width = o.__width;
                __height = o.__height;
                __bytes = o.__bytes;
            }
            return *this;
        }
    }
}
