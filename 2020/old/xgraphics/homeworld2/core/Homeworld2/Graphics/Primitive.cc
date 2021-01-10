#include "Primitive.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Primitive::Primitive()
        :   x::graphics::primitive(),
            __index(x::invalid),
            __material(nullptr)
        {
        }

        Primitive::Primitive(const Homeworld2::Graphics::Primitive & o)
        :   x::graphics::primitive(o),
            __index(o.__index),
            __material(o.__material)
        {
        }

        Primitive::Primitive(Homeworld2::Graphics::Primitive && o) noexcept
        :   x::graphics::primitive(x::move(o)),
            __index(o.__index),
            __material(o.__material)
        {
            o.__index = x::invalid;
            o.__material = nullptr;
        }

        Primitive::~Primitive()
        {
            __index = x::invalid;
            __material = nullptr;
        }

        Homeworld2::Graphics::Primitive & Primitive::operator=(const Homeworld2::Graphics::Primitive & o)
        {
            if(&o != this)
            {
                x::graphics::primitive::operator=(o);

                __index = o.__index;
                __material= o.__material;
            }
            return *this;
        }

        Homeworld2::Graphics::Primitive & Primitive::operator=(Homeworld2::Graphics::Primitive && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::primitive::operator=(x::move(o));

                __index = o.__index;
                __material= o.__material;

                o.__index = x::invalid;
                o.__material = nullptr;
            }
            return *this;
        }


        Homeworld2::Graphics::Objects::Base * Primitive::build(x::array<x::graphics::texture> & textures, x::array<Material> & materials)
        {
            x::graphics::application & application = x::graphics::application::get();

            __material = &materials[__index];

            x::graphics::program * program = &application.programs[__material->shader()];
            x::graphics::texture * texture = &application.textures[textures[__material->diffuse()].name()];

            return new Homeworld2::Graphics::Objects::Base(this, program, texture);
        }
    }
}
