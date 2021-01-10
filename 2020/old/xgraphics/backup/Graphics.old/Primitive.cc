#include "Primitive.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Primitive::Primitive()
        :   x::reality::reference(),
            x::graphics::primitive(""),
            __index(x::invalid),
            __material(nullptr)
        {
        }

        Primitive::Primitive(const Primitive & o)
        :   x::reality::reference(),
            x::graphics::primitive(o),
            __index(o.__index),
            __material(o.__material)
        {
        }

        Primitive::Primitive(Primitive && o) noexcept
        :   x::reality::reference(),
            x::graphics::primitive(x::move(o)),
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

        Homeworld2::Graphics::Primitive & Homeworld2::Graphics::Primitive::operator=(const Homeworld2::Graphics::Primitive & o)
        {
            if(&o != this)
            {
                x::graphics::primitive::operator=(o);

                __index = o.__index;
                __material = o.__material;
            }
            return *this;
        }

        Homeworld2::Graphics::Primitive & Homeworld2::Graphics::Primitive::operator=(Homeworld2::Graphics::Primitive && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::primitive::operator=(x::move(o));

                __index = o.__index;
                __material = o.__material;

                o.__index = x::invalid;
                o.__material = nullptr;
            }
            return *this;
        }
    }
}
