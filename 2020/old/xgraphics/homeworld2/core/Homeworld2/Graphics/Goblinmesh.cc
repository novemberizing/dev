#include "Goblinmesh.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Goblinmesh::Goblinmesh()
        :   x::graphics::reference(),
            singlemesh(),
            __parent(),
            __name()
        {
        }

        Goblinmesh::Goblinmesh(const Homeworld2::Graphics::Goblinmesh & o)
        :   x::graphics::reference(),
            singlemesh(o.singlemesh),
            __parent(o.__parent),
            __name(o.__name)
        {
        }

        Goblinmesh::Goblinmesh(Homeworld2::Graphics::Goblinmesh && o) noexcept
        :   x::graphics::reference(),
            singlemesh(x::move(o.singlemesh)),
            __parent(x::move(o.__parent)),
            __name(x::move(o.__name))
        {
        }

        Goblinmesh::~Goblinmesh()
        {
        }

        Homeworld2::Graphics::Goblinmesh & Goblinmesh::operator=(const Homeworld2::Graphics::Goblinmesh & o)
        {
            if(&o != this)
            {
                singlemesh = o.singlemesh;
                __parent = o.__parent;
                __name = o.__name;
            }
            return *this;
        }

        Homeworld2::Graphics::Goblinmesh & Goblinmesh::operator=(Homeworld2::Graphics::Goblinmesh && o) noexcept
        {
            if(&o != this)
            {
                singlemesh = x::move(o.singlemesh);
                __parent = x::move(o.__parent);
                __name = x::move(o.__name);
            }
            return *this;
        }

        void Goblinmesh::load()
        {
            singlemesh.load();
        }

        void Goblinmesh::unload()
        {
            singlemesh.unload();
        }

        void Goblinmesh::render()
        {
            singlemesh.render();
        }

        const x::string & Goblinmesh::name() const
        {
            return __name;
        }

        Homeworld2::Graphics::Objects::Single * Goblinmesh::build(x::array<x::graphics::texture> & textures, x::array<Material> & materials)
        {
            return new Homeworld2::Graphics::Objects::Single(__name, singlemesh.build(textures, materials));
        }
    }
}
