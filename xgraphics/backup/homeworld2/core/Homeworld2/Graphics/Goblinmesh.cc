#include "Goblinmesh.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Goblinmesh::Goblinmesh()
        :   x::reality::reference(),
            x::graphics::reference(),
            singlemesh(),
            __parent()
        {
        }

        Goblinmesh::Goblinmesh(const Goblinmesh & o)
        :   x::reality::reference(o),
            x::graphics::reference(o),
            singlemesh(o.singlemesh),
            __parent(o.__parent)
        {
        }

        Goblinmesh::Goblinmesh(Goblinmesh && o) noexcept
        :   x::reality::reference(x::move(o)),
            x::graphics::reference(x::move(o)),
            singlemesh(x::move(o.singlemesh)),
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
                x::graphics::reference::operator=(o);

                singlemesh = o.singlemesh;
                __parent = o.__parent;
            }
            return *this;
        }

        Goblinmesh & Goblinmesh::operator=(Goblinmesh && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::reference::operator=(x::move(o));
                
                singlemesh = x::move(o.singlemesh);
                __parent = x::move(o.__parent);
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

        void Goblinmesh::render(const x::reality::matrix & model)
        {
            singlemesh.render(model);
        }
    }
}
