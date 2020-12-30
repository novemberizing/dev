#include "mipmap.hh"

namespace x
{
    namespace graphics
    {
        mipmap::mipmap(x::uint32 width, x::uint32 height, x::bytes && bytes)
        :   x::graphics::image(width, height, x::move(bytes))
        {

        }

        mipmap::mipmap(x::uint32 width, x::uint32 height, const x::bytes & bytes)
        :   x::graphics::image(width, height, bytes)
        {

        }

        mipmap::mipmap()
        :   x::graphics::image()
        {
        }

        mipmap::mipmap(const x::graphics::mipmap & o)
        :   x::graphics::image(o)
        {
        }

        mipmap::mipmap(x::graphics::mipmap && o) noexcept
        :   x::graphics::image(x::move(o))
        {
        }

        mipmap::~mipmap()
        {
        }

        x::graphics::mipmap & mipmap::operator=(const x::graphics::mipmap & o)
        {
            if(&o != this)
            {
                x::graphics::image::operator=(o);
            }
            return *this;
        }

        x::graphics::mipmap & mipmap::operator=(x::graphics::mipmap && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::image::operator=(o);
            }
            return *this;
        }
    }
}
