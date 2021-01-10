#include "Multimesh.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Multimesh::Multimesh()
        :   x::reality::reference(),
            x::graphics::reference(),
            __parent(),
            singlemeshs()
        {
        }

        Multimesh::Multimesh(const Multimesh & o)
        :   x::reality::reference(o),
            x::graphics::reference(o),
            __parent(o.__parent),
            singlemeshs(o.singlemeshs)
        {
        }

        Multimesh::Multimesh(Multimesh && o) noexcept
        :   x::reality::reference(x::move(o)),
            x::graphics::reference(x::move(o)),
            __parent(x::move(o.__parent)),
            singlemeshs(x::move(o.singlemeshs))
        {
        }

        Multimesh::~Multimesh()
        {
        }

        Multimesh & Multimesh::operator=(const Multimesh & o)
        {
            if(&o != this)
            {
                x::graphics::reference::operator=(o);
                __parent = o.__parent;
                singlemeshs = o.singlemeshs;
            }
            return *this;
        }

        Multimesh & Multimesh::operator=(Multimesh && o) noexcept
        {
            if(&o != this)
            {
                x::graphics::reference::operator=(x::move(o));
                __parent = x::move(o.__parent);
                singlemeshs = x::move(o.singlemeshs);
            }
            return *this;
        }


        void Multimesh::load()
        {
            singlemeshs.each([](Singlemesh & singlemesh){
                singlemesh.load();
            });
        }

        void Multimesh::unload()
        {
            singlemeshs.each([](Singlemesh & singlemesh){
                singlemesh.unload();
            });
        }

        void Multimesh::render(const x::reality::matrix & model)
        {
            singlemeshs.each([&model](Singlemesh & singlemesh){
                singlemesh.render(model);
            });
        }
    }
}
