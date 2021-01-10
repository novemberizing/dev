#include "Singlemesh.hh"

#include <x/reality/matrix.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        Singlemesh::Singlemesh()
        :   x::graphics::reference(),
            __name(),
            __index(x::invalid),
            __level(0),
            children()
        {
        }

        Singlemesh::Singlemesh(const Homeworld2::Graphics::Singlemesh & o)
        :   x::graphics::reference(),
            __name(o.__name),
            __index(o.__index),
            __level(o.__level),
            children(o.children)
        {
        }

        Singlemesh::Singlemesh(Homeworld2::Graphics::Singlemesh && o) noexcept
        :   x::graphics::reference(),
            __name(x::move(o.__name)),
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

        Homeworld2::Graphics::Singlemesh & Singlemesh::operator=(const Homeworld2::Graphics::Singlemesh & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __index = o.__index;
                __level = o.__level;
                children = o.children;
            }
            return *this;
        }

        Homeworld2::Graphics::Singlemesh & Singlemesh::operator=(Homeworld2::Graphics::Singlemesh && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __index = o.__index;
                __level = o.__level;
                children = x::move(o.children);

                o.__index = x::invalid;
                o.__level = 0;
            }
            return *this;
        }

        const x::string & Singlemesh::name() const
        {
            return __name;
        }

        void Singlemesh::render()
        {
            if(__level == 0)
            {
                children.each([](Homeworld2::Graphics::Primitive & o) {
                    o.render();
                });
            }
        }

        void Singlemesh::load()
        {
            children.each([](Homeworld2::Graphics::Primitive & o){
                o.load();
            });
        }

        void Singlemesh::unload()
        {
            children.each([](Homeworld2::Graphics::Primitive & o){
                o.unload();
            });
        }

        Homeworld2::Graphics::Objects::Lod * Singlemesh::build(x::array<x::graphics::texture> & textures, x::array<Material> & materials)
        {
            Homeworld2::Graphics::Objects::Lod * lod = new Homeworld2::Graphics::Objects::Lod(__level);

            children.each([lod, &textures, &materials](Homeworld2::Graphics::Primitive & primitive){
                lod->add(primitive.build(textures, materials));
            });

            return lod;
        }
    }
}
