#include "Primitive.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Primitive::Primitive()
        :   x::graphics::primitive(),
            __index(x::invalid),
            __material(nullptr),
            __textures(nullptr)
        {
        }

        Primitive::Primitive(const Primitive & o)
        :   x::graphics::primitive(o),
            __index(o.__index),
            __material(o.__material),
            __textures(o.__textures)
        {
        }

        Primitive::Primitive(Primitive && o) noexcept
        :   x::graphics::primitive(x::move(o)),
            __index(o.__index),
            __material(o.__material),
            __textures(o.__textures)
        {
            o.__index = x::invalid;
            o.__material = nullptr;
            o.__textures = nullptr;
        }

        Primitive::~Primitive()
        {
            __index = x::invalid;
            __material = nullptr;
            __textures = nullptr;
        }

        Primitive & Primitive::operator=(const Primitive & o)
        {
            if(&o != this)
            {
                x::graphics::primitive::operator=(o);
                __index = o.__index;
                __material = o.__material;
                __textures = o.__textures;
            }
            return *this;
        }

        Primitive & Primitive::operator=(Primitive && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::primitive::operator=(x::move(o));
                __index = o.__index;
                __material = o.__material;
                __textures = o.__textures;

                o.__index = 0;
                o.__material = nullptr;
                o.__textures = nullptr;
            }
            return *this;
        }

        x::boolean Primitive::bind(const x::string & name, x::uint32 id, const x::reality::matrix & matrix)
        {
            if(!x::graphics::primitive::bind(name, id, matrix))
            {
                x::graphics::application & application = x::graphics::application::get();

                if(name == "textureSampler")
                {
                    // x::console::out << "textureSampler" << x::endl << x::flush;

                    x::array<x::graphics::texture> & textures = *__textures;
                    x::graphics::texture & texture = textures[__material->diffuse()];

                    application.bind(texture);
                    application.bind(id, 0);    // TEXTURE SLOT
                }
            }
        }
    }
}
