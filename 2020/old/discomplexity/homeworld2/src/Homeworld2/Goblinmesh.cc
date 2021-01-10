#include "Goblinmesh.hh"

namespace Homeworld2
{
    Goblinmesh::Goblinmesh()
    :   x::graphics::object(),
        __singlemesh(),
        __parent()
    {
    }

    Goblinmesh::Goblinmesh(const Goblinmesh & o)
    :   x::graphics::object(o),
        __singlemesh(o.__singlemesh),
        __parent(o.__parent)
    {
    }

    Goblinmesh::Goblinmesh(Goblinmesh && o) noexcept
    :   x::graphics::object(x::move(o)),
        __singlemesh(x::move(o.__singlemesh)),
        __parent(x::move(o.__parent))
    {
    }

    Goblinmesh::~Goblinmesh()
    {
    }

    Goblinmesh & Goblinmesh::operator=(const Goblinmesh & o)
    {
        if(&o != this)
        {
            x::graphics::object::operator=(o);
            __singlemesh = o.__singlemesh;
            __parent = o.__parent;
        }
        return *this;
    }

    Goblinmesh & Goblinmesh::operator=(Goblinmesh && o) noexcept
    {
        if(&o != this)
        {
            x::graphics::object::operator=(x::move(o));
            __singlemesh = x::move(o.__singlemesh);
            __parent = x::move(o.__parent);
        }
        return *this;
    }

    void Goblinmesh::load()
    {
        __singlemesh.load();
    }
    void Goblinmesh::unload()
    {
        __singlemesh.unload();
    }
    void Goblinmesh::render(const x::graphics::matrix & model, x::uint32 level)
    {
        __singlemesh.render(model, level);
    }

    void Goblinmesh::status(x::uint32 v)
    {
        __singlemesh.status(v);
    }
}
