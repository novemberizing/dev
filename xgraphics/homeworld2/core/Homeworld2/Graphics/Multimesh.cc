#include "Multimesh.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Multimesh::Multimesh()
        :   x::graphics::reference(),
            __name(),
            __parent(),
            singlemeshs()
        {
        }

        Multimesh::Multimesh(const Multimesh & o)
        :   x::graphics::reference(),
            __name(o.__name),
            __parent(o.__parent),
            singlemeshs(o.singlemeshs)
        {
        }

        Multimesh::Multimesh(Multimesh && o) noexcept
        :   x::graphics::reference(),
            __name(x::move(o.__name)),
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
                __name = o.__name;
                __parent = o.__parent;
                singlemeshs = o.singlemeshs;
            }
            return *this;
        }

        Multimesh & Multimesh::operator=(Multimesh && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __parent = x::move(o.__parent);
                singlemeshs = x::move(o.singlemeshs);
            }
            return *this;
        }

        const x::string & Multimesh::name() const
        {
            return __name;
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

        void Multimesh::render()
        {
            singlemeshs.each([](Singlemesh & singlemesh){
                singlemesh.render();
            });
        }

        Homeworld2::Graphics::Objects::Multi * Multimesh::build(x::array<x::graphics::texture> & textures, x::array<Material> & materials)
        {
            Homeworld2::Graphics::Objects::Multi * multi = new Homeworld2::Graphics::Objects::Multi(__name);

            singlemeshs.each([multi, &textures, &materials](Singlemesh & singlemesh){
                multi->add(singlemesh.build(textures, materials));
            });

            return multi;
        }
    }
}
