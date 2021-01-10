#include "Singlemesh.hh"

#include <x/reality/matrix.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        Singlemesh::Singlemesh()
        :   x::reality::reference(),
            x::graphics::reference(),
            __index(x::invalid),
            __level(0),
            children()
        {
        }

        Singlemesh::Singlemesh(const Singlemesh & o)
        :   x::reality::reference(o),
            x::graphics::reference(o),
            __index(o.__index),
            __level(o.__level),
            children(o.children)
        {
        }

        Singlemesh::Singlemesh(Singlemesh && o) noexcept
        :   x::reality::reference(x::move(o)),
            x::graphics::reference(x::move(o)),
            __index(o.__index),
            __level(o.__level),
            children(x::move(o.children))
        {
            o.__index = x::invalid;
            o.__level = 0;
        }

        Singlemesh::~Singlemesh()
        {
            __index = x::invalid;
            __level = 0;
        }

        Singlemesh & Singlemesh::operator=(const Singlemesh & o)
        {
            if(&o != this)
            {
                // x::reality::reference::operator=(o);
                x::graphics::reference::operator=(o);

                __index = o.__index;
                __level = o.__level;
                children = o.children;
            }
            return *this;
        }

        Singlemesh & Singlemesh::operator=(Singlemesh && o) noexcept
        {
            if(&o != this)
            {
                // x::reality::reference::operator=(x::move(o));
                x::graphics::reference::operator=(x::move(o));

                __index = o.__index;
                __level = o.__level;
                children = x::move(o.children);

                o.__index = x::invalid;
            }
            return *this;
        }

        void Singlemesh::render(const x::reality::matrix & model)
        {
            if(__level == 0)
            {
                // x::console::out << "single render" << x::endl << x::flush;
                children.each([&model](typename x::var<Primitive *>::type & o) {
                    o->render(model);
                });
            }
        }

        void Singlemesh::load()
        {
            children.each([](typename x::var<Primitive *>::type & o){
                o->load();
            });
        }

        void Singlemesh::unload()
        {
            children.each([](typename x::var<Primitive *>::type & o){
                o->unload();
            });
        }
    }
}
