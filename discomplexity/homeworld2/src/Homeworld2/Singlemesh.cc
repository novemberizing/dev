#include "Singlemesh.hh"

#include <x/graphics/matrix.hh>

namespace Homeworld2
{
    Singlemesh::Singlemesh()
    :   x::graphics::complex()
    {
    }

    Singlemesh::Singlemesh(const Singlemesh & o)
    :   x::graphics::complex(o)
    {
    }

    Singlemesh::Singlemesh(Singlemesh && o) noexcept
    :   x::graphics::complex(x::move(o))
    {
    }

    Singlemesh::~Singlemesh()
    {
    }

    Singlemesh & Singlemesh::operator=(const Singlemesh & o)
    {
        if(&o != this)
        {
            x::graphics::complex::operator=(o);
        }
        return *this;
    }

    Singlemesh & Singlemesh::operator=(Singlemesh && o) noexcept
    {
        if(&o != this)
        {
            x::graphics::complex::operator=(x::move(o));
        }
        return *this;
    }

    void Singlemesh::render(const x::graphics::matrix & model, x::uint32 level)
    {
        if(__level == level)
        {
            x::graphics::complex::render(model, level);
        }
    }
}
