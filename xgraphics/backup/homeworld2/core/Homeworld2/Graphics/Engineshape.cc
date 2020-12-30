#include "Engineshape.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Engineshape::Engineshape()
        :   x::graphics::primitive(),
            __parent()
        {
        }

        Engineshape::Engineshape(const Engineshape & o)
        :   x::graphics::primitive(o),
            __parent(o.__parent)
        {
        }

        Engineshape::Engineshape(Engineshape && o) noexcept
        :   x::graphics::primitive(x::move(o)),
            __parent(x::move(o.__parent))
        {
        }

        Engineshape::~Engineshape()
        {
        }

        Engineshape & Engineshape::operator=(const Engineshape & o)
        {
            if(&o != this)
            {
                x::graphics::primitive::operator=(o);
                __parent = o.__parent;
            }
            return *this;
        }

        Engineshape & Engineshape::operator=(Engineshape && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::primitive::operator=(x::move(o));
                __parent = x::move(o.__parent);
            }
            return *this;
        }
    }
}
