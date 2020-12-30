#include "Multimesh.hh"

namespace Homeworld2
{
    Multimesh::Multimesh()
    :   x::graphics::object(),
        __parent(),
        __singlemeshs()
    {
    }

    Multimesh::Multimesh(const Multimesh & o)
    :   x::graphics::object(o),
        __parent(o.__parent),
        __singlemeshs(o.__singlemeshs)
    {
    }

    Multimesh::Multimesh(Multimesh && o) noexcept
    :   x::graphics::object(x::move(o)),
        __parent(x::move(o.__parent)),
        __singlemeshs(x::move(o.__singlemeshs))
    {
    }

    Multimesh::~Multimesh()
    {
    }

    Multimesh & Multimesh::operator=(const Multimesh & o)
    {
        if(&o != this)
        {
            x::graphics::object::operator=(o);
            __parent = o.__parent;
            __singlemeshs = o.__singlemeshs;
        }
        return *this;
    }

    Multimesh & Multimesh::operator=(Multimesh && o) noexcept
    {
        if(&o != this)
        {
            x::graphics::object::operator=(x::move(o));
            __parent = x::move(o.__parent);
            __singlemeshs = x::move(o.__singlemeshs);
        }
        return *this;
    }

    void Multimesh::load()
    {
        __singlemeshs.each([](Singlemesh & singlemesh){
            singlemesh.load();
        });
    }

    void Multimesh::unload()
    {
        __singlemeshs.each([](Singlemesh & singlemesh){
            singlemesh.unload();
        });
    }
    void Multimesh::render(const x::graphics::matrix & model, x::uint32 level)
    {
        __singlemeshs.each([&model, &level](Singlemesh & singlemesh){
            singlemesh.render(model, level);
        });
    }

    void Multimesh::status(x::uint32 v)
    {
        __singlemeshs.each([&v](Singlemesh & singlemesh){
            singlemesh.status(v);
        });
    }
}
