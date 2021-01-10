#include "texture.hh"
#include "application.hh"

namespace x
{
    namespace graphics
    {
        texture::texture(const x::string & name, x::uint32 format, const x::array<x::graphics::mipmap> & images)
        :   __name(name),
            __id(0),
            __format(format),
            mipmaps(images)
        {

        }

        texture::texture(x::string && name, x::uint32 format, const x::array<x::graphics::mipmap> & images)
        :   __name(x::move(name)),
            __id(0),
            __format(format),
            mipmaps(images)
        {

        }

        texture::texture(const x::string & name, const x::graphics::mipmap & image)
        :   __name(name),
            __id(0),
            __format(0),
            mipmaps()
        {
            mipmaps.append(image);
        }

        texture::texture(x::string && name, const x::graphics::mipmap & image)
        :   __name(x::move(name)),
            __id(0),
            __format(0),
            mipmaps()
        {
            mipmaps.append(image);
        }

        texture::texture()
        :   __name(),
            __id(0),
            __format(0),
            mipmaps()
        {
        }

        texture::texture(const x::graphics::texture & o)
        :   __name(o.__name),
            __id(o.__id),
            __format(o.__format),
            mipmaps(o.mipmaps)
        {
        }

        texture::texture(x::graphics::texture && o) noexcept
        :   __name(x::move(o.__name)),
            __id(o.__id),
            __format(o.__format),
            mipmaps(x::move(o.mipmaps))
        {
            o.__id = 0;
            o.__format = 0;
        }

        texture::~texture()
        {
            __id = 0;
            __format = 0;
        }

        x::graphics::texture & texture::operator=(const x::graphics::texture & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __id = o.__id;
                __format = o.__format;
                mipmaps = o.mipmaps;
            }
            return *this;
        }

        x::graphics::texture & texture::operator=(x::graphics::texture && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __id = o.__id;
                __format = o.__format;
                mipmaps = x::move(o.mipmaps);

                o.__id = 0;
                o.__format = 0;
            }
            return *this;
        }

        void texture::load()
        {
            x::graphics::application & application = x::graphics::application::get();

            application.load(*this);
        }

        void texture::unload()
        {
            x::graphics::application & application = x::graphics::application::get();

            application.unload(*this);
        }
    }
}
